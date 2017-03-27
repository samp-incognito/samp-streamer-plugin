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

#include "../natives.h"

#include "../core.h"
#include "../utility.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::Streamer_GetDistanceToItem(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "Streamer_GetDistanceToItem");
	int dimensions = static_cast<int>(params[7]);
	Eigen::Vector3f position = Eigen::Vector3f::Zero();
	switch (static_cast<int>(params[4]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[5]));
			if (o != core->getData()->objects.end())
			{
				if (o->second->attach)
				{
					position = o->second->attach->position;
				}
				else
				{
					position = o->second->position;
				}
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[5]));
			if (p != core->getData()->pickups.end())
			{
				position = p->second->position;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[5]));
			if (c != core->getData()->checkpoints.end())
			{
				position = c->second->position;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[5]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				position = r->second->position;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[5]));
			if (m != core->getData()->mapIcons.end())
			{
				position = m->second->position;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[5]));
			if (t != core->getData()->textLabels.end())
			{
				if (t->second->attach)
				{
					position = t->second->attach->position;
				}
				else
				{
					position = t->second->position;
				}
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[5]));
			if (a != core->getData()->areas.end())
			{
				switch (a->second->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					case STREAMER_AREA_TYPE_CYLINDER:
					{
						float distance = 0.0f;
						if (a->second->attach)
						{
							distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(a->second->attach->position[0], a->second->attach->position[1])));
						}
						else
						{
							distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), boost::get<Eigen::Vector2f>(a->second->position)));
						}
						Utility::storeFloatInNative(amx, params[6], distance);
						return 1;
					}
					case STREAMER_AREA_TYPE_SPHERE:
					{
						if (a->second->attach)
						{
							position = a->second->attach->position;
						}
						else
						{
							position = boost::get<Eigen::Vector3f>(a->second->position);
						}
						break;
					}
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Box2D>(a->second->position));
						float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
						Utility::storeFloatInNative(amx, params[6], distance);
						return 1;
					}
					case STREAMER_AREA_TYPE_CUBOID:
					{
						Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3D>(a->second->position));
						float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), centroid));
						Utility::storeFloatInNative(amx, params[6], distance);
						return 1;
					}
					case STREAMER_AREA_TYPE_POLYGON:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2D>(a->second->position));
						float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
						Utility::storeFloatInNative(amx, params[6], distance);
						return 1;
					}
				}
			}
			return 0;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[5]));
			if (a != core->getData()->actors.end())
			{
				position = a->second->position;
				break;
			}
			return 0;
		}
		default:
		{
			Utility::logError("Streamer_GetDistanceToItem: Invalid type specified");
			return 0;
		}
	}
	switch (dimensions)
	{
		case 2:
		{
			float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(position[0], position[1])));
			Utility::storeFloatInNative(amx, params[6], distance);
			return 1;
		}
		case 3:
		{
			float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), position));
			Utility::storeFloatInNative(amx, params[6], distance);
			return 1;
		}
		default:
		{
			Utility::logError("Streamer_GetDistanceToItem: Invalid number of dimensions specified (outside range of 2-3)");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleItem(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_ToggleItem");
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[3]));
			if (o != core->getData()->objects.end())
			{
				if (!static_cast<int>(params[4]))
				{
					return static_cast<cell>(Utility::removeFromContainer(o->second->players, static_cast<int>(params[1])));
				}
				else
				{
					return static_cast<cell>(Utility::addToContainer(o->second->players, static_cast<int>(params[1])));
				}
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[3]));
			if (p != core->getData()->pickups.end())
			{
				if (!static_cast<int>(params[4]))
				{
					return static_cast<cell>(Utility::removeFromContainer(p->second->players, static_cast<int>(params[1])));
				}
				else
				{
					return static_cast<cell>(Utility::addToContainer(p->second->players, static_cast<int>(params[1])));
				}
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[3]));
			if (c != core->getData()->checkpoints.end())
			{
				if (!static_cast<int>(params[4]))
				{
					return static_cast<cell>(Utility::removeFromContainer(c->second->players, static_cast<int>(params[1])));
				}
				else
				{
					return static_cast<cell>(Utility::addToContainer(c->second->players, static_cast<int>(params[1])));
				}
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[3]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				if (!static_cast<int>(params[4]))
				{
					return static_cast<cell>(Utility::removeFromContainer(r->second->players, static_cast<int>(params[1])));
				}
				else
				{
					return static_cast<cell>(Utility::addToContainer(r->second->players, static_cast<int>(params[1])));
				}
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[3]));
			if (m != core->getData()->mapIcons.end())
			{
				if (!static_cast<int>(params[4]))
				{
					return static_cast<cell>(Utility::removeFromContainer(m->second->players, static_cast<int>(params[1])));
				}
				else
				{
					return static_cast<cell>(Utility::addToContainer(m->second->players, static_cast<int>(params[1])));
				}
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[3]));
			if (t != core->getData()->textLabels.end())
			{
				if (!static_cast<int>(params[4]))
				{
					return static_cast<cell>(Utility::removeFromContainer(t->second->players, static_cast<int>(params[1])));
				}
				else
				{
					return static_cast<cell>(Utility::addToContainer(t->second->players, static_cast<int>(params[1])));
				}
			}
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[3]));
			if (a != core->getData()->areas.end())
			{
				if (!static_cast<int>(params[4]))
				{
					return static_cast<cell>(Utility::removeFromContainer(a->second->players, static_cast<int>(params[1])));
				}
				else
				{
					return static_cast<cell>(Utility::addToContainer(a->second->players, static_cast<int>(params[1])));
				}
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[3]));
			if (a != core->getData()->actors.end())
			{
				if (!static_cast<int>(params[4]))
				{
					return static_cast<cell>(Utility::removeFromContainer(a->second->players, static_cast<int>(params[1])));
				}
				else
				{
					return static_cast<cell>(Utility::addToContainer(a->second->players, static_cast<int>(params[1])));
				}
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_ToggleItem: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleItem(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_IsToggleItem");
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[3]));
			if (o != core->getData()->objects.end())
			{
				return static_cast<cell>(Utility::isInContainer(o->second->players, static_cast<int>(params[1])));
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[3]));
			if (p != core->getData()->pickups.end())
			{
				return static_cast<cell>(Utility::isInContainer(p->second->players, static_cast<int>(params[1])));
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[3]));
			if (c != core->getData()->checkpoints.end())
			{
				return static_cast<cell>(Utility::isInContainer(c->second->players, static_cast<int>(params[1])));
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[3]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				return static_cast<cell>(Utility::isInContainer(r->second->players, static_cast<int>(params[1])));
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[3]));
			if (m != core->getData()->mapIcons.end())
			{
				return static_cast<cell>(Utility::isInContainer(m->second->players, static_cast<int>(params[1])));
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[3]));
			if (t != core->getData()->textLabels.end())
			{
				return static_cast<cell>(Utility::isInContainer(t->second->players, static_cast<int>(params[1])));
			}
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[3]));
			if (a != core->getData()->areas.end())
			{
				return static_cast<cell>(Utility::isInContainer(a->second->players, static_cast<int>(params[1])));
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[3]));
			if (a != core->getData()->actors.end())
			{
				return static_cast<cell>(Utility::isInContainer(a->second->players, static_cast<int>(params[1])));
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_IsToggleItem: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleAllItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "Streamer_ToggleAllItems");
	boost::unordered_set<int> exceptions;
	Utility::convertArrayToContainer(amx, params[4], params[5], exceptions);
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			for (boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.begin(); o != core->getData()->objects.end(); ++o)
			{
				boost::unordered_set<int>::iterator e = exceptions.find(o->first);
				if (e == exceptions.end())
				{
					if (!static_cast<int>(params[3]))
					{
						Utility::removeFromContainer(o->second->players, static_cast<int>(params[1]));
					}
					else
					{
						Utility::addToContainer(o->second->players, static_cast<int>(params[1]));
					}
				}
			}
			return 1;
		}
		case STREAMER_TYPE_PICKUP:
		{
			for (boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.begin(); p != core->getData()->pickups.end(); ++p)
			{
				boost::unordered_set<int>::iterator e = exceptions.find(p->first);
				if (e == exceptions.end())
				{
					if (!static_cast<int>(params[3]))
					{
						Utility::removeFromContainer(p->second->players, static_cast<int>(params[1]));
					}
					else
					{
						Utility::addToContainer(p->second->players, static_cast<int>(params[1]));
					}
				}
			}
			return 1;
		}
		case STREAMER_TYPE_CP:
		{
			for (boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
			{
				boost::unordered_set<int>::iterator e = exceptions.find(c->first);
				if (e == exceptions.end())
				{
					if (!static_cast<int>(params[3]))
					{
						Utility::removeFromContainer(c->second->players, static_cast<int>(params[1]));
					}
					else
					{
						Utility::addToContainer(c->second->players, static_cast<int>(params[1]));
					}
				}
			}
			return 1;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
			{
				boost::unordered_set<int>::iterator e = exceptions.find(r->first);
				if (e == exceptions.end())
				{
					if (!static_cast<int>(params[3]))
					{
						Utility::removeFromContainer(r->second->players, static_cast<int>(params[1]));
					}
					else
					{
						Utility::addToContainer(r->second->players, static_cast<int>(params[1]));
					}
				}
			}
			return 1;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			for (boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin(); m != core->getData()->mapIcons.end(); ++m)
			{
				boost::unordered_set<int>::iterator e = exceptions.find(m->first);
				if (e == exceptions.end())
				{
					if (!static_cast<int>(params[3]))
					{
						Utility::removeFromContainer(m->second->players, static_cast<int>(params[1]));
					}
					else
					{
						Utility::addToContainer(m->second->players, static_cast<int>(params[1]));
					}
				}
			}
			return 1;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			for (boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.begin(); t != core->getData()->textLabels.end(); ++t)
			{
				boost::unordered_set<int>::iterator e = exceptions.find(t->first);
				if (e == exceptions.end())
				{
					if (!static_cast<int>(params[3]))
					{
						Utility::removeFromContainer(t->second->players, static_cast<int>(params[1]));
					}
					else
					{
						Utility::addToContainer(t->second->players, static_cast<int>(params[1]));
					}
				}
			}
			return 1;
		}
		case STREAMER_TYPE_AREA:
		{
			for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				boost::unordered_set<int>::iterator e = exceptions.find(a->first);
				if (e == exceptions.end())
				{
					if (!static_cast<int>(params[3]))
					{
						Utility::removeFromContainer(a->second->players, static_cast<int>(params[1]));
					}
					else
					{
						Utility::addToContainer(a->second->players, static_cast<int>(params[1]));
					}
				}
			}
			return 1;
		}
		case STREAMER_TYPE_ACTOR:
		{
			for (boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.begin(); a != core->getData()->actors.end(); ++a)
			{
				boost::unordered_set<int>::iterator e = exceptions.find(a->first);
				if (e == exceptions.end())
				{
					if (!static_cast<int>(params[3]))
					{
						Utility::removeFromContainer(a->second->players, static_cast<int>(params[1]));
					}
					else
					{
						Utility::addToContainer(a->second->players, static_cast<int>(params[1]));
					}
				}
			}
			return 1;
		}
		default:
		{
			Utility::logError("Streamer_ToggleAllItems: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetItemInternalID(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_GetItemInternalID");
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.find(static_cast<int>(params[3]));
			if (i != core->getData()->internalPickups.end())
			{
				return static_cast<cell>(i->second);
			}
			return 0;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.find(static_cast<int>(params[3]));
			if (i != core->getData()->internalActors.end())
			{
				return static_cast<cell>(i->second);
			}
			return 0;
		}
	}
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(static_cast<int>(params[3]));
				if (i != p->second.internalObjects.end())
				{
					return static_cast<cell>(i->second);
				}
				return 0;
			}
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return 0;
			}
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return 0;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(static_cast<int>(params[3]));
				if (i != p->second.internalMapIcons.end())
				{
					return static_cast<cell>(i->second);
				}
				return 0;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(static_cast<int>(params[3]));
				if (i != p->second.internalTextLabels.end())
				{
					return static_cast<cell>(i->second);
				}
			}
			case STREAMER_TYPE_AREA:
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[3]));
				if (i != p->second.internalAreas.end())
				{
					return *i;
				}
				return 0;
			}
			default:
			{
				Utility::logError("Streamer_GetItemInternalID: Invalid type specified");
				return 0;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetItemStreamerID(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_GetItemStreamerID");
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			for (boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.begin(); i != core->getData()->internalPickups.end(); ++i)
			{
				if (i->second == static_cast<int>(params[3]))
				{
					return i->first;
				}
			}
			return 0;
		}
		case STREAMER_TYPE_ACTOR:
		{
			for (boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.begin(); i != core->getData()->internalActors.end(); ++i)
			{
				if (i->second == static_cast<int>(params[3]))
				{
					return i->first;
				}
			}
			return 0;
		}
	}
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
				{
					if (i->second == static_cast<int>(params[3]))
					{
						return i->first;
					}
				}
				return 0;
			}
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return 0;
			}
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return 0;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				for (boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.begin(); i != p->second.internalMapIcons.end(); ++i)
				{
					if (i->second == static_cast<int>(params[3]))
					{
						return i->first;
					}
				}
				return 0;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				for (boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.begin(); i != p->second.internalTextLabels.end(); ++i)
				{
					if (i->second == static_cast<int>(params[3]))
					{
						return i->first;
					}
				}
				return 0;
			}
			case STREAMER_TYPE_AREA:
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[3]));
				if (i != p->second.internalAreas.end())
				{
					return *i;
				}
				return 0;
			}
			default:
			{
				Utility::logError("Streamer_GetItemStreamerID: Invalid type specified");
				return 0;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsItemVisible(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_IsItemVisible");
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.find(static_cast<int>(params[3]));
			if (i != core->getData()->internalPickups.end())
			{
				return 1;
			}
			return 0;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.find(static_cast<int>(params[3]));
			if (i != core->getData()->internalActors.end())
			{
				return 1;
			}
			return 0;
		}
	}
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(static_cast<int>(params[3]));
				if (i != p->second.internalObjects.end())
				{
					return 1;
				}
				return 0;
			}
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return 0;
			}
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return 0;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(static_cast<int>(params[3]));
				if (i != p->second.internalMapIcons.end())
				{
					return 1;
				}
				return 0;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(static_cast<int>(params[3]));
				if (i != p->second.internalTextLabels.end())
				{
					return 1;
				}
			}
			case STREAMER_TYPE_AREA:
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[3]));
				if (i != p->second.internalAreas.end())
				{
					return 1;
				}
				return 0;
			}
			default:
			{
				Utility::logError("Streamer_IsItemVisible: Invalid type specified");
				return 0;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_DestroyAllVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_DestroyAllVisibleItems");
	bool serverWide = static_cast<int>(params[3]) != 0;
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.begin();
			while (i != core->getData()->internalPickups.end())
			{
				boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(i->first);
				if (serverWide || (p != core->getData()->pickups.end() && p->second->amx == amx))
				{
					sampgdk::DestroyPickup(i->second);
					i = core->getData()->internalPickups.erase(i);
				}
				else
				{
					++i;
				}
			}
			return 1;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.begin();
			while (i != core->getData()->internalActors.end())
			{
				boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(i->first);
				if (serverWide || (a != core->getData()->actors.end() && a->second->amx == amx))
				{
					sampgdk::DestroyActor(i->second);
					i = core->getData()->internalActors.erase(i);
				}
				else
				{
					++i;
				}
			}
			return 1;
		}
	}
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin();
				while (i != p->second.internalObjects.end())
				{
					boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(i->first);
					if (serverWide || (o != core->getData()->objects.end() && o->second->amx == amx))
					{
						sampgdk::DestroyPlayerObject(p->first, i->second);
						i = p->second.internalObjects.erase(i);
					}
					else
					{
						++i;
					}
				}
				return 1;
			}
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint)
				{
					boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(p->second.visibleCheckpoint);
					if (serverWide || (c != core->getData()->checkpoints.end() && c->second->amx == amx))
					{
						sampgdk::DisablePlayerCheckpoint(p->first);
						p->second.activeCheckpoint = 0;
						p->second.visibleCheckpoint = 0;
						return 1;
					}
				}
				return 0;
			}
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint)
				{
					boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(p->second.visibleRaceCheckpoint);
					if (serverWide || (r != core->getData()->raceCheckpoints.end() && r->second->amx == amx))
					{
						sampgdk::DisablePlayerRaceCheckpoint(p->first);
						p->second.activeRaceCheckpoint = 0;
						p->second.visibleRaceCheckpoint = 0;
						return 1;
					}
				}
				return 0;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.begin();
				while (i != p->second.internalMapIcons.end())
				{
					boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(i->first);
					if (serverWide || (m != core->getData()->mapIcons.end() && m->second->amx == amx))
					{
						sampgdk::RemovePlayerMapIcon(p->first, i->second);
						i = p->second.internalMapIcons.erase(i);
					}
					else
					{
						++i;
					}
				}
				return 1;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.begin();
				while (i != p->second.internalTextLabels.end())
				{
					boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(i->first);
					if (serverWide || (t != core->getData()->textLabels.end() && t->second->amx == amx))
					{
						sampgdk::DeletePlayer3DTextLabel(p->first, i->second);
						i = p->second.internalTextLabels.erase(i);
					}
					else
					{
						++i;
					}
				}
				return 1;
			}
			case STREAMER_TYPE_AREA:
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.begin();
				while (i != p->second.internalAreas.end())
				{
					boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(*i);
					if (serverWide || (a != core->getData()->areas.end() && a->second->amx == amx))
					{
						i = p->second.internalAreas.erase(i);
					}
					else
					{
						++i;
					}
				}
				return 1;
			}
			default:
			{
				Utility::logError("Streamer_DestroyAllVisibleItems: Invalid type specified");
				return 0;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_CountVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_CountVisibleItems");
	bool serverWide = static_cast<int>(params[3]) != 0;
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			return static_cast<cell>(core->getData()->internalPickups.size());
		}
		case STREAMER_TYPE_ACTOR:
		{
			return static_cast<cell>(core->getData()->internalActors.size());
		}
	}
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				if (serverWide)
				{
					return static_cast<cell>(p->second.internalObjects.size());
				}
				else
				{
					int count = 0;
					for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
					{
						boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(i->first);
						if (o != core->getData()->objects.end() && o->second->amx == amx)
						{
							++count;
						}
					}
					return static_cast<cell>(count);
				}
			}
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint)
				{
					boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(p->second.visibleCheckpoint);
					if (serverWide || (c != core->getData()->checkpoints.end() && c->second->amx == amx))
					{
						return 1;
					}
					return 0;
				}
			}
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint)
				{
					boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(p->second.visibleRaceCheckpoint);
					if (serverWide || (r != core->getData()->raceCheckpoints.end() && r->second->amx == amx))
					{
						return 1;
					}
				}
				return 0;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				if (serverWide)
				{
					return static_cast<cell>(p->second.internalMapIcons.size());
				}
				else
				{
					int count = 0;
					for (boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.begin(); i != p->second.internalMapIcons.end(); ++i)
					{
						boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(i->first);
						if (m != core->getData()->mapIcons.end() && m->second->amx == amx)
						{
							++count;
						}
					}
					return static_cast<cell>(count);
				}
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				if (serverWide)
				{
					return static_cast<cell>(p->second.internalTextLabels.size());
				}
				else
				{
					int count = 0;
					for (boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.begin(); i != p->second.internalTextLabels.end(); ++i)
					{
						boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(i->first);
						if (t != core->getData()->textLabels.end() && t->second->amx == amx)
						{
							++count;
						}
					}
					return static_cast<cell>(count);
				}
			}
			case STREAMER_TYPE_AREA:
			{
				if (serverWide)
				{
					return static_cast<cell>(p->second.internalAreas.size());
				}
				else
				{
					int count = 0;
					for (boost::unordered_set<int>::iterator i = p->second.internalAreas.begin(); i != p->second.internalAreas.end(); ++i)
					{
						boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(*i);
						if (a != core->getData()->areas.end() && a->second->amx == amx)
						{
							++count;
						}
					}
					return static_cast<cell>(count);
				}
			}
			default:
			{
				Utility::logError("Streamer_CountVisibleItems: Invalid type specified");
				return 0;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_DestroyAllItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_DestroyAllItems");
	bool serverWide = static_cast<int>(params[2]) != 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.begin();
			while (o != core->getData()->objects.end())
			{
				if (serverWide || o->second->amx == amx)
				{
					o = Utility::destroyObject(o);
				}
				else
				{
					++o;
				}
			}
			return 1;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.begin();
			while (p != core->getData()->pickups.end())
			{
				if (serverWide || p->second->amx == amx)
				{
					p = Utility::destroyPickup(p);
				}
				else
				{
					++p;
				}
			}
			return 1;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin();
			while (c != core->getData()->checkpoints.end())
			{
				if (serverWide || c->second->amx == amx)
				{
					c = Utility::destroyCheckpoint(c);
				}
				else
				{
					++c;
				}
			}
			return 1;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin();
			while (r != core->getData()->raceCheckpoints.end())
			{
				if (serverWide || r->second->amx == amx)
				{
					r = Utility::destroyRaceCheckpoint(r);
				}
				else
				{
					++r;
				}
			}
			return 1;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin();
			while (m != core->getData()->mapIcons.end())
			{
				if (serverWide || m->second->amx == amx)
				{
					m = Utility::destroyMapIcon(m);
				}
				else
				{
					++m;
				}
			}
			return 1;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.begin();
			while (t != core->getData()->textLabels.end())
			{
				if (serverWide || t->second->amx == amx)
				{
					t = Utility::destroyTextLabel(t);
				}
				else
				{
					++t;
				}
			}
			return 1;
		}
		case STREAMER_TYPE_AREA:
		{
			Utility::executeFinalAreaCallbacksForAllAreas(amx, serverWide);
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin();
			while (a != core->getData()->areas.end())
			{
				if (serverWide || a->second->amx == amx)
				{
					a = Utility::destroyArea(a);
				}
				else
				{
					++a;
				}
			}
			return 1;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.begin();
			while (a != core->getData()->actors.end())
			{
				if (serverWide || a->second->amx == amx)
				{
					a = Utility::destroyActor(a);
				}
				else
				{
					++a;
				}
			}
			return 1;
		}
		default:
		{
			Utility::logError("Streamer_DestroyAllItems: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_CountItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_CountItems");
	bool serverWide = static_cast<int>(params[2]) != 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			if (serverWide)
			{
				return static_cast<cell>(core->getData()->objects.size());
			}
			else
			{
				int count = 0;
				for (boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.begin(); o != core->getData()->objects.end(); ++o)
				{
					if (o->second->amx == amx)
					{
						++count;
					}
				}
				return static_cast<cell>(count);
			}
		}
		case STREAMER_TYPE_PICKUP:
		{
			if (serverWide)
			{
				return static_cast<cell>(core->getData()->pickups.size());
			}
			else
			{
				int count = 0;
				for (boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.begin(); p != core->getData()->pickups.end(); ++p)
				{
					if (p->second->amx == amx)
					{
						++count;
					}
				}
				return static_cast<cell>(count);
			}
		}
		case STREAMER_TYPE_CP:
		{
			if (serverWide)
			{
				return static_cast<cell>(core->getData()->checkpoints.size());
			}
			else
			{
				int count = 0;
				for (boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
				{
					if (c->second->amx == amx)
					{
						++count;
					}
				}
				return static_cast<cell>(count);
			}
		}
		case STREAMER_TYPE_RACE_CP:
		{
			if (serverWide)
			{
				return static_cast<cell>(core->getData()->raceCheckpoints.size());
			}
			else
			{
				int count = 0;
				for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
				{
					if (r->second->amx == amx)
					{
						++count;
					}
				}
				return static_cast<cell>(count);
			}
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			if (serverWide)
			{
				return static_cast<cell>(core->getData()->mapIcons.size());
			}
			else
			{
				int count = 0;
				for (boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin(); m != core->getData()->mapIcons.end(); ++m)
				{
					if (m->second->amx == amx)
					{
						++count;
					}
				}
				return static_cast<cell>(count);
			}
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			if (serverWide)
			{
				return static_cast<cell>(core->getData()->textLabels.size());
			}
			else
			{
				int count = 0;
				for (boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.begin(); t != core->getData()->textLabels.end(); ++t)
				{
					if (t->second->amx == amx)
					{
						++count;
					}
				}
				return static_cast<cell>(count);
			}
		}
		case STREAMER_TYPE_AREA:
		{
			if (serverWide)
			{
				return static_cast<cell>(core->getData()->areas.size());
			}
			else
			{
				int count = 0;
				for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
				{
					if (a->second->amx == amx)
					{
						++count;
					}
				}
				return static_cast<cell>(count);
			}
		}
		case STREAMER_TYPE_ACTOR:
		{
			if (serverWide)
			{
				return static_cast<cell>(core->getData()->actors.size());
			}
			else
			{
				int count = 0;
				for (boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.begin(); a != core->getData()->actors.end(); ++a)
				{
					if (a->second->amx == amx)
					{
						++count;
					}
				}
				return static_cast<cell>(count);
			}
		}
		default:
		{
			Utility::logError("Streamer_CountItems: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetNearbyItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "Streamer_GetNearbyItems");
	Eigen::Vector2f position2D = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	Eigen::Vector3f position3D = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	float range = amx_ctof(params[7]) * amx_ctof(params[7]);
	std::multimap<float, int> orderedItems;
	std::vector<SharedCell> pointCells;
	core->getGrid()->findMinimalCellsForPoint(position2D, pointCells);
	switch (static_cast<int>(params[4]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedObject>::const_iterator o = (*p)->objects.begin(); o != (*p)->objects.end(); ++o)
				{
					float distance = 0.0f;
					if (o->second->attach)
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(position3D, o->second->attach->position));
					}
					else
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(position3D, o->second->position));
					}
					if (distance < range)
					{
						orderedItems.insert(std::pair<float, int>(distance, o->first));
					}
				}
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedPickup>::const_iterator q = (*p)->pickups.begin(); q != (*p)->pickups.end(); ++q)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(position3D, q->second->position));
					if (distance < range)
					{
						orderedItems.insert(std::pair<float, int>(distance, q->first));
					}
				}
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedCheckpoint>::const_iterator c = (*p)->checkpoints.begin(); c != (*p)->checkpoints.end(); ++c)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(position3D, c->second->position));
					if (distance < range)
					{
						orderedItems.insert(std::pair<float, int>(distance, c->first));
					}
				}
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::const_iterator r = (*p)->raceCheckpoints.begin(); r != (*p)->raceCheckpoints.end(); ++r)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(position3D, r->second->position));
					if (distance < range)
					{
						orderedItems.insert(std::pair<float, int>(distance, r->first));
					}
				}
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedMapIcon>::const_iterator m = (*p)->mapIcons.begin(); m != (*p)->mapIcons.end(); ++m)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(position3D, m->second->position));
					if (distance < range)
					{
						orderedItems.insert(std::pair<float, int>(distance, m->first));
					}
				}
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedTextLabel>::const_iterator t = (*p)->textLabels.begin(); t != (*p)->textLabels.end(); ++t)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(position3D, t->second->position));
					if (distance < range)
					{
						orderedItems.insert(std::pair<float, int>(distance, t->first));
					}
				}
			}
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = (*p)->areas.begin(); a != (*p)->areas.end(); ++a)
				{
					float distance = 0.0f;
					switch (a->second->type)
					{
						case STREAMER_AREA_TYPE_CIRCLE:
						case STREAMER_AREA_TYPE_CYLINDER:
						{
							if (a->second->attach)
							{
								distance = static_cast<float>(boost::geometry::distance(position2D, Eigen::Vector2f(a->second->attach->position[0], a->second->attach->position[1])));
							}
							else
							{
								distance = static_cast<float>(boost::geometry::distance(position2D, boost::get<Eigen::Vector2f>(a->second->position)));
							}
							break;
						}
						case STREAMER_AREA_TYPE_SPHERE:
						{
							if (a->second->attach)
							{
								distance = static_cast<float>(boost::geometry::comparable_distance(position3D, a->second->attach->position));
							}
							else
							{
								distance = static_cast<float>(boost::geometry::comparable_distance(position3D, boost::get<Eigen::Vector3f>(a->second->position)));
							}
							break;
						}
						case STREAMER_AREA_TYPE_RECTANGLE:
						{
							Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Box2D>(a->second->position));
							distance = static_cast<float>(boost::geometry::comparable_distance(position2D, centroid));
							break;
						}
						case STREAMER_AREA_TYPE_CUBOID:
						{
							Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3D>(a->second->position));
							distance = static_cast<float>(boost::geometry::comparable_distance(position3D, centroid));
							break;
						}
						case STREAMER_AREA_TYPE_POLYGON:
						{
							Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2D>(a->second->position));
							distance = static_cast<float>(boost::geometry::comparable_distance(position2D, centroid));
							break;
						}
					}
					if (distance < range)
					{
						orderedItems.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedActor>::const_iterator a = (*p)->actors.begin(); a != (*p)->actors.end(); ++a)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(position3D, a->second->position));
					if (distance < range)
					{
						orderedItems.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_GetNearbyItems: Invalid type specified");
			return 0;
		}
	}
	std::vector<int> finalItems;
	for (std::multimap<float, int>::iterator i = orderedItems.begin(); i != orderedItems.end(); ++i)
	{
		finalItems.push_back(i->second);
	}
	Utility::convertContainerToArray(amx, params[5], params[6], finalItems);
	return static_cast<cell>(finalItems.size());
}

