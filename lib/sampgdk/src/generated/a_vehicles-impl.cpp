SAMPGDK_NATIVE(float, GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleDistanceFromPoint");
	cell params[] = {
		4 * sizeof(cell),
		vehicleid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeFloat(native, params);
}

SAMPGDK_NATIVE(int, CreateVehicle(int vehicletype, float x, float y, float z, float rotation, int color1, int color2, int respawn_delay)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("CreateVehicle");
	cell params[] = {
		8 * sizeof(cell),
		vehicletype,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(rotation),
		color1,
		color2,
		respawn_delay
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, DestroyVehicle(int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DestroyVehicle");
	cell params[] = {
		1 * sizeof(cell),
		vehicleid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsVehicleStreamedIn(int vehicleid, int forplayerid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsVehicleStreamedIn");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		forplayerid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetVehiclePos(int vehicleid, float * x, float * y, float * z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehiclePos");
	sampgdk::FakeAmxHeapObject x_;
	sampgdk::FakeAmxHeapObject y_;
	sampgdk::FakeAmxHeapObject z_;
	cell params[] = {
		4 * sizeof(cell),
		vehicleid,
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

SAMPGDK_NATIVE(bool, SetVehiclePos(int vehicleid, float x, float y, float z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehiclePos");
	cell params[] = {
		4 * sizeof(cell),
		vehicleid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetVehicleZAngle(int vehicleid, float * z_angle)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleZAngle");
	sampgdk::FakeAmxHeapObject z_angle_;
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		z_angle_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*z_angle = z_angle_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, GetVehicleRotationQuat(int vehicleid, float * w, float * x, float * y, float * z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleRotationQuat");
	sampgdk::FakeAmxHeapObject w_;
	sampgdk::FakeAmxHeapObject x_;
	sampgdk::FakeAmxHeapObject y_;
	sampgdk::FakeAmxHeapObject z_;
	cell params[] = {
		5 * sizeof(cell),
		vehicleid,
		w_.address(),
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*w = w_.GetAsFloat();
	*x = x_.GetAsFloat();
	*y = y_.GetAsFloat();
	*z = z_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, SetVehicleZAngle(int vehicleid, float z_angle)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleZAngle");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		amx_ftoc(z_angle)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleParamsForPlayer");
	cell params[] = {
		4 * sizeof(cell),
		vehicleid,
		playerid,
		objective,
		doorslocked
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ManualVehicleEngineAndLights()) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ManualVehicleEngineAndLights");
	return sampgdk::FakeAmx::CallNativeBool(native);
}

SAMPGDK_NATIVE(bool, SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleParamsEx");
	cell params[] = {
		8 * sizeof(cell),
		vehicleid,
		engine,
		lights,
		alarm,
		doors,
		bonnet,
		boot,
		objective
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetVehicleParamsEx(int vehicleid, bool * engine, bool * lights, bool * alarm, bool * doors, bool * bonnet, bool * boot, bool * objective)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleParamsEx");
	sampgdk::FakeAmxHeapObject engine_;
	sampgdk::FakeAmxHeapObject lights_;
	sampgdk::FakeAmxHeapObject alarm_;
	sampgdk::FakeAmxHeapObject doors_;
	sampgdk::FakeAmxHeapObject bonnet_;
	sampgdk::FakeAmxHeapObject boot_;
	sampgdk::FakeAmxHeapObject objective_;
	cell params[] = {
		8 * sizeof(cell),
		vehicleid,
		engine_.address(),
		lights_.address(),
		alarm_.address(),
		doors_.address(),
		bonnet_.address(),
		boot_.address(),
		objective_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*engine = engine_.GetAsBool();
	*lights = lights_.GetAsBool();
	*alarm = alarm_.GetAsBool();
	*doors = doors_.GetAsBool();
	*bonnet = bonnet_.GetAsBool();
	*boot = boot_.GetAsBool();
	*objective = objective_.GetAsBool();
	return retval;
}

SAMPGDK_NATIVE(bool, SetVehicleToRespawn(int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleToRespawn");
	cell params[] = {
		1 * sizeof(cell),
		vehicleid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, LinkVehicleToInterior(int vehicleid, int interiorid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("LinkVehicleToInterior");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		interiorid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, AddVehicleComponent(int vehicleid, int componentid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AddVehicleComponent");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		componentid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, RemoveVehicleComponent(int vehicleid, int componentid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("RemoveVehicleComponent");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		componentid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ChangeVehicleColor(int vehicleid, int color1, int color2)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ChangeVehicleColor");
	cell params[] = {
		3 * sizeof(cell),
		vehicleid,
		color1,
		color2
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, ChangeVehiclePaintjob(int vehicleid, int paintjobid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("ChangeVehiclePaintjob");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		paintjobid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetVehicleHealth(int vehicleid, float health)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleHealth");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		amx_ftoc(health)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetVehicleHealth(int vehicleid, float * health)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleHealth");
	sampgdk::FakeAmxHeapObject health_;
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		health_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*health = health_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, AttachTrailerToVehicle(int trailerid, int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("AttachTrailerToVehicle");
	cell params[] = {
		2 * sizeof(cell),
		trailerid,
		vehicleid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, DetachTrailerFromVehicle(int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("DetachTrailerFromVehicle");
	cell params[] = {
		1 * sizeof(cell),
		vehicleid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, IsTrailerAttachedToVehicle(int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("IsTrailerAttachedToVehicle");
	cell params[] = {
		1 * sizeof(cell),
		vehicleid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetVehicleTrailer(int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleTrailer");
	cell params[] = {
		1 * sizeof(cell),
		vehicleid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, SetVehicleNumberPlate(int vehicleid, const char * numberplate)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleNumberPlate");
	sampgdk::FakeAmxHeapObject numberplate_(numberplate);
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		numberplate_.address()
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetVehicleModel(int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleModel");
	cell params[] = {
		1 * sizeof(cell),
		vehicleid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetVehicleComponentInSlot(int vehicleid, int slot)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleComponentInSlot");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		slot
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(int, GetVehicleComponentType(int component)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleComponentType");
	cell params[] = {
		1 * sizeof(cell),
		component
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, RepairVehicle(int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("RepairVehicle");
	cell params[] = {
		1 * sizeof(cell),
		vehicleid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetVehicleVelocity(int vehicleid, float * X, float * Y, float * Z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleVelocity");
	sampgdk::FakeAmxHeapObject X_;
	sampgdk::FakeAmxHeapObject Y_;
	sampgdk::FakeAmxHeapObject Z_;
	cell params[] = {
		4 * sizeof(cell),
		vehicleid,
		X_.address(),
		Y_.address(),
		Z_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*X = X_.GetAsFloat();
	*Y = Y_.GetAsFloat();
	*Z = Z_.GetAsFloat();
	return retval;
}

SAMPGDK_NATIVE(bool, SetVehicleVelocity(int vehicleid, float X, float Y, float Z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleVelocity");
	cell params[] = {
		4 * sizeof(cell),
		vehicleid,
		amx_ftoc(X),
		amx_ftoc(Y),
		amx_ftoc(Z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleAngularVelocity");
	cell params[] = {
		4 * sizeof(cell),
		vehicleid,
		amx_ftoc(X),
		amx_ftoc(Y),
		amx_ftoc(Z)
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, GetVehicleDamageStatus(int vehicleid, int * panels, int * doors, int * lights, int * tires)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleDamageStatus");
	sampgdk::FakeAmxHeapObject panels_;
	sampgdk::FakeAmxHeapObject doors_;
	sampgdk::FakeAmxHeapObject lights_;
	sampgdk::FakeAmxHeapObject tires_;
	cell params[] = {
		5 * sizeof(cell),
		vehicleid,
		panels_.address(),
		doors_.address(),
		lights_.address(),
		tires_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*panels = panels_.Get();
	*doors = doors_.Get();
	*lights = lights_.Get();
	*tires = tires_.Get();
	return retval;
}

SAMPGDK_NATIVE(bool, UpdateVehicleDamageStatus(int vehicleid, int panels, int doors, int lights, int tires)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("UpdateVehicleDamageStatus");
	cell params[] = {
		5 * sizeof(cell),
		vehicleid,
		panels,
		doors,
		lights,
		tires
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(bool, SetVehicleVirtualWorld(int vehicleid, int worldid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("SetVehicleVirtualWorld");
	cell params[] = {
		2 * sizeof(cell),
		vehicleid,
		worldid
	};
	return sampgdk::FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_NATIVE(int, GetVehicleVirtualWorld(int vehicleid)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleVirtualWorld");
	cell params[] = {
		1 * sizeof(cell),
		vehicleid
	};
	return sampgdk::FakeAmx::CallNative(native, params);
}

SAMPGDK_NATIVE(bool, GetVehicleModelInfo(int model, int infotype, float * X, float * Y, float * Z)) {
	static AMX_NATIVE native = sampgdk::Natives::GetNativeWarn("GetVehicleModelInfo");
	sampgdk::FakeAmxHeapObject X_;
	sampgdk::FakeAmxHeapObject Y_;
	sampgdk::FakeAmxHeapObject Z_;
	cell params[] = {
		5 * sizeof(cell),
		model,
		infotype,
		X_.address(),
		Y_.address(),
		Z_.address()
	};
	bool retval = sampgdk::FakeAmx::CallNativeBool(native, params);
	*X = X_.GetAsFloat();
	*Y = Y_.GetAsFloat();
	*Z = Z_.GetAsFloat();
	return retval;
}

