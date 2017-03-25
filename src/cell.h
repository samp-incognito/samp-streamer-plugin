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

#ifndef CELL_H
#define CELL_H

#include "common.h"
#include "item.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/unordered_map.hpp>

class Cell
{
public:
	Cell();
	Cell(CellID cellID);

	CellID cellID;
	int references;

	boost::unordered_map<int, Item::SharedArea> areas;
	boost::unordered_map<int, Item::SharedCheckpoint> checkpoints;
	boost::unordered_map<int, Item::SharedMapIcon> mapIcons;
	boost::unordered_map<int, Item::SharedObject> objects;
	boost::unordered_map<int, Item::SharedPickup> pickups;
	boost::unordered_map<int, Item::SharedRaceCheckpoint> raceCheckpoints;
	boost::unordered_map<int, Item::SharedTextLabel> textLabels;
	boost::unordered_map<int, Item::SharedActor> actors;
};

#endif
