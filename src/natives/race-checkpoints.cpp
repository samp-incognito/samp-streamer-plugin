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
#include <boost/unordered_set.hpp>

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::CreateDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicRaceCP");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_RACE_CP) == core->getData()->raceCheckpoints.size())
	{
		return 0;
	}
	int raceCheckpointID = Item::RaceCheckpoint::identifier.get();
	Item::SharedRaceCheckpoint raceCheckpoint(new Item::RaceCheckpoint);
	raceCheckpoint->amx = amx;
	raceCheckpoint->raceCheckpointID = raceCheckpointID;
	raceCheckpoint->type = static_cast<int>(params[1]);
	raceCheckpoint->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	raceCheckpoint->next = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	raceCheckpoint->size = amx_ctof(params[8]);
	Utility::addToContainer(raceCheckpoint->worlds, static_cast<int>(params[9]));
	Utility::addToContainer(raceCheckpoint->interiors, static_cast<int>(params[10]));
	Utility::addToContainer(raceCheckpoint->players, static_cast<int>(params[11]));
	raceCheckpoint->streamDistance = amx_ctof(params[12]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[12]) : amx_ctof(params[12]) * amx_ctof(params[12]);
	core->getGrid()->addRaceCheckpoint(raceCheckpoint);
	core->getData()->raceCheckpoints.insert(std::make_pair(raceCheckpointID, raceCheckpoint));
	return static_cast<cell>(raceCheckpointID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicRaceCP");
	boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[1]));
	if (r != core->getData()->raceCheckpoints.end())
	{
		Utility::destroyRaceCheckpoint(r);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicRaceCP");
	boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[1]));
	if (r != core->getData()->raceCheckpoints.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicRaceCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledRaceCheckpoints.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledRaceCheckpoints.end())
			{
				p->second.disabledRaceCheckpoints.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledRaceCheckpoints.end())
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[2]))
				{
					DisablePlayerRaceCheckpoint(p->first);
					p->second.activeRaceCheckpoint = 0;
					p->second.visibleRaceCheckpoint = 0;
				}
				p->second.disabledRaceCheckpoints.insert(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicRaceCPs(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicRaceCPs");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledRaceCheckpoints.clear();
		if (!static_cast<int>(params[2]))
		{
			if (p->second.visibleRaceCheckpoint != 0)
			{
				DisablePlayerRaceCheckpoint(p->first);
				p->second.activeRaceCheckpoint = 0;
				p->second.visibleRaceCheckpoint = 0;
			}
			for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
			{
				p->second.disabledRaceCheckpoints.insert(r->first);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInDynamicRaceCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint == static_cast<int>(params[2]))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerVisibleDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetPlayerVisibleDynamicRaceCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return p->second.visibleRaceCheckpoint;
	}
	return 0;
}
