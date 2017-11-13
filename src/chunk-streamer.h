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

#ifndef CHUNK_STREAMER_H
#define CHUNK_STREAMER_H

#include "cell.h"
#include "common.h"
#include "player.h"
#include "streamer.h"

#include <vector>

class ChunkStreamer : public Streamer
{
public:
	ChunkStreamer();

	inline bool getChunkStreamingEnabled()
	{
		return chunkStreamingEnabled;
	}

	inline void setChunkStreamingEnabled(bool enabled)
	{
		chunkStreamingEnabled = enabled;
	}

	friend void Streamer::performPlayerUpdate(Player &player, bool automatic);
	void performPlayerChunkUpdate(Player &player, bool automatic);

	std::size_t getChunkSize(int type);
	bool setChunkSize(int type, std::size_t value);
private:
	void discoverMapIcons(Player &player, const std::vector<SharedCell> &cells);
	void streamMapIcons(Player &player, bool automatic);

	void discoverObjects(Player &player, const std::vector<SharedCell> &cells);
	void streamObjects(Player &player, bool automatic);

	void discoverTextLabels(Player &player, const std::vector<SharedCell> &cells);
	void streamTextLabels(Player &player, bool automatic);

	std::size_t chunkSize[STREAMER_MAX_TYPES];
	bool chunkStreamingEnabled;
};

#endif
