/*
 * Copyright (C) 2015 Incognito
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

#include "core.h"
#include "utility.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <set>

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p == core->getData()->players.end())
		{
			Player player(playerid);
			core->getData()->players.insert(std::make_pair(playerid, player));
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	core->getData()->players.erase(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint != p->second.visibleCheckpoint)
		{
			int checkpointid = p->second.visibleCheckpoint;
			p->second.activeCheckpoint = checkpointid;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicCP", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(checkpointid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint == p->second.visibleCheckpoint)
		{
			int checkpointid = p->second.activeCheckpoint;
			p->second.activeCheckpoint = 0;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicCP", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(checkpointid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint != p->second.visibleRaceCheckpoint)
		{
			int checkpointid = p->second.visibleRaceCheckpoint;
			p->second.activeRaceCheckpoint = checkpointid;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicRaceCP", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(checkpointid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint == p->second.visibleRaceCheckpoint)
		{
			int checkpointid = p->second.activeRaceCheckpoint;
			p->second.activeRaceCheckpoint = 0;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicRaceCP", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(checkpointid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.begin(); i != core->getData()->internalPickups.end(); ++i)
	{
		if (i->second == pickupid)
		{
			int pickupid = i->first;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerPickUpDynamicPickup", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(pickupid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	if (playerobject)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
			{
				if (i->second == objectid)
				{
					int objectid = i->first;
					for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
					{
						int amxIndex = 0;
						if (!amx_FindPublic(*a, "OnPlayerEditDynamicObject", &amxIndex))
						{
							amx_Push(*a, amx_ftoc(fRotZ));
							amx_Push(*a, amx_ftoc(fRotY));
							amx_Push(*a, amx_ftoc(fRotX));
							amx_Push(*a, amx_ftoc(fZ));
							amx_Push(*a, amx_ftoc(fY));
							amx_Push(*a, amx_ftoc(fX));
							amx_Push(*a, static_cast<cell>(response));
							amx_Push(*a, static_cast<cell>(objectid));
							amx_Push(*a, static_cast<cell>(playerid));
							amx_Exec(*a, NULL, amxIndex);
						}
					}
					break;
				}
			}
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z)
{
	if (type == SELECT_OBJECT_PLAYER_OBJECT)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
			{
				if (i->second == objectid)
				{
					int objectid = i->first;
					for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
					{
						int amxIndex = 0;
						if (!amx_FindPublic(*a, "OnPlayerSelectDynamicObject", &amxIndex))
						{
							amx_Push(*a, amx_ftoc(z));
							amx_Push(*a, amx_ftoc(y));
							amx_Push(*a, amx_ftoc(x));
							amx_Push(*a, static_cast<cell>(modelid));
							amx_Push(*a, static_cast<cell>(objectid));
							amx_Push(*a, static_cast<cell>(playerid));
							amx_Exec(*a, NULL, amxIndex);
						}
					}
					break;
				}
			}
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float x, float y, float z)
{
	if (hittype == BULLET_HIT_TYPE_PLAYER_OBJECT)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
			{
				if (i->second == hitid)
				{
					int objectid = i->first;
					for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
					{
						int amxIndex = 0;
						if (!amx_FindPublic(*a, "OnPlayerShootDynamicObject", &amxIndex))
						{
							amx_Push(*a, amx_ftoc(z));
							amx_Push(*a, amx_ftoc(y));
							amx_Push(*a, amx_ftoc(x));
							amx_Push(*a, static_cast<cell>(objectid));
							amx_Push(*a, static_cast<cell>(weaponid));
							amx_Push(*a, static_cast<cell>(playerid));
							amx_Exec(*a, NULL, amxIndex);
						}
					}
					break;
				}
			}
		}
	}
	else if (hittype == BULLET_HIT_TYPE_VEHICLE)
	{
		for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
		{
			if (i->second == hitid)
			{
				int vehicleid = i->first;
				for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
				{
					int amxIndex = 0;
					if (!amx_FindPublic(*a, "OnPlayerShootDynamicVehicle", &amxIndex))
					{
						amx_Push(*a, amx_ftoc(z));
						amx_Push(*a, amx_ftoc(y));
						amx_Push(*a, amx_ftoc(x));
						amx_Push(*a, static_cast<cell>(vehicleid));
						amx_Push(*a, static_cast<cell>(weaponid));
						amx_Push(*a, static_cast<cell>(playerid));
						amx_Exec(*a, NULL, amxIndex);
					}
				}
				break;
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehicleSpawn", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(i->first);
			if (p != core->getData()->vehicles.end())
			{
				if (p->second->touched)
				{
					p->second->touched = false;
					p->second->used = true;
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehicleDeath", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(killerid));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicVehicle", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(ispassenger));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(i->first);
			if (p != core->getData()->vehicles.end())
			{
				if (!p->second->touched)
				{
					p->second->touched = true;
					p->second->used = true;
					core->getStreamer()->movingVehicles.insert(p->second);
				}
				p->second->lastUpdatedTick = GetTickCount();
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerExitDynamicVehicle", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehicleMod", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(componentid));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(i->first);
			if (p != core->getData()->vehicles.end())
			{
				if (!Utility::isInContainer(p->second->carmods, componentid))
				{
					Utility::addToContainer(p->second->carmods, componentid);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehiclePaintjob", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(paintjobid));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(i->first);
			if (p != core->getData()->vehicles.end())
			{
				p->second->paintjob = paintjobid; 
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehicleRespray", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(color2));
					amx_Push(*a, static_cast<cell>(color1));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(i->first);
			if (p != core->getData()->vehicles.end())
			{
				p->second->color1 = color1; 
				p->second->color2 = color2; 
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehDamageStatusUpdate", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(i->first);
			if (p != core->getData()->vehicles.end())
			{		
				/*
				if (!p->second->touched)
				{
					p->second->touched = true;
					core->getStreamer()->movingVehicles.insert(p->second);
				}
				*/
				p->second->lastUpdatedTick = GetTickCount();
				GetVehicleDamageStatus(i->first, &p->second->panels, &p->second->doors, &p->second->lights, &p->second->tires);
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnUnoccupiedDynamicVehUpdate", &amxIndex))
				{
					amx_Push(*a, amx_ftoc(vel_z));
					amx_Push(*a, amx_ftoc(vel_y));
					amx_Push(*a, amx_ftoc(vel_x));
					amx_Push(*a, amx_ftoc(new_z));
					amx_Push(*a, amx_ftoc(new_y));
					amx_Push(*a, amx_ftoc(new_x));
					amx_Push(*a, static_cast<cell>(passenger_seat));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(i->first);
			if (p != core->getData()->vehicles.end())
			{		
				if (!p->second->touched)
				{
					p->second->touched = true;
					core->getStreamer()->movingVehicles.insert(p->second);
				}
				p->second->lastUpdatedTick = GetTickCount();
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnTrailerUpdate(int playerid, int vehicleid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				cell ret = 1;
				if (!amx_FindPublic(*a, "OnDynamicTrailerUpdate", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, &ret, amxIndex);

					if(!ret) return false;
				}
			}
			boost::unordered_map<int, Item::SharedVehicle>::iterator p = core->getData()->vehicles.find(i->first);
			if (p != core->getData()->vehicles.end())
			{		
				if (!p->second->touched)
				{
					p->second->touched = true;
					core->getStreamer()->movingVehicles.insert(p->second);
				}
				p->second->lastUpdatedTick = GetTickCount();
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehicleStreamIn", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(forplayerid));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehicleStreamOut", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(forplayerid));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSirenStateChange(int playerid, int vehicleid, bool newstate)
{
	for (boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin(); i != core->getData()->internalVehicles.end(); ++i)
	{
		if (i->second == vehicleid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicVehSirenStateChange", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(newstate));
					amx_Push(*a, static_cast<cell>(i->first));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}