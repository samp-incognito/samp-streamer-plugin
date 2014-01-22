SAMPGDK_NATIVE(int, CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CreateObject");
	cell params[] = {
		8 * sizeof(cell),
		modelid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(rX),
		amx_ftoc(rY),
		amx_ftoc(rZ),
		amx_ftoc(DrawDistance)
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AttachObjectToVehicle");
	cell params[] = {
		8 * sizeof(cell),
		objectid,
		vehicleid,
		amx_ftoc(fOffsetX),
		amx_ftoc(fOffsetY),
		amx_ftoc(fOffsetZ),
		amx_ftoc(fRotX),
		amx_ftoc(fRotY),
		amx_ftoc(fRotZ)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, AttachObjectToObject(int objectid, int attachtoid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AttachObjectToObject");
	cell params[] = {
		9 * sizeof(cell),
		objectid,
		attachtoid,
		amx_ftoc(fOffsetX),
		amx_ftoc(fOffsetY),
		amx_ftoc(fOffsetZ),
		amx_ftoc(fRotX),
		amx_ftoc(fRotY),
		amx_ftoc(fRotZ),
		SyncRotation
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, AttachObjectToPlayer(int objectid, int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AttachObjectToPlayer");
	cell params[] = {
		8 * sizeof(cell),
		objectid,
		playerid,
		amx_ftoc(fOffsetX),
		amx_ftoc(fOffsetY),
		amx_ftoc(fOffsetZ),
		amx_ftoc(fRotX),
		amx_ftoc(fRotY),
		amx_ftoc(fRotZ)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetObjectPos(int objectid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetObjectPos");
	cell params[] = {
		4 * sizeof(cell),
		objectid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetObjectPos(int objectid, float * x, float * y, float * z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetObjectPos");
	sampgdk::FakeAmxHeapObject x_;
	sampgdk::FakeAmxHeapObject y_;
	sampgdk::FakeAmxHeapObject z_;
	cell params[] = {
		4 * sizeof(cell),
		objectid,
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

SAMPGDK_NATIVE(bool, SetObjectRot(int objectid, float rotX, float rotY, float rotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetObjectRot");
	cell params[] = {
		4 * sizeof(cell),
		objectid,
		amx_ftoc(rotX),
		amx_ftoc(rotY),
		amx_ftoc(rotZ)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetObjectRot(int objectid, float * rotX, float * rotY, float * rotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetObjectRot");
	sampgdk::FakeAmxHeapObject rotX_;
	sampgdk::FakeAmxHeapObject rotY_;
	sampgdk::FakeAmxHeapObject rotZ_;
	cell params[] = {
		4 * sizeof(cell),
		objectid,
		rotX_.address(),
		rotY_.address(),
		rotZ_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*rotX = rotX_.GetAsFloat();
	*rotY = rotY_.GetAsFloat();
	*rotZ = rotZ_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, IsValidObject(int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsValidObject");
	cell params[] = {
		1 * sizeof(cell),
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, DestroyObject(int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DestroyObject");
	cell params[] = {
		1 * sizeof(cell),
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("MoveObject");
	cell params[] = {
		8 * sizeof(cell),
		objectid,
		amx_ftoc(X),
		amx_ftoc(Y),
		amx_ftoc(Z),
		amx_ftoc(Speed),
		amx_ftoc(RotX),
		amx_ftoc(RotY),
		amx_ftoc(RotZ)
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, StopObject(int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("StopObject");
	cell params[] = {
		1 * sizeof(cell),
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsObjectMoving(int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsObjectMoving");
	cell params[] = {
		1 * sizeof(cell),
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, EditObject(int playerid, int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("EditObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, EditPlayerObject(int playerid, int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("EditPlayerObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SelectObject(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SelectObject");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, CancelEdit(int playerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CancelEdit");
	cell params[] = {
		1 * sizeof(cell),
		playerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CreatePlayerObject");
	cell params[] = {
		9 * sizeof(cell),
		playerid,
		modelid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(rX),
		amx_ftoc(rY),
		amx_ftoc(rZ),
		amx_ftoc(DrawDistance)
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AttachPlayerObjectToPlayer");
	cell params[] = {
		9 * sizeof(cell),
		objectplayer,
		objectid,
		attachplayer,
		amx_ftoc(OffsetX),
		amx_ftoc(OffsetY),
		amx_ftoc(OffsetZ),
		amx_ftoc(rX),
		amx_ftoc(rY),
		amx_ftoc(rZ)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AttachPlayerObjectToVehicle");
	cell params[] = {
		9 * sizeof(cell),
		playerid,
		objectid,
		vehicleid,
		amx_ftoc(fOffsetX),
		amx_ftoc(fOffsetY),
		amx_ftoc(fOffsetZ),
		amx_ftoc(fRotX),
		amx_ftoc(fRotY),
		amx_ftoc(RotZ)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerObjectPos");
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		objectid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerObjectPos(int playerid, int objectid, float * x, float * y, float * z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerObjectPos");
	sampgdk::FakeAmxHeapObject x_;
	sampgdk::FakeAmxHeapObject y_;
	sampgdk::FakeAmxHeapObject z_;
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		objectid,
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

SAMPGDK_NATIVE(bool, SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerObjectRot");
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		objectid,
		amx_ftoc(rotX),
		amx_ftoc(rotY),
		amx_ftoc(rotZ)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetPlayerObjectRot(int playerid, int objectid, float * rotX, float * rotY, float * rotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetPlayerObjectRot");
	sampgdk::FakeAmxHeapObject rotX_;
	sampgdk::FakeAmxHeapObject rotY_;
	sampgdk::FakeAmxHeapObject rotZ_;
	cell params[] = {
		5 * sizeof(cell),
		playerid,
		objectid,
		rotX_.address(),
		rotY_.address(),
		rotZ_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*rotX = rotX_.GetAsFloat();
	*rotY = rotY_.GetAsFloat();
	*rotZ = rotZ_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, IsValidPlayerObject(int playerid, int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsValidPlayerObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, DestroyPlayerObject(int playerid, int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DestroyPlayerObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX, float RotY, float RotZ)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("MovePlayerObject");
	cell params[] = {
		9 * sizeof(cell),
		playerid,
		objectid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(Speed),
		amx_ftoc(RotX),
		amx_ftoc(RotY),
		amx_ftoc(RotZ)
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, StopPlayerObject(int playerid, int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("StopPlayerObject");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsPlayerObjectMoving(int playerid, int objectid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsPlayerObjectMoving");
	cell params[] = {
		2 * sizeof(cell),
		playerid,
		objectid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetObjectMaterial(int objectid, int materialindex, int modelid, const char * txdname, const char * texturename, int materialcolor)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetObjectMaterial");
	sampgdk::FakeAmxHeapObject txdname_(txdname);
	sampgdk::FakeAmxHeapObject texturename_(texturename);
	cell params[] = {
		6 * sizeof(cell),
		objectid,
		materialindex,
		modelid,
		txdname_.address(),
		texturename_.address(),
		materialcolor
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectMaterial(int playerid, int objectid, int materialindex, int modelid, const char * txdname, const char * texturename, int materialcolor)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerObjectMaterial");
	sampgdk::FakeAmxHeapObject txdname_(txdname);
	sampgdk::FakeAmxHeapObject texturename_(texturename);
	cell params[] = {
		7 * sizeof(cell),
		playerid,
		objectid,
		materialindex,
		modelid,
		txdname_.address(),
		texturename_.address(),
		materialcolor
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetObjectMaterialText(int objectid, const char * text, int materialindex, int materialsize, const char * fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetObjectMaterialText");
	sampgdk::FakeAmxHeapObject text_(text);
	sampgdk::FakeAmxHeapObject fontface_(fontface);
	cell params[] = {
		10 * sizeof(cell),
		objectid,
		text_.address(),
		materialindex,
		materialsize,
		fontface_.address(),
		fontsize,
		bold,
		fontcolor,
		backcolor,
		textalignment
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectMaterialText(int playerid, int objectid, const char * text, int materialindex, int materialsize, const char * fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetPlayerObjectMaterialText");
	sampgdk::FakeAmxHeapObject text_(text);
	sampgdk::FakeAmxHeapObject fontface_(fontface);
	cell params[] = {
		11 * sizeof(cell),
		playerid,
		objectid,
		text_.address(),
		materialindex,
		materialsize,
		fontface_.address(),
		fontsize,
		bold,
		fontcolor,
		backcolor,
		textalignment
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

