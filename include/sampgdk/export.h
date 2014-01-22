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

#ifndef SAMPGDK_EXPORT_H
#define SAMPGDK_EXPORT_H
#pragma once

#undef SAMPGDK_EXPORT
#undef SAMPGDK_CALL

#include <sampgdk/config.h>

#define SAMPGDK_CALL
#define SAMPGDK_EXPORT

#define SAMPGDK_NATIVE(ret_type, native) \
	SAMPGDK_EXPORT ret_type SAMPGDK_CALL sampgdk_##native

#endif /* SAMPGDK_EXPORT_H */
