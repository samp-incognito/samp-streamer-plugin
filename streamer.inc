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

#include <a_samp>

// Definitions

#define STREAMER_TYPE_OBJECT (0)
#define STREAMER_TYPE_PICKUP (1)
#define STREAMER_TYPE_CP (2)
#define STREAMER_TYPE_RACE_CP (3)
#define STREAMER_TYPE_MAP_ICON (4)
#define STREAMER_TYPE_3D_TEXT_LABEL (5)
#define STREAMER_TYPE_AREA (6)

#define STREAMER_AREA_TYPE_CIRCLE (0)
#define STREAMER_AREA_TYPE_CYLINDER (1)
#define STREAMER_AREA_TYPE_SPHERE (2)
#define STREAMER_AREA_TYPE_RECTANGLE (3)
#define STREAMER_AREA_TYPE_CUBOID (4)
#define STREAMER_AREA_TYPE_POLYGON (5)

#define STREAMER_OBJECT_TYPE_GLOBAL (0)
#define STREAMER_OBJECT_TYPE_PLAYER (1)
#define STREAMER_OBJECT_TYPE_DYNAMIC (2)

#define STREAMER_MAX_TYPES (7)
#define STREAMER_MAX_AREA_TYPES (5)
#define STREAMER_MAX_OBJECT_TYPES (3)

#define INVALID_STREAMER_ID (0)

#if !defined FLOAT_INFINITY
    #define FLOAT_INFINITY (Float:0x7F800000)
#endif

#if !defined STREAMER_ENABLE_TAGS
	#define STREAMER_TAG_OBJECT
	#define STREAMER_TAG_OBJECT_ALT
	#define STREAMER_TAG_PICKUP
	#define STREAMER_TAG_CP
	#define STREAMER_TAG_RACE_CP
	#define STREAMER_TAG_MAP_ICON
	#define STREAMER_TAG_AREA

	#if !defined STREAMER_REMOVE_TEXT3D_TAG
		#if !defined STREAMER_USE_DYNAMIC_TEXT3D_TAG
			#define STREAMER_TAG_3D_TEXT_LABEL Text3D:
			#define STREAMER_ALL_TAGS {Text3D,_}:
		#else
			#define STREAMER_TAG_3D_TEXT_LABEL DynamicText3D:
			#define STREAMER_ALL_TAGS {DynamicText3D,_}:
		#endif
	#else
		#define STREAMER_TAG_3D_TEXT_LABEL
		#define STREAMER_ALL_TAGS
	#endif
#else
	#define STREAMER_TAG_OBJECT DynamicObject:
	#define STREAMER_TAG_OBJECT_ALT {DynamicObject,_}:
	#define STREAMER_TAG_PICKUP DynamicPickup:
	#define STREAMER_TAG_CP DynamicCP:
	#define STREAMER_TAG_RACE_CP DynamicRaceCP:
	#define STREAMER_TAG_MAP_ICON DynamicMapIcon:
	#define STREAMER_TAG_3D_TEXT_LABEL DynamicText3D:
	#define STREAMER_TAG_AREA DynamicArea:

	#define STREAMER_ALL_TAGS {DynamicObject,DynamicPickup,DynamicCP,DynamicRaceCP,DynamicMapIcon,DynamicText3D,DynamicArea,_}:
#endif

#if !defined STREAMER_OBJECT_SD
	#define STREAMER_OBJECT_SD 300.0
#endif
#if !defined STREAMER_OBJECT_DD
	#define STREAMER_OBJECT_DD 0.0
#endif
#if !defined STREAMER_PICKUP_SD
	#define STREAMER_PICKUP_SD 200.0
#endif
#if !defined STREAMER_CP_SD
	#define STREAMER_CP_SD 200.0
#endif
#if !defined STREAMER_RACE_CP_SD
	#define STREAMER_RACE_CP_SD 200.0
#endif
#if !defined STREAMER_MAP_ICON_SD
	#define STREAMER_MAP_ICON_SD 200.0
#endif
#if !defined STREAMER_3D_TEXT_LABEL_SD
	#define STREAMER_3D_TEXT_LABEL_SD 200.0
#endif

// Include File Version

public Streamer_IncludeFileVersion = 0x280001;

#pragma unused Streamer_IncludeFileVersion

// Enumerator

