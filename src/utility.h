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

#ifndef UTILITY_H
#define UTILITY_H

#include "common.h"
#include "item.h"

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <Eigen/Core>

#include <algorithm>
#include <bitset>
#include <string>

#define MAX_BUFFER (1024)

namespace Utility
{
	cell AMX_NATIVE_CALL hookedNative(AMX *amx, cell *params);

	int checkInterfaceAndRegisterNatives(AMX *amx, AMX_NATIVE_INFO *amxNativeList);
	void destroyAllItemsInInterface(AMX *amx);

	boost::unordered_map<int, Item::SharedArea>::iterator destroyArea(boost::unordered_map<int, Item::SharedArea>::iterator a);
	boost::unordered_map<int, Item::SharedCheckpoint>::iterator destroyCheckpoint(boost::unordered_map<int, Item::SharedCheckpoint>::iterator c);
	boost::unordered_map<int, Item::SharedMapIcon>::iterator destroyMapIcon(boost::unordered_map<int, Item::SharedMapIcon>::iterator m);
	boost::unordered_map<int, Item::SharedObject>::iterator destroyObject(boost::unordered_map<int, Item::SharedObject>::iterator o);
	boost::unordered_map<int, Item::SharedPickup>::iterator destroyPickup(boost::unordered_map<int, Item::SharedPickup>::iterator p);
	boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator destroyRaceCheckpoint(boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r);
	boost::unordered_map<int, Item::SharedTextLabel>::iterator destroyTextLabel(boost::unordered_map<int, Item::SharedTextLabel>::iterator t);

	void executeFinalAreaCallbacks(int areaid);
	void executeFinalAreaCallbacksForAllAreas(AMX *amx, bool ignoreInterface);

	void logError(const char *format, ...);

	bool isPointInArea(const Eigen::Vector3f &point, const Item::SharedArea &area);

	void projectPoint(const Eigen::Vector3f &point, const float &heading, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const Eigen::Vector3f &rotation, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const Eigen::Vector4f &quaternion, Eigen::Vector3f &position);

	std::size_t getGlobalMaxVisibleItems(int type, int playerid);
	bool setMaxVisibleItems(int type, std::size_t value, int playerid);

	float getRadiusMultiplier(int type, int playerid);
	bool setRadiusMultiplier(int type, float value, int playerid);

	template<typename T>
	inline bool almostEquals(T a, T b)
	{
		return std::fabs(a - b) < std::numeric_limits<T>::epsilon();
	}

	template<typename T>
	inline bool addToContainer(std::vector<T> &container, T value)
	{
		container.push_back(value);
		return true;
	}

	template<typename T>
	inline bool addToContainer(boost::unordered_set<T> &container, T value)
	{
		if (value >= 0)
		{
			container.insert(value);
			return true;
		}
		else
		{
			container.clear();
		}
		return false;
	}

	template<std::size_t N, typename T>
	inline bool addToContainer(std::bitset<N> &container, T value)
	{
		if (value >= 0 && static_cast<std::size_t>(value) < N)
		{
			container.set(static_cast<std::size_t>(value));
			return true;
		}
		else
		{
			container.set();
		}
		return false;
	}

	template<typename T>
	inline int getFirstValueInContainer(std::vector<T> &container)
	{
		if (!container.empty())
		{
			return container.front();
		}
		return 0;
	}

	template<typename T>
	inline int getFirstValueInContainer(boost::unordered_set<T> &container)
	{
		boost::unordered_set<int>::iterator i = container.begin();
		if (i != container.end())
		{
			return *i;
		}
		return -1;
	}

	template<std::size_t N>
	inline int getFirstValueInContainer(std::bitset<N> &container)
	{
		if (container.any())
		{
			for (std::size_t i = 0; i < N; ++i)
			{
				if (container.test(i))
				{
					return i;
				}
			}
		}
		return -1;
	}

	template<typename T>
	inline bool setFirstValueInContainer(std::vector<T> &container, T value)
	{
		container.clear();
		return addToContainer(container, value);
	}

	template<typename T>
	inline bool setFirstValueInContainer(boost::unordered_set<T> &container, T value)
	{
		container.clear();
		return addToContainer(container, value);
	}

	template<std::size_t N, typename T>
	inline bool setFirstValueInContainer(std::bitset<N> &container, T value)
	{
		container.reset();
		return addToContainer(container, value);
	}

	template<typename T>
	inline bool isInContainer(std::vector<T> &container, T value)
	{
		if (std::find(container.begin(), container.end(), value) != container.end())
		{
			return true;
		}
		return false;
	}

	template<typename T>
	inline bool isInContainer(boost::unordered_set<T> &container, T value)
	{
		if (value >= 0)
		{
			if (container.find(value) != container.end())
			{
				return true;
			}
		}
		else
		{
			if (container.empty())
			{
				return true;
			}
		}
		return false;
	}

	template<std::size_t N, typename T>
	inline bool isInContainer(std::bitset<N> &container, T value)
	{
		if (value >= 0 && static_cast<std::size_t>(value) < N)
		{
			if (container[static_cast<std::size_t>(value)])
			{
				return true;
			}
		}
		else
		{
			if (container.count() == N)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline bool removeFromContainer(std::vector<T> &container, T value)
	{
		typename std::vector<T>::iterator i = std::find(container.begin(), container.end(), value);
		if (i != container.end())
		{
			container.erase(i);
			return true;
		}
		return false;
	}

	template<typename T>
	inline bool removeFromContainer(boost::unordered_set<T> &container, T value)
	{
		if (value >= 0)
		{
			container.erase(value);
			return true;
		}
		else
		{
			container.clear();
		}
		return false;
	}

	template<std::size_t N, typename T>
	inline bool removeFromContainer(std::bitset<N> &container, T value)
	{
		if (value >= 0 && static_cast<std::size_t>(value) < N)
		{
			container.reset(static_cast<std::size_t>(value));
			return true;
		}
		else
		{
			container.reset();
		}
		return false;
	}

	template<typename T>
	inline bool convertArrayToContainer(AMX *amx, cell input, cell size, std::vector<T> &container)
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
	inline bool convertArrayToContainer(AMX *amx, cell input, cell size, boost::unordered_set<T> &container)
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
	inline bool convertArrayToContainer(AMX *amx, cell input, cell size, std::bitset<N> &container)
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
	inline bool convertContainerToArray(AMX *amx, cell output, cell size, std::vector<T> &container)
	{
		cell *array = NULL;
		std::size_t i = 0;
		amx_GetAddr(amx, output, &array);
		for (typename std::vector<T>::iterator c = container.begin(); c != container.end(); ++c)
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
	inline bool convertContainerToArray(AMX *amx, cell output, cell size, boost::unordered_set<T> &container)
	{
		cell *array = NULL;
		std::size_t i = 0;
		amx_GetAddr(amx, output, &array);
		for (typename boost::unordered_set<T>::iterator c = container.begin(); c != container.end(); ++c)
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
	inline bool convertContainerToArray(AMX *amx, cell output, cell size, std::bitset<N> &container)
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
