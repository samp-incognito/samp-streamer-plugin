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

#ifndef UTILITY_GEOMETRY_H
#define UTILITY_GEOMETRY_H

#include "../common.h"
#include "../item.h"

#include <Eigen/Core>

#define MAX_BUFFER (1024)

namespace Utility
{
	bool doesLineSegmentIntersectArea(const Eigen::Vector3f &lineSegmentStart, const Eigen::Vector3f &lineSegmentEnd, const Item::SharedArea &area);
	bool isPointInArea(const Eigen::Vector3f &point, const Item::SharedArea &area);

	void projectPoint(const Eigen::Vector3f &point, const float &heading, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const Eigen::Vector3f &rotation, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const Eigen::Vector4f &quaternion, Eigen::Vector3f &position);

	// "Fast, Branchless Ray/Bounding Box Intersections" by Tavian Barnes
	template<typename T1, typename T2>
	bool doesLineSegmentIntersectBox(const T1 &lineSegmentStart, const T1 &lineSegmentEnd, const T2 &box)
	{
		T1 intersectionInterval = T1::Zero();

		#ifdef _WIN32
			#pragma warning(push)
			// Disable the "potential divide by zero" warning
			#pragma warning(disable: 4723)
		#endif

		T1 lineSegmentEndInverse = lineSegmentEnd.cwiseInverse();

		#ifdef _WIN32
			#pragma warning(pop)
		#endif

		float min = 0.0f, max = 0.0f;
		for (int i = 0; i < intersectionInterval.size(); ++i)
		{
			intersectionInterval[0] = (box.min_corner()[i] - lineSegmentStart[i]) * lineSegmentEndInverse[i];
			intersectionInterval[1] = (box.max_corner()[i] - lineSegmentStart[i]) * lineSegmentEndInverse[i];
			if (!i)
			{
				min = std::min(intersectionInterval[0], intersectionInterval[1]);
				max = std::max(intersectionInterval[0], intersectionInterval[1]);
			}
			else
			{
				min = std::max(min, std::min(std::min(intersectionInterval[0], intersectionInterval[1]), max));
				max = std::min(max, std::max(std::max(intersectionInterval[0], intersectionInterval[1]), min));
			}
		}
		return max > std::max(min, 0.0f);
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
