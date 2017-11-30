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

#ifndef MANIPULATION_ARRAY_H
#define MANIPULATION_ARRAY_H

#include "../manipulation.h"
#include "../utility.h"

namespace Manipulation
{
	int getArrayData(AMX *amx, cell *params);
	int setArrayData(AMX *amx, cell *params);
	int isInArrayData(AMX *amx, cell *params);
	int appendArrayData(AMX *amx, cell *params);
	int removeArrayData(AMX *amx, cell *params);
	int getArrayDataLength(AMX *amx, cell *params);

	template <typename T>
	int getArrayDataForItem(T &container, AMX *amx, int id, int data, cell output, cell size, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (data)
			{
				case AreaID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->areas) != 0;
				}
				case ExtraID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->extras) != 0;
				}
				case InteriorID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->interiors) != 0;
				}
				case PlayerID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->players) != 0;
				}
				case WorldID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->worlds) != 0;
				}
				default:
				{
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidID;
		}
		return 0;
	}

	template <typename T>
	int setArrayDataForItem(T &container, AMX *amx, int id, int data, cell input, cell size, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (data)
			{
				case AreaID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->areas) != 0;
				}
				case ExtraID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->extras) != 0;
				}
				case InteriorID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->interiors) != 0;
				}
				case PlayerID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->players) != 0;
				}
				case WorldID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->worlds) != 0;
				}
				default:
				{
					error = InvalidData;
					return 0;
				}
			}
		}
		error = InvalidID;
		return 0;
	}

	template <typename T>
	int isInArrayDataForItem(T &container, int id, int data, int value, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (data)
			{
				case AreaID:
				{
					return Utility::isInContainer(i->second->areas, value) != 0;
				}
				case ExtraID:
				{
					return Utility::isInContainer(i->second->extras, value) != 0;
				}
				case InteriorID:
				{
					return Utility::isInContainer(i->second->interiors, value) != 0;
				}
				case PlayerID:
				{
					return Utility::isInContainer(i->second->players, value) != 0;
				}
				case WorldID:
				{
					return Utility::isInContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidID;
		}
		return 0;
	}

	template <typename T>
	int appendArrayDataForItem(T &container, int id, int data, int value, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (data)
			{
				case AreaID:
				{
					return Utility::addToContainer(i->second->areas, value) != 0;
				}
				case ExtraID:
				{
					return Utility::addToContainer(i->second->extras, value) != 0;
				}
				case InteriorID:
				{
					return Utility::addToContainer(i->second->interiors, value) != 0;
				}
				case PlayerID:
				{
					return Utility::addToContainer(i->second->players, value) != 0;
				}
				case WorldID:
				{
					return Utility::addToContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidID;
		}
		return 0;
	}

	template <typename T>
	int removeArrayDataForItem(T &container, int id, int data, int value, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (data)
			{
				case AreaID:
				{
					return Utility::removeFromContainer(i->second->areas, value) != 0;
				}
				case ExtraID:
				{
					return Utility::removeFromContainer(i->second->extras, value) != 0;
				}
				case InteriorID:
				{
					return Utility::removeFromContainer(i->second->interiors, value) != 0;
				}
				case PlayerID:
				{
					return Utility::removeFromContainer(i->second->players, value) != 0;
				}
				case WorldID:
				{
					return Utility::removeFromContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidID;
		}
		return 0;
	}

	template <typename T>
	int getArrayDataLengthForItem(T &container, int id, int data, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (data)
			{
				case AreaID:
				{
					int size = static_cast<int>(i->second->areas.size());
					return size ? size : -1;
				}
				case ExtraID:
				{
					return static_cast<int>(i->second->extras.size());
				}
				case InteriorID:
				{
					int size = static_cast<int>(i->second->interiors.size());
					return size ? size : -1;
				}
				case PlayerID:
				{
					return static_cast<int>(i->second->players.count());
				}
				case WorldID:
				{
					int size = static_cast<int>(i->second->worlds.size());
					return size ? size : -1;
				}
				default:
				{
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidID;
		}
		return 0;
	}
}

#endif
