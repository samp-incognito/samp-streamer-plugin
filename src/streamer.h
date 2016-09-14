/*
 * Copyright (C) 2016 Incognito
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

#ifndef STREAMER_H
#define STREAMER_H

#define INVALID_ALTERNATE_ID (-1)
#define INVALID_GENERIC_ID (0xFFFF)
#define INVALID_STREAMER_ID (0)

#include "cell.h"
#include "common.h"
#include "item.h"
#include "player.h"
#include "utility.h"

#include <boost/tuple/tuple.hpp>
#include <boost/unordered_set.hpp>

#include <bitset>
#include <map>

class Streamer
{
public:
	Streamer();

	inline float getLastUpdateTime()
	{
		return lastUpdateTime;
	}

	inline std::size_t getTickRate()
	{
		return tickRate;
	}

	inline bool setTickRate(std::size_t value)
	{
		if (value > 0)
		{
			tickRate = value;
			return true;
		}
		return false;
	}

	std::size_t getChunkSize(int type);
	bool setChunkSize(int type, std::size_t value);

	void startAutomaticUpdate();
	void startManualUpdate(Player &player, int type);

	void processActiveItems();

	boost::unordered_set<Item::SharedArea> attachedAreas;
	boost::unordered_set<Item::SharedObject> attachedObjects;
	boost::unordered_set<Item::SharedTextLabel> attachedTextLabels;
	boost::unordered_set<Item::SharedObject> movingObjects;
private:
	void calculateAverageElapsedTime();

	void performPlayerChunkUpdate(Player &player);
	void performPlayerUpdate(Player &player, bool automatic);
	void executeCallbacks();

	void processAreas(Player &player, const std::vector<SharedCell> &cells);
	void processCheckpoints(Player &player, const std::vector<SharedCell> &cells);
	void processRaceCheckpoints(Player &player, const std::vector<SharedCell> &cells);

	void discoverMapIcons(Player &player, const std::vector<SharedCell> &cells);
	void streamMapIcons(Player &player);

	void discoverObjects(Player &player, const std::vector<SharedCell> &cells);
	void streamObjects(Player &player);

	void discoverPickups(Player &player, const std::vector<SharedCell> &cells);
	void streamPickups();

	void discoverTextLabels(Player &player, const std::vector<SharedCell> &cells);
	void streamTextLabels(Player &player);

	void processMovingObjects();
	void processAttachedAreas();
	void processAttachedObjects();
	void processAttachedTextLabels();

	std::size_t chunkSize[STREAMER_MAX_TYPES];

	std::size_t tickCount;
	std::size_t tickRate;

	float averageElapsedTime;
	float lastUpdateTime;

	boost::tuple<float, float> velocityBoundaries;

	std::vector<boost::tuple<int, int> > areaEnterCallbacks;
	std::vector<boost::tuple<int, int> > areaLeaveCallbacks;
	std::vector<int> objectMoveCallbacks;

	boost::unordered_map<int, Item::SharedPickup> discoveredPickups;

	template<std::size_t N, typename T>
	inline bool doesPlayerSatisfyConditions(const std::bitset<N> &a, const T &b, const boost::unordered_set<T> &c, const T &d, const boost::unordered_set<T> &e, const T &f)
	{
		return (a[b] && (c.empty() || c.find(d) != c.end()) && (e.empty() || e.find(f) != e.end()));
	}

	template<std::size_t N, typename T>
	inline bool doesPlayerSatisfyConditions(const std::bitset<N> &a, const T &b, const boost::unordered_set<T> &c, const T &d, const boost::unordered_set<T> &e, const T &f, const boost::unordered_set<T> &g, const boost::unordered_set<T> &h, bool i)
	{
		return (a[b] && (c.empty() || c.find(d) != c.end()) && (e.empty() || e.find(f) != e.end()) && (g.empty() || i ? !Utility::isContainerWithinContainer(g, h) : Utility::isContainerWithinContainer(g, h)));
	}
};

#endif
