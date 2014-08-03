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

#include "callbacks.h"

#include "core.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <set>

bool Callbacks::OnPlayerConnect(int playerid)
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

bool Callbacks::OnPlayerDisconnect(int playerid, int reason)
{
	core->getData()->players.erase(playerid);
	return true;
}

bool Callbacks::OnPlayerEnterCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint != p->second.visibleCheckpoint)
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(p->second.activeCheckpoint);
			if (c != core->getData()->checkpoints.end())
			{
				if (c->second->amx != interface)
				{
					return true;
				}
			}
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

bool Callbacks::OnPlayerLeaveCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint == p->second.visibleCheckpoint)
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(p->second.activeCheckpoint);
			if (c != core->getData()->checkpoints.end())
			{
				if (c->second->amx != interface)
				{
					return true;
				}
			}
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

bool Callbacks::OnPlayerEnterRaceCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint != p->second.visibleRaceCheckpoint)
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(p->second.activeRaceCheckpoint);
			if (r != core->getData()->raceCheckpoints.end())
			{
				if (r->second->amx != interface)
				{
					return true;
				}
			}
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

bool Callbacks::OnPlayerLeaveRaceCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint == p->second.visibleRaceCheckpoint)
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(p->second.activeRaceCheckpoint);
			if (r != core->getData()->raceCheckpoints.end())
			{
				if (r->second->amx != interface)
				{
					return true;
				}
			}
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

bool Callbacks::OnPlayerPickUpPickup(int playerid, int pickupid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.begin(); i != core->getStreamer()->internalPickups.end(); ++i)
	{
		if (i->second == pickupid)
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(i->first);
			if (p != core->getData()->pickups.end())
			{
				if (p->second->amx != interface)
				{
					break;
				}
			}
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

bool Callbacks::OnPlayerEditObject(int playerid, int playerobject, int objectid, int response, float x, float y, float z, float rx, float ry, float rz)
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
						amx_Push(*a, amx_ftoc(rz));
						amx_Push(*a, amx_ftoc(ry));
						amx_Push(*a, amx_ftoc(rx));
						amx_Push(*a, amx_ftoc(z));
						amx_Push(*a, amx_ftoc(y));
						amx_Push(*a, amx_ftoc(x));
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
	return true;
}

bool Callbacks::OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z)
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
	return true;
}

bool Callbacks::OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float x, float y, float z)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
		{
			if (i->second == hitid)
			{
				boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(i->first);
				if (o != core->getData()->objects.end())
				{
					if (o->second->amx != interface)
					{
						break;
					}
				}
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
	return true;
}
