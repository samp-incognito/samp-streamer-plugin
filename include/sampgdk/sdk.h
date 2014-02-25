/* Copyright (C) 2011-2014 Zeex
 * Portions Copyright 2004-2007 SA:MP Team
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

#ifndef SAMPGDK_AMX_H
#define SAMPGDK_AMX_H

#include <sampgdk/bool.h>
#include <sampgdk/platform.h>

/* stdint.h */
#if !defined HAVE_STDINT_H
  #if (!defined __STDC__ && __STDC_VERSION__ >= 199901L /* C99 or newer */)\
    || (defined _MSC_VER && _MSC_VER >= 1600 /* Visual Studio 2010 and later */)\
    || defined __GNUC__ /* GCC, MinGW, etc */
    #define HAVE_STDINT_H 1
  #endif
#endif

/* size_t */
#include <stddef.h>

/* alloca() */
#if SAMPGDK_WINDOWS
  #undef HAVE_ALLOCA_H
  #include <malloc.h> /* for _alloca() */
  #if !defined alloca
    #define alloca _alloca
  #endif
#elif SAMPGDK_LINUX
  #if defined __GNUC__
    #define HAVE_ALLOCA_H 1
    #if !defined alloca
      #define alloca __builtin_alloca
    #endif
  #endif
#endif

#if defined __INTEL_COMPILER
  /* ... */
#elif defined __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wignored-attributes"
#elif defined __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wattributes"
#endif

#include <sdk/amx/amx.h>
#include <sdk/plugin.h>

#if defined __INTEL_COMPILER
  /* ... */
#elif defined __clang_
  #pragma clang diagnostic pop
#elif defined __GNUC__
  #pragma GCC diagnostic pop
#endif

/**
 * \addtogroup sdk
 * @{
 */

/**
 * \brief Entry point index used for fake GDK publics.
 */
#define AMX_EXEC_GDK (-10)

/**
 * \brief Gets called before Load() to check for compatibility.
 *
 * The Supports() function indicates what possibilities this
 * plugin has. The SUPPORTS_VERSION flag is required to check
 * for compatibility with the server. 
 *
 * \returns One or more of the SUPPORTS_* flags.
 */
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports();

/**
 * \brief Gets called when the plugin is loaded.
 *
 * The Load() function gets passed on exported functions from
 * the SA-MP Server, like the AMX Functions and logprintf().
 * Should return true if loading the plugin has succeeded.
 *
 * \returns True of if the plugin has successfully loaded and
 * false otherwise.
 */
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData);

/**
 * \brief Gets called when the plugin is unloaded.
 *
 * The Unload() function is called when the server shuts down,
 * meaning this plugin gets shut down with it.
 */
PLUGIN_EXPORT void PLUGIN_CALL Unload();

/**
 * \brief Gets called when a new script is loaded.
 *
 * The AmxLoad() function gets called when a new gamemode or
 * filterscript gets loaded with the server. In here we register
 * the native functions we like to add to the scripts.
 *
 * \returns One of the AMX error codes.
 */
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx);

/**
 * \brief Gets called when a script is unloaded.
 *
 * When a gamemode is over or a filterscript gets unloaded, this
 * function gets called. No special actions needed in here.
 *
 * \returns One of the AMX error codes.
 */
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx);

/**
 * \brief Gets called on every server tick.
 *
 * Each tick corresponds to one iteration of the server's internal
 * event loop. The interval between ticks depends on many factors,
 * but it's possible to set the minimum tick rate via server.cfg
 * (default is 5ms).
 */
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick();

/** @} */

#endif /* !SAMPGDK_AMX_H */
