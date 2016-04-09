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
#include "../utility.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::CreateDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(11, "CreateDynamicMapIcon");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_MAP_ICON) == core->getData()->mapIcons.size())
	{
		return 0;
	}
	int mapIconID = Item::MapIcon::identifier.get();
	Item::SharedMapIcon mapIcon(new Item::MapIcon);
	mapIcon->amx = amx;
	mapIcon->mapIconID = mapIconID;
	mapIcon->originalStreamDistance = -1.0f;
	mapIcon->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	mapIcon->type = static_cast<int>(params[4]);
	mapIcon->color = static_cast<int>(params[5]);
	Utility::addToContainer(mapIcon->worlds, static_cast<int>(params[6]));
	Utility::addToContainer(mapIcon->interiors, static_cast<int>(params[7]));
	Utility::addToContainer(mapIcon->players, static_cast<int>(params[8]));
	mapIcon->streamDistance = amx_ctof(params[9]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[9]) : amx_ctof(params[9]) * amx_ctof(params[9]);
	mapIcon->style = static_cast<int>(params[10]);
	Utility::addToContainer(mapIcon->areas, static_cast<int>(params[11]));
	core->getGrid()->addMapIcon(mapIcon);
	core->getData()->mapIcons.insert(std::make_pair(mapIconID, mapIcon));
	return static_cast<cell>(mapIconID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicMapIcon");
	boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[1]));
	if (m != core->getData()->mapIcons.end())
	{
		Utility::destroyMapIcon(m);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicMapIcon");
	boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[1]));
	if (m != core->getData()->mapIcons.end())
	{
		return 1;
	}
	return 0;
}
