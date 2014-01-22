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

#ifndef SAMPGDK_HOOK_H
#define SAMPGDK_HOOK_H

#include <sampgdk/config.h>

namespace sampgdk {

class Hook {
public:
	static const int kJmpInstrSize = 5;

	Hook();
	Hook(void *src, void *dst);
	~Hook();

	bool Install();
	bool Install(void *src, void *dst);
	bool IsInstalled() const;
	bool Remove();

	static void *GetTargetAddress(void *jmp);

	// Temporary Remove()
	class ScopedRemove {
	public:
		ScopedRemove(Hook *jmp) 
			: jmp_(jmp)
			, removed_(jmp->Remove())
		{
			// nothing
		}

		~ScopedRemove() {
			if (removed_) {
				jmp_->Install();
			}
		}

	private:		
		Hook *jmp_;
		bool removed_;
	};

	// Temporary Install() 
	class ScopedInstall {
	public:
		ScopedInstall(Hook *jmp) 
			: jmp_(jmp)
			, installed_(jmp->Install())
		{
			// nothing
		}

		~ScopedInstall() {
			if (installed_) {
				jmp_->Remove();
			}
		}

	private:
		Hook *jmp_;
		bool installed_;
	};

private:
	static void Unprotect(void *address, int size);

private:
	void *src_;
	void *dst_;
	unsigned char code_[5];
	bool installed_;
};

} // namespace sampgdk

#endif
