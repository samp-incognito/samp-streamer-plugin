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

#include <boost/scoped_ptr.hpp>

cell AMX_NATIVE_CALL Natives::Streamer_GetTickRate(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getStreamer()->getTickRate());
}

cell AMX_NATIVE_CALL Natives::Streamer_SetTickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_SetTickRate");
	if (static_cast<std::size_t>(params[1]) > 0)
	{
		core->getStreamer()->setTickRate(static_cast<std::size_t>(params[1]));
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetMaxItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetMaxItems");
	return static_cast<cell>(core->getData()->getGlobalMaxItems(static_cast<std::size_t>(params[1])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetMaxItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetMaxItems");
	return static_cast<cell>(core->getData()->setGlobalMaxItems(static_cast<int>(params[1]), static_cast<std::size_t>(params[2])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_GetVisibleItems");
	return static_cast<cell>(Utility::getMaxVisibleItems(static_cast<std::size_t>(params[1]), static_cast<int>(params[2])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_SetVisibleItems");
	return static_cast<cell>(Utility::setMaxVisibleItems(static_cast<int>(params[1]), static_cast<std::size_t>(params[2]), static_cast<int>(params[3])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetRadiusMultiplier(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_GetRadiusMultiplier");
	float radiusMultiplier = Utility::getRadiusMultiplier(static_cast<std::size_t>(params[1]), static_cast<int>(params[3]));
	Utility::storeFloatInNative(amx, params[2], radiusMultiplier);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetRadiusMultiplier(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_SetRadiusMultiplier");
	return static_cast<cell>(Utility::setRadiusMultiplier(static_cast<int>(params[1]), amx_ctof(params[2]), static_cast<int>(params[3])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetTypePriority(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_GetTypePriority");
	return Utility::convertContainerToArray(amx, params[1], params[2], core->getData()->typePriority);
}

cell AMX_NATIVE_CALL Natives::Streamer_SetTypePriority(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetTypePriority");
	return Utility::convertArrayToContainer(amx, params[1], params[2], core->getData()->typePriority);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetCellDistance(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetCellDistance");
	float cellDistance = core->getGrid()->getCellDistance();
	Utility::storeFloatInNative(amx, params[1], cellDistance);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetCellDistance(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_SetCellDistance");
	core->getGrid()->setCellDistance(amx_ctof(params[1]) * amx_ctof(params[1]));
	core->getGrid()->rebuildGrid();
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetCellSize(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetCellSize");
	float cellSize = core->getGrid()->getCellSize();
	Utility::storeFloatInNative(amx, params[1], cellSize);
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_SetCellSize(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_SetCellSize");
	core->getGrid()->setCellSize(amx_ctof(params[1]));
	core->getGrid()->rebuildGrid();
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleErrorCallback(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_ToggleErrorCallback");
	core->getData()->errorCallbackEnabled = static_cast<int>(params[1]) != 0;
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsToggleErrorCallback(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_IsToggleErrorCallback");
	return static_cast<cell>(core->getData()->errorCallbackEnabled != 0);
}
