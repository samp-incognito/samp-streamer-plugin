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

#include <sampgdk/plugin.h>

class Events
{
public:
	bool OnPlayerConnect(int playerid);
	bool OnPlayerDisconnect(int playerid, int reason);
	bool OnPlayerEditObject(int playerid, int playerobject, int objectid, int response, float x, float y, float z, float rx, float ry, float rz);
	bool OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z);
	bool OnPlayerPickUpPickup(int playerid, int pickupid);
	bool OnPlayerEnterCheckpoint(int playerid);
	bool OnPlayerLeaveCheckpoint(int playerid);
	bool OnPlayerEnterRaceCheckpoint(int playerid);
	bool OnPlayerLeaveRaceCheckpoint(int playerid);

	inline void setInterface(AMX *amx)
	{
		interface = amx;
	}
private:
	AMX *interface;
};

#endif
