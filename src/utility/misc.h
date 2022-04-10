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

#ifndef UTILITY_MISC_H
#define UTILITY_MISC_H

#include "../item.h"

namespace Utility
{
	std::unordered_map<int, Item::SharedActor>::iterator destroyActor(std::unordered_map<int, Item::SharedActor>::iterator a);
	std::unordered_map<int, Item::SharedArea>::iterator destroyArea(std::unordered_map<int, Item::SharedArea>::iterator a);
	std::unordered_map<int, Item::SharedCheckpoint>::iterator destroyCheckpoint(std::unordered_map<int, Item::SharedCheckpoint>::iterator c);
	std::unordered_map<int, Item::SharedMapIcon>::iterator destroyMapIcon(std::unordered_map<int, Item::SharedMapIcon>::iterator m);
	std::unordered_map<int, Item::SharedObject>::iterator destroyObject(std::unordered_map<int, Item::SharedObject>::iterator o);
	std::unordered_map<int, Item::SharedPickup>::iterator destroyPickup(std::unordered_map<int, Item::SharedPickup>::iterator p);
	std::unordered_map<int, Item::SharedRaceCheckpoint>::iterator destroyRaceCheckpoint(std::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r);
	std::unordered_map<int, Item::SharedTextLabel>::iterator destroyTextLabel(std::unordered_map<int, Item::SharedTextLabel>::iterator t);

	std::size_t getChunkTickRate(int type, int playerid);
	bool setChunkTickRate(int type, std::size_t value, int playerid);

	std::size_t getMaxVisibleItems(int type, int playerid);
	bool setMaxVisibleItems(int type, std::size_t value, int playerid);

	float getRadiusMultiplier(int type, int playerid);
	bool setRadiusMultiplier(int type, float value, int playerid);

	void processPendingDestroyedActors();

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
	inline bool addToContainer(std::unordered_set<T> &container, T value)
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
		if (value < 0)
		{
			container.set();
		}
		else if (static_cast<std::size_t>(value) >= N)
		{
			container.reset();
		}
		else
		{
			container.set(static_cast<std::size_t>(value));
			return true;
		}
		return false;
	}

	template<typename T>
	inline int getFirstValueInContainer(const std::vector<T> &container)
	{
		if (!container.empty())
		{
			return container.front();
		}
		return 0;
	}

	template<typename T>
	inline int getFirstValueInContainer(const std::unordered_set<T> &container)
	{
		std::unordered_set<int>::iterator i = container.begin();
		if (i != container.end())
		{
			return *i;
		}
		return -1;
	}

	template<std::size_t N>
	inline int getFirstValueInContainer(const std::bitset<N> &container)
	{
		if (container.any())
		{
			if (container.all())
			{
				return -1;
			}
			for (std::size_t i = 0; i < N; ++i)
			{
				if (container.test(i))
				{
					return i;
				}
			}
		}
		return INVALID_PLAYER_ID;
	}

	template<typename T>
	inline bool setFirstValueInContainer(std::vector<T> &container, T value)
	{
		container.clear();
		return addToContainer(container, value);
	}

	template<typename T>
	inline bool setFirstValueInContainer(std::unordered_set<T> &container, T value)
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
	inline bool isInContainer(const std::vector<T> &container, const T value)
	{
		if (std::find(container.begin(), container.end(), value) != container.end())
		{
			return true;
		}
		return false;
	}

	template<typename T>
	inline bool isInContainer(const std::unordered_set<T> &container, const T value)
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
	inline bool isInContainer(const std::bitset<N> &container, const T value)
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
	inline bool isContainerWithinContainer(const std::unordered_set<T> &mainContainer, const std::unordered_set<T> &overlappingContainer)
	{
		for (typename std::unordered_set<T>::const_iterator o = overlappingContainer.begin(); o != overlappingContainer.end(); ++o)
		{
			if (mainContainer.find(*o) != mainContainer.end())
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
	inline bool removeFromContainer(std::unordered_set<T> &container, T value)
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
}

#endif
