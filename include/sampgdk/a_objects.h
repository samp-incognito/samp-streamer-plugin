/* Copyright (C) 2011-2012, Zeex
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

#ifndef SAMPGDK_A_OBJECTS_H
#define SAMPGDK_A_OBJECTS_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/export.h>
#include <sampgdk/generated/a_objects-defs.h>

SAMPGDK_NATIVE(int, CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance));
SAMPGDK_NATIVE(bool, AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ));
SAMPGDK_NATIVE(bool, AttachObjectToObject(int objectid, int attachtoid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation));
SAMPGDK_NATIVE(bool, AttachObjectToPlayer(int objectid, int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ));
SAMPGDK_NATIVE(bool, SetObjectPos(int objectid, float x, float y, float z));
SAMPGDK_NATIVE(bool, GetObjectPos(int objectid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, SetObjectRot(int objectid, float rotX, float rotY, float rotZ));
SAMPGDK_NATIVE(bool, GetObjectRot(int objectid, float *rotX, float *rotY, float *rotZ));
SAMPGDK_NATIVE(bool, IsValidObject(int objectid));
SAMPGDK_NATIVE(bool, DestroyObject(int objectid));
SAMPGDK_NATIVE(int, MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ));
SAMPGDK_NATIVE(bool, StopObject(int objectid));
SAMPGDK_NATIVE(bool, IsObjectMoving(int objectid));
SAMPGDK_NATIVE(bool, EditObject(int playerid, int objectid));
SAMPGDK_NATIVE(bool, EditPlayerObject(int playerid, int objectid));
SAMPGDK_NATIVE(bool, SelectObject(int playerid));
SAMPGDK_NATIVE(bool, CancelEdit(int playerid));
SAMPGDK_NATIVE(int, CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance));
SAMPGDK_NATIVE(bool, AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ));
SAMPGDK_NATIVE(bool, AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ));
SAMPGDK_NATIVE(bool, SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z));
SAMPGDK_NATIVE(bool, GetPlayerObjectPos(int playerid, int objectid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ));
SAMPGDK_NATIVE(bool, GetPlayerObjectRot(int playerid, int objectid, float *rotX, float *rotY, float *rotZ));
SAMPGDK_NATIVE(bool, IsValidPlayerObject(int playerid, int objectid));
SAMPGDK_NATIVE(bool, DestroyPlayerObject(int playerid, int objectid));
SAMPGDK_NATIVE(int, MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX, float RotY, float RotZ));
SAMPGDK_NATIVE(bool, StopPlayerObject(int playerid, int objectid));
SAMPGDK_NATIVE(bool, IsPlayerObjectMoving(int playerid, int objectid));

#define OBJECT_MATERIAL_SIZE_32x32     10
#define OBJECT_MATERIAL_SIZE_64x32     20
#define OBJECT_MATERIAL_SIZE_64x64     30
#define OBJECT_MATERIAL_SIZE_128x32    40
#define OBJECT_MATERIAL_SIZE_128x64    50
#define OBJECT_MATERIAL_SIZE_128x128   60
#define OBJECT_MATERIAL_SIZE_256x32    70
#define OBJECT_MATERIAL_SIZE_256x64    80
#define OBJECT_MATERIAL_SIZE_256x128   90
#define OBJECT_MATERIAL_SIZE_256x256   100
#define OBJECT_MATERIAL_SIZE_512x64    110
#define OBJECT_MATERIAL_SIZE_512x128   120
#define OBJECT_MATERIAL_SIZE_512x256   130
#define OBJECT_MATERIAL_SIZE_512x512   140

#define OBJECT_MATERIAL_TEXT_ALIGN_LEFT     0
#define OBJECT_MATERIAL_TEXT_ALIGN_CENTER   1
#define OBJECT_MATERIAL_TEXT_ALIGN_RIGHT    2

SAMPGDK_NATIVE(bool, SetObjectMaterial(int objectid, int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor));
SAMPGDK_NATIVE(bool, SetPlayerObjectMaterial(int playerid, int objectid, int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor));

SAMPGDK_NATIVE(bool, SetObjectMaterialText(int objectid, const char *text, int materialindex, int materialsize, const char *fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment));
SAMPGDK_NATIVE(bool, SetPlayerObjectMaterialText(int playerid, int objectid, const char *text, int materialindex, int materialsize, const char *fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment));

#endif /* !SAMPGDK_A_OBJECTS_H */
