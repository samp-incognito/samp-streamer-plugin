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

#include <set>

extern void *pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	core.reset(new Core);
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	bool load = sampgdk::Load(ppData);
	sampgdk::logprintf("\n\n*** Streamer Plugin v%s by Incognito loaded ***\n", PLUGIN_VERSION);
	return load;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	core.reset();
	sampgdk::logprintf("\n\n*** Streamer Plugin v%s by Incognito unloaded ***\n", PLUGIN_VERSION);
	sampgdk::Unload();
}

AMX_NATIVE_INFO natives[] =
{
	// Settings
	{ "Streamer_GetTickRate", Natives::Streamer_GetTickRate },
	{ "Streamer_SetTickRate", Natives::Streamer_SetTickRate },
	{ "Streamer_GetMaxItems", Natives::Streamer_GetMaxItems },
	{ "Streamer_SetMaxItems", Natives::Streamer_SetMaxItems },
	{ "Streamer_GetVisibleItems", Natives::Streamer_GetVisibleItems },
	{ "Streamer_SetVisibleItems", Natives::Streamer_SetVisibleItems },
	{ "Streamer_GetCellDistance", Natives::Streamer_GetCellDistance },
	{ "Streamer_SetCellDistance", Natives::Streamer_SetCellDistance },
	{ "Streamer_GetCellSize", Natives::Streamer_GetCellSize },
	{ "Streamer_SetCellSize", Natives::Streamer_SetCellSize },
	// Updates
	{ "Streamer_ProcessActiveItems", Natives::Streamer_ProcessActiveItems },
	{ "Streamer_ToggleIdleUpdate", Natives::Streamer_ToggleIdleUpdate },
	{ "Streamer_IsToggleIdleUpdate", Natives::Streamer_IsToggleIdleUpdate },
	{ "Streamer_ToggleItemUpdate", Natives::Streamer_ToggleItemUpdate },
	{ "Streamer_IsToggleItemUpdate", Natives::Streamer_IsToggleItemUpdate },
	{ "Streamer_Update", Natives::Streamer_Update },
	{ "Streamer_UpdateEx", Natives::Streamer_UpdateEx },
	// Data Manipulation
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
	// Miscellaneous
	{ "Streamer_GetDistanceToItem", Natives::Streamer_GetDistanceToItem },
	{ "Streamer_GetItemInternalID", Natives::Streamer_GetItemInternalID },
	{ "Streamer_GetItemStreamerID", Natives::Streamer_GetItemStreamerID },
	{ "Streamer_IsItemVisible", Natives::Streamer_IsItemVisible },
	{ "Streamer_DestroyAllVisibleItems", Natives::Streamer_DestroyAllVisibleItems },
	{ "Streamer_CountVisibleItems", Natives::Streamer_CountVisibleItems },
	{ "Streamer_DestroyAllItems", Natives::Streamer_DestroyAllItems },
	{ "Streamer_CountItems", Natives::Streamer_CountItems },
	// Objects
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
	{ "AttachDynamicObjectToPlayer", Natives::AttachDynamicObjectToPlayer },
	{ "AttachDynamicObjectToVehicle", Natives::AttachDynamicObjectToVehicle },
	{ "EditDynamicObject", Natives::EditDynamicObject },
	{ "GetDynamicObjectMaterial", Natives::GetDynamicObjectMaterial },
	{ "SetDynamicObjectMaterial", Natives::SetDynamicObjectMaterial },
	{ "GetDynamicObjectMaterialText", Natives::GetDynamicObjectMaterialText },
	{ "SetDynamicObjectMaterialText", Natives::SetDynamicObjectMaterialText },
	// Pickups
	{ "CreateDynamicPickup", Natives::CreateDynamicPickup },
	{ "DestroyDynamicPickup", Natives::DestroyDynamicPickup },
	{ "IsValidDynamicPickup", Natives::IsValidDynamicPickup },
	// Checkpoints
	{ "CreateDynamicCP", Natives::CreateDynamicCP },
	{ "DestroyDynamicCP", Natives::DestroyDynamicCP },
	{ "IsValidDynamicCP", Natives::IsValidDynamicCP },
	{ "TogglePlayerDynamicCP", Natives::TogglePlayerDynamicCP },
	{ "TogglePlayerAllDynamicCPs", Natives::TogglePlayerAllDynamicCPs },
	{ "IsPlayerInDynamicCP", Natives::IsPlayerInDynamicCP },
	{ "GetPlayerVisibleDynamicCP", Natives::GetPlayerVisibleDynamicCP },
	// Race Checkpoints
	{ "CreateDynamicRaceCP", Natives::CreateDynamicRaceCP },
	{ "DestroyDynamicRaceCP", Natives::DestroyDynamicRaceCP },
	{ "IsValidDynamicRaceCP", Natives::IsValidDynamicRaceCP },
	{ "TogglePlayerDynamicRaceCP", Natives::TogglePlayerDynamicRaceCP },
	{ "TogglePlayerAllDynamicRaceCPs", Natives::TogglePlayerAllDynamicRaceCPs },
	{ "IsPlayerInDynamicRaceCP", Natives::IsPlayerInDynamicRaceCP },
	{ "GetPlayerVisibleDynamicRaceCP", Natives::GetPlayerVisibleDynamicRaceCP },
	// Map Icons
	{ "CreateDynamicMapIcon", Natives::CreateDynamicMapIcon },
	{ "DestroyDynamicMapIcon", Natives::DestroyDynamicMapIcon },
	{ "IsValidDynamicMapIcon", Natives::IsValidDynamicMapIcon },
	// 3D Text Labels
	{ "CreateDynamic3DTextLabel", Natives::CreateDynamic3DTextLabel },
	{ "DestroyDynamic3DTextLabel", Natives::DestroyDynamic3DTextLabel },
	{ "IsValidDynamic3DTextLabel", Natives::IsValidDynamic3DTextLabel },
	{ "GetDynamic3DTextLabelText", Natives::GetDynamic3DTextLabelText },
	{ "UpdateDynamic3DTextLabelText", Natives::UpdateDynamic3DTextLabelText },
	// Areas
	{ "CreateDynamicCircle", Natives::CreateDynamicCircle },
	{ "CreateDynamicCylinder", Natives::CreateDynamicCylinder },
	{ "CreateDynamicSphere", Natives::CreateDynamicSphere },
	{ "CreateDynamicRectangle", Natives::CreateDynamicRectangle },
	{ "CreateDynamicCuboid", Natives::CreateDynamicCuboid },
	{ "CreateDynamicCube", Natives::CreateDynamicCuboid },
	{ "CreateDynamicPolygon", Natives::CreateDynamicPolygon },
	{ "DestroyDynamicArea", Natives::DestroyDynamicArea },
	{ "IsValidDynamicArea", Natives::IsValidDynamicArea },
	{ "GetDynamicPolygonPoints", Natives::GetDynamicPolygonPoints },
	{ "GetDynamicPolygonNumberPoints", Natives::GetDynamicPolygonNumberPoints },
	{ "TogglePlayerDynamicArea", Natives::TogglePlayerDynamicArea },
	{ "TogglePlayerAllDynamicAreas", Natives::TogglePlayerAllDynamicAreas },
	{ "IsPlayerInDynamicArea", Natives::IsPlayerInDynamicArea },
	{ "IsPlayerInAnyDynamicArea", Natives::IsPlayerInAnyDynamicArea },
	{ "IsAnyPlayerInDynamicArea", Natives::IsAnyPlayerInDynamicArea },
	{ "IsAnyPlayerInAnyDynamicArea", Natives::IsAnyPlayerInAnyDynamicArea },
	{ "IsPointInDynamicArea", Natives::IsPointInDynamicArea },
	{ "IsPointInAnyDynamicArea", Natives::IsPointInAnyDynamicArea },
	{ "GetPlayerDynamicAreas", Natives::GetPlayerDynamicAreas },
	{ "GetPlayerNumberDynamicAreas", Natives::GetPlayerNumberDynamicAreas },
	{ "AttachDynamicAreaToObject", Natives::AttachDynamicAreaToObject },
	{ "AttachDynamicAreaToPlayer", Natives::AttachDynamicAreaToPlayer },
	{ "AttachDynamicAreaToVehicle", Natives::AttachDynamicAreaToVehicle },
	// Extended
	{ "CreateDynamicObjectEx", Natives::CreateDynamicObjectEx },
	{ "CreateDynamicPickupEx", Natives::CreateDynamicPickupEx },
	{ "CreateDynamicCPEx", Natives::CreateDynamicCPEx },
	{ "CreateDynamicRaceCPEx", Natives::CreateDynamicRaceCPEx },
	{ "CreateDynamicMapIconEx", Natives::CreateDynamicMapIconEx },
	{ "CreateDynamic3DTextLabelEx", Natives::CreateDynamic3DTextLabelEx },
	{ "CreateDynamicCircleEx", Natives::CreateDynamicCircleEx },
	{ "CreateDynamicCylinderEx", Natives::CreateDynamicCylinderEx },
	{ "CreateDynamicSphereEx", Natives::CreateDynamicSphereEx },
	{ "CreateDynamicRectangleEx", Natives::CreateDynamicRectangleEx },
	{ "CreateDynamicCuboidEx", Natives::CreateDynamicCuboidEx },
	{ "CreateDynamicCubeEx", Natives::CreateDynamicCuboidEx },
	{ "CreateDynamicPolygonEx", Natives::CreateDynamicPolygonEx },
	// Deprecated
	{ "Streamer_TickRate", Natives::Streamer_SetTickRate },
	{ "Streamer_MaxItems", Natives::Streamer_SetMaxItems },
	{ "Streamer_VisibleItems", Natives::Streamer_SetVisibleItems },
	{ "Streamer_CellDistance", Natives::Streamer_SetCellDistance },
	{ "Streamer_CellSize", Natives::Streamer_SetCellSize },
	{ "Streamer_CallbackHook", Natives::Streamer_CallbackHook },
	{ "DestroyAllDynamicObjects", Natives::DestroyAllDynamicObjects },
	{ "CountDynamicObjects", Natives::CountDynamicObjects },
	{ "DestroyAllDynamicPickups", Natives::DestroyAllDynamicPickups },
	{ "CountDynamicPickups", Natives::CountDynamicPickups },
	{ "DestroyAllDynamicCPs", Natives::DestroyAllDynamicCPs },
	{ "CountDynamicCPs", Natives::CountDynamicCPs },
	{ "DestroyAllDynamicRaceCPs", Natives::DestroyAllDynamicRaceCPs },
	{ "CountDynamicRaceCPs", Natives::CountDynamicRaceCPs },
	{ "DestroyAllDynamicMapIcons", Natives::DestroyAllDynamicMapIcons },
	{ "CountDynamicMapIcons", Natives::CountDynamicMapIcons },
	{ "DestroyAllDynamic3DTextLabels", Natives::DestroyAllDynamic3DTextLabels },
	{ "CountDynamic3DTextLabels", Natives::CountDynamic3DTextLabels },
	{ "DestroyAllDynamicAreas", Natives::DestroyAllDynamicAreas },
	{ "CountDynamicAreas", Natives::CountDynamicAreas },
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
