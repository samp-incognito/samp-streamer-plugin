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

#include "../precompiled.h"

#include "../natives.h"
#include "../core.h"
#include "../utility.h"

cell AMX_NATIVE_CALL Natives::Streamer_GetDistanceToItem(AMX *amx, cell *params)
{
	CHECK_PARAMS(7);
	int dimensions = static_cast<int>(params[7]);
	Eigen::Vector3f position = Eigen::Vector3f::Zero();
	bool success = false;
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
				boost::variant<Polygon2d, Box2d, Box3d, Eigen::Vector2f, Eigen::Vector3f> areaPosition;
				if (a->second->attach)
				{
					areaPosition = a->second->attach->position;
				}
				else
				{
					areaPosition = a->second->position;
				}
				switch (a->second->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					case STREAMER_AREA_TYPE_CYLINDER:
					{
						float distance = 0.0f;
						distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), boost::get<Eigen::Vector2f>(areaPosition)));
						Utility::storeFloatInNative(amx, params[6], distance);
						return 1;
					}
					case STREAMER_AREA_TYPE_SPHERE:
					{
						position = boost::get<Eigen::Vector3f>(areaPosition);
						success = true;
						break;
					}
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Box2d>(areaPosition));
						float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
						Utility::storeFloatInNative(amx, params[6], distance);
						return 1;
					}
					case STREAMER_AREA_TYPE_CUBOID:
					{
						position = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3d>(areaPosition));
						success = true;
						break;
					}
					case STREAMER_AREA_TYPE_POLYGON:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2d>(areaPosition));
						float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
						Utility::storeFloatInNative(amx, params[6], distance);
						return 1;
					}
				}
			}
			if (success)
			{
				break;
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
			Utility::logError("Streamer_GetDistanceToItem: Invalid type specified.");
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
			Utility::logError("Streamer_GetDistanceToItem: Invalid number of dimensions specified (outside range of 2-3).");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleItem(AMX *amx, cell *params)
{
	CHECK_PARAMS(4);
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
			Utility::logError("Streamer_ToggleItem: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleItem(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
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
			Utility::logError("Streamer_IsToggleItem: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleAllItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(5);
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
			Utility::logError("Streamer_ToggleAllItems: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetItemInternalID(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			int pickupId = static_cast<int>(params[3]);
			Item::SharedPickup p = core->getData()->pickups[pickupId];
			for (boost::unordered_set<int>::const_iterator w = p->worlds.begin(); w != p->worlds.end(); ++w)
			{
				boost::unordered_map<std::pair<int, int>, int>::iterator i = core->getData()->internalPickups.find(std::make_pair(pickupId, *w));
				if (i != core->getData()->internalPickups.end())
				{
					return static_cast<cell>(i->second);
				}
			}
			return INVALID_PICKUP_ID;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.find(static_cast<int>(params[3]));
			if (i != core->getData()->internalActors.end())
			{
				return static_cast<cell>(i->second);
			}
			return INVALID_ACTOR_ID;
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
				return INVALID_OBJECT_ID;
			}
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return -1;
			}
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return -1;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(static_cast<int>(params[3]));
				if (i != p->second.internalMapIcons.end())
				{
					return static_cast<cell>(i->second);
				}
				return -1;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(static_cast<int>(params[3]));
				if (i != p->second.internalTextLabels.end())
				{
					return static_cast<cell>(i->second);
				}
				return INVALID_3DTEXT_ID;
			}
			case STREAMER_TYPE_AREA:
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[3]));
				if (i != p->second.internalAreas.end())
				{
					return *i;
				}
				return INVALID_STREAMER_ID;
			}
			default:
			{
				Utility::logError("Streamer_GetItemInternalID: Invalid type specified.");
				return -1;
			}
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetItemStreamerID(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			int pickupId = static_cast<int>(params[3]);
			Item::SharedPickup p = core->getData()->pickups[pickupId];
			for (boost::unordered_set<int>::const_iterator w = p->worlds.begin(); w != p->worlds.end(); ++w)
			{
				for (boost::unordered_map<std::pair<int, int>, int>::iterator i = core->getData()->internalPickups.begin(); i != core->getData()->internalPickups.end(); ++i)
				{
					if (i->second == pickupId)
					{
						return i->first.first;
					}
				}
			}
			return INVALID_STREAMER_ID;
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
			return INVALID_STREAMER_ID;
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
				return INVALID_STREAMER_ID;
			}
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return INVALID_STREAMER_ID;
			}
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
				return INVALID_STREAMER_ID;
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
				return INVALID_STREAMER_ID;
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
				return INVALID_STREAMER_ID;
			}
			case STREAMER_TYPE_AREA:
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[3]));
				if (i != p->second.internalAreas.end())
				{
					return *i;
				}
				return INVALID_STREAMER_ID;
			}
			default:
			{
				Utility::logError("Streamer_GetItemStreamerID: Invalid type specified.");
				return INVALID_STREAMER_ID;
			}
		}
	}
	return INVALID_STREAMER_ID;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsItemVisible(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			int pickupId = static_cast<int>(params[3]);
			Item::SharedPickup p = core->getData()->pickups[pickupId];
			for (boost::unordered_set<int>::const_iterator w = p->worlds.begin(); w != p->worlds.end(); ++w)
			{
				boost::unordered_map<std::pair<int, int>, int>::iterator i = core->getData()->internalPickups.find(std::make_pair(pickupId, *w));
				if (i != core->getData()->internalPickups.end())
				{
					return 1;
				}
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
				Utility::logError("Streamer_IsItemVisible: Invalid type specified.");
				return 0;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_DestroyAllVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	bool serverWide = static_cast<int>(params[3]) != 0;
	switch (static_cast<int>(params[2]))
	{
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<std::pair<int, int>, int>::iterator i = core->getData()->internalPickups.begin();
			while (i != core->getData()->internalPickups.end())
			{
				boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(i->first.first);
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
				Utility::logError("Streamer_DestroyAllVisibleItems: Invalid type specified.");
				return 0;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_CountVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
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
				Utility::logError("Streamer_CountVisibleItems: Invalid type specified.");
				return 0;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_DestroyAllItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2);
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
			Utility::logError("Streamer_DestroyAllItems: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_CountItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2);
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
			Utility::logError("Streamer_CountItems: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetNearbyItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(8);
	Eigen::Vector2f position2d = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	Eigen::Vector3f position3d = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	float range = amx_ctof(params[7]) * amx_ctof(params[7]);
	int worldId = static_cast<int>(params[8]);
	std::multimap<float, int> orderedItems;
	std::vector<SharedCell> pointCells;
	core->getGrid()->findMinimalCellsForPoint(position2d, pointCells, range);
	switch (static_cast<int>(params[4]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
			{
				for (boost::unordered_map<int, Item::SharedObject>::const_iterator o = (*p)->objects.begin(); o != (*p)->objects.end(); ++o)
				{
					if (worldId == -1 || o->second->worlds.find(worldId) != o->second->worlds.end())
					{
						float distance = 0.0f;
						if (o->second->attach)
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(position3d, o->second->attach->position));
						}
						else
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(position3d, o->second->position));
						}
						if (distance < range)
						{
							orderedItems.insert(std::pair<float, int>(distance, o->first));
						}
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
					if (worldId == -1 || q->second->worlds.find(worldId) != q->second->worlds.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(position3d, q->second->position));
						if (distance < range)
						{
							orderedItems.insert(std::pair<float, int>(distance, q->first));
						}
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
					if (worldId == -1 || c->second->worlds.find(worldId) != c->second->worlds.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(position3d, c->second->position));
						if (distance < range)
						{
							orderedItems.insert(std::pair<float, int>(distance, c->first));
						}
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
					if (worldId == -1 || r->second->worlds.find(worldId) != r->second->worlds.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(position3d, r->second->position));
						if (distance < range)
						{
							orderedItems.insert(std::pair<float, int>(distance, r->first));
						}
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
					if (worldId == -1 || m->second->worlds.find(worldId) != m->second->worlds.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(position3d, m->second->position));
						if (distance < range)
						{
							orderedItems.insert(std::pair<float, int>(distance, m->first));
						}
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
					if (worldId == -1 || t->second->worlds.find(worldId) != t->second->worlds.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(position3d, t->second->position));
						if (distance < range)
						{
							orderedItems.insert(std::pair<float, int>(distance, t->first));
						}
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
					if (worldId == -1 || a->second->worlds.find(worldId) != a->second->worlds.end())
					{
						boost::variant<Polygon2d, Box2d, Box3d, Eigen::Vector2f, Eigen::Vector3f> position;
						if (a->second->attach)
						{
							position = a->second->position;
						}
						else
						{
							position = a->second->position;
						}
						float distance = 0.0f;
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_CYLINDER:
							{
								distance = static_cast<float>(boost::geometry::distance(position2d, boost::get<Eigen::Vector2f>(position)));
								break;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								distance = static_cast<float>(boost::geometry::comparable_distance(position3d, boost::get<Eigen::Vector3f>(position)));
								break;
							}
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Box2d>(position));
								distance = static_cast<float>(boost::geometry::comparable_distance(position2d, centroid));
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3d>(position));
								distance = static_cast<float>(boost::geometry::comparable_distance(position3d, centroid));
								break;
							}
							case STREAMER_AREA_TYPE_POLYGON:
							{
								Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2d>(position));
								distance = static_cast<float>(boost::geometry::comparable_distance(position2d, centroid));
								break;
							}
						}
						if (distance < range)
						{
							orderedItems.insert(std::pair<float, int>(distance, a->first));
						}
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
					if (worldId == -1 || a->second->worlds.find(worldId) != a->second->worlds.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(position3d, a->second->position));
						if (distance < range)
						{
							orderedItems.insert(std::pair<float, int>(distance, a->first));
						}
					}
				}
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_GetNearbyItems: Invalid type specified.");
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
	CHECK_PARAMS(4);
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
				for (boost::unordered_map<std::pair<int, int>, int>::iterator i = core->getData()->internalPickups.begin(); i != core->getData()->internalPickups.end(); ++i)
				{
					boost::unordered_map<int, Item::SharedPickup>::iterator q = core->getData()->pickups.find(i->first.first);
					if (q != core->getData()->pickups.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, q->second->position));
						orderedItems.insert(std::pair<float, int>(distance, q->first));
					}
				}
				break;
			}
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint != INVALID_STREAMER_ID)
				{
					boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(p->second.visibleCheckpoint);
					if (c != core->getData()->checkpoints.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, c->second->position));
						orderedItems.insert(std::pair<float, int>(distance, c->first));
					}
				}
				break;
			}
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint != INVALID_STREAMER_ID)
				{
					boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator c = core->getData()->raceCheckpoints.find(p->second.visibleRaceCheckpoint);
					if (c != core->getData()->raceCheckpoints.end())
					{
						float distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, c->second->position));
						orderedItems.insert(std::pair<float, int>(distance, c->first));
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

