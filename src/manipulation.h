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

#ifndef MANIPULATION_H
#define MANIPULATION_H

#include "main.h"
#include "utility.h"

namespace Manipulation
{
	enum
	{
		AttachedObject,
		AttachedPlayer,
		AttachedVehicle,
		AttachOffsetX,
		AttachOffsetY,
		AttachOffsetZ,
		AttachRX,
		AttachRY,
		AttachRZ,
		AttachX,
		AttachY,
		AttachZ,
		Color,
		DrawDistance,
		ExtraID,
		InteriorID,
		MaxX,
		MaxY,
		MaxZ,
		MinX,
		MinY,
		MinZ,
		ModelID,
		MoveRX,
		MoveRY,
		MoveRZ,
		MoveSpeed,
		MoveX,
		MoveY,
		MoveZ,
		NextX,
		NextY,
		NextZ,
		PlayerID,
		RX,
		RY,
		RZ,
		Size,
		StreamDistance,
		Style,
		SyncRotation,
		TestLOS,
		Type,
		WorldID,
		X,
		Y,
		Z
	};

	enum
	{
		InvalidData,
		InvalidID,
		InvalidType
	};

	int getFloatData(AMX *amx, cell *params);
	int setFloatData(AMX *amx, cell *params);
	int getIntData(AMX *amx, cell *params);
	int setIntData(AMX *amx, cell *params);
	int getArrayData(AMX *amx, cell *params);
	int setArrayData(AMX *amx, cell *params);
	int isInArrayData(AMX *amx, cell *params);
	int appendArrayData(AMX *amx, cell *params);
	int removeArrayData(AMX *amx, cell *params);

	template <typename T>
	int getArrayDataForItem(T &container, AMX *amx, int id, int type, cell output, cell size, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
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
	int setArrayDataForItem(T &container, AMX *amx, int id, int type, cell input, cell size, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
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
	int isInArrayDataForItem(T &container, int id, int type, int value, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
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
	int appendArrayDataForItem(T &container, int id, int type, int value, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
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
	int removeArrayDataForItem(T &container, int id, int type, int value, int &error)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
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
}

#endif
