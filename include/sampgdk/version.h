/* Copyright (C) 2011-2014 Zeex
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

#ifndef SAMPGDK_VERSION_H
#define SAMPGDK_VERSION_H

#include <sampgdk/export.h>

/**
 * \addtogroup version
 * @{
 */

/**
 * \brief Major version.
 */
#define SAMPGDK_VERSION_MAJOR 3

/**
 * \brief Minor version.
 */
#define SAMPGDK_VERSION_MINOR 99

/**
 * \brief Patch version.
 */
#define SAMPGDK_VERSION_PATCH 0

/**
 * \brief Library version in the form of \c 0xAABBCC00 where \c AA, \c BB
 * and \c CC are the major, minor and patch numbers.
 */
#define SAMPGDK_VERSION_ID 56819712

/**
 * \brief Library version string.
 */
#define SAMPGDK_VERSION_STRING "3.99.0"

/**
 * \brief Gets library version number.
 *
 * \returns The version number in the form of \c 0xAABBCCDD where \c AA, 
 * c BB and \c CC are the major, minor and patch numbers.
 *
 * \see SAMPGDK_VERSION_ID
 * \see sampgdk_get_version_string()
 */
SAMPGDK_API(int, sampgdk_GetVersion(void));

/**
 * \brief Gets library version string.
 *
 * \returns The version string in the form of \c x.y.z
 *
 * \see SAMPGDK_VERSION_STRING
 * \see sampgdk_get_version().
 */
SAMPGDK_API(const char *, sampgdk_GetVersionString(void));

/** @} */

#endif /* !SAMPGDK_VERSION_H */
