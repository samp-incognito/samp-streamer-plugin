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

#include "../main.h"

#include "../natives.h"
#include "../core.h"
#include "../utility.h"

cell AMX_NATIVE_CALL Natives::CreateDynamicCircle(AMX *amx, cell *params)
{
	CHECK_PARAMS(7);
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return INVALID_STREAMER_ID;
	}
	int areaId = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaId = areaId;
	area->type = STREAMER_AREA_TYPE_CIRCLE;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->comparableSize = amx_ctof(params[3]) * amx_ctof(params[3]);
	area->size = amx_ctof(params[3]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[4]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[5]));
	Utility::addToContainer(area->players, static_cast<int>(params[6]));
	area->priority = static_cast<int>(params[7]);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaId, area));
	return static_cast<cell>(areaId);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCylinder(AMX *amx, cell *params)
{
	CHECK_PARAMS(9);
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return INVALID_STREAMER_ID;
	}
	int areaId = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaId = areaId;
	area->type = STREAMER_AREA_TYPE_CYLINDER;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->height = Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4]));
	area->comparableSize = amx_ctof(params[5]) * amx_ctof(params[5]);
	area->size = amx_ctof(params[5]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[6]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[7]));
	Utility::addToContainer(area->players, static_cast<int>(params[8]));
	area->priority = static_cast<int>(params[9]);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaId, area));
	return static_cast<cell>(areaId);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicSphere(AMX *amx, cell *params)
{
	CHECK_PARAMS(8);
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return INVALID_STREAMER_ID;
	}
	int areaId = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaId = areaId;
	area->spectateMode = true;
	area->type = STREAMER_AREA_TYPE_SPHERE;
	area->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	area->comparableSize = amx_ctof(params[4]) * amx_ctof(params[4]);
	area->size = amx_ctof(params[4]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	area->priority = static_cast<int>(params[8]);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaId, area));
	return static_cast<cell>(areaId);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRectangle(AMX *amx, cell *params)
{
	CHECK_PARAMS(8);
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return INVALID_STREAMER_ID;
	}
	int areaId = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaId = areaId;
	area->spectateMode = true;
	area->type = STREAMER_AREA_TYPE_RECTANGLE;
	area->position = Box2d(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4])));
	boost::geometry::correct(std::get<Box2d>(area->position));
	area->comparableSize = static_cast<float>(boost::geometry::comparable_distance(std::get<Box2d>(area->position).min_corner(), std::get<Box2d>(area->position).max_corner()));
	area->size = static_cast<float>(boost::geometry::distance(std::get<Box2d>(area->position).min_corner(), std::get<Box2d>(area->position).max_corner()));
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	area->priority = static_cast<int>(params[8]);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaId, area));
	return static_cast<cell>(areaId);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCuboid(AMX *amx, cell *params)
{
	CHECK_PARAMS(10);
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return INVALID_STREAMER_ID;
	}
	int areaId = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaId = areaId;
	area->spectateMode = true;
	area->type = STREAMER_AREA_TYPE_CUBOID;
	area->position = Box3d(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
	boost::geometry::correct(std::get<Box3d>(area->position));
	area->comparableSize = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(std::get<Box3d>(area->position).min_corner()[0], std::get<Box3d>(area->position).min_corner()[1]), Eigen::Vector2f(std::get<Box3d>(area->position).max_corner()[0], std::get<Box3d>(area->position).max_corner()[1])));
	area->size = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(std::get<Box3d>(area->position).min_corner()[0], std::get<Box3d>(area->position).min_corner()[1]), Eigen::Vector2f(std::get<Box3d>(area->position).max_corner()[0], std::get<Box3d>(area->position).max_corner()[1])));
	Utility::addToContainer(area->worlds, static_cast<int>(params[7]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[8]));
	Utility::addToContainer(area->players, static_cast<int>(params[9]));
	area->priority = static_cast<int>(params[10]);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaId, area));
	return static_cast<cell>(areaId);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPolygon(AMX *amx, cell *params)
{
	CHECK_PARAMS(8);
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return INVALID_STREAMER_ID;
	}
	if (static_cast<int>(params[4]) < 6 || static_cast<int>(params[4]) % 2)
	{
		Utility::logError("CreateDynamicPolygon: Number of points must be divisible by 2 and bigger or equal to 6.");
		return INVALID_STREAMER_ID;
	}
	int areaId = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaId = areaId;
	area->spectateMode = true;
	area->type = STREAMER_AREA_TYPE_POLYGON;
	Utility::convertArrayToPolygon(amx, params[1], params[4], std::get<Polygon2d>(area->position));
	area->height = Eigen::Vector2f(amx_ctof(params[2]), amx_ctof(params[3]));
	Box2d box = boost::geometry::return_envelope<Box2d>(std::get<Polygon2d>(area->position));
	area->comparableSize = static_cast<float>(boost::geometry::comparable_distance(box.min_corner(), box.max_corner()));
	area->size = static_cast<float>(boost::geometry::distance(box.min_corner(), box.max_corner()));
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	area->priority = static_cast<int>(params[8]);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaId, area));
	return static_cast<cell>(areaId);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);
	Utility::executeFinalAreaCallbacks(static_cast<int>(params[1]));
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		Utility::destroyArea(a);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicAreaType(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return a->second->type;
	}
	return -1;
}

