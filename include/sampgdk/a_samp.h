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

#ifndef SAMPGDK_A_SAMP_H
#define SAMPGDK_A_SAMP_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/export.h>
#include <sampgdk/plugin.h>
#include <sampgdk/generated/a_samp-defs.h>

#include <stddef.h>

#define MAX_PLAYER_NAME         (24)
#define MAX_PLAYERS             (1000)
#define MAX_VEHICLES            (2000)
#define INVALID_PLAYER_ID       (0xFFFF)
#define INVALID_VEHICLE_ID      (0xFFFF)
#define NO_TEAM                 (255)
#define MAX_OBJECTS             (1000)
#define INVALID_OBJECT_ID       (0xFFFF)
#define MAX_GANG_ZONES          (1024)
#define MAX_TEXT_DRAWS          (2048)
#define MAX_PLAYER_TEXT_DRAWS   (256)
#define MAX_MENUS               (128)
#define MAX_3DTEXT_GLOBAL       (1024)
#define MAX_3DTEXT_PLAYER       (1024)
#define MAX_PICKUPS             (4096)
#define INVALID_MENU            (0xFF)
#define INVALID_TEXT_DRAW       (0xFFFF)
#define INVALID_GANG_ZONE       (-1)
#define INVALID_3DTEXT_ID       (0xFFFF)

SAMPGDK_NATIVE(bool, SendClientMessage(int playerid, int color, const char *message));
SAMPGDK_NATIVE(bool, SendClientMessageToAll(int color, const char *message));
SAMPGDK_NATIVE(bool, SendPlayerMessageToPlayer(int playerid, int senderid, const char *message));
SAMPGDK_NATIVE(bool, SendPlayerMessageToAll(int senderid, const char *message));
SAMPGDK_NATIVE(bool, SendDeathMessage(int killer, int killee, int weapon));
SAMPGDK_NATIVE(bool, GameTextForAll(const char *text, int time, int style));
SAMPGDK_NATIVE(bool, GameTextForPlayer(int playerid, const char *text, int time, int style));
SAMPGDK_NATIVE(int, GetTickCount());
SAMPGDK_NATIVE(int, GetMaxPlayers());

SAMPGDK_NATIVE(bool, SetGameModeText(const char *text));
SAMPGDK_NATIVE(bool, SetTeamCount(int count));
SAMPGDK_NATIVE(int, AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));
SAMPGDK_NATIVE(int, AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));
SAMPGDK_NATIVE(int, AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2));
SAMPGDK_NATIVE(int, AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay));
SAMPGDK_NATIVE(int, AddStaticPickup(int model, int type, float x, float y, float z, int virtualworld));
SAMPGDK_NATIVE(int, CreatePickup(int model, int type, float x, float y, float z, int virtualworld));
SAMPGDK_NATIVE(bool, DestroyPickup(int pickup));
SAMPGDK_NATIVE(bool, ShowNameTags(bool show));
SAMPGDK_NATIVE(bool, ShowPlayerMarkers(bool mode));
SAMPGDK_NATIVE(bool, GameModeExit());
SAMPGDK_NATIVE(bool, SetWorldTime(int hour));
SAMPGDK_NATIVE(bool, GetWeaponName(int weaponid, char *name, int size));
SAMPGDK_NATIVE(bool, EnableTirePopping(bool enable));
SAMPGDK_NATIVE(bool, AllowInteriorWeapons(bool allow));
SAMPGDK_NATIVE(bool, SetWeather(int weatherid));
SAMPGDK_NATIVE(bool, SetGravity(float gravity));
SAMPGDK_NATIVE(bool, AllowAdminTeleport(bool allow));
SAMPGDK_NATIVE(bool, SetDeathDropAmount(int amount));
SAMPGDK_NATIVE(bool, CreateExplosion(float x, float y, float z, int type, float radius));
SAMPGDK_NATIVE(bool, EnableZoneNames(bool enable));
SAMPGDK_NATIVE(bool, UsePlayerPedAnims());
SAMPGDK_NATIVE(bool, DisableInteriorEnterExits());
SAMPGDK_NATIVE(bool, SetNameTagDrawDistance(float distance));
SAMPGDK_NATIVE(bool, DisableNameTagLOS());
SAMPGDK_NATIVE(bool, LimitGlobalChatRadius(float chat_radius));
SAMPGDK_NATIVE(bool, LimitPlayerMarkerRadius(float marker_radius));

