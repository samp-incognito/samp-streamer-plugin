// Copyright (C) 2011-2012, Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sampgdk/config.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include "amxhooks.h"
#include "hook.h"
#include "natives.h"

#include <cstring>

extern void *pAMXFunctions;

namespace sampgdk {

Hook AmxHooks::amx_RegisterHook_;

std::vector<AMX_NATIVE_INFO> AmxHooks::native_info_;

void AmxHooks::Initialize(void **ppPluginData) {
	pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];

	void **amxExports = static_cast<void**>(pAMXFunctions);
	amx_RegisterHook_.Install(
		amxExports[PLUGIN_AMX_EXPORT_Register],
		(void*)amx_Register);
}

void AmxHooks::Finalize() {
	amx_RegisterHook_.Remove();
}

int AMXAPI AmxHooks::amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
	Hook::ScopedRemove r(&amx_RegisterHook_);

	for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
		Natives::SetNative(nativelist[i].name, nativelist[i].func);
		native_info_.push_back(nativelist[i]);
	}
	return ::amx_Register(amx, nativelist, number);
}

} // namespace sampgdk