cell AMX_NATIVE_CALL Natives::GetDynamicPolygonPoints(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		Utility::convertPolygonToArray(amx, params[2], params[3], std::get<Polygon2d>(a->second->position));
		return static_cast<cell>(std::get<Polygon2d>(a->second->position).outer().size());
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicPolygonNumberPoints(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return static_cast<cell>(std::get<Polygon2d>(a->second->position).outer().size());
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		bool recheck = static_cast<int>(params[3]) != 0;
		if (!recheck)
		{
			std::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[2]));
			if (i != p->second.internalAreas.end())
			{
				return 1;
			}
		}
		else
		{
			std::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{

				return static_cast<cell>(core->getStreamer()->processPlayerArea(p->second, a->second, ompgdk::GetPlayerState(p->second.playerId)) != 0);
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		bool recheck = static_cast<int>(params[2]) != 0;
		if (!recheck)
		{
			if (!p->second.internalAreas.empty())
			{
				return 1;
			}
		}
		else
		{
			int state = ompgdk::GetPlayerState(p->second.playerId);
			for (std::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				if (core->getStreamer()->processPlayerArea(p->second, a->second, state) != 0)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsAnyPlayerInDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(2);
	bool recheck = static_cast<int>(params[2]) != 0;
	if (!recheck)
	{
		for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			std::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[1]));
			if (i != p->second.internalAreas.end())
			{
				return 1;
			}
		}
	}
	else
	{
		std::unordered_map<int, Item::SharedArea>::const_iterator a;
		for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			a = core->getData()->areas.find(static_cast<int>(params[1]));
			if (a != core->getData()->areas.end())
			{
				return static_cast<cell>(core->getStreamer()->processPlayerArea(p->second, a->second, ompgdk::GetPlayerState(p->second.playerId)) != 0);
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsAnyPlayerInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);
	bool recheck = static_cast<int>(params[1]) != 0;
	if (!recheck)
	{
		for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			if (!p->second.internalAreas.empty())
			{
				return 1;
			}
		}
	}
	else
	{
		std::unordered_map<int, Item::SharedArea>::const_iterator a;
		for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			for (a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				if (core->getStreamer()->processPlayerArea(p->second, a->second, ompgdk::GetPlayerState(p->second.playerId)) != 0)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPointInDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(4);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return Utility::isPointInArea(Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4])), a->second);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPointInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	for (std::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		if (Utility::isPointInArea(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), a->second))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsLineInDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(7);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return Utility::doesLineSegmentIntersectArea(Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4])), Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7])), a->second);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsLineInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(6);
	for (std::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		if (Utility::doesLineSegmentIntersectArea(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])), a->second))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerDynamicAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		std::multimap<float, int> orderedAreas;
		for (std::unordered_set<int>::iterator i = p->second.internalAreas.begin(); i != p->second.internalAreas.end(); ++i)
		{
			std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(*i);
			if (a != core->getData()->areas.end())
			{
				std::variant<Polygon2d, Box2d, Box3d, Eigen::Vector2f, Eigen::Vector3f> position;
				if (a->second->attach)
				{
					position = a->second->position;
				}
				else
				{
					position = a->second->position;
				}
				float distance = 0.0f;
				switch (a->second->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					case STREAMER_AREA_TYPE_CYLINDER:
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(p->second.position[0], p->second.position[1]), std::get<Eigen::Vector2f>(position)));
						break;
					}
					case STREAMER_AREA_TYPE_SPHERE:
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, std::get<Eigen::Vector3f>(position)));
						break;
					}
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(std::get<Box2d>(position));
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(p->second.position[0], p->second.position[1]), centroid));
						break;
					}
					case STREAMER_AREA_TYPE_CUBOID:
					{
						Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(std::get<Box3d>(position));
						distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, centroid));
						break;
					
					}
					case STREAMER_AREA_TYPE_POLYGON:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(std::get<Polygon2d>(position));
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(p->second.position[0], p->second.position[1]), centroid));
						break;
					}
				}
				orderedAreas.insert(std::pair<float, int>(distance, a->first));
			}
		}
		std::vector<int> finalAreas;
		for (std::map<float, int>::iterator i = orderedAreas.begin(); i != orderedAreas.end(); ++i)
		{
			finalAreas.push_back(i->second);
		}
		Utility::convertContainerToArray(amx, params[2], params[3], finalAreas);
		return static_cast<cell>(finalAreas.size());
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerNumberDynamicAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return static_cast<cell>(p->second.internalAreas.size());
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicAreasForPoint(AMX *amx, cell *params)
{
	CHECK_PARAMS(5);
	std::multimap<float, int> orderedAreas;
	std::vector<SharedCell> pointCells;
	core->getGrid()->findMinimalCellsForPoint(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), pointCells);
	for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
	{
		for (std::unordered_map<int, Item::SharedArea>::const_iterator a = (*p)->areas.begin(); a != (*p)->areas.end(); ++a)
		{
			if (Utility::isPointInArea(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), a->second))
			{
				std::variant<Polygon2d, Box2d, Box3d, Eigen::Vector2f, Eigen::Vector3f> position;
				if (a->second->attach)
				{
					position = a->second->position;
				}
				else
				{
					position = a->second->position;
				}
				float distance = 0.0f;
				switch (a->second->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					case STREAMER_AREA_TYPE_CYLINDER:
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), std::get<Eigen::Vector2f>(position)));
						break;
					}
					case STREAMER_AREA_TYPE_SPHERE:
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), std::get<Eigen::Vector3f>(position)));
						break;
					}
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(std::get<Box2d>(position));
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
						break;
					}
					case STREAMER_AREA_TYPE_CUBOID:
					{
						Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(std::get<Box3d>(position));
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), centroid));
						break;

					}
					case STREAMER_AREA_TYPE_POLYGON:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(std::get<Polygon2d>(position));
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
						break;
					}
				}
				orderedAreas.insert(std::pair<float, int>(distance, a->first));
			}
		}
	}
	std::vector<int> finalAreas;
	for (std::map<float, int>::iterator i = orderedAreas.begin(); i != orderedAreas.end(); ++i)
	{
		finalAreas.push_back(i->second);
	}
	Utility::convertContainerToArray(amx, params[4], params[5], finalAreas);
	return static_cast<cell>(finalAreas.size());
}