SAMPGDK_NATIVE(bool, ConnectNPC(const char *name, const char *script));
SAMPGDK_NATIVE(bool, IsPlayerNPC(int playerid));

SAMPGDK_NATIVE(bool, IsPlayerAdmin(int playerid));
SAMPGDK_NATIVE(bool, Kick(int playerid));
SAMPGDK_NATIVE(bool, Ban(int playerid));
SAMPGDK_NATIVE(bool, BanEx(int playerid, const char *reason));
SAMPGDK_NATIVE(bool, SendRconCommand(const char *command));
SAMPGDK_NATIVE(bool, GetServerVarAsString(const char *varname, char *value, int size));
SAMPGDK_NATIVE(int, GetServerVarAsInt(const char *varname));
SAMPGDK_NATIVE(bool, GetServerVarAsBool(const char *varname));
SAMPGDK_NATIVE(bool, GetPlayerNetworkStats(int playerid, char *retstr, int size));
SAMPGDK_NATIVE(bool, GetNetworkStats(char *retstr, int size));
SAMPGDK_NATIVE(bool, GetPlayerVersion(int playerid, char *version, int len));

SAMPGDK_NATIVE(int, CreateMenu(const char *title, int columns, float x, float y, float col1width, float col2width));
SAMPGDK_NATIVE(bool, DestroyMenu(int menuid));
SAMPGDK_NATIVE(int, AddMenuItem(int menuid, int column, const char *menutext));
SAMPGDK_NATIVE(bool, SetMenuColumnHeader(int menuid, int column, const char *columnheader));
SAMPGDK_NATIVE(bool, ShowMenuForPlayer(int menuid, int playerid));
SAMPGDK_NATIVE(bool, HideMenuForPlayer(int menuid, int playerid));
SAMPGDK_NATIVE(bool, IsValidMenu(int menuid));
SAMPGDK_NATIVE(bool, DisableMenu(int menuid));
SAMPGDK_NATIVE(bool, DisableMenuRow(int menuid, int row));
SAMPGDK_NATIVE(int, GetPlayerMenu(int playerid));

SAMPGDK_NATIVE(int, TextDrawCreate(float x, float y, const char *text));
SAMPGDK_NATIVE(bool, TextDrawDestroy(int text));
SAMPGDK_NATIVE(bool, TextDrawLetterSize(int text, float x, float y));
SAMPGDK_NATIVE(bool, TextDrawTextSize(int text, float x, float y));
SAMPGDK_NATIVE(bool, TextDrawAlignment(int text, int alignment));
SAMPGDK_NATIVE(bool, TextDrawColor(int text, int color));
SAMPGDK_NATIVE(bool, TextDrawUseBox(int text, bool use));
SAMPGDK_NATIVE(bool, TextDrawBoxColor(int text, int color));
SAMPGDK_NATIVE(bool, TextDrawSetShadow(int text, int size));
SAMPGDK_NATIVE(bool, TextDrawSetOutline(int text, int size));
SAMPGDK_NATIVE(bool, TextDrawBackgroundColor(int text, int color));
SAMPGDK_NATIVE(bool, TextDrawFont(int text, int font));
SAMPGDK_NATIVE(bool, TextDrawSetProportional(int text, bool set));
SAMPGDK_NATIVE(bool, TextDrawSetSelectable(int text, bool set));
SAMPGDK_NATIVE(bool, TextDrawShowForPlayer(int playerid, int text));
SAMPGDK_NATIVE(bool, TextDrawHideForPlayer(int playerid, int text));
SAMPGDK_NATIVE(bool, TextDrawShowForAll(int text));
SAMPGDK_NATIVE(bool, TextDrawHideForAll(int text));
SAMPGDK_NATIVE(bool, TextDrawSetString(int text, const char *string));
SAMPGDK_NATIVE(bool, SelectTextDraw(int playerid, int hovercolor));
SAMPGDK_NATIVE(bool, CancelSelectTextDraw(int playerid));

