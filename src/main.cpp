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

#include "main.h"

#include "core.h"
#include "natives.h"
#include "utility.h"

#include <boost/scoped_ptr.hpp>

#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include <set>

logprintf_t logprintf;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)
{
	core.reset(new Core);
	sampgdk_initialize_plugin(ppPluginData);
	logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];
	logprintf("\n\n*** Streamer Plugin v%s by Incognito loaded ***\n", PLUGIN_VERSION);
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	core.reset();
	logprintf("\n\n*** Streamer Plugin v%s by Incognito unloaded ***\n", PLUGIN_VERSION);
}

AMX_NATIVE_INFO natives[] =
{
	{ "Streamer_TickRate", Natives::Streamer_TickRate },
	{ "Streamer_MaxItems", Natives::Streamer_MaxItems },
	{ "Streamer_VisibleItems", Natives::Streamer_VisibleItems },
	{ "Streamer_CellDistance", Natives::Streamer_CellDistance },
	{ "Streamer_CellSize", Natives::Streamer_CellSize },
	{ "Streamer_ProcessActiveItems", Natives::Streamer_ProcessActiveItems },
	{ "Streamer_ToggleIdleUpdate", Natives::Streamer_ToggleIdleUpdate },
	{ "Streamer_ToggleItemUpdate", Natives::Streamer_ToggleItemUpdate },
	{ "Streamer_Update", Natives::Streamer_Update },
	{ "Streamer_UpdateEx", Natives::Streamer_UpdateEx },
	{ "Streamer_GetFloatData", Natives::Streamer_GetFloatData },
	{ "Streamer_SetFloatData", Natives::Streamer_SetFloatData },
	{ "Streamer_GetIntData", Natives::Streamer_GetIntData },
	{ "Streamer_SetIntData", Natives::Streamer_SetIntData },
	{ "Streamer_GetArrayData", Natives::Streamer_GetArrayData },
	{ "Streamer_SetArrayData", Natives::Streamer_SetArrayData },
	{ "Streamer_IsInArrayData", Natives::Streamer_IsInArrayData },
	{ "Streamer_AppendArrayData", Natives::Streamer_AppendArrayData },
	{ "Streamer_RemoveArrayData", Natives::Streamer_RemoveArrayData },
	{ "Streamer_GetUpperBound", Natives::Streamer_GetUpperBound },
	{ "Streamer_GetDistanceToItem", Natives::Streamer_GetDistanceToItem },
	{ "Streamer_IsItemVisible", Natives::Streamer_IsItemVisible },
	{ "Streamer_CountVisibleItems", Natives::Streamer_CountVisibleItems },
	{ "Streamer_DestroyAllVisibleItems", Natives::Streamer_DestroyAllVisibleItems },
	{ "CreateDynamicObject", Natives::CreateDynamicObject },
	{ "DestroyDynamicObject", Natives::DestroyDynamicObject },
	{ "IsValidDynamicObject", Natives::IsValidDynamicObject },
	{ "SetDynamicObjectPos", Natives::SetDynamicObjectPos },
	{ "GetDynamicObjectPos", Natives::GetDynamicObjectPos },
	{ "SetDynamicObjectRot", Natives::SetDynamicObjectRot },
	{ "GetDynamicObjectRot", Natives::GetDynamicObjectRot },
	{ "MoveDynamicObject", Natives::MoveDynamicObject },
	{ "StopDynamicObject", Natives::StopDynamicObject },
	{ "IsDynamicObjectMoving", Natives::IsDynamicObjectMoving },
	{ "AttachCameraToDynamicObject", Natives::AttachCameraToDynamicObject },
	{ "AttachDynamicObjectToVehicle", Natives::AttachDynamicObjectToVehicle },
	{ "EditDynamicObject", Natives::EditDynamicObject },
	{ "GetDynamicObjectMaterial", Natives::GetDynamicObjectMaterial },
	{ "SetDynamicObjectMaterial", Natives::SetDynamicObjectMaterial },
	{ "GetDynamicObjectMaterialText", Natives::GetDynamicObjectMaterialText },
	{ "SetDynamicObjectMaterialText", Natives::SetDynamicObjectMaterialText },
	{ "DestroyAllDynamicObjects", Natives::DestroyAllDynamicObjects },
	{ "CountDynamicObjects", Natives::CountDynamicObjects },
	{ "CreateDynamicPickup", Natives::CreateDynamicPickup },
	{ "DestroyDynamicPickup", Natives::DestroyDynamicPickup },
	{ "IsValidDynamicPickup", Natives::IsValidDynamicPickup },
	{ "DestroyAllDynamicPickups", Natives::DestroyAllDynamicPickups },
	{ "CountDynamicPickups", Natives::CountDynamicPickups },
	{ "CreateDynamicCP", Natives::CreateDynamicCP },
	{ "DestroyDynamicCP", Natives::DestroyDynamicCP },
	{ "IsValidDynamicCP", Natives::IsValidDynamicCP },
	{ "TogglePlayerDynamicCP", Natives::TogglePlayerDynamicCP },
	{ "TogglePlayerAllDynamicCPs", Natives::TogglePlayerAllDynamicCPs },
	{ "IsPlayerInDynamicCP", Natives::IsPlayerInDynamicCP },
	{ "GetPlayerVisibleDynamicCP", Natives::GetPlayerVisibleDynamicCP },
	{ "DestroyAllDynamicCPs", Natives::DestroyAllDynamicCPs },
	{ "CountDynamicCPs", Natives::CountDynamicCPs },
	{ "CreateDynamicRaceCP", Natives::CreateDynamicRaceCP },
	{ "DestroyDynamicRaceCP", Natives::DestroyDynamicRaceCP },
	{ "IsValidDynamicRaceCP", Natives::IsValidDynamicRaceCP },
	{ "TogglePlayerDynamicRaceCP", Natives::TogglePlayerDynamicRaceCP },
	{ "TogglePlayerAllDynamicRaceCPs", Natives::TogglePlayerAllDynamicRaceCPs },
	{ "IsPlayerInDynamicRaceCP", Natives::IsPlayerInDynamicRaceCP },
	{ "GetPlayerVisibleDynamicRaceCP", Natives::GetPlayerVisibleDynamicRaceCP },
	{ "DestroyAllDynamicRaceCPs", Natives::DestroyAllDynamicRaceCPs },
	{ "CountDynamicRaceCPs", Natives::CountDynamicRaceCPs },
	{ "CreateDynamicMapIcon", Natives::CreateDynamicMapIcon },
	{ "DestroyDynamicMapIcon", Natives::DestroyDynamicMapIcon },
	{ "IsValidDynamicMapIcon", Natives::IsValidDynamicMapIcon },
	{ "DestroyAllDynamicMapIcons", Natives::DestroyAllDynamicMapIcons },
	{ "CountDynamicMapIcons", Natives::CountDynamicMapIcons },
	{ "CreateDynamic3DTextLabel", Natives::CreateDynamic3DTextLabel },
	{ "DestroyDynamic3DTextLabel", Natives::DestroyDynamic3DTextLabel },
	{ "IsValidDynamic3DTextLabel", Natives::IsValidDynamic3DTextLabel },
	{ "GetDynamic3DTextLabelText", Natives::GetDynamic3DTextLabelText },
	{ "UpdateDynamic3DTextLabelText", Natives::UpdateDynamic3DTextLabelText },
	{ "DestroyAllDynamic3DTextLabels", Natives::DestroyAllDynamic3DTextLabels },
	{ "CountDynamic3DTextLabels", Natives::CountDynamic3DTextLabels },
	{ "CreateDynamicCircle", Natives::CreateDynamicCircle },
	{ "CreateDynamicRectangle", Natives::CreateDynamicRectangle },
	{ "CreateDynamicSphere", Natives::CreateDynamicSphere },
	{ "CreateDynamicCube", Natives::CreateDynamicCube },
	{ "CreateDynamicPolygon", Natives::CreateDynamicPolygon },
	{ "DestroyDynamicArea", Natives::DestroyDynamicArea },
	{ "IsValidDynamicArea", Natives::IsValidDynamicArea },
	{ "TogglePlayerDynamicArea", Natives::TogglePlayerDynamicArea },
	{ "TogglePlayerAllDynamicAreas", Natives::TogglePlayerAllDynamicAreas },
	{ "IsPlayerInDynamicArea", Natives::IsPlayerInDynamicArea },
	{ "IsPlayerInAnyDynamicArea", Natives::IsPlayerInAnyDynamicArea },
	{ "IsPointInDynamicArea", Natives::IsPointInDynamicArea },
	{ "IsPointInAnyDynamicArea", Natives::IsPointInAnyDynamicArea },
	{ "AttachDynamicAreaToObject", Natives::AttachDynamicAreaToObject },
	{ "AttachDynamicAreaToPlayer", Natives::AttachDynamicAreaToPlayer },
	{ "AttachDynamicAreaToVehicle", Natives::AttachDynamicAreaToVehicle },
	{ "DestroyAllDynamicAreas", Natives::DestroyAllDynamicAreas },
	{ "CountDynamicAreas", Natives::CountDynamicAreas },
	{ "CreateDynamicObjectEx", Natives::CreateDynamicObjectEx },
	{ "CreateDynamicPickupEx", Natives::CreateDynamicPickupEx },
	{ "CreateDynamicCPEx", Natives::CreateDynamicCPEx },
	{ "CreateDynamicRaceCPEx", Natives::CreateDynamicRaceCPEx },
	{ "CreateDynamicMapIconEx", Natives::CreateDynamicMapIconEx },
	{ "CreateDynamic3DTextLabelEx", Natives::CreateDynamic3DTextLabelEx },
	{ "CreateDynamicCircleEx", Natives::CreateDynamicCircleEx },
	{ "CreateDynamicRectangleEx", Natives::CreateDynamicRectangleEx },
	{ "CreateDynamicSphereEx", Natives::CreateDynamicSphereEx },
	{ "CreateDynamicCubeEx", Natives::CreateDynamicCubeEx },
	{ "CreateDynamicPolygonEx", Natives::CreateDynamicPolygonEx },
	{ "Streamer_CallbackHook", Natives::Streamer_CallbackHook },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	core->getData()->interfaces.insert(amx);
	return Utility::checkInterfaceAndRegisterNatives(amx, natives);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	core->getData()->interfaces.erase(amx);
	Utility::destroyAllItemsInInterface(amx);
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	core->getStreamer()->startAutomaticUpdate();
}
