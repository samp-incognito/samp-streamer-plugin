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

#ifndef SAMPGDK_EXPORT_H
#define SAMPGDK_EXPORT_H

#include <sampgdk/platform.h>
#include <sampgdk/sdk.h>

#undef SAMPGDK_EXPORT
#undef SAMPGDK_CALL

#ifdef __cplusplus
  #define SAMPGDK_EXTERN_C extern "C"
#else
  #define SAMPGDK_EXTERN_C
#endif

#if defined SAMPGDK_STATIC || defined SAMPGDK_AMALGAMATION
  #define SAMPGDK_CALL
#else
  #define SAMPGDK_CALL SAMPGDK_CDECL
#endif

#if defined SAMPGDK_STATIC || defined SAMPGDK_AMALGAMATION
  #define SAMPGDK_EXPORT SAMPGDK_EXTERN_C
#else
  #if SAMPGDK_LINUX
    #if defined IN_SAMPGDK
      #define SAMPGDK_EXPORT SAMPGDK_EXTERN_C __attribute__((visibility("default")))
    #else
      #define SAMPGDK_EXPORT SAMPGDK_EXTERN_C
    #endif
  #elif SAMPGDK_WINDOWS
    #if defined IN_SAMPGDK
      #define SAMPGDK_EXPORT SAMPGDK_EXTERN_C __declspec(dllexport)
    #else
      #define SAMPGDK_EXPORT SAMPGDK_EXTERN_C __declspec(dllimport)
    #endif
  #else
    #error Usupported operating system
  #endif
#endif

#define SAMPGDK_API(return_type, rest) \
  SAMPGDK_EXPORT return_type SAMPGDK_CALL rest

#undef SAMPGDK_NATIVE_EXPORT
#undef SAMPGDK_NATIVE_CALL

#define SAMPGDK_NATIVE_EXPORT SAMPGDK_EXPORT
#define SAMPGDK_NATIVE_CALL SAMPGDK_CALL
#define SAMPGDK_NATIVE(return_type, rest) \
  SAMPGDK_NATIVE_EXPORT return_type SAMPGDK_NATIVE_CALL rest

#undef SAMPGDK_CALLBACK_EXPORT
#undef SAMPGDK_CALLBACK_CALL

#define SAMPGDK_CALLBACK_EXPORT PLUGIN_EXPORT
#define SAMPGDK_CALLBACK_CALL PLUGIN_CALL
#define SAMPGDK_CALLBACK(return_type, rest) \
  SAMPGDK_CALLBACK_EXPORT return_type SAMPGDK_CALLBACK_CALL rest

#endif /* !SAMPGDK_EXPORT_H */