enum
{
	E_STREAMER_AREA_ID,
	E_STREAMER_ATTACHED_OBJECT,
	E_STREAMER_ATTACHED_PLAYER,
	E_STREAMER_ATTACHED_VEHICLE,
	E_STREAMER_ATTACH_OFFSET_X,
	E_STREAMER_ATTACH_OFFSET_Y,
	E_STREAMER_ATTACH_OFFSET_Z,
	E_STREAMER_ATTACH_R_X,
	E_STREAMER_ATTACH_R_Y,
	E_STREAMER_ATTACH_R_Z,
	E_STREAMER_ATTACH_X,
	E_STREAMER_ATTACH_Y,
	E_STREAMER_ATTACH_Z,
	E_STREAMER_COLOR,
	E_STREAMER_DRAW_DISTANCE,
	E_STREAMER_EXTRA_ID,
	E_STREAMER_INTERIOR_ID,
	E_STREAMER_MAX_X,
	E_STREAMER_MAX_Y,
	E_STREAMER_MAX_Z,
	E_STREAMER_MIN_X,
	E_STREAMER_MIN_Y,
	E_STREAMER_MIN_Z,
	E_STREAMER_MODEL_ID,
	E_STREAMER_MOVE_R_X,
	E_STREAMER_MOVE_R_Y,
	E_STREAMER_MOVE_R_Z,
	E_STREAMER_MOVE_SPEED,
	E_STREAMER_MOVE_X,
	E_STREAMER_MOVE_Y,
	E_STREAMER_MOVE_Z,
	E_STREAMER_NEXT_X,
	E_STREAMER_NEXT_Y,
	E_STREAMER_NEXT_Z,
	E_STREAMER_PLAYER_ID,
	E_STREAMER_R_X,
	E_STREAMER_R_Y,
	E_STREAMER_R_Z,
	E_STREAMER_SIZE,
	E_STREAMER_STREAM_DISTANCE,
	E_STREAMER_STYLE,
	E_STREAMER_SYNC_ROTATION,
	E_STREAMER_TEST_LOS,
	E_STREAMER_TYPE,
	E_STREAMER_WORLD_ID,
	E_STREAMER_X,
	E_STREAMER_Y,
	E_STREAMER_Z
}

// Natives (Settings)

native Streamer_GetTickRate();
native Streamer_SetTickRate(rate);
native Streamer_GetMaxItems(type);
native Streamer_SetMaxItems(type, items);
native Streamer_GetVisibleItems(type, playerid = -1);
native Streamer_SetVisibleItems(type, items, playerid = -1);
native Streamer_GetRadiusMultiplier(type, &Float:multiplier, playerid = -1);
native Streamer_SetRadiusMultiplier(type, Float:multiplier, playerid = -1);
native Streamer_GetTypePriority(types[], maxtypes = sizeof types);
native Streamer_SetTypePriority(const types[], maxtypes = sizeof types);
native Streamer_GetCellDistance(&Float:distance);
native Streamer_SetCellDistance(Float:distance);
native Streamer_GetCellSize(&Float:size);
native Streamer_SetCellSize(Float:size);
native Streamer_ToggleErrorCallback(toggle);
native Streamer_IsToggleErrorCallback();

// Natives (Updates)

native Streamer_ProcessActiveItems();
native Streamer_ToggleIdleUpdate(playerid, toggle);
native Streamer_IsToggleIdleUpdate(playerid);
native Streamer_ToggleCameraUpdate(playerid, toggle);
native Streamer_IsToggleCameraUpdate(playerid);
native Streamer_ToggleItemUpdate(playerid, type, toggle);
native Streamer_IsToggleItemUpdate(playerid, type);
native Streamer_Update(playerid, type = -1);
native Streamer_UpdateEx(playerid, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, type = -1);

// Natives (Data Manipulation)

native Streamer_GetFloatData(type, STREAMER_ALL_TAGS id, data, &Float:result);
native Streamer_SetFloatData(type, STREAMER_ALL_TAGS id, data, Float:value);
native Streamer_GetIntData(type, STREAMER_ALL_TAGS id, data);
native Streamer_SetIntData(type, STREAMER_ALL_TAGS id, data, value);
native Streamer_GetArrayData(type, STREAMER_ALL_TAGS id, data, dest[], maxdest = sizeof dest);
native Streamer_SetArrayData(type, STREAMER_ALL_TAGS id, data, const src[], maxsrc = sizeof src);
native Streamer_IsInArrayData(type, STREAMER_ALL_TAGS id, data, value);
native Streamer_AppendArrayData(type, STREAMER_ALL_TAGS id, data, value);
native Streamer_RemoveArrayData(type, STREAMER_ALL_TAGS id, data, value);
native Streamer_GetUpperBound(type);