SAMPGDK_NATIVE(int, GangZoneCreate(float minx, float miny, float maxx, float maxy));
SAMPGDK_NATIVE(bool, GangZoneDestroy(int zone));
SAMPGDK_NATIVE(bool, GangZoneShowForPlayer(int playerid, int zone, int color));
SAMPGDK_NATIVE(bool, GangZoneShowForAll(int zone, int color));
SAMPGDK_NATIVE(bool, GangZoneHideForPlayer(int playerid, int zone));
SAMPGDK_NATIVE(bool, GangZoneHideForAll(int zone));
SAMPGDK_NATIVE(bool, GangZoneFlashForPlayer(int playerid, int zone, int flashcolor));
SAMPGDK_NATIVE(bool, GangZoneFlashForAll(int zone, int flashcolor));
SAMPGDK_NATIVE(bool, GangZoneStopFlashForPlayer(int playerid, int zone));
SAMPGDK_NATIVE(bool, GangZoneStopFlashForAll(int zone));

SAMPGDK_NATIVE(int, Create3DTextLabel(const char *text, int color, float x, float y, float z, float DrawDistance, int virtualworld, bool testLOS));
SAMPGDK_NATIVE(bool, Delete3DTextLabel(int id));
SAMPGDK_NATIVE(bool, Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ));
SAMPGDK_NATIVE(bool, Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ));
SAMPGDK_NATIVE(bool, Update3DTextLabelText(int id, int color, const char *text));

SAMPGDK_NATIVE(int, CreatePlayer3DTextLabel(int playerid, const char *text, int color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS));
SAMPGDK_NATIVE(bool, DeletePlayer3DTextLabel(int playerid, int id));
SAMPGDK_NATIVE(bool, UpdatePlayer3DTextLabelText(int playerid, int id, int color, const char *text));

#define DIALOG_STYLE_MSGBOX   (0)
#define DIALOG_STYLE_INPUT    (1)
#define DIALOG_STYLE_LIST     (2)
#define DIALOG_STYLE_PASSWORD (3)

SAMPGDK_NATIVE(bool, ShowPlayerDialog(int playerid, int dialogid, int style, const char *caption, const char *info, const char *button1, const char *button2));

typedef void (SAMPGDK_CALL *TimerCallback)(int timerid, void *param);

SAMPGDK_NATIVE(int, SetTimer(int interval, bool repeat, TimerCallback callback, void *param)); /* $codeless */
SAMPGDK_NATIVE(bool, KillTimer(int timerid)); /* $codeless */

#define PLAYER_STATE_NONE                    (0)
#define PLAYER_STATE_ONFOOT                  (1)
#define PLAYER_STATE_DRIVER                  (2)
#define PLAYER_STATE_PASSENGER               (3)
#define PLAYER_STATE_EXIT_VEHICLE            (4)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER    (5)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER (6)
#define PLAYER_STATE_WASTED                  (7)
#define PLAYER_STATE_SPAWNED                 (8)
#define PLAYER_STATE_SPECTATING              (9)

#define PLAYER_MARKERS_MODE_OFF              (0)
#define PLAYER_MARKERS_MODE_GLOBAL           (1)
#define PLAYER_MARKERS_MODE_STREAMED         (2)

