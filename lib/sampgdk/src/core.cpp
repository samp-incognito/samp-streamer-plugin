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
#include <sampgdk/export.h>
#include <sampgdk/plugin.h>

#include "amxhooks.h"
#include "natives.h"
#include "timers.h"

static void **plugin_data;

sampgdk_logprintf_t sampgdk_logprintf;

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_initialize(void **ppPluginData) {
	static bool initialized = false;
	if (!initialized) {
		plugin_data = ppPluginData;
		sampgdk_logprintf = (sampgdk_logprintf_t)plugin_data[PLUGIN_DATA_LOGPRINTF];
		sampgdk::AmxHooks::Initialize(ppPluginData);
		initialized = true;
	}
}

SAMPGDK_EXPORT void **SAMPGDK_CALL sampgdk_get_plugin_data() {
	return plugin_data;
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_finalize() {
	// nothing
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_register_plugin(void *plugin) {
	// nothing
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_unregister_plugin(void *plugin) {
	// nothing
}

SAMPGDK_EXPORT const AMX_NATIVE_INFO *SAMPGDK_CALL sampgdk_get_natives() {
	return &(sampgdk::AmxHooks::GetNatives()[0]);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers() {
	sampgdk::Timer::ProcessTimers();
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_plugin_timers(void *plugin) {
	sampgdk::Timer::ProcessTimers(plugin);
}
