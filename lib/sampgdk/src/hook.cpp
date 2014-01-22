// Copyright (C) 2012, Zeex
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

#include <cstring>

#include "hook.h"

namespace sampgdk {

Hook::Hook() 
	: src_(0)
	, dst_(0)
	, installed_(false)
{}

Hook::Hook(void *src, void *dst) 
	: src_(0)
	, dst_(0)
	, installed_(false)
{
	Install(src, dst);
}

Hook::~Hook() {
	Remove();
}

bool Hook::Install() {
	if (installed_) {
		return false;
	}

	// Set write permission
	Unprotect(src_, kJmpInstrSize);

	// Store the code we are going to overwrite (probably to copy it back later)
	memcpy(code_, src_, kJmpInstrSize);

	// E9 - jump near, relative
	unsigned char JMP = 0xE9;
	memcpy(src_, &JMP, 1);

	// Jump address is relative to the next instruction's address
	size_t offset = (int)dst_ - ((int)src_ + kJmpInstrSize);
	memcpy((void*)((int)src_ + 1), &offset, kJmpInstrSize - 1);

	installed_ = true;
	return true;
}

bool Hook::Install(void *src, void *dst) {
	if (installed_) {
		return false;
	}

    src_ = src; 
	dst_ = dst;
	return Install();
}

bool Hook::Remove() {
	if (!installed_) {
		return false;
	}

	std::memcpy(src_, code_, kJmpInstrSize);
	installed_ = false;
	return true;
}

bool Hook::IsInstalled() const {
	return installed_;
}

// static 
void *Hook::GetTargetAddress(void *jmp) {
	if (*reinterpret_cast<unsigned char*>(jmp) == 0xE9) {
		int next_instr = reinterpret_cast<int>(reinterpret_cast<char*>(jmp) + kJmpInstrSize);
		int rel_addr = *reinterpret_cast<int*>(reinterpret_cast<char*>(jmp) + 1);
		int abs_addr = rel_addr + next_instr;
		return reinterpret_cast<void*>(abs_addr);
	}
	return 0;
}

} // namespace sampgdk
