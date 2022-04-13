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

#include "../main.h"

#include "misc.h"
#include "../core.h"

using namespace Utility;

std::unordered_map<int, Item::SharedActor>::iterator Utility::destroyActor(std::unordered_map<int, Item::SharedActor>::iterator a)
{
	Item::Actor::identifier.remove(a->first, core->getData()->actors.size());
	for (std::unordered_set<int>::const_iterator w = a->second->worlds.begin(); w != a->second->worlds.end(); ++w)
	{
		std::unordered_map<std::pair<int, int>, int, pair_hash>::iterator i = core->getData()->internalActors.find(std::make_pair(a->first, *w));
		if (i != core->getData()->internalActors.end())
		{
			core->getData()->destroyedActors.push_back(i->second);
			core->getData()->internalActors.erase(i);
		}
		std::unordered_map<std::pair<int, int>, Item::SharedActor, pair_hash>::iterator d = core->getData()->discoveredActors.find(std::make_pair(a->first, *w));
		if (d != core->getData()->discoveredActors.end())
		{
			core->getData()->discoveredActors.erase(d);
		}
	}
	core->getGrid()->removeActor(a->second);
	return core->getData()->actors.erase(a);
}

std::unordered_map<int, Item::SharedArea>::iterator Utility::destroyArea(std::unordered_map<int, Item::SharedArea>::iterator a)
{
	Item::Area::identifier.remove(a->first, core->getData()->areas.size());
	for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.internalAreas.erase(a->first);
		p->second.visibleCell->areas.erase(a->first);
	}
	core->getGrid()->removeArea(a->second);
	return core->getData()->areas.erase(a);
}

std::unordered_map<int, Item::SharedCheckpoint>::iterator Utility::destroyCheckpoint(std::unordered_map<int, Item::SharedCheckpoint>::iterator c)
{
	Item::Checkpoint::identifier.remove(c->first, core->getData()->checkpoints.size());
	for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		if (p->second.visibleCheckpoint == c->first)
		{
			ompgdk::DisablePlayerCheckpoint(p->first);
			p->second.activeCheckpoint = 0;
			p->second.visibleCheckpoint = 0;
		}
		p->second.visibleCell->checkpoints.erase(c->first);
	}
	core->getGrid()->removeCheckpoint(c->second);
	return core->getData()->checkpoints.erase(c);
}

std::unordered_map<int, Item::SharedMapIcon>::iterator Utility::destroyMapIcon(std::unordered_map<int, Item::SharedMapIcon>::iterator m)
{
	Item::MapIcon::identifier.remove(m->first, core->getData()->mapIcons.size());
	for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		Item::Bimap<Item::SharedMapIcon>::Type::right_iterator d = p->second.discoveredMapIcons.right.find(std::make_tuple(m->first, m->second));
		if (d != p->second.discoveredMapIcons.right.end())
		{
			p->second.discoveredMapIcons.right.erase(d);
		}
		Item::Bimap<Item::SharedMapIcon>::Type::right_iterator e = p->second.existingMapIcons.right.find(std::make_tuple(m->first, m->second));
		if (e != p->second.existingMapIcons.right.end())
		{
			p->second.existingMapIcons.right.erase(e);
		}
		std::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
		if (i != p->second.internalMapIcons.end())
		{
			ompgdk::RemovePlayerMapIcon(p->first, i->second);
			p->second.mapIconIdentifier.remove(i->second, p->second.internalMapIcons.size());
			p->second.internalMapIcons.erase(i);
		}
		std::unordered_set<int>::iterator r = p->second.removedMapIcons.find(m->first);
		if (r != p->second.removedMapIcons.end())
		{
			p->second.removedMapIcons.erase(r);
		}
		p->second.visibleCell->mapIcons.erase(m->first);
	}
	core->getGrid()->removeMapIcon(m->second);
	return core->getData()->mapIcons.erase(m);
}

std::unordered_map<int, Item::SharedObject>::iterator Utility::destroyObject(std::unordered_map<int, Item::SharedObject>::iterator o)
{
	Item::Object::identifier.remove(o->first, core->getData()->objects.size());
	for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		Item::Bimap<Item::SharedObject>::Type::right_iterator d = p->second.discoveredObjects.right.find(std::make_tuple(o->first, o->second));
		if (d != p->second.discoveredObjects.right.end())
		{
			p->second.discoveredObjects.right.erase(d);
		}
		Item::Bimap<Item::SharedObject>::Type::right_iterator e = p->second.existingObjects.right.find(std::make_tuple(o->first, o->second));
		if (e != p->second.existingObjects.right.end())
		{
			p->second.existingObjects.right.erase(e);
		}
		std::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
		if (i != p->second.internalObjects.end())
		{
			ompgdk::DestroyPlayerObject(p->first, i->second);
			p->second.internalObjects.erase(i);
		}
		std::unordered_set<int>::iterator r = p->second.removedObjects.find(o->first);
		if (r != p->second.removedObjects.end())
		{
			p->second.removedObjects.erase(r);
		}
		p->second.visibleCell->objects.erase(o->first);
	}
	core->getGrid()->removeObject(o->second);
	return core->getData()->objects.erase(o);
}

