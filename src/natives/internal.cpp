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
	core->getCallbacks()->setInterface(amx);
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_OPC:
		{ 
			CHECK_PARAMS(2, "Streamer_CallbackHook"); 
			//cell *playerid = NULL; 
			//amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getCallbacks()->OnPlayerConnect(static_cast<int>(params[2])));
		}
		case STREAMER_OPDC:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			//cell *playerid = NULL, *reason = NULL;
			//amx_GetAddr(amx, params[2], &playerid);
			//amx_GetAddr(amx, params[3], &reason);
			return static_cast<cell>(core->getCallbacks()->OnPlayerDisconnect(static_cast<int>(params[2]), static_cast<int>(params[3])));
		}
		case STREAMER_OPEO:
		{
			CHECK_PARAMS(11, "Streamer_CallbackHook");
			/*cell *playerid = NULL, *playerobject = NULL, *objectid = NULL, *response = NULL, *x = NULL, *y = NULL, *z = NULL, *rx = NULL, *ry = NULL, *rz = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &playerobject);
			amx_GetAddr(amx, params[4], &objectid);
			amx_GetAddr(amx, params[5], &response);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);
			amx_GetAddr(amx, params[9], &rx);
			amx_GetAddr(amx, params[10], &ry);
			amx_GetAddr(amx, params[11], &rz);*/
			return static_cast<cell>(core->getCallbacks()->OnPlayerEditObject(static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), static_cast<int>(params[5]), 
				static_cast<float>(params[6]), static_cast<float>(params[7]), static_cast<float>(params[8]), static_cast<float>(params[9]), static_cast<float>(params[10]),static_cast<float>(params[11]) ));
		}
		case STREAMER_OPSO:
		{
			CHECK_PARAMS(8, "Streamer_CallbackHook");
			/*cell *playerid = NULL, *type = NULL, *objectid = NULL, *modelid = NULL, *x = NULL, *y = NULL, *z = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &type);
			amx_GetAddr(amx, params[4], &objectid);
			amx_GetAddr(amx, params[5], &modelid);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);*/
			return static_cast<cell>(core->getCallbacks()->OnPlayerSelectObject(static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), static_cast<int>(params[5]),
				static_cast<float>(params[6]), static_cast<float>(params[7]), static_cast<float>(params[8])));
		}
		case STREAMER_OPPP:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			//cell *playerid = NULL, *pickupid = NULL;
			//amx_GetAddr(amx, params[2], &playerid);
			//amx_GetAddr(amx, params[3], &pickupid);
			return static_cast<cell>(core->getCallbacks()->OnPlayerPickUpPickup(static_cast<int>(params[2]), static_cast<int>(params[3])));
		}
		case STREAMER_OPEC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			//cell *playerid = NULL;
			//amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getCallbacks()->OnPlayerEnterCheckpoint(static_cast<int>(params[2])));
		}
		case STREAMER_OPLC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			//cell *playerid = NULL;
			//amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getCallbacks()->OnPlayerLeaveCheckpoint(static_cast<int>(params[2])));
		}
		case STREAMER_OPERC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			//cell *playerid = NULL;
			//amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getCallbacks()->OnPlayerEnterRaceCheckpoint(static_cast<int>(params[2])));
		}
		case STREAMER_OPLRC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			//cell *playerid = NULL;
			//amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getCallbacks()->OnPlayerLeaveRaceCheckpoint(static_cast<int>(params[2])));
		}
		case STREAMER_OPWS:
		{
			CHECK_PARAMS(8, "Streamer_CallbackHook");
			/*cell *playerid = NULL, *weaponid = NULL, *hittype = NULL, *hitid = NULL, *x = NULL, *y = NULL, *z = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &weaponid);
			amx_GetAddr(amx, params[4], &hittype);
			amx_GetAddr(amx, params[5], &hitid);
			amx_GetAddr(amx, params[6], &x);
			amx_GetAddr(amx, params[7], &y);
			amx_GetAddr(amx, params[8], &z);*/
			return static_cast<cell>(core->getCallbacks()->OnPlayerWeaponShot(static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), static_cast<int>(params[5]),
				static_cast<float>(params[6]), static_cast<float>(params[7]), static_cast<float>(params[8])));
		}
	}
	return 0;
}
