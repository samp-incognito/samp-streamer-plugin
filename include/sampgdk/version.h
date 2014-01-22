/* Copyright (C) 2011-2012, Zeex
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
#pragma once

#define SAMPGDK_VERSION_MAJOR  3
#define SAMPGDK_VERSION_MINOR  0
#define SAMPGDK_VERSION_PATCH  2
#define SAMPGDK_VERSION_TWEAK  0
#define SAMPGDK_VERSION_ID     ((SAMPGDK_VERSION_MAJOR << 24) |\
                                (SAMPGDK_VERSION_MINOR << 16) |\
                                (SAMPGDK_VERSION_PATCH << 8) |\
                                (SAMPGDK_VERSION_TWEAK))
#define SAMPGDK_VERSION_STRING "3.0.2"

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_version_id();
SAMPGDK_EXPORT const char *SAMPGDK_CALL sampgdk_version_string();

#endif /* !SAMPGDK_VERSION_H */
