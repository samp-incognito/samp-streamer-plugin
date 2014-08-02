/*
 * Copyright (C) 2014 Incognito
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

#include <sampgdk/sampgdk.h>

#include <set>

class Data
{
public:
	Data();

	std::size_t getMaxItems(int type);
	bool setMaxItems(int type, std::size_t value);

	std::set<AMX*> interfaces;

	boost::unordered_map<int, Item::SharedArea> areas;
	boost::unordered_map<int, Item::SharedCheckpoint> checkpoints;
	boost::unordered_map<int, Item::SharedMapIcon> mapIcons;
	boost::unordered_map<int, Item::SharedObject> objects;
	boost::unordered_map<int, Item::SharedPickup> pickups;
	boost::unordered_map<int, Item::SharedRaceCheckpoint> raceCheckpoints;
	boost::unordered_map<int, Item::SharedTextLabel> textLabels;
	boost::unordered_map<int, Item::SharedVehicle> vehicles;

	boost::unordered_map<int, Player> players;
private:
	std::size_t maxAreas;
	std::size_t maxCheckpoints;
	std::size_t maxMapIcons;
	std::size_t maxObjects;
	std::size_t maxPickups;
	std::size_t maxRaceCheckpoints;
	std::size_t maxTextLabels;
	std::size_t maxVehicles;
};

#endif
