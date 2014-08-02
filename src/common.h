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

#ifndef COMMON_H
#define COMMON_H

#define STREAMER_MAX_TYPES (8)

#define STREAMER_TYPE_OBJECT (0)
<<<<<<< HEAD
#define STREAMER_TYPE_VEHICLE (1)
#define STREAMER_TYPE_PICKUP (2)
#define STREAMER_TYPE_CP (3)
#define STREAMER_TYPE_RACE_CP (4)
#define STREAMER_TYPE_MAP_ICON (5)
#define STREAMER_TYPE_3D_TEXT_LABEL (6)
#define STREAMER_TYPE_AREA (7)
=======
#define STREAMER_TYPE_PICKUP (1)
#define STREAMER_TYPE_CP (2)
#define STREAMER_TYPE_RACE_CP (3)
#define STREAMER_TYPE_MAP_ICON (4)
#define STREAMER_TYPE_3D_TEXT_LABEL (5)
#define STREAMER_TYPE_AREA (6)
#define STREAMER_TYPE_VEHICLE (7)
>>>>>>> eb58555d09afd5eef80ed420a45e41a2f820cc69

#define STREAMER_MAX_AREA_TYPES (5)

#define STREAMER_AREA_TYPE_CIRCLE (0)
#define STREAMER_AREA_TYPE_RECTANGLE (1)
#define STREAMER_AREA_TYPE_SPHERE (2)
#define STREAMER_AREA_TYPE_CUBE (3)
#define STREAMER_AREA_TYPE_POLYGON (4)

#define STREAMER_MAX_OBJECT_TYPES (3)

#define STREAMER_OBJECT_TYPE_GLOBAL (0)
#define STREAMER_OBJECT_TYPE_PLAYER (1)
#define STREAMER_OBJECT_TYPE_DYNAMIC (2)

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

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include <Eigen/Core>

#include <utility>

class Cell;
class Data;
class Events;
class Identifier;
class Grid;
struct Player;
class Streamer;

typedef std::pair<int, int> CellID;
typedef boost::intrusive_ptr<Cell> SharedCell;

typedef boost::geometry::model::box<Eigen::Vector2f> Box2D;
typedef boost::geometry::model::box<Eigen::Vector3f> Box3D;
typedef boost::tuple<boost::geometry::model::polygon<Eigen::Vector2f>, Eigen::Vector2f> Polygon2D;

namespace Item
{
	struct Area;
	struct Checkpoint;
	struct MapIcon;
	struct Object;
	struct Pickup;
	struct RaceCheckpoint;
	struct TextLabel;
	struct Vehicle;

	typedef boost::intrusive_ptr<Area> SharedArea;
	typedef boost::intrusive_ptr<Checkpoint> SharedCheckpoint;
	typedef boost::intrusive_ptr<MapIcon> SharedMapIcon;
	typedef boost::intrusive_ptr<Object> SharedObject;
	typedef boost::intrusive_ptr<Pickup> SharedPickup;
	typedef boost::intrusive_ptr<RaceCheckpoint> SharedRaceCheckpoint;
	typedef boost::intrusive_ptr<TextLabel> SharedTextLabel;
	typedef boost::intrusive_ptr<Vehicle> SharedVehicle;
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
