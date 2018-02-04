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

#ifndef UTILITY_GEOMETRY_H
#define UTILITY_GEOMETRY_H

#include "misc.h"
#include "../item.h"

namespace Utility
{
	bool doesLineSegmentIntersectArea(const Eigen::Vector3f &lineSegmentStart, const Eigen::Vector3f &lineSegmentEnd, const Item::SharedArea &area);
	bool isPointInArea(const Eigen::Vector3f &point, const Item::SharedArea &area);

	void constructAttachedArea(const Item::SharedArea &area, const boost::variant<float, Eigen::Vector3f, Eigen::Vector4f> &orientation, const Eigen::Vector3f location);

	void projectPoint(const Eigen::Vector3f &point, const boost::variant<float, Eigen::Vector3f, Eigen::Vector4f> &orientation, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const float &heading, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const Eigen::Vector3f &rotation, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const Eigen::Vector4f &quaternion, Eigen::Vector3f &position);

	template<typename T1, typename T2>
	bool doesLineSegmentIntersectBox(const T1 &lineSegmentStart, const T1 &lineSegmentEnd, const T2 &box)
	{
		boost::geometry::model::segment<T1> lineSegment = boost::geometry::model::segment<T1>(lineSegmentStart, lineSegmentEnd);
		return boost::geometry::intersects(lineSegment, box);
	}

	template<typename T>
	bool doesLineSegmentIntersectCircleOrSphere(const T &lineSegmentStart, const T &lineSegmentEnd, const T &center, float squaredRadius)
	{
		boost::geometry::model::segment<T> lineSegment = boost::geometry::model::segment<T>(lineSegmentStart, lineSegmentEnd);
		float comparableDistance = static_cast<float>(boost::geometry::comparable_distance(lineSegment, center));
		return comparableDistance < squaredRadius || almostEquals(comparableDistance, squaredRadius);
	}
}

#endif
