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

#include "array.h"

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

#include <bitset>
#include <cmath>

using namespace Manipulation;

int Manipulation::getArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = getArrayDataForItem(core->getData()->objects, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = getArrayDataForItem(core->getData()->pickups, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = getArrayDataForItem(core->getData()->checkpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = getArrayDataForItem(core->getData()->raceCheckpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = getArrayDataForItem(core->getData()->mapIcons, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = getArrayDataForItem(core->getData()->textLabels, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			switch (static_cast<int>(params[3]))
			{
				case AreaID:
				{
					error = InvalidData;
					break;
				}
				default:
				{
					result = getArrayDataForItem(core->getData()->areas, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
					break;
				}
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			result = getArrayDataForItem(core->getData()->actors, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_GetArrayData: Invalid data specified.");
			break;
		}
		case InvalidID:
		{
			Utility::logError("Streamer_GetArrayData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_GetArrayData: Invalid type specified.");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::setArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = setArrayDataForItem(core->getData()->objects, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = setArrayDataForItem(core->getData()->pickups, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = setArrayDataForItem(core->getData()->checkpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = setArrayDataForItem(core->getData()->raceCheckpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = setArrayDataForItem(core->getData()->mapIcons, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = setArrayDataForItem(core->getData()->textLabels, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			switch (static_cast<int>(params[3]))
			{
				case AreaID:
				{
					error = InvalidData;
					break;
				}
				default:
				{
					result = setArrayDataForItem(core->getData()->areas, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
					break;
				}
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			result = setArrayDataForItem(core->getData()->actors, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_SetArrayData: Invalid data specified.");
			break;
		}
		case InvalidID:
		{
			Utility::logError("Streamer_SetArrayData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_SetArrayData: Invalid type specified.");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::isInArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = isInArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = isInArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = isInArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = isInArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = isInArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = isInArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			switch (static_cast<int>(params[3]))
			{
				case AreaID:
				{
					error = InvalidData;
					break;
				}
				default:
				{
					result = isInArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
					break;
				}
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			result = isInArrayDataForItem(core->getData()->actors, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_IsInArrayData: Invalid data specified.");
			break;
		}
		case InvalidID:
		{
			Utility::logError("Streamer_IsInArrayData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_IsInArrayData: Invalid type specified.");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::appendArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = appendArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = appendArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = appendArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = appendArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = appendArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = appendArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			switch (static_cast<int>(params[3]))
			{
				case AreaID:
				{
					error = InvalidData;
					break;
				}
				default:
				{
					result = appendArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
					break;
				}
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			result = appendArrayDataForItem(core->getData()->actors, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_AppendArrayData: Invalid data specified.");
			break;
		}
		case InvalidID:
		{
			Utility::logError("Streamer_AppendArrayData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_AppendArrayData: Invalid type specified.");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::removeArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = removeArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = removeArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = removeArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = removeArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = removeArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = removeArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			switch (static_cast<int>(params[3]))
			{
				case AreaID:
				{
					error = InvalidData;
					break;
				}
				default:
				{
					result = removeArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
					break;
				}
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			result = removeArrayDataForItem(core->getData()->actors, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_RemoveArrayData: Invalid data specified.");
			break;
		}
		case InvalidID:
		{
			Utility::logError("Streamer_RemoveArrayData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_RemoveArrayData: Invalid type specified.");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::getArrayDataLength(AMX *amx, cell *params)
{
	int error = -1, result = -1;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = getArrayDataLengthForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = getArrayDataLengthForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = getArrayDataLengthForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = getArrayDataLengthForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = getArrayDataLengthForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = getArrayDataLengthForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			switch (static_cast<int>(params[3]))
			{
				case AreaID:
				{
					error = InvalidData;
					break;
				}
				default:
				{
					result = getArrayDataLengthForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), error);
					break;
				}
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			result = getArrayDataLengthForItem(core->getData()->actors, static_cast<int>(params[2]), static_cast<int>(params[3]), error);
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_GetArrayDataLength: Invalid data specified.");
			break;
		}
		case InvalidID:
		{
			Utility::logError("Streamer_GetArrayDataLength: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_GetArrayDataLength: Invalid type specified.");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}
