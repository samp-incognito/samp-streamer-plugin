#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/types.h>

#ifndef DOXYGEN
#undef  SendClientMessage
#define SendClientMessage sampgdk_SendClientMessage
#undef  SendClientMessageToAll
#define SendClientMessageToAll sampgdk_SendClientMessageToAll
#undef  SendPlayerMessageToPlayer
#define SendPlayerMessageToPlayer sampgdk_SendPlayerMessageToPlayer
#undef  SendPlayerMessageToAll
#define SendPlayerMessageToAll sampgdk_SendPlayerMessageToAll
#undef  SendDeathMessage
#define SendDeathMessage sampgdk_SendDeathMessage
#undef  SendDeathMessageToPlayer
#define SendDeathMessageToPlayer sampgdk_SendDeathMessageToPlayer
#undef  GameTextForAll
#define GameTextForAll sampgdk_GameTextForAll
#undef  GameTextForPlayer
#define GameTextForPlayer sampgdk_GameTextForPlayer
#undef  GetTickCount
#define GetTickCount sampgdk_GetTickCount
#undef  GetMaxPlayers
#define GetMaxPlayers sampgdk_GetMaxPlayers
#undef  VectorSize
#define VectorSize sampgdk_VectorSize
#undef  SetGameModeText
#define SetGameModeText sampgdk_SetGameModeText
#undef  SetTeamCount
#define SetTeamCount sampgdk_SetTeamCount
#undef  AddPlayerClass
#define AddPlayerClass sampgdk_AddPlayerClass
#undef  AddPlayerClassEx
#define AddPlayerClassEx sampgdk_AddPlayerClassEx
#undef  AddStaticVehicle
#define AddStaticVehicle sampgdk_AddStaticVehicle
#undef  AddStaticVehicleEx
#define AddStaticVehicleEx sampgdk_AddStaticVehicleEx
#undef  AddStaticPickup
#define AddStaticPickup sampgdk_AddStaticPickup
#undef  CreatePickup
#define CreatePickup sampgdk_CreatePickup
#undef  DestroyPickup
#define DestroyPickup sampgdk_DestroyPickup
#undef  ShowNameTags
#define ShowNameTags sampgdk_ShowNameTags
#undef  ShowPlayerMarkers
#define ShowPlayerMarkers sampgdk_ShowPlayerMarkers
#undef  GameModeExit
#define GameModeExit sampgdk_GameModeExit
#undef  SetWorldTime
#define SetWorldTime sampgdk_SetWorldTime
#undef  GetWeaponName
#define GetWeaponName sampgdk_GetWeaponName
#undef  EnableTirePopping
#define EnableTirePopping sampgdk_EnableTirePopping
#undef  EnableVehicleFriendlyFire
#define EnableVehicleFriendlyFire sampgdk_EnableVehicleFriendlyFire
#undef  AllowInteriorWeapons
#define AllowInteriorWeapons sampgdk_AllowInteriorWeapons
#undef  SetWeather
#define SetWeather sampgdk_SetWeather
#undef  SetGravity
#define SetGravity sampgdk_SetGravity
#undef  AllowAdminTeleport
#define AllowAdminTeleport sampgdk_AllowAdminTeleport
#undef  SetDeathDropAmount
#define SetDeathDropAmount sampgdk_SetDeathDropAmount
#undef  CreateExplosion
#define CreateExplosion sampgdk_CreateExplosion
#undef  EnableZoneNames
#define EnableZoneNames sampgdk_EnableZoneNames
#undef  UsePlayerPedAnims
#define UsePlayerPedAnims sampgdk_UsePlayerPedAnims
#undef  DisableInteriorEnterExits
#define DisableInteriorEnterExits sampgdk_DisableInteriorEnterExits
#undef  SetNameTagDrawDistance
#define SetNameTagDrawDistance sampgdk_SetNameTagDrawDistance
#undef  DisableNameTagLOS
#define DisableNameTagLOS sampgdk_DisableNameTagLOS
#undef  LimitGlobalChatRadius
#define LimitGlobalChatRadius sampgdk_LimitGlobalChatRadius
#undef  LimitPlayerMarkerRadius
#define LimitPlayerMarkerRadius sampgdk_LimitPlayerMarkerRadius
#undef  ConnectNPC
#define ConnectNPC sampgdk_ConnectNPC
#undef  IsPlayerNPC
#define IsPlayerNPC sampgdk_IsPlayerNPC
#undef  IsPlayerAdmin
#define IsPlayerAdmin sampgdk_IsPlayerAdmin
#undef  Kick
#define Kick sampgdk_Kick
#undef  Ban
#define Ban sampgdk_Ban
#undef  BanEx
#define BanEx sampgdk_BanEx
#undef  SendRconCommand
#define SendRconCommand sampgdk_SendRconCommand
#undef  GetServerVarAsString
#define GetServerVarAsString sampgdk_GetServerVarAsString
#undef  GetServerVarAsInt
#define GetServerVarAsInt sampgdk_GetServerVarAsInt
#undef  GetServerVarAsBool
#define GetServerVarAsBool sampgdk_GetServerVarAsBool
#undef  GetPlayerNetworkStats
#define GetPlayerNetworkStats sampgdk_GetPlayerNetworkStats
#undef  GetNetworkStats
#define GetNetworkStats sampgdk_GetNetworkStats
#undef  GetPlayerVersion
#define GetPlayerVersion sampgdk_GetPlayerVersion
#undef  BlockIpAddress
#define BlockIpAddress sampgdk_BlockIpAddress
#undef  UnBlockIpAddress
#define UnBlockIpAddress sampgdk_UnBlockIpAddress
#undef  GetServerTickRate
#define GetServerTickRate sampgdk_GetServerTickRate
#undef  NetStats_GetConnectedTime
#define NetStats_GetConnectedTime sampgdk_NetStats_GetConnectedTime
#undef  NetStats_MessagesReceived
#define NetStats_MessagesReceived sampgdk_NetStats_MessagesReceived
#undef  NetStats_BytesReceived
#define NetStats_BytesReceived sampgdk_NetStats_BytesReceived
#undef  NetStats_MessagesSent
#define NetStats_MessagesSent sampgdk_NetStats_MessagesSent
#undef  NetStats_BytesSent
#define NetStats_BytesSent sampgdk_NetStats_BytesSent
#undef  NetStats_MessagesRecvPerSecond
#define NetStats_MessagesRecvPerSecond sampgdk_NetStats_MessagesRecvPerSecond
#undef  NetStats_PacketLossPercent
#define NetStats_PacketLossPercent sampgdk_NetStats_PacketLossPercent
#undef  NetStats_ConnectionStatus
#define NetStats_ConnectionStatus sampgdk_NetStats_ConnectionStatus
#undef  NetStats_GetIpPort
#define NetStats_GetIpPort sampgdk_NetStats_GetIpPort
#undef  CreateMenu
#define CreateMenu sampgdk_CreateMenu
#undef  DestroyMenu
#define DestroyMenu sampgdk_DestroyMenu
#undef  AddMenuItem
#define AddMenuItem sampgdk_AddMenuItem
#undef  SetMenuColumnHeader
#define SetMenuColumnHeader sampgdk_SetMenuColumnHeader
#undef  ShowMenuForPlayer
#define ShowMenuForPlayer sampgdk_ShowMenuForPlayer
#undef  HideMenuForPlayer
#define HideMenuForPlayer sampgdk_HideMenuForPlayer
#undef  IsValidMenu
#define IsValidMenu sampgdk_IsValidMenu
#undef  DisableMenu
#define DisableMenu sampgdk_DisableMenu
#undef  DisableMenuRow
#define DisableMenuRow sampgdk_DisableMenuRow
#undef  GetPlayerMenu
#define GetPlayerMenu sampgdk_GetPlayerMenu
#undef  TextDrawCreate
#define TextDrawCreate sampgdk_TextDrawCreate
#undef  TextDrawDestroy
#define TextDrawDestroy sampgdk_TextDrawDestroy
#undef  TextDrawLetterSize
#define TextDrawLetterSize sampgdk_TextDrawLetterSize
#undef  TextDrawTextSize
#define TextDrawTextSize sampgdk_TextDrawTextSize
#undef  TextDrawAlignment
#define TextDrawAlignment sampgdk_TextDrawAlignment
#undef  TextDrawColor
#define TextDrawColor sampgdk_TextDrawColor
#undef  TextDrawUseBox
#define TextDrawUseBox sampgdk_TextDrawUseBox
#undef  TextDrawBoxColor
#define TextDrawBoxColor sampgdk_TextDrawBoxColor
#undef  TextDrawSetShadow
#define TextDrawSetShadow sampgdk_TextDrawSetShadow
#undef  TextDrawSetOutline
#define TextDrawSetOutline sampgdk_TextDrawSetOutline
#undef  TextDrawBackgroundColor
#define TextDrawBackgroundColor sampgdk_TextDrawBackgroundColor
#undef  TextDrawFont
#define TextDrawFont sampgdk_TextDrawFont
#undef  TextDrawSetProportional
#define TextDrawSetProportional sampgdk_TextDrawSetProportional
#undef  TextDrawSetSelectable
#define TextDrawSetSelectable sampgdk_TextDrawSetSelectable
#undef  TextDrawShowForPlayer
#define TextDrawShowForPlayer sampgdk_TextDrawShowForPlayer
#undef  TextDrawHideForPlayer
#define TextDrawHideForPlayer sampgdk_TextDrawHideForPlayer
#undef  TextDrawShowForAll
#define TextDrawShowForAll sampgdk_TextDrawShowForAll
#undef  TextDrawHideForAll
#define TextDrawHideForAll sampgdk_TextDrawHideForAll
#undef  TextDrawSetString
#define TextDrawSetString sampgdk_TextDrawSetString
#undef  TextDrawSetPreviewModel
#define TextDrawSetPreviewModel sampgdk_TextDrawSetPreviewModel
#undef  TextDrawSetPreviewRot
#define TextDrawSetPreviewRot sampgdk_TextDrawSetPreviewRot
#undef  TextDrawSetPreviewVehCol
#define TextDrawSetPreviewVehCol sampgdk_TextDrawSetPreviewVehCol
#undef  SelectTextDraw
#define SelectTextDraw sampgdk_SelectTextDraw
#undef  CancelSelectTextDraw
#define CancelSelectTextDraw sampgdk_CancelSelectTextDraw
#undef  GangZoneCreate
#define GangZoneCreate sampgdk_GangZoneCreate
#undef  GangZoneDestroy
#define GangZoneDestroy sampgdk_GangZoneDestroy
#undef  GangZoneShowForPlayer
#define GangZoneShowForPlayer sampgdk_GangZoneShowForPlayer
#undef  GangZoneShowForAll
#define GangZoneShowForAll sampgdk_GangZoneShowForAll
#undef  GangZoneHideForPlayer
#define GangZoneHideForPlayer sampgdk_GangZoneHideForPlayer
#undef  GangZoneHideForAll
#define GangZoneHideForAll sampgdk_GangZoneHideForAll
#undef  GangZoneFlashForPlayer
#define GangZoneFlashForPlayer sampgdk_GangZoneFlashForPlayer
#undef  GangZoneFlashForAll
#define GangZoneFlashForAll sampgdk_GangZoneFlashForAll
#undef  GangZoneStopFlashForPlayer
#define GangZoneStopFlashForPlayer sampgdk_GangZoneStopFlashForPlayer
#undef  GangZoneStopFlashForAll
#define GangZoneStopFlashForAll sampgdk_GangZoneStopFlashForAll
#undef  Create3DTextLabel
#define Create3DTextLabel sampgdk_Create3DTextLabel
#undef  Delete3DTextLabel
#define Delete3DTextLabel sampgdk_Delete3DTextLabel
#undef  Attach3DTextLabelToPlayer
#define Attach3DTextLabelToPlayer sampgdk_Attach3DTextLabelToPlayer
#undef  Attach3DTextLabelToVehicle
#define Attach3DTextLabelToVehicle sampgdk_Attach3DTextLabelToVehicle
#undef  Update3DTextLabelText
#define Update3DTextLabelText sampgdk_Update3DTextLabelText
#undef  CreatePlayer3DTextLabel
#define CreatePlayer3DTextLabel sampgdk_CreatePlayer3DTextLabel
#undef  DeletePlayer3DTextLabel
#define DeletePlayer3DTextLabel sampgdk_DeletePlayer3DTextLabel
#undef  UpdatePlayer3DTextLabelText
#define UpdatePlayer3DTextLabelText sampgdk_UpdatePlayer3DTextLabelText
#undef  ShowPlayerDialog
#define ShowPlayerDialog sampgdk_ShowPlayerDialog
#undef  SetTimer
#define SetTimer sampgdk_SetTimer
#undef  KillTimer
#define KillTimer sampgdk_KillTimer
#undef  gpci
#define gpci sampgdk_gpci
#endif