// Natives (Miscellaneous)

native Streamer_GetDistanceToItem(Float:x, Float:y, Float:z, type, STREAMER_ALL_TAGS id, &Float:distance, dimensions = 3);
native Streamer_ToggleStaticItem(type, STREAMER_ALL_TAGS id, toggle);
native Streamer_IsToggleStaticItem(type, STREAMER_ALL_TAGS id);
native Streamer_GetItemInternalID(playerid, type, STREAMER_ALL_TAGS streamerid);
native Streamer_GetItemStreamerID(playerid, type, internalid);
native Streamer_IsItemVisible(playerid, type, STREAMER_ALL_TAGS id);
native Streamer_DestroyAllVisibleItems(playerid, type, serverwide = 1);
native Streamer_CountVisibleItems(playerid, type, serverwide = 1);
native Streamer_DestroyAllItems(type, serverwide = 1);
native Streamer_CountItems(type, serverwide = 1);

// Natives (Objects)

native STREAMER_TAG_OBJECT CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1);
native DestroyDynamicObject(STREAMER_TAG_OBJECT objectid);
native IsValidDynamicObject(STREAMER_TAG_OBJECT objectid);
native SetDynamicObjectPos(STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z);
native GetDynamicObjectPos(STREAMER_TAG_OBJECT objectid, &Float:x, &Float:y, &Float:z);
native SetDynamicObjectRot(STREAMER_TAG_OBJECT objectid, Float:rx, Float:ry, Float:rz);
native GetDynamicObjectRot(STREAMER_TAG_OBJECT objectid, &Float:rx, &Float:ry, &Float:rz);
native SetDynamicObjectNoCameraCol(STREAMER_TAG_OBJECT objectid);
native GetDynamicObjectNoCameraCol(STREAMER_TAG_OBJECT objectid);
native MoveDynamicObject(STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z, Float:speed, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0);
native StopDynamicObject(STREAMER_TAG_OBJECT objectid);
native IsDynamicObjectMoving(STREAMER_TAG_OBJECT objectid);
native AttachCameraToDynamicObject(playerid, STREAMER_TAG_OBJECT objectid);
native AttachDynamicObjectToObject(STREAMER_TAG_OBJECT objectid, attachtoid, Float:offsetx, Float:offsety, Float:offsetz, Float:rx, Float:ry, Float:rz, syncrotation = 1);
native AttachDynamicObjectToPlayer(STREAMER_TAG_OBJECT objectid, playerid, Float:offsetx, Float:offsety, Float:offsetz, Float:rx, Float:ry, Float:rz);
native AttachDynamicObjectToVehicle(STREAMER_TAG_OBJECT objectid, vehicleid, Float:offsetx, Float:offsety, Float:offsetz, Float:rx, Float:ry, Float:rz);
native EditDynamicObject(playerid, STREAMER_TAG_OBJECT objectid);
native IsDynamicObjectMaterialUsed(STREAMER_TAG_OBJECT objectid, materialindex);
native GetDynamicObjectMaterial(STREAMER_TAG_OBJECT objectid, materialindex, &modelid, txdname[], texturename[], &materialcolor, maxtxdname = sizeof txdname, maxtexturename = sizeof texturename);
native SetDynamicObjectMaterial(STREAMER_TAG_OBJECT objectid, materialindex, modelid, const txdname[], const texturename[], materialcolor = 0);
native IsDynamicObjectMaterialTextUsed(STREAMER_TAG_OBJECT objectid, materialindex);
native GetDynamicObjectMaterialText(STREAMER_TAG_OBJECT objectid, materialindex, text[], &materialsize, fontface[], &fontsize, &bold, &fontcolor, &backcolor, &textalignment, maxtext = sizeof text, maxfontface = sizeof fontface);
native SetDynamicObjectMaterialText(STREAMER_TAG_OBJECT objectid, materialindex, const text[], materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);

// Natives (Pickups)

native STREAMER_TAG_PICKUP CreateDynamicPickup(modelid, type, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_PICKUP_SD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1);
native DestroyDynamicPickup(STREAMER_TAG_PICKUP pickupid);
native IsValidDynamicPickup(STREAMER_TAG_PICKUP pickupid);

// Natives (Checkpoints)

