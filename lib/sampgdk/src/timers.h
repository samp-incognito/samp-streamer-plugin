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

#ifndef SAMPGDK_TIMERS_H
#define SAMPGDK_TIMERS_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/a_samp.h>

#include <vector>

namespace sampgdk {

class Timer {
private:
	Timer(int interval, bool repeat, TimerCallback hander, void *param);

public:
	int GetInterval() const {
		return interval_;
	}
	bool IsRepeating() const {
		return repeating_;
	}
	int GetStartTime() const {
		return start_time_;
	}
	void *GetPlugin() const {
		return plugin_;
	}

	void Fire(int elapsed_time);

public:
	static int SetTimer(int interval, bool repeat, TimerCallback handler, void *param);
	static bool KillTimer(int timerid);
	static void ProcessTimers(void *plugin = 0);

private:
	static int Clock();
	static int GetTimerId(Timer *timer);

private:
	int interval_;
	bool repeating_;
	TimerCallback callback_;
	void *param_;
	void *plugin_;
	int start_time_;
};

} // namespace sampgdk

#endif // SAMPGDK_TIMERS_H
