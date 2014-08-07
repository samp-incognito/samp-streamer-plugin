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

#include "utility.h"

#include "core.h"
#include "main.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace Utility;

cell AMX_NATIVE_CALL Utility::hookedNative(AMX *amx, cell *params)
{
	return 1;
}

int Utility::checkInterfaceAndRegisterNatives(AMX *amx, AMX_NATIVE_INFO *amxNativeList)
{
	AMX_HEADER *amxHeader = reinterpret_cast<AMX_HEADER*>(amx->base);
	AMX_FUNCSTUBNT *amxNativeTable = reinterpret_cast<AMX_FUNCSTUBNT*>(amx->base + amxHeader->natives);
	int amxRegisterResult = amx_Register(amx, amxNativeList, -1);
	bool foundNatives = false;
	bool hookedNatives = false;
	int numberOfNatives = 0;
	amx_NumNatives(amx, &numberOfNatives);
	for (int i = 0; i < numberOfNatives; ++i)
	{
		char *name = reinterpret_cast<char*>(amx->base + amxNativeTable[i].nameofs);
		if (std::string(name).find("Streamer_") != std::string::npos)
		{
			foundNatives = true;
			if (!amxNativeTable[i].address)
			{
				sampgdk::logprintf("*** Streamer Plugin: Warning: Obsolete or invalid native \"%s\" found (script might need to be recompiled with the latest include file)", name);
				amxNativeTable[i].address = reinterpret_cast<cell>(hookedNative);
				hookedNatives = true;
			}
		}
	}
	if (foundNatives)
	{
		cell amxAddr = 0;
		int includeFileValue = 0;
		if (!amx_FindPubVar(amx, "Streamer_IncludeFileVersion", &amxAddr))
		{
			cell *amxPhysAddr = NULL;
			if (!amx_GetAddr(amx, amxAddr, &amxPhysAddr))
			{
				includeFileValue = static_cast<int>(*amxPhysAddr);
			}
		}
		if (includeFileValue != INCLUDE_FILE_VERSION)
		{
			std::ostringstream includeFileVersion;
			if (includeFileValue <= 0)
			{
				includeFileVersion << "unknown version";
			}
			else
			{
				includeFileVersion << std::hex << std::showbase << includeFileValue;
			}
			sampgdk::logprintf("*** Streamer Plugin: Warning: Include file version (%s) does not match plugin version (%#x) (script might need to be recompiled with the latest include file)", includeFileVersion.str().c_str(), INCLUDE_FILE_VERSION);
		}
	}
	if (hookedNatives)
	{
		amxRegisterResult = amx_Register(amx, amxNativeList, -1);
	}
	return amxRegisterResult;
}

void Utility::destroyAllItemsInInterface(AMX *amx)
{
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.begin();
	while (o != core->getData()->objects.end())
	{
		if (o->second->amx == amx)
		{
			o = destroyObject(o);
		}
		else
		{
			++o;
		}
	}
	boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.begin();
	while (p != core->getData()->pickups.end())
	{
		if (p->second->amx == amx)
		{
			p = destroyPickup(p);
		}
		else
		{
			++p;
		}
	}
	boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin();
	while (c != core->getData()->checkpoints.end())
	{
		if (c->second->amx == amx)
		{
			c = destroyCheckpoint(c);
		}
		else
		{
			++c;
		}
	}
	boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin();
	while (r != core->getData()->raceCheckpoints.end())
	{
		if (r->second->amx == amx)
		{
			r = destroyRaceCheckpoint(r);
		}
		else
		{
			++r;
		}
	}
	boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin();
	while (m != core->getData()->mapIcons.end())
	{
		if (m->second->amx == amx)
		{
			m = destroyMapIcon(m);
		}
		else
		{
			++m;
		}
	}
	boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.begin();
	while (t != core->getData()->textLabels.end())
	{
		if (t->second->amx == amx)
		{
			t = destroyTextLabel(t);
		}
		else
		{
			++t;
		}
	}
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin();
	while (a != core->getData()->areas.end())
	{
		if (a->second->amx == amx)
		{
			a = destroyArea(a);
		}
		else
		{
			++a;
		}
	}
}

