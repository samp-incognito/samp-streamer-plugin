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

#ifndef SAMPGDK_CORE_H
#define SAMPGDK_CORE_H

#include <stdarg.h>

#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/sdk.h>

/**
 * \defgroup core      Core
 * \defgroup interop   Interop
 * \defgroup version   Version
 * \defgroup sdk       SA-MP SDK
 * \defgroup natives   SA-MP Natives
 * \defgroup callbacks SA-MP Callbacks
 */

/**
 * \addtogroup core
 * @{
 */

/**
 * \brief Returns supported SDK version.
 *
 * This function is intended to be used in Supports(). For example:
 *
 * \code
 * PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
 *   return sampgdk_Supports() | SUPPORTS_PROCESS_TICK;
 * }
 * \endcode
 *
 * \returns SUPPORTS_VERSION.
 */
SAMPGDK_API(unsigned int, sampgdk_Supports(void));

/**
 * \brief Initializes the library.
 * 
 * When called for the first time, sets up internal global state and
 * registers the calling plugin for receiving events. All subsequent
 * calls are ignored until sampgdk_Unload() is called.
 *
 * This function is intended to be used in Load(). For example:
 *
 * \code
 * PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
 *   ...
 *   return sampgdk_Load(ppData);
 * }
 * \endcode
 *
 * \param ppData A pointer to the SA-MP plugin data passed to Load().
 *
 * \returns Returns \c true on success and \c false otherwise.
 *
 * \see sampgdk_Unload()
 */
SAMPGDK_API(bool, sampgdk_Load(void **ppData));

/**
 * \brief Performs the final cleanup.
 *
 * This function is intended to be using in Unload(). For example:
 *
 * \code
 * PLUGIN_EXPORT void PLUGIN_CALL Unload() {
 *   ...
 *   sampgdk_Unload();
 * }
 * \endcode
 *
 * \see sampgdk_Load()
 */
SAMPGDK_API(void, sampgdk_Unload(void));

/**
 * \brief Processes timers created by the calling plugin.
 *
 * \see sampgdk_process_plugin_timers()
 */
SAMPGDK_API(void, sampgdk_ProcessTick(void));

/**
 * \brief Prints a message to the server log.
 *
 * \note The resulting message cannot be longer than 1024 characters.
 *
 * \param format A printf-like format string.
 * \param ... Further arguments to logprintf().
 *
 * \see sampgdk_vlogprintf()
 */
SAMPGDK_API(void, sampgdk_logprintf(const char *format, ...));

/**
 * \brief Prints a message to the server log.
 *
 * This is a \c va_list version of sampgdk_logprintf().
 *
 * \param format A printf-like format string.
 * \param args Further arguments to logprintf().
 *
 * \see sampgdk_logprintf()
 */
SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args));

/** @} */

#endif /* !SAMPGDK_CORE_H */
