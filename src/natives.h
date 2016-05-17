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

#ifndef NATIVES_H
#define NATIVES_H

#define STREAMER_OPC (0)
#define STREAMER_OPDC (1)
#define STREAMER_OPEO (2)
#define STREAMER_OPSO (3)
#define STREAMER_OPPP (4)
#define STREAMER_OPEC (5)
#define STREAMER_OPLC (6)
#define STREAMER_OPERC (7)
#define STREAMER_OPLRC (8)
#define STREAMER_OPWS (9)

#include "common.h"
#include "utility.h"

#define CHECK_PARAMS(m, n) \
	if (params[0] != (m * 4)) \
	{ \
		Utility::logError("%s: Expecting %d parameter(s), but found %d", n, m, params[0] / sizeof(cell)); \
		return 0; \
	}

namespace Natives
{
	// Settings
	cell AMX_NATIVE_CALL Streamer_GetTickRate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetTickRate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetMaxItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetMaxItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetVisibleItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetVisibleItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetRadiusMultiplier(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetRadiusMultiplier(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetTypePriority(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetTypePriority(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetCellDistance(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetCellDistance(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetCellSize(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetCellSize(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleStaticItem(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsToggleStaticItem(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleErrorCallback(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsToggleErrorCallback(AMX *amx, cell *params);
	// Updates
	cell AMX_NATIVE_CALL Streamer_ProcessActiveItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleIdleUpdate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsToggleIdleUpdate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleCameraUpdate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsToggleCameraUpdate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleItemUpdate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsToggleItemUpdate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_Update(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_UpdateEx(AMX *amx, cell *params);
	// Data Manipulation
	cell AMX_NATIVE_CALL Streamer_GetFloatData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetFloatData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetIntData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetIntData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsInArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_AppendArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_RemoveArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetUpperBound(AMX *amx, cell *params);
	// Miscellaneous
	cell AMX_NATIVE_CALL Streamer_GetDistanceToItem(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleItem(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsToggleItem(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleAllItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetItemInternalID(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetItemStreamerID(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsItemVisible(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_DestroyAllVisibleItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_CountVisibleItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_DestroyAllItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_CountItems(AMX *amx, cell *params);
	// Objects
	cell AMX_NATIVE_CALL CreateDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectPos(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectPos(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectRot(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectRot(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectNoCameraCol(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectNoCameraCol(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL MoveDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL StopDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsDynamicObjectMoving(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachCameraToDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicObjectToObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicObjectToPlayer(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicObjectToVehicle(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL EditDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsDynamicObjectMaterialUsed(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectMaterial(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectMaterial(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsDynamicObjectMaterialTextUsed(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectMaterialText(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectMaterialText(AMX *amx, cell *params);
	// Pickups
	cell AMX_NATIVE_CALL CreateDynamicPickup(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicPickup(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicPickup(AMX *amx, cell *params);
	// Checkpoints
	cell AMX_NATIVE_CALL CreateDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPlayerInDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetPlayerVisibleDynamicCP(AMX *amx, cell *params);
	// Race Checkpoints
	cell AMX_NATIVE_CALL CreateDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPlayerInDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetPlayerVisibleDynamicRaceCP(AMX *amx, cell *params);
	// Map Icons
	cell AMX_NATIVE_CALL CreateDynamicMapIcon(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicMapIcon(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicMapIcon(AMX *amx, cell *params);
	// 3D Text Labels
	cell AMX_NATIVE_CALL CreateDynamic3DTextLabel(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamic3DTextLabel(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamic3DTextLabel(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamic3DTextLabelText(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL UpdateDynamic3DTextLabelText(AMX *amx, cell *params);
	// Areas
	cell AMX_NATIVE_CALL CreateDynamicCircle(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCylinder(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicSphere(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicRectangle(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCuboid(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicPolygon(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicPolygonPoints(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicPolygonNumberPoints(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPlayerInDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPlayerInAnyDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsAnyPlayerInDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsAnyPlayerInAnyDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetPlayerDynamicAreas(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetPlayerNumberDynamicAreas(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPointInDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPointInAnyDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsLineInDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsLineInAnyDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicAreasForPoint(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetNumberDynamicAreasForPoint(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicAreasForLine(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetNumberDynamicAreasForLine(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicAreaToObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicAreaToPlayer(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicAreaToVehicle(AMX *amx, cell *params);
	// Extended
	cell AMX_NATIVE_CALL CreateDynamicObjectEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicPickupEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCPEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicRaceCPEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicMapIconEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamic3DTextLabelEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCircleEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCylinderEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicSphereEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicRectangleEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCuboidEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicPolygonEx(AMX *amx, cell *params);
	// Internal
	cell AMX_NATIVE_CALL Streamer_CallbackHook(AMX *amx, cell *params);
	// Deprecated
	cell AMX_NATIVE_CALL DestroyAllDynamicObjects(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicObjects(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicPickups(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicPickups(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicRaceCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicRaceCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicMapIcons(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicMapIcons(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamic3DTextLabels(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamic3DTextLabels(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicAreas(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicAreas(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerAllDynamicCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerAllDynamicRaceCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerAllDynamicAreas(AMX *amx, cell *params);
}

#endif
