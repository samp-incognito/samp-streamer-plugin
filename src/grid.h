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

#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "common.h"

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <cmath>
#include <vector>

class Grid
{
public:
	Grid();

	void addArea(const Item::SharedArea &area);
	void addCheckpoint(const Item::SharedCheckpoint &checkpoint);
	void addMapIcon(const Item::SharedMapIcon &mapIcon);
	void addObject(const Item::SharedObject &object);
	void addPickup(const Item::SharedPickup &pickup);
	void addRaceCheckpoint(const Item::SharedRaceCheckpoint &raceCheckpoint);
	void addTextLabel(const Item::SharedTextLabel &textLabel);
	void addVehicle(const Item::SharedVehicle &vehicle);

	inline float getCellSize()
	{
		return cellSize;
	}

	inline float getCellDistance()
	{
		return sqrt(cellDistance);
	}

	inline void setCellSize(float size)
	{
		cellSize = size;
	}

	inline void setCellDistance(float distance)
	{
		cellDistance = distance * distance;
	}

	void rebuildGrid();

	void removeArea(const Item::SharedArea &area, bool reassign = false);
	void removeCheckpoint(const Item::SharedCheckpoint &checkpoint, bool reassign = false);
	void removeMapIcon(const Item::SharedMapIcon &mapIcon, bool reassign = false);
	void removeObject(const Item::SharedObject &object, bool reassign = false);
	void removePickup(const Item::SharedPickup &pickup, bool reassign = false);
	void removeRaceCheckpoint(const Item::SharedRaceCheckpoint &raceCheckpoint, bool reassign = false);
	void removeTextLabel(const Item::SharedTextLabel &textLabel, bool reassign = false);
	void removeVehicle(const Item::SharedVehicle &vehicle, bool reassign = false);

	void findAllCells(Player &player, std::vector<SharedCell> &playerCells);
	void findMinimalCells(Player &player, std::vector<SharedCell> &playerCells);
private:
	float cellDistance;
	float cellSize;
	SharedCell globalCell;
	Eigen::Matrix<float, 2, 9> translationMatrix;

	boost::unordered_map<CellID, SharedCell> cells;

	inline void calculateTranslationMatrix()
	{
		translationMatrix << 0.0f, 0.0f, cellSize, cellSize, cellSize * -1.0f, 0.0f, cellSize * -1.0f, cellSize, cellSize * -1.0f,
		                     0.0f, cellSize, 0.0f, cellSize, 0.0f, cellSize * -1.0f, cellSize, cellSize * -1.0f, cellSize * -1.0f;
	}

	inline void eraseCellIfEmpty(const SharedCell &cell)
	{
		if (cell->areas.empty() && cell->checkpoints.empty() && cell->mapIcons.empty() && cell->objects.empty() && cell->pickups.empty() && cell->raceCheckpoints.empty() && cell->textLabels.empty())
		{
			cells.erase(cell->cellID);
		}
	}

	CellID getCellID(const Eigen::Vector2f &position, bool insert = true);
	void processDiscoveredCells(Player &player, std::vector<SharedCell> &playerCells, const boost::unordered_set<CellID> &discoveredCells);
};

#endif
