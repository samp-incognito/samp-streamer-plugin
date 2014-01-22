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

#ifndef SAMPGDK_FAKEAMX_H
#define SAMPGDK_FAKEAMX_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/amx.h>

#include <cstddef>
#include <vector>

namespace sampgdk {

class FakeAmx {
public:
	static const size_t INITIAL_HEAP_SIZE = 1024;

	static AMX *amx();

	static cell Push(size_t cells);
	static cell Push(const char *s);

	static void Get(cell address, cell &value);
	static void Get(cell address, char *value, size_t size);

	static void Pop(cell address);

	static inline cell CallNative(AMX_NATIVE native, cell *params) {
		return native(&amx_, params);
	}
	static inline bool CallNativeBool(AMX_NATIVE native, cell *params) {
		return CallNative(native, params) != 0;
	}
	static inline float CallNativeFloat(AMX_NATIVE native, cell *params) {
		cell retval = CallNative(native, params);
		return amx_ctof(retval);
	}

	// Parameter-less versions
	static inline cell CallNative(AMX_NATIVE native) {
		return native(&amx_, 0);
	}
	static inline bool CallNativeBool(AMX_NATIVE native) {
		return CallNative(native) != 0;
	}
	static inline float CallNativeFloat(AMX_NATIVE native) {
		cell retval = CallNative(native);
		return amx_ctof(retval);
	}

private:
	static AMX amx_;
	static AMX_HEADER hdr_;

	static std::vector<cell> heap_;
};

class FakeAmxHeapObject {
public:
	FakeAmxHeapObject();
	FakeAmxHeapObject(size_t cells);
	FakeAmxHeapObject(const char *s);
	~FakeAmxHeapObject();

	cell address() const;
	size_t size() const;

	cell  Get() const;
	bool GetAsBool() const;
	float GetAsFloat() const;
	void  GetAsString(char *s, size_t size) const;

private:
	size_t size_;
	cell address_;
};

} // namespace sampgdk

#endif // !SAMPGDK_FAKEAMX