#define WEAPON_BRASSKNUCKLE       (1)
#define WEAPON_GOLFCLUB           (2)
#define WEAPON_NITESTICK          (3)
#define WEAPON_KNIFE              (4)
#define WEAPON_BAT                (5)
#define WEAPON_SHOVEL             (6)
#define WEAPON_POOLSTICK          (7)
#define WEAPON_KATANA             (8)
#define WEAPON_CHAINSAW           (9)
#define WEAPON_DILDO              (10)
#define WEAPON_DILDO2             (11)
#define WEAPON_VIBRATOR           (12)
#define WEAPON_VIBRATOR2          (13)
#define WEAPON_FLOWER             (14)
#define WEAPON_CANE               (15)
#define WEAPON_GRENADE            (16)
#define WEAPON_TEARGAS            (17)
#define WEAPON_MOLTOV             (18)
#define WEAPON_COLT45             (22)
#define WEAPON_SILENCED           (23)
#define WEAPON_DEAGLE             (24)
#define WEAPON_SHOTGUN            (25)
#define WEAPON_SAWEDOFF           (26)
#define WEAPON_SHOTGSPA           (27)
#define WEAPON_UZI                (28)
#define WEAPON_MP5                (29)
#define WEAPON_AK47               (30)
#define WEAPON_M4                 (31)
#define WEAPON_TEC9               (32)
#define WEAPON_RIFLE              (33)
#define WEAPON_SNIPER             (34)
#define WEAPON_ROCKETLAUNCHER     (35)
#define WEAPON_HEATSEEKER         (36)
#define WEAPON_FLAMETHROWER       (37)
#define WEAPON_MINIGUN            (38)
#define WEAPON_SATCHEL            (39)
#define WEAPON_BOMB               (40)
#define WEAPON_SPRAYCAN           (41)
#define WEAPON_FIREEXTINGUISHER   (42)
#define WEAPON_CAMERA             (43)
#define WEAPON_PARACHUTE          (46)
#define WEAPON_VEHICLE            (49)
#define WEAPON_DROWN              (53)
#define WEAPON_COLLISION          (54)

#define KEY_ACTION                (1)
#define KEY_CROUCH                (2)
#define KEY_FIRE                  (4)
#define KEY_SPRINT                (8)
#define KEY_SECONDARY_ATTACK      (16)
#define KEY_JUMP                  (32)
#define KEY_LOOK_RIGHT            (64)
#define KEY_HANDBRAKE             (128)
#define KEY_LOOK_LEFT             (256)
#define KEY_SUBMISSION            (512)
#define KEY_LOOK_BEHIND           (512)
#define KEY_WALK                  (1024)
#define KEY_ANALOG_UP             (2048)
#define KEY_ANALOG_DOWN           (4096)
#define KEY_ANALOG_LEFT           (8192)
#define KEY_ANALOG_RIGHT          (16384)
#define KEY_YES                   (65536)
#define KEY_NO                    (131072)
#define KEY_CTRL_BACK             (262144)
#define KEY_UP                    (-128)
#define KEY_DOWN                  (128)
#define KEY_LEFT                  (-128)
#define KEY_RIGHT                 (128)

SAMPGDK_NATIVE(bool, gpci(int playerid, char *buffer, int size));

#ifdef __cplusplus

#include <string>

template<size_t N> inline bool GetNetworkStats(char (&retstr)[N]) {
	return GetNetworkStats(retstr, N);
}
template<size_t N> inline bool GetPlayerNetworkStats(int playerid, char (&retstr)[N]) {
	return GetPlayerNetworkStats(playerid, retstr, N);
}
template<size_t N> inline bool GetPlayerVersion(int playerid, char (&version)[N]) {
	return GetPlayerVersion(playerid, version, N);
}
template<size_t N> inline bool GetWeaponName(int weaponid, char (&name)[N]) {
	return GetWeaponName(weaponid, name, N);
}

#endif /* __cplusplus */

#define CLICK_SOURCE_SCOREBOARD (0)

#define EDIT_RESPONSE_CANCEL   (0)
#define EDIT_RESPONSE_FINAL    (1)
#define EDIT_RESPONSE_UPDATE   (2)

#define SELECT_OBJECT_GLOBAL_OBJECT (1)
#define SELECT_OBJECT_PLAYER_OBJECT (2)

#endif /* !SAMPGDK_A_SAMP_H */