cell AMX_NATIVE_CALL Natives::GetNumberDynamicAreasForPoint(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);
	int areaCount = 0;
	std::vector<SharedCell> pointCells;
	core->getGrid()->findMinimalCellsForPoint(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), pointCells);
	for (std::vector<SharedCell>::const_iterator p = pointCells.begin(); p != pointCells.end(); ++p)
	{
		for (std::unordered_map<int, Item::SharedArea>::const_iterator a = (*p)->areas.begin(); a != (*p)->areas.end(); ++a)
		{
			if (Utility::isPointInArea(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), a->second))
			{
				++areaCount;
			}
		}
	}
	return static_cast<cell>(areaCount);
}

cell AMX_NATIVE_CALL Natives::GetDynamicAreasForLine(AMX *amx, cell *params)
{
	CHECK_PARAMS(8);
	std::multimap<float, int> orderedAreas;
	for (std::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		if (Utility::doesLineSegmentIntersectArea(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])), a->second))
		{
			std::variant<Polygon2d, Box2d, Box3d, Eigen::Vector2f, Eigen::Vector3f> position;
			if (a->second->attach)
			{
				position = a->second->position;
			}
			else
			{
				position = a->second->position;
			}
			float distance = 0.0f;
			switch (a->second->type)
			{
				case STREAMER_AREA_TYPE_CIRCLE:
				case STREAMER_AREA_TYPE_CYLINDER:
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), std::get<Eigen::Vector2f>(position)));
					break;
				}
				case STREAMER_AREA_TYPE_SPHERE:
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), std::get<Eigen::Vector3f>(position)));
					break;
				}
				case STREAMER_AREA_TYPE_RECTANGLE:
				{
					Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(std::get<Box2d>(position));
					distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
					break;
				}
				case STREAMER_AREA_TYPE_CUBOID:
				{
					Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(std::get<Box3d>(position));
					distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), centroid));
					break;

				}
				case STREAMER_AREA_TYPE_POLYGON:
				{
					Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(std::get<Polygon2d>(position));
					distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
					break;
				}
			}
			orderedAreas.insert(std::pair<float, int>(distance, a->first));
		}
	}
	std::vector<int> finalAreas;
	for (std::map<float, int>::iterator i = orderedAreas.begin(); i != orderedAreas.end(); ++i)
	{
		finalAreas.push_back(i->second);
	}
	Utility::convertContainerToArray(amx, params[7], params[8], finalAreas);
	return static_cast<cell>(finalAreas.size());
}

