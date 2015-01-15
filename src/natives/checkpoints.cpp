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

cell AMX_NATIVE_CALL Natives::CreateDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "CreateDynamicCP");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_CP) == core->getData()->checkpoints.size())
	{
		return 0;
	}
	int checkpointID = Item::Checkpoint::identifier.get();
	Item::SharedCheckpoint checkpoint(new Item::Checkpoint);
	checkpoint->amx = amx;
	checkpoint->checkpointID = checkpointID;
	checkpoint->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	checkpoint->size = amx_ctof(params[4]);
	Utility::addToContainer(checkpoint->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(checkpoint->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(checkpoint->players, static_cast<int>(params[7]));
	checkpoint->streamDistance = amx_ctof(params[8]) * amx_ctof(params[8]);
	core->getGrid()->addCheckpoint(checkpoint);
	core->getData()->checkpoints.insert(std::make_pair(checkpointID, checkpoint));
	return static_cast<cell>(checkpointID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicCP");
	boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[1]));
	if (c != core->getData()->checkpoints.end())
	{
		Utility::destroyCheckpoint(c);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicCP");
	boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[1]));
	if (c != core->getData()->checkpoints.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledCheckpoints.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledCheckpoints.end())
			{
				p->second.disabledCheckpoints.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledCheckpoints.end())
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[2]))
				{
					DisablePlayerCheckpoint(p->first);
					p->second.activeCheckpoint = 0;
					p->second.visibleCheckpoint = 0;
				}
				p->second.disabledCheckpoints.insert(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicCPs(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicCPs");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledCheckpoints.clear();
		if (!static_cast<int>(params[2]))
		{
			if (p->second.visibleCheckpoint != 0)
			{
				DisablePlayerCheckpoint(p->first);
				p->second.activeCheckpoint = 0;
				p->second.visibleCheckpoint = 0;
			}
			for (boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
			{
				p->second.disabledCheckpoints.insert(c->first);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInDynamicCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint == static_cast<int>(params[2]))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetPlayerVisibleDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetPlayerVisibleDynamicCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return p->second.visibleCheckpoint;
	}
	return 0;
}
