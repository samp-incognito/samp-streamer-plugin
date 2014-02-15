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
	return static_cast<cell>(core->getData()->getMaxItems(static_cast<std::size_t>(params[1])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetMaxItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetMaxItems");
	return static_cast<cell>(core->getData()->setMaxItems(static_cast<int>(params[1]), static_cast<int>(params[2])) != 0);
}

cell AMX_NATIVE_CALL Natives::Streamer_GetVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetVisibleItems");
	return static_cast<cell>(core->getStreamer()->getVisibleItems(static_cast<std::size_t>(params[1])));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_SetVisibleItems");
	return static_cast<cell>(core->getStreamer()->setVisibleItems(static_cast<int>(params[1]), static_cast<int>(params[2])) != 0);
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
