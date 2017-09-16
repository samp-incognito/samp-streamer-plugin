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
	{ "Streamer_GetPlayerTickRate", Natives::Streamer_GetPlayerTickRate },
	{ "Streamer_SetPlayerTickRate", Natives::Streamer_SetPlayerTickRate },
	{ "Streamer_ToggleChunkStream", Natives::Streamer_ToggleChunkStream },
	{ "Streamer_IsToggleChunkStream", Natives::Streamer_IsToggleChunkStream },
	{ "Streamer_GetChunkTickRate", Natives::Streamer_GetChunkTickRate },
	{ "Streamer_SetChunkTickRate", Natives::Streamer_SetChunkTickRate },
	{ "Streamer_GetChunkSize", Natives::Streamer_GetChunkSize },
	{ "Streamer_SetChunkSize", Natives::Streamer_SetChunkSize },
	{ "Streamer_GetMaxItems", Natives::Streamer_GetMaxItems },
	{ "Streamer_SetMaxItems", Natives::Streamer_SetMaxItems },
	{ "Streamer_GetVisibleItems", Natives::Streamer_GetVisibleItems },
	{ "Streamer_SetVisibleItems", Natives::Streamer_SetVisibleItems },
	{ "Streamer_GetRadiusMultiplier", Natives::Streamer_GetRadiusMultiplier },
	{ "Streamer_SetRadiusMultiplier", Natives::Streamer_SetRadiusMultiplier },
	{ "Streamer_GetTypePriority", Natives::Streamer_GetTypePriority },
	{ "Streamer_SetTypePriority", Natives::Streamer_SetTypePriority },
	{ "Streamer_GetCellDistance", Natives::Streamer_GetCellDistance },
	{ "Streamer_SetCellDistance", Natives::Streamer_SetCellDistance },
	{ "Streamer_GetCellSize", Natives::Streamer_GetCellSize },
	{ "Streamer_SetCellSize", Natives::Streamer_SetCellSize },
	{ "Streamer_ToggleItemStatic", Natives::Streamer_ToggleItemStatic },
	{ "Streamer_IsToggleItemStatic", Natives::Streamer_IsToggleItemStatic },
	{ "Streamer_ToggleItemInvAreas", Natives::Streamer_ToggleItemInvAreas },
	{ "Streamer_IsToggleItemInvAreas", Natives::Streamer_IsToggleItemInvAreas },
	{ "Streamer_ToggleItemCallbacks", Natives::Streamer_ToggleItemCallbacks },
	{ "Streamer_IsToggleItemCallbacks", Natives::Streamer_IsToggleItemCallbacks },
	{ "Streamer_ToggleErrorCallback", Natives::Streamer_ToggleErrorCallback },
	{ "Streamer_IsToggleErrorCallback", Natives::Streamer_IsToggleErrorCallback },
	// Updates
	{ "Streamer_ProcessActiveItems", Natives::Streamer_ProcessActiveItems },
	{ "Streamer_ToggleIdleUpdate", Natives::Streamer_ToggleIdleUpdate },
	{ "Streamer_IsToggleIdleUpdate", Natives::Streamer_IsToggleIdleUpdate },
	{ "Streamer_ToggleCameraUpdate", Natives::Streamer_ToggleCameraUpdate },
	{ "Streamer_IsToggleCameraUpdate", Natives::Streamer_IsToggleCameraUpdate },
	{ "Streamer_ToggleItemUpdate", Natives::Streamer_ToggleItemUpdate },
	{ "Streamer_IsToggleItemUpdate", Natives::Streamer_IsToggleItemUpdate },
	{ "Streamer_GetLastUpdateTime", Natives::Streamer_GetLastUpdateTime },
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
	{ "Streamer_ToggleItem", Natives::Streamer_ToggleItem },
	{ "Streamer_IsToggleItem", Natives::Streamer_IsToggleItem },
	{ "Streamer_ToggleAllItems", Natives::Streamer_ToggleAllItems },
	{ "Streamer_GetItemInternalID", Natives::Streamer_GetItemInternalID },
	{ "Streamer_GetItemStreamerID", Natives::Streamer_GetItemStreamerID },
	{ "Streamer_IsItemVisible", Natives::Streamer_IsItemVisible },
	{ "Streamer_DestroyAllVisibleItems", Natives::Streamer_DestroyAllVisibleItems },
	{ "Streamer_CountVisibleItems", Natives::Streamer_CountVisibleItems },
	{ "Streamer_DestroyAllItems", Natives::Streamer_DestroyAllItems },
	{ "Streamer_CountItems", Natives::Streamer_CountItems },
	{ "Streamer_GetNearbyItems", Natives::Streamer_GetNearbyItems },
	{ "Streamer_GetAllVisibleItems", Natives::Streamer_GetAllVisibleItems },
	{ "Streamer_GetItemOffset", Natives::Streamer_GetItemOffset },
	{ "Streamer_SetItemOffset", Natives::Streamer_SetItemOffset },
	// Objects
	{ "CreateDynamicObject", Natives::CreateDynamicObject },
	{ "DestroyDynamicObject", Natives::DestroyDynamicObject },
	{ "IsValidDynamicObject", Natives::IsValidDynamicObject },
	{ "GetDynamicObjectPos", Natives::GetDynamicObjectPos },
	{ "SetDynamicObjectPos", Natives::SetDynamicObjectPos },
	{ "GetDynamicObjectRot", Natives::GetDynamicObjectRot },
	{ "SetDynamicObjectRot", Natives::SetDynamicObjectRot },
	{ "GetDynamicObjectNoCameraCol", Natives::GetDynamicObjectNoCameraCol },
	{ "SetDynamicObjectNoCameraCol", Natives::SetDynamicObjectNoCameraCol },
	{ "MoveDynamicObject", Natives::MoveDynamicObject },
	{ "StopDynamicObject", Natives::StopDynamicObject },
	{ "IsDynamicObjectMoving", Natives::IsDynamicObjectMoving },
	{ "AttachCameraToDynamicObject", Natives::AttachCameraToDynamicObject },
	{ "AttachDynamicObjectToObject", Natives::AttachDynamicObjectToObject },
	{ "AttachDynamicObjectToPlayer", Natives::AttachDynamicObjectToPlayer },
	{ "AttachDynamicObjectToVehicle", Natives::AttachDynamicObjectToVehicle },
	{ "EditDynamicObject", Natives::EditDynamicObject },
	{ "IsDynamicObjectMaterialUsed", Natives::IsDynamicObjectMaterialUsed },
	{ "GetDynamicObjectMaterial", Natives::GetDynamicObjectMaterial },
	{ "SetDynamicObjectMaterial", Natives::SetDynamicObjectMaterial },
	{ "IsDynamicObjectMaterialTextUsed", Natives::IsDynamicObjectMaterialTextUsed },
	{ "GetDynamicObjectMaterialText", Natives::GetDynamicObjectMaterialText },
	{ "SetDynamicObjectMaterialText", Natives::SetDynamicObjectMaterialText },
	{ "GetPlayerCameraTargetDynObject", Natives::GetPlayerCameraTargetDynObject },
	// Pickups
	{ "CreateDynamicPickup", Natives::CreateDynamicPickup },
	{ "DestroyDynamicPickup", Natives::DestroyDynamicPickup },
	{ "IsValidDynamicPickup", Natives::IsValidDynamicPickup },
	// Checkpoints
	{ "CreateDynamicCP", Natives::CreateDynamicCP },
	{ "DestroyDynamicCP", Natives::DestroyDynamicCP },
	{ "IsValidDynamicCP", Natives::IsValidDynamicCP },
	{ "IsPlayerInDynamicCP", Natives::IsPlayerInDynamicCP },
	{ "GetPlayerVisibleDynamicCP", Natives::GetPlayerVisibleDynamicCP },
	// Race Checkpoints
	{ "CreateDynamicRaceCP", Natives::CreateDynamicRaceCP },
	{ "DestroyDynamicRaceCP", Natives::DestroyDynamicRaceCP },
	{ "IsValidDynamicRaceCP", Natives::IsValidDynamicRaceCP },
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
	{ "IsPlayerInDynamicArea", Natives::IsPlayerInDynamicArea },
	{ "IsPlayerInAnyDynamicArea", Natives::IsPlayerInAnyDynamicArea },
	{ "IsAnyPlayerInDynamicArea", Natives::IsAnyPlayerInDynamicArea },
	{ "IsAnyPlayerInAnyDynamicArea", Natives::IsAnyPlayerInAnyDynamicArea },
	{ "GetPlayerDynamicAreas", Natives::GetPlayerDynamicAreas },
	{ "GetPlayerNumberDynamicAreas", Natives::GetPlayerNumberDynamicAreas },
	{ "IsPointInDynamicArea", Natives::IsPointInDynamicArea },
	{ "IsPointInAnyDynamicArea", Natives::IsPointInAnyDynamicArea },
	{ "IsLineInDynamicArea", Natives::IsLineInDynamicArea },
	{ "IsLineInAnyDynamicArea", Natives::IsLineInAnyDynamicArea },
	{ "GetDynamicAreasForPoint", Natives::GetDynamicAreasForPoint },
	{ "GetNumberDynamicAreasForPoint", Natives::GetNumberDynamicAreasForPoint },
	{ "GetDynamicAreasForLine", Natives::GetDynamicAreasForLine },
	{ "GetNumberDynamicAreasForLine", Natives::GetNumberDynamicAreasForLine },
	{ "AttachDynamicAreaToObject", Natives::AttachDynamicAreaToObject },
	{ "AttachDynamicAreaToPlayer", Natives::AttachDynamicAreaToPlayer },
	{ "AttachDynamicAreaToVehicle", Natives::AttachDynamicAreaToVehicle },
	{ "ToggleDynAreaSpectateMode", Natives::ToggleDynAreaSpectateMode},
	{ "IsToggleDynAreaSpectateMode", Natives::IsToggleDynAreaSpectateMode },
	// Actors
	{ "CreateDynamicActor", Natives::CreateDynamicActor },
	{ "DestroyDynamicActor", Natives::DestroyDynamicActor },
	{ "IsValidDynamicActor", Natives::IsValidDynamicActor },
	{ "IsDynamicActorStreamedIn", Natives::IsDynamicActorStreamedIn },
	{ "GetDynamicActorVirtualWorld", Natives::GetDynamicActorVirtualWorld },
	{ "SetDynamicActorVirtualWorld", Natives::SetDynamicActorVirtualWorld },
	{ "GetDynamicActorAnimation", Natives::GetDynamicActorAnimation },
	{ "ApplyDynamicActorAnimation", Natives::ApplyDynamicActorAnimation },
	{ "ClearDynamicActorAnimations", Natives::ClearDynamicActorAnimations },
	{ "GetDynamicActorFacingAngle", Natives::GetDynamicActorFacingAngle },
	{ "SetDynamicActorFacingAngle", Natives::SetDynamicActorFacingAngle },
	{ "GetDynamicActorPos", Natives::GetDynamicActorPos },
	{ "SetDynamicActorPos", Natives::SetDynamicActorPos },
	{ "GetDynamicActorHealth", Natives::GetDynamicActorHealth },
	{ "SetDynamicActorHealth", Natives::SetDynamicActorHealth },
	{ "SetDynamicActorInvulnerable", Natives::SetDynamicActorInvulnerable },
	{ "IsDynamicActorInvulnerable", Natives::IsDynamicActorInvulnerable },
	{ "GetPlayerTargetDynamicActor", Natives::GetPlayerTargetDynamicActor },
	{ "GetPlayerCameraTargetDynActor", Natives::GetPlayerCameraTargetDynActor },
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
	{ "CreateDynamicActorEx", Natives::CreateDynamicActorEx },
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
	{ "TogglePlayerDynamicCP", Natives::TogglePlayerDynamicCP },
	{ "TogglePlayerAllDynamicCPs", Natives::TogglePlayerAllDynamicCPs },
	{ "TogglePlayerDynamicRaceCP", Natives::TogglePlayerDynamicRaceCP },
	{ "TogglePlayerAllDynamicRaceCPs", Natives::TogglePlayerAllDynamicRaceCPs },
	{ "TogglePlayerDynamicArea", Natives::TogglePlayerDynamicArea },
	{ "TogglePlayerAllDynamicAreas", Natives::TogglePlayerAllDynamicAreas },
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
