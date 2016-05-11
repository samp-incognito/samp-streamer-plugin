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

#include <cmath>
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
				Utility::logError("Obsolete or invalid native \"%s\" found (script might need to be recompiled with the latest include file)", name);
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
			Utility::logError("Include file version (%s) does not match plugin version (%#x) (script might need to be recompiled with the latest include file)", includeFileVersion.str().c_str(), INCLUDE_FILE_VERSION);
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
	Utility::executeFinalAreaCallbacksForAllAreas(amx, false);
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
			sampgdk::DisablePlayerCheckpoint(p->first);
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
			sampgdk::RemovePlayerMapIcon(p->first, i->second);
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
			sampgdk::DestroyPlayerObject(p->first, i->second);
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
	boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.find(p->first);
	if (i != core->getData()->internalPickups.end())
	{
		sampgdk::DestroyPickup(i->second);
		core->getData()->internalPickups.quick_erase(i);
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
			sampgdk::DisablePlayerRaceCheckpoint(p->first);
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
			sampgdk::DeletePlayer3DTextLabel(p->first, i->second);
			p->second.internalTextLabels.quick_erase(i);
		}
		p->second.visibleCell->textLabels.erase(t->first);
	}
	core->getGrid()->removeTextLabel(t->second);
	return core->getData()->textLabels.erase(t);
}

void Utility::executeFinalAreaCallbacks(int areaid)
{
	std::vector<boost::tuple<int, int> > callbacks;
	boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(areaid);
	if (a != core->getData()->areas.end())
	{
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_set<int>::iterator i = p->second.internalAreas.find(a->first);
			if (i != p->second.internalAreas.end())
			{
				callbacks.push_back(boost::make_tuple(a->first, p->first));
			}
		}
	}
	for (std::vector<boost::tuple<int, int> >::const_iterator c = callbacks.begin(); c != callbacks.end(); ++c)
	{
		for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
		{
			int amxIndex = 0;
			if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicArea", &amxIndex))
			{
				amx_Push(*a, static_cast<cell>(c->get<0>()));
				amx_Push(*a, static_cast<cell>(c->get<1>()));
				amx_Exec(*a, NULL, amxIndex);
			}
		}
	}
}

void Utility::executeFinalAreaCallbacksForAllAreas(AMX *amx, bool ignoreInterface)
{
	std::vector<boost::tuple<int, int> > callbacks;
	for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		if (ignoreInterface || a->second->amx == amx)
		{
			for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.find(a->first);
				if (i != p->second.internalAreas.end())
				{
					callbacks.push_back(boost::make_tuple(a->first, p->first));
				}
			}
		}
	}
	for (std::vector<boost::tuple<int, int> >::const_iterator c = callbacks.begin(); c != callbacks.end(); ++c)
	{
		for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
		{
			int amxIndex = 0;
			if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicArea", &amxIndex))
			{
				amx_Push(*a, static_cast<cell>(c->get<0>()));
				amx_Push(*a, static_cast<cell>(c->get<1>()));
				amx_Exec(*a, NULL, amxIndex);
			}
		}
	}
}

void Utility::logError(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	char buffer[MAX_BUFFER];
	vsnprintf(buffer, sizeof(buffer), format, args);
	buffer[sizeof(buffer) - 1] = '\0';
	va_end(args);
	if (core->getData()->errorCallbackEnabled)
	{
		for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
		{
			cell amxAddress = 0;
			int amxIndex = 0;
			if (!amx_FindPublic(*a, "Streamer_OnPluginError", &amxIndex))
			{
				amx_PushString(*a, &amxAddress, NULL, buffer, 0, 0);
				amx_Exec(*a, NULL, amxIndex);
				amx_Release(*a, amxAddress);
			}
		}
	}
	else
	{
		static std::string lastErrorMessage;
		if (lastErrorMessage != buffer)
		{
			sampgdk::logprintf("*** Streamer Plugin: %s", buffer);
		}
		lastErrorMessage = buffer;
	}
}