boost::unordered_map<int, Item::SharedArea>::iterator Utility::destroyArea(boost::unordered_map<int, Item::SharedArea>::iterator a)
{
	Item::Area::identifier.remove(a->first, core->getData()->areas.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.disabledAreas.erase(a->first);
		p->second.internalAreas.erase(a->first);
		p->second.visibleCell->areas.erase(a->first);
	}
	core->getGrid()->removeArea(a->second);
	return core->getData()->areas.erase(a);
}

boost::unordered_map<int, Item::SharedCheckpoint>::iterator Utility::destroyCheckpoint(boost::unordered_map<int, Item::SharedCheckpoint>::iterator c)
{
	Item::Checkpoint::identifier.remove(c->first, core->getData()->checkpoints.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		if (p->second.visibleCheckpoint == c->first)
		{
			DisablePlayerCheckpoint(p->first);
			p->second.activeCheckpoint = 0;
			p->second.visibleCheckpoint = 0;
		}
		p->second.disabledCheckpoints.erase(c->first);
		p->second.visibleCell->checkpoints.erase(c->first);
	}
	core->getGrid()->removeCheckpoint(c->second);
	return core->getData()->checkpoints.erase(c);
}

boost::unordered_map<int, Item::SharedMapIcon>::iterator Utility::destroyMapIcon(boost::unordered_map<int, Item::SharedMapIcon>::iterator m)
{
	Item::MapIcon::identifier.remove(m->first, core->getData()->mapIcons.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
		if (i != p->second.internalMapIcons.end())
		{
			RemovePlayerMapIcon(p->first, i->second);
			p->second.mapIconIdentifier.remove(i->second, p->second.internalMapIcons.size());
			p->second.internalMapIcons.quick_erase(i);
		}
		p->second.visibleCell->mapIcons.erase(m->first);
	}
	core->getGrid()->removeMapIcon(m->second);
	return core->getData()->mapIcons.erase(m);
}

boost::unordered_map<int, Item::SharedObject>::iterator Utility::destroyObject(boost::unordered_map<int, Item::SharedObject>::iterator o)
{
	Item::Object::identifier.remove(o->first, core->getData()->objects.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
		if (i != p->second.internalObjects.end())
		{
			DestroyPlayerObject(p->first, i->second);
			p->second.internalObjects.quick_erase(i);
		}
		p->second.visibleCell->objects.erase(o->first);
	}
	core->getGrid()->removeObject(o->second);
	return core->getData()->objects.erase(o);
}

boost::unordered_map<int, Item::SharedPickup>::iterator Utility::destroyPickup(boost::unordered_map<int, Item::SharedPickup>::iterator p)
{
	Item::Pickup::identifier.remove(p->first, core->getData()->pickups.size());
	boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(p->first);
	if (i != core->getStreamer()->internalPickups.end())
	{
		DestroyPickup(i->second);
		core->getStreamer()->internalPickups.quick_erase(i);
	}
	core->getGrid()->removePickup(p->second);
	return core->getData()->pickups.erase(p);
}

boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator Utility::destroyRaceCheckpoint(boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r)
{
	Item::RaceCheckpoint::identifier.remove(r->first, core->getData()->raceCheckpoints.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		if (p->second.visibleRaceCheckpoint == r->first)
		{
			DisablePlayerRaceCheckpoint(p->first);
			p->second.activeRaceCheckpoint = 0;
			p->second.visibleRaceCheckpoint = 0;
		}
		p->second.disabledRaceCheckpoints.erase(r->first);
		p->second.visibleCell->raceCheckpoints.erase(r->first);
	}
	core->getGrid()->removeRaceCheckpoint(r->second);
	return core->getData()->raceCheckpoints.erase(r);
}

boost::unordered_map<int, Item::SharedTextLabel>::iterator Utility::destroyTextLabel(boost::unordered_map<int, Item::SharedTextLabel>::iterator t)
{
	Item::TextLabel::identifier.remove(t->first, core->getData()->textLabels.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
		if (i != p->second.internalTextLabels.end())
		{
			DeletePlayer3DTextLabel(p->first, i->second);
			p->second.internalTextLabels.quick_erase(i);
		}
		p->second.visibleCell->textLabels.erase(t->first);
	}
	core->getGrid()->removeTextLabel(t->second);
	return core->getData()->textLabels.erase(t);
}

