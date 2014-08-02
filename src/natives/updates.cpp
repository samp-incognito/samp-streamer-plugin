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

#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <Eigen/Core>

#include <sampgdk/sampgdk.h>

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

cell AMX_NATIVE_CALL Natives::Streamer_ToggleItemUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_ToggleItemUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (static_cast<size_t>(params[2]) >= 0 && static_cast<size_t>(params[2]) < STREAMER_MAX_TYPES)
		{
			p->second.enabledItems.set(static_cast<size_t>(params[2]), static_cast<int>(params[3]) != 0);
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
		if (static_cast<size_t>(params[2]) >= 0 && static_cast<size_t>(params[2]) < STREAMER_MAX_TYPES)
		{
			return static_cast<cell>(p->second.enabledItems.test(params[2]) != 0);
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_Update(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_Update");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		core->getStreamer()->startManualUpdate(p->second, true);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_UpdateEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(6, "Streamer_UpdateEx");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		if (static_cast<int>(params[5]) >= 0)
		{
			p->second.worldID = static_cast<int>(params[5]);
		}
		else
		{
			p->second.worldID = GetPlayerVirtualWorld(p->first);
		}
		if (static_cast<int>(params[6]) >= 0)
		{
			p->second.interiorID = static_cast<int>(params[6]);
		}
		else
		{
			p->second.interiorID = GetPlayerInterior(p->first);
		}
		core->getStreamer()->startManualUpdate(p->second, false);
		return 1;
	}
	return 0;
}
