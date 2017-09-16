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

#include <boost/scoped_ptr.hpp>

cell AMX_NATIVE_CALL Natives::Streamer_GetTickRate(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getStreamer()->getTickRate());
}

cell AMX_NATIVE_CALL Natives::Streamer_SetTickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_SetTickRate");
	return static_cast<cell>(core->getStreamer()->setTickRate(static_cast<std::size_t>(params[1])));
}

cell AMX_NATIVE_CALL Natives::Streamer_GetPlayerTickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetPlayerTickRate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return static_cast<cell>(p->second.tickRate);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetPlayerTickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetPlayerTickRate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.tickRate = static_cast<std::size_t>(params[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleChunkStream(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_ToggleChunkStream");
	core->getStreamer()->setChunkStreamingEnabled(static_cast<int>(params[1]) != 0);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleChunkStream(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getStreamer()->getChunkStreamingEnabled());
}

cell AMX_NATIVE_CALL Natives::Streamer_GetChunkTickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_GetChunkTickRate");
	return static_cast<cell>(Utility::getChunkTickRate(static_cast<std::size_t>(params[1]), static_cast<std::size_t>(params[2])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetChunkTickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_SetChunkTickRate");
	return static_cast<cell>(Utility::setChunkTickRate(static_cast<int>(params[1]), static_cast<std::size_t>(params[2]), static_cast<std::size_t>(params[3])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetChunkSize(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetChunkSize");
	return static_cast<cell>(core->getStreamer()->getChunkSize(static_cast<std::size_t>(params[1])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetChunkSize(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetChunkSize");
	return static_cast<cell>(core->getStreamer()->setChunkSize(static_cast<int>(params[1]), static_cast<std::size_t>(params[2])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetMaxItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetMaxItems");
	return static_cast<cell>(core->getData()->getGlobalMaxItems(static_cast<std::size_t>(params[1])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetMaxItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetMaxItems");
	return static_cast<cell>(core->getData()->setGlobalMaxItems(static_cast<int>(params[1]), static_cast<std::size_t>(params[2])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_GetVisibleItems");
	return static_cast<cell>(Utility::getMaxVisibleItems(static_cast<std::size_t>(params[1]), static_cast<int>(params[2])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_SetVisibleItems");
	return static_cast<cell>(Utility::setMaxVisibleItems(static_cast<int>(params[1]), static_cast<std::size_t>(params[2]), static_cast<int>(params[3])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetRadiusMultiplier(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_GetRadiusMultiplier");
	float radiusMultiplier = Utility::getRadiusMultiplier(static_cast<std::size_t>(params[1]), static_cast<int>(params[3]));
	Utility::storeFloatInNative(amx, params[2], radiusMultiplier);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetRadiusMultiplier(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_SetRadiusMultiplier");
	return static_cast<cell>(Utility::setRadiusMultiplier(static_cast<int>(params[1]), amx_ctof(params[2]), static_cast<int>(params[3])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetTypePriority(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_GetTypePriority");
	return Utility::convertContainerToArray(amx, params[1], params[2], core->getData()->typePriority);
}

cell AMX_NATIVE_CALL Natives::Streamer_SetTypePriority(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetTypePriority");
	return Utility::convertArrayToContainer(amx, params[1], params[2], core->getData()->typePriority);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetCellDistance(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetCellDistance");
	float cellDistance = core->getGrid()->getCellDistance();
	Utility::storeFloatInNative(amx, params[1], cellDistance);
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
	CHECK_PARAMS(1, "Streamer_GetCellSize");
	float cellSize = core->getGrid()->getCellSize();
	Utility::storeFloatInNative(amx, params[1], cellSize);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetCellSize(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_SetCellSize");
	core->getGrid()->setCellSize(amx_ctof(params[1]));
	core->getGrid()->rebuildGrid();
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleItemStatic(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_ToggleItemStatic");
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				if (static_cast<int>(params[3]))
				{
					if (o->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && o->second->originalComparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						o->second->originalComparableStreamDistance = o->second->comparableStreamDistance;
						o->second->comparableStreamDistance = -1.0f;
					}
				}
				else
				{
					if (o->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && o->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						o->second->comparableStreamDistance = o->second->originalComparableStreamDistance;
						o->second->originalComparableStreamDistance = -1.0f;
					}
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
				if (static_cast<int>(params[3]))
				{
					if (p->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && p->second->originalComparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						p->second->originalComparableStreamDistance = p->second->comparableStreamDistance;
						p->second->comparableStreamDistance = -1.0f;
					}
				}
				else
				{
					if (p->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && p->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						p->second->comparableStreamDistance = p->second->originalComparableStreamDistance;
						p->second->originalComparableStreamDistance = -1.0f;
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
				if (static_cast<int>(params[3]))
				{
					if (c->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && c->second->originalComparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						c->second->originalComparableStreamDistance = c->second->comparableStreamDistance;
						c->second->comparableStreamDistance = -1.0f;
					}
				}
				else
				{
					if (c->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && c->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						c->second->comparableStreamDistance = c->second->originalComparableStreamDistance;
						c->second->originalComparableStreamDistance = -1.0f;
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
				if (static_cast<int>(params[3]))
				{
					if (r->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && r->second->originalComparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						r->second->originalComparableStreamDistance = r->second->comparableStreamDistance;
						r->second->comparableStreamDistance = -1.0f;
					}
				}
				else
				{
					if (r->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && r->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						r->second->comparableStreamDistance = r->second->originalComparableStreamDistance;
						r->second->originalComparableStreamDistance = -1.0f;
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
				if (static_cast<int>(params[3]))
				{
					if (m->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && m->second->originalComparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						m->second->originalComparableStreamDistance = m->second->comparableStreamDistance;
						m->second->comparableStreamDistance = -1.0f;
					}
				}
				else
				{
					if (m->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && m->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						m->second->comparableStreamDistance = m->second->originalComparableStreamDistance;
						m->second->originalComparableStreamDistance = -1.0f;
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
				if (static_cast<int>(params[3]))
				{
					if (t->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && t->second->originalComparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						t->second->originalComparableStreamDistance = t->second->comparableStreamDistance;
						t->second->comparableStreamDistance = -1.0f;
					}
				}
				else
				{
					if (t->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && t->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						t->second->comparableStreamDistance = t->second->originalComparableStreamDistance;
						t->second->originalComparableStreamDistance = -1.0f;
					}
				}
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				if (static_cast<int>(params[3]))
				{
					if (a->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && a->second->originalComparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						a->second->originalComparableStreamDistance = a->second->comparableStreamDistance;
						a->second->comparableStreamDistance = -1.0f;
					}
				}
				else
				{
					if (a->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && a->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						a->second->comparableStreamDistance = a->second->originalComparableStreamDistance;
						a->second->originalComparableStreamDistance = -1.0f;
					}
				}
				return 1;
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_ToggleItemStatic: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleItemStatic(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_IsToggleItemStatic");
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				if (o->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && o->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					return 1;
				}
			}
			return 0;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				if (p->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && p->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					return 1;
				}
			}
			return 0;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				if (c->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && c->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					return 1;
				}
			}
			return 0;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				if (r->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && r->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					return 1;
				}
			}
			return 0;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				if (m->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && m->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					return 1;
				}
			}
			return 0;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				if (t->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && t->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					return 1;
				}
			}
			return 0;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				if (a->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && a->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					return 1;
				}
			}
			return 0;
		}
		default:
		{
			Utility::logError("Streamer_IsToggleItemStatic: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleItemInvAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_ToggleItemInvAreas");
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				o->second->inverseAreaChecking = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				p->second->inverseAreaChecking = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				c->second->inverseAreaChecking = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				r->second->inverseAreaChecking = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				m->second->inverseAreaChecking = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				t->second->inverseAreaChecking = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				a->second->inverseAreaChecking = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_ToggleItemInvAreas: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleItemInvAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_IsToggleItemInvAreas");
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				return static_cast<cell>(o->second->inverseAreaChecking != 0);
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				return static_cast<cell>(p->second->inverseAreaChecking != 0);
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				return static_cast<cell>(c->second->inverseAreaChecking != 0);
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				return static_cast<cell>(r->second->inverseAreaChecking != 0);
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				return static_cast<cell>(m->second->inverseAreaChecking != 0);
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				return static_cast<cell>(t->second->inverseAreaChecking != 0);
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				return static_cast<cell>(a->second->inverseAreaChecking != 0);
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_IsToggleItemInvAreas: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleItemCallbacks(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_ToggleItemCallbacks");
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				o->second->streamCallbacks = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				p->second->streamCallbacks = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				c->second->streamCallbacks = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				r->second->streamCallbacks = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				m->second->streamCallbacks = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				t->second->streamCallbacks = static_cast<int>(params[3]) != 0;
				return 1;
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_ToggleItemCallbacks: Invalid type specified.");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleItemCallbacks(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_IsToggleItemCallbacks");
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				return static_cast<cell>(o->second->streamCallbacks != 0);
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				return static_cast<cell>(p->second->streamCallbacks != 0);
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				return static_cast<cell>(c->second->streamCallbacks != 0);
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				return static_cast<cell>(r->second->streamCallbacks != 0);
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				return static_cast<cell>(m->second->streamCallbacks != 0);
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				return static_cast<cell>(t->second->streamCallbacks != 0);
			}
			break;
		}
		default:
		{
			Utility::logError("Streamer_IsToggleItemCallbacks: Invalid type specified.");
			return 0;
		}
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleErrorCallback(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_ToggleErrorCallback");
	core->getData()->errorCallbackEnabled = static_cast<int>(params[1]) != 0;
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleErrorCallback(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_IsToggleErrorCallback");
	return static_cast<cell>(core->getData()->errorCallbackEnabled != 0);
}