cell AMX_NATIVE_CALL Natives::GetNumberDynamicAreasForLine(AMX *amx, cell *params)
{
	CHECK_PARAMS(6);
	int areaCount = 0;
	for (std::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		if (Utility::doesLineSegmentIntersectArea(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])), a->second))
		{
			++areaCount;
		}
	}
	return static_cast<cell>(areaCount);
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(7);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if ((static_cast<int>(params[2]) != INVALID_OBJECT_ID && static_cast<int>(params[3]) != STREAMER_OBJECT_TYPE_DYNAMIC) || (static_cast<int>(params[2]) != INVALID_STREAMER_ID && static_cast<int>(params[3]) == STREAMER_OBJECT_TYPE_DYNAMIC))
		{
			a->second->attach = std::make_shared<Item::Area::Attach>();
			a->second->attach->player = INVALID_PLAYER_ID;
			a->second->attach->vehicle = INVALID_VEHICLE_ID;
			a->second->attach->position = a->second->position;
			a->second->attach->object = std::make_tuple(static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
			a->second->attach->positionOffset = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if ((std::get<0>(a->second->attach->object) != INVALID_OBJECT_ID && std::get<1>(a->second->attach->object) != STREAMER_OBJECT_TYPE_DYNAMIC) || (std::get<0>(a->second->attach->object) != INVALID_STREAMER_ID && std::get<1>(a->second->attach->object) == STREAMER_OBJECT_TYPE_DYNAMIC))
				{
					a->second->attach.reset();
					core->getStreamer()->attachedAreas.erase(a->second);
					core->getGrid()->removeArea(a->second, true);
				}
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToPlayer(AMX *amx, cell *params)
{
	CHECK_PARAMS(5);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (static_cast<int>(params[2]) != INVALID_PLAYER_ID)
		{
			a->second->attach = std::make_shared<Item::Area::Attach>();
			a->second->attach->object = std::make_tuple(INVALID_STREAMER_ID, STREAMER_OBJECT_TYPE_DYNAMIC, INVALID_PLAYER_ID);
			a->second->attach->vehicle = INVALID_VEHICLE_ID;
			a->second->attach->position = a->second->position;
			a->second->attach->player = static_cast<int>(params[2]);
			a->second->attach->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if (a->second->attach->player != INVALID_PLAYER_ID)
				{
					a->second->attach.reset();
					core->getStreamer()->attachedAreas.erase(a->second);
					core->getGrid()->removeArea(a->second, true);
				}
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(5);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (static_cast<int>(params[2]) != INVALID_VEHICLE_ID)
		{
			a->second->attach = std::make_shared<Item::Area::Attach>();
			a->second->attach->object = std::make_tuple(INVALID_STREAMER_ID, STREAMER_OBJECT_TYPE_DYNAMIC, INVALID_PLAYER_ID);
			a->second->attach->player = INVALID_PLAYER_ID;
			a->second->attach->position = a->second->position;
			a->second->attach->vehicle = static_cast<int>(params[2]);
			a->second->attach->positionOffset = a->second->attach->positionOffset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if (a->second->attach->vehicle != INVALID_VEHICLE_ID)
				{
					a->second->attach.reset();
					core->getStreamer()->attachedAreas.erase(a->second);
					core->getGrid()->removeArea(a->second, true);
				}
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::ToggleDynAreaSpectateMode(AMX *amx, cell *params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		a->second->spectateMode = static_cast<int>(params[2]) != 0;
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsToggleDynAreaSpectateMode(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return static_cast<cell>(a->second->spectateMode != 0);
	}
	return 0;
}
