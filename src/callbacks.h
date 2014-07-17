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

#ifndef EVENTS_H
#define EVENTS_H

#include <sampgdk/sdk.h>

class Callbacks
{
public:
	bool OnPlayerConnect(int playerid);
	bool OnPlayerDisconnect(int playerid, int reason);
	bool OnPlayerEnterCheckpoint(int playerid);
	bool OnPlayerLeaveCheckpoint(int playerid);
	bool OnPlayerEnterRaceCheckpoint(int playerid);
	bool OnPlayerLeaveRaceCheckpoint(int playerid);
	bool OnPlayerPickUpPickup(int playerid, int pickupid);
	bool OnPlayerEditObject(int playerid, int playerobject, int objectid, int response, float x, float y, float z, float rx, float ry, float rz);
	bool OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z);
	bool OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float x, float y, float z);

	bool OnVehicleSpawn(int vehicleid);
	bool OnVehicleDeath(int vehicleid, int killerid);
	bool OnPlayerEnterVehicle(int playerid, int vehicleid, int ispassenger);
	bool OnPlayerExitVehicle(int playerid, int vehicleid);
	bool OnVehicleMod(int playerid, int vehicleid, int componentid);
	bool OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid);
	bool OnVehicleRespray(int playerid, int vehicleid, int color1, int color2);
	bool OnVehicleDamageStatusUpdate(int vehicleid, int playerid);
	bool OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z);

	inline void setInterface(AMX *amx)
	{
		interface = amx;
	}
private:
	AMX *interface;
};

#endif
