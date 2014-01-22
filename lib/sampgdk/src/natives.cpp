// Copyright (C) 2011-2012, Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sampgdk/config.h>
#include <sampgdk/amx.h>
#include <sampgdk/core.h>

#include <cstdlib>

#include "natives.h"

extern sampgdk_logprintf_t sampgdk_logprintf;

namespace sampgdk {

Natives::StringToNativeMap Natives::string_to_native_;

AMX_NATIVE Natives::GetNative(const char *name) {
	StringToNativeMap::const_iterator iter = string_to_native_.find(name);
	if (iter == string_to_native_.end()) {
		return 0;
	}
	return iter->second;
}

AMX_NATIVE Natives::GetNativeWarn(const char *name) {
	AMX_NATIVE native = GetNative(name);
	if (native == 0) {
		sampgdk_logprintf("sampgdk: warning: native function \"%s\" does not exist", name);
	}
	return native;
}

void Natives::SetNative(const char *name, AMX_NATIVE native) {
	string_to_native_[std::string(name)] = native;
}

} // namespace sampgdk