std::unordered_map<int, Item::SharedPickup>::iterator Utility::destroyPickup(std::unordered_map<int, Item::SharedPickup>::iterator p)
{
	Item::Pickup::identifier.remove(p->first, core->getData()->pickups.size());
	for (std::unordered_set<int>::const_iterator w = p->second->worlds.begin(); w != p->second->worlds.end(); ++w)
	{
		std::unordered_map<std::pair<int, int>, int, pair_hash>::iterator i = core->getData()->internalPickups.find(std::make_pair(p->first, *w));
		if (i != core->getData()->internalPickups.end())
		{
			ompgdk::DestroyPickup(i->second);
			core->getData()->internalPickups.erase(i);
		}
		std::unordered_map<std::pair<int, int>, Item::SharedPickup, pair_hash>::iterator d = core->getData()->discoveredPickups.find(std::make_pair(p->first, *w));
		if (d != core->getData()->discoveredPickups.end())
		{
			core->getData()->discoveredPickups.erase(d);
		}
	}
	core->getGrid()->removePickup(p->second);
	return core->getData()->pickups.erase(p);
}

std::unordered_map<int, Item::SharedRaceCheckpoint>::iterator Utility::destroyRaceCheckpoint(std::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r)
{
	Item::RaceCheckpoint::identifier.remove(r->first, core->getData()->raceCheckpoints.size());
	for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		if (p->second.visibleRaceCheckpoint == r->first)
		{
			ompgdk::DisablePlayerRaceCheckpoint(p->first);
			p->second.activeRaceCheckpoint = 0;
			p->second.visibleRaceCheckpoint = 0;
		}
		p->second.visibleCell->raceCheckpoints.erase(r->first);
	}
	core->getGrid()->removeRaceCheckpoint(r->second);
	return core->getData()->raceCheckpoints.erase(r);
}

std::unordered_map<int, Item::SharedTextLabel>::iterator Utility::destroyTextLabel(std::unordered_map<int, Item::SharedTextLabel>::iterator t)
{
	Item::TextLabel::identifier.remove(t->first, core->getData()->textLabels.size());
	for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		Item::Bimap<Item::SharedTextLabel>::Type::right_iterator d = p->second.discoveredTextLabels.right.find(std::make_tuple(t->first, t->second));
		if (d != p->second.discoveredTextLabels.right.end())
		{
			p->second.discoveredTextLabels.right.erase(d);
		}
		Item::Bimap<Item::SharedTextLabel>::Type::right_iterator e = p->second.existingTextLabels.right.find(std::make_tuple(t->first, t->second));
		if (e != p->second.existingTextLabels.right.end())
		{
			p->second.existingTextLabels.right.erase(e);
		}
		std::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
		if (i != p->second.internalTextLabels.end())
		{
			ompgdk::DeletePlayer3DTextLabel(p->first, i->second);
			p->second.internalTextLabels.erase(i);
		}
		std::unordered_set<int>::iterator r = p->second.removedTextLabels.find(t->first);
		if (r != p->second.removedTextLabels.end())
		{
			p->second.removedTextLabels.erase(r);
		}
		p->second.visibleCell->textLabels.erase(t->first);
	}
	core->getGrid()->removeTextLabel(t->second);
	return core->getData()->textLabels.erase(t);
}

std::size_t Utility::getChunkTickRate(int type, int playerid)
{
	if (playerid >= 0 && playerid < PLAYER_POOL_SIZE)
	{
		std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
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
	if (playerid >= 0 && playerid < PLAYER_POOL_SIZE)
	{
		std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
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
	for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
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
	if (playerid >= 0 && playerid < PLAYER_POOL_SIZE)
	{
		std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
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
	if (playerid >= 0 && playerid < PLAYER_POOL_SIZE)
	{
		std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
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
	for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
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
		if (playerid >= 0 && playerid < PLAYER_POOL_SIZE)
		{
			std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
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
		if (playerid >= 0 && playerid < PLAYER_POOL_SIZE)
		{
			std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				p->second.radiusMultipliers[type] = value;
				return true;
			}
		}
		for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			p->second.radiusMultipliers[type] = value;
		}
	}
	return core->getData()->setGlobalRadiusMultiplier(type, value);
}

void Utility::processPendingDestroyedActors()
{
	if (!core->getData()->destroyedActors.empty())
	{
		std::vector<int>::iterator a = core->getData()->destroyedActors.begin();
		while (a != core->getData()->destroyedActors.end())
		{
			if (ompgdk::IsValidActor(*a))
			{
				ompgdk::DestroyActor(*a);
			}
			a = core->getData()->destroyedActors.erase(a);
		}
	}
}
