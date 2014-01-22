SAMPGDK_NATIVE(bool, SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetSpawnInfo");
	cell params[] = {
		13 * sizeof(cell),
		playerid,
		team,
		skin,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(rotation),
		weapon1,
		weapon1_ammo,
		weapon2,
		weapon2_ammo,
		weapon3,
		weapon3_ammo
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SpawnPlayer(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SpawnPlayer");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerPos(int playerid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerPos");
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerPosFindZ(int playerid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerPosFindZ");
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerPos(int playerid, float * x, float * y, float * z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerPos");
	sampgdk::FakeAmxHeapObject x_;
	sampgdk::FakeAmxHeapObject y_;
	sampgdk::FakeAmxHeapObject z_;
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, SetPlayerFacingAngle(int playerid, float angle)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerFacingAngle");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		amx_ftoc(angle)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerFacingAngle(int playerid, float * angle)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerFacingAngle");
	sampgdk::FakeAmxHeapObject angle_;
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		angle_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*angle = angle_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerInRangeOfPoint");
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		amx_ftoc(range),
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(float, GetPlayerDistanceFromPoint(int playerid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerDistanceFromPoint");
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeFloat(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerStreamedIn(int playerid, int forplayerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerStreamedIn");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		forplayerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerInterior(int playerid, int interiorid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerInterior");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		interiorid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerInterior(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerInterior");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerHealth(int playerid, float health)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerHealth");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		amx_ftoc(health)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerHealth(int playerid, float * health)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerHealth");
	sampgdk::FakeAmxHeapObject health_;
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		health_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*health = health_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, SetPlayerArmour(int playerid, float armour)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerArmour");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		amx_ftoc(armour)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerArmour(int playerid, float * armour)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerArmour");
	sampgdk::FakeAmxHeapObject armour_;
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		armour_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*armour = armour_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, SetPlayerAmmo(int playerid, int weaponslot, int ammo)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerAmmo");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		weaponslot,
		ammo
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerAmmo(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerAmmo");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerWeaponState(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerWeaponState");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerTargetPlayer(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerTargetPlayer");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerTeam(int playerid, int teamid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerTeam");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		teamid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerTeam(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerTeam");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerScore(int playerid, int score)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerScore");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		score
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerScore(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerScore");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerDrunkLevel(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerDrunkLevel");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerDrunkLevel(int playerid, int level)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerDrunkLevel");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		level
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerColor(int playerid, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerColor");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerColor(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerColor");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerSkin(int playerid, int skinid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerSkin");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		skinid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerSkin(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerSkin");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, GivePlayerWeapon(int playerid, int weaponid, int ammo)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GivePlayerWeapon");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		weaponid,
		ammo
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ResetPlayerWeapons(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ResetPlayerWeapons");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerArmedWeapon(int playerid, int weaponid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerArmedWeapon");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		weaponid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerWeaponData(int playerid, int slot, int * weapon, int * ammo)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerWeaponData");
	sampgdk::FakeAmxHeapObject weapon_;
	sampgdk::FakeAmxHeapObject ammo_;
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		slot,
		weapon_.address(),
		ammo_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*weapon = weapon_.Get();
	*ammo = ammo_.Get();
	return retval;
}

SAMPGDK_NATIVE(bool, GivePlayerMoney(int playerid, int money)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GivePlayerMoney");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		money
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ResetPlayerMoney(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ResetPlayerMoney");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, SetPlayerName(int playerid, const char * name)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerName");
	sampgdk::FakeAmxHeapObject name_(name);
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		name_.address()
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerMoney(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerMoney");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerState(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerState");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerIp(int playerid, char * ip, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerIp");
	sampgdk::FakeAmxHeapObject ip_(size);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		ip_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	ip_.GetAsString(ip, size);
	return retval;
}

SAMPGDK_NATIVE(int, GetPlayerPing(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerPing");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerWeapon(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerWeapon");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerKeys(int playerid, int * keys, int * updown, int * leftright)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerKeys");
	sampgdk::FakeAmxHeapObject keys_;
	sampgdk::FakeAmxHeapObject updown_;
	sampgdk::FakeAmxHeapObject leftright_;
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		keys_.address(),
		updown_.address(),
		leftright_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*keys = keys_.Get();
	*updown = updown_.Get();
	*leftright = leftright_.Get();
	return retval;
}

SAMPGDK_NATIVE(bool, GetPlayerName(int playerid, char * name, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerName");
	sampgdk::FakeAmxHeapObject name_(size);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		name_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	name_.GetAsString(name, size);
	return retval;
}

SAMPGDK_NATIVE(bool, SetPlayerTime(int playerid, int hour, int minute)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerTime");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		hour,
		minute
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerTime(int playerid, int * hour, int * minute)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerTime");
	sampgdk::FakeAmxHeapObject hour_;
	sampgdk::FakeAmxHeapObject minute_;
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		hour_.address(),
		minute_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*hour = hour_.Get();
	*minute = minute_.Get();
	return retval;
}

SAMPGDK_NATIVE(bool, TogglePlayerClock(int playerid, bool toggle)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TogglePlayerClock");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		toggle
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerWeather(int playerid, int weather)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerWeather");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		weather
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ForceClassSelection(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ForceClassSelection");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerWantedLevel(int playerid, int level)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerWantedLevel");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		level
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerWantedLevel(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerWantedLevel");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerFightingStyle(int playerid, int style)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerFightingStyle");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		style
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerFightingStyle(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerFightingStyle");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerVelocity(int playerid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerVelocity");
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerVelocity(int playerid, float * x, float * y, float * z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerVelocity");
	sampgdk::FakeAmxHeapObject x_;
	sampgdk::FakeAmxHeapObject y_;
	sampgdk::FakeAmxHeapObject z_;
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, PlayCrimeReportForPlayer(int playerid, int suspectid, int crime)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayCrimeReportForPlayer");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		suspectid,
		crime
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayAudioStreamForPlayer(int playerid, const char * url, float posX, float posY, float posZ, float distance, bool usepos)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayAudioStreamForPlayer");
	sampgdk::FakeAmxHeapObject url_(url);
	cell params[] = {
		7 * sizeof(cell),
		playerid,
		url_.address(),
		amx_ftoc(posX),
		amx_ftoc(posY),
		amx_ftoc(posZ),
		amx_ftoc(distance),
		usepos
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, StopAudioStreamForPlayer(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("StopAudioStreamForPlayer");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerShopName(int playerid, const char * shopname)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerShopName");
	sampgdk::FakeAmxHeapObject shopname_(shopname);
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		shopname_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerSkillLevel(int playerid, int skill, int level)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerSkillLevel");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		skill,
		level
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerSurfingVehicleID(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerSurfingVehicleID");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerSurfingObjectID(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerSurfingObjectID");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("RemoveBuildingForPlayer");
	cell params[] = {
		6 * sizeof(cell),
		playerid,
		modelid,
		amx_ftoc(fX),
		amx_ftoc(fY),
		amx_ftoc(fZ),
		amx_ftoc(fRadius)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ, int materialcolor1, int materialcolor2)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerAttachedObject");
	cell params[] = {
		15 * sizeof(cell),
		playerid,
		index,
		modelid,
		bone,
		amx_ftoc(fOffsetX),
		amx_ftoc(fOffsetY),
		amx_ftoc(fOffsetZ),
		amx_ftoc(fRotX),
		amx_ftoc(fRotY),
		amx_ftoc(fRotZ),
		amx_ftoc(fScaleX),
		amx_ftoc(fScaleY),
		amx_ftoc(fScaleZ),
		materialcolor1,
		materialcolor2
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, RemovePlayerAttachedObject(int playerid, int index)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("RemovePlayerAttachedObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		index
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerAttachedObjectSlotUsed(int playerid, int index)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerAttachedObjectSlotUsed");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		index
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, EditAttachedObject(int playerid, int index)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("EditAttachedObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		index
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, CreatePlayerTextDraw(int playerid, float x, float y, const char * text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CreatePlayerTextDraw");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		text_.address()
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawDestroy(int playerid, int text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawDestroy");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		text
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawLetterSize(int playerid, int text, float x, float y)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawLetterSize");
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		text,
		amx_ftoc(x),
		amx_ftoc(y)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawTextSize(int playerid, int text, float x, float y)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawTextSize");
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		text,
		amx_ftoc(x),
		amx_ftoc(y)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawAlignment(int playerid, int text, int alignment)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawAlignment");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		alignment
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawColor(int playerid, int text, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawColor");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawUseBox(int playerid, int text, bool use)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawUseBox");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		use
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawBoxColor(int playerid, int text, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawBoxColor");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetShadow(int playerid, int text, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawSetShadow");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		size
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetOutline(int playerid, int text, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawSetOutline");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		size
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawBackgroundColor(int playerid, int text, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawBackgroundColor");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawFont(int playerid, int text, int font)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawFont");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		font
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetProportional(int playerid, int text, bool set)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawSetProportional");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		set
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetSelectable(int playerid, int text, bool set)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawSetSelectable");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		set
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawShow(int playerid, int text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawShow");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		text
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawHide(int playerid, int text)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawHide");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		text
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetString(int playerid, int text, const char * string)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerTextDrawSetString");
	sampgdk::FakeAmxHeapObject string_(string);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		text,
		string_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPVarInt(int playerid, const char * varname, int value)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPVarInt");
	sampgdk::FakeAmxHeapObject varname_(varname);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		varname_.address(),
		value
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPVarInt(int playerid, const char * varname)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPVarInt");
	sampgdk::FakeAmxHeapObject varname_(varname);
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		varname_.address()
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPVarString(int playerid, const char * varname, const char * value)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPVarString");
	sampgdk::FakeAmxHeapObject varname_(varname);
	sampgdk::FakeAmxHeapObject value_(value);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		varname_.address(),
		value_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPVarString(int playerid, const char * varname, char * value, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPVarString");
	sampgdk::FakeAmxHeapObject varname_(varname);
	sampgdk::FakeAmxHeapObject value_(size);
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		varname_.address(),
		value_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	value_.GetAsString(value, size);
	return retval;
}

SAMPGDK_NATIVE(bool, SetPVarFloat(int playerid, const char * varname, float value)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPVarFloat");
	sampgdk::FakeAmxHeapObject varname_(varname);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		varname_.address(),
		amx_ftoc(value)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(float, GetPVarFloat(int playerid, const char * varname)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPVarFloat");
	sampgdk::FakeAmxHeapObject varname_(varname);
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		varname_.address()
	};
	return sampgdk::FakeAmx::CallNativeFloat(native, params);
}

SAMPGDK_NATIVE(bool, DeletePVar(int playerid, const char * varname)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DeletePVar");
	sampgdk::FakeAmxHeapObject varname_(varname);
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		varname_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPVarsUpperIndex(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPVarsUpperIndex");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, GetPVarNameAtIndex(int playerid, int index, char * varname, int size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPVarNameAtIndex");
	sampgdk::FakeAmxHeapObject varname_(size);
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		index,
		varname_.address(),
		size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	varname_.GetAsString(varname, size);
	return retval;
}

SAMPGDK_NATIVE(int, GetPVarType(int playerid, const char * varname)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPVarType");
	sampgdk::FakeAmxHeapObject varname_(varname);
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		varname_.address()
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerChatBubble(int playerid, const char * text, int color, float drawdistance, int expiretime)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerChatBubble");
	sampgdk::FakeAmxHeapObject text_(text);
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		text_.address(),
		color,
		amx_ftoc(drawdistance),
		expiretime
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PutPlayerInVehicle(int playerid, int vehicleid, int seatid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PutPlayerInVehicle");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		vehicleid,
		seatid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerVehicleID(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerVehicleID");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerVehicleSeat(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerVehicleSeat");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, RemovePlayerFromVehicle(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("RemovePlayerFromVehicle");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TogglePlayerControllable(int playerid, bool toggle)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TogglePlayerControllable");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		toggle
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerPlaySound(int playerid, int soundid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerPlaySound");
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		soundid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ApplyAnimation(int playerid, const char * animlib, const char * animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ApplyAnimation");
	sampgdk::FakeAmxHeapObject animlib_(animlib);
	sampgdk::FakeAmxHeapObject animname_(animname);
	cell params[] = {
		10 * sizeof(cell),
		playerid,
		animlib_.address(),
		animname_.address(),
		amx_ftoc(fDelta),
		loop,
		lockx,
		locky,
		freeze,
		time,
		forcesync
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ClearAnimations(int playerid, bool forcesync)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ClearAnimations");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		forcesync
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerAnimationIndex(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerAnimationIndex");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, GetAnimationName(int index, char * animlib, int animlib_size, char * animname, int animname_size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetAnimationName");
	sampgdk::FakeAmxHeapObject animlib_(animlib_size);
	sampgdk::FakeAmxHeapObject animname_(animname_size);
	cell params[] = {
		5 * sizeof(cell),
		index,
		animlib_.address(),
		animlib_size,
		animname_.address(),
		animname_size
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	animlib_.GetAsString(animlib, animlib_size);
	animname_.GetAsString(animname, animname_size);
	return retval;
}

SAMPGDK_NATIVE(int, GetPlayerSpecialAction(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerSpecialAction");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerSpecialAction(int playerid, int actionid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerSpecialAction");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		actionid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerCheckpoint(int playerid, float x, float y, float z, float size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerCheckpoint");
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(size)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, DisablePlayerCheckpoint(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DisablePlayerCheckpoint");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerRaceCheckpoint");
	cell params[] = {
		9 * sizeof(cell),
		playerid,
		type,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(nextx),
		amx_ftoc(nexty),
		amx_ftoc(nextz),
		amx_ftoc(size)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, DisablePlayerRaceCheckpoint(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DisablePlayerRaceCheckpoint");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerWorldBounds");
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		amx_ftoc(x_max),
		amx_ftoc(x_min),
		amx_ftoc(y_max),
		amx_ftoc(y_min)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerMarkerForPlayer");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		showplayerid,
		color
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ShowPlayerNameTagForPlayer");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		showplayerid,
		show
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerMapIcon");
	cell params[] = {
		8 * sizeof(cell),
		playerid,
		iconid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		markertype,
		color,
		style
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, RemovePlayerMapIcon(int playerid, int iconid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("RemovePlayerMapIcon");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		iconid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, AllowPlayerTeleport(int playerid, bool allow)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AllowPlayerTeleport");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		allow
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerCameraPos(int playerid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerCameraPos");
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerCameraLookAt");
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		cut
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetCameraBehindPlayer(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetCameraBehindPlayer");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerCameraPos(int playerid, float * x, float * y, float * z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerCameraPos");
	sampgdk::FakeAmxHeapObject x_;
	sampgdk::FakeAmxHeapObject y_;
	sampgdk::FakeAmxHeapObject z_;
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, GetPlayerCameraFrontVector(int playerid, float * x, float * y, float * z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerCameraFrontVector");
	sampgdk::FakeAmxHeapObject x_;
	sampgdk::FakeAmxHeapObject y_;
	sampgdk::FakeAmxHeapObject z_;
	cell params[] = {
		4 * sizeof(cell),
		playerid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(int, GetPlayerCameraMode(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerCameraMode");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, AttachCameraToObject(int playerid, int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AttachCameraToObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, AttachCameraToPlayerObject(int playerid, int playerobjectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AttachCameraToPlayerObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		playerobjectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("InterpolateCameraPos");
	cell params[] = {
		9 * sizeof(cell),
		playerid,
		amx_ftoc(FromX),
		amx_ftoc(FromY),
		amx_ftoc(FromZ),
		amx_ftoc(ToX),
		amx_ftoc(ToY),
		amx_ftoc(ToZ),
		time,
		cut
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("InterpolateCameraLookAt");
	cell params[] = {
		9 * sizeof(cell),
		playerid,
		amx_ftoc(FromX),
		amx_ftoc(FromY),
		amx_ftoc(FromZ),
		amx_ftoc(ToX),
		amx_ftoc(ToY),
		amx_ftoc(ToZ),
		time,
		cut
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerConnected(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerConnected");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerInVehicle(int playerid, int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerInVehicle");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		vehicleid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerInAnyVehicle(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerInAnyVehicle");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerInCheckpoint(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerInCheckpoint");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerInRaceCheckpoint(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerInRaceCheckpoint");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerVirtualWorld(int playerid, int worldid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerVirtualWorld");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		worldid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetPlayerVirtualWorld(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerVirtualWorld");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, EnableStuntBonusForPlayer(int playerid, bool enable)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("EnableStuntBonusForPlayer");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		enable
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, EnableStuntBonusForAll(bool enable)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("EnableStuntBonusForAll");
	cell params[] = {
		1 * sizeof(cell),
		enable
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, TogglePlayerSpectating(int playerid, bool toggle)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("TogglePlayerSpectating");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		toggle
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerSpectatePlayer(int playerid, int targetplayerid, int mode)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerSpectatePlayer");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		targetplayerid,
		mode
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("PlayerSpectateVehicle");
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		targetvehicleid,
		mode
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, StartRecordingPlayerData(int playerid, int recordtype, const char * recordname)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("StartRecordingPlayerData");
	sampgdk::FakeAmxHeapObject recordname_(recordname);
	cell params[] = {
		3 * sizeof(cell),
		playerid,
		recordtype,
		recordname_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, StopRecordingPlayerData(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("StopRecordingPlayerData");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

