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

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::CreateDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicVehicle");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_VEHICLE) == core->getData()->vehicles.size())
	{
		return 0;
	}
	int vehicleID = Item::Vehicle::identifier.get();
	Item::SharedVehicle vehicle(new Item::Vehicle);
	vehicle->amx = amx;
	vehicle->vehicleID = vehicleID;
	vehicle->modelID = static_cast<int>(params[1]);

	vehicle->spawn.position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	vehicle->spawn.angle = amx_ctof(params[5]);
	vehicle->spawn.color1 = static_cast<int>(params[6]);
	vehicle->spawn.color2 = static_cast<int>(params[7]);
	vehicle->respawnDelay = static_cast<int>(params[8]) != -1 ? static_cast<int>(params[8]) * 1000 : -1;
	vehicle->spawn.addsiren = static_cast<int>(params[9]) != 0;
	vehicle->position = vehicle->spawn.position;
	vehicle->angle = vehicle->spawn.angle;
	vehicle->color1 = vehicle->spawn.color1;
	vehicle->color2 = vehicle->spawn.color2;
	vehicle->paintjob = 4; // In GTA, you can use 0 - 3 IDs for paintjobs, 4 is invalid
	vehicle->health = 1000.0f;
	vehicle->carmods.clear();
	vehicle->touched = false;
	vehicle->used = false;
	vehicle->spawnedTick = GetTickCount();
	
	// Reset vehicle damage
	vehicle->panels = 0;
	vehicle->doors = 0;
	vehicle->lights = 0;
	vehicle->tires = 0;

	// Set vehicle parameters as unset
	vehicle->params.engine = VEHICLE_PARAMS_UNSET;
	vehicle->params.lights = VEHICLE_PARAMS_UNSET;
	vehicle->params.alarm = VEHICLE_PARAMS_UNSET;
	vehicle->params.doors = VEHICLE_PARAMS_UNSET;
	vehicle->params.bonnet = VEHICLE_PARAMS_UNSET;
	vehicle->params.boot = VEHICLE_PARAMS_UNSET;
	vehicle->params.objective = VEHICLE_PARAMS_UNSET;
	vehicle->params.siren = VEHICLE_PARAMS_UNSET;
	vehicle->params.cardoors.driver = VEHICLE_PARAMS_UNSET;
	vehicle->params.cardoors.passenger = VEHICLE_PARAMS_UNSET;
	vehicle->params.cardoors.backleft = VEHICLE_PARAMS_UNSET;
	vehicle->params.cardoors.backright = VEHICLE_PARAMS_UNSET;
	vehicle->params.carwindows.driver = VEHICLE_PARAMS_UNSET;
	vehicle->params.carwindows.passenger = VEHICLE_PARAMS_UNSET;
	vehicle->params.carwindows.backleft = VEHICLE_PARAMS_UNSET;
	vehicle->params.carwindows.backright = VEHICLE_PARAMS_UNSET;
	vehicle->worldID = static_cast<int>(params[10]);
	vehicle->interior = static_cast<int>(params[11]);
	vehicle->streamDistance = amx_ctof(params[12]) * amx_ctof(params[12]);
	core->getGrid()->addVehicle(vehicle);
	core->getData()->vehicles.insert(std::make_pair(vehicleID, vehicle));
	return static_cast<cell>(vehicleID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicVehicle");
	int vehicleid = static_cast<int>(params[1]);
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(vehicleid);
	if (v != core->getData()->vehicles.end())
	{
		Utility::destroyVehicle(v);
		return 1;
	}
/*
	for (boost::unordered_set<Item::SharedObject>::iterator o = core->getStreamer()->attachedObjects.begin(); o != core->getStreamer()->attachedObjects.end(); ++o)
	{
		if ((*o)->attach)
		{
			if((*o)->attach->vehicle == vehicleid && (*o)->attach->vehicleType == STREAMER_VEHICLE_TYPE_DYNAMIC)
			{
				boost::unordered_map<int, Item::SharedObject>::iterator p = core->getData()->objects.find((*o)->objectID);
				if (p != core->getData()->objects.end())
				{
					Utility::destroyObject(p);
					return 1;
				}
			
			}
		}
	}
	for(boost::unordered_set<Item::SharedTextLabel>::iterator t = core->getStreamer()->attachedTextLabels.begin(); t != core->getStreamer()->attachedTextLabels.end(); ++t)
	{
		if((*t)->attach)
		{
			if((*t)->attach->vehicle == vehicleid && (*t)->attach->vehicleType == STREAMER_VEHICLE_TYPE_DYNAMIC)
			{
				boost::unordered_map<int, Item::SharedTextLabel>::iterator p = core->getData()->textLabels.find((*t)->textLabelID);
				if(p != core->getData()->textLabels.end())
				{
					Utility::destroyTextLabel(p);
					return 1;
				}

			}
		}
	}
	for (boost::unordered_set<Item::SharedArea>::iterator a = core->getStreamer()->attachedAreas.begin(); a != core->getStreamer()->attachedAreas.end(); ++a)
	{
		if ((*a)->attach)
		{
			if((*a)->attach->vehicle == vehicleid && (*a)->attach->vehicleType == STREAMER_VEHICLE_TYPE_DYNAMIC)
			{
				boost::unordered_map<int, Item::SharedArea>::iterator p = core->getData()->areas.find((*a)->areaID);
				if (p != core->getData()->areas.end())
				{
					Utility::destroyArea(p);
					return 1;
				}
			
			}
		}
	}
*/
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicVehicle");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicVehicleStreamedIn(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsDynamicVehicleStreamedIn");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			return IsVehicleStreamedIn(i->second, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleSpawnInfo(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "GetDynamicVehicleSpawnInfo");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Utility::storeFloatInNative(amx, params[2], v->second->spawn.position[0]);
		Utility::storeFloatInNative(amx, params[3], v->second->spawn.position[1]);
		Utility::storeFloatInNative(amx, params[4], v->second->spawn.position[2]);
		Utility::storeFloatInNative(amx, params[5], v->second->spawn.angle);
		Utility::storeIntegerInNative(amx, params[6], v->second->spawn.color1);
		Utility::storeIntegerInNative(amx, params[7], v->second->spawn.color2);
		Utility::storeIntegerInNative(amx, params[8], v->second->spawn.addsiren);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleSpawnInfo(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "SetDynamicVehicleSpawnInfo");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if(v != core->getData()->vehicles.end())
	{
		v->second->spawn.position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		v->second->spawn.angle = amx_ctof(params[5]);
		v->second->spawn.color1 = static_cast<int>(params[6]);
		v->second->spawn.color2 = static_cast<int>(params[7]);
		v->second->spawn.addsiren = static_cast<int>(params[8]) != 0;
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehiclePos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicVehiclePos");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		if (v->second->touched)
		{
			core->getStreamer()->processActiveItems();
		}		
		Utility::storeFloatInNative(amx, params[2], v->second->position[0]);
		Utility::storeFloatInNative(amx, params[3], v->second->position[1]);
		Utility::storeFloatInNative(amx, params[4], v->second->position[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehiclePos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicVehiclePos");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Eigen::Vector3f position = v->second->position;
		v->second->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehiclePos(i->second, amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		}
		if (position[0] != v->second->position[0] || position[1] != v->second->position[1])
		{
			if (v->second->cell)
			{
				core->getGrid()->removeVehicle(v->second, true);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleZAngle(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "GetDynamicVehicleZAngle");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		float angle;
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			GetVehicleZAngle(i->second, &angle);
		}
		else
		{
			angle = v->second->angle;
		}
		Utility::storeFloatInNative(amx, params[2], angle);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleRotationQuat(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "GetDynamicVehicleRotationQuat");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		float w, x, y, z;
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			GetVehicleRotationQuat(i->second, &w, &x, &y, &z);
		}
		else
		{
			w = v->second->qw;
			x = v->second->qx;
			y = v->second->qy;
			z = v->second->qz;
		}
		Utility::storeFloatInNative(amx, params[2], w);
		Utility::storeFloatInNative(amx, params[3], x);
		Utility::storeFloatInNative(amx, params[4], y);
		Utility::storeFloatInNative(amx, params[5], z);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehDistanceFromPoint(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicVehDistanceFromPoint");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Eigen::Vector3f position;
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			GetVehiclePos(i->second, &position[0], &position[1], &position[2]);
		}
		else
		{
			position = v->second->position;
		}
		float distance = static_cast<float>(boost::geometry::distance(Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4])), position));
		return amx_ftoc(distance);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleZAngle(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SetDynamicVehicleZAngle");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		float angle = amx_ctof(params[2]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleZAngle(i->second, angle);
		}
		else
		{
			v->second->angle = angle;
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehParamsForPlayer(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicVehParamsForPlayer");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleParamsForPlayer(i->second, static_cast<int>(params[2]), static_cast<int>(params[3]) != 0, static_cast<int>(params[4]) != 0);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleParamsEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "SetDynamicVehicleParamsEx");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->params.engine = static_cast<char>(params[2]);
		v->second->params.lights = static_cast<char>(params[3]);
		v->second->params.alarm = static_cast<char>(params[4]);
		v->second->params.doors = static_cast<char>(params[5]);
		v->second->params.bonnet = static_cast<char>(params[6]);
		v->second->params.boot = static_cast<char>(params[7]);
		v->second->params.objective = static_cast<char>(params[8]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleParamsEx(i->second, v->second->params.engine, v->second->params.lights, v->second->params.alarm, v->second->params.doors, v->second->params.bonnet, v->second->params.boot, v->second->params.objective);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleParamsEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "GetDynamicVehicleParamsEx");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Utility::storeIntegerInNative(amx, params[2], v->second->params.engine);
		Utility::storeIntegerInNative(amx, params[3], v->second->params.lights);
		Utility::storeIntegerInNative(amx, params[4], v->second->params.alarm);
		Utility::storeIntegerInNative(amx, params[5], v->second->params.doors);
		Utility::storeIntegerInNative(amx, params[6], v->second->params.bonnet);
		Utility::storeIntegerInNative(amx, params[7], v->second->params.boot);
		Utility::storeIntegerInNative(amx, params[8], v->second->params.objective);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehParamsSirenState(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicVehParamsSirenState");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		return v->second->params.siren;
	}
	return VEHICLE_PARAMS_UNSET;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehParamsCarDoors(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "SetDynamicVehParamsCarDoors");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->params.cardoors.driver = static_cast<char>(params[2]);
		v->second->params.cardoors.passenger = static_cast<char>(params[3]);
		v->second->params.cardoors.backleft = static_cast<char>(params[4]);
		v->second->params.cardoors.backright = static_cast<char>(params[5]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleParamsCarDoors(i->second, v->second->params.cardoors.driver, v->second->params.cardoors.passenger, v->second->params.cardoors.backleft, v->second->params.cardoors.backright);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehParamsCarDoors(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "SetDynamicVehParamsCarDoors");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Utility::storeIntegerInNative(amx, params[2], v->second->params.cardoors.driver);
		Utility::storeIntegerInNative(amx, params[3], v->second->params.cardoors.passenger);
		Utility::storeIntegerInNative(amx, params[4], v->second->params.cardoors.backleft);
		Utility::storeIntegerInNative(amx, params[5], v->second->params.cardoors.backright);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehParamsCarWindows(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "SetDynamicVehParamsCarWindows");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->params.carwindows.driver = static_cast<char>(params[2]);
		v->second->params.carwindows.passenger = static_cast<char>(params[3]);
		v->second->params.carwindows.backleft = static_cast<char>(params[4]);
		v->second->params.carwindows.backright = static_cast<char>(params[5]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleParamsCarWindows(i->second, v->second->params.carwindows.driver, v->second->params.carwindows.passenger, v->second->params.carwindows.backleft, v->second->params.carwindows.backright);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehParamsCarWindows(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "GetDynamicVehParamsCarWindows");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Utility::storeIntegerInNative(amx, params[2], v->second->params.carwindows.driver);
		Utility::storeIntegerInNative(amx, params[3], v->second->params.carwindows.passenger);
		Utility::storeIntegerInNative(amx, params[4], v->second->params.carwindows.backleft);
		Utility::storeIntegerInNative(amx, params[5], v->second->params.carwindows.backright);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleToRespawn(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "SetDynamicVehicleToRespawn");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Eigen::Vector3f position = v->second->position;
		v->second->position = v->second->spawn.position;
		v->second->angle = v->second->spawn.angle;
		v->second->color1 = v->second->spawn.color1;
		v->second->color2 = v->second->spawn.color2;
		v->second->paintjob = 4; // In GTA, you can use 0 - 3 IDs for paintjobs, 4 is invalid
		v->second->health = 1000.0f;
		v->second->carmods.clear();
		if (v->second->touched)
		{
			v->second->touched = false;
			v->second->used = true;
			core->getStreamer()->movingVehicles.erase(v->second);
		}
		v->second->spawnedTick = GetTickCount();

		// Reset vehicle damage
		v->second->panels = 0;
		v->second->doors = 0;
		v->second->lights = 0;
		v->second->tires = 0;

		// Set vehicle parameters as unset
		v->second->params.engine = VEHICLE_PARAMS_UNSET;
		v->second->params.lights = VEHICLE_PARAMS_UNSET;
		v->second->params.alarm = VEHICLE_PARAMS_UNSET;
		v->second->params.doors = VEHICLE_PARAMS_UNSET;
		v->second->params.bonnet = VEHICLE_PARAMS_UNSET;
		v->second->params.boot = VEHICLE_PARAMS_UNSET;
		v->second->params.objective = VEHICLE_PARAMS_UNSET;
		v->second->params.siren = VEHICLE_PARAMS_UNSET;
		v->second->params.cardoors.driver = VEHICLE_PARAMS_UNSET;
		v->second->params.cardoors.passenger = VEHICLE_PARAMS_UNSET;
		v->second->params.cardoors.backleft = VEHICLE_PARAMS_UNSET;
		v->second->params.cardoors.backright = VEHICLE_PARAMS_UNSET;
		v->second->params.carwindows.driver = VEHICLE_PARAMS_UNSET;
		v->second->params.carwindows.passenger = VEHICLE_PARAMS_UNSET;
		v->second->params.carwindows.backleft = VEHICLE_PARAMS_UNSET;
		v->second->params.carwindows.backright = VEHICLE_PARAMS_UNSET;
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleToRespawn(i->second);
			SetVehiclePos(i->second, v->second->position[0], v->second->position[1], v->second->position[2]);
			SetVehicleZAngle(i->second, v->second->angle);
			LinkVehicleToInterior(i->second, v->second->interior);
			SetVehicleVirtualWorld(i->second, v->second->worldID);
		}
		else
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehicleSpawn", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(v->first));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
		if (position[0] != v->second->position[0] || position[1] != v->second->position[1])
		{
			if (v->second->cell)
			{
				core->getGrid()->removeVehicle(v->second, true);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::LinkDynamicVehicleToInterior(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "LinkDynamicVehicleToInterior");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->interior = static_cast<int>(params[2]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			LinkVehicleToInterior(i->second, v->second->interior);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleInterior(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicVehicleColor");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		return v->second->interior;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AddDynamicVehicleComponent(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AddDynamicVehicleComponent");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		int componentid = static_cast<int>(params[2]);
		if (!Utility::isInContainer(v->second->carmods, componentid))
		{
			Utility::addToContainer(v->second->carmods, componentid);
		}
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			AddVehicleComponent(i->second, componentid);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::RemoveDynamicVehicleComponent(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "RemoveDynamicVehicleComponent");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		int componentid = static_cast<int>(params[2]);
		if (Utility::isInContainer(v->second->carmods, componentid))
		{
			Utility::removeFromContainer(v->second->carmods, componentid);
		}
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			RemoveVehicleComponent(i->second, componentid);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::ChangeDynamicVehicleColor(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "ChangeDynamicVehicleColor");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->color1 = static_cast<int>(params[2]);
		v->second->color2 = static_cast<int>(params[3]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			ChangeVehicleColor(i->second, v->second->color1, v->second->color2);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleColor(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "GetDynamicVehicleColor");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Utility::storeIntegerInNative(amx, params[2], v->second->color1);
		Utility::storeIntegerInNative(amx, params[3], v->second->color2);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::ChangeDynamicVehiclePaintjob(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "ChangeDynamicVehiclePaintjob");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->paintjob = static_cast<int>(params[2]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			ChangeVehiclePaintjob(i->second, v->second->paintjob);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehiclePaintjob(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicVehiclePaintjob");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		return v->second->paintjob;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleHealth(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SetDynamicVehicleHealth");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->health = amx_ctof(params[2]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleHealth(i->second, v->second->health);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleHealth(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "GetDynamicVehicleHealth");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		float health;
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			GetVehicleHealth(i->second, &health);
		}
		else
		{
			health = v->second->health;
		}
		Utility::storeFloatInNative(amx, params[2], health);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachTrailerToDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AttachTrailerToDynamicVehicle");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, Item::SharedVehicle>::iterator v2 = core->getData()->vehicles.find(static_cast<int>(params[2]));
		if (v2 != core->getData()->vehicles.end())
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
			if (i != core->getData()->internalVehicles.end())
			{
				boost::unordered_map<int, int>::iterator i2 = core->getData()->internalVehicles.find(v2->first);
				if (i2 != core->getData()->internalVehicles.end())
				{
					AttachTrailerToVehicle(i2->second, i->second);
					return 1;
				}
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DetachTrailerFromDynamicVeh(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DetachTrailerFromDynamicVeh");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			return DetachTrailerFromVehicle(i->second);
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsTrailerAttachedToDynamicVeh(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsTrailerAttachedToDynamicVeh");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			return IsTrailerAttachedToVehicle(i->second);
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleTrailer(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicVehicleTrailer");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			int trailerid = GetVehicleTrailer(i->second);
			for (boost::unordered_map<int, int>::iterator j = core->getData()->internalVehicles.begin(); j != core->getData()->internalVehicles.end(); j++)
			{
				if (j->second == trailerid)
				{
					return j->first;
				}
			}
			return 0;
		}
		return 0;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleNumberPlate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "GetDynamicVehicleModel");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->numberplate = Utility::convertNativeStringToString(amx, params[2]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleNumberPlate(i->second, v->second->numberplate.c_str());
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleNumberPlate(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "GetDynamicVehicleNumberPlate");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		cell *text = NULL;
		amx_GetAddr(amx, params[2], &text);
		amx_SetString(text, v->second->numberplate.c_str(), 0, 0, static_cast<size_t>(params[3]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleModel(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicVehicleModel");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		return v->second->modelID;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehComponentInSlot(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "GetDynamicVehComponentInSlot");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	int ret = 0;
	if (v != core->getData()->vehicles.end())
	{
		int slot = static_cast<int>(params[2]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			ret = GetVehicleComponentInSlot(i->second, slot);
		}
		else
		{
			try
			{
				ret = v->second->carmods.at(slot);
			}
			catch (...)
			{
				ret = 0;
			}
		}
	}
	return ret;
}

cell AMX_NATIVE_CALL Natives::RepairDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "RepairDynamicVehicle");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			RepairVehicle(i->second);
		}
		else
		{
			v->second->health = 1000.0f;
			v->second->panels = 0;
			v->second->doors = 0;
			v->second->lights = 0;
			v->second->tires = 0;
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleVelocity(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicVehicleVelocity");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Eigen::Vector3f velocity = Eigen::Vector3f(0.0f, 0.0f, 0.0f);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			GetVehicleVelocity(i->second, &velocity[0], &velocity[1], &velocity[2]);
		}
		Utility::storeFloatInNative(amx, params[2], velocity[0]);
		Utility::storeFloatInNative(amx, params[3], velocity[1]);
		Utility::storeFloatInNative(amx, params[4], velocity[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleVelocity(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicVehicleVelocity");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Eigen::Vector3f velocity = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleVelocity(i->second, velocity[0], velocity[1], velocity[2]);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehAngularVelocity(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicVehAngularVelocity");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		Eigen::Vector3f velocity = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleAngularVelocity(i->second, velocity[0], velocity[1], velocity[2]);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleDamageStatus(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "GetDynamicVehicleDamageStatus");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		int panels, doors, lights, tires;
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			GetVehicleDamageStatus(i->second, &panels, &doors, &lights, &tires);
		}
		else
		{
			panels = v->second->panels;
			doors = v->second->doors;
			lights = v->second->lights;
			tires = v->second->tires;
		}
		Utility::storeIntegerInNative(amx, params[2], panels);
		Utility::storeIntegerInNative(amx, params[3], doors);
		Utility::storeIntegerInNative(amx, params[4], lights);
		Utility::storeIntegerInNative(amx, params[5], tires);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::UpdateDynamicVehDamageStatus(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "UpdateDynamicVehDamageStatus");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->panels = static_cast<int>(params[2]);
		v->second->doors = static_cast<int>(params[3]);
		v->second->lights = static_cast<int>(params[4]);
		v->second->tires = static_cast<int>(params[5]);

		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			UpdateVehicleDamageStatus(i->second, v->second->panels, v->second->doors, v->second->lights, v->second->tires);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicVehicleVirtualWorld(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SetDynamicVehicleVirtualWorld");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		v->second->worldID = static_cast<int>(params[2]);
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			SetVehicleVirtualWorld(i->second, static_cast<int>(params[2]));
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicVehicleVirtualWorld(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicVehicleVirtualWorld");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[1]));
	if (v != core->getData()->vehicles.end())
	{
		return v->second->worldID;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerSurfingDynamicVehID(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetPlayerSurfingDynamicVehID");
	int internalid = GetPlayerSurfingVehicleID(static_cast<int>(params[1]));
	if (internalid)
	{
		for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); i++)
		{
			if (i->second == internalid)
			{
				return i->first;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::PutPlayerInDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "PutPlayerInDynamicVehicle");
	int playerid = static_cast<int>(params[1]);
	int vehicleid = static_cast<int>(params[2]);
	int seatid = static_cast<int>(params[3]);
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(vehicleid);
		if (v != core->getData()->vehicles.end())
		{
			boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
			if (i == core->getData()->internalVehicles.end())
			{
				int internalID = INVALID_VEHICLE_ID;
				switch(v->second->modelID)
				{
					case 537:
					case 538:
					{
						//internalID = AddStaticVehicle(v->second->modelID, v->second->position[0], v->second->position[1], v->second->position[2], v->second->angle, v->second->color1, v->second->color2);
						// TODO - This won't work properly without modifing train handling in samp server
						// If you create train, then you create 4 vehicle - the base model ID has been returned, but the last 3 trailer not and you can't get these IDs - only when these ids are in sequence
						// but these IDs won't be in sequence when server randomly destroy and create vehicles at different ids - for more info: http://pastebin.com/wZsiVHBr
						break;
					}
					default:
					{
						internalID = CreateVehicle(v->second->modelID, v->second->position[0], v->second->position[1], v->second->position[2], v->second->angle, v->second->color1, v->second->color2, -1, v->second->spawn.addsiren);
						break;
					}
				}
				if (internalID == INVALID_VEHICLE_ID)
				{
					return 0;
				}
				if (!v->second->numberplate.empty())
				{
					SetVehicleNumberPlate(internalID, v->second->numberplate.c_str());
				}
				if(v->second->interior)
				{
					LinkVehicleToInterior(internalID, v->second->interior);
				}
				if(v->second->worldID)
				{
					SetVehicleVirtualWorld(internalID, v->second->worldID);
				}
				if (!v->second->carmods.empty())
				{
					for (std::vector<int>::iterator c = v->second->carmods.begin(); c != v->second->carmods.end(); c++)
					{
						AddVehicleComponent(internalID, *c);
					}
				}
				if (v->second->paintjob != 4)
				{
					ChangeVehiclePaintjob(internalID, v->second->paintjob);
				}
				if(v->second->panels != 0 || v->second->doors != 0 || v->second->lights != 0|| v->second->tires != 0)
				{
					UpdateVehicleDamageStatus(internalID, v->second->panels, v->second->doors, v->second->lights, v->second->tires);
				}
				if (v->second->health != 1000.0f)
				{
					SetVehicleHealth(internalID, v->second->health);
				}
				if(v->second->params.engine != VEHICLE_PARAMS_UNSET || v->second->params.lights != VEHICLE_PARAMS_UNSET || v->second->params.alarm != VEHICLE_PARAMS_UNSET || v->second->params.doors != VEHICLE_PARAMS_UNSET || v->second->params.bonnet != VEHICLE_PARAMS_UNSET || v->second->params.boot != VEHICLE_PARAMS_UNSET || v->second->params.objective != VEHICLE_PARAMS_UNSET)
				{
					SetVehicleParamsEx(internalID, v->second->params.engine, v->second->params.lights, v->second->params.alarm, v->second->params.doors, v->second->params.bonnet, v->second->params.boot, v->second->params.objective);
				}
				if(v->second->params.cardoors.driver != VEHICLE_PARAMS_UNSET || v->second->params.cardoors.passenger != VEHICLE_PARAMS_UNSET || v->second->params.cardoors.backleft != VEHICLE_PARAMS_UNSET || v->second->params.cardoors.backright != VEHICLE_PARAMS_UNSET)
				{
					SetVehicleParamsCarDoors(internalID, v->second->params.cardoors.driver, v->second->params.cardoors.passenger, v->second->params.cardoors.backleft, v->second->params.cardoors.backright);
				}
				if(v->second->params.carwindows.driver != VEHICLE_PARAMS_UNSET || v->second->params.carwindows.passenger != VEHICLE_PARAMS_UNSET || v->second->params.carwindows.backleft != VEHICLE_PARAMS_UNSET || v->second->params.carwindows.backright != VEHICLE_PARAMS_UNSET)
				{
					SetVehicleParamsCarWindows(internalID, v->second->params.carwindows.driver, v->second->params.carwindows.passenger, v->second->params.carwindows.backleft, v->second->params.carwindows.backright);
				}
				if(internalID != INVALID_VEHICLE_ID)
				{
					PutPlayerInVehicle(playerid, internalID, seatid);
					core->getData()->internalVehicles.insert(std::make_pair(v->first, internalID));
				}
				else
				{
					return 0;
				}
			}
			else
			{
				PutPlayerInVehicle(playerid, i->second, seatid);
			}
			if (!v->second->touched)
			{
				v->second->touched = true;
				v->second->used = true;
				core->getStreamer()->movingVehicles.insert(v->second);
			}
			v->second->lastUpdatedTick = GetTickCount();
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerDynamicVehicleID(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetPlayerDynamicVehicleID");
	int internalid = GetPlayerVehicleID(static_cast<int>(params[1]));
	if (internalid)
	{
		for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); i++)
		{
			if (i->second == internalid)
			{
				return i->first;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInDynamicVehicle");
	int internalid = GetPlayerVehicleID(static_cast<int>(params[1]));
	if (internalid)
	{
		for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); i++)
		{
			if (i->second == internalid)
			{
				return i->first == static_cast<int>(params[2]);
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInAnyDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsPlayerInAnyDynamicVehicle");
	int internalid = GetPlayerVehicleID(static_cast<int>(params[1]));
	if (internalid)
	{
		for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); i++)
		{
			if (i->second == internalid)
			{
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicVehicleOccupied(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsDynamicVehicleOccupied");
	boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(static_cast<int>(params[1]));
	if (i != core->getData()->internalVehicles.end())
	{
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); p++)
		{
			if (GetPlayerVehicleID(p->first) == i->second) return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::PlayerSpectateDynamicVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "PlayerSpectateDynamicVehicle");
	boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(static_cast<int>(params[2]));
	if (v != core->getData()->vehicles.end())
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
		if (i != core->getData()->internalVehicles.end())
		{
			PlayerSpectateVehicle(static_cast<int>(params[1]), i->second, static_cast<int>(params[3]));
		}
		return 1;
	}
	return 0;
}
