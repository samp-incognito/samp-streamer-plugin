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

cell AMX_NATIVE_CALL Natives::Streamer_ToggleStaticItem(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_ToggleStaticItem");
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
		default:
		{
			Utility::logError("Streamer_ToggleStaticItem: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleStaticItem(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_IsToggleStaticItem");
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
		default:
		{
			Utility::logError("Streamer_IsToggleStaticItem: Invalid type specified");
			return 0;
		}
	}
	return 0;
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
