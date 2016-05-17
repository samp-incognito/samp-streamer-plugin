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

#ifndef UTILITY_AMX_H
#define UTILITY_AMX_H

#include "misc.h"

#include "../common.h"
#include "../item.h"

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <algorithm>
#include <bitset>
#include <string>

#define MAX_BUFFER (1024)

namespace Utility
{
	cell AMX_NATIVE_CALL hookedNative(AMX *amx, cell *params);

	int checkInterfaceAndRegisterNatives(AMX *amx, AMX_NATIVE_INFO *amxNativeList);
	void destroyAllItemsInInterface(AMX *amx);
	void executeFinalAreaCallbacks(int areaid);
	void executeFinalAreaCallbacksForAllAreas(AMX *amx, bool ignoreInterface);
	void logError(const char *format, ...);

	template<typename T>
	bool convertArrayToContainer(AMX *amx, cell input, cell size, std::vector<T> &container)
	{
		cell *array = NULL;
		amx_GetAddr(amx, input, &array);
		container.clear();
		for (std::size_t i = 0; i < static_cast<std::size_t>(size); ++i)
		{
			if (!addToContainer(container, static_cast<T>(array[i])))
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	bool convertArrayToContainer(AMX *amx, cell input, cell size, boost::unordered_set<T> &container)
	{
		cell *array = NULL;
		amx_GetAddr(amx, input, &array);
		container.clear();
		for (std::size_t i = 0; i < static_cast<std::size_t>(size); ++i)
		{
			if (!addToContainer(container, static_cast<T>(array[i])))
			{
				return false;
			}
		}
		return true;
	}

	template<std::size_t N>
	bool convertArrayToContainer(AMX *amx, cell input, cell size, std::bitset<N> &container)
	{
		cell *array = NULL;
		amx_GetAddr(amx, input, &array);
		container.reset();
		for (std::size_t i = 0; i < static_cast<std::size_t>(size); ++i)
		{
			if (!addToContainer(container, static_cast<std::size_t>(array[i])))
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	bool convertContainerToArray(AMX *amx, cell output, cell size, const std::vector<T> &container)
	{
		cell *array = NULL;
		std::size_t i = 0;
		amx_GetAddr(amx, output, &array);
		for (typename std::vector<T>::const_iterator c = container.begin(); c != container.end(); ++c)
		{
			if (i == static_cast<std::size_t>(size))
			{
				return false;
			}
			array[i++] = static_cast<cell>(*c);
		}
		return true;
	}

	template<typename T>
	bool convertContainerToArray(AMX *amx, cell output, cell size, const boost::unordered_set<T> &container)
	{
		cell *array = NULL;
		std::size_t i = 0;
		amx_GetAddr(amx, output, &array);
		for (typename boost::unordered_set<T>::const_iterator c = container.begin(); c != container.end(); ++c)
		{
			if (i == static_cast<std::size_t>(size))
			{
				return false;
			}
			array[i++] = static_cast<cell>(*c);
		}
		return true;
	}

	template<std::size_t N>
	bool convertContainerToArray(AMX *amx, cell output, cell size, const std::bitset<N> &container)
	{
		cell *array = NULL;
		std::size_t i = 0;
		amx_GetAddr(amx, output, &array);
		for (std::size_t c = 0; c < N; ++c)
		{
			if (i == static_cast<std::size_t>(size))
			{
				return false;
			}
			if (container[c])
			{
				array[i++] = static_cast<cell>(c);
			}
		}
		return true;
	}

	void convertArrayToPolygon(AMX *amx, cell input, cell size, Polygon2D &polygon);
	bool convertPolygonToArray(AMX *amx, cell output, cell size, Polygon2D &polygon);
	std::string convertNativeStringToString(AMX *amx, cell input);
	void convertStringToNativeString(AMX *amx, cell output, cell size, std::string string);
	void storeFloatInNative(AMX *amx, cell output, float number);
	void storeIntegerInNative(AMX *amx, cell output, int number);
}

#endif
