/*
 * Copyright (C) 2014 Incognito
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

Player::Player(int playerID) : playerID(playerID)
{
	activeCheckpoint = 0;
	activeRaceCheckpoint = 0;
	activeVehicle = INVALID_VEHICLE_ID;
	enabledItems.set();
	interiorID = 0;
	position.setZero();
	updateWhenIdle = false;
	visibleCell = SharedCell(new Cell());
	visibleCheckpoint = 0;
	visibleRaceCheckpoint = 0;
	visibleObjects = core->getStreamer()->getVisibleItems(STREAMER_TYPE_OBJECT);
	visibleTextLabels = core->getStreamer()->getVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL);
	worldID = 0;
}
