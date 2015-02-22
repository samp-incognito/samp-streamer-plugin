/*
 * Copyright (C) 2015 Incognito
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
#include "../main.h"
#include "../manipulation.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>

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
			Utility::logError("Streamer_GetUpperBound: Invalid type specified");
			return 0;
		}
	}
	return 0;
}
