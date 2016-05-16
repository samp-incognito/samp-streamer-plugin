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

#ifndef UTILITY_MISC_H
#define UTILITY_MISC_H

#include "../common.h"
#include "../item.h"

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <Eigen/Core>

namespace Utility
{
	boost::unordered_map<int, Item::SharedArea>::iterator destroyArea(boost::unordered_map<int, Item::SharedArea>::iterator a);
	boost::unordered_map<int, Item::SharedCheckpoint>::iterator destroyCheckpoint(boost::unordered_map<int, Item::SharedCheckpoint>::iterator c);
	boost::unordered_map<int, Item::SharedMapIcon>::iterator destroyMapIcon(boost::unordered_map<int, Item::SharedMapIcon>::iterator m);
	boost::unordered_map<int, Item::SharedObject>::iterator destroyObject(boost::unordered_map<int, Item::SharedObject>::iterator o);
	boost::unordered_map<int, Item::SharedPickup>::iterator destroyPickup(boost::unordered_map<int, Item::SharedPickup>::iterator p);
	boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator destroyRaceCheckpoint(boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r);
	boost::unordered_map<int, Item::SharedTextLabel>::iterator destroyTextLabel(boost::unordered_map<int, Item::SharedTextLabel>::iterator t);

	std::size_t getMaxVisibleItems(int type, int playerid);
	bool setMaxVisibleItems(int type, std::size_t value, int playerid);

	float getRadiusMultiplier(int type, int playerid);
	bool setRadiusMultiplier(int type, float value, int playerid);

	template<typename T>
	inline bool almostEquals(T a, T b)
	{
		return std::fabs(a - b) < std::numeric_limits<T>::epsilon();
	}
}

#endif
