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

#ifndef DATA_H
#define DATA_H

#include "common.h"
#include "player.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <set>

class Data
{
public:
	Data();

	std::size_t getGlobalMaxItems(int type);
	bool setGlobalMaxItems(int type, std::size_t value);

	std::size_t getGlobalMaxVisibleItems(int type);
	bool setGlobalMaxVisibleItems(int type, std::size_t value);

	float getGlobalRadiusMultiplier(int type);
	bool setGlobalRadiusMultiplier(int type, float value);

	bool errorCallbackEnabled;

	std::set<AMX*> interfaces;

	boost::unordered_map<int, int> internalPickups;

	boost::unordered_map<int, Item::SharedArea> areas;
	boost::unordered_map<int, Item::SharedCheckpoint> checkpoints;
	boost::unordered_map<int, Item::SharedMapIcon> mapIcons;
	boost::unordered_map<int, Item::SharedObject> objects;
	boost::unordered_map<int, Item::SharedPickup> pickups;
	boost::unordered_map<int, Item::SharedRaceCheckpoint> raceCheckpoints;
	boost::unordered_map<int, Item::SharedTextLabel> textLabels;

	boost::unordered_map<int, Player> players;
private:
	std::size_t globalMaxItems[STREAMER_MAX_TYPES];
	std::size_t globalMaxVisibleItems[STREAMER_MAX_TYPES];
	float globalRadiusMultipliers[STREAMER_MAX_TYPES];
};

#endif
