/*
 * Copyright (C) 2015 Incognito
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

#include "grid.h"

#include "core.h"
#include "main.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <cmath>
#include <vector>

Grid::Grid()
{
	cellDistance = 360000.0f;
	cellSize = 300.0f;
	globalCell = SharedCell(new Cell());
	calculateTranslationMatrix();
}

void Grid::addArea(const Item::SharedArea &area)
{
	if (area->size > cellDistance)
	{
		globalCell->areas.insert(std::make_pair(area->areaID, area));
		area->cell.reset();
	}
	else
	{
		Eigen::Vector2f position = Eigen::Vector2f::Zero();
		switch (area->type)
		{
			case STREAMER_AREA_TYPE_CIRCLE:
			case STREAMER_AREA_TYPE_CYLINDER:
			{
				if (area->attach)
				{
					position = Eigen::Vector2f(area->attach->position[0], area->attach->position[1]);
				}
				else
				{
					position = boost::get<Eigen::Vector2f>(area->position);
				}
				break;
			}
			case STREAMER_AREA_TYPE_SPHERE:
			{
				if (area->attach)
				{
					position = Eigen::Vector2f(area->attach->position[0], area->attach->position[1]);
				}
				else
				{
					position = Eigen::Vector2f(boost::get<Eigen::Vector3f>(area->position)[0], boost::get<Eigen::Vector3f>(area->position)[1]);
				}
				break;
			}
			case STREAMER_AREA_TYPE_RECTANGLE:
			{
				boost::geometry::centroid(boost::get<Box2D>(area->position), position);
				break;
			}
			case STREAMER_AREA_TYPE_CUBOID:
			{
				Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3D>(area->position));
				position = Eigen::Vector2f(centroid[0], centroid[1]);
				break;
			}
			case STREAMER_AREA_TYPE_POLYGON:
			{
				boost::geometry::centroid(boost::get<Polygon2D>(area->position), position);
				break;
			}
		}
		CellID cellID = getCellID(position);
		cells[cellID]->areas.insert(std::make_pair(area->areaID, area));
		area->cell = cells[cellID];
	}
}

void Grid::addCheckpoint(const Item::SharedCheckpoint &checkpoint)
{
	if (checkpoint->streamDistance > cellDistance || checkpoint->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
	{
		globalCell->checkpoints.insert(std::make_pair(checkpoint->checkpointID, checkpoint));
		checkpoint->cell.reset();
	}
	else
	{
		CellID cellID = getCellID(Eigen::Vector2f(checkpoint->position[0], checkpoint->position[1]));
		cells[cellID]->checkpoints.insert(std::make_pair(checkpoint->checkpointID, checkpoint));
		checkpoint->cell = cells[cellID];
	}
}

void Grid::addMapIcon(const Item::SharedMapIcon &mapIcon)
{
	if (mapIcon->streamDistance > cellDistance || mapIcon->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
	{
		globalCell->mapIcons.insert(std::make_pair(mapIcon->mapIconID, mapIcon));
		mapIcon->cell.reset();
	}
	else
	{
		CellID cellID = getCellID(Eigen::Vector2f(mapIcon->position[0], mapIcon->position[1]));
		cells[cellID]->mapIcons.insert(std::make_pair(mapIcon->mapIconID, mapIcon));
		mapIcon->cell = cells[cellID];
	}
}

void Grid::addObject(const Item::SharedObject &object)
{
	if (object->streamDistance > cellDistance || object->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
	{
		globalCell->objects.insert(std::make_pair(object->objectID, object));
		object->cell.reset();
	}
	else
	{
		Eigen::Vector2f position = Eigen::Vector2f::Zero();
		if (object->attach)
		{
			position = Eigen::Vector2f(object->attach->position[0], object->attach->position[1]);
		}
		else
		{
			position = Eigen::Vector2f(object->position[0], object->position[1]);
		}
		CellID cellID = getCellID(Eigen::Vector2f(position[0], position[1]));
		cells[cellID]->objects.insert(std::make_pair(object->objectID, object));
		object->cell = cells[cellID];
	}
}

void Grid::addPickup(const Item::SharedPickup &pickup)
{
	if (pickup->streamDistance > cellDistance || pickup->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
	{
		globalCell->pickups.insert(std::make_pair(pickup->pickupID, pickup));
		pickup->cell.reset();
	}
	else
	{
		CellID cellID = getCellID(Eigen::Vector2f(pickup->position[0], pickup->position[1]));
		cells[cellID]->pickups.insert(std::make_pair(pickup->pickupID, pickup));
		pickup->cell = cells[cellID];
	}
}

void Grid::addRaceCheckpoint(const Item::SharedRaceCheckpoint &raceCheckpoint)
{
	if (raceCheckpoint->streamDistance > cellDistance || raceCheckpoint->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
	{
		globalCell->raceCheckpoints.insert(std::make_pair(raceCheckpoint->raceCheckpointID, raceCheckpoint));
		raceCheckpoint->cell.reset();
	}
	else
	{
		CellID cellID = getCellID(Eigen::Vector2f(raceCheckpoint->position[0], raceCheckpoint->position[1]));
		cells[cellID]->raceCheckpoints.insert(std::make_pair(raceCheckpoint->raceCheckpointID, raceCheckpoint));
		raceCheckpoint->cell = cells[cellID];
	}
}

void Grid::addTextLabel(const Item::SharedTextLabel &textLabel)
{
	if (textLabel->streamDistance > cellDistance || textLabel->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
	{
		globalCell->textLabels.insert(std::make_pair(textLabel->textLabelID, textLabel));
		textLabel->cell.reset();
	}
	else
	{
		Eigen::Vector2f position = Eigen::Vector2f::Zero();
		if (textLabel->attach)
		{
			position = Eigen::Vector2f(textLabel->attach->position[0], textLabel->attach->position[1]);
		}
		else
		{
			position = Eigen::Vector2f(textLabel->position[0], textLabel->position[1]);;
		}
		CellID cellID = getCellID(position);
		cells[cellID]->textLabels.insert(std::make_pair(textLabel->textLabelID, textLabel));
		textLabel->cell = cells[cellID];
	}
}

void Grid::rebuildGrid()
{
	cells.clear();
	globalCell = SharedCell(new Cell());
	calculateTranslationMatrix();
	for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		addArea(a->second);
	}
	for (boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
	{
		addCheckpoint(c->second);
	}
	for (boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin(); m != core->getData()->mapIcons.end(); ++m)
	{
		addMapIcon(m->second);
	}
	for (boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.begin(); o != core->getData()->objects.end(); ++o)
	{
		addObject(o->second);
	}
	for (boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.begin(); p != core->getData()->pickups.end(); ++p)
	{
		addPickup(p->second);
	}
	for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
	{
		addRaceCheckpoint(r->second);
	}
	for (boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.begin(); t != core->getData()->textLabels.end(); ++t)
	{
		addTextLabel(t->second);
	}
}

void Grid::removeArea(const Item::SharedArea &area, bool reassign)
{
	bool found = false;
	if (area->cell)
	{
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(area->cell->cellID);
		if (c != cells.end())
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = c->second->areas.find(area->areaID);
			if (a != c->second->areas.end())
			{
				c->second->areas.quick_erase(a);
				eraseCellIfEmpty(c->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Item::SharedArea>::iterator a = globalCell->areas.find(area->areaID);
		if (a != globalCell->areas.end())
		{
			globalCell->areas.quick_erase(a);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addArea(area);
		}
		else
		{
			if (area->attach)
			{
				core->getStreamer()->attachedAreas.erase(area);
			}
		}
	}
}

void Grid::removeCheckpoint(const Item::SharedCheckpoint &checkpoint, bool reassign)
{
	bool found = false;
	if (checkpoint->cell)
	{
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(checkpoint->cell->cellID);
		if (c != cells.end())
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator d = c->second->checkpoints.find(checkpoint->checkpointID);
			if (d != c->second->checkpoints.end())
			{
				c->second->checkpoints.quick_erase(d);
				eraseCellIfEmpty(c->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = globalCell->checkpoints.find(checkpoint->checkpointID);
		if (c != globalCell->checkpoints.end())
		{
			globalCell->checkpoints.quick_erase(c);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addCheckpoint(checkpoint);
		}
	}
}

void Grid::removeMapIcon(const Item::SharedMapIcon &mapIcon, bool reassign)
{
	bool found = false;
	if (mapIcon->cell)
	{
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(mapIcon->cell->cellID);
		if (c != cells.end())
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = c->second->mapIcons.find(mapIcon->mapIconID);
			if (m != c->second->mapIcons.end())
			{
				c->second->mapIcons.quick_erase(m);
				eraseCellIfEmpty(c->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Item::SharedMapIcon>::iterator m = globalCell->mapIcons.find(mapIcon->mapIconID);
		if (m != globalCell->mapIcons.end())
		{
			globalCell->mapIcons.quick_erase(m);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addMapIcon(mapIcon);
		}
	}
}

void Grid::removeObject(const Item::SharedObject &object, bool reassign)
{
	bool found = false;
	if (object->cell)
	{
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(object->cell->cellID);
		if (c != cells.end())
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = c->second->objects.find(object->objectID);
			if (o != c->second->objects.end())
			{
				c->second->objects.quick_erase(o);
				eraseCellIfEmpty(c->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Item::SharedObject>::iterator o = globalCell->objects.find(object->objectID);
		if (o != globalCell->objects.end())
		{
			globalCell->objects.quick_erase(o);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addObject(object);
		}
		else
		{
			if (object->attach)
			{
				core->getStreamer()->attachedObjects.erase(object);
			}
			if (object->move)
			{
				core->getStreamer()->movingObjects.erase(object);
			}
		}
	}
}

void Grid::removePickup(const Item::SharedPickup &pickup, bool reassign)
{
	bool found = false;
	if (pickup->cell)
	{
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(pickup->cell->cellID);
		if (c != cells.end())
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = c->second->pickups.find(pickup->pickupID);
			if (p != c->second->pickups.end())
			{
				c->second->pickups.quick_erase(p);
				eraseCellIfEmpty(c->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Item::SharedPickup>::iterator p = globalCell->pickups.find(pickup->pickupID);
		if (p != globalCell->pickups.end())
		{
			globalCell->pickups.quick_erase(p);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addPickup(pickup);
		}
	}
}

void Grid::removeRaceCheckpoint(const Item::SharedRaceCheckpoint &raceCheckpoint, bool reassign)
{
	bool found = false;
	if (raceCheckpoint->cell)
	{
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(raceCheckpoint->cell->cellID);
		if (c != cells.end())
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = c->second->raceCheckpoints.find(raceCheckpoint->raceCheckpointID);
			if (r != c->second->raceCheckpoints.end())
			{
				c->second->raceCheckpoints.quick_erase(r);
				eraseCellIfEmpty(c->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = globalCell->raceCheckpoints.find(raceCheckpoint->raceCheckpointID);
		if (r != globalCell->raceCheckpoints.end())
		{
			globalCell->raceCheckpoints.quick_erase(r);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addRaceCheckpoint(raceCheckpoint);
		}
	}
}

void Grid::removeTextLabel(const Item::SharedTextLabel &textLabel, bool reassign)
{
	bool found = false;
	if (textLabel->cell)
	{
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(textLabel->cell->cellID);
		if (c != cells.end())
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = c->second->textLabels.find(textLabel->textLabelID);
			if (t != c->second->textLabels.end())
			{
				c->second->textLabels.quick_erase(t);
				eraseCellIfEmpty(c->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Item::SharedTextLabel>::iterator t = globalCell->textLabels.find(textLabel->textLabelID);
		if (t != globalCell->textLabels.end())
		{
			globalCell->textLabels.quick_erase(t);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addTextLabel(textLabel);
		}
		else
		{
			if (textLabel->attach)
			{
				core->getStreamer()->attachedTextLabels.erase(textLabel);
			}
		}
	}
}

CellID Grid::getCellID(const Eigen::Vector2f &position, bool insert)
{
	static Box2D box;
	box.min_corner()[0] = std::floor((position[0] / cellSize)) * cellSize;
	box.min_corner()[1] = std::floor((position[1] / cellSize)) * cellSize;
	box.max_corner()[0] = box.min_corner()[0] + cellSize;
	box.max_corner()[1] = box.min_corner()[1] + cellSize;
	Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(box);
	CellID cellID = std::make_pair(static_cast<int>(centroid[0]), static_cast<int>(centroid[1]));
	if (insert)
	{
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(cellID);
		if (c == cells.end())
		{
			SharedCell cell(new Cell(cellID));
			cells[cellID] = cell;
		}
	}
	return cellID;
}

void Grid::processDiscoveredCellsForPlayer(Player &player, std::vector<SharedCell> &playerCells, const boost::unordered_set<CellID> &discoveredCells)
{
	playerCells.push_back(SharedCell(new Cell()));;
	if (player.enabledItems[STREAMER_TYPE_OBJECT])
	{
		boost::unordered_map<int, Item::SharedObject>::iterator o = player.visibleCell->objects.begin();
		while (o != player.visibleCell->objects.end())
		{
			boost::unordered_set<CellID>::iterator d = discoveredCells.find(o->second->cell->cellID);
			if (d != discoveredCells.end())
			{
				o = player.visibleCell->objects.erase(o);
			}
			else
			{
				++o;
			}
		}
		playerCells.back()->objects.swap(player.visibleCell->objects);
	}
	if (player.enabledItems[STREAMER_TYPE_CP])
	{
		boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = player.visibleCell->checkpoints.begin();
		while (c != player.visibleCell->checkpoints.end())
		{
			boost::unordered_set<CellID>::iterator d = discoveredCells.find(c->second->cell->cellID);
			if (d != discoveredCells.end())
			{
				c = player.visibleCell->checkpoints.erase(c);
			}
			else
			{
				++c;
			}
		}
		playerCells.back()->checkpoints.swap(player.visibleCell->checkpoints);
	}
	if (player.enabledItems[STREAMER_TYPE_RACE_CP])
	{
		boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator t = player.visibleCell->raceCheckpoints.begin();
		while (t != player.visibleCell->raceCheckpoints.end())
		{
			boost::unordered_set<CellID>::iterator d = discoveredCells.find(t->second->cell->cellID);
			if (d != discoveredCells.end())
			{
				t = player.visibleCell->raceCheckpoints.erase(t);
			}
			else
			{
				++t;
			}
		}
		playerCells.back()->raceCheckpoints.swap(player.visibleCell->raceCheckpoints);
	}
	if (player.enabledItems[STREAMER_TYPE_MAP_ICON])
	{
		boost::unordered_map<int, Item::SharedMapIcon>::iterator m = player.visibleCell->mapIcons.begin();
		while (m != player.visibleCell->mapIcons.end())
		{
			boost::unordered_set<CellID>::iterator d = discoveredCells.find(m->second->cell->cellID);
			if (d != discoveredCells.end())
			{
				m = player.visibleCell->mapIcons.erase(m);
			}
			else
			{
				++m;
			}
		}
		playerCells.back()->mapIcons.swap(player.visibleCell->mapIcons);
	}
	if (player.enabledItems[STREAMER_TYPE_3D_TEXT_LABEL])
	{
		boost::unordered_map<int, Item::SharedTextLabel>::iterator t = player.visibleCell->textLabels.begin();
		while (t != player.visibleCell->textLabels.end())
		{
			boost::unordered_set<CellID>::iterator d = discoveredCells.find(t->second->cell->cellID);
			if (d != discoveredCells.end())
			{
				t = player.visibleCell->textLabels.erase(t);
			}
			else
			{
				++t;
			}
		}
		playerCells.back()->textLabels.swap(player.visibleCell->textLabels);
	}
	if (player.enabledItems[STREAMER_TYPE_AREA])
	{
		boost::unordered_map<int, Item::SharedArea>::iterator a = player.visibleCell->areas.begin();
		while (a != player.visibleCell->areas.end())
		{
			boost::unordered_set<CellID>::iterator d = discoveredCells.find(a->second->cell->cellID);
			if (d != discoveredCells.end())
			{
				a = player.visibleCell->areas.erase(a);
			}
			else
			{
				++a;
			}
		}
		playerCells.back()->areas.swap(player.visibleCell->areas);
	}
}

void Grid::findAllCellsForPlayer(Player &player, std::vector<SharedCell> &playerCells)
{
	boost::unordered_set<CellID> discoveredCells;
	for (int i = 0; i < translationMatrix.cols(); ++i)
	{
		Eigen::Vector2f position = Eigen::Vector2f(player.position[0], player.position[1]) + translationMatrix.col(i);
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(getCellID(position, false));
		if (c != cells.end())
		{
			discoveredCells.insert(c->first);
			playerCells.push_back(c->second);
		}
	}
	processDiscoveredCellsForPlayer(player, playerCells, discoveredCells);
	playerCells.push_back(globalCell);
}

void Grid::findMinimalCellsForPlayer(Player &player, std::vector<SharedCell> &playerCells)
{
	for (int i = 0; i < translationMatrix.cols(); ++i)
	{
		Eigen::Vector2f position = Eigen::Vector2f(player.position[0], player.position[1]) + translationMatrix.col(i);
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(getCellID(position, false));
		if (c != cells.end())
		{
			playerCells.push_back(c->second);
		}
	}
	playerCells.push_back(globalCell);
}

void Grid::findMinimalCellsForPoint(Eigen::Vector2f &point, std::vector<SharedCell> &pointCells)
{
	for (int i = 0; i < translationMatrix.cols(); ++i)
	{
		Eigen::Vector2f position = Eigen::Vector2f(point[0], point[1]) + translationMatrix.col(i);
		boost::unordered_map<CellID, SharedCell>::iterator c = cells.find(getCellID(position, false));
		if (c != cells.end())
		{
			pointCells.push_back(c->second);
		}
	}
	pointCells.push_back(globalCell);
}
