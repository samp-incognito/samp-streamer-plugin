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

#ifndef CORE_H
#define CORE_H

#include "chunk-streamer.h"
#include "data.h"
#include "grid.h"
#include "streamer.h"

class Core
{
public:
	Core();

	inline Data *getData()
	{
		return data.get();
	}

	inline Grid *getGrid()
	{
		return grid.get();
	}

	inline ChunkStreamer *getChunkStreamer()
	{
		return chunkStreamer.get();
	}

	inline Streamer *getStreamer()
	{
		return streamer.get();
	}
private:
	boost::scoped_ptr<Data> data;
	boost::scoped_ptr<Grid> grid;

	boost::scoped_ptr<ChunkStreamer> chunkStreamer;
	boost::scoped_ptr<Streamer> streamer;
};

extern boost::scoped_ptr<Core> core;

#endif
