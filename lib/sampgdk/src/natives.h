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

#ifndef SAMPGDK_NATIVES_H
#define SAMPGDK_NATIVES_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/amx.h>

#include <map>
#include <string>

namespace sampgdk {

class Natives {
public:
	// This method MUST be called before executing any native.
	static void Initialize();

	// Gets a native function previously added with SetNative().
	// Returns NULL if the requested function does not exist.
	static AMX_NATIVE GetNative(const char *name);

	// Same as GetNative() but prints a warning message to log when fails.
	static AMX_NATIVE GetNativeWarn(const char *name);

	// Add a new native function or override an exiting one.
	static void SetNative(const char *name, AMX_NATIVE native);

private:
	Natives();

private:
	typedef std::map<std::string, AMX_NATIVE> StringToNativeMap;
	static StringToNativeMap string_to_native_;
};

} // namespace sampgdk

#endif // !SAMPGDK_NATIVES_H