cell AMX_NATIVE_CALL Natives::Streamer_GetAllVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_GetAllVisibleItems");
	std::multimap<float, int> orderedItems;
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
				{
					boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(i->first);
					if (o != core->getData()->objects.end())
					{
						float distance = 0.0f;
						if (o->second->attach)
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, o->second->attach->position));
						}
						else
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, o->second->position));
						}
						orderedItems.insert(std::pair<float, int>(distance, o->first));
					}
				}
				break;
			}
			case STREAMER_TYPE_PICKUP:
			{
				for (boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.begin(); i != core->getData()->internalPickups.end(); ++i)
				{
					boost::unordered_map<int, Item::SharedPickup>::iterator q = core->getData()->pickups.find(i->first);
					if (q != core->getData()->pickups.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, q->second->position));
						orderedItems.insert(std::pair<float, int>(distance, q->first));
					}
				}
				break;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				for (boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.begin(); i != p->second.internalMapIcons.end(); ++i)
				{
					boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(i->first);
					if (m != core->getData()->mapIcons.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, m->second->position));
						orderedItems.insert(std::pair<float, int>(distance, m->first));
					}
				}
				break;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				for (boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.begin(); i != p->second.internalTextLabels.end(); ++i)
				{
					boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(i->first);
					if (t != core->getData()->textLabels.end())
					{
						float distance = 0.0f;
						if (t->second->attach)
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, t->second->attach->position));
						}
						else
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, t->second->position));
						}
						orderedItems.insert(std::pair<float, int>(distance, t->first));
					}
				}
				break;
			}
			case STREAMER_TYPE_ACTOR:
			{
				for (boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.begin(); i != core->getData()->internalActors.end(); ++i)
				{
					boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(i->first);
					if (a != core->getData()->actors.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, a->second->position));
						orderedItems.insert(std::pair<float, int>(distance, a->first));
					}
				}
				break;
			}
		}
	}
	std::vector<int> finalItems;
	for (std::multimap<float, int>::iterator i = orderedItems.begin(); i != orderedItems.end(); ++i)
	{
		finalItems.push_back(i->second);
	}
	Utility::convertContainerToArray(amx, params[3], params[4], finalItems);
	return static_cast<cell>(finalItems.size());
}

