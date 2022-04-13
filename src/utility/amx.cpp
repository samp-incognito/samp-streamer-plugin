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

#include "amx.h"
#include "../core.h"

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
				amxNativeTable[i].address = reinterpret_cast<cell>(hookedNative);
				hookedNatives = true;
			}
		}
	}
	if (foundNatives)
	{
		cell amxAddr = 0;
		int includeFileVersion = 0;
		if (!amx_FindPubVar(amx, "Streamer_IncludeFileVersion", &amxAddr))
		{
			cell *amxPhysAddr = NULL;
			if (!amx_GetAddr(amx, amxAddr, &amxPhysAddr))
			{
				includeFileVersion = static_cast<int>(*amxPhysAddr);
			}
		}
		std::ostringstream includeFileVersionStream, pluginVersionStream;
		if (includeFileVersion <= 0)
		{
			includeFileVersionStream << "unknown version";
		}
		else
		{
			includeFileVersionStream << std::hex << std::showbase << includeFileVersion;
			pluginVersionStream << std::hex << std::showbase << INCLUDE_FILE_VERSION;
			std::istringstream(includeFileVersionStream.str().substr(0, pluginVersionStream.str().length())) >> std::hex >> includeFileVersion;
		}
		if (includeFileVersion < INCLUDE_FILE_VERSION)
		{
			Utility::logError("The include file version (%s) for this script is older than the plugin version (%#x). The script might need to be recompiled with the latest include file.", includeFileVersionStream.str().c_str(), INCLUDE_FILE_VERSION);
		}
		else if (includeFileVersion > INCLUDE_FILE_VERSION)
		{
			Utility::logError("The plugin version (%#x) is older than the include file version (%s) for this script. The plugin might need to be updated to the latest version.", INCLUDE_FILE_VERSION, includeFileVersionStream.str().c_str());
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
	std::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.begin();
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
	std::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.begin();
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
	std::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin();
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
	std::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin();
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
	std::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin();
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
	std::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.begin();
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
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin();
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
	std::unordered_map<int, Item::SharedActor>::iterator b = core->getData()->actors.begin();
	while (b != core->getData()->actors.end())
	{
		if (b->second->amx == amx)
		{
			b = destroyActor(b);
		}
		else
		{
			++b;
		}
	}
}

void Utility::executeFinalAreaCallbacks(int areaid)
{
	std::vector<std::tuple<int, int> > callbacks;
	std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(areaid);
	if (a != core->getData()->areas.end())
	{
		for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			std::unordered_set<int>::iterator i = p->second.internalAreas.find(a->first);
			if (i != p->second.internalAreas.end())
			{
				callbacks.push_back(std::make_tuple(a->first, p->first));
			}
		}
	}
	for (std::vector<std::tuple<int, int> >::const_iterator c = callbacks.begin(); c != callbacks.end(); ++c)
	{
		for (std::set<AMX*>::iterator amx = core->getData()->interfaces.begin(); amx != core->getData()->interfaces.end(); ++amx)
		{
			int amxIndex = 0;
			if (!amx_FindPublic(*amx, "OnPlayerLeaveDynamicArea", &amxIndex))
			{
				amx_Push(*amx, static_cast<cell>(std::get<0>(*c)));
				amx_Push(*amx, static_cast<cell>(std::get<1>(*c)));
				amx_Exec(*amx, NULL, amxIndex);
			}
		}
	}
}

void Utility::executeFinalAreaCallbacksForAllAreas(AMX *amx, bool ignoreInterface)
{
	std::vector<std::tuple<int, int> > callbacks;
	for (std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
	{
		if (ignoreInterface || a->second->amx == amx)
		{
			for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				std::unordered_set<int>::iterator i = p->second.internalAreas.find(a->first);
				if (i != p->second.internalAreas.end())
				{
					callbacks.push_back(std::make_tuple(a->first, p->first));
				}
			}
		}
	}
	for (std::vector<std::tuple<int, int> >::const_iterator c = callbacks.begin(); c != callbacks.end(); ++c)
	{
		for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
		{
			int amxIndex = 0;
			if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicArea", &amxIndex))
			{
				amx_Push(*a, static_cast<cell>(std::get<0>(*c)));
				amx_Push(*a, static_cast<cell>(std::get<1>(*c)));
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
			if (ompgdk::GDKManager::Get()->GetCore())
			{
				ompgdk::GDKManager::Get()->GetCore()->printLn("*** Streamer Plugin: %s", buffer);
			}
		}
		lastErrorMessage = buffer;
	}
}

void Utility::convertArrayToPolygon(AMX *amx, cell input, cell size, Polygon2d &polygon)
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

bool Utility::convertPolygonToArray(AMX *amx, cell output, cell size, Polygon2d &polygon)
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
