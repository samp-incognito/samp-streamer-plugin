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

#include "data.h"

#include <limits>

Data::Data()
{
	maxAreas = std::numeric_limits<int>::max();
	maxCheckpoints = std::numeric_limits<int>::max();
	maxMapIcons = std::numeric_limits<int>::max();
	maxObjects = std::numeric_limits<int>::max();
	maxPickups = std::numeric_limits<int>::max();
	maxRaceCheckpoints = std::numeric_limits<int>::max();
	maxTextLabels = std::numeric_limits<int>::max();
	maxVisibleMapIcons = 100;
	maxVisibleObjects = 500;
	maxVisiblePickups = 4096;
	maxVisibleTextLabels = 1024;
}

std::size_t Data::getMaxItems(int type)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			return maxObjects;
		}
		case STREAMER_TYPE_PICKUP:
		{
			return maxPickups;
		}
		case STREAMER_TYPE_CP:
		{
			return maxCheckpoints;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			return maxRaceCheckpoints;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return maxMapIcons;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return maxTextLabels;
		}
		case STREAMER_TYPE_AREA:
		{
			return maxAreas;
		}
	}
	return 0;
}

bool Data::setMaxItems(int type, std::size_t value)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			maxObjects = value;
			return true;
		}
		case STREAMER_TYPE_PICKUP:
		{
			maxPickups = value;
			return true;
		}
		case STREAMER_TYPE_CP:
		{
			maxCheckpoints = value;
			return true;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			maxRaceCheckpoints = value;
			return true;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			maxMapIcons = value;
			return true;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			maxTextLabels = value;
			return true;
		}
		case STREAMER_TYPE_AREA:
		{
			maxAreas = value;
			return true;
		}
	}
	return false;
}

std::size_t Data::getMaxVisibleItems(int type)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			return maxVisibleObjects;
		}
		case STREAMER_TYPE_PICKUP:
		{
			return maxVisiblePickups;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return maxVisibleMapIcons;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return maxVisibleTextLabels;
		}
	}
	return 0;
}

bool Data::setMaxVisibleItems(int type, std::size_t value)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			maxVisibleObjects = value;
			return true;
		}
		case STREAMER_TYPE_PICKUP:
		{
			maxVisiblePickups = value;
			return true;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			maxVisibleMapIcons = value;
			return true;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			maxVisibleTextLabels = value;
			return true;
		}
	}
	return false;
}
