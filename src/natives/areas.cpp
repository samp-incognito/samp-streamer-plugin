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

#include "../natives.h"

#include "../core.h"
#include "../main.h"
#include "../utility.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::CreateDynamicCircle(AMX *amx, cell *params)
{
	CHECK_PARAMS(6, "CreateDynamicCircle");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_CIRCLE;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->size = amx_ctof(params[3]) * amx_ctof(params[3]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[4]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[5]));
	Utility::addToContainer(area->players, static_cast<int>(params[6]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCylinder(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "CreateDynamicCylinder");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_CYLINDER;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->height = Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4]));
	area->size = amx_ctof(params[5]) * amx_ctof(params[5]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[6]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[7]));
	Utility::addToContainer(area->players, static_cast<int>(params[8]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicSphere(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicSphere");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_SPHERE;
	area->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	area->size = amx_ctof(params[4]) * amx_ctof(params[4]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRectangle(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicRectangle");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_RECTANGLE;
	area->position = Box2D(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4])));
	boost::geometry::correct(boost::get<Box2D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(boost::get<Box2D>(area->position).min_corner(), boost::get<Box2D>(area->position).max_corner()));
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCuboid(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicCuboid");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_CUBOID;
	area->position = Box3D(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
	boost::geometry::correct(boost::get<Box3D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Box3D>(area->position).min_corner()[0], boost::get<Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(area->position).max_corner()[0], boost::get<Box3D>(area->position).max_corner()[1])));
	Utility::addToContainer(area->worlds, static_cast<int>(params[7]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[8]));
	Utility::addToContainer(area->players, static_cast<int>(params[9]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPolygon(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicPolygon");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	if (static_cast<int>(params[4] >= 2 && static_cast<int>(params[4]) % 2))
	{
		Utility::logError("CreateDynamicPolygon: Number of points must be divisible by two");
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_POLYGON;
	Utility::convertArrayToPolygon(amx, params[1], params[4], boost::get<Polygon2D>(area->position));
	area->height = Eigen::Vector2f(amx_ctof(params[2]), amx_ctof(params[3]));
	Box2D box = boost::geometry::return_envelope<Box2D>(boost::get<Polygon2D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(box.min_corner(), box.max_corner()));
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicArea");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		Utility::destroyArea(a);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicArea");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicPolygonPoints(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "GetDynamicPolygonPoints");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return static_cast<cell>(Utility::convertPolygonToArray(amx, params[2], params[3], boost::get<Polygon2D>(a->second->position)) != 0);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicPolygonNumberPoints(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicPolygonNumberPoints");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return static_cast<cell>(boost::get<Polygon2D>(a->second->position).outer().size());
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledAreas.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledAreas.end())
			{
				p->second.disabledAreas.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledAreas.end())
			{
				p->second.disabledAreas.insert(static_cast<int>(params[2]));
				p->second.internalAreas.erase(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicAreas");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledAreas.clear();
		if (!static_cast<int>(params[2]))
		{
			for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				p->second.disabledAreas.insert(a->first);
			}
			p->second.internalAreas.clear();
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "IsPlayerInDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		bool recheck = static_cast<int>(params[3]) != 0;
		if (!recheck)
		{
			boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[2]));
			if (i != p->second.internalAreas.end())
			{
				return 1;
			}
		}
		else
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			return static_cast<cell>(Utility::isPointInArea(p->second.position, a->second)) != 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInAnyDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
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
			for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				if (Utility::isPointInArea(p->second.position, a->second))
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
	CHECK_PARAMS(2, "IsAnyPlayerInDynamicArea");
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		bool recheck = static_cast<int>(params[2]) != 0;
		if (!recheck)
		{
			boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[1]));
			if (i != p->second.internalAreas.end())
			{
				return 1;
			}
		}
		else
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
			return static_cast<cell>(Utility::isPointInArea(p->second.position, a->second)) != 0;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsAnyPlayerInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsAnyPlayerInAnyDynamicArea");
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		bool recheck = static_cast<int>(params[1]) != 0;
		if (!recheck)
		{
			if (!p->second.internalAreas.empty())
			{
				return 1;
			}
		}
		else
		{
			for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				if (Utility::isPointInArea(p->second.position, a->second))
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
	CHECK_PARAMS(4, "IsPointInDynamicArea");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return Utility::isPointInArea(Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4])), a->second);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPointInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "IsPointInAnyDynamicArea");
	for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		if (Utility::isPointInArea(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), a->second))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerDynamicAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "GetPlayerDynamicAreas");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		std::vector<int> finalAreas;
		std::map<float, int> orderedAreas;
		for (boost::unordered_set<int>::iterator i = p->second.internalAreas.begin(); i != p->second.internalAreas.end(); ++i)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(*i);
			if (a != core->getData()->areas.end())
			{
				float distance = 0.0f;
				switch (a->second->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					case STREAMER_AREA_TYPE_CYLINDER:
					{
						if (a->second->attach)
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(a->second->attach->position[0], a->second->attach->position[1])));
						}
						else
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), boost::get<Eigen::Vector2f>(a->second->position)));
						}
						break;
					}
					case STREAMER_AREA_TYPE_SPHERE:
					{
						if (a->second->attach)
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, a->second->attach->position));
						}
						else
						{
							distance = static_cast<float>(boost::geometry::comparable_distance(p->second.position, boost::get<Eigen::Vector3f>(a->second->position)));
						}
						break;
					}
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Box2D>(a->second->position));
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
						break;
					}
					case STREAMER_AREA_TYPE_CUBOID:
					{
						Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3D>(a->second->position));
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), centroid));
						break;
					
					}
					case STREAMER_AREA_TYPE_POLYGON:
					{
						Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2D>(a->second->position));
						distance = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), centroid));
						break;
					}
				}
				orderedAreas.insert(std::pair<float, int>(distance, a->first));
			}
		}
		for (std::map<float, int>::iterator i = orderedAreas.begin(); i != orderedAreas.end(); ++i)
		{
			finalAreas.push_back(i->second);
		}
		return static_cast<cell>(Utility::convertContainerToArray(amx, params[2], params[3], finalAreas) != 0);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerNumberDynamicAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetPlayerNumberDynamicAreas");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return static_cast<cell>(p->second.internalAreas.size());
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "AttachDynamicAreaToObject");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
		{
			Utility::logError("AttachDynamicAreaToObject: Only circles and spheres may be attached to objects");
			return 0;
		}
		if ((static_cast<int>(params[2]) != INVALID_GENERIC_ID && static_cast<int>(params[3]) != STREAMER_OBJECT_TYPE_DYNAMIC) || static_cast<int>(params[2]) != INVALID_STREAMER_ID && static_cast<int>(params[3]) == STREAMER_OBJECT_TYPE_DYNAMIC)
		{
			a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
			a->second->attach->player = INVALID_GENERIC_ID;
			a->second->attach->vehicle = INVALID_GENERIC_ID;
			a->second->attach->object = boost::make_tuple(static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if ((a->second->attach->object.get<0>() != INVALID_GENERIC_ID && a->second->attach->object.get<1>() != STREAMER_OBJECT_TYPE_DYNAMIC) || (a->second->attach->object.get<0>() != INVALID_STREAMER_ID && a->second->attach->object.get<1>() == STREAMER_OBJECT_TYPE_DYNAMIC))
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
	CHECK_PARAMS(2, "AttachDynamicAreaToPlayer");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
		{
			Utility::logError("AttachDynamicAreaToPlayer: Only circles and spheres may be attached to players");
			return 0;
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
			a->second->attach->object = boost::make_tuple(INVALID_STREAMER_ID, STREAMER_OBJECT_TYPE_DYNAMIC, INVALID_PLAYER_ID);
			a->second->attach->vehicle = INVALID_GENERIC_ID;
			a->second->attach->player = static_cast<int>(params[2]);
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if (a->second->attach->player != INVALID_GENERIC_ID)
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
	CHECK_PARAMS(2, "AttachDynamicAreaToVehicle");
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
		{
			Utility::logError("AttachDynamicAreaToVehicle: Only circles and spheres may be attached to vehicles");
			return 0;
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
			a->second->attach->object = boost::make_tuple(INVALID_STREAMER_ID, STREAMER_OBJECT_TYPE_DYNAMIC, INVALID_PLAYER_ID);
			a->second->attach->player = INVALID_GENERIC_ID;
			a->second->attach->vehicle = static_cast<int>(params[2]);
			core->getStreamer()->attachedAreas.insert(a->second);
		}
		else
		{
			if (a->second->attach)
			{
				if (a->second->attach->vehicle != INVALID_GENERIC_ID)
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
