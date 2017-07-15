/*
 * Copyright (C) 2017 Incognito
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "misc.h"

#include "../core.h"
#include "../main.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

using namespace Utility;

boost::unordered_map<int, Item::SharedActor>::iterator Utility::destroyActor(boost::unordered_map<int, Item::SharedActor>::iterator a)
{
	Item::Actor::identifier.remove(a->first, core->getData()->actors.size());
	boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.find(a->first);
	if (i != core->getData()->internalActors.end())
	{
		core->getData()->destroyedActors.push_back(i->second);
		core->getData()->internalActors.quick_erase(i);
	}
	boost::unordered_map<int, Item::SharedActor>::iterator d = core->getData()->discoveredActors.find(a->first);
	if (d != core->getData()->discoveredActors.end())
	{
		core->getData()->discoveredActors.erase(d);
	}
	core->getGrid()->removeActor(a->second);
	return core->getData()->actors.erase(a);
}

boost::unordered_map<int, Item::SharedArea>::iterator Utility::destroyArea(boost::unordered_map<int, Item::SharedArea>::iterator a)
{
	Item::Area::identifier.remove(a->first, core->getData()->areas.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.internalAreas.erase(a->first);
		p->second.visibleCell->areas.erase(a->first);
	}
	core->getGrid()->removeArea(a->second);
	return core->getData()->areas.erase(a);
}

boost::unordered_map<int, Item::SharedCheckpoint>::iterator Utility::destroyCheckpoint(boost::unordered_map<int, Item::SharedCheckpoint>::iterator c)
{
	Item::Checkpoint::identifier.remove(c->first, core->getData()->checkpoints.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		if (p->second.visibleCheckpoint == c->first)
		{
			sampgdk::DisablePlayerCheckpoint(p->first);
			p->second.activeCheckpoint = 0;
			p->second.visibleCheckpoint = 0;
		}
		p->second.visibleCell->checkpoints.erase(c->first);
	}
	core->getGrid()->removeCheckpoint(c->second);
	return core->getData()->checkpoints.erase(c);
}

boost::unordered_map<int, Item::SharedMapIcon>::iterator Utility::destroyMapIcon(boost::unordered_map<int, Item::SharedMapIcon>::iterator m)
{
	Item::MapIcon::identifier.remove(m->first, core->getData()->mapIcons.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
		if (i != p->second.internalMapIcons.end())
		{
			sampgdk::RemovePlayerMapIcon(p->first, i->second);
			p->second.mapIconIdentifier.remove(i->second, p->second.internalMapIcons.size());
			p->second.internalMapIcons.quick_erase(i);
		}
		p->second.visibleCell->mapIcons.erase(m->first);
	}
	core->getGrid()->removeMapIcon(m->second);
	return core->getData()->mapIcons.erase(m);
}

boost::unordered_map<int, Item::SharedObject>::iterator Utility::destroyObject(boost::unordered_map<int, Item::SharedObject>::iterator o)
{
	Item::Object::identifier.remove(o->first, core->getData()->objects.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
		if (i != p->second.internalObjects.end())
		{
			sampgdk::DestroyPlayerObject(p->first, i->second);
			p->second.internalObjects.quick_erase(i);
		}
		p->second.visibleCell->objects.erase(o->first);
	}
	core->getGrid()->removeObject(o->second);
	return core->getData()->objects.erase(o);
}

boost::unordered_map<int, Item::SharedPickup>::iterator Utility::destroyPickup(boost::unordered_map<int, Item::SharedPickup>::iterator p)
{
	Item::Pickup::identifier.remove(p->first, core->getData()->pickups.size());
	boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.find(p->first);
	if (i != core->getData()->internalPickups.end())
	{
		sampgdk::DestroyPickup(i->second);
		core->getData()->internalPickups.quick_erase(i);
	}
	boost::unordered_map<int, Item::SharedPickup>::iterator d = core->getData()->discoveredPickups.find(p->first);
	if (d != core->getData()->discoveredPickups.end())
	{
		core->getData()->discoveredPickups.erase(d);
	}
	core->getGrid()->removePickup(p->second);
	return core->getData()->pickups.erase(p);
}

boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator Utility::destroyRaceCheckpoint(boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r)
{
	Item::RaceCheckpoint::identifier.remove(r->first, core->getData()->raceCheckpoints.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		if (p->second.visibleRaceCheckpoint == r->first)
		{
			sampgdk::DisablePlayerRaceCheckpoint(p->first);
			p->second.activeRaceCheckpoint = 0;
			p->second.visibleRaceCheckpoint = 0;
		}
		p->second.visibleCell->raceCheckpoints.erase(r->first);
	}
	core->getGrid()->removeRaceCheckpoint(r->second);
	return core->getData()->raceCheckpoints.erase(r);
}

boost::unordered_map<int, Item::SharedTextLabel>::iterator Utility::destroyTextLabel(boost::unordered_map<int, Item::SharedTextLabel>::iterator t)
{
	Item::TextLabel::identifier.remove(t->first, core->getData()->textLabels.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
		if (i != p->second.internalTextLabels.end())
		{
			sampgdk::DeletePlayer3DTextLabel(p->first, i->second);
			p->second.internalTextLabels.quick_erase(i);
		}
		p->second.visibleCell->textLabels.erase(t->first);
	}
	core->getGrid()->removeTextLabel(t->second);
	return core->getData()->textLabels.erase(t);
}

std::size_t Utility::getChunkTickRate(int type, int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			switch (type)
			{
				case STREAMER_TYPE_OBJECT:
				{
					return p->second.chunkTickRate[STREAMER_TYPE_OBJECT];
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					return p->second.chunkTickRate[STREAMER_TYPE_MAP_ICON];
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					return p->second.chunkTickRate[STREAMER_TYPE_3D_TEXT_LABEL];
				}
			}
		}
	}
	return core->getData()->getGlobalChunkTickRate(type);
}

bool Utility::setChunkTickRate(int type, std::size_t value, int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			switch (type)
			{
				case STREAMER_TYPE_OBJECT:
				{
					p->second.chunkTickRate[STREAMER_TYPE_OBJECT] = value;
					return true;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					p->second.chunkTickRate[STREAMER_TYPE_MAP_ICON] = value;
					return true;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					p->second.chunkTickRate[STREAMER_TYPE_3D_TEXT_LABEL] = value;
					return true;
				}
			}
		}
	}
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		switch (type)
		{
			case STREAMER_TYPE_OBJECT:
			{
				p->second.chunkTickRate[STREAMER_TYPE_OBJECT] = value;
				break;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				p->second.chunkTickRate[STREAMER_TYPE_MAP_ICON] = value;
				break;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				p->second.chunkTickRate[STREAMER_TYPE_3D_TEXT_LABEL] = value;
				break;
			}
		}
	}
	return core->getData()->setGlobalChunkTickRate(type, value);
}

std::size_t Utility::getMaxVisibleItems(int type, int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			switch (type)
			{
				case STREAMER_TYPE_OBJECT:
				{
					return p->second.maxVisibleObjects;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					return p->second.maxVisibleMapIcons;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					return p->second.maxVisibleTextLabels;
				}
			}
		}
	}
	return core->getData()->getGlobalMaxVisibleItems(type);
}

bool Utility::setMaxVisibleItems(int type, std::size_t value, int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			switch (type)
			{
				case STREAMER_TYPE_OBJECT:
				{
					p->second.maxVisibleObjects = value;
					return true;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					p->second.maxVisibleMapIcons = value;
					return true;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					p->second.maxVisibleTextLabels = value;
					return true;
				}
			}
		}
	}
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		switch (type)
		{
			case STREAMER_TYPE_OBJECT:
			{
				p->second.maxVisibleObjects = value;
				break;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				p->second.maxVisibleMapIcons = value;
				break;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				p->second.maxVisibleTextLabels = value;
				break;
			}
		}
	}
	return core->getData()->setGlobalMaxVisibleItems(type, value);
}

float Utility::getRadiusMultiplier(int type, int playerid)
{
	if (type >= 0 && type < STREAMER_MAX_TYPES)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				return p->second.radiusMultipliers[type];
			}
		}
	}
	return core->getData()->getGlobalRadiusMultiplier(type);
}

bool Utility::setRadiusMultiplier(int type, float value, int playerid)
{
	if (type >= 0 && type < STREAMER_MAX_TYPES)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				p->second.radiusMultipliers[type] = value;
				return true;
			}
		}
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			p->second.radiusMultipliers[type] = value;
		}
	}
	return core->getData()->setGlobalRadiusMultiplier(type, value);
}

bool Utility::haveAllPlayersCheckedActors()
{
	if (!core->getData()->players.empty())
	{
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			if (!p->second.checkedActors && p->second.enabledItems[STREAMER_TYPE_ACTOR])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Utility::haveAllPlayersCheckedPickups()
{
	if (!core->getData()->players.empty())
	{
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			if (!p->second.checkedPickups && p->second.enabledItems[STREAMER_TYPE_PICKUP])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void Utility::processPendingDestroyedActors()
{
	if (!core->getData()->destroyedActors.empty())
	{
		std::vector<int>::iterator a = core->getData()->destroyedActors.begin();
		while (a != core->getData()->destroyedActors.end())
		{
			sampgdk::DestroyActor(*a);
			a = core->getData()->destroyedActors.erase(a);
		}
	}
}
