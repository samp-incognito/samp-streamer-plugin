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
#include <sampgdk/export.h>

#include <set>
#include <vector>

#include "timers.h"

namespace sampgdk {

int GetTimerId(Timer *timer);

Timer::Timer(int interval, bool repeat, TimerCallback callback, void *param)
	: interval_(interval)
	, repeating_(repeat)
	, callback_(callback)
	, param_(param)
	, plugin_(sampgdk_get_plugin_handle((void*)callback))
	, start_time_(Clock())
{
}

void Timer::Fire(int elapsed_time) {
	callback_(GetTimerId(this), param_);
	if (repeating_) {
		start_time_ = Clock() - (elapsed_time - interval_);
	}
}

} // namespace sampgdk 

namespace {

std::vector<sampgdk::Timer*> timers;

} // unnamed namespace

namespace sampgdk {

// static
int Timer::GetTimerId(Timer *timer) {
	int timerid = 0;
	while (timerid < static_cast<int>(timers.size())) {
		if (timers[timerid] == timer) {
			break;
		}
		++timerid;
	}
	return timerid;
}

// static
int Timer::SetTimer(int interval, bool repeat, TimerCallback handler, void *param) {
	Timer *timer = new Timer(interval, repeat, handler, param);
	size_t timerid = 0;
	while (timerid < timers.size()) {
		if (timers[timerid] == 0) {
			timers[timerid] = timer;
			break;
		}
		++timerid;
	}
	if (timerid == timers.size()) {
		timers.push_back(timer);
	}
	return timerid;
}

// static
bool Timer::KillTimer(int timerid) {
	if (timerid < 0 || timerid >= static_cast<int>(timers.size())) {
		return false;
	}

	Timer *timer = timers[timerid];
	delete timer;

	if (timerid == static_cast<int>(timers.size())) {
		timers.pop_back();
	} else {
		timers[timerid] = 0;
	}

	return true;
}

// static
void Timer::ProcessTimers(void *plugin) {
	int time = Timer::Clock();
	for (size_t i = 0; i < timers.size(); ++i) {
		Timer *timer = timers[i];
		if (plugin != 0 && timer->GetPlugin() != plugin) {
			continue;
		}
		int elapsed_time = time - timer->GetStartTime();
		if (elapsed_time >= timer->GetInterval()) {
			timer->Fire(elapsed_time);
			if (!timer->IsRepeating()) {
				KillTimer(i);
			}
		}
	}
}

} // namespace sampgdk
