/*
 * Copyright (C) 2014 Incognito
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

#include "natives.h"

#include "core.h"
#include "main.h"
#include "manipulation.h"
#include "utility.h"

#include <boost/chrono.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <sampgdk/a_objects.h>
#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/plugin.h>

#include <bitset>
#include <limits>
#include <string>

// Settings

cell AMX_NATIVE_CALL Natives::Streamer_GetTickRate(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getStreamer()->getTickRate());
}

cell AMX_NATIVE_CALL Natives::Streamer_SetTickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_SetTickRate");
	if (static_cast<std::size_t>(params[1]) > 0)
	{
		core->getStreamer()->setTickRate(static_cast<std::size_t>(params[1]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetMaxItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetMaxItems");
	return static_cast<cell>(core->getData()->getMaxItems(static_cast<std::size_t>(params[1])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetMaxItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetMaxItems");
	return static_cast<cell>(core->getData()->setMaxItems(static_cast<int>(params[1]), static_cast<int>(params[2])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetVisibleItems");
	return static_cast<cell>(core->getStreamer()->getVisibleItems(static_cast<std::size_t>(params[1])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetVisibleItems");
	return static_cast<cell>(core->getStreamer()->setVisibleItems(static_cast<int>(params[1]), static_cast<int>(params[2])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetCellDistance(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_GetCellDistance");
	float cellDistance = core->getGrid()->getCellDistance();
	Utility::storeFloatInNative(amx, params[2], cellDistance);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetCellDistance(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_SetCellDistance");
	core->getGrid()->setCellDistance(amx_ctof(params[1]) * amx_ctof(params[1]));
	core->getGrid()->rebuildGrid();
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetCellSize(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_GetCellSize");
	float cellSize = core->getGrid()->getCellSize();
	Utility::storeFloatInNative(amx, params[2], cellSize);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetCellSize(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_SetCellSize");
	core->getGrid()->setCellSize(amx_ctof(params[1]));
	core->getGrid()->rebuildGrid();
	return 1;
}

// Updates

cell AMX_NATIVE_CALL Natives::Streamer_ProcessActiveItems(AMX *amx, cell *params)
{
	core->getStreamer()->processActiveItems();
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleIdleUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_ToggleIdleUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.updateWhenIdle = static_cast<int>(params[2]) != 0;
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleIdleUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_IsToggleIdleUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return static_cast<cell>(p->second.updateWhenIdle != 0);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleItemUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_ToggleItemUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (static_cast<size_t>(params[2]) >= 0 && static_cast<size_t>(params[2]) < STREAMER_MAX_TYPES)
		{
			p->second.enabledItems.set(static_cast<size_t>(params[2]), static_cast<int>(params[3]) != 0);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleItemUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_IsToggleItemUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (static_cast<size_t>(params[2]) >= 0 && static_cast<size_t>(params[2]) < STREAMER_MAX_TYPES)
		{
			return static_cast<cell>(p->second.enabledItems.test(params[2]) != 0);
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_Update(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_Update");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		core->getStreamer()->startManualUpdate(p->second, true);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_UpdateEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(6, "Streamer_UpdateEx");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		if (static_cast<int>(params[5]) >= 0)
		{
			p->second.worldID = static_cast<int>(params[5]);
		}
		else
		{
			p->second.worldID = GetPlayerVirtualWorld(p->first);
		}
		if (static_cast<int>(params[6]) >= 0)
		{
			p->second.interiorID = static_cast<int>(params[6]);
		}
		else
		{
			p->second.interiorID = GetPlayerInterior(p->first);
		}
		core->getStreamer()->startManualUpdate(p->second, false);
		return 1;
	}
	return 0;
}

// Data Manipulation

cell AMX_NATIVE_CALL Natives::Streamer_GetFloatData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_GetFloatData");
	return static_cast<cell>(Manipulation::getFloatData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetFloatData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_SetFloatData");
	return static_cast<cell>(Manipulation::setFloatData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_GetIntData(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_GetIntData");
	return static_cast<cell>(Manipulation::getIntData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetIntData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_SetIntData");
	return static_cast<cell>(Manipulation::setIntData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_GetArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "Streamer_GetArrayData");
	return static_cast<cell>(Manipulation::getArrayData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "Streamer_SetArrayData");
	return static_cast<cell>(Manipulation::setArrayData(amx, params));
}


cell AMX_NATIVE_CALL Natives::Streamer_IsInArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_IsInArrayData");
	return static_cast<cell>(Manipulation::isInArrayData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_AppendArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_AppendArrayData");
	return static_cast<cell>(Manipulation::appendArrayData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_RemoveArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_RemoveArrayData");
	return static_cast<cell>(Manipulation::removeArrayData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_GetUpperBound(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetUpperBound");
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			int objectID = 0;
			for (boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.begin(); o != core->getData()->objects.end(); ++o)
			{
				if (o->first > objectID)
				{
					objectID = o->first;
				}
			}
			return static_cast<cell>(objectID + 1);
		}
		case STREAMER_TYPE_PICKUP:
		{
			int pickupID = 0;
			for (boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.begin(); p != core->getData()->pickups.end(); ++p)
			{
				if (p->first > pickupID)
				{
					pickupID = p->first;
				}
			}
			return static_cast<cell>(pickupID + 1);
		}
		case STREAMER_TYPE_CP:
		{
			int checkpointID = 0;
			for (boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
			{
				if (c->first > checkpointID)
				{
					checkpointID = c->first;
				}
			}
			return static_cast<cell>(checkpointID + 1);
		}
		case STREAMER_TYPE_RACE_CP:
		{
			int raceCheckpointID = 0;
			for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
			{
				if (r->first > raceCheckpointID)
				{
					raceCheckpointID = r->first;
				}
			}
			return static_cast<cell>(raceCheckpointID + 1);
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			int mapIconID = 0;
			for (boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin(); m != core->getData()->mapIcons.end(); ++m)
			{
				if (m->first > mapIconID)
				{
					mapIconID = m->first;
				}
			}
			return static_cast<cell>(mapIconID + 1);
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			int textLabelID = 0;
			for (boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.begin(); t != core->getData()->textLabels.end(); ++t)
			{
				if (t->first > textLabelID)
				{
					textLabelID = t->first;
				}
			}
			return static_cast<cell>(textLabelID + 1);
		}
		case STREAMER_TYPE_AREA:
		{
			int areaID = 0;
			for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				if (a->first > areaID)
				{
					areaID = a->first;
				}
			}
			return static_cast<cell>(areaID + 1);
		}
		default:
		{
			logprintf("*** Streamer_GetUpperBound: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

// Miscellaneous

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
				float distance = 0.0f;
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
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Box2D>(a->second->position));
						float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
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
					case STREAMER_AREA_TYPE_CUBE:
					{
						Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3D>(a->second->position));
						float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), centroid));
						Utility::storeFloatInNative(amx, params[6], distance);
						return 1;
					}
					case STREAMER_AREA_TYPE_POLYGON:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2D>(a->second->position).get<0>());
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
			logprintf("*** Streamer_GetDistanceToItem: Invalid type specified");
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
			logprintf("*** Streamer_GetDistanceToItem: Invalid number of dimensions specified (outside range of 2-3)");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsItemVisible(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_IsItemVisible");
	if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
	{
		boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(static_cast<int>(params[3]));
		if (i != core->getStreamer()->internalPickups.end())
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
				logprintf("*** Streamer_IsItemVisible: Invalid type specified");
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
		boost::unordered_map<int, int>::iterator p = core->getStreamer()->internalPickups.begin();
		while (p != core->getStreamer()->internalPickups.end())
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator q = core->getData()->pickups.find(q->first);
			if (serverWide || (q != core->getData()->pickups.end() && q->second->amx == amx))
			{
				DestroyPickup(p->second);
				p = core->getStreamer()->internalPickups.erase(p);
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
						DestroyPlayerObject(p->first, o->second);
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
						DisablePlayerCheckpoint(p->first);
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
						DisablePlayerRaceCheckpoint(p->first);
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
						RemovePlayerMapIcon(p->first, m->second);
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
						DeletePlayer3DTextLabel(p->first, t->second);
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
				logprintf("*** Streamer_DestroyAllVisibleItems: Invalid type specified");
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
		return static_cast<cell>(core->getStreamer()->internalPickups.size());
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
				logprintf("*** Streamer_CountVisibleItems: Invalid type specified");
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
			logprintf("*** Streamer_DestroyAllItems: Invalid type specified");
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
			logprintf("*** Streamer_CountItems: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

// Objects

cell AMX_NATIVE_CALL Natives::CreateDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicObject");
	if (core->getData()->getMaxItems(STREAMER_TYPE_OBJECT) == core->getData()->objects.size())
	{
		return 0;
	}
	int objectID = Item::Object::identifier.get();
	Item::SharedObject object(new Item::Object);
	object->amx = amx;
	object->extraID = 0;
	object->objectID = objectID;
	object->modelID = static_cast<int>(params[1]);
	object->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	object->rotation = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	Utility::addToContainer(object->worlds, static_cast<int>(params[8]));
	Utility::addToContainer(object->interiors, static_cast<int>(params[9]));
	Utility::addToContainer(object->players, static_cast<int>(params[10]));
	object->streamDistance = amx_ctof(params[11]) * amx_ctof(params[11]);
	object->drawDistance = amx_ctof(params[12]);
	core->getGrid()->addObject(object);
	core->getData()->objects.insert(std::make_pair(objectID, object));
	return static_cast<cell>(objectID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicObject");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		Utility::destroyObject(o);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicObject");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectPos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicObjectPos");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		Eigen::Vector3f position = o->second->position;
		o->second->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				SetPlayerObjectPos(p->first, i->second, o->second->position[0], o->second->position[1], o->second->position[2]);
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
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectPos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicObjectPos");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			core->getStreamer()->processActiveItems();
		}
		Utility::storeFloatInNative(amx, params[2], o->second->position[0]);
		Utility::storeFloatInNative(amx, params[3], o->second->position[1]);
		Utility::storeFloatInNative(amx, params[4], o->second->position[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectRot(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicObjectRot");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			return 0;
		}
		o->second->rotation = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				SetPlayerObjectRot(p->first, i->second, o->second->rotation[0], o->second->rotation[1], o->second->rotation[2]);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectRot(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicObjectRot");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			core->getStreamer()->processActiveItems();
		}
		Utility::storeFloatInNative(amx, params[2], o->second->rotation[0]);
		Utility::storeFloatInNative(amx, params[3], o->second->rotation[1]);
		Utility::storeFloatInNative(amx, params[4], o->second->rotation[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::MoveDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "MoveDynamicObject");
	if (!amx_ctof(params[5]))
	{
		return 0;
	}
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->attach)
		{
			logprintf("MoveDynamicObject: Object is currently attached and cannot be moved");
			return 0;
		}
		Eigen::Vector3f position(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		Eigen::Vector3f rotation(amx_ctof(params[6]), amx_ctof(params[7]), amx_ctof(params[8]));
		o->second->move = boost::intrusive_ptr<Item::Object::Move>(new Item::Object::Move);
		o->second->move->duration = static_cast<int>((static_cast<float>(boost::geometry::distance(position, o->second->position) / amx_ctof(params[5])) * 1000.0f));
		o->second->move->position.get<0>() = position;
		o->second->move->position.get<1>() = o->second->position;
		o->second->move->position.get<2>() = (position - o->second->position) / static_cast<float>(o->second->move->duration);
		o->second->move->rotation.get<0>() = rotation;
		if ((o->second->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
		{
			o->second->move->rotation.get<1>() = o->second->rotation;
			o->second->move->rotation.get<2>() = (rotation - o->second->rotation) / static_cast<float>(o->second->move->duration);
		}
		o->second->move->speed = amx_ctof(params[5]);
		o->second->move->time = boost::chrono::steady_clock::now();
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				StopPlayerObject(p->first, i->second);
				MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
			}
		}
		core->getStreamer()->movingObjects.insert(o->second);
		return static_cast<cell>(o->second->move->duration);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::StopDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "StopDynamicObject");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
				if (i != p->second.internalObjects.end())
				{
					StopPlayerObject(p->first, i->second);
				}
			}
			o->second->move.reset();
			core->getStreamer()->movingObjects.erase(o->second);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicObjectMoving(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsDynamicObjectMoving");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachCameraToDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AttachCameraToDynamicObject");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(static_cast<int>(params[2]));
		if (i != p->second.internalObjects.end())
		{
			AttachCameraToPlayerObject(p->first, i->second);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicObjectToVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "AttachDynamicObjectToVehicle");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			logprintf("AttachDynamicObjectToVehicle: Object is currently moving and cannot be attached");
			return 0;
		}
		o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
		o->second->attach->vehicle = static_cast<int>(params[2]);
		o->second->attach->offset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
		o->second->attach->rotation = Eigen::Vector3f(amx_ctof(params[6]), amx_ctof(params[7]), amx_ctof(params[8]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
				for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
				{
					if (m->second.main)
					{
						SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
					}
					else if (m->second.text)
					{
						SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
					}
				}
			}
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			core->getStreamer()->attachedObjects.insert(o->second);
		}
		else
		{
			o->second->attach.reset();
			core->getStreamer()->attachedObjects.erase(o->second);
			core->getGrid()->removeObject(o->second, true);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::EditDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "EditDynamicObject");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		core->getStreamer()->startManualUpdate(p->second, true);
		boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(static_cast<int>(params[2]));
		if (i != p->second.internalObjects.end())
		{
			EditPlayerObject(p->first, i->second);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectMaterial(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "GetDynamicObjectMaterial");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.find(static_cast<int>(params[2]));
		if (m != o->second->materials.end())
		{
			if (m->second.main)
			{
				Utility::storeIntegerInNative(amx, params[3], m->second.main->modelID);
				Utility::convertStringToNativeString(amx, params[4], params[7], m->second.main->txdFileName);
				Utility::convertStringToNativeString(amx, params[5], params[8], m->second.main->textureName);
				Utility::storeIntegerInNative(amx, params[6], m->second.main->materialColor);
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectMaterial(AMX *amx, cell *params)
{
	CHECK_PARAMS(6, "SetDynamicObjectMaterial");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		int index = static_cast<int>(params[2]);
		o->second->materials[index].main = boost::intrusive_ptr<Item::Object::Material::Main>(new Item::Object::Material::Main);
		o->second->materials[index].main->modelID = static_cast<int>(params[3]);
		o->second->materials[index].main->txdFileName = Utility::convertNativeStringToString(amx, params[4]);
		o->second->materials[index].main->textureName = Utility::convertNativeStringToString(amx, params[5]);
		o->second->materials[index].main->materialColor = static_cast<int>(params[6]);
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				SetPlayerObjectMaterial(p->first, i->second, index, o->second->materials[index].main->modelID, o->second->materials[index].main->txdFileName.c_str(), o->second->materials[index].main->textureName.c_str(), o->second->materials[index].main->materialColor);
			}
		}
		o->second->materials[index].text.reset();
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectMaterialText(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "GetDynamicObjectMaterialText");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.find(static_cast<int>(params[2]));
		if (m != o->second->materials.end())
		{
			if (m->second.text)
			{
				Utility::convertStringToNativeString(amx, params[3], params[11], m->second.text->materialText);
				Utility::storeIntegerInNative(amx, params[4], m->second.text->materialSize);
				Utility::convertStringToNativeString(amx, params[5], params[12], m->second.text->fontFace);
				Utility::storeIntegerInNative(amx, params[6], m->second.text->fontSize);
				Utility::storeIntegerInNative(amx, params[7], m->second.text->bold != 0);
				Utility::storeIntegerInNative(amx, params[8], m->second.text->fontColor);
				Utility::storeIntegerInNative(amx, params[9], m->second.text->backColor);
				Utility::storeIntegerInNative(amx, params[10], m->second.text->textAlignment);
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectMaterialText(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "SetDynamicObjectMaterialText");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		int index = static_cast<int>(params[2]);
		o->second->materials[index].text = boost::intrusive_ptr<Item::Object::Material::Text>(new Item::Object::Material::Text);
		o->second->materials[index].text->materialText = Utility::convertNativeStringToString(amx, params[3]);
		o->second->materials[index].text->materialSize = static_cast<int>(params[4]);
		o->second->materials[index].text->fontFace = Utility::convertNativeStringToString(amx, params[5]);
		o->second->materials[index].text->fontSize = static_cast<int>(params[6]);
		o->second->materials[index].text->bold = static_cast<int>(params[7]) != 0;
		o->second->materials[index].text->fontColor = static_cast<int>(params[8]);
		o->second->materials[index].text->backColor = static_cast<int>(params[9]);
		o->second->materials[index].text->textAlignment = static_cast<int>(params[10]);
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				SetPlayerObjectMaterialText(p->first, i->second, o->second->materials[index].text->materialText.c_str(), index, o->second->materials[index].text->materialSize, o->second->materials[index].text->fontFace.c_str(), o->second->materials[index].text->fontSize, o->second->materials[index].text->bold, o->second->materials[index].text->fontColor, o->second->materials[index].text->backColor, o->second->materials[index].text->textAlignment);
			}
		}
		o->second->materials[index].main.reset();
		return 1;
	}
	return 0;
}

// Pickups

cell AMX_NATIVE_CALL Natives::CreateDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicPickup");
	if (core->getData()->getMaxItems(STREAMER_TYPE_PICKUP) == core->getData()->pickups.size())
	{
		return 0;
	}
	int pickupID = Item::Pickup::identifier.get();
	Item::SharedPickup pickup(new Item::Pickup);
	pickup->amx = amx;
	pickup->extraID = 0;
	pickup->pickupID = pickupID;
	pickup->worldID = 0;
	pickup->modelID = static_cast<int>(params[1]);
	pickup->type = static_cast<int>(params[2]);
	pickup->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	Utility::addToContainer(pickup->worlds, static_cast<int>(params[6]));
	Utility::addToContainer(pickup->interiors, static_cast<int>(params[7]));
	Utility::addToContainer(pickup->players, static_cast<int>(params[8]));
	pickup->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	core->getGrid()->addPickup(pickup);
	core->getData()->pickups.insert(std::make_pair(pickupID, pickup));
	return static_cast<cell>(pickupID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicPickup");
	boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[1]));
	if (p != core->getData()->pickups.end())
	{
		Utility::destroyPickup(p);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicPickup");
	boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[1]));
	if (p != core->getData()->pickups.end())
	{
		return 1;
	}
	return 0;
}

// Checkpoints

cell AMX_NATIVE_CALL Natives::CreateDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "CreateDynamicCP");
	if (core->getData()->getMaxItems(STREAMER_TYPE_CP) == core->getData()->checkpoints.size())
	{
		return 0;
	}
	int checkpointID = Item::Checkpoint::identifier.get();
	Item::SharedCheckpoint checkpoint(new Item::Checkpoint);
	checkpoint->amx = amx;
	checkpoint->checkpointID = checkpointID;
	checkpoint->extraID = 0;
	checkpoint->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	checkpoint->size = amx_ctof(params[4]);
	Utility::addToContainer(checkpoint->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(checkpoint->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(checkpoint->players, static_cast<int>(params[7]));
	checkpoint->streamDistance = amx_ctof(params[8]) * amx_ctof(params[8]);
	core->getGrid()->addCheckpoint(checkpoint);
	core->getData()->checkpoints.insert(std::make_pair(checkpointID, checkpoint));
	return static_cast<cell>(checkpointID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicCP");
	boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[1]));
	if (c != core->getData()->checkpoints.end())
	{
		Utility::destroyCheckpoint(c);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicCP");
	boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[1]));
	if (c != core->getData()->checkpoints.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledCheckpoints.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledCheckpoints.end())
			{
				p->second.disabledCheckpoints.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledCheckpoints.end())
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[2]))
				{
					DisablePlayerCheckpoint(p->first);
					p->second.activeCheckpoint = 0;
					p->second.visibleCheckpoint = 0;
				}
				p->second.disabledCheckpoints.insert(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicCPs(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicCPs");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledCheckpoints.clear();
		if (!static_cast<int>(params[2]))
		{
			if (p->second.visibleCheckpoint != 0)
			{
				DisablePlayerCheckpoint(p->first);
				p->second.activeCheckpoint = 0;
				p->second.visibleCheckpoint = 0;
			}
			for (boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
			{
				p->second.disabledCheckpoints.insert(c->first);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInDynamicCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint == static_cast<int>(params[2]))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerVisibleDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetPlayerVisibleDynamicCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return p->second.visibleCheckpoint;
	}
	return 0;
}

// Race Checkpoints

cell AMX_NATIVE_CALL Natives::CreateDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicRaceCP");
	if (core->getData()->getMaxItems(STREAMER_TYPE_RACE_CP) == core->getData()->raceCheckpoints.size())
	{
		return 0;
	}
	int raceCheckpointID = Item::RaceCheckpoint::identifier.get();
	Item::SharedRaceCheckpoint raceCheckpoint(new Item::RaceCheckpoint);
	raceCheckpoint->amx = amx;
	raceCheckpoint->extraID = 0;
	raceCheckpoint->raceCheckpointID = raceCheckpointID;
	raceCheckpoint->type = static_cast<int>(params[1]);
	raceCheckpoint->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	raceCheckpoint->next = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	raceCheckpoint->size = amx_ctof(params[8]);
	Utility::addToContainer(raceCheckpoint->worlds, static_cast<int>(params[9]));
	Utility::addToContainer(raceCheckpoint->interiors, static_cast<int>(params[10]));
	Utility::addToContainer(raceCheckpoint->players, static_cast<int>(params[11]));
	raceCheckpoint->streamDistance = amx_ctof(params[12]) * amx_ctof(params[12]);
	core->getGrid()->addRaceCheckpoint(raceCheckpoint);
	core->getData()->raceCheckpoints.insert(std::make_pair(raceCheckpointID, raceCheckpoint));
	return static_cast<cell>(raceCheckpointID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicRaceCP");
	boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[1]));
	if (r != core->getData()->raceCheckpoints.end())
	{
		Utility::destroyRaceCheckpoint(r);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicRaceCP");
	boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[1]));
	if (r != core->getData()->raceCheckpoints.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicRaceCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledRaceCheckpoints.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledRaceCheckpoints.end())
			{
				p->second.disabledRaceCheckpoints.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledRaceCheckpoints.end())
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[2]))
				{
					DisablePlayerRaceCheckpoint(p->first);
					p->second.activeRaceCheckpoint = 0;
					p->second.visibleRaceCheckpoint = 0;
				}
				p->second.disabledRaceCheckpoints.insert(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicRaceCPs(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicRaceCPs");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledRaceCheckpoints.clear();
		if (!static_cast<int>(params[2]))
		{
			if (p->second.visibleRaceCheckpoint != 0)
			{
				DisablePlayerRaceCheckpoint(p->first);
				p->second.activeRaceCheckpoint = 0;
				p->second.visibleRaceCheckpoint = 0;
			}
			for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
			{
				p->second.disabledRaceCheckpoints.insert(r->first);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInDynamicRaceCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint == static_cast<int>(params[2]))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerVisibleDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetPlayerVisibleDynamicRaceCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return p->second.visibleRaceCheckpoint;
	}
	return 0;
}

// Map Icons

cell AMX_NATIVE_CALL Natives::CreateDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicMapIcon");
	if (core->getData()->getMaxItems(STREAMER_TYPE_MAP_ICON) == core->getData()->mapIcons.size())
	{
		return 0;
	}
	int mapIconID = Item::MapIcon::identifier.get();
	Item::SharedMapIcon mapIcon(new Item::MapIcon);
	mapIcon->amx = amx;
	mapIcon->extraID = 0;
	mapIcon->mapIconID = mapIconID;
	mapIcon->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	mapIcon->type = static_cast<int>(params[4]);
	mapIcon->color = static_cast<int>(params[5]);
	Utility::addToContainer(mapIcon->worlds, static_cast<int>(params[6]));
	Utility::addToContainer(mapIcon->interiors, static_cast<int>(params[7]));
	Utility::addToContainer(mapIcon->players, static_cast<int>(params[8]));
	mapIcon->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	mapIcon->style = static_cast<int>(params[10]);
	core->getGrid()->addMapIcon(mapIcon);
	core->getData()->mapIcons.insert(std::make_pair(mapIconID, mapIcon));
	return static_cast<cell>(mapIconID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicMapIcon");
	boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[1]));
	if (m != core->getData()->mapIcons.end())
	{
		Utility::destroyMapIcon(m);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicMapIcon");
	boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[1]));
	if (m != core->getData()->mapIcons.end())
	{
		return 1;
	}
	return 0;
}

// 3D Text Labels

cell AMX_NATIVE_CALL Natives::CreateDynamic3DTextLabel(AMX *amx, cell *params)
{
	CHECK_PARAMS(13, "CreateDynamic3DTextLabel");
	if (core->getData()->getMaxItems(STREAMER_TYPE_3D_TEXT_LABEL) == core->getData()->textLabels.size())
	{
		return 0;
	}
	int textLabelID = Item::TextLabel::identifier.get();
	Item::SharedTextLabel textLabel(new Item::TextLabel);
	textLabel->amx = amx;
	textLabel->extraID = 0;
	textLabel->textLabelID = textLabelID;
	textLabel->text = Utility::convertNativeStringToString(amx, params[1]);
	textLabel->color = static_cast<int>(params[2]);
	textLabel->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	textLabel->drawDistance = amx_ctof(params[6]);
	if (static_cast<int>(params[7]) != INVALID_GENERIC_ID || static_cast<int>(params[8]) != INVALID_GENERIC_ID)
	{
		textLabel->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
		textLabel->attach->player = static_cast<int>(params[7]);
		textLabel->attach->vehicle = static_cast<int>(params[8]);
		if (textLabel->position.cwiseAbs().maxCoeff() > 50.0f)
		{
			textLabel->position.setZero();
		}
		core->getStreamer()->attachedTextLabels.insert(textLabel);
	}
	textLabel->testLOS = static_cast<int>(params[9]) != 0;
	Utility::addToContainer(textLabel->worlds, static_cast<int>(params[10]));
	Utility::addToContainer(textLabel->interiors, static_cast<int>(params[11]));
	Utility::addToContainer(textLabel->players, static_cast<int>(params[12]));
	textLabel->streamDistance = amx_ctof(params[13]) * amx_ctof(params[13]);
	core->getGrid()->addTextLabel(textLabel);
	core->getData()->textLabels.insert(std::make_pair(textLabelID, textLabel));
	return static_cast<cell>(textLabelID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamic3DTextLabel(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamic3DTextLabel");
	boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[1]));
	if (t != core->getData()->textLabels.end())
	{
		Utility::destroyTextLabel(t);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamic3DTextLabel(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamic3DTextLabel");
	boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[1]));
	if (t != core->getData()->textLabels.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamic3DTextLabelText(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "GetDynamic3DTextLabelText");
	boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[1]));
	if (t != core->getData()->textLabels.end())
	{
		cell *text = NULL;
		amx_GetAddr(amx, params[2], &text);
		amx_SetString(text, t->second->text.c_str(), 0, 0, static_cast<size_t>(params[3]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::UpdateDynamic3DTextLabelText(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "UpdateDynamic3DTextLabelText");
	boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[1]));
	if (t != core->getData()->textLabels.end())
	{
		t->second->color = static_cast<int>(params[2]);
		t->second->text = Utility::convertNativeStringToString(amx, params[3]);
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
			if (i != p->second.internalTextLabels.end())
			{
				UpdatePlayer3DTextLabelText(p->first, i->second, t->second->color, t->second->text.c_str());
			}
		}
		return 1;
	}
	return 0;
}

// Areas

cell AMX_NATIVE_CALL Natives::CreateDynamicCircle(AMX *amx, cell *params)
{
	CHECK_PARAMS(6, "CreateDynamicCircle");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_CIRCLE;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->size = amx_ctof(params[3]) * amx_ctof(params[3]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[4]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[5]));
	Utility::addToContainer(area->players, static_cast<int>(params[6]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRectangle(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicRectangle");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_RECTANGLE;
	area->position = Box2D(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4])));
	boost::geometry::correct(boost::get<Box2D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(boost::get<Box2D>(area->position).min_corner(), boost::get<Box2D>(area->position).max_corner()));
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicSphere(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicSphere");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_SPHERE;
	area->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	area->size = amx_ctof(params[4]) * amx_ctof(params[4]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCube(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicCube");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_CUBE;
	area->position = Box3D(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
	boost::geometry::correct(boost::get<Box3D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Box3D>(area->position).min_corner()[0], boost::get<Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(area->position).max_corner()[0], boost::get<Box3D>(area->position).max_corner()[1])));
	Utility::addToContainer(area->worlds, static_cast<int>(params[7]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[8]));
	Utility::addToContainer(area->players, static_cast<int>(params[9]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPolygon(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicPolygon");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	if (static_cast<int>(params[4] >= 2 && static_cast<int>(params[4]) % 2))
	{
		logprintf("*** CreateDynamicPolygon: Number of points must be divisible by two");
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_POLYGON;
	Utility::convertArrayToPolygon(amx, params[1], params[4], boost::get<Polygon2D>(area->position));
	Box2D box = boost::geometry::return_envelope<Box2D>(boost::get<Polygon2D>(area->position).get<0>());
	area->size = static_cast<float>(boost::geometry::comparable_distance(box.min_corner(), box.max_corner()));
	boost::get<Polygon2D>(area->position).get<1>() = Eigen::Vector2f(amx_ctof(params[2]), amx_ctof(params[3]));
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicArea");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		Utility::destroyArea(a);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicArea");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledAreas.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledAreas.end())
			{
				p->second.disabledAreas.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledAreas.end())
			{
				p->second.disabledAreas.insert(static_cast<int>(params[2]));
				p->second.internalAreas.erase(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicAreas");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledAreas.clear();
		if (!static_cast<int>(params[2]))
		{
			for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				p->second.disabledAreas.insert(a->first);
			}
			p->second.internalAreas.clear();
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "IsPlayerInDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		bool recheck = static_cast<int>(params[3]) != 0;
		if (!recheck)
		{
			boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[2]));
			if (i != p->second.internalAreas.end())
			{
				return 1;
			}
		}
		else
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			return static_cast<cell>(Utility::isPointInArea(p->second.position, a->second)) != 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInAnyDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		bool recheck = static_cast<int>(params[2]) != 0;
		if (!recheck)
		{
			if (!p->second.internalAreas.empty())
			{
				return 1;
			}
		}
		else
		{
			for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				if (Utility::isPointInArea(p->second.position, a->second))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPointInDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "IsPointInDynamicArea");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return Utility::isPointInArea(Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4])), a->second);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPointInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "IsPointInAnyDynamicArea");
	for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		if (Utility::isPointInArea(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), a->second))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "AttachDynamicAreaToObject");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
		{
			logprintf("*** AttachDynamicAreaToObject: Only circles and spheres may be attached to objects");
			return 0;
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
			a->second->attach->object = boost::make_tuple(static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
			a->second->attach->player = INVALID_GENERIC_ID;
			a->second->attach->vehicle = INVALID_GENERIC_ID;
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if (a->second->attach->object.get<0>() != INVALID_GENERIC_ID)
				{
					a->second->attach.reset();
					core->getStreamer()->attachedAreas.erase(a->second);
					core->getGrid()->removeArea(a->second, true);
				}
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToPlayer(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AttachDynamicAreaToPlayer");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
		{
			logprintf("*** AttachDynamicAreaToPlayer: Only circles and spheres may be attached to players");
			return 0;
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
			a->second->attach->object.get<0>() = INVALID_GENERIC_ID;
			a->second->attach->player = static_cast<int>(params[2]);
			a->second->attach->vehicle = INVALID_GENERIC_ID;
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if (a->second->attach->player != INVALID_GENERIC_ID)
				{
					a->second->attach.reset();
					core->getStreamer()->attachedAreas.erase(a->second);
					core->getGrid()->removeArea(a->second, true);
				}
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AttachDynamicAreaToVehicle");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
		{
			logprintf("*** AttachDynamicAreaToVehicle: Only circles and spheres may be attached to vehicles");
			return 0;
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
			a->second->attach->object.get<0>() = INVALID_GENERIC_ID;
			a->second->attach->player = INVALID_GENERIC_ID;
			a->second->attach->vehicle = static_cast<int>(params[2]);
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if (a->second->attach->vehicle != INVALID_GENERIC_ID)
				{
					a->second->attach.reset();
					core->getStreamer()->attachedAreas.erase(a->second);
					core->getGrid()->removeArea(a->second, true);
				}
			}
		}
		return 1;
	}
	return 0;
}

// Extended

cell AMX_NATIVE_CALL Natives::CreateDynamicObjectEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(15, "CreateDynamicObjectEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_OBJECT) == core->getData()->objects.size())
	{
		return 0;
	}
	int objectID = Item::Object::identifier.get();
	Item::SharedObject object(new Item::Object);
	object->amx = amx;
	object->extraID = 0;
	object->objectID = objectID;
	object->modelID = static_cast<int>(params[1]);
	object->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	object->rotation = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	object->drawDistance = amx_ctof(params[8]);
	object->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	Utility::convertArrayToContainer(amx, params[10], params[13], object->worlds);
	Utility::convertArrayToContainer(amx, params[11], params[14], object->interiors);
	Utility::convertArrayToContainer(amx, params[12], params[15], object->players);
	core->getGrid()->addObject(object);
	core->getData()->objects.insert(std::make_pair(objectID, object));
	return static_cast<cell>(objectID);
	return 1;
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPickupEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicPickupEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_PICKUP) == core->getData()->pickups.size())
	{
		return 0;
	}
	int pickupID = Item::Pickup::identifier.get();
	Item::SharedPickup pickup(new Item::Pickup);
	pickup->amx = amx;
	pickup->extraID = 0;
	pickup->pickupID = pickupID;
	pickup->modelID = static_cast<int>(params[1]);
	pickup->type = static_cast<int>(params[2]);
	pickup->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	pickup->streamDistance = amx_ctof(params[6]) * amx_ctof(params[6]);
	Utility::convertArrayToContainer(amx, params[7], params[10], pickup->worlds);
	Utility::convertArrayToContainer(amx, params[8], params[11], pickup->interiors);
	Utility::convertArrayToContainer(amx, params[9], params[12], pickup->players);
	core->getGrid()->addPickup(pickup);
	core->getData()->pickups.insert(std::make_pair(pickupID, pickup));
	return static_cast<cell>(pickupID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCPEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(11, "CreateDynamicCPEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_CP) == core->getData()->checkpoints.size())
	{
		return 0;
	}
	int checkpointID = Item::Checkpoint::identifier.get();
	Item::SharedCheckpoint checkpoint(new Item::Checkpoint);
	checkpoint->amx = amx;
	checkpoint->checkpointID = checkpointID;
	checkpoint->extraID = 0;
	checkpoint->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	checkpoint->size = amx_ctof(params[4]);
	checkpoint->streamDistance = amx_ctof(params[5]) * amx_ctof(params[5]);
	Utility::convertArrayToContainer(amx, params[6], params[9], checkpoint->worlds);
	Utility::convertArrayToContainer(amx, params[7], params[10], checkpoint->interiors);
	Utility::convertArrayToContainer(amx, params[8], params[11], checkpoint->players);
	core->getGrid()->addCheckpoint(checkpoint);
	core->getData()->checkpoints.insert(std::make_pair(checkpointID, checkpoint));
	return static_cast<cell>(checkpointID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRaceCPEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(15, "CreateDynamicRaceCPEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_RACE_CP) == core->getData()->raceCheckpoints.size())
	{
		return 0;
	}
	int raceCheckpointID = Item::RaceCheckpoint::identifier.get();
	Item::SharedRaceCheckpoint raceCheckpoint(new Item::RaceCheckpoint);
	raceCheckpoint->amx = amx;
	raceCheckpoint->extraID = 0;
	raceCheckpoint->raceCheckpointID = raceCheckpointID;
	raceCheckpoint->type = static_cast<int>(params[1]);
	raceCheckpoint->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	raceCheckpoint->next = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	raceCheckpoint->size = amx_ctof(params[8]);
	raceCheckpoint->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	Utility::convertArrayToContainer(amx, params[10], params[13], raceCheckpoint->worlds);
	Utility::convertArrayToContainer(amx, params[11], params[14], raceCheckpoint->interiors);
	Utility::convertArrayToContainer(amx, params[12], params[15], raceCheckpoint->players);
	core->getGrid()->addRaceCheckpoint(raceCheckpoint);
	core->getData()->raceCheckpoints.insert(std::make_pair(raceCheckpointID, raceCheckpoint));
	return static_cast<cell>(raceCheckpointID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicMapIconEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(13, "CreateDynamicMapIconEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_MAP_ICON) == core->getData()->mapIcons.size())
	{
		return 0;
	}
	int mapIconID = Item::MapIcon::identifier.get();
	Item::SharedMapIcon mapIcon(new Item::MapIcon);
	mapIcon->amx = amx;
	mapIcon->extraID = 0;
	mapIcon->mapIconID = mapIconID;
	mapIcon->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	mapIcon->type = static_cast<int>(params[4]);
	mapIcon->color = static_cast<int>(params[5]);
	mapIcon->style = static_cast<int>(params[6]);
	mapIcon->streamDistance = amx_ctof(params[7]) * amx_ctof(params[7]);
	Utility::convertArrayToContainer(amx, params[8], params[11], mapIcon->worlds);
	Utility::convertArrayToContainer(amx, params[9], params[12], mapIcon->interiors);
	Utility::convertArrayToContainer(amx, params[10], params[13], mapIcon->players);
	core->getGrid()->addMapIcon(mapIcon);
	core->getData()->mapIcons.insert(std::make_pair(mapIconID, mapIcon));
	return static_cast<cell>(mapIconID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamic3DTextLabelEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(16, "CreateDynamic3DTextLabelEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_3D_TEXT_LABEL) == core->getData()->textLabels.size())
	{
		return 0;
	}
	int textLabelID = Item::TextLabel::identifier.get();
	Item::SharedTextLabel textLabel(new Item::TextLabel);
	textLabel->amx = amx;
	textLabel->extraID = 0;
	textLabel->textLabelID = textLabelID;
	textLabel->text = Utility::convertNativeStringToString(amx, params[1]);
	textLabel->color = static_cast<int>(params[2]);
	textLabel->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	textLabel->drawDistance = amx_ctof(params[6]);
	if (static_cast<int>(params[7]) != INVALID_GENERIC_ID || static_cast<int>(params[8]) != INVALID_GENERIC_ID)
	{
		textLabel->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
		textLabel->attach->player = static_cast<int>(params[7]);
		textLabel->attach->vehicle = static_cast<int>(params[8]);
		if (textLabel->position.cwiseAbs().maxCoeff() > 50.0f)
		{
			textLabel->position.setZero();
		}
		core->getStreamer()->attachedTextLabels.insert(textLabel);
	}
	textLabel->testLOS = static_cast<int>(params[9]) != 0;
	textLabel->streamDistance = amx_ctof(params[10]) * amx_ctof(params[10]);
	Utility::convertArrayToContainer(amx, params[11], params[14], textLabel->worlds);
	Utility::convertArrayToContainer(amx, params[12], params[15], textLabel->interiors);
	Utility::convertArrayToContainer(amx, params[13], params[16], textLabel->players);
	core->getGrid()->addTextLabel(textLabel);
	core->getData()->textLabels.insert(std::make_pair(textLabelID, textLabel));
	return static_cast<cell>(textLabelID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCircleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicCircleEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_CIRCLE;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->size = amx_ctof(params[3]) * amx_ctof(params[3]);
	Utility::convertArrayToContainer(amx, params[4], params[7], area->worlds);
	Utility::convertArrayToContainer(amx, params[5], params[8], area->interiors);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRectangleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicRectangleEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_RECTANGLE;
	area->position = Box2D(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4])));
	boost::geometry::correct(boost::get<Box2D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(boost::get<Box2D>(area->position).min_corner(), boost::get<Box2D>(area->position).max_corner()));
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicSphereEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicSphereEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_SPHERE;
	area->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	area->size = amx_ctof(params[4]) * amx_ctof(params[4]);
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCubeEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicCubeEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_CUBE;
	area->position = Box3D(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
	boost::geometry::correct(boost::get<Box3D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Box3D>(area->position).min_corner()[0], boost::get<Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(area->position).max_corner()[0], boost::get<Box3D>(area->position).max_corner()[1])));
	Utility::convertArrayToContainer(amx, params[7], params[10], area->worlds);
	Utility::convertArrayToContainer(amx, params[8], params[11], area->interiors);
	Utility::convertArrayToContainer(amx, params[9], params[12], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPolygonEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicPolygonEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	if (static_cast<int>(params[4] >= 2 && static_cast<int>(params[4]) % 2))
	{
		logprintf("*** CreateDynamicPolygonEx: Number of points must be divisible by two");
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_POLYGON;
	Utility::convertArrayToPolygon(amx, params[1], params[4], boost::get<Polygon2D>(area->position));
	Box2D box = boost::geometry::return_envelope<Box2D>(boost::get<Polygon2D>(area->position).get<0>());
	area->size = static_cast<float>(boost::geometry::comparable_distance(box.min_corner(), box.max_corner()));
	boost::get<Polygon2D>(area->position).get<1>() = Eigen::Vector2f(amx_ctof(params[2]), amx_ctof(params[3]));
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

// Internal

cell AMX_NATIVE_CALL Natives::Streamer_CallbackHook(AMX *amx, cell *params)
{
	core->getEvents()->setInterface(amx);
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_OPC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerConnect(static_cast<int>(*playerid)));
		}
		case STREAMER_OPDC:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			cell *playerid = NULL, *reason = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &reason);
			return static_cast<cell>(core->getEvents()->OnPlayerDisconnect(static_cast<int>(*playerid), static_cast<int>(*reason)));
		}
		case STREAMER_OPEO:
		{
			CHECK_PARAMS(11, "Streamer_CallbackHook");
			cell *playerid = NULL, *playerobject = NULL, *objectid = NULL, *response = NULL, *x = NULL, *y = NULL, *z = NULL, *rx = NULL, *ry = NULL, *rz = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &playerobject);
			amx_GetAddr(amx, params[4], &objectid);
			amx_GetAddr(amx, params[5], &response);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);
			amx_GetAddr(amx, params[9], &rx);
			amx_GetAddr(amx, params[10], &ry);
			amx_GetAddr(amx, params[11], &rz);
			return static_cast<cell>(core->getEvents()->OnPlayerEditObject(static_cast<int>(*playerid), static_cast<int>(*playerobject), static_cast<int>(*objectid), static_cast<int>(*response), amx_ctof(*x), amx_ctof(*y), amx_ctof(*z), amx_ctof(*rx), amx_ctof(*ry), amx_ctof(*rz)));
		}
		case STREAMER_OPSO:
		{
			CHECK_PARAMS(8, "Streamer_CallbackHook");
			cell *playerid = NULL, *type = NULL, *objectid = NULL, *modelid = NULL, *x = NULL, *y = NULL, *z = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &type);
			amx_GetAddr(amx, params[4], &objectid);
			amx_GetAddr(amx, params[5], &modelid);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);
			return static_cast<cell>(core->getEvents()->OnPlayerSelectObject(static_cast<int>(*playerid), static_cast<int>(*type), static_cast<int>(*objectid), static_cast<int>(*modelid), amx_ctof(*x), amx_ctof(*y), amx_ctof(*z)));
		}
		case STREAMER_OPPP:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			cell *playerid = NULL, *pickupid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &pickupid);
			return static_cast<cell>(core->getEvents()->OnPlayerPickUpPickup(static_cast<int>(*playerid), static_cast<int>(*pickupid)));
		}
		case STREAMER_OPEC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerEnterCheckpoint(static_cast<int>(*playerid)));
		}
		case STREAMER_OPLC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerLeaveCheckpoint(static_cast<int>(*playerid)));
		}
		case STREAMER_OPERC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerEnterRaceCheckpoint(static_cast<int>(*playerid)));
		}
		case STREAMER_OPLRC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerLeaveRaceCheckpoint(static_cast<int>(*playerid)));
		}
		case STREAMER_OPWS:
		{
			CHECK_PARAMS(8, "Streamer_CallbackHook");
			cell *playerid = NULL, *weaponid = NULL, *hittype = NULL, *hitid = NULL, *x = NULL, *y = NULL, *z = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &weaponid);
			amx_GetAddr(amx, params[4], &hittype);
			amx_GetAddr(amx, params[5], &hitid);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);
			return static_cast<cell>(core->getEvents()->OnPlayerWeaponShot(static_cast<int>(*playerid), static_cast<int>(*weaponid), static_cast<int>(*hittype), static_cast<int>(*hitid), amx_ctof(*x), amx_ctof(*y), amx_ctof(*z)));
		}
	}
	return 0;
}

// Deprecated

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicObjects(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_OBJECT, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicObjects(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_OBJECT, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicPickups(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_PICKUP, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicPickups(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_PICKUP, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicCPs(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_CP, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicCPs(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_CP, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicRaceCPs(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_RACE_CP, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicRaceCPs(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_RACE_CP, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicMapIcons(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_MAP_ICON, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicMapIcons(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_MAP_ICON, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamic3DTextLabels(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_3D_TEXT_LABEL, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamic3DTextLabels(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_3D_TEXT_LABEL, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicAreas(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_AREA, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicAreas(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_AREA, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}
