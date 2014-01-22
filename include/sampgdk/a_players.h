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

#ifndef SAMPGDK_A_PLAYERS_H
#define SAMPGDK_A_PLAYERS_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/export.h>
#include <sampgdk/generated/a_players-defs.h>

#include <stddef.h>

#define SPECIAL_ACTION_NONE             (0)
#define SPECIAL_ACTION_DUCK             (1)
#define SPECIAL_ACTION_USEJETPACK       (2)
#define SPECIAL_ACTION_ENTER_VEHICLE    (3)
#define SPECIAL_ACTION_EXIT_VEHICLE     (4)
#define SPECIAL_ACTION_DANCE1           (5)
#define SPECIAL_ACTION_DANCE2           (6)
#define SPECIAL_ACTION_DANCE3           (7)
#define SPECIAL_ACTION_DANCE4           (8)
#define SPECIAL_ACTION_HANDSUP          (10)
#define SPECIAL_ACTION_USECELLPHONE     (11)
#define SPECIAL_ACTION_SITTING          (12)
#define SPECIAL_ACTION_STOPUSECELLPHONE (13)
#define SPECIAL_ACTION_DRINK_BEER       (20)
#define SPECIAL_ACTION_SMOKE_CIGGY      (21)
#define SPECIAL_ACTION_DRINK_WINE       (22)
#define SPECIAL_ACTION_DRINK_SPRUNK     (23)

#define FIGHT_STYLE_NORMAL    (4)
#define FIGHT_STYLE_BOXING    (5)
#define FIGHT_STYLE_KUNGFU    (6)
#define FIGHT_STYLE_KNEEHEAD  (7)
#define FIGHT_STYLE_GRABKICK  (15)
#define FIGHT_STYLE_ELBOW     (16)

#define WEAPONSKILL_PISTOL          (0)
#define WEAPONSKILL_PISTOL_SILENCED (1)
#define WEAPONSKILL_DESERT_EAGLE    (2)
#define WEAPONSKILL_SHOTGUN         (3)
#define WEAPONSKILL_SAWNOFF_SHOTGUN (4)
#define WEAPONSKILL_SPAS12_SHOTGUN  (5)
#define WEAPONSKILL_MICRO_UZI       (6)
#define WEAPONSKILL_MP5             (7)
#define WEAPONSKILL_AK47            (8)
#define WEAPONSKILL_M4              (9)
#define WEAPONSKILL_SNIPERRIFLE     (10)

#define WEAPONSTATE_UNKNOWN      (-1)
#define WEAPONSTATE_NO_BULLETS   (0)
#define WEAPONSTATE_LAST_BULLET  (1)
#define WEAPONSTATE_MORE_BULLETS (2)
#define WEAPONSTATE_RELOADING    (3)

SAMPGDK_NATIVE(bool, SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));
SAMPGDK_NATIVE(bool, SpawnPlayer(int playerid));