cell AMX_NATIVE_CALL Natives::Streamer_GetItemPos(AMX *amx, cell *params)
{
	CHECK_PARAMS(5);
	Eigen::Vector3f position = Eigen::Vector3f::Zero();
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
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
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				position = p->second->position;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				position = c->second->position;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				position = r->second->position;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				position = m->second->position;
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
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
			bool success = false;
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				boost::variant<Polygon2d, Box2d, Box3d, Eigen::Vector2f, Eigen::Vector3f> areaPosition;
				if (a->second->attach)
				{
					areaPosition = a->second->attach->position;
				}
				else
				{
					areaPosition = a->second->position;
				}
				switch (a->second->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					{
						position[0] = boost::get<Eigen::Vector2f>(areaPosition)[0];
						position[1] = boost::get<Eigen::Vector2f>(areaPosition)[1];
						position[2] = 0.0f;
						success = true;
						break;
					}
					case STREAMER_AREA_TYPE_CYLINDER:
					{
						position[0] = boost::get<Eigen::Vector2f>(areaPosition)[0];
						position[1] = boost::get<Eigen::Vector2f>(areaPosition)[1];
						if (a->second->height[0] == -std::numeric_limits<float>::infinity() || a->second->height[1] == std::numeric_limits<float>::infinity())
						{
							position[2] = 0.0f;
						}
						else
						{
							position[2] = (a->second->height[0] + a->second->height[1]) / 2.0f;
						}
						success = true;
						break;
					}
					case STREAMER_AREA_TYPE_SPHERE:
					{
						position = boost::get<Eigen::Vector3f>(areaPosition);
						success = true;
						break;
					}
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Box2d>(areaPosition));
						position[0] = centroid[0];
						position[1] = centroid[1];
						position[2] = 0.0f;
						success = true;
						break;
					}
					case STREAMER_AREA_TYPE_CUBOID:
					{
						position = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3d>(areaPosition));
						success = true;
						break;
					}
					case STREAMER_AREA_TYPE_POLYGON:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2d>(areaPosition));
						position[0] = centroid[0];
						position[1] = centroid[1];
						if (a->second->height[0] == -std::numeric_limits<float>::infinity() || a->second->height[1] == std::numeric_limits<float>::infinity())
						{
							position[2] = 0.0f;
						}
						else
						{
							position[2] = (a->second->height[0] + a->second->height[1]) / 2.0f;
						}
						success = true;
						break;
					}
				}
			}
			if (success)
			{
				break;
			}
			return 0;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				position = a->second->position;
				break;
			}
			return 0;
		}
		default:
		{
			Utility::logError("Streamer_GetItemPos: Invalid type specified.");
			return 0;
		}
	}
	Utility::storeFloatInNative(amx, params[3], position[0]);
	Utility::storeFloatInNative(amx, params[4], position[1]);
	Utility::storeFloatInNative(amx, params[5], position[2]);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetItemPos(AMX *amx, cell *params)
{
	CHECK_PARAMS(5);
	Eigen::Vector3f newpos = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				Eigen::Vector3f position = o->second->position;
				o->second->position = newpos;
				for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
					if (i != p->second.internalObjects.end())
					{
						sampgdk::SetPlayerObjectPos(p->first, i->second, o->second->position[0], o->second->position[1], o->second->position[2]);
					}
				}
				if (position[0] != o->second->position[0] || position[1] != o->second->position[1])
				{
					if (o->second->cell)
					{
						core->getGrid()->removeObject(o->second, true);
					}
				}
				if (o->second->move)
				{
					o->second->move->duration = static_cast<int>((static_cast<float>(boost::geometry::distance(o->second->move->position.get<0>(), o->second->position) / o->second->move->speed) * 1000.0f));
					o->second->move->position.get<1>() = o->second->position;
					o->second->move->position.get<2>() = (o->second->move->position.get<0>() - o->second->position) / static_cast<float>(o->second->move->duration);
					if ((o->second->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
					{
						o->second->move->rotation.get<1>() = o->second->rotation;
						o->second->move->rotation.get<2>() = (o->second->move->rotation.get<0>() - o->second->rotation) / static_cast<float>(o->second->move->duration);
					}
					o->second->move->time = boost::chrono::steady_clock::now();
				}
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				Eigen::Vector3f position = p->second->position;
				p->second->position = newpos;
				if (position[0] != p->second->position[0] || position[1] != p->second->position[1])
				{
					if (p->second->cell)
					{
						core->getGrid()->removePickup(p->second, true);
					}
				}
				for (boost::unordered_set<int>::const_iterator w = p->second->worlds.begin(); w != p->second->worlds.end(); ++w)
				{
					boost::unordered_map<std::pair<int, int>, int>::iterator i = core->getData()->internalPickups.find(std::make_pair(p->first, *w));
					if (i != core->getData()->internalPickups.end())
					{
						sampgdk::DestroyPickup(i->second);
						i->second = sampgdk::CreatePickup(p->second->modelId, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], *w);
					}
				}
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				Eigen::Vector3f position = c->second->position;
				c->second->position = newpos;
				if (position[0] != c->second->position[0] || position[1] != c->second->position[1])
				{
					if (c->second->cell)
					{
						core->getGrid()->removeCheckpoint(c->second, true);
					}
				}
				for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					if (p->second.visibleCheckpoint == c->first)
					{
						sampgdk::DisablePlayerCheckpoint(p->first);
						p->second.activeCheckpoint = 0;
						p->second.visibleCheckpoint = 0;
					}
				}
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				Eigen::Vector3f position = r->second->position;
				r->second->position = newpos;
				if (position[0] != r->second->position[0] || position[1] != r->second->position[1])
				{
					if (r->second->cell)
					{
						core->getGrid()->removeRaceCheckpoint(r->second, true);
					}
				}
				for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					if (p->second.visibleRaceCheckpoint == r->first)
					{
						sampgdk::DisablePlayerRaceCheckpoint(p->first);
						p->second.activeRaceCheckpoint = 0;
						p->second.visibleRaceCheckpoint = 0;
					}
				}
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				Eigen::Vector3f position = m->second->position;
				m->second->position = newpos;
				if (position[0] != m->second->position[0] || position[1] != m->second->position[1])
				{
					if (m->second->cell)
					{
						core->getGrid()->removeMapIcon(m->second, true);
					}
				}
				for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
					if (i != p->second.internalMapIcons.end())
					{
						sampgdk::RemovePlayerMapIcon(p->first, i->second);
						sampgdk::SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
					}
				}
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				Eigen::Vector3f position = t->second->position;
				t->second->position = newpos;
				if (position[0] != t->second->position[0] || position[1] != t->second->position[1])
				{
					if (t->second->cell)
					{
						core->getGrid()->removeTextLabel(t->second, true);
					}
				}
				for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
					if (i != p->second.internalTextLabels.end())
					{
						sampgdk::DeletePlayer3DTextLabel(p->first, i->second);
						i->second = sampgdk::CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, t->second->attach ? t->second->attach->player : INVALID_PLAYER_ID, t->second->attach ? t->second->attach->vehicle : INVALID_VEHICLE_ID, t->second->testLOS);
					}
				}
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (a->second->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					{
						a->second->position = Eigen::Vector2f(newpos.head<2>());
						break;
					}
					case STREAMER_AREA_TYPE_SPHERE:
					{
						a->second->position = newpos;
						break;
					}
					default:
					{
						Utility::logError("Streamer_SetItemPos: Invalid area type specified (only circles and spheres are supported).");
						return 0;
					}
				}
				core->getGrid()->removeArea(a->second, true);
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				Eigen::Vector3f position = a->second->position;
				a->second->position = newpos;
				if (position[0] != a->second->position[0] || position[1] != a->second->position[1])
				{
					if (a->second->cell)
					{
						core->getGrid()->removeActor(a->second, true);
					}
				}
				boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.find(a->first);
				if (i != core->getData()->internalActors.end())
				{
					sampgdk::DestroyActor(i->second);
					i->second = sampgdk::CreateActor(a->second->modelId, a->second->position[0], a->second->position[1], a->second->position[2], a->second->rotation);
					sampgdk::SetActorInvulnerable(i->second, a->second->invulnerable);
					sampgdk::SetActorHealth(i->second, a->second->health);
					sampgdk::SetActorVirtualWorld(i->second, a->second->worldId);
					if (a->second->anim)
					{
						sampgdk::ApplyActorAnimation(i->second, a->second->anim->lib.c_str(), a->second->anim->name.c_str(), a->second->anim->delta, a->second->anim->loop, a->second->anim->lockx, a->second->anim->locky, a->second->anim->freeze, a->second->anim->time);
					}
				}
				return 1;
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_SetItemPos: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetItemOffset(AMX *amx, cell *params)
{
	CHECK_PARAMS(5);
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
			Utility::logError("Streamer_GetItemPosOffset: Invalid type specified.");
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
	CHECK_PARAMS(5);
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
			Utility::logError("Streamer_SetItemPosOffset: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}
