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

#include "../natives.h"

#include "../core.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <Eigen/Core>

#include <bitset>

cell AMX_NATIVE_CALL Natives::Streamer_ProcessActiveItems(AMX *amx, cell *params)
{
	core->getStreamer()->processActiveItems();
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleIdleUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_ToggleIdleUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.updateWhenIdle = static_cast<int>(params[2]) != 0;
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleIdleUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_IsToggleIdleUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return static_cast<cell>(p->second.updateWhenIdle != 0);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleCameraUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_ToggleCameraUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.updateUsingCameraPosition = static_cast<int>(params[2]) != 0;
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleCameraUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_IsToggleCameraUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		return static_cast<cell>(p->second.updateUsingCameraPosition != 0);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleItemUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_ToggleItemUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (static_cast<int>(params[2]) >= 0 && static_cast<int>(params[2]) < STREAMER_MAX_TYPES)
		{
			p->second.enabledItems.set(static_cast<size_t>(params[2]), params[3] != 0);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleItemUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_IsToggleItemUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (static_cast<int>(params[2]) >= 0 && static_cast<int>(params[2]) < STREAMER_MAX_TYPES)
		{
			return static_cast<cell>(p->second.enabledItems.test(params[2]) != 0);
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetLastUpdateTime(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetLastUpdateTime");
	Utility::storeFloatInNative(amx, params[1], core->getStreamer()->getLastUpdateTime());
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_Update(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_Update");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.interiorId = sampgdk::GetPlayerInterior(p->first);
		p->second.worldId = sampgdk::GetPlayerVirtualWorld(p->first);
		sampgdk::GetPlayerPos(p->first, &p->second.position[0], &p->second.position[1], &p->second.position[2]);
		core->getStreamer()->startManualUpdate(p->second, static_cast<int>(params[2]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_UpdateEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "Streamer_UpdateEx");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		if (static_cast<int>(params[5]) >= 0)
		{
			p->second.worldId = static_cast<int>(params[5]);
		}
		else
		{
			p->second.worldId = sampgdk::GetPlayerVirtualWorld(p->first);
		}
		if (static_cast<int>(params[6]) >= 0)
		{
			p->second.interiorId = static_cast<int>(params[6]);
		}
		else
		{
			p->second.interiorId = sampgdk::GetPlayerInterior(p->first);
		}
		if (static_cast<int>(params[8]) >= 0)
		{
			sampgdk::SetPlayerPos(p->first, p->second.position[0], p->second.position[1], p->second.position[2]);
			if (static_cast<int>(params[9]))
			{
				sampgdk::TogglePlayerControllable(p->first, false);
			}
			p->second.delayedUpdate = true;
			p->second.delayedUpdateType = static_cast<int>(params[7]);
			p->second.delayedUpdateTime = boost::chrono::steady_clock::now() + boost::chrono::milliseconds(static_cast<int>(params[8]));
			p->second.delayedUpdateFreeze = static_cast<int>(params[9]) != 0;
		}
		core->getStreamer()->startManualUpdate(p->second, static_cast<int>(params[7]));
		return 1;
	}
	return 0;
}