native STREAMER_TAG_CP CreateDynamicCP(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_CP_SD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1);
native DestroyDynamicCP(STREAMER_TAG_CP checkpointid);
native IsValidDynamicCP(STREAMER_TAG_CP checkpointid);
native TogglePlayerDynamicCP(playerid, STREAMER_TAG_CP checkpointid, toggle);
native TogglePlayerAllDynamicCPs(playerid, toggle);
native IsPlayerInDynamicCP(playerid, STREAMER_TAG_CP checkpointid);
native GetPlayerVisibleDynamicCP(playerid);

// Natives (Race Checkpoints)

native STREAMER_TAG_RACE_CP CreateDynamicRaceCP(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_RACE_CP_SD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1);
native DestroyDynamicRaceCP(STREAMER_TAG_RACE_CP checkpointid);
native IsValidDynamicRaceCP(STREAMER_TAG_RACE_CP checkpointid);
native TogglePlayerDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP checkpointid, toggle);
native TogglePlayerAllDynamicRaceCPs(playerid, toggle);
native IsPlayerInDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP checkpointid);
native GetPlayerVisibleDynamicRaceCP(playerid);

// Natives (Map Icons)

native STREAMER_TAG_MAP_ICON CreateDynamicMapIcon(Float:x, Float:y, Float:z, type, color, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_MAP_ICON_SD, style = MAPICON_LOCAL, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1);
native DestroyDynamicMapIcon(STREAMER_TAG_MAP_ICON iconid);
native IsValidDynamicMapIcon(STREAMER_TAG_MAP_ICON iconid);

// Natives (3D Text Labels)

native STREAMER_TAG_3D_TEXT_LABEL CreateDynamic3DTextLabel(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1);
native DestroyDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL id);
native IsValidDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL id);
native GetDynamic3DTextLabelText(STREAMER_TAG_3D_TEXT_LABEL id, text[], maxtext = sizeof text);
native UpdateDynamic3DTextLabelText(STREAMER_TAG_3D_TEXT_LABEL id, color, const text[]);

// Natives (Areas)

native STREAMER_TAG_AREA CreateDynamicCircle(Float:x, Float:y, Float:size, worldid = -1, interiorid = -1, playerid = -1);
native STREAMER_TAG_AREA CreateDynamicCylinder(Float:x, Float:y, Float:minz, Float:maxz, Float:size, worldid = -1, interiorid = -1, playerid = -1);
native STREAMER_TAG_AREA CreateDynamicSphere(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1);
native STREAMER_TAG_AREA CreateDynamicRectangle(Float:minx, Float:miny, Float:maxx, Float:maxy, worldid = -1, interiorid = -1, playerid = -1);
native STREAMER_TAG_AREA CreateDynamicCuboid(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1);
native STREAMER_TAG_AREA CreateDynamicCube(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1);
native STREAMER_TAG_AREA CreateDynamicPolygon(Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof points, worldid = -1, interiorid = -1, playerid = -1);
native DestroyDynamicArea(STREAMER_TAG_AREA areaid);
native IsValidDynamicArea(STREAMER_TAG_AREA areaid);
native GetDynamicPolygonPoints(STREAMER_TAG_AREA areaid, Float:points[], maxpoints = sizeof points);
native GetDynamicPolygonNumberPoints(STREAMER_TAG_AREA areaid);
native TogglePlayerDynamicArea(playerid, STREAMER_TAG_AREA areaid, toggle);
native TogglePlayerAllDynamicAreas(playerid, toggle);
native IsPlayerInDynamicArea(playerid, STREAMER_TAG_AREA areaid, recheck = 0);
native IsPlayerInAnyDynamicArea(playerid, recheck = 0);
native IsAnyPlayerInDynamicArea(STREAMER_TAG_AREA areaid, recheck = 0);
native IsAnyPlayerInAnyDynamicArea(recheck = 0);
native GetPlayerDynamicAreas(playerid, STREAMER_TAG_AREA areas[], maxareas = sizeof areas);
native GetPlayerNumberDynamicAreas(playerid);
native IsPointInDynamicArea(STREAMER_TAG_AREA areaid, Float:x, Float:y, Float:z);
native IsPointInAnyDynamicArea(Float:x, Float:y, Float:z);
native GetDynamicAreasForPoint(Float:x, Float:y, Float:z, STREAMER_TAG_AREA areas[], maxareas = sizeof areas);
native GetNumberDynamicAreasForPoint(Float:x, Float:y, Float:z);
native AttachDynamicAreaToObject(STREAMER_TAG_AREA areaid, STREAMER_TAG_OBJECT_ALT objectid, type = STREAMER_OBJECT_TYPE_DYNAMIC, playerid = INVALID_PLAYER_ID, Float:offsetx = 0.0, Float:offsety = 0.0, Float:offsetz = 0.0);
native AttachDynamicAreaToPlayer(STREAMER_TAG_AREA areaid, playerid, Float:offsetx = 0.0, Float:offsety = 0.0, Float:offsetz = 0.0);
native AttachDynamicAreaToVehicle(STREAMER_TAG_AREA areaid, vehicleid, Float:offsetx = 0.0, Float:offsety = 0.0, Float:offsetz = 0.0);