bool Utility::isPointInArea(const Eigen::Vector3f &point, const Item::SharedArea &area)
{
	switch (area->type)
	{
		case STREAMER_AREA_TYPE_CIRCLE:
		{
			if (area->attach)
			{
				if (boost::geometry::comparable_distance(Eigen::Vector2f(point[0], point[1]), Eigen::Vector2f(area->attach->position[0], area->attach->position[1])) <= area->size)
				{
					return true;
				}
			}
			else
			{
				if (boost::geometry::comparable_distance(Eigen::Vector2f(point[0], point[1]), boost::get<Eigen::Vector2f>(area->position)) <= area->size)
				{
					return true;
				}
			}
			return false;
		}
		case STREAMER_AREA_TYPE_CYLINDER:
		{
			if (point[2] >= area->height[0] && point[2] <= area->height[1])
			{
				if (boost::geometry::comparable_distance(Eigen::Vector2f(point[0], point[1]), boost::get<Eigen::Vector2f>(area->position)) <= area->size)
				{
					return true;
				}
			}
			return false;
		}
		case STREAMER_AREA_TYPE_SPHERE:
		{
			if (area->attach)
			{
				if (boost::geometry::comparable_distance(point, area->attach->position) <= area->size)
				{
					return true;
				}
			}
			else
			{
				if (boost::geometry::comparable_distance(point, boost::get<Eigen::Vector3f>(area->position)) <= area->size)
				{
					return true;
				}
			}
			return false;
		}
		case STREAMER_AREA_TYPE_RECTANGLE:
		{
			return boost::geometry::covered_by(Eigen::Vector2f(point[0], point[1]), boost::get<Box2D>(area->position));
		}
		case STREAMER_AREA_TYPE_CUBOID:
		{
			return boost::geometry::covered_by(point, boost::get<Box3D>(area->position));
		}
		case STREAMER_AREA_TYPE_POLYGON:
		{
			if (point[2] >= area->height[0] && point[2] <= area->height[1])
			{
				return boost::geometry::covered_by(Eigen::Vector2f(point[0], point[1]), boost::get<Polygon2D>(area->position));
			}
			return false;
		}
	}
	return false;
}

void Utility::convertArrayToPolygon(AMX *amx, cell input, cell size, Polygon2D &polygon)
{
	cell *array = NULL;
	std::vector<Eigen::Vector2f> points;
	amx_GetAddr(amx, input, &array);
	for (std::size_t i = 0; i < static_cast<std::size_t>(size); i += 2)
	{
		points.push_back(Eigen::Vector2f(amx_ctof(array[i]), amx_ctof(array[i + 1])));
	}
	boost::geometry::assign_points(polygon, points);
	boost::geometry::correct(polygon);
}

bool Utility::convertPolygonToArray(AMX *amx, cell output, cell size, Polygon2D &polygon)
{
	cell *array = NULL;
	std::size_t i = 0;
	amx_GetAddr(amx, output, &array);
	for (std::vector<Eigen::Vector2f>::iterator p = polygon.outer().begin(); p != polygon.outer().end(); ++p)
	{
		if ((i + 1) >= static_cast<std::size_t>(size))
		{
			return false;
		}
		array[i++] = amx_ftoc(p->data()[0]);
		array[i++] = amx_ftoc(p->data()[1]);
	}
	return true;
}

std::string Utility::convertNativeStringToString(AMX *amx, cell input)
{
	char *string = NULL;
	amx_StrParam(amx, input, string);
	return string ? string : "";
}

void Utility::convertStringToNativeString(AMX *amx, cell output, cell size, std::string string)
{
	cell *address = NULL;
	amx_GetAddr(amx, output, &address);
	amx_SetString(address, string.c_str(), 0, 0, static_cast<size_t>(size));
}

void Utility::storeFloatInNative(AMX *amx, cell output, float value)
{
	cell *address;
	amx_GetAddr(amx, output, &address);
	*address = amx_ftoc(value);
}

void Utility::storeIntegerInNative(AMX *amx, cell output, int value)
{
	cell *address;
	amx_GetAddr(amx, output, &address);
	*address = value;
}
