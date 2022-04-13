/*
 * Copyright (C) 2017 Incognito
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

#ifndef PLAYER_H
#define PLAYER_H

#include "cell.h"
#include "identifier.h"

struct Player
{
	Player(int id);

	int activeCheckpoint;
	int activeRaceCheckpoint;
	std::size_t chunkTickCount[STREAMER_MAX_TYPES];
	std::size_t chunkTickRate[STREAMER_MAX_TYPES];
	std::size_t currentVisibleObjects;
	std::size_t currentVisibleTextLabels;
	int delayedCheckpoint;
	int delayedRaceCheckpoint;
	bool delayedUpdate;
	bool delayedUpdateFreeze;
	std::chrono::steady_clock::time_point delayedUpdateTime;
	int delayedUpdateType;
	int interiorId;
	std::size_t maxVisibleMapIcons;
	std::size_t maxVisibleObjects;
	std::size_t maxVisibleTextLabels;
	int playerId;
	Eigen::Vector3f position;
	float radiusMultipliers[STREAMER_MAX_TYPES];
	int references;
	bool requestingClass;
	std::size_t tickCount;
	std::size_t tickRate;
	bool updateUsingCameraPosition;
	bool updateWhenIdle;
	SharedCell visibleCell;
	int visibleCheckpoint;
	int visibleRaceCheckpoint;
	int worldId;

	std::bitset<STREAMER_MAX_TYPES> enabledItems;
	std::bitset<STREAMER_MAX_TYPES> processingChunks;

	Item::Bimap<Item::SharedMapIcon>::Type discoveredMapIcons;
	Item::Bimap<Item::SharedObject>::Type discoveredObjects;
	Item::Bimap<Item::SharedTextLabel>::Type discoveredTextLabels;

	Item::Bimap<Item::SharedMapIcon>::Type existingMapIcons;
	Item::Bimap<Item::SharedObject>::Type existingObjects;
	Item::Bimap<Item::SharedTextLabel>::Type existingTextLabels;

	std::unordered_set<int> internalAreas;
	std::unordered_map<int, int> internalMapIcons;
	std::unordered_map<int, int> internalObjects;
	std::unordered_map<int, int> internalTextLabels;

	std::unordered_set<int> removedMapIcons;
	std::unordered_set<int> removedObjects;
	std::unordered_set<int> removedTextLabels;

	Identifier mapIconIdentifier;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif
