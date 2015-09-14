/*
 * Copyright (C) 2015 Incognito
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

#include "player.h"

#include "core.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <Eigen/Core>

#include <bitset>

Player::Player(int id)
{
	activeCheckpoint = 0;
	activeRaceCheckpoint = 0;
	currentVisibleObjects = core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_OBJECT);
	currentVisibleTextLabels = core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL);
	delayedCheckpoint = 0;
	delayedRaceCheckpoint = 0;
	enabledItems.set();
	interiorID = 0;
	maxVisibleMapIcons = core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_MAP_ICON);
	maxVisibleObjects = core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_OBJECT);
	maxVisibleTextLabels = core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL);
	playerID = id;
	position.setZero();
	radiusMultipliers[STREAMER_TYPE_OBJECT] = core->getData()->getGlobalRadiusMultiplier(STREAMER_TYPE_OBJECT);
	radiusMultipliers[STREAMER_TYPE_PICKUP] = core->getData()->getGlobalRadiusMultiplier(STREAMER_TYPE_PICKUP);
	radiusMultipliers[STREAMER_TYPE_CP] = core->getData()->getGlobalRadiusMultiplier(STREAMER_TYPE_CP);
	radiusMultipliers[STREAMER_TYPE_RACE_CP] = core->getData()->getGlobalRadiusMultiplier(STREAMER_TYPE_RACE_CP);
	radiusMultipliers[STREAMER_TYPE_MAP_ICON] = core->getData()->getGlobalRadiusMultiplier(STREAMER_TYPE_MAP_ICON);
	radiusMultipliers[STREAMER_TYPE_3D_TEXT_LABEL] = core->getData()->getGlobalRadiusMultiplier(STREAMER_TYPE_3D_TEXT_LABEL);
	radiusMultipliers[STREAMER_TYPE_AREA] = core->getData()->getGlobalRadiusMultiplier(STREAMER_TYPE_AREA);
	radiusMultipliers[STREAMER_TYPE_VEHICLE] = core->getData()->getGlobalRadiusMultiplier(STREAMER_TYPE_VEHICLE);
	updateUsingCameraPosition = false;
	updateWhenIdle = false;
	visibleCell = SharedCell(new Cell());
	visibleCheckpoint = 0;
	visibleRaceCheckpoint = 0;
	worldID = 0;
}
