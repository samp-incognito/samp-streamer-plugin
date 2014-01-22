SAMPGDK_NATIVE(bool, SendClientMessage(int playerid, int color, const char * message)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SendClientMessage");
	sampgdk::FakeAmxHeapObject message_(message);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		color,
		message_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SendClientMessageToAll(int color, const char * message)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SendClientMessageToAll");
	sampgdk::FakeAmxHeapObject message_(message);
	cell params[] = {
		2 * sizeof(cell),
		color,
		message_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SendPlayerMessageToPlayer(int playerid, int senderid, const char * message)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SendPlayerMessageToPlayer");
	sampgdk::FakeAmxHeapObject message_(message);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		senderid,
		message_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SendPlayerMessageToAll(int senderid, const char * message)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SendPlayerMessageToAll");
	sampgdk::FakeAmxHeapObject message_(message);
	cell params[] = {
		2 * sizeof(cell),
		senderid,
		message_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SendDeathMessage(int killer, int killee, int weapon)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SendDeathMessage");
	cell params[] = {
		3 * sizeof(cell),
		killer,
		killee,
		weapon
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GameTextForAll(const char * text, int time, int style)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GameTextForAll");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		3 * sizeof(cell),
		text_.address(),
		time,
		style
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GameTextForPlayer(int playerid, const char * text, int time, int style)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GameTextForPlayer");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		text_.address(),
		time,
		style
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetTickCount()) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetTickCount");
	return sampgdk::FakeAmx::CallNative(native);
}

SAMPGDK_NATIVE(int, GetMaxPlayers()) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetMaxPlayers");
	return sampgdk::FakeAmx::CallNative(native);
}

SAMPGDK_NATIVE(bool, SetGameModeText(const char * text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetGameModeText");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		1 * sizeof(cell),
		text_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetTeamCount(int count)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetTeamCount");
	cell params[] = {
		1 * sizeof(cell),
		count
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AddPlayerClass");
	cell params[] = {
		11 * sizeof(cell),
		modelid,
		amx_ftoc(spawn_x),
		amx_ftoc(spawn_y),
		amx_ftoc(spawn_z),
		amx_ftoc(z_angle),
		weapon1,
		weapon1_ammo,
		weapon2,
		weapon2_ammo,
		weapon3,
		weapon3_ammo
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AddPlayerClassEx");
	cell params[] = {
		12 * sizeof(cell),
		teamid,
		modelid,
		amx_ftoc(spawn_x),
		amx_ftoc(spawn_y),
		amx_ftoc(spawn_z),
		amx_ftoc(z_angle),
		weapon1,
		weapon1_ammo,
		weapon2,
		weapon2_ammo,
		weapon3,
		weapon3_ammo
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AddStaticVehicle");
	cell params[] = {
		7 * sizeof(cell),
		modelid,
		amx_ftoc(spawn_x),
		amx_ftoc(spawn_y),
		amx_ftoc(spawn_z),
		amx_ftoc(z_angle),
		color1,
		color2
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AddStaticVehicleEx");
	cell params[] = {
		8 * sizeof(cell),
		modelid,
		amx_ftoc(spawn_x),
		amx_ftoc(spawn_y),
		amx_ftoc(spawn_z),
		amx_ftoc(z_angle),
		color1,
		color2,
		respawn_delay
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, AddStaticPickup(int model, int type, float x, float y, float z, int virtualworld)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AddStaticPickup");
	cell params[] = {
		6 * sizeof(cell),
		model,
		type,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		virtualworld
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, CreatePickup(int model, int type, float x, float y, float z, int virtualworld)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CreatePickup");
	cell params[] = {
		6 * sizeof(cell),
		model,
		type,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		virtualworld
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, DestroyPickup(int pickup)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DestroyPickup");
	cell params[] = {
		1 * sizeof(cell),
		pickup
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ShowNameTags(bool show)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ShowNameTags");
	cell params[] = {
		1 * sizeof(cell),
		show
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ShowPlayerMarkers(bool mode)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ShowPlayerMarkers");
	cell params[] = {
		1 * sizeof(cell),
		mode
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GameModeExit()) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GameModeExit");
	return sampgdk::FakeAmx::CallNativeBool(native);
}

SAMPGDK_NATIVE(bool, SetWorldTime(int hour)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetWorldTime");
	cell params[] = {
		1 * sizeof(cell),
		hour
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetWeaponName(int weaponid, char * name, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetWeaponName");
	sampgdk::FakeAmxHeapObject name_(size);
	cell params[] = {
		3 * sizeof(cell),
		weaponid,
		name_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	name_.GetAsString(name, size);
	return retval;
}

SAMPGDK_NATIVE(bool, EnableTirePopping(bool enable)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("EnableTirePopping");
	cell params[] = {
		1 * sizeof(cell),
		enable
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, AllowInteriorWeapons(bool allow)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AllowInteriorWeapons");
	cell params[] = {
		1 * sizeof(cell),
		allow
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetWeather(int weatherid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetWeather");
	cell params[] = {
		1 * sizeof(cell),
		weatherid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetGravity(float gravity)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetGravity");
	cell params[] = {
		1 * sizeof(cell),
		amx_ftoc(gravity)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, AllowAdminTeleport(bool allow)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AllowAdminTeleport");
	cell params[] = {
		1 * sizeof(cell),
		allow
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetDeathDropAmount(int amount)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetDeathDropAmount");
	cell params[] = {
		1 * sizeof(cell),
		amount
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, CreateExplosion(float x, float y, float z, int type, float radius)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CreateExplosion");
	cell params[] = {
		5 * sizeof(cell),
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		type,
		amx_ftoc(radius)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, EnableZoneNames(bool enable)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("EnableZoneNames");
	cell params[] = {
		1 * sizeof(cell),
		enable
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, UsePlayerPedAnims()) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("UsePlayerPedAnims");
	return sampgdk::FakeAmx::CallNativeBool(native);
}

SAMPGDK_NATIVE(bool, DisableInteriorEnterExits()) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DisableInteriorEnterExits");
	return sampgdk::FakeAmx::CallNativeBool(native);
}

SAMPGDK_NATIVE(bool, SetNameTagDrawDistance(float distance)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetNameTagDrawDistance");
	cell params[] = {
		1 * sizeof(cell),
		amx_ftoc(distance)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, DisableNameTagLOS()) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DisableNameTagLOS");
	return sampgdk::FakeAmx::CallNativeBool(native);
}

SAMPGDK_NATIVE(bool, LimitGlobalChatRadius(float chat_radius)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("LimitGlobalChatRadius");
	cell params[] = {
		1 * sizeof(cell),
		amx_ftoc(chat_radius)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, LimitPlayerMarkerRadius(float marker_radius)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("LimitPlayerMarkerRadius");
	cell params[] = {
		1 * sizeof(cell),
		amx_ftoc(marker_radius)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ConnectNPC(const char * name, const char * script)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ConnectNPC");
	sampgdk::FakeAmxHeapObject name_(name);
	sampgdk::FakeAmxHeapObject script_(script);
	cell params[] = {
		2 * sizeof(cell),
		name_.address(),
		script_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerNPC(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerNPC");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerAdmin(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerAdmin");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, Kick(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("Kick");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, Ban(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("Ban");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, BanEx(int playerid, const char * reason)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("BanEx");
	sampgdk::FakeAmxHeapObject reason_(reason);
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		reason_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SendRconCommand(const char * command)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SendRconCommand");
	sampgdk::FakeAmxHeapObject command_(command);
	cell params[] = {
		1 * sizeof(cell),
		command_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetServerVarAsString(const char * varname, char * value, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetServerVarAsString");
	sampgdk::FakeAmxHeapObject varname_(varname);
	sampgdk::FakeAmxHeapObject value_(size);
	cell params[] = {
		3 * sizeof(cell),
		varname_.address(),
		value_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	value_.GetAsString(value, size);
	return retval;
}

SAMPGDK_NATIVE(int, GetServerVarAsInt(const char * varname)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetServerVarAsInt");
	sampgdk::FakeAmxHeapObject varname_(varname);
	cell params[] = {
		1 * sizeof(cell),
		varname_.address()
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, GetServerVarAsBool(const char * varname)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetServerVarAsBool");
	sampgdk::FakeAmxHeapObject varname_(varname);
	cell params[] = {
		1 * sizeof(cell),
		varname_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerNetworkStats(int playerid, char * retstr, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerNetworkStats");
	sampgdk::FakeAmxHeapObject retstr_(size);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		retstr_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	retstr_.GetAsString(retstr, size);
	return retval;
}

SAMPGDK_NATIVE(bool, GetNetworkStats(char * retstr, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetNetworkStats");
	sampgdk::FakeAmxHeapObject retstr_(size);
	cell params[] = {
		2 * sizeof(cell),
		retstr_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	retstr_.GetAsString(retstr, size);
	return retval;
}

SAMPGDK_NATIVE(bool, GetPlayerVersion(int playerid, char * version, int len)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerVersion");
	sampgdk::FakeAmxHeapObject version_(len);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		version_.address(),
		len
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	version_.GetAsString(version, len);
	return retval;
}

SAMPGDK_NATIVE(int, CreateMenu(const char * title, int columns, float x, float y, float col1width, float col2width)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CreateMenu");
	sampgdk::FakeAmxHeapObject title_(title);
	cell params[] = {
		6 * sizeof(cell),
		title_.address(),
		columns,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(col1width),
		amx_ftoc(col2width)
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, DestroyMenu(int menuid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DestroyMenu");
	cell params[] = {
		1 * sizeof(cell),
		menuid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, AddMenuItem(int menuid, int column, const char * menutext)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AddMenuItem");
	sampgdk::FakeAmxHeapObject menutext_(menutext);
	cell params[] = {
		3 * sizeof(cell),
		menuid,
		column,
		menutext_.address()
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetMenuColumnHeader(int menuid, int column, const char * columnheader)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetMenuColumnHeader");
	sampgdk::FakeAmxHeapObject columnheader_(columnheader);
	cell params[] = {
		3 * sizeof(cell),
		menuid,
		column,
		columnheader_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ShowMenuForPlayer(int menuid, int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ShowMenuForPlayer");
	cell params[] = {
		2 * sizeof(cell),
		menuid,
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, HideMenuForPlayer(int menuid, int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("HideMenuForPlayer");
	cell params[] = {
		2 * sizeof(cell),
		menuid,
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsValidMenu(int menuid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsValidMenu");
	cell params[] = {
		1 * sizeof(cell),
		menuid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, DisableMenu(int menuid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DisableMenu");
	cell params[] = {
		1 * sizeof(cell),
		menuid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, DisableMenuRow(int menuid, int row)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DisableMenuRow");
	cell params[] = {
		2 * sizeof(cell),
		menuid,
		row
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerMenu(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerMenu");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, TextDrawCreate(float x, float y, const char * text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawCreate");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		3 * sizeof(cell),
		amx_ftoc(x),
		amx_ftoc(y),
		text_.address()
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawDestroy(int text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawDestroy");
	cell params[] = {
		1 * sizeof(cell),
		text
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawLetterSize(int text, float x, float y)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawLetterSize");
	cell params[] = {
		3 * sizeof(cell),
		text,
		amx_ftoc(x),
		amx_ftoc(y)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawTextSize(int text, float x, float y)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawTextSize");
	cell params[] = {
		3 * sizeof(cell),
		text,
		amx_ftoc(x),
		amx_ftoc(y)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawAlignment(int text, int alignment)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawAlignment");
	cell params[] = {
		2 * sizeof(cell),
		text,
		alignment
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawColor(int text, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawColor");
	cell params[] = {
		2 * sizeof(cell),
		text,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawUseBox(int text, bool use)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawUseBox");
	cell params[] = {
		2 * sizeof(cell),
		text,
		use
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawBoxColor(int text, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawBoxColor");
	cell params[] = {
		2 * sizeof(cell),
		text,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawSetShadow(int text, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawSetShadow");
	cell params[] = {
		2 * sizeof(cell),
		text,
		size
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawSetOutline(int text, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawSetOutline");
	cell params[] = {
		2 * sizeof(cell),
		text,
		size
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawBackgroundColor(int text, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawBackgroundColor");
	cell params[] = {
		2 * sizeof(cell),
		text,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawFont(int text, int font)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawFont");
	cell params[] = {
		2 * sizeof(cell),
		text,
		font
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawSetProportional(int text, bool set)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawSetProportional");
	cell params[] = {
		2 * sizeof(cell),
		text,
		set
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawSetSelectable(int text, bool set)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawSetSelectable");
	cell params[] = {
		2 * sizeof(cell),
		text,
		set
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawShowForPlayer(int playerid, int text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawShowForPlayer");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		text
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawHideForPlayer(int playerid, int text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawHideForPlayer");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		text
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawShowForAll(int text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawShowForAll");
	cell params[] = {
		1 * sizeof(cell),
		text
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawHideForAll(int text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawHideForAll");
	cell params[] = {
		1 * sizeof(cell),
		text
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TextDrawSetString(int text, const char * string)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TextDrawSetString");
	sampgdk::FakeAmxHeapObject string_(string);
	cell params[] = {
		2 * sizeof(cell),
		text,
		string_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SelectTextDraw(int playerid, int hovercolor)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SelectTextDraw");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		hovercolor
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, CancelSelectTextDraw(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CancelSelectTextDraw");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GangZoneCreate(float minx, float miny, float maxx, float maxy)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneCreate");
	cell params[] = {
		4 * sizeof(cell),
		amx_ftoc(minx),
		amx_ftoc(miny),
		amx_ftoc(maxx),
		amx_ftoc(maxy)
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneDestroy(int zone)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneDestroy");
	cell params[] = {
		1 * sizeof(cell),
		zone
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneShowForPlayer(int playerid, int zone, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneShowForPlayer");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		zone,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneShowForAll(int zone, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneShowForAll");
	cell params[] = {
		2 * sizeof(cell),
		zone,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneHideForPlayer(int playerid, int zone)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneHideForPlayer");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		zone
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneHideForAll(int zone)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneHideForAll");
	cell params[] = {
		1 * sizeof(cell),
		zone
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneFlashForPlayer(int playerid, int zone, int flashcolor)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneFlashForPlayer");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		zone,
		flashcolor
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneFlashForAll(int zone, int flashcolor)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneFlashForAll");
	cell params[] = {
		2 * sizeof(cell),
		zone,
		flashcolor
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneStopFlashForPlayer(int playerid, int zone)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneStopFlashForPlayer");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		zone
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GangZoneStopFlashForAll(int zone)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GangZoneStopFlashForAll");
	cell params[] = {
		1 * sizeof(cell),
		zone
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, Create3DTextLabel(const char * text, int color, float x, float y, float z, float DrawDistance, int virtualworld, bool testLOS)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("Create3DTextLabel");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		8 * sizeof(cell),
		text_.address(),
		color,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(DrawDistance),
		virtualworld,
		testLOS
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, Delete3DTextLabel(int id)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("Delete3DTextLabel");
	cell params[] = {
		1 * sizeof(cell),
		id
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("Attach3DTextLabelToPlayer");
	cell params[] = {
		5 * sizeof(cell),
		id,
		playerid,
		amx_ftoc(OffsetX),
		amx_ftoc(OffsetY),
		amx_ftoc(OffsetZ)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("Attach3DTextLabelToVehicle");
	cell params[] = {
		5 * sizeof(cell),
		id,
		vehicleid,
		amx_ftoc(OffsetX),
		amx_ftoc(OffsetY),
		amx_ftoc(OffsetZ)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, Update3DTextLabelText(int id, int color, const char * text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("Update3DTextLabelText");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		3 * sizeof(cell),
		id,
		color,
		text_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, CreatePlayer3DTextLabel(int playerid, const char * text, int color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CreatePlayer3DTextLabel");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		10 * sizeof(cell),
		playerid,
		text_.address(),
		color,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(DrawDistance),
		attachedplayer,
		attachedvehicle,
		testLOS
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, DeletePlayer3DTextLabel(int playerid, int id)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DeletePlayer3DTextLabel");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		id
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, UpdatePlayer3DTextLabelText(int playerid, int id, int color, const char * text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("UpdatePlayer3DTextLabelText");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		id,
		color,
		text_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ShowPlayerDialog(int playerid, int dialogid, int style, const char * caption, const char * info, const char * button1, const char * button2)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ShowPlayerDialog");
	sampgdk::FakeAmxHeapObject caption_(caption);
	sampgdk::FakeAmxHeapObject info_(info);
	sampgdk::FakeAmxHeapObject button1_(button1);
	sampgdk::FakeAmxHeapObject button2_(button2);
	cell params[] = {
		7 * sizeof(cell),
		playerid,
		dialogid,
		style,
		caption_.address(),
		info_.address(),
		button1_.address(),
		button2_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, gpci(int playerid, char * buffer, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("gpci");
	sampgdk::FakeAmxHeapObject buffer_(size);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		buffer_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	buffer_.GetAsString(buffer, size);
	return retval;
}

