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

#include <cstddef>
#include <cstring>
#include <limits>

#include "fakeamx.h"

namespace sampgdk {

std::vector<cell> FakeAmx::heap_(FakeAmx::INITIAL_HEAP_SIZE);

AMX_HEADER FakeAmx::hdr_ = {
	0, // size
	AMX_MAGIC, // magic
	MIN_FILE_VERSION, // file_version
	MIN_AMX_VERSION, // amx_version
	0, // flags
	0, // defsize
	0, // cod
	reinterpret_cast<int32_t>(&heap_[0]) - reinterpret_cast<int32_t>(&hdr_), // dat
	0, // hea 
	0, // stp
	0, // cip
	0, // publics
	0, // natives
	0, // libraries
	0, // pubvars
	0, // tags
	0, // nametable
};

AMX FakeAmx::amx_ = {
	reinterpret_cast<unsigned char*>(&FakeAmx::hdr_), // base
	reinterpret_cast<unsigned char*>(&FakeAmx::heap_[0]), // data
	amx_Callback, // callback
	0, // debug hook
	0, // cip
	0, // frm
	0, // hea
	0, // hlw
	0, // stk
	std::numeric_limits<int32_t>::max(), // stp
	0, // flags
	{0}, // usertags
	{0}, // userdata
	AMX_ERR_NONE, // error
	0, // paramcount 
	0, // pri
	0, // alt
	0, // reset_stk
	0, // reset_hea
	0, // sysreq_d
};

// static
cell FakeAmx::Push(size_t cells) {
	cell address = amx_.hea;
	amx_.hea += cells * sizeof(cell);
	if (static_cast<cell>(amx_.hea/sizeof(cell)) >= static_cast<cell>(heap_.size())) {
		heap_.resize(amx_.hea/sizeof(cell));
	}
	return address;
}

// static
cell FakeAmx::Push(const char *s) {
	std::size_t size = std::strlen(s) + 1;
	cell address = Push(size);
	amx_SetString(&heap_[0] + address/sizeof(cell), s, 0, 0, size);
	return address;
}

// static
void FakeAmx::Get(cell address, cell &value) {
	value = heap_[address/sizeof(cell)];
}

// static
void FakeAmx::Get(cell address, char *value, size_t size) {
	const cell *ptr = &heap_[0] + address/sizeof(cell);
	amx_GetString(value, ptr, 0, size);
}

// static
void FakeAmx::Pop(cell address) {
	if (amx_.hea > address) {
		amx_.hea = address;
	}
}

FakeAmxHeapObject::FakeAmxHeapObject()
	: size_(1), address_(FakeAmx::Push(1))
{}

FakeAmxHeapObject::FakeAmxHeapObject(size_t cells)
	: size_(cells), address_(FakeAmx::Push(cells))
{}

FakeAmxHeapObject::FakeAmxHeapObject(const char *s)
	: size_(std::strlen(s) + 1), address_(FakeAmx::Push(s))
{}

FakeAmxHeapObject::~FakeAmxHeapObject() { FakeAmx::Pop(address_); }

cell FakeAmxHeapObject::address() const { return address_; }

size_t FakeAmxHeapObject::size() const { return size_; }

cell FakeAmxHeapObject::Get() const {
	cell value;
	FakeAmx::Get(address_, value);
	return value;
}

bool FakeAmxHeapObject::GetAsBool() const {
	return Get() != 0;
}

float FakeAmxHeapObject::GetAsFloat() const {
	cell value = this->Get();
	return amx_ctof(value);
}

void FakeAmxHeapObject::GetAsString(char *s, size_t size) const {
	FakeAmx::Get(address_, s, size);
}

} // namespace sampgdk