bool Utility::isPointInArea(const Eigen::Vector3f &point, const Item::SharedArea &area)
{
	switch (area->type)
	{
		case STREAMER_AREA_TYPE_CIRCLE:
		{
			if (area->attach)
			{
				if (boost::geometry::comparable_distance(Eigen::Vector2f(point[0], point[1]), Eigen::Vector2f(area->attach->position[0], area->attach->position[1])) < area->size)
				{
					return true;
				}
			}
			else
			{
				if (boost::geometry::comparable_distance(Eigen::Vector2f(point[0], point[1]), boost::get<Eigen::Vector2f>(area->position)) < area->size)
				{
					return true;
				}
			}
			return false;
		}
		case STREAMER_AREA_TYPE_CYLINDER:
		{
			if ((almostEquals(point[2], area->height[0]) || (point[2] > area->height[0])) && (almostEquals(point[2], area->height[1]) || (point[2] < area->height[1])))
			{
				if (boost::geometry::comparable_distance(Eigen::Vector2f(point[0], point[1]), boost::get<Eigen::Vector2f>(area->position)) < area->size)
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
				if (boost::geometry::comparable_distance(point, area->attach->position) < area->size)
				{
					return true;
				}
			}
			else
			{
				if (boost::geometry::comparable_distance(point, boost::get<Eigen::Vector3f>(area->position)) < area->size)
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
			if ((almostEquals(point[2], area->height[0]) || (point[2] > area->height[0])) && (almostEquals(point[2], area->height[1]) || (point[2] < area->height[1])))
			{
				return boost::geometry::covered_by(Eigen::Vector2f(point[0], point[1]), boost::get<Polygon2D>(area->position));
			}
			return false;
		}
	}
	return false;
}

void Utility::projectPoint(const Eigen::Vector3f &point, const float &heading, Eigen::Vector3f &position)
{
	float angle = (std::atan2(point[0], point[1]) * (180.0f / (std::atan(1.0f) * 4.0f))) - heading, distance = std::sqrt((point[0] * point[0]) + (point[1] * point[1]));
	position[0] += distance * std::sin(angle * ((std::atan(1.0f) * 4.0f) / 180.0f));
	position[1] += distance * std::cos(angle * ((std::atan(1.0f) * 4.0f) / 180.0f));
	position[2] += point[2];
}

void Utility::projectPoint(const Eigen::Vector3f &point, const Eigen::Vector3f &rotation, Eigen::Vector3f &position)
{
	Eigen::Vector3f rotRad = rotation * ((std::atan(1.0f) * 4.0f) / 180.0f), rotCos(std::cos(rotRad[0]), std::cos(rotRad[1]), std::cos(rotRad[2])), rotSin(std::sin(rotRad[0]), std::sin(rotRad[1]), std::sin(rotRad[2]));
	position[0] += (point[0] * rotCos[1] * rotCos[2]) - (point[0] * rotSin[0] * rotSin[1] * rotSin[2]) - (point[1] * rotCos[0] * rotSin[2]) + (point[2] * rotSin[1] * rotCos[2]) + (point[2] * rotSin[0] * rotCos[1] * rotSin[2]);
	position[1] += (point[0] * rotCos[1] * rotSin[2]) + (point[0] * rotSin[0] * rotSin[1] * rotCos[2]) + (point[1] * rotCos[0] * rotCos[2]) + (point[2] * rotSin[1] * rotSin[2]) - (point[2] * rotSin[0] * rotCos[1] * rotCos[2]);
	position[2] += -(point[0] * rotCos[0] * rotSin[1]) + (point[1] * rotSin[0]) + (point[2] * rotCos[0] * rotCos[1]);
}

void Utility::projectPoint(const Eigen::Vector3f &point, const Eigen::Vector4f &quaternion, Eigen::Vector3f &position)
{
	Eigen::Matrix3f matrix = Eigen::Matrix3f::Zero();
	matrix(0, 0) = 1 - 2 * ((quaternion[1] * quaternion[1]) + (quaternion[2] * quaternion[2]));
	matrix(0, 1) = 2 * ((quaternion[0] * quaternion[1]) - (quaternion[2] * quaternion[3]));
	matrix(0, 2) = 2 * ((quaternion[0] * quaternion[2]) + (quaternion[1] * quaternion[3]));
	matrix(1, 0) = 2 * ((quaternion[0] * quaternion[1]) + (quaternion[2] * quaternion[3]));
	matrix(1, 1) = 1 - 2 * ((quaternion[0] * quaternion[0]) + (quaternion[2] * quaternion[2]));
	matrix(1, 2) = 2 * ((quaternion[1] * quaternion[2]) - (quaternion[0] * quaternion[3]));
	matrix(2, 0) = 2 * ((quaternion[0] * quaternion[2]) - (quaternion[1] * quaternion[3]));
	matrix(2, 1) = 2 * ((quaternion[1] * quaternion[2]) + (quaternion[0] * quaternion[3]));
	matrix(2, 2) = 1 - 2 * ((quaternion[0] * quaternion[0]) + (quaternion[1] * quaternion[1]));
	position[0] += -((point[2] * matrix(2, 0)) + (point[1] * matrix(2, 1)) + (point[0] * matrix(2, 2)));
	position[1] += (point[2] * matrix(1, 0)) + (point[1] * matrix(1, 1)) + (point[0] * matrix(1, 2));
	position[2] += (point[2] * matrix(0, 0)) + (point[1] * matrix(0, 1)) + (point[0] * matrix(0, 2));
}

std::size_t Utility::getMaxVisibleItems(int type, int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			switch (type)
			{
				case STREAMER_TYPE_OBJECT:
				{
					return p->second.maxVisibleObjects;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					return p->second.maxVisibleMapIcons;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					return p->second.maxVisibleTextLabels;
				}
			}
		}
	}
	return core->getData()->getGlobalMaxVisibleItems(type);
}

bool Utility::setMaxVisibleItems(int type, std::size_t value, int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			switch (type)
			{
				case STREAMER_TYPE_OBJECT:
				{
					p->second.maxVisibleObjects = value;
					return true;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					p->second.maxVisibleMapIcons = value;
					return true;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					p->second.maxVisibleTextLabels = value;
					return true;
				}
			}
		}
	}
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		switch (type)
		{
			case STREAMER_TYPE_OBJECT:
			{
				p->second.maxVisibleObjects = value;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				p->second.maxVisibleMapIcons = value;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				p->second.maxVisibleTextLabels = value;
			}
		}
	}
	return core->getData()->setGlobalMaxVisibleItems(type, value);
}

float Utility::getRadiusMultiplier(int type, int playerid)
{
	if (type >= 0 && type < STREAMER_MAX_TYPES)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				return p->second.radiusMultipliers[type];
			}
		}
	}
	return core->getData()->getGlobalRadiusMultiplier(type);
}

bool Utility::setRadiusMultiplier(int type, float value, int playerid)
{
	if (type >= 0 && type < STREAMER_MAX_TYPES)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				p->second.radiusMultipliers[type] = value;
				return true;
			}
		}
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			p->second.radiusMultipliers[type] = value;
		}
	}
	return core->getData()->setGlobalRadiusMultiplier(type, value);
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
