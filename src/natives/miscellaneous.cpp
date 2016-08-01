/*
 * Copyright (C) 2016 Incognito
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
				position = o->second->position;
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
						static_cast<cell>(Utility::removeFromContainer(o->second->players, static_cast<int>(params[1])));
					}
					else
					{
						static_cast<cell>(Utility::addToContainer(o->second->players, static_cast<int>(params[1])));
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
						static_cast<cell>(Utility::removeFromContainer(p->second->players, static_cast<int>(params[1])));
					}
					else
					{
						static_cast<cell>(Utility::addToContainer(p->second->players, static_cast<int>(params[1])));
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
						static_cast<cell>(Utility::removeFromContainer(c->second->players, static_cast<int>(params[1])));
					}
					else
					{
						static_cast<cell>(Utility::addToContainer(c->second->players, static_cast<int>(params[1])));
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
						static_cast<cell>(Utility::removeFromContainer(r->second->players, static_cast<int>(params[1])));
					}
					else
					{
						static_cast<cell>(Utility::addToContainer(r->second->players, static_cast<int>(params[1])));
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
						static_cast<cell>(Utility::removeFromContainer(m->second->players, static_cast<int>(params[1])));
					}
					else
					{
						static_cast<cell>(Utility::addToContainer(m->second->players, static_cast<int>(params[1])));
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
						static_cast<cell>(Utility::removeFromContainer(t->second->players, static_cast<int>(params[1])));
					}
					else
					{
						static_cast<cell>(Utility::addToContainer(t->second->players, static_cast<int>(params[1])));
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
						static_cast<cell>(Utility::removeFromContainer(a->second->players, static_cast<int>(params[1])));
					}
					else
					{
						static_cast<cell>(Utility::addToContainer(a->second->players, static_cast<int>(params[1])));
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
	if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.find(static_cast<int>(params[3]));
		if (i != core->getData()->internalPickups.end())
		{
			return static_cast<cell>(i->second);
		}
		return 0;
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
	if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
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
	if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.find(static_cast<int>(params[3]));
		if (i != core->getData()->internalPickups.end())
		{
			return 1;
		}
		return 0;
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
	if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
	{
		boost::unordered_map<int, int>::iterator p = core->getData()->internalPickups.begin();
		while (p != core->getData()->internalPickups.end())
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator q = core->getData()->pickups.find(p->first);
			if (serverWide || (q != core->getData()->pickups.end() && q->second->amx == amx))
			{
				sampgdk::DestroyPickup(p->second);
				p = core->getData()->internalPickups.erase(p);
			}
			else
			{
				++p;
			}
		}
		return 1;
	}
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				boost::unordered_map<int, int>::iterator o = p->second.internalObjects.begin();
				while (o != p->second.internalObjects.end())
				{
					boost::unordered_map<int, Item::SharedObject>::iterator q = core->getData()->objects.find(o->first);
					if (serverWide || (q != core->getData()->objects.end() && q->second->amx == amx))
					{
						sampgdk::DestroyPlayerObject(p->first, o->second);
						o = p->second.internalObjects.erase(o);
					}
					else
					{
						++o;
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
				boost::unordered_map<int, int>::iterator m = p->second.internalMapIcons.begin();
				while (m != p->second.internalMapIcons.end())
				{
					boost::unordered_map<int, Item::SharedMapIcon>::iterator n = core->getData()->mapIcons.find(m->first);
					if (serverWide || (n != core->getData()->mapIcons.end() && n->second->amx == amx))
					{
						sampgdk::RemovePlayerMapIcon(p->first, m->second);
						m = p->second.internalMapIcons.erase(m);
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
				boost::unordered_map<int, int>::iterator t = p->second.internalTextLabels.begin();
				while (t != p->second.internalMapIcons.end())
				{
					boost::unordered_map<int, Item::SharedTextLabel>::iterator u = core->getData()->textLabels.find(t->first);
					if (serverWide || (u != core->getData()->textLabels.end() && u->second->amx == amx))
					{
						sampgdk::DeletePlayer3DTextLabel(p->first, t->second);
						t = p->second.internalTextLabels.erase(t);
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
				boost::unordered_set<int>::iterator a = p->second.internalAreas.begin();
				while (a != p->second.internalAreas.end())
				{
					boost::unordered_map<int, Item::SharedArea>::iterator b = core->getData()->areas.find(*a);
					if (serverWide || (b != core->getData()->areas.end() && b->second->amx == amx))
					{
						a = p->second.internalAreas.erase(a);
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
	if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
	{
		return static_cast<cell>(core->getData()->internalPickups.size());
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
					for (boost::unordered_map<int, int>::iterator o = p->second.internalObjects.begin(); o != p->second.internalObjects.end(); ++o)
					{
						boost::unordered_map<int, Item::SharedObject>::iterator q = core->getData()->objects.find(o->first);
						if (q != core->getData()->objects.end() && q->second->amx == amx)
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
					for (boost::unordered_map<int, int>::iterator m = p->second.internalMapIcons.begin(); m != p->second.internalObjects.end(); ++m)
					{
						boost::unordered_map<int, Item::SharedMapIcon>::iterator n = core->getData()->mapIcons.find(m->first);
						if (n != core->getData()->mapIcons.end() && n->second->amx == amx)
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
					for (boost::unordered_map<int, int>::iterator t = p->second.internalTextLabels.begin(); t != p->second.internalTextLabels.end(); ++t)
					{
						boost::unordered_map<int, Item::SharedTextLabel>::iterator u = core->getData()->textLabels.find(t->first);
						if (u != core->getData()->textLabels.end() && u->second->amx == amx)
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
					for (boost::unordered_set<int>::iterator a = p->second.internalAreas.begin(); a != p->second.internalAreas.end(); ++a)
					{
						boost::unordered_map<int, Item::SharedArea>::iterator b = core->getData()->areas.find(*a);
						if (b != core->getData()->areas.end() && b->second->amx == amx)
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
	Eigen::Vector3f position3d = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	Eigen::Vector2f position2d = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	float range = pow(amx_ctof(params[7]), 2);
	switch (static_cast<int>(params[4]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			std::vector<SharedCell> pointCells;
			core->getGrid()->findMinimalCellsForPoint(position2d, pointCells);
			std::multimap<float, int> orderedObjects;
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedObject>::const_iterator a = (*p)->objects.begin(); a != (*p)->objects.end(); ++a)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(a->second->position, position3d));
					if(distance < range)
					{
						orderedObjects.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			std::vector<int> final;
			for (std::multimap<float, int>::iterator i = orderedObjects.begin(); i != orderedObjects.end(); ++i)
			{
				final.push_back(i->second);
			}
			Utility::convertContainerToArray(amx, params[5], params[6], final);
			return static_cast<cell>(final.size());
		}
		case STREAMER_TYPE_PICKUP:
		{
			std::vector<SharedCell> pointCells;
			core->getGrid()->findMinimalCellsForPoint(position2d, pointCells);
			std::multimap<float, int> orderedPickups;
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedPickup>::const_iterator a = (*p)->pickups.begin(); a != (*p)->pickups.end(); ++a)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(a->second->position, position3d));
					if(distance < range)
					{
						orderedPickups.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			std::vector<int> final;
			for (std::multimap<float, int>::iterator i = orderedPickups.begin(); i != orderedPickups.end(); ++i)
			{
				final.push_back(i->second);
			}
			Utility::convertContainerToArray(amx, params[5], params[6], final);
			return static_cast<cell>(final.size());
		}
		case STREAMER_TYPE_CP:
		{
			std::vector<SharedCell> pointCells;
			core->getGrid()->findMinimalCellsForPoint(position2d, pointCells);
			std::multimap<float, int> orderedCheckpoints;
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedCheckpoint>::const_iterator a = (*p)->checkpoints.begin(); a != (*p)->checkpoints.end(); ++a)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(a->second->position, position3d));
					if(distance < range)
					{
						orderedCheckpoints.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			std::vector<int> final;
			for (std::multimap<float, int>::iterator i = orderedCheckpoints.begin(); i != orderedCheckpoints.end(); ++i)
			{
				final.push_back(i->second);
			}
			Utility::convertContainerToArray(amx, params[5], params[6], final);
			return static_cast<cell>(final.size());
		}
		case STREAMER_TYPE_RACE_CP:
		{
			std::vector<SharedCell> pointCells;
			core->getGrid()->findMinimalCellsForPoint(position2d, pointCells);
			std::multimap<float, int> orderedRaceCheckpoints;
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::const_iterator a = (*p)->raceCheckpoints.begin(); a != (*p)->raceCheckpoints.end(); ++a)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(a->second->position, position3d));
					if(distance < range)
					{
						orderedRaceCheckpoints.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			std::vector<int> final;
			for (std::multimap<float, int>::iterator i = orderedRaceCheckpoints.begin(); i != orderedRaceCheckpoints.end(); ++i)
			{
				final.push_back(i->second);
			}
			Utility::convertContainerToArray(amx, params[5], params[6], final);
			return static_cast<cell>(final.size());
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			std::vector<SharedCell> pointCells;
			core->getGrid()->findMinimalCellsForPoint(position2d, pointCells);
			std::multimap<float, int> orderedMapIcons;
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedMapIcon>::const_iterator a = (*p)->mapIcons.begin(); a != (*p)->mapIcons.end(); ++a)
				{
					float distance = static_cast<float>(boost::geometry::comparable_distance(a->second->position, position3d));
					if(distance < range)
					{
						orderedMapIcons.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			std::vector<int> final;
			for (std::multimap<float, int>::iterator i = orderedMapIcons.begin(); i != orderedMapIcons.end(); ++i)
			{
				final.push_back(i->second);
			}
			Utility::convertContainerToArray(amx, params[5], params[6], final);
			return static_cast<cell>(final.size());
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			std::vector<SharedCell> pointCells;
			core->getGrid()->findMinimalCellsForPoint(position2d, pointCells);
			std::multimap<float, int> orderedTextLabels;
			float distance = 0.0;
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedTextLabel>::const_iterator a = (*p)->textLabels.begin(); a != (*p)->textLabels.end(); ++a)
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(a->second->position, position3d));
					if(distance < range)
					{
						orderedTextLabels.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			std::vector<int> final;
			for (std::multimap<float, int>::iterator i = orderedTextLabels.begin(); i != orderedTextLabels.end(); ++i)
			{
				final.push_back(i->second);
			}
			Utility::convertContainerToArray(amx, params[5], params[6], final);
			return static_cast<cell>(final.size());
		}
		case STREAMER_TYPE_AREA:
		{
			std::vector<SharedCell> pointCells;
			core->getGrid()->findMinimalCellsForPoint(position2d, pointCells);
			std::multimap<float, int> orderedAreas;
			float distance = 0.0;
			Eigen::Vector3f tempPos;
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = (*p)->areas.begin(); a != (*p)->areas.end(); ++a)
				{
					switch (a->second->type)
					{
						case STREAMER_AREA_TYPE_CIRCLE:
						case STREAMER_AREA_TYPE_CYLINDER:
						case STREAMER_AREA_TYPE_SPHERE:
						{
							if (a->second->attach)
							{
								distance = static_cast<float>(boost::geometry::comparable_distance(a->second->attach->position, position3d));
							}
							else
							{
								distance = static_cast<float>(boost::geometry::comparable_distance(boost::get<Eigen::Vector3f>(a->second->position), position3d));
							}
							break;
						}
						case STREAMER_AREA_TYPE_RECTANGLE:
						{
							Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3D>(a->second->position));
							distance = static_cast<float>(boost::geometry::comparable_distance(centroid, position3d));
							break;
						}
						case STREAMER_AREA_TYPE_CUBOID:
						{
							Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3D>(a->second->position));
							distance = static_cast<float>(boost::geometry::comparable_distance(centroid, position3d));
							break;
						}
						case STREAMER_AREA_TYPE_POLYGON:
						{
							Eigen::Vector2f centroidxy = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2D>(a->second->position));
							Eigen::Vector2f positionz = boost::get<Eigen::Vector2f>(a->second->height);
							Eigen::Vector3f centroid = Eigen::Vector3f(centroidxy[0], centroidxy[1], positionz[1] - positionz[0]);
							distance = static_cast<float>(boost::geometry::comparable_distance(centroid, position3d));
							break;
						}
					}
					if(distance < range)
					{
						orderedAreas.insert(std::pair<float, int>(distance, a->first));
					}
				}
			}
			std::vector<int> final;
			for (std::multimap<float, int>::iterator i = orderedAreas.begin(); i != orderedAreas.end(); ++i)
			{
				final.push_back(i->second);
			}
			Utility::convertContainerToArray(amx, params[5], params[6], final);
			return static_cast<cell>(final.size());
		}
		default:
		{
			Utility::logError("Streamer_GetNearbyItems: Invalid type specified");
			return 0;
		}
	}

	return 0;
}