cell AMX_NATIVE_CALL Natives::Streamer_GetItemOffset(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "Streamer_GetItemOffset");
	Eigen::Vector3f positionOffset = Eigen::Vector3f::Zero();
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				positionOffset = o->second->positionOffset;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				positionOffset = p->second->positionOffset;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				positionOffset = c->second->positionOffset;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				positionOffset = r->second->positionOffset;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				positionOffset = m->second->positionOffset;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				positionOffset = t->second->positionOffset;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				positionOffset = a->second->positionOffset;
				break;
			}
			return 0;
		}
		default:
		{
			Utility::logError("Streamer_GetItemPosOffset: Invalid type specified");
			return 0;
		}
	}
	Utility::storeFloatInNative(amx, params[3], positionOffset[0]);
	Utility::storeFloatInNative(amx, params[4], positionOffset[1]);
	Utility::storeFloatInNative(amx, params[5], positionOffset[2]);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetItemOffset(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "Streamer_SetItemOffset");
	Eigen::Vector3f positionOffset = Eigen::Vector3f::Zero();
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				o->second->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				p->second->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				c->second->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				r->second->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				m->second->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				t->second->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				a->second->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
				return 1;
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_SetItemPosOffset: Invalid type specified");
			return 0;
		}
	}
	return 0;
}
