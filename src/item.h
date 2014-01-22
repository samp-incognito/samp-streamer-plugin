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

#ifndef ITEM_H
#define ITEM_H

#include "cell.h"
#include "common.h"
#include "identifier.h"

#include <boost/chrono.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <sampgdk/a_samp.h>
#include <sampgdk/plugin.h>

#include <bitset>
#include <string>

namespace Item
{
	struct Area
	{
		Area();

		AMX *amx;
		int areaID;
		SharedCell cell;
		int extraID;
		int references;
		float size;
		int type;

		boost::variant<Polygon2D, Box2D, Box3D, Eigen::Vector2f, Eigen::Vector3f> position;

		struct Attach
		{
			Attach();

			boost::tuple<int, int, int> object;
			int player;
			Eigen::Vector3f position;
			int references;
			int vehicle;
		};

		boost::intrusive_ptr<Attach> attach;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct Checkpoint
	{
		Checkpoint();

		AMX *amx;
		SharedCell cell;
		int checkpointID;
		int extraID;
		Eigen::Vector3f position;
		int references;
		float size;
		float streamDistance;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct MapIcon
	{
		MapIcon();

		AMX *amx;
		SharedCell cell;
		int color;
		int extraID;
		int mapIconID;
		Eigen::Vector3f position;
		int references;
		float streamDistance;
		int style;
		int type;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct Object
	{
		Object();

		AMX *amx;
		SharedCell cell;
		float drawDistance;
		int extraID;
		int modelID;
		int objectID;
		Eigen::Vector3f position;
		int references;
		Eigen::Vector3f rotation;
		float streamDistance;

		struct Attach
		{
			Attach();

			Eigen::Vector3f position;
			Eigen::Vector3f offset;
			int references;
			Eigen::Vector3f rotation;
			int vehicle;
		};

		boost::intrusive_ptr<Attach> attach;

		struct Material
		{
			struct Main
			{
				Main();

				int materialColor;
				int modelID;
				int references;
				std::string textureName;
				std::string txdFileName;
			};

			boost::intrusive_ptr<Main> main;

			struct Text
			{
				Text();

				int backColor;
				bool bold;
				int fontColor;
				std::string fontFace;
				int fontSize;
				int references;
				int materialSize;
				std::string materialText;
				int textAlignment;
			};

			boost::intrusive_ptr<Text> text;
		};

		boost::unordered_map<int, Material> materials;

		struct Move
		{
			Move();

			int duration;
			boost::tuple<Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f> position;
			int references;
			boost::tuple<Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f> rotation;
			float speed;
			boost::chrono::steady_clock::time_point time;
		};

		boost::intrusive_ptr<Move> move;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct Pickup
	{
		Pickup();

		AMX *amx;
		SharedCell cell;
		int extraID;
		int modelID;
		int pickupID;
		Eigen::Vector3f position;
		int references;
		float streamDistance;
		int type;
		int worldID;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct RaceCheckpoint
	{
		RaceCheckpoint();

		AMX *amx;
		SharedCell cell;
		int extraID;
		Eigen::Vector3f next;
		Eigen::Vector3f position;
		int raceCheckpointID;
		int references;
		float size;
		float streamDistance;
		int type;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct TextLabel
	{
		TextLabel();

		AMX *amx;
		SharedCell cell;
		int color;
		float drawDistance;
		int extraID;
		Eigen::Vector3f position;
		int references;
		float streamDistance;
		bool testLOS;
		std::string text;
		int textLabelID;

		struct Attach
		{
			Attach();

			int player;
			Eigen::Vector3f position;
			int references;
			int vehicle;
		};

		boost::intrusive_ptr<Attach> attach;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};
}

#endif
