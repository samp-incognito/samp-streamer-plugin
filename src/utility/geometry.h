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
	bool isPointInArea(const Eigen::Vector3f &point, const Item::SharedArea &area);

	void projectPoint(const Eigen::Vector3f &point, const float &heading, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const Eigen::Vector3f &rotation, Eigen::Vector3f &position);
	void projectPoint(const Eigen::Vector3f &point, const Eigen::Vector4f &quaternion, Eigen::Vector3f &position);

#endif
