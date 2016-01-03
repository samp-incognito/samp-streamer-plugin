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

#include <boost/scoped_ptr.hpp>

cell AMX_NATIVE_CALL Natives::Streamer_CallbackHook(AMX *amx, cell *params)
{
	return 0;
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicObjects(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_OBJECT, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicObjects(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_OBJECT, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicPickups(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_PICKUP, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicPickups(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_PICKUP, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicCPs(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_CP, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicCPs(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_CP, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicRaceCPs(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_RACE_CP, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicRaceCPs(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_RACE_CP, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicMapIcons(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_MAP_ICON, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicMapIcons(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_MAP_ICON, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamic3DTextLabels(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_3D_TEXT_LABEL, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamic3DTextLabels(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_3D_TEXT_LABEL, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicAreas(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_AREA, 1 };
	return Natives::Streamer_DestroyAllItems(amx, newParams);
}

cell AMX_NATIVE_CALL Natives::CountDynamicAreas(AMX *amx, cell *params)
{
	cell newParams[3] = { sizeof(cell) * 2, STREAMER_TYPE_AREA, 1 };
	return Natives::Streamer_CountItems(amx, newParams);
}