// Natives (Extended)

native STREAMER_TAG_OBJECT CreateDynamicObjectEx(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, STREAMER_TAG_AREA areas[] = { STREAMER_TAG_AREA -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas);
native STREAMER_TAG_PICKUP CreateDynamicPickupEx(modelid, type, Float:x, Float:y, Float:z, Float:streamdistance = STREAMER_PICKUP_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, STREAMER_TAG_AREA areas[] = { STREAMER_TAG_AREA -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas);
native STREAMER_TAG_CP CreateDynamicCPEx(Float:x, Float:y, Float:z, Float:size, Float:streamdistance = STREAMER_CP_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, STREAMER_TAG_AREA areas[] = { STREAMER_TAG_AREA -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas);
native STREAMER_TAG_RACE_CP CreateDynamicRaceCPEx(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, Float:streamdistance = STREAMER_RACE_CP_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, STREAMER_TAG_AREA areas[] = { STREAMER_TAG_AREA -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas);
native STREAMER_TAG_MAP_ICON CreateDynamicMapIconEx(Float:x, Float:y, Float:z, type, color, style = MAPICON_LOCAL, Float:streamdistance = STREAMER_MAP_ICON_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, STREAMER_TAG_AREA areas[] = { STREAMER_TAG_AREA -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas);
native STREAMER_TAG_3D_TEXT_LABEL CreateDynamic3DTextLabelEx(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, STREAMER_TAG_AREA areas[] = { STREAMER_TAG_AREA -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas);
native STREAMER_TAG_AREA CreateDynamicCircleEx(Float:x, Float:y, Float:size, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native STREAMER_TAG_AREA CreateDynamicCylinderEx(Float:x, Float:y, Float:minz, Float:maxz, Float:size, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native STREAMER_TAG_AREA CreateDynamicSphereEx(Float:x, Float:y, Float:z, Float:size, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native STREAMER_TAG_AREA CreateDynamicRectangleEx(Float:minx, Float:miny, Float:maxx, Float:maxy, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native STREAMER_TAG_AREA CreateDynamicCuboidEx(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native STREAMER_TAG_AREA CreateDynamicCubeEx(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native STREAMER_TAG_AREA CreateDynamicPolygonEx(Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof points, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);

// Natives (Deprecated)

native Streamer_TickRate(rate);
native Streamer_MaxItems(type, items);
native Streamer_VisibleItems(type, items, playerid = -1);
native Streamer_CellDistance(Float:distance);
native Streamer_CellSize(Float:size);
native Streamer_CallbackHook(callback, {Float,_}:...);

native DestroyAllDynamicObjects();
native CountDynamicObjects();
native DestroyAllDynamicPickups();
native CountDynamicPickups();
native DestroyAllDynamicCPs();
native CountDynamicCPs();
native DestroyAllDynamicRaceCPs();
native CountDynamicRaceCPs();
native DestroyAllDynamicMapIcons();
native CountDynamicMapIcons();
native DestroyAllDynamic3DTextLabels();
native CountDynamic3DTextLabels();
native DestroyAllDynamicAreas();
native CountDynamicAreas();

// Callbacks

forward OnDynamicObjectMoved(STREAMER_TAG_OBJECT objectid);
forward OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
forward OnPlayerSelectDynamicObject(playerid, STREAMER_TAG_OBJECT objectid, modelid, Float:x, Float:y, Float:z);
forward OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z);
forward OnPlayerPickUpDynamicPickup(playerid, STREAMER_TAG_PICKUP pickupid);
forward OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid);
forward OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP checkpointid);
forward OnPlayerEnterDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP checkpointid);
forward OnPlayerLeaveDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP checkpointid);
forward OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA areaid);
forward OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA areaid);
forward Streamer_OnPluginError(error[]);
