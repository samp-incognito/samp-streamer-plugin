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

#include "../natives.h"

#include "../core.h"
#include "../main.h"
#include "../utility.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <sampgdk/a_vehicles.h>

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::CreateDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicVehicle");
	if (core->getData()->getMaxItems(STREAMER_TYPE_VEHICLE) == core->getData()->vehicles.size())
	{
		return 0;
	}

	int vehicleID = Item::Vehicle::identifier.get();
	Item::SharedVehicle vehicle(new Item::Vehicle);
	vehicle->amx = amx;
	vehicle->vehicleID = vehicleID;
	vehicle->worldID = 0;
	vehicle->modelID = static_cast<int>(params[1]);
	vehicle->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	vehicle->angle = amx_ctof(params[5]);
	vehicle->color1 = static_cast<int>(params[6]);
	vehicle->color2 = static_cast<int>(params[7]);
	vehicle->respawndelay = static_cast<int>(params[8]);

	Utility::addToContainer(vehicle->worlds, static_cast<int>(params[10]));
	Utility::addToContainer(vehicle->interiors, static_cast<int>(params[11]));
	Utility::addToContainer(vehicle->players, static_cast<int>(params[12]));
	vehicle->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	core->getGrid()->addVehicle(vehicle);
	core->getData()->vehicles.insert(std::make_pair(vehicleID, vehicle));
	return static_cast<cell>(vehicleID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicVehicle");
	boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (p != core->getData()->vehicles.end())
	{
		Utility::destroyVehicle(p);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicVehicle");
	boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (p != core->getData()->vehicles.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehiclePos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicVehiclePos");
	boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (p != core->getData()->vehicles.end())
	{
		Utility::storeFloatInNative(amx, params[2], p->second->position[0]);
		Utility::storeFloatInNative(amx, params[3], p->second->position[1]);
		Utility::storeFloatInNative(amx, params[4], p->second->position[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehiclePos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicVehiclePos");
	boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (p != core->getData()->vehicles.end())
	{
		SetVehiclePos(static_cast<int>(params[1]), amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		return 1;
	}
	return 0;
}


