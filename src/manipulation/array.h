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
				case AreaId:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->areas) != 0;
				}
				case ExtraId:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->extras) != 0;
				}
				case InteriorId:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->interiors) != 0;
				}
				case PlayerId:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->players) != 0;
				}
				case WorldId:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->worlds) != 0;
				}
				default:
				{
					if (data & 0x40000000)
					{
						boost::unordered_map<int, std::vector<int>>::iterator p = i->second->extraExtras.find(data & ~0xC0000000);
						if (p != i->second->extraExtras.end())
						{
							return Utility::convertContainerToArray(amx, output, size, p->second) != 0;
						}
					}
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidId;
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
				case AreaId:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->areas) != 0;
				}
				case ExtraId:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->extras) != 0;
				}
				case InteriorId:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->interiors) != 0;
				}
				case PlayerId:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->players) != 0;
				}
				case WorldId:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->worlds) != 0;
				}
				default:
				{
					if (data & 0x40000000)
					{
						i->second->extraExtras[data & ~0xC0000000] = std::vector<int>();
						return Utility::convertArrayToContainer(amx, input, size, i->second->extraExtras[data & ~0xC0000000]) != 0;
					}
					error = InvalidData;
					return 0;
				}
			}
		}
		error = InvalidId;
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
				case AreaId:
				{
					return Utility::isInContainer(i->second->areas, value) != 0;
				}
				case ExtraId:
				{
					return Utility::isInContainer(i->second->extras, value) != 0;
				}
				case InteriorId:
				{
					return Utility::isInContainer(i->second->interiors, value) != 0;
				}
				case PlayerId:
				{
					return Utility::isInContainer(i->second->players, value) != 0;
				}
				case WorldId:
				{
					return Utility::isInContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					if (data & 0x40000000)
					{
						boost::unordered_map<int, std::vector<int>>::iterator p = i->second->extraExtras.find(data & ~0xC0000000);
						if (p != i->second->extraExtras.end())
						{
							return Utility::isInContainer(p->second, value) != 0;
						}
					}
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidId;
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
				case AreaId:
				{
					return Utility::addToContainer(i->second->areas, value) != 0;
				}
				case ExtraId:
				{
					return Utility::addToContainer(i->second->extras, value) != 0;
				}
				case InteriorId:
				{
					return Utility::addToContainer(i->second->interiors, value) != 0;
				}
				case PlayerId:
				{
					return Utility::addToContainer(i->second->players, value) != 0;
				}
				case WorldId:
				{
					return Utility::addToContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					if (data & 0x40000000)
					{
						boost::unordered_map<int, std::vector<int>>::iterator p = i->second->extraExtras.find(data & ~0xC0000000);
						if (p != i->second->extraExtras.end())
						{
							return Utility::addToContainer(p->second, value) != 0;
						}
					}
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidId;
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
				case AreaId:
				{
					return Utility::removeFromContainer(i->second->areas, value) != 0;
				}
				case ExtraId:
				{
					return Utility::removeFromContainer(i->second->extras, value) != 0;
				}
				case InteriorId:
				{
					return Utility::removeFromContainer(i->second->interiors, value) != 0;
				}
				case PlayerId:
				{
					return Utility::removeFromContainer(i->second->players, value) != 0;
				}
				case WorldId:
				{
					return Utility::removeFromContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					if (data & 0x40000000)
					{
						boost::unordered_map<int, std::vector<int>>::iterator p = i->second->extraExtras.find(data & ~0xC0000000);
						if (p != i->second->extraExtras.end())
						{
							return Utility::removeFromContainer(p->second, value) != 0;
						}
					}
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidId;
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
				case AreaId:
				{
					int size = static_cast<int>(i->second->areas.size());
					return size ? size : -1;
				}
				case ExtraId:
				{
					return static_cast<int>(i->second->extras.size());
				}
				case InteriorId:
				{
					int size = static_cast<int>(i->second->interiors.size());
					return size ? size : -1;
				}
				case PlayerId:
				{
					return static_cast<int>(i->second->players.count());
				}
				case WorldId:
				{
					int size = static_cast<int>(i->second->worlds.size());
					return size ? size : -1;
				}
				default:
				{
					if (data & 0x40000000)
					{
						boost::unordered_map<int, std::vector<int>>::iterator p = i->second->extraExtras.find(data & ~0xC0000000);
						if (p != i->second->extraExtras.end())
						{
							int size = static_cast<int>(p->second.size());
							return size ? size : -1;
						}
					}
					error = InvalidData;
					break;
				}
			}
		}
		else
		{
			error = InvalidId;
		}
		return 0;
	}
}

#endif
