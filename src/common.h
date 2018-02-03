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

#ifndef COMMON_H
#define COMMON_H

#define INVALID_PICKUP_ID (-1)
#define INVALID_STREAMER_ID (0)

#define STREAMER_MAX_TYPES (8)

#define STREAMER_TYPE_OBJECT (0)
#define STREAMER_TYPE_PICKUP (1)
#define STREAMER_TYPE_CP (2)
#define STREAMER_TYPE_RACE_CP (3)
#define STREAMER_TYPE_MAP_ICON (4)
#define STREAMER_TYPE_3D_TEXT_LABEL (5)
#define STREAMER_TYPE_AREA (6)
#define STREAMER_TYPE_ACTOR (7)

#define STREAMER_MAX_AREA_TYPES (6)

#define STREAMER_AREA_TYPE_CIRCLE (0)
#define STREAMER_AREA_TYPE_CYLINDER (1)
#define STREAMER_AREA_TYPE_SPHERE (2)
#define STREAMER_AREA_TYPE_RECTANGLE (3)
#define STREAMER_AREA_TYPE_CUBOID (4)
#define STREAMER_AREA_TYPE_POLYGON (5)

#define STREAMER_MAX_OBJECT_TYPES (3)

#define STREAMER_OBJECT_TYPE_GLOBAL (0)
#define STREAMER_OBJECT_TYPE_PLAYER (1)
#define STREAMER_OBJECT_TYPE_DYNAMIC (2)

#define STREAMER_STATIC_DISTANCE_CUTOFF (0.0f)

template<typename T>
inline void intrusive_ptr_add_ref(T *t)
{
	++t->references;
}

template<typename T>
inline void intrusive_ptr_release(T *t)
{
	if (!(--t->references))
	{
		delete t;
	}
}

#include "sampgdk.h"

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include <Eigen/Core>

#include <utility>

class Cell;
class Data;
class Events;
class Grid;
class Identifier;
struct Player;
class Streamer;

typedef std::pair<int, int> CellId;
typedef boost::intrusive_ptr<Cell> SharedCell;

typedef boost::geometry::model::box<Eigen::Vector2f> Box2d;
typedef boost::geometry::model::box<Eigen::Vector3f> Box3d;
typedef boost::geometry::model::polygon<Eigen::Vector2f> Polygon2d;

namespace Item
{
	struct Actor;
	struct Area;
	struct Checkpoint;
	struct MapIcon;
	struct Object;
	struct Pickup;
	struct RaceCheckpoint;
	struct TextLabel;

	typedef boost::intrusive_ptr<Actor> SharedActor;
	typedef boost::intrusive_ptr<Area> SharedArea;
	typedef boost::intrusive_ptr<Checkpoint> SharedCheckpoint;
	typedef boost::intrusive_ptr<MapIcon> SharedMapIcon;
	typedef boost::intrusive_ptr<Object> SharedObject;
	typedef boost::intrusive_ptr<Pickup> SharedPickup;
	typedef boost::intrusive_ptr<RaceCheckpoint> SharedRaceCheckpoint;
	typedef boost::intrusive_ptr<TextLabel> SharedTextLabel;

	template<typename T>
	struct Hash
	{
		std::size_t operator()(boost::tuple<int, T> const &t) const
		{
			std::size_t seed = 0;
			boost::hash_combine(seed, boost::get<0>(t));
			boost::hash_combine(seed, boost::get<1>(t));
			return seed;
		}
	};

	struct PairCompare
	{
		bool operator()(std::pair<int, float> const &a, std::pair<int, float> const &b) const
		{
			if (a.first != b.first)
			{
				return a.first > b.first;
			}
			return a.second < b.second;
		}
	};

	template<typename T>
	struct LeftTupleCompare
	{
		bool operator()(boost::tuple<int, float> const &a, boost::tuple<int, float> const &b) const
		{
			if (boost::get<0>(a) != boost::get<0>(b))
			{
				return boost::get<0>(a) > boost::get<0>(b);
			}
			return boost::get<1>(a) < boost::get<1>(b);
		}
	};

	template<typename T>
	struct RightTupleCompare
	{
		bool operator()(boost::tuple<int, T> const &a, boost::tuple<int, T> const &b) const
		{
			return boost::get<0>(a) == boost::get<0>(b) && boost::get<1>(a) == boost::get<1>(b);
		}
	};

	template<typename T>
	struct Bimap
	{
		typedef boost::bimap<boost::bimaps::multiset_of<boost::tuple<int, float>, LeftTupleCompare<T> >, boost::bimaps::unordered_set_of<boost::tuple<int, T>, Hash<T>, RightTupleCompare<T> > > Type;
	};
}

namespace boost { namespace geometry { namespace traits {
	template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
	struct tag<Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> >
	{
		typedef point_tag type;
	};

	template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
	struct coordinate_type<Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> >
	{
		typedef _Scalar type;
	};

	template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
	struct coordinate_system<Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> >
	{
		typedef cs::cartesian type;
	};

	template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
	struct dimension<Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> > : boost::mpl::int_<_Rows> {};

	template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols, std::size_t Dimension>
	struct access<Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>, Dimension>
	{
		static inline _Scalar get(Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> const &matrix)
		{
			return matrix[Dimension];
		}

		static inline void set(Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> &matrix, _Scalar const &value)
		{
			matrix[Dimension] = value;
		}
	};
}}}

#endif