SAMPGDK_NATIVE(bool, SetPlayerPos(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, SetPlayerPosFindZ(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, GetPlayerPos(int playerid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, SetPlayerFacingAngle(int playerid, float angle));
SAMPGDK_NATIVE(bool, GetPlayerFacingAngle(int playerid, float *angle));
SAMPGDK_NATIVE(bool, IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z));
SAMPGDK_NATIVE(float, GetPlayerDistanceFromPoint(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, IsPlayerStreamedIn(int playerid, int forplayerid));
SAMPGDK_NATIVE(bool, SetPlayerInterior(int playerid, int interiorid));
SAMPGDK_NATIVE(int, GetPlayerInterior(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerHealth(int playerid, float health));
SAMPGDK_NATIVE(bool, GetPlayerHealth(int playerid, float *health));
SAMPGDK_NATIVE(bool, SetPlayerArmour(int playerid, float armour));
SAMPGDK_NATIVE(bool, GetPlayerArmour(int playerid, float *armour));
SAMPGDK_NATIVE(bool, SetPlayerAmmo(int playerid, int weaponslot, int ammo));
SAMPGDK_NATIVE(int, GetPlayerAmmo(int playerid));
SAMPGDK_NATIVE(int, GetPlayerWeaponState(int playerid));
SAMPGDK_NATIVE(int, GetPlayerTargetPlayer(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerTeam(int playerid, int teamid));
SAMPGDK_NATIVE(int, GetPlayerTeam(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerScore(int playerid, int score));
SAMPGDK_NATIVE(int, GetPlayerScore(int playerid));
SAMPGDK_NATIVE(int, GetPlayerDrunkLevel(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerDrunkLevel(int playerid, int level));
SAMPGDK_NATIVE(bool, SetPlayerColor(int playerid, int color));
SAMPGDK_NATIVE(int, GetPlayerColor(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerSkin(int playerid, int skinid));
SAMPGDK_NATIVE(int, GetPlayerSkin(int playerid));
SAMPGDK_NATIVE(bool, GivePlayerWeapon(int playerid, int weaponid, int ammo));
SAMPGDK_NATIVE(bool, ResetPlayerWeapons(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerArmedWeapon(int playerid, int weaponid));
SAMPGDK_NATIVE(bool, GetPlayerWeaponData(int playerid, int slot, int *weapon, int *ammo));
SAMPGDK_NATIVE(bool, GivePlayerMoney(int playerid, int money));
SAMPGDK_NATIVE(bool, ResetPlayerMoney(int playerid));
SAMPGDK_NATIVE(int, SetPlayerName(int playerid, const char *name));
SAMPGDK_NATIVE(int, GetPlayerMoney(int playerid));
SAMPGDK_NATIVE(int, GetPlayerState(int playerid));
SAMPGDK_NATIVE(bool, GetPlayerIp(int playerid, char *ip, int size));
SAMPGDK_NATIVE(int, GetPlayerPing(int playerid));
SAMPGDK_NATIVE(int, GetPlayerWeapon(int playerid));
SAMPGDK_NATIVE(bool, GetPlayerKeys(int playerid, int *keys, int *updown, int *leftright));
SAMPGDK_NATIVE(bool, GetPlayerName(int playerid, char *name, int size));
SAMPGDK_NATIVE(bool, SetPlayerTime(int playerid, int hour, int minute));
SAMPGDK_NATIVE(bool, GetPlayerTime(int playerid, int *hour, int *minute));
SAMPGDK_NATIVE(bool, TogglePlayerClock(int playerid, bool toggle));
SAMPGDK_NATIVE(bool, SetPlayerWeather(int playerid, int weather));
SAMPGDK_NATIVE(bool, ForceClassSelection(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerWantedLevel(int playerid, int level));
SAMPGDK_NATIVE(int, GetPlayerWantedLevel(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerFightingStyle(int playerid, int style));
SAMPGDK_NATIVE(int, GetPlayerFightingStyle(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerVelocity(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, GetPlayerVelocity( int playerid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, PlayCrimeReportForPlayer(int playerid, int suspectid, int crime));
SAMPGDK_NATIVE(bool, PlayAudioStreamForPlayer(int playerid, const char *url, float posX, float posY, float posZ, float distance, bool usepos));
SAMPGDK_NATIVE(bool, StopAudioStreamForPlayer(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerShopName(int playerid, const char *shopname));
SAMPGDK_NATIVE(bool, SetPlayerSkillLevel(int playerid, int skill, int level));
SAMPGDK_NATIVE(int, GetPlayerSurfingVehicleID(int playerid));
SAMPGDK_NATIVE(int, GetPlayerSurfingObjectID(int playerid));
SAMPGDK_NATIVE(bool, RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius));

#define MAX_PLAYER_ATTACHED_OBJECTS (10)

SAMPGDK_NATIVE(bool, SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ, int materialcolor1, int materialcolor2));
SAMPGDK_NATIVE(bool, RemovePlayerAttachedObject(int playerid, int index));
SAMPGDK_NATIVE(bool, IsPlayerAttachedObjectSlotUsed(int playerid, int index));
SAMPGDK_NATIVE(bool, EditAttachedObject(int playerid, int index));

SAMPGDK_NATIVE(int, CreatePlayerTextDraw(int playerid, float x, float y, const char *text));
SAMPGDK_NATIVE(bool, PlayerTextDrawDestroy(int playerid, int text));
SAMPGDK_NATIVE(bool, PlayerTextDrawLetterSize(int playerid, int text, float x, float y));
SAMPGDK_NATIVE(bool, PlayerTextDrawTextSize(int playerid, int text, float x, float y));
SAMPGDK_NATIVE(bool, PlayerTextDrawAlignment(int playerid, int text, int alignment));
SAMPGDK_NATIVE(bool, PlayerTextDrawColor(int playerid, int text, int color));
SAMPGDK_NATIVE(bool, PlayerTextDrawUseBox(int playerid, int text, bool use));
SAMPGDK_NATIVE(bool, PlayerTextDrawBoxColor(int playerid, int text, int color));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetShadow(int playerid, int text, int size));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetOutline(int playerid, int text, int size));
SAMPGDK_NATIVE(bool, PlayerTextDrawBackgroundColor(int playerid, int text, int color));
SAMPGDK_NATIVE(bool, PlayerTextDrawFont(int playerid, int text, int font));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetProportional(int playerid, int text, bool set));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetSelectable(int playerid, int text, bool set));
SAMPGDK_NATIVE(bool, PlayerTextDrawShow(int playerid, int text));
SAMPGDK_NATIVE(bool, PlayerTextDrawHide(int playerid, int text));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetString(int playerid, int text, const char *string));

#define PLAYER_VARTYPE_NONE   (0)
#define PLAYER_VARTYPE_INT    (1)
#define PLAYER_VARTYPE_STRING (2)
#define PLAYER_VARTYPE_FLOAT  (3)

SAMPGDK_NATIVE(bool, SetPVarInt(int playerid, const char *varname, int value));
SAMPGDK_NATIVE(int, GetPVarInt(int playerid, const char *varname));
SAMPGDK_NATIVE(bool, SetPVarString(int playerid, const char *varname, const char *value));
SAMPGDK_NATIVE(bool, GetPVarString(int playerid, const char *varname, char *value, int size));
SAMPGDK_NATIVE(bool, SetPVarFloat(int playerid, const char *varname, float value));
SAMPGDK_NATIVE(float, GetPVarFloat(int playerid, const char *varname));
SAMPGDK_NATIVE(bool, DeletePVar(int playerid, const char *varname));

SAMPGDK_NATIVE(int, GetPVarsUpperIndex(int playerid));
SAMPGDK_NATIVE(bool, GetPVarNameAtIndex(int playerid, int index, char *varname, int size));
SAMPGDK_NATIVE(int, GetPVarType(int playerid, const char *varname));

#define MAX_CHATBUBBLE_LENGTH (144)

SAMPGDK_NATIVE(bool, SetPlayerChatBubble(int playerid, const char *text, int color, float drawdistance, int expiretime));

SAMPGDK_NATIVE(bool, PutPlayerInVehicle(int playerid, int vehicleid, int seatid));
SAMPGDK_NATIVE(int, GetPlayerVehicleID(int playerid));
SAMPGDK_NATIVE(int, GetPlayerVehicleSeat(int playerid));
SAMPGDK_NATIVE(bool, RemovePlayerFromVehicle(int playerid));
SAMPGDK_NATIVE(bool, TogglePlayerControllable(int playerid, bool toggle));
SAMPGDK_NATIVE(bool, PlayerPlaySound(int playerid, int soundid, float x, float y, float z));
SAMPGDK_NATIVE(bool, ApplyAnimation(int playerid, const char *animlib, const char *animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync));
SAMPGDK_NATIVE(bool, ClearAnimations(int playerid, bool forcesync));
SAMPGDK_NATIVE(int, GetPlayerAnimationIndex(int playerid));
SAMPGDK_NATIVE(bool, GetAnimationName(int index, char *animlib, int animlib_size, char *animname, int animname_size));
SAMPGDK_NATIVE(int, GetPlayerSpecialAction(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerSpecialAction(int playerid, int actionid));

SAMPGDK_NATIVE(bool, SetPlayerCheckpoint(int playerid, float x, float y, float z, float size));
SAMPGDK_NATIVE(bool, DisablePlayerCheckpoint(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size));
SAMPGDK_NATIVE(bool, DisablePlayerRaceCheckpoint(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min));
SAMPGDK_NATIVE(bool, SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color));
SAMPGDK_NATIVE(bool, ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show));

#define MAPICON_LOCAL             (0)
#define MAPICON_GLOBAL            (1)
#define MAPICON_LOCAL_CHECKPOINT  (2)
#define MAPICON_GLOBAL_CHECKPOINT (3)

SAMPGDK_NATIVE(bool, SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style));
SAMPGDK_NATIVE(bool, RemovePlayerMapIcon(int playerid, int iconid));

SAMPGDK_NATIVE(bool, AllowPlayerTeleport(int playerid, bool allow));

#define CAMERA_CUT  2
#define CAMERA_MOVE 1

SAMPGDK_NATIVE(bool, SetPlayerCameraPos(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut));
SAMPGDK_NATIVE(bool, SetCameraBehindPlayer(int playerid));
SAMPGDK_NATIVE(bool, GetPlayerCameraPos(int playerid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, GetPlayerCameraFrontVector(int playerid, float *x, float *y, float *z));
SAMPGDK_NATIVE(int, GetPlayerCameraMode(int playerid));
SAMPGDK_NATIVE(bool, AttachCameraToObject(int playerid, int objectid));
SAMPGDK_NATIVE(bool, AttachCameraToPlayerObject(int playerid, int playerobjectid));
SAMPGDK_NATIVE(bool, InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut));
SAMPGDK_NATIVE(bool, InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut));

SAMPGDK_NATIVE(bool, IsPlayerConnected(int playerid));
SAMPGDK_NATIVE(bool, IsPlayerInVehicle(int playerid, int vehicleid));
SAMPGDK_NATIVE(bool, IsPlayerInAnyVehicle(int playerid));
SAMPGDK_NATIVE(bool, IsPlayerInCheckpoint(int playerid));
SAMPGDK_NATIVE(bool, IsPlayerInRaceCheckpoint(int playerid));

SAMPGDK_NATIVE(bool, SetPlayerVirtualWorld(int playerid, int worldid));
SAMPGDK_NATIVE(int, GetPlayerVirtualWorld(int playerid));

SAMPGDK_NATIVE(bool, EnableStuntBonusForPlayer(int playerid, bool enable));
SAMPGDK_NATIVE(bool, EnableStuntBonusForAll(bool enable));

#define SPECTATE_MODE_NORMAL  (1)
#define SPECTATE_MODE_FIXED   (2)
#define SPECTATE_MODE_SIDE    (3)

SAMPGDK_NATIVE(bool, TogglePlayerSpectating(int playerid, bool toggle));
SAMPGDK_NATIVE(bool, PlayerSpectatePlayer(int playerid, int targetplayerid, int mode));
SAMPGDK_NATIVE(bool, PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode));

#define PLAYER_RECORDING_TYPE_NONE   (0)
#define PLAYER_RECORDING_TYPE_DRIVER (1)
#define PLAYER_RECORDING_TYPE_ONFOOT (2)

SAMPGDK_NATIVE(bool, StartRecordingPlayerData(int playerid, int recordtype, const char *recordname));
SAMPGDK_NATIVE(bool, StopRecordingPlayerData(int playerid));

#ifdef __cplusplus

#include <cassert>
#include <cmath>
#include <string>
#include <vector>

template<size_t N> inline bool GetPlayerName(int playerid, char (&name)[N]) {
	return GetPlayerName(playerid, name, N);
}
template<size_t N> inline bool GetPlayerIp(int playerid, char (&ip)[N]) {
	return GetPlayerIp(playerid, ip, N);
}
template<size_t N> inline bool GetPVarString(int playerid, const char *varname, char (&value)[N]) {
	return GetPVarString(playerid, varname, value, N);
}
template<size_t N> inline bool GetPVarNameAtIndex(int playerid, int index, char (&varname)[N]) {
	return GetPVarNameAtIndex(playerid, index, varname, N);
}
template<size_t N1, size_t N2> inline bool GetAnimationName(int index, char (&animlib)[N1], char (&animname)[N2]) {
	return GetAnimationName(index, animlib, N1, animname, N2);
}

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_PLAYERS_H */
