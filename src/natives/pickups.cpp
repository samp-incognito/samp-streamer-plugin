/*
 * Copyright (C) 2016 Incognito
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

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::CreateDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicPickup");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_PICKUP) == core->getData()->pickups.size())
	{
		return 0;
	}
	int pickupID = Item::Pickup::identifier.get();
	Item::SharedPickup pickup(new Item::Pickup);
	pickup->amx = amx;
	pickup->pickupID = pickupID;
	pickup->originalStreamDistance = -1.0f;
	pickup->modelID = static_cast<int>(params[1]);
	pickup->type = static_cast<int>(params[2]);
	pickup->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	Utility::addToContainer(pickup->worlds, static_cast<int>(params[6]));
	Utility::addToContainer(pickup->interiors, static_cast<int>(params[7]));
	Utility::addToContainer(pickup->players, static_cast<int>(params[8]));
	pickup->streamDistance = amx_ctof(params[9]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[9]) : amx_ctof(params[9]) * amx_ctof(params[9]);
	Utility::addToContainer(pickup->areas, static_cast<int>(params[10]));
	core->getGrid()->addPickup(pickup);
	core->getData()->pickups.insert(std::make_pair(pickupID, pickup));
	return static_cast<cell>(pickupID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicPickup");
	boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[1]));
	if (p != core->getData()->pickups.end())
	{
		Utility::destroyPickup(p);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicPickup");
	boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[1]));
	if (p != core->getData()->pickups.end())
	{
		return 1;
	}
	return 0;
}
