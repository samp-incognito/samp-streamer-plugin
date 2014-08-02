/*
<<<<<<< HEAD
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
=======
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
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69

#include "../natives.h"

#include "../core.h"
#include "../main.h"
#include "../utility.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
<<<<<<< HEAD
#include <boost/unordered_map.hpp>

#include <sampgdk/a_vehicles.h>

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::CreateDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicVehicle");
=======
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <sampgdk/sampgdk.h>

cell AMX_NATIVE_CALL Natives::CreateDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicVehicle");
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69
	if (core->getData()->getMaxItems(STREAMER_TYPE_VEHICLE) == core->getData()->vehicles.size())
	{
		return 0;
	}
<<<<<<< HEAD

=======
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69
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
<<<<<<< HEAD
	vehicle->respawndelay = static_cast<int>(params[8]);

	Utility::addToContainer(vehicle->worlds, static_cast<int>(params[10]));
	Utility::addToContainer(vehicle->interiors, static_cast<int>(params[11]));
	Utility::addToContainer(vehicle->players, static_cast<int>(params[12]));
	vehicle->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
=======
	Utility::addToContainer(vehicle->worlds, static_cast<int>(params[8]));
	Utility::addToContainer(vehicle->interiors, static_cast<int>(params[9]));
	Utility::addToContainer(vehicle->players, static_cast<int>(params[10]));
	vehicle->streamDistance = amx_ctof(params[11]) * amx_ctof(params[11]);
	vehicle->respawn_delay = static_cast<int>(params[12]);
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69
	core->getGrid()->addVehicle(vehicle);
	core->getData()->vehicles.insert(std::make_pair(vehicleID, vehicle));
	return static_cast<cell>(vehicleID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicVehicle(AMX *amx, cell *params)
<<<<<<< HEAD
{
=======
{ 
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69
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

<<<<<<< HEAD
cell AMX_NATIVE_CALL Natives::GetDynamicVehiclePos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicVehiclePos");
	boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (p != core->getData()->vehicles.end())
	{
		Utility::storeFloatInNative(amx, params[2], p->second->position[0]);
		Utility::storeFloatInNative(amx, params[3], p->second->position[1]);
		Utility::storeFloatInNative(amx, params[4], p->second->position[2]);
=======
cell AMX_NATIVE_CALL Natives::GetDynamicVehicleModel(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicVehicleModel");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		return o->second->modelID;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehiclePos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicVehiclePos");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		float x, y, z;
		GetVehiclePos(o->second, &x, &y, &z);
		Utility::storeFloatInNative(amx, params[2], x);
		Utility::storeFloatInNative(amx, params[3], y);
		Utility::storeFloatInNative(amx, params[4], z);
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehiclePos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicVehiclePos");
<<<<<<< HEAD
	boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (p != core->getData()->vehicles.end())
	{
		SetVehiclePos(static_cast<int>(params[1]), amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
=======
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		SetVehiclePos(o->second, amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleZAngle(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "GetDynamicVehicleZAngle");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		float a;
		GetVehicleZAngle(o->second, &a);
		Utility::storeFloatInNative(amx, params[2], a);
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69
		return 1;
	}
	return 0;
}

<<<<<<< HEAD

=======
cell AMX_NATIVE_CALL Natives::SetDynamicVehicleZAngle(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SetDynamicVehicleZAngle");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		SetVehicleZAngle(o->second, amx_ctof(params[2]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleDistanceFromPoint(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicVehicleDistanceFromPoint");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		return static_cast<cell>(GetVehicleDistanceFromPoint(o->second, amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4])));
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleColor(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "SetDynamicVehicleColor");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		o->second->color1 = static_cast<int>(params[2]);
		o->second->color2 = static_cast<int>(params[3]);

		boost::unordered_map<int, int>::iterator v = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
		if (v != core->getStreamer()->internalVehicles.end())
		{
			ChangeVehicleColor(v->second, o->second->color1, o->second->color2);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleColor(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "GetDynamicVehicleColor");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		Utility::storeIntegerInNative(amx, params[2], o->second->color1);
		Utility::storeIntegerInNative(amx, params[3], o->second->color2);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehiclePaintjob(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SetDynamicVehiclePaintjob");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		o->second->paintjob = static_cast<int>(params[2]);

		boost::unordered_map<int, int>::iterator v = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
		if (v != core->getStreamer()->internalVehicles.end())
		{
			ChangeVehiclePaintjob(v->second, o->second->paintjob);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehiclePaintjob(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "GetDynamicVehiclePaintjob");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		Utility::storeIntegerInNative(amx, params[2], o->second->paintjob);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleNumberPlate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SetDynamicVehicleNumberPlate");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		o->second->plate_number = Utility::convertNativeStringToString(amx, params[2]);

		boost::unordered_map<int, int>::iterator v = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
		if (v != core->getStreamer()->internalVehicles.end())
		{
			SetVehicleNumberPlate(v->second, o->second->plate_number.c_str());
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleNumberPlate(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "GetDynamicVehicleNumberPlate");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		Utility::convertStringToNativeString(amx, params[2], params[3], o->second->plate_number);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleToRespawn(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "SetDynamicVehicleToRespawn");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		SetVehicleToRespawn(o->second);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AddDynamicVehicleComponent(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AddDynamicVehicleComponent");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator c = o->second->components.find(GetVehicleComponentType(static_cast<int>(params[2])));
		if (c != o->second->components.end()) {
			o->second->components.quick_erase(c);
		}

		o->second->components.insert(std::make_pair(GetVehicleComponentType(static_cast<int>(params[2])), static_cast<int>(params[2])));

		boost::unordered_map<int, int>::iterator v = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
		if (v != core->getStreamer()->internalVehicles.end())
		{
			AddVehicleComponent(v->second, static_cast<int>(params[2]));
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::RemoveDynamicVehicleComponent(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "RemoveDynamicVehicleComponent");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator c = o->second->components.find(GetVehicleComponentType(static_cast<int>(params[2])));
		if (c != o->second->components.end()) {
			o->second->components.quick_erase(c);
		}

		boost::unordered_map<int, int>::iterator v = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
		if (v != core->getStreamer()->internalVehicles.end())
		{
			RemoveVehicleComponent(v->second, static_cast<int>(params[2]));
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleComponentInSlot(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "GetDynamicVehicleComponentInSlot");
	boost::unordered_map<int, Item::SharedVehicle>::iterator o = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (o != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator c = o->second->components.find(static_cast<int>(params[2]));
		if (c != o->second->components.end()) {
			return c->second;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleHealth(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "GetDynamicVehicleHealth");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		float health;
		GetVehicleHealth(o->second, &health);
		Utility::storeFloatInNative(amx, params[2], health);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleHealth(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SetDynamicVehicleHealth");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		SetVehicleHealth(o->second, amx_ctof(params[2]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleDamageStatus(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "GetDynamicVehicleDamageStatus");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		int panels, doors, lights, tires;
		GetVehicleDamageStatus(o->second, &panels, &doors, &lights, &tires);
		Utility::storeIntegerInNative(amx, params[2], panels);
		Utility::storeIntegerInNative(amx, params[3], doors);
		Utility::storeIntegerInNative(amx, params[4], lights);
		Utility::storeIntegerInNative(amx, params[5], tires);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleDamageStatus(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "SetDynamicVehicleDamageStatus");
	boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[1]));
	if (o != core->getStreamer()->internalVehicles.end())
	{
		UpdateVehicleDamageStatus(o->second, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), static_cast<int>(params[5]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerDynamicVehicleID(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetPlayerDynamicVehicleID");

	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (p->second.activeVehicle != INVALID_VEHICLE_ID) {
			return p->second.activeVehicle;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::PutPlayerInDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "PutPlayerInDynamicVehicle");

	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_map<int, int>::iterator o = core->getStreamer()->internalVehicles.find(static_cast<int>(params[2]));
		if (o != core->getStreamer()->internalVehicles.end())
		{
			PutPlayerInVehicle(static_cast<int>(params[1]), static_cast<int>(params[2]), static_cast<int>(params[3]));
			return 1;
		}
	}
	return 0;
}
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69
