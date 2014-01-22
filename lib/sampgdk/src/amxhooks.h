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

#ifndef SAMPGDK_AMXHOOKS_H
#define SAMPGDK_AMXHOOKS_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/amx.h>

#include <map>
#include <string>
#include <vector>

#include "hook.h"

namespace sampgdk {

class AmxHooks  {
public:
	static void Initialize(void **ppPluginData);
	static void Finalize();

	static int amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);

	static const std::vector<AMX_NATIVE_INFO> &GetNatives() {
		return native_info_;
	}

private:
	static Hook amx_RegisterHook_;

	static std::vector<AMX_NATIVE_INFO> native_info_;
};

} // namespace sampgdk

#endif // !SAMPGDK_AMXHOOKS_H
