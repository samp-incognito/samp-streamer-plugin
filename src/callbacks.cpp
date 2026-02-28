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

// v2.9.7 - eLdarQo: Modernised all iterator loops to range-based for (C++20),
//           added null-core guard on every callback, added null AMX pointer
//           guard before calling amx_FindPublic/amx_Exec, replaced NULL with
//           nullptr throughout.

#include "main.h"

#include "core.h"

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	if (!core) return true;
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		auto &players = core->getData()->players;
		if (players.find(playerid) == players.end())
		{
			players.emplace(playerid, Player(playerid));
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	if (!core) return true;
	core->getData()->players.erase(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	if (!core) return true;
	auto p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		p->second.requestingClass = false;
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid)
{
	if (!core) return true;
	auto p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		p->second.requestingClass = true;
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid)
{
	if (!core) return true;
	auto p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint != p->second.visibleCheckpoint)
		{
			int checkpointid = p->second.visibleCheckpoint;
			p->second.activeCheckpoint = checkpointid;
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				if (!amx_FindPublic(amx, "OnPlayerEnterDynamicCP", &amxIndex))
				{
					amx_Push(amx, static_cast<cell>(checkpointid));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, nullptr, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid)
{
	if (!core) return true;
	auto p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint == p->second.visibleCheckpoint)
		{
			int checkpointid = p->second.activeCheckpoint;
			p->second.activeCheckpoint = 0;
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				if (!amx_FindPublic(amx, "OnPlayerLeaveDynamicCP", &amxIndex))
				{
					amx_Push(amx, static_cast<cell>(checkpointid));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, nullptr, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid)
{
	if (!core) return true;
	auto p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint != p->second.visibleRaceCheckpoint)
		{
			int checkpointid = p->second.visibleRaceCheckpoint;
			p->second.activeRaceCheckpoint = checkpointid;
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				if (!amx_FindPublic(amx, "OnPlayerEnterDynamicRaceCP", &amxIndex))
				{
					amx_Push(amx, static_cast<cell>(checkpointid));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, nullptr, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid)
{
	if (!core) return true;
	auto p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint == p->second.visibleRaceCheckpoint)
		{
			int checkpointid = p->second.activeRaceCheckpoint;
			p->second.activeRaceCheckpoint = 0;
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				if (!amx_FindPublic(amx, "OnPlayerLeaveDynamicRaceCP", &amxIndex))
				{
					amx_Push(amx, static_cast<cell>(checkpointid));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, nullptr, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
{
	if (!core) return true;
	for (const auto &[key, internalId] : core->getData()->internalPickups)
	{
		if (internalId == pickupid)
		{
			int dynPickupId = key.first;
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				if (!amx_FindPublic(amx, "OnPlayerPickUpDynamicPickup", &amxIndex))
				{
					amx_Push(amx, static_cast<cell>(dynPickupId));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, nullptr, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	if (!core || !playerobject) return false;

	auto p = core->getData()->players.find(playerid);
	if (p == core->getData()->players.end()) return false;

	for (const auto &[dynObjId, internalId] : p->second.internalObjects)
	{
		if (internalId == objectid)
		{
			if (response == EDIT_RESPONSE_CANCEL || response == EDIT_RESPONSE_FINAL)
			{
				auto o = core->getData()->objects.find(dynObjId);
				if (o != core->getData()->objects.end())
				{
					auto &obj = *o->second;
					if (obj.comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF &&
					    obj.originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						obj.comparableStreamDistance = obj.originalComparableStreamDistance;
						obj.originalComparableStreamDistance = -1.0f;
					}
				}
			}
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				cell amxRetVal = 0;
				if (!amx_FindPublic(amx, "OnPlayerEditDynamicObject", &amxIndex))
				{
					amx_Push(amx, amx_ftoc(fRotZ));
					amx_Push(amx, amx_ftoc(fRotY));
					amx_Push(amx, amx_ftoc(fRotX));
					amx_Push(amx, amx_ftoc(fZ));
					amx_Push(amx, amx_ftoc(fY));
					amx_Push(amx, amx_ftoc(fX));
					amx_Push(amx, static_cast<cell>(response));
					amx_Push(amx, static_cast<cell>(dynObjId));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, &amxRetVal, amxIndex);
					if (amxRetVal) break;
				}
			}
			return true;
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z)
{
	if (!core || type != SELECT_OBJECT_PLAYER_OBJECT) return false;

	auto p = core->getData()->players.find(playerid);
	if (p == core->getData()->players.end()) return false;

	for (const auto &[dynObjId, internalId] : p->second.internalObjects)
	{
		if (internalId == objectid)
		{
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				cell amxRetVal = 0;
				if (!amx_FindPublic(amx, "OnPlayerSelectDynamicObject", &amxIndex))
				{
					amx_Push(amx, amx_ftoc(z));
					amx_Push(amx, amx_ftoc(y));
					amx_Push(amx, amx_ftoc(x));
					amx_Push(amx, static_cast<cell>(modelid));
					amx_Push(amx, static_cast<cell>(dynObjId));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, &amxRetVal, amxIndex);
					if (amxRetVal) break;
				}
			}
			return true;
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float x, float y, float z)
{
	bool retVal = true;
	if (!core || hittype != BULLET_HIT_TYPE_PLAYER_OBJECT) return retVal;

	auto p = core->getData()->players.find(playerid);
	if (p == core->getData()->players.end()) return retVal;

	for (const auto &[dynObjId, internalId] : p->second.internalObjects)
	{
		if (internalId == hitid)
		{
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				cell amxRetVal = 0;
				if (!amx_FindPublic(amx, "OnPlayerShootDynamicObject", &amxIndex))
				{
					amx_Push(amx, amx_ftoc(z));
					amx_Push(amx, amx_ftoc(y));
					amx_Push(amx, amx_ftoc(x));
					amx_Push(amx, static_cast<cell>(dynObjId));
					amx_Push(amx, static_cast<cell>(weaponid));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, &amxRetVal, amxIndex);
					if (!amxRetVal) retVal = false;
				}
			}
			break;
		}
	}
	return retVal;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamageActor(int playerid, int actorid, float amount, int weaponid, int bodypart)
{
	if (!core) return false;
	for (const auto &[key, internalId] : core->getData()->internalActors)
	{
		if (internalId == actorid)
		{
			int dynActorId = key.first;
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				cell amxRetVal = 0;
				if (!amx_FindPublic(amx, "OnPlayerGiveDamageDynamicActor", &amxIndex))
				{
					amx_Push(amx, static_cast<cell>(bodypart));
					amx_Push(amx, static_cast<cell>(weaponid));
					amx_Push(amx, amx_ftoc(amount));
					amx_Push(amx, static_cast<cell>(dynActorId));
					amx_Push(amx, static_cast<cell>(playerid));
					amx_Exec(amx, &amxRetVal, amxIndex);
					if (amxRetVal) break;
				}
			}
			return true;
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamIn(int actorid, int forplayerid)
{
	if (!core) return true;
	for (const auto &[key, internalId] : core->getData()->internalActors)
	{
		if (internalId == actorid)
		{
			int dynActorId = key.first;
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				if (!amx_FindPublic(amx, "OnDynamicActorStreamIn", &amxIndex))
				{
					amx_Push(amx, static_cast<cell>(forplayerid));
					amx_Push(amx, static_cast<cell>(dynActorId));
					amx_Exec(amx, nullptr, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamOut(int actorid, int forplayerid)
{
	if (!core) return true;
	for (const auto &[key, internalId] : core->getData()->internalActors)
	{
		if (internalId == actorid)
		{
			int dynActorId = key.first;
			for (AMX *amx : core->getData()->interfaces)
			{
				if (!amx) continue;
				int amxIndex = 0;
				if (!amx_FindPublic(amx, "OnDynamicActorStreamOut", &amxIndex))
				{
					amx_Push(amx, static_cast<cell>(forplayerid));
					amx_Push(amx, static_cast<cell>(dynActorId));
					amx_Exec(amx, nullptr, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}