/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendClientMessage">SendClientMessage on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendClientMessage(int playerid, int color, const char * message));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendClientMessageToAll">SendClientMessageToAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendClientMessageToAll(int color, const char * message));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendPlayerMessageToPlayer">SendPlayerMessageToPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendPlayerMessageToPlayer(int playerid, int senderid, const char * message));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendPlayerMessageToAll">SendPlayerMessageToAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendPlayerMessageToAll(int senderid, const char * message));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendDeathMessage">SendDeathMessage on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendDeathMessage(int killer, int killee, int weapon));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendDeathMessageToPlayer">SendDeathMessageToPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendDeathMessageToPlayer(int playerid, int killer, int killee, int weapon));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GameTextForAll">GameTextForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GameTextForAll(const char * text, int time, int style));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GameTextForPlayer">GameTextForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GameTextForPlayer(int playerid, const char * text, int time, int style));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetTickCount">GetTickCount on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetTickCount());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetMaxPlayers">GetMaxPlayers on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetMaxPlayers());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/VectorSize">VectorSize on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, VectorSize(float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetGameModeText">SetGameModeText on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetGameModeText(const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetTeamCount">SetTeamCount on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetTeamCount(int count));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddPlayerClass">AddPlayerClass on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddPlayerClassEx">AddPlayerClassEx on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddStaticVehicle">AddStaticVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddStaticVehicleEx">AddStaticVehicleEx on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddStaticPickup">AddStaticPickup on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddStaticPickup(int model, int type, float x, float y, float z, int virtualworld));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreatePickup">CreatePickup on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreatePickup(int model, int type, float x, float y, float z, int virtualworld));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DestroyPickup">DestroyPickup on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DestroyPickup(int pickup));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowNameTags">ShowNameTags on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowNameTags(bool show));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowPlayerMarkers">ShowPlayerMarkers on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowPlayerMarkers(int mode));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GameModeExit">GameModeExit on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GameModeExit());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetWorldTime">SetWorldTime on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetWorldTime(int hour));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetWeaponName">GetWeaponName on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetWeaponName(int weaponid, char * name, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableTirePopping">EnableTirePopping on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EnableTirePopping(bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableVehicleFriendlyFire">EnableVehicleFriendlyFire on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EnableVehicleFriendlyFire());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AllowInteriorWeapons">AllowInteriorWeapons on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AllowInteriorWeapons(bool allow));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetWeather">SetWeather on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetWeather(int weatherid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetGravity">SetGravity on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetGravity(float gravity));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AllowAdminTeleport">AllowAdminTeleport on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AllowAdminTeleport(bool allow));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetDeathDropAmount">SetDeathDropAmount on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetDeathDropAmount(int amount));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreateExplosion">CreateExplosion on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, CreateExplosion(float x, float y, float z, int type, float radius));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableZoneNames">EnableZoneNames on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EnableZoneNames(bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/UsePlayerPedAnims">UsePlayerPedAnims on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, UsePlayerPedAnims());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableInteriorEnterExits">DisableInteriorEnterExits on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisableInteriorEnterExits());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetNameTagDrawDistance">SetNameTagDrawDistance on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetNameTagDrawDistance(float distance));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableNameTagLOS">DisableNameTagLOS on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisableNameTagLOS());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/LimitGlobalChatRadius">LimitGlobalChatRadius on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, LimitGlobalChatRadius(float chat_radius));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/LimitPlayerMarkerRadius">LimitPlayerMarkerRadius on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, LimitPlayerMarkerRadius(float marker_radius));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ConnectNPC">ConnectNPC on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ConnectNPC(const char * name, const char * script));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerNPC">IsPlayerNPC on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerNPC(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerAdmin">IsPlayerAdmin on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerAdmin(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Kick">Kick on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Kick(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Ban">Ban on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Ban(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/BanEx">BanEx on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, BanEx(int playerid, const char * reason));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendRconCommand">SendRconCommand on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendRconCommand(const char * command));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetServerVarAsString">GetServerVarAsString on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetServerVarAsString(const char * varname, char * value, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetServerVarAsInt">GetServerVarAsInt on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetServerVarAsInt(const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetServerVarAsBool">GetServerVarAsBool on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetServerVarAsBool(const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerNetworkStats">GetPlayerNetworkStats on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerNetworkStats(int playerid, char * retstr, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetNetworkStats">GetNetworkStats on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetNetworkStats(char * retstr, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVersion">GetPlayerVersion on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerVersion(int playerid, char * version, int len));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/BlockIpAddress">BlockIpAddress on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, BlockIpAddress(const char * ip_address, int timems));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/UnBlockIpAddress">UnBlockIpAddress on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, UnBlockIpAddress(const char * ip_address));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetServerTickRate">GetServerTickRate on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetServerTickRate());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_GetConnectedTime">NetStats_GetConnectedTime on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_GetConnectedTime(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_MessagesReceived">NetStats_MessagesReceived on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_MessagesReceived(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_BytesReceived">NetStats_BytesReceived on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_BytesReceived(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_MessagesSent">NetStats_MessagesSent on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_MessagesSent(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_BytesSent">NetStats_BytesSent on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_BytesSent(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_MessagesRecvPerSecond">NetStats_MessagesRecvPerSecond on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_MessagesRecvPerSecond(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_PacketLossPercent">NetStats_PacketLossPercent on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, NetStats_PacketLossPercent(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_ConnectionStatus">NetStats_ConnectionStatus on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_ConnectionStatus(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_GetIpPort">NetStats_GetIpPort on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, NetStats_GetIpPort(int playerid, char * ip_port, int ip_port_len));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreateMenu">CreateMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreateMenu(const char * title, int columns, float x, float y, float col1width, float col2width));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DestroyMenu">DestroyMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DestroyMenu(int menuid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddMenuItem">AddMenuItem on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddMenuItem(int menuid, int column, const char * menutext));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetMenuColumnHeader">SetMenuColumnHeader on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetMenuColumnHeader(int menuid, int column, const char * columnheader));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowMenuForPlayer">ShowMenuForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowMenuForPlayer(int menuid, int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/HideMenuForPlayer">HideMenuForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, HideMenuForPlayer(int menuid, int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsValidMenu">IsValidMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsValidMenu(int menuid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableMenu">DisableMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisableMenu(int menuid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableMenuRow">DisableMenuRow on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisableMenuRow(int menuid, int row));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerMenu">GetPlayerMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerMenu(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawCreate">TextDrawCreate on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, TextDrawCreate(float x, float y, const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawDestroy">TextDrawDestroy on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawDestroy(int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawLetterSize">TextDrawLetterSize on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawLetterSize(int text, float x, float y));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawTextSize">TextDrawTextSize on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawTextSize(int text, float x, float y));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawAlignment">TextDrawAlignment on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawAlignment(int text, int alignment));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawColor">TextDrawColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawColor(int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawUseBox">TextDrawUseBox on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawUseBox(int text, bool use));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawBoxColor">TextDrawBoxColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawBoxColor(int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetShadow">TextDrawSetShadow on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetShadow(int text, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetOutline">TextDrawSetOutline on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetOutline(int text, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawBackgroundColor">TextDrawBackgroundColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawBackgroundColor(int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawFont">TextDrawFont on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawFont(int text, int font));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetProportional">TextDrawSetProportional on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetProportional(int text, bool set));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetSelectable">TextDrawSetSelectable on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetSelectable(int text, bool set));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawShowForPlayer">TextDrawShowForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawShowForPlayer(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawHideForPlayer">TextDrawHideForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawHideForPlayer(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawShowForAll">TextDrawShowForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawShowForAll(int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawHideForAll">TextDrawHideForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawHideForAll(int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetString">TextDrawSetString on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetString(int text, const char * string));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetPreviewModel">TextDrawSetPreviewModel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetPreviewModel(int text, int modelindex));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetPreviewRot">TextDrawSetPreviewRot on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetPreviewRot(int text, float fRotX, float fRotY, float fRotZ, float fZoom));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetPreviewVehCol">TextDrawSetPreviewVehCol on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetPreviewVehCol(int text, int color1, int color2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SelectTextDraw">SelectTextDraw on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SelectTextDraw(int playerid, int hovercolor));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CancelSelectTextDraw">CancelSelectTextDraw on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, CancelSelectTextDraw(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneCreate">GangZoneCreate on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GangZoneCreate(float minx, float miny, float maxx, float maxy));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneDestroy">GangZoneDestroy on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneDestroy(int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneShowForPlayer">GangZoneShowForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneShowForPlayer(int playerid, int zone, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneShowForAll">GangZoneShowForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneShowForAll(int zone, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneHideForPlayer">GangZoneHideForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneHideForPlayer(int playerid, int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneHideForAll">GangZoneHideForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneHideForAll(int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneFlashForPlayer">GangZoneFlashForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneFlashForPlayer(int playerid, int zone, int flashcolor));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneFlashForAll">GangZoneFlashForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneFlashForAll(int zone, int flashcolor));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneStopFlashForPlayer">GangZoneStopFlashForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneStopFlashForPlayer(int playerid, int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneStopFlashForAll">GangZoneStopFlashForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneStopFlashForAll(int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Create3DTextLabel">Create3DTextLabel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, Create3DTextLabel(const char * text, int color, float x, float y, float z, float DrawDistance, int virtualworld, bool testLOS));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Delete3DTextLabel">Delete3DTextLabel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Delete3DTextLabel(int id));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Attach3DTextLabelToPlayer">Attach3DTextLabelToPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Attach3DTextLabelToVehicle">Attach3DTextLabelToVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Update3DTextLabelText">Update3DTextLabelText on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Update3DTextLabelText(int id, int color, const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreatePlayer3DTextLabel">CreatePlayer3DTextLabel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreatePlayer3DTextLabel(int playerid, const char * text, int color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DeletePlayer3DTextLabel">DeletePlayer3DTextLabel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DeletePlayer3DTextLabel(int playerid, int id));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/UpdatePlayer3DTextLabelText">UpdatePlayer3DTextLabelText on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, UpdatePlayer3DTextLabelText(int playerid, int id, int color, const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowPlayerDialog">ShowPlayerDialog on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowPlayerDialog(int playerid, int dialogid, int style, const char * caption, const char * info, const char * button1, const char * button2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetTimer">SetTimer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, SetTimer(int interval, bool repeat, TimerCallback callback, void * param));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/KillTimer">KillTimer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, KillTimer(int timerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/gpci">gpci on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, gpci(int playerid, char * buffer, int size));

#define MAX_PLAYER_NAME (24)
#define MAX_CLIENT_MESSAGE (144)
#define MAX_PLAYERS (500)
#define MAX_VEHICLES (2000)
#define INVALID_PLAYER_ID (0xFFFF)
#define INVALID_VEHICLE_ID (0xFFFF)
#define NO_TEAM (255)
#define MAX_OBJECTS (1000)
#define INVALID_OBJECT_ID (0xFFFF)
#define MAX_GANG_ZONES (1024)
#define MAX_TEXT_DRAWS (2048)
#define MAX_PLAYER_TEXT_DRAWS (256)
#define MAX_MENUS (128)
#define MAX_3DTEXT_GLOBAL (1024)
#define MAX_3DTEXT_PLAYER (1024)
#define MAX_PICKUPS (4096)
#define INVALID_MENU (0xFF)
#define INVALID_TEXT_DRAW (0xFFFF)
#define INVALID_GANG_ZONE (-1)
#define INVALID_3DTEXT_ID (0xFFFF)
#define TEXT_DRAW_FONT_SPRITE_DRAW (4)
#define TEXT_DRAW_FONT_MODEL_PREVIEW (5)
#define DIALOG_STYLE_MSGBOX (0)
#define DIALOG_STYLE_INPUT (1)
#define DIALOG_STYLE_LIST (2)
#define DIALOG_STYLE_PASSWORD (3)
#define PLAYER_STATE_NONE (0)
#define PLAYER_STATE_ONFOOT (1)
#define PLAYER_STATE_DRIVER (2)
#define PLAYER_STATE_PASSENGER (3)
#define PLAYER_STATE_EXIT_VEHICLE (4)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER (5)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER (6)
#define PLAYER_STATE_WASTED (7)
#define PLAYER_STATE_SPAWNED (8)
#define PLAYER_STATE_SPECTATING (9)
#define PLAYER_MARKERS_MODE_OFF (0)
#define PLAYER_MARKERS_MODE_GLOBAL (1)
#define PLAYER_MARKERS_MODE_STREAMED (2)
#define WEAPON_BRASSKNUCKLE (1)
#define WEAPON_GOLFCLUB (2)
#define WEAPON_NITESTICK (3)
#define WEAPON_KNIFE (4)
#define WEAPON_BAT (5)
#define WEAPON_SHOVEL (6)
#define WEAPON_POOLSTICK (7)
#define WEAPON_KATANA (8)
#define WEAPON_CHAINSAW (9)
#define WEAPON_DILDO (10)
#define WEAPON_DILDO2 (11)
#define WEAPON_VIBRATOR (12)
#define WEAPON_VIBRATOR2 (13)
#define WEAPON_FLOWER (14)
#define WEAPON_CANE (15)
#define WEAPON_GRENADE (16)
#define WEAPON_TEARGAS (17)
#define WEAPON_MOLTOV (18)
#define WEAPON_COLT45 (22)
#define WEAPON_SILENCED (23)
#define WEAPON_DEAGLE (24)
#define WEAPON_SHOTGUN (25)
#define WEAPON_SAWEDOFF (26)
#define WEAPON_SHOTGSPA (27)
#define WEAPON_UZI (28)
#define WEAPON_MP5 (29)
#define WEAPON_AK47 (30)
#define WEAPON_M4 (31)
#define WEAPON_TEC9 (32)
#define WEAPON_RIFLE (33)
#define WEAPON_SNIPER (34)
#define WEAPON_ROCKETLAUNCHER (35)
#define WEAPON_HEATSEEKER (36)
#define WEAPON_FLAMETHROWER (37)
#define WEAPON_MINIGUN (38)
#define WEAPON_SATCHEL (39)
#define WEAPON_BOMB (40)
#define WEAPON_SPRAYCAN (41)
#define WEAPON_FIREEXTINGUISHER (42)
#define WEAPON_CAMERA (43)
#define WEAPON_PARACHUTE (46)
#define WEAPON_VEHICLE (49)
#define WEAPON_DROWN (53)
#define WEAPON_COLLISION (54)
#define KEY_ACTION (1)
#define KEY_CROUCH (2)
#define KEY_FIRE (4)
#define KEY_SPRINT (8)
#define KEY_SECONDARY_ATTACK (16)
#define KEY_JUMP (32)
#define KEY_LOOK_RIGHT (64)
#define KEY_HANDBRAKE (128)
#define KEY_LOOK_LEFT (256)
#define KEY_SUBMISSION (512)
#define KEY_LOOK_BEHIND (512)
#define KEY_WALK (1024)
#define KEY_ANALOG_UP (2048)
#define KEY_ANALOG_DOWN (4096)
#define KEY_ANALOG_LEFT (8192)
#define KEY_ANALOG_RIGHT (16384)
#define KEY_YES (65536)
#define KEY_NO (131072)
#define KEY_CTRL_BACK (262144)
#define KEY_UP (-128)
#define KEY_DOWN (128)
#define KEY_LEFT (-128)
#define KEY_RIGHT (128)
#define CLICK_SOURCE_SCOREBOARD (0)
#define EDIT_RESPONSE_CANCEL (0)
#define EDIT_RESPONSE_FINAL (1)
#define EDIT_RESPONSE_UPDATE (2)
#define SELECT_OBJECT_GLOBAL_OBJECT (1)
#define SELECT_OBJECT_PLAYER_OBJECT (2)
#define BULLET_HIT_TYPE_NONE (0)
#define BULLET_HIT_TYPE_PLAYER (1)
#define BULLET_HIT_TYPE_VEHICLE (2)
#define BULLET_HIT_TYPE_OBJECT (3)
#define BULLET_HIT_TYPE_PLAYER_OBJECT (4)


/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnGameModeInit">OnGameModeInit on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnGameModeInit());

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnGameModeExit">OnGameModeExit on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnGameModeExit());

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerConnect">OnPlayerConnect on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerConnect(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerDisconnect">OnPlayerDisconnect on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerDisconnect(int playerid, int reason));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerSpawn">OnPlayerSpawn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerSpawn(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerDeath">OnPlayerDeath on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerDeath(int playerid, int killerid, int reason));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleSpawn">OnVehicleSpawn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleSpawn(int vehicleid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleDeath">OnVehicleDeath on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleDeath(int vehicleid, int killerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerText">OnPlayerText on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerText(int playerid, const char * text));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerCommandText">OnPlayerCommandText on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerCommandText(int playerid, const char * cmdtext));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerRequestClass">OnPlayerRequestClass on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerRequestClass(int playerid, int classid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEnterVehicle">OnPlayerEnterVehicle on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerExitVehicle">OnPlayerExitVehicle on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerExitVehicle(int playerid, int vehicleid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerStateChange">OnPlayerStateChange on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerStateChange(int playerid, int newstate, int oldstate));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEnterCheckpoint">OnPlayerEnterCheckpoint on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEnterCheckpoint(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerLeaveCheckpoint">OnPlayerLeaveCheckpoint on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerLeaveCheckpoint(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEnterRaceCheckpoint">OnPlayerEnterRaceCheckpoint on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEnterRaceCheckpoint(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerLeaveRaceCheckpoint">OnPlayerLeaveRaceCheckpoint on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerLeaveRaceCheckpoint(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnRconCommand">OnRconCommand on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnRconCommand(const char * cmd));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerRequestSpawn">OnPlayerRequestSpawn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerRequestSpawn(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnObjectMoved">OnObjectMoved on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnObjectMoved(int objectid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerObjectMoved">OnPlayerObjectMoved on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerObjectMoved(int playerid, int objectid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerPickUpPickup">OnPlayerPickUpPickup on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerPickUpPickup(int playerid, int pickupid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleMod">OnVehicleMod on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleMod(int playerid, int vehicleid, int componentid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnEnterExitModShop">OnEnterExitModShop on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnEnterExitModShop(int playerid, int enterexit, int interiorid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehiclePaintjob">OnVehiclePaintjob on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleRespray">OnVehicleRespray on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleRespray(int playerid, int vehicleid, int color1, int color2));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleDamageStatusUpdate">OnVehicleDamageStatusUpdate on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleDamageStatusUpdate(int vehicleid, int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnUnoccupiedVehicleUpdate">OnUnoccupiedVehicleUpdate on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerSelectedMenuRow">OnPlayerSelectedMenuRow on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerSelectedMenuRow(int playerid, int row));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerExitedMenu">OnPlayerExitedMenu on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerExitedMenu(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerInteriorChange">OnPlayerInteriorChange on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerKeyStateChange">OnPlayerKeyStateChange on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnRconLoginAttempt">OnRconLoginAttempt on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnRconLoginAttempt(const char * ip, const char * password, bool success));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerUpdate">OnPlayerUpdate on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerUpdate(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerStreamIn">OnPlayerStreamIn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerStreamIn(int playerid, int forplayerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerStreamOut">OnPlayerStreamOut on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerStreamOut(int playerid, int forplayerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleStreamIn">OnVehicleStreamIn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleStreamIn(int vehicleid, int forplayerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleStreamOut">OnVehicleStreamOut on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleStreamOut(int vehicleid, int forplayerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnDialogResponse">OnDialogResponse on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerTakeDamage">OnPlayerTakeDamage on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerGiveDamage">OnPlayerGiveDamage on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerClickMap">OnPlayerClickMap on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerClickMap(int playerid, float fX, float fY, float fZ));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerClickTextDraw">OnPlayerClickTextDraw on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerClickTextDraw(int playerid, int clickedid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerClickPlayerTextDraw">OnPlayerClickPlayerTextDraw on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerClickPlayerTextDraw(int playerid, int playertextid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnIncomingConnection">OnIncomingConnection on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnIncomingConnection(int playerid, const char * ip_address, int port));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerClickPlayer">OnPlayerClickPlayer on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerClickPlayer(int playerid, int clickedplayerid, int source));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEditObject">OnPlayerEditObject on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEditAttachedObject">OnPlayerEditAttachedObject on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerSelectObject">OnPlayerSelectObject on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerWeaponShot">OnPlayerWeaponShot on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ));
