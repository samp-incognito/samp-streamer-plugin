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

#include <boost/scoped_ptr.hpp>

cell AMX_NATIVE_CALL Natives::Streamer_CallbackHook(AMX *amx, cell *params)
{
	core->getEvents()->setInterface(amx);
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_OPC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerConnect(static_cast<int>(*playerid)));
		}
		case STREAMER_OPDC:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			cell *playerid = NULL, *reason = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &reason);
			return static_cast<cell>(core->getEvents()->OnPlayerDisconnect(static_cast<int>(*playerid), static_cast<int>(*reason)));
		}
		case STREAMER_OPEO:
		{
			CHECK_PARAMS(11, "Streamer_CallbackHook");
			cell *playerid = NULL, *playerobject = NULL, *objectid = NULL, *response = NULL, *x = NULL, *y = NULL, *z = NULL, *rx = NULL, *ry = NULL, *rz = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &playerobject);
			amx_GetAddr(amx, params[4], &objectid);
			amx_GetAddr(amx, params[5], &response);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);
			amx_GetAddr(amx, params[9], &rx);
			amx_GetAddr(amx, params[10], &ry);
			amx_GetAddr(amx, params[11], &rz);
			return static_cast<cell>(core->getEvents()->OnPlayerEditObject(static_cast<int>(*playerid), static_cast<int>(*playerobject), static_cast<int>(*objectid), static_cast<int>(*response), amx_ctof(*x), amx_ctof(*y), amx_ctof(*z), amx_ctof(*rx), amx_ctof(*ry), amx_ctof(*rz)));
		}
		case STREAMER_OPSO:
		{
			CHECK_PARAMS(8, "Streamer_CallbackHook");
			cell *playerid = NULL, *type = NULL, *objectid = NULL, *modelid = NULL, *x = NULL, *y = NULL, *z = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &type);
			amx_GetAddr(amx, params[4], &objectid);
			amx_GetAddr(amx, params[5], &modelid);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);
			return static_cast<cell>(core->getEvents()->OnPlayerSelectObject(static_cast<int>(*playerid), static_cast<int>(*type), static_cast<int>(*objectid), static_cast<int>(*modelid), amx_ctof(*x), amx_ctof(*y), amx_ctof(*z)));
		}
		case STREAMER_OPPP:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			cell *playerid = NULL, *pickupid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &pickupid);
			return static_cast<cell>(core->getEvents()->OnPlayerPickUpPickup(static_cast<int>(*playerid), static_cast<int>(*pickupid)));
		}
		case STREAMER_OPEC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerEnterCheckpoint(static_cast<int>(*playerid)));
		}
		case STREAMER_OPLC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerLeaveCheckpoint(static_cast<int>(*playerid)));
		}
		case STREAMER_OPERC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerEnterRaceCheckpoint(static_cast<int>(*playerid)));
		}
		case STREAMER_OPLRC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerLeaveRaceCheckpoint(static_cast<int>(*playerid)));
		}
		case STREAMER_OPWS:
		{
			CHECK_PARAMS(8, "Streamer_CallbackHook");
			cell *playerid = NULL, *weaponid = NULL, *hittype = NULL, *hitid = NULL, *x = NULL, *y = NULL, *z = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &weaponid);
			amx_GetAddr(amx, params[4], &hittype);
			amx_GetAddr(amx, params[5], &hitid);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);
			return static_cast<cell>(core->getEvents()->OnPlayerWeaponShot(static_cast<int>(*playerid), static_cast<int>(*weaponid), static_cast<int>(*hittype), static_cast<int>(*hitid), amx_ctof(*x), amx_ctof(*y), amx_ctof(*z)));
		}
	}
	return 0;
}
