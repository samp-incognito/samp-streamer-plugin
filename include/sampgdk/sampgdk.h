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

#ifndef SAMPGDK_BOOL_H
#define SAMPGDK_BOOL_H

/* bool */
#if !defined __cplusplus && !defined HAVE_BOOL
  /* If HAVE_BOOL is not defined we attempt to detect stdbool.h first,
   * then define our own "bool" type.
   */
  #if defined __STDC__ && defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L\
      || defined HAVE_STDBOOL_H
    /* Have a C99-conformant compiler. */
    #include <stdbool.h>
  #else
    typedef unsigned char bool;
    #define true 1
    #define false 0
    #define __bool_true_false_are_defined
  #endif
#else
  /* Make sure their "bool" is one byte in size. This is required for binary
   * compatibility with C++ code. */
  typedef int sizeof_bool_must_be_1[sizeof(bool) == 1 ? 1 : -1];
#endif

#endif /* !SAMPGDK_BOOL_H */

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

#ifndef SAMPGDK_PLATFORM_H
#define SAMPGDK_PLATFORM_H

#if !defined _M_IX86 && !defined __i386__ && !defined RC_INVOKED
  #error Unsupported architecture
#endif

#if defined WIN32 || defined _WIN32 || defined __WIN32__
  #define SAMPGDK_LINUX 0
  #define SAMPGDK_WINDOWS 1
#endif

#if defined __linux__ || defined __linux || defined linux
  #if !defined LINUX
    #define LINUX
  #endif
  #define SAMPGDK_LINUX 1
  #define SAMPGDK_WINDOWS 0
#endif

#if defined __GNUC__
  #define SAMPGDK_DEPRECATED_API(type, rest) \
    SAMPGDK_API(type, rest) __attribute__((deprecated))
#elif defined _MSC_VER
  #define SAMPGDK_DEPRECATED_API(return_type, rest) \
    __declspec(deprecated) SAMPGDK_API(return_type, rest)
#else
  #define SAMPGDK_DEPRECATED_API(return_type, rest)
#endif

#if SAMPGDK_WINDOWS
  #define SAMPGDK_CDECL __cdecl
  #define SAMPGDK_STDCALL __stdcall
#elif SAMPGDK_LINUX
  #define SAMPGDK_CDECL __attribute__((cdecl))
  #define SAMPGDK_STDCALL __attribute__((stdcall))
#endif

#endif /* !SAMPGDK_PLATFORM_H */

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

/* #include <sampgdk/bool.h> */
/* #include <sampgdk/platform.h> */

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

/* #include <sampgdk/platform.h> */
/* #include <sampgdk/sdk.h> */

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

/* #include <sampgdk/export.h> */

/**
 * \addtogroup version
 * @{
 */

/**
 * \brief Major version.
 */
#define SAMPGDK_VERSION_MAJOR 4

/**
 * \brief Minor version.
 */
#define SAMPGDK_VERSION_MINOR 0

/**
 * \brief Patch version.
 */
#define SAMPGDK_VERSION_PATCH 1

/**
 * \brief Library version in the form of \c 0xAABBCC00 where \c AA, \c BB
 * and \c CC are the major, minor and patch numbers.
 */
#define SAMPGDK_VERSION_ID 67109120

/**
 * \brief Library version string.
 */
#define SAMPGDK_VERSION_STRING "4.0.1"

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

#ifdef __cplusplus

namespace sampgdk {

/// \brief C++ wrapper around sampgdk_GetVersion().
inline int GetVersion() {
  return sampgdk_GetVersion();
}

/// \brief C++ wrapper around sampgdk_GetVersionString().
inline const char *GetVersionString() {
  return sampgdk_GetVersionString();
}

} // namespace sampgdk

#endif /* __cplusplus */

/** @} */

#endif /* !SAMPGDK_VERSION_H */

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

/* #include <sampgdk/bool.h> */
/* #include <sampgdk/export.h> */
/* #include <sampgdk/sdk.h> */

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
 * \brief Hidden parameter type. Don't use this.
 */
typedef int sampgdk_hidden_t;

/**
 * \brief Returns supported SDK version.
 *
 * This function should be called from Supports():
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
 * This function should be called when the plugin is loaded,
 * e.g. from Load():
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
SAMPGDK_API(bool, sampgdk_Load(void **ppData, sampgdk_hidden_t));

/**
 * \brief Shuts everything down (opposite of sampgdk_Load()).
 *
 * This function should be called when the plugin is unloaded,
 * e.g. from Unload():
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
SAMPGDK_API(void, sampgdk_Unload(sampgdk_hidden_t));

/**
 * \brief Processes timers created by the calling plugin.
 *
 * This function should be called from ProcessTick():
 *
 * \code
 * PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
 *   sampgdk_ProcessTick();
 * }
 * \endcode
 */
SAMPGDK_API(void, sampgdk_ProcessTick(sampgdk_hidden_t));

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
 * This function is identical to sampgdk_logprintf() but takes a
 * \c va_list instead of a variable number of arguments.
 *
 * \param format A printf-like format string.
 * \param args Further arguments to logprintf().
 *
 * \see sampgdk_logprintf()
 */
SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args));

/** @} */

#define sampgdk_Load(ppData)  sampgdk_Load(ppData, 0)
#define sampgdk_Unload()      sampgdk_Unload(0)
#define sampgdk_ProcessTick() sampgdk_ProcessTick(0)

#ifdef __cplusplus

/// \brief Main namespace.
namespace sampgdk {

/**
 * \addtogroup core
 * @{
 */

/// \brief C++ wrapper around sampgdk_Supports().
inline unsigned int Supports() {
  return sampgdk_Supports();
}

/// \brief C++ wrapper around sampgdk_Load().
inline bool Load(void **ppData) {
  return sampgdk_Load(ppData);
}

/// \brief C++ wrapper around sampgdk_Unload().
inline void Unload() {
  sampgdk_Unload();
}

/// \brief C++ wrapper around sampgdk_ProcessTick().
inline void ProcessTick() {
  sampgdk_ProcessTick();
}

/// \brief C++ wrapper around sampgdk_logprintf().
inline void logprintf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  sampgdk_vlogprintf(format, args);
  va_end(args);
}

/// \brief C++ wrapper around sampgdk_vlogprintf().
inline void vlogprintf(const char *format, va_list args) {
  sampgdk_vlogprintf(format, args);
}

/** @} */

} // namespace sampgdk

#endif /* __cplusplus */

#endif /* !SAMPGDK_CORE_H */

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

#ifndef SAMPGDK_TYPES_H
#define SAMPGDK_TYPES_H

/* #include <sampgdk/export.h> */

/**
 * \brief Defines the signature of a timer callback function.
 * \ingroup natives
 *
 * \param timerid The unique ID for the timer returned by SetTimer().
 * \param param A pointer to user-supplied data passed to SetTimer().
 * This parameter may be \c NULL.
 */
typedef void (SAMPGDK_CALL *TimerCallback)(int timerid, void *param);

#endif /* !SAMPGDK_TYPES_H */

/* Copyright (C) 2013-2014 Zeex
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

#ifndef SAMPGDK_INTEROP_H
#define SAMPGDK_INTEROP_H

#include <stdarg.h>

/* #include <sampgdk/bool.h> */
/* #include <sampgdk/export.h> */

/**
 * \addtogroup interop
 * @{
 */

/**
 * \brief Returns all currently registered native functions.
 *
 * This function can be used to get the names and addresses of all native
 * functions that have been registered with amx_Register(), by both the
 * server and plugins.
 *
 * \note The returned array is NULL-terminated.
 *
 * \param number A pointer to the variable that will store the number of
 *               elements in the returned array (optional).
 *
 * \returns A pointer to the internal array of native functions.
 *
 * \see sampgdk_FindNative()
 * \see sampgdk_CallNative()
 * \see sampgdk_InvokeNative()
 */
SAMPGDK_API(const AMX_NATIVE_INFO *, sampgdk_GetNatives(int *number));

/**
 * \brief Finds a native function by name.
 *
 * Searches for a native function with the specified name and returns its
 * address. In order to be found the function must be registered with
 * amx_Register() prior to the call.
 *
 * This function is implemented using binary search.
 *
 * \param name The name of the native function.
 *
 * \returns The function's address or \c NULL if not found.
 *
 * \see sampgdk_GetNatives()
 * \see sampgdk_CallNative()
 * \see sampgdk_InvokeNative()
 */
SAMPGDK_API(AMX_NATIVE, sampgdk_FindNative(const char *name));

/**
 * \brief Calls a native function.
 *
 * This function is suitable for calling simple natives that either have only
 * value parameters or don't have any parameters at all. If you have to pass
 * a reference or a string use sampgdk_InvokeNative() instead.
 *
 * \note The first element of \p params must contain the number of arguments
 * multiplied by \c sizeof(cell).
 *
 * \param native A pointer to the native function.
 * \param params The \c params array passsed to the function.
 *
 * \returns The value returned by the function.
 *
 * \see sampgdk_GetNatives()
 * \see sampgdk_FindNative()
 * \see sampgdk_InvokeNative()
 */
SAMPGDK_API(cell, sampgdk_CallNative(AMX_NATIVE native, cell *params));

/**
 * \brief Invokes a native function with the specified arguments.
 *
 * Argument types are specified via \p format where each character, or
 * *specifier*, corresponds to a single argument. The following format
 * specifiers are supported:
 *
 * Specifier | C/C++ type    | Description
 * :-------- | :------------ | :-------------------------------------
 * i         | int           | integer value
 * d         | int           | integer value (same as 'i')
 * b         | bool          | boolean value
 * f         | double        | floating-point value
 * r         | const cell *  | const reference (input only)
 * R         | cell *        | non-const reference (both input and output)
 * s         | const char *  | const string (input only)
 * S         | char *        | non-const string (both input and output)
 * a         | const cell *  | const string (input only)
 * A         | cell *        | non-const string (both input and output)
 *
 * \remarks For the 'S', 'a' and 'A' specifiers you have to specify the size
 * of the string/array in square brackets, e.g. "a[100]" (fixed size)
 * or s[*2] (size passed via 2nd argument).
 *
 * \note In Pawn, variadic functions always take their variable arguments
 * (those represented by "...") by reference. This means that for such
 * functions you have to use the 'r' specifier where you would normally
 * use 'b', 'i' 'd' or 'f'.
 *
 * \param native A pointer to the native function.
 * \param format A format string specifying the types of the arguments.
 * \param ... The arguments themselves.
 *
 * \returns The value returned by the function.
 *
 * \see sampgdk_GetNatives()
 * \see sampgdk_FindNative()
 * \see sampgdk_InvokeNativeV()
 * \see sampgdk_InvokeNativeArray()
 */
SAMPGDK_API(cell, sampgdk_InvokeNative(AMX_NATIVE native,
    const char *format, ...));

/**
* \brief Invokes a native function with the specified arguments.
*
* This function is identical to sampgdk_InvokeNative() but takes a
* \c va_list instead of a variable number of arguments.
*
* \see sampgdk_GetNatives()
* \see sampgdk_FindNative()
* \see sampgdk_InvokeNative()
* \see sampgdk_InvokeNativeArray()
*/
SAMPGDK_API(cell, sampgdk_InvokeNativeV(AMX_NATIVE native,
    const char *format, va_list args));

/**
* \brief Invokes a native function with the specified arguments.
*
* This function is similar to sampgdk_InvokeNative() but the arguments
* are passed as an array where each element is a pointer pointing to
* the actual value.
*
* Argument types are specified via \p format where each character, or
* *specifier*, corresponds to a single argument. See sampgdk_InvokeNative()
* for the list of supported format specifiers.
*
* \param native A pointer to the native function.
* \param format A format string specifying the types of the arguments.
* \param args The arguments themselves.
*
* \returns The value returned by the function.
*
* \see sampgdk_GetNatives()
* \see sampgdk_FindNative()
* \see sampgdk_InvokeNative()
*/
SAMPGDK_API(cell, sampgdk_InvokeNativeArray(AMX_NATIVE native,
    const char *format, void **args));

/**
 * \brief Gets called on every public function call.
 *
 * This is the public filter callback. It is called whenever the server
 * calls \c amx_Exec(), which practiacally means that you can use it to
 * hook *any* callback, even those that are called by other plugins.
 *
 * \param amx The AMX instance on which the public function is called.
 * \param name The name of the function.
 * \param params The function's arguments as stored on the AMX stack, with
 * \c params[0] set to the number of arguments multiplied by \c sizeof(cell).
 * \param retval The function's return value. This parameter can be \c NULL.
 *
 * \returns If returns \c true the callback is executed,
 *          otherwise it's ignored.
 */
SAMPGDK_CALLBACK(bool, OnPublicCall(AMX *amx, const char *name,
    cell *params, cell *retval));

/** @} */

#ifdef __cplusplus

namespace sampgdk {

/**
  * \addtogroup interop
  * @{
  */

/// \brief C++ wrapper around sampgdk_GetNatives().
inline const AMX_NATIVE_INFO *GetNatives(int &number) {
  return sampgdk_GetNatives(&number);
}

/// \brief C++ wrapper around sampgdk_GetNatives().
inline const AMX_NATIVE_INFO *GetNatives() {
  return sampgdk_GetNatives(0);
}

/// \brief C++ wrapper around sampgdk_FindNative().
inline AMX_NATIVE FindNative(const char *name) {
  return sampgdk_FindNative(name);
}

/// \brief C++ wrapper around sampgdk_CallNative().
inline cell CallNative(AMX_NATIVE native, cell *params) {
  return sampgdk_CallNative(native, params);
}

/// \brief C++ wrapper around sampgdk_InvokeNative().
inline cell InvokeNative(AMX_NATIVE native, const char *format, ...) {
  va_list args;
  va_start(args, format);
  cell retval = sampgdk_InvokeNativeV(native, format, args);
  va_end(args);
  return retval;
}

/// \brief C++ wrapper around sampgdk_InvokeNativeV().
inline cell InvokeNativeV(AMX_NATIVE native, const char *format,
    va_list args) {
  return sampgdk_InvokeNativeV(native, format, args);
}

/// \brief C++ wrapper around sampgdk_InvokeNativeArray().
inline cell InvokeNativeArray(AMX_NATIVE native, const char *format,
    void **args) {
  return sampgdk_InvokeNativeArray(native, format, args);
}

/** @} */

} // namespace sampgdk

#endif /* __cplusplus */

#endif /* !SAMPGDK_INTEROP_H */

/* #include <sampgdk/bool.h> */
/* #include <sampgdk/export.h> */
/* #include <sampgdk/types.h> */

#ifndef DOXYGEN
#undef  IsValidVehicle
#define IsValidVehicle sampgdk_IsValidVehicle
#undef  GetVehicleDistanceFromPoint
#define GetVehicleDistanceFromPoint sampgdk_GetVehicleDistanceFromPoint
#undef  CreateVehicle
#define CreateVehicle sampgdk_CreateVehicle
#undef  DestroyVehicle
#define DestroyVehicle sampgdk_DestroyVehicle
#undef  IsVehicleStreamedIn
#define IsVehicleStreamedIn sampgdk_IsVehicleStreamedIn
#undef  GetVehiclePos
#define GetVehiclePos sampgdk_GetVehiclePos
#undef  SetVehiclePos
#define SetVehiclePos sampgdk_SetVehiclePos
#undef  GetVehicleZAngle
#define GetVehicleZAngle sampgdk_GetVehicleZAngle
#undef  GetVehicleRotationQuat
#define GetVehicleRotationQuat sampgdk_GetVehicleRotationQuat
#undef  SetVehicleZAngle
#define SetVehicleZAngle sampgdk_SetVehicleZAngle
#undef  SetVehicleParamsForPlayer
#define SetVehicleParamsForPlayer sampgdk_SetVehicleParamsForPlayer
#undef  ManualVehicleEngineAndLights
#define ManualVehicleEngineAndLights sampgdk_ManualVehicleEngineAndLights
#undef  SetVehicleParamsEx
#define SetVehicleParamsEx sampgdk_SetVehicleParamsEx
#undef  GetVehicleParamsEx
#define GetVehicleParamsEx sampgdk_GetVehicleParamsEx
#undef  SetVehicleToRespawn
#define SetVehicleToRespawn sampgdk_SetVehicleToRespawn
#undef  LinkVehicleToInterior
#define LinkVehicleToInterior sampgdk_LinkVehicleToInterior
#undef  AddVehicleComponent
#define AddVehicleComponent sampgdk_AddVehicleComponent
#undef  RemoveVehicleComponent
#define RemoveVehicleComponent sampgdk_RemoveVehicleComponent
#undef  ChangeVehicleColor
#define ChangeVehicleColor sampgdk_ChangeVehicleColor
#undef  ChangeVehiclePaintjob
#define ChangeVehiclePaintjob sampgdk_ChangeVehiclePaintjob
#undef  SetVehicleHealth
#define SetVehicleHealth sampgdk_SetVehicleHealth
#undef  GetVehicleHealth
#define GetVehicleHealth sampgdk_GetVehicleHealth
#undef  AttachTrailerToVehicle
#define AttachTrailerToVehicle sampgdk_AttachTrailerToVehicle
#undef  DetachTrailerFromVehicle
#define DetachTrailerFromVehicle sampgdk_DetachTrailerFromVehicle
#undef  IsTrailerAttachedToVehicle
#define IsTrailerAttachedToVehicle sampgdk_IsTrailerAttachedToVehicle
#undef  GetVehicleTrailer
#define GetVehicleTrailer sampgdk_GetVehicleTrailer
#undef  SetVehicleNumberPlate
#define SetVehicleNumberPlate sampgdk_SetVehicleNumberPlate
#undef  GetVehicleModel
#define GetVehicleModel sampgdk_GetVehicleModel
#undef  GetVehicleComponentInSlot
#define GetVehicleComponentInSlot sampgdk_GetVehicleComponentInSlot
#undef  GetVehicleComponentType
#define GetVehicleComponentType sampgdk_GetVehicleComponentType
#undef  RepairVehicle
#define RepairVehicle sampgdk_RepairVehicle
#undef  GetVehicleVelocity
#define GetVehicleVelocity sampgdk_GetVehicleVelocity
#undef  SetVehicleVelocity
#define SetVehicleVelocity sampgdk_SetVehicleVelocity
#undef  SetVehicleAngularVelocity
#define SetVehicleAngularVelocity sampgdk_SetVehicleAngularVelocity
#undef  GetVehicleDamageStatus
#define GetVehicleDamageStatus sampgdk_GetVehicleDamageStatus
#undef  UpdateVehicleDamageStatus
#define UpdateVehicleDamageStatus sampgdk_UpdateVehicleDamageStatus
#undef  SetVehicleVirtualWorld
#define SetVehicleVirtualWorld sampgdk_SetVehicleVirtualWorld
#undef  GetVehicleVirtualWorld
#define GetVehicleVirtualWorld sampgdk_GetVehicleVirtualWorld
#undef  GetVehicleModelInfo
#define GetVehicleModelInfo sampgdk_GetVehicleModelInfo
#endif


/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsValidVehicle">IsValidVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsValidVehicle(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleDistanceFromPoint">GetVehicleDistanceFromPoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreateVehicle">CreateVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreateVehicle(int vehicletype, float x, float y, float z, float rotation, int color1, int color2, int respawn_delay));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DestroyVehicle">DestroyVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DestroyVehicle(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsVehicleStreamedIn">IsVehicleStreamedIn on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsVehicleStreamedIn(int vehicleid, int forplayerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehiclePos">GetVehiclePos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetVehiclePos(int vehicleid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehiclePos">SetVehiclePos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehiclePos(int vehicleid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleZAngle">GetVehicleZAngle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetVehicleZAngle(int vehicleid, float * z_angle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleRotationQuat">GetVehicleRotationQuat on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetVehicleRotationQuat(int vehicleid, float * w, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleZAngle">SetVehicleZAngle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleZAngle(int vehicleid, float z_angle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleParamsForPlayer">SetVehicleParamsForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ManualVehicleEngineAndLights">ManualVehicleEngineAndLights on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ManualVehicleEngineAndLights());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleParamsEx">SetVehicleParamsEx on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleParamsEx">GetVehicleParamsEx on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetVehicleParamsEx(int vehicleid, bool * engine, bool * lights, bool * alarm, bool * doors, bool * bonnet, bool * boot, bool * objective));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleToRespawn">SetVehicleToRespawn on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleToRespawn(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/LinkVehicleToInterior">LinkVehicleToInterior on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, LinkVehicleToInterior(int vehicleid, int interiorid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddVehicleComponent">AddVehicleComponent on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AddVehicleComponent(int vehicleid, int componentid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemoveVehicleComponent">RemoveVehicleComponent on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, RemoveVehicleComponent(int vehicleid, int componentid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ChangeVehicleColor">ChangeVehicleColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ChangeVehicleColor(int vehicleid, int color1, int color2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ChangeVehiclePaintjob">ChangeVehiclePaintjob on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ChangeVehiclePaintjob(int vehicleid, int paintjobid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleHealth">SetVehicleHealth on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleHealth(int vehicleid, float health));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleHealth">GetVehicleHealth on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetVehicleHealth(int vehicleid, float * health));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachTrailerToVehicle">AttachTrailerToVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AttachTrailerToVehicle(int trailerid, int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DetachTrailerFromVehicle">DetachTrailerFromVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DetachTrailerFromVehicle(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsTrailerAttachedToVehicle">IsTrailerAttachedToVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsTrailerAttachedToVehicle(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleTrailer">GetVehicleTrailer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetVehicleTrailer(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleNumberPlate">SetVehicleNumberPlate on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleNumberPlate(int vehicleid, const char * numberplate));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleModel">GetVehicleModel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetVehicleModel(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleComponentInSlot">GetVehicleComponentInSlot on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetVehicleComponentInSlot(int vehicleid, int slot));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleComponentType">GetVehicleComponentType on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetVehicleComponentType(int component));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RepairVehicle">RepairVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, RepairVehicle(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleVelocity">GetVehicleVelocity on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetVehicleVelocity(int vehicleid, float * X, float * Y, float * Z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleVelocity">SetVehicleVelocity on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleVelocity(int vehicleid, float X, float Y, float Z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleAngularVelocity">SetVehicleAngularVelocity on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleDamageStatus">GetVehicleDamageStatus on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetVehicleDamageStatus(int vehicleid, int * panels, int * doors, int * lights, int * tires));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/UpdateVehicleDamageStatus">UpdateVehicleDamageStatus on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, UpdateVehicleDamageStatus(int vehicleid, int panels, int doors, int lights, int tires));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetVehicleVirtualWorld">SetVehicleVirtualWorld on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetVehicleVirtualWorld(int vehicleid, int worldid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleVirtualWorld">GetVehicleVirtualWorld on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetVehicleVirtualWorld(int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetVehicleModelInfo">GetVehicleModelInfo on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetVehicleModelInfo(int model, int infotype, float * X, float * Y, float * Z));

#define CARMODTYPE_SPOILER (0)
#define CARMODTYPE_HOOD (1)
#define CARMODTYPE_ROOF (2)
#define CARMODTYPE_SIDESKIRT (3)
#define CARMODTYPE_LAMPS (4)
#define CARMODTYPE_NITRO (5)
#define CARMODTYPE_EXHAUST (6)
#define CARMODTYPE_WHEELS (7)
#define CARMODTYPE_STEREO (8)
#define CARMODTYPE_HYDRAULICS (9)
#define CARMODTYPE_FRONT_BUMPER (10)
#define CARMODTYPE_REAR_BUMPER (11)
#define CARMODTYPE_VENT_RIGHT (12)
#define CARMODTYPE_VENT_LEFT (13)
#define VEHICLE_PARAMS_UNSET (-1)
#define VEHICLE_PARAMS_OFF (0)
#define VEHICLE_PARAMS_ON (1)
#define VEHICLE_MODEL_INFO_SIZE (1)
#define VEHICLE_MODEL_INFO_FRONTSEAT (2)
#define VEHICLE_MODEL_INFO_REARSEAT (3)
#define VEHICLE_MODEL_INFO_PETROLCAP (4)
#define VEHICLE_MODEL_INFO_WHEELSFRONT (5)
#define VEHICLE_MODEL_INFO_WHEELSREAR (6)
#define VEHICLE_MODEL_INFO_WHEELSMID (7)
#define VEHICLE_MODEL_INFO_FRONT_BUMPER_Z (8)
#define VEHICLE_MODEL_INFO_REAR_BUMPER_Z (9)


/* #include <sampgdk/bool.h> */
/* #include <sampgdk/export.h> */
/* #include <sampgdk/types.h> */

#ifndef DOXYGEN
#undef  SetSpawnInfo
#define SetSpawnInfo sampgdk_SetSpawnInfo
#undef  SpawnPlayer
#define SpawnPlayer sampgdk_SpawnPlayer
#undef  SetPlayerPos
#define SetPlayerPos sampgdk_SetPlayerPos
#undef  SetPlayerPosFindZ
#define SetPlayerPosFindZ sampgdk_SetPlayerPosFindZ
#undef  GetPlayerPos
#define GetPlayerPos sampgdk_GetPlayerPos
#undef  SetPlayerFacingAngle
#define SetPlayerFacingAngle sampgdk_SetPlayerFacingAngle
#undef  GetPlayerFacingAngle
#define GetPlayerFacingAngle sampgdk_GetPlayerFacingAngle
#undef  IsPlayerInRangeOfPoint
#define IsPlayerInRangeOfPoint sampgdk_IsPlayerInRangeOfPoint
#undef  GetPlayerDistanceFromPoint
#define GetPlayerDistanceFromPoint sampgdk_GetPlayerDistanceFromPoint
#undef  IsPlayerStreamedIn
#define IsPlayerStreamedIn sampgdk_IsPlayerStreamedIn
#undef  SetPlayerInterior
#define SetPlayerInterior sampgdk_SetPlayerInterior
#undef  GetPlayerInterior
#define GetPlayerInterior sampgdk_GetPlayerInterior
#undef  SetPlayerHealth
#define SetPlayerHealth sampgdk_SetPlayerHealth
#undef  GetPlayerHealth
#define GetPlayerHealth sampgdk_GetPlayerHealth
#undef  SetPlayerArmour
#define SetPlayerArmour sampgdk_SetPlayerArmour
#undef  GetPlayerArmour
#define GetPlayerArmour sampgdk_GetPlayerArmour
#undef  SetPlayerAmmo
#define SetPlayerAmmo sampgdk_SetPlayerAmmo
#undef  GetPlayerAmmo
#define GetPlayerAmmo sampgdk_GetPlayerAmmo
#undef  GetPlayerWeaponState
#define GetPlayerWeaponState sampgdk_GetPlayerWeaponState
#undef  GetPlayerTargetPlayer
#define GetPlayerTargetPlayer sampgdk_GetPlayerTargetPlayer
#undef  SetPlayerTeam
#define SetPlayerTeam sampgdk_SetPlayerTeam
#undef  GetPlayerTeam
#define GetPlayerTeam sampgdk_GetPlayerTeam
#undef  SetPlayerScore
#define SetPlayerScore sampgdk_SetPlayerScore
#undef  GetPlayerScore
#define GetPlayerScore sampgdk_GetPlayerScore
#undef  GetPlayerDrunkLevel
#define GetPlayerDrunkLevel sampgdk_GetPlayerDrunkLevel
#undef  SetPlayerDrunkLevel
#define SetPlayerDrunkLevel sampgdk_SetPlayerDrunkLevel
#undef  SetPlayerColor
#define SetPlayerColor sampgdk_SetPlayerColor
#undef  GetPlayerColor
#define GetPlayerColor sampgdk_GetPlayerColor
#undef  SetPlayerSkin
#define SetPlayerSkin sampgdk_SetPlayerSkin
#undef  GetPlayerSkin
#define GetPlayerSkin sampgdk_GetPlayerSkin
#undef  GivePlayerWeapon
#define GivePlayerWeapon sampgdk_GivePlayerWeapon
#undef  ResetPlayerWeapons
#define ResetPlayerWeapons sampgdk_ResetPlayerWeapons
#undef  SetPlayerArmedWeapon
#define SetPlayerArmedWeapon sampgdk_SetPlayerArmedWeapon
#undef  GetPlayerWeaponData
#define GetPlayerWeaponData sampgdk_GetPlayerWeaponData
#undef  GivePlayerMoney
#define GivePlayerMoney sampgdk_GivePlayerMoney
#undef  ResetPlayerMoney
#define ResetPlayerMoney sampgdk_ResetPlayerMoney
#undef  SetPlayerName
#define SetPlayerName sampgdk_SetPlayerName
#undef  GetPlayerMoney
#define GetPlayerMoney sampgdk_GetPlayerMoney
#undef  GetPlayerState
#define GetPlayerState sampgdk_GetPlayerState
#undef  GetPlayerIp
#define GetPlayerIp sampgdk_GetPlayerIp
#undef  GetPlayerPing
#define GetPlayerPing sampgdk_GetPlayerPing
#undef  GetPlayerWeapon
#define GetPlayerWeapon sampgdk_GetPlayerWeapon
#undef  GetPlayerKeys
#define GetPlayerKeys sampgdk_GetPlayerKeys
#undef  GetPlayerName
#define GetPlayerName sampgdk_GetPlayerName
#undef  SetPlayerTime
#define SetPlayerTime sampgdk_SetPlayerTime
#undef  GetPlayerTime
#define GetPlayerTime sampgdk_GetPlayerTime
#undef  TogglePlayerClock
#define TogglePlayerClock sampgdk_TogglePlayerClock
#undef  SetPlayerWeather
#define SetPlayerWeather sampgdk_SetPlayerWeather
#undef  ForceClassSelection
#define ForceClassSelection sampgdk_ForceClassSelection
#undef  SetPlayerWantedLevel
#define SetPlayerWantedLevel sampgdk_SetPlayerWantedLevel
#undef  GetPlayerWantedLevel
#define GetPlayerWantedLevel sampgdk_GetPlayerWantedLevel
#undef  SetPlayerFightingStyle
#define SetPlayerFightingStyle sampgdk_SetPlayerFightingStyle
#undef  GetPlayerFightingStyle
#define GetPlayerFightingStyle sampgdk_GetPlayerFightingStyle
#undef  SetPlayerVelocity
#define SetPlayerVelocity sampgdk_SetPlayerVelocity
#undef  GetPlayerVelocity
#define GetPlayerVelocity sampgdk_GetPlayerVelocity
#undef  PlayCrimeReportForPlayer
#define PlayCrimeReportForPlayer sampgdk_PlayCrimeReportForPlayer
#undef  PlayAudioStreamForPlayer
#define PlayAudioStreamForPlayer sampgdk_PlayAudioStreamForPlayer
#undef  StopAudioStreamForPlayer
#define StopAudioStreamForPlayer sampgdk_StopAudioStreamForPlayer
#undef  SetPlayerShopName
#define SetPlayerShopName sampgdk_SetPlayerShopName
#undef  SetPlayerSkillLevel
#define SetPlayerSkillLevel sampgdk_SetPlayerSkillLevel
#undef  GetPlayerSurfingVehicleID
#define GetPlayerSurfingVehicleID sampgdk_GetPlayerSurfingVehicleID
#undef  GetPlayerSurfingObjectID
#define GetPlayerSurfingObjectID sampgdk_GetPlayerSurfingObjectID
#undef  RemoveBuildingForPlayer
#define RemoveBuildingForPlayer sampgdk_RemoveBuildingForPlayer
#undef  GetPlayerLastShotVectors
#define GetPlayerLastShotVectors sampgdk_GetPlayerLastShotVectors
#undef  SetPlayerAttachedObject
#define SetPlayerAttachedObject sampgdk_SetPlayerAttachedObject
#undef  RemovePlayerAttachedObject
#define RemovePlayerAttachedObject sampgdk_RemovePlayerAttachedObject
#undef  IsPlayerAttachedObjectSlotUsed
#define IsPlayerAttachedObjectSlotUsed sampgdk_IsPlayerAttachedObjectSlotUsed
#undef  EditAttachedObject
#define EditAttachedObject sampgdk_EditAttachedObject
#undef  CreatePlayerTextDraw
#define CreatePlayerTextDraw sampgdk_CreatePlayerTextDraw
#undef  PlayerTextDrawDestroy
#define PlayerTextDrawDestroy sampgdk_PlayerTextDrawDestroy
#undef  PlayerTextDrawLetterSize
#define PlayerTextDrawLetterSize sampgdk_PlayerTextDrawLetterSize
#undef  PlayerTextDrawTextSize
#define PlayerTextDrawTextSize sampgdk_PlayerTextDrawTextSize
#undef  PlayerTextDrawAlignment
#define PlayerTextDrawAlignment sampgdk_PlayerTextDrawAlignment
#undef  PlayerTextDrawColor
#define PlayerTextDrawColor sampgdk_PlayerTextDrawColor
#undef  PlayerTextDrawUseBox
#define PlayerTextDrawUseBox sampgdk_PlayerTextDrawUseBox
#undef  PlayerTextDrawBoxColor
#define PlayerTextDrawBoxColor sampgdk_PlayerTextDrawBoxColor
#undef  PlayerTextDrawSetShadow
#define PlayerTextDrawSetShadow sampgdk_PlayerTextDrawSetShadow
#undef  PlayerTextDrawSetOutline
#define PlayerTextDrawSetOutline sampgdk_PlayerTextDrawSetOutline
#undef  PlayerTextDrawBackgroundColor
#define PlayerTextDrawBackgroundColor sampgdk_PlayerTextDrawBackgroundColor
#undef  PlayerTextDrawFont
#define PlayerTextDrawFont sampgdk_PlayerTextDrawFont
#undef  PlayerTextDrawSetProportional
#define PlayerTextDrawSetProportional sampgdk_PlayerTextDrawSetProportional
#undef  PlayerTextDrawSetSelectable
#define PlayerTextDrawSetSelectable sampgdk_PlayerTextDrawSetSelectable
#undef  PlayerTextDrawShow
#define PlayerTextDrawShow sampgdk_PlayerTextDrawShow
#undef  PlayerTextDrawHide
#define PlayerTextDrawHide sampgdk_PlayerTextDrawHide
#undef  PlayerTextDrawSetString
#define PlayerTextDrawSetString sampgdk_PlayerTextDrawSetString
#undef  PlayerTextDrawSetPreviewModel
#define PlayerTextDrawSetPreviewModel sampgdk_PlayerTextDrawSetPreviewModel
#undef  PlayerTextDrawSetPreviewRot
#define PlayerTextDrawSetPreviewRot sampgdk_PlayerTextDrawSetPreviewRot
#undef  PlayerTextDrawSetPreviewVehCol
#define PlayerTextDrawSetPreviewVehCol sampgdk_PlayerTextDrawSetPreviewVehCol
#undef  SetPVarInt
#define SetPVarInt sampgdk_SetPVarInt
#undef  GetPVarInt
#define GetPVarInt sampgdk_GetPVarInt
#undef  SetPVarString
#define SetPVarString sampgdk_SetPVarString
#undef  GetPVarString
#define GetPVarString sampgdk_GetPVarString
#undef  SetPVarFloat
#define SetPVarFloat sampgdk_SetPVarFloat
#undef  GetPVarFloat
#define GetPVarFloat sampgdk_GetPVarFloat
#undef  DeletePVar
#define DeletePVar sampgdk_DeletePVar
#undef  GetPVarsUpperIndex
#define GetPVarsUpperIndex sampgdk_GetPVarsUpperIndex
#undef  GetPVarNameAtIndex
#define GetPVarNameAtIndex sampgdk_GetPVarNameAtIndex
#undef  GetPVarType
#define GetPVarType sampgdk_GetPVarType
#undef  SetPlayerChatBubble
#define SetPlayerChatBubble sampgdk_SetPlayerChatBubble
#undef  PutPlayerInVehicle
#define PutPlayerInVehicle sampgdk_PutPlayerInVehicle
#undef  GetPlayerVehicleID
#define GetPlayerVehicleID sampgdk_GetPlayerVehicleID
#undef  GetPlayerVehicleSeat
#define GetPlayerVehicleSeat sampgdk_GetPlayerVehicleSeat
#undef  RemovePlayerFromVehicle
#define RemovePlayerFromVehicle sampgdk_RemovePlayerFromVehicle
#undef  TogglePlayerControllable
#define TogglePlayerControllable sampgdk_TogglePlayerControllable
#undef  PlayerPlaySound
#define PlayerPlaySound sampgdk_PlayerPlaySound
#undef  ApplyAnimation
#define ApplyAnimation sampgdk_ApplyAnimation
#undef  ClearAnimations
#define ClearAnimations sampgdk_ClearAnimations
#undef  GetPlayerAnimationIndex
#define GetPlayerAnimationIndex sampgdk_GetPlayerAnimationIndex
#undef  GetAnimationName
#define GetAnimationName sampgdk_GetAnimationName
#undef  GetPlayerSpecialAction
#define GetPlayerSpecialAction sampgdk_GetPlayerSpecialAction
#undef  SetPlayerSpecialAction
#define SetPlayerSpecialAction sampgdk_SetPlayerSpecialAction
#undef  SetPlayerCheckpoint
#define SetPlayerCheckpoint sampgdk_SetPlayerCheckpoint
#undef  DisablePlayerCheckpoint
#define DisablePlayerCheckpoint sampgdk_DisablePlayerCheckpoint
#undef  SetPlayerRaceCheckpoint
#define SetPlayerRaceCheckpoint sampgdk_SetPlayerRaceCheckpoint
#undef  DisablePlayerRaceCheckpoint
#define DisablePlayerRaceCheckpoint sampgdk_DisablePlayerRaceCheckpoint
#undef  SetPlayerWorldBounds
#define SetPlayerWorldBounds sampgdk_SetPlayerWorldBounds
#undef  SetPlayerMarkerForPlayer
#define SetPlayerMarkerForPlayer sampgdk_SetPlayerMarkerForPlayer
#undef  ShowPlayerNameTagForPlayer
#define ShowPlayerNameTagForPlayer sampgdk_ShowPlayerNameTagForPlayer
#undef  SetPlayerMapIcon
#define SetPlayerMapIcon sampgdk_SetPlayerMapIcon
#undef  RemovePlayerMapIcon
#define RemovePlayerMapIcon sampgdk_RemovePlayerMapIcon
#undef  AllowPlayerTeleport
#define AllowPlayerTeleport sampgdk_AllowPlayerTeleport
#undef  SetPlayerCameraPos
#define SetPlayerCameraPos sampgdk_SetPlayerCameraPos
#undef  SetPlayerCameraLookAt
#define SetPlayerCameraLookAt sampgdk_SetPlayerCameraLookAt
#undef  SetCameraBehindPlayer
#define SetCameraBehindPlayer sampgdk_SetCameraBehindPlayer
#undef  GetPlayerCameraPos
#define GetPlayerCameraPos sampgdk_GetPlayerCameraPos
#undef  GetPlayerCameraFrontVector
#define GetPlayerCameraFrontVector sampgdk_GetPlayerCameraFrontVector
#undef  GetPlayerCameraMode
#define GetPlayerCameraMode sampgdk_GetPlayerCameraMode
#undef  GetPlayerCameraAspectRatio
#define GetPlayerCameraAspectRatio sampgdk_GetPlayerCameraAspectRatio
#undef  GetPlayerCameraZoom
#define GetPlayerCameraZoom sampgdk_GetPlayerCameraZoom
#undef  AttachCameraToObject
#define AttachCameraToObject sampgdk_AttachCameraToObject
#undef  AttachCameraToPlayerObject
#define AttachCameraToPlayerObject sampgdk_AttachCameraToPlayerObject
#undef  InterpolateCameraPos
#define InterpolateCameraPos sampgdk_InterpolateCameraPos
#undef  InterpolateCameraLookAt
#define InterpolateCameraLookAt sampgdk_InterpolateCameraLookAt
#undef  IsPlayerConnected
#define IsPlayerConnected sampgdk_IsPlayerConnected
#undef  IsPlayerInVehicle
#define IsPlayerInVehicle sampgdk_IsPlayerInVehicle
#undef  IsPlayerInAnyVehicle
#define IsPlayerInAnyVehicle sampgdk_IsPlayerInAnyVehicle
#undef  IsPlayerInCheckpoint
#define IsPlayerInCheckpoint sampgdk_IsPlayerInCheckpoint
#undef  IsPlayerInRaceCheckpoint
#define IsPlayerInRaceCheckpoint sampgdk_IsPlayerInRaceCheckpoint
#undef  SetPlayerVirtualWorld
#define SetPlayerVirtualWorld sampgdk_SetPlayerVirtualWorld
#undef  GetPlayerVirtualWorld
#define GetPlayerVirtualWorld sampgdk_GetPlayerVirtualWorld
#undef  EnableStuntBonusForPlayer
#define EnableStuntBonusForPlayer sampgdk_EnableStuntBonusForPlayer
#undef  EnableStuntBonusForAll
#define EnableStuntBonusForAll sampgdk_EnableStuntBonusForAll
#undef  TogglePlayerSpectating
#define TogglePlayerSpectating sampgdk_TogglePlayerSpectating
#undef  PlayerSpectatePlayer
#define PlayerSpectatePlayer sampgdk_PlayerSpectatePlayer
#undef  PlayerSpectateVehicle
#define PlayerSpectateVehicle sampgdk_PlayerSpectateVehicle
#undef  StartRecordingPlayerData
#define StartRecordingPlayerData sampgdk_StartRecordingPlayerData
#undef  StopRecordingPlayerData
#define StopRecordingPlayerData sampgdk_StopRecordingPlayerData
#undef  CreateExplosionForPlayer
#define CreateExplosionForPlayer sampgdk_CreateExplosionForPlayer
#endif


/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetSpawnInfo">SetSpawnInfo on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SpawnPlayer">SpawnPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SpawnPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerPos">SetPlayerPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerPos(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerPosFindZ">SetPlayerPosFindZ on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerPosFindZ(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerPos">GetPlayerPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerPos(int playerid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerFacingAngle">SetPlayerFacingAngle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerFacingAngle(int playerid, float angle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerFacingAngle">GetPlayerFacingAngle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerFacingAngle(int playerid, float * angle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInRangeOfPoint">IsPlayerInRangeOfPoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerDistanceFromPoint">GetPlayerDistanceFromPoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, GetPlayerDistanceFromPoint(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerStreamedIn">IsPlayerStreamedIn on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerStreamedIn(int playerid, int forplayerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerInterior">SetPlayerInterior on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerInterior(int playerid, int interiorid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerInterior">GetPlayerInterior on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerInterior(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerHealth">SetPlayerHealth on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerHealth(int playerid, float health));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerHealth">GetPlayerHealth on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerHealth(int playerid, float * health));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerArmour">SetPlayerArmour on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerArmour(int playerid, float armour));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerArmour">GetPlayerArmour on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerArmour(int playerid, float * armour));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerAmmo">SetPlayerAmmo on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerAmmo(int playerid, int weaponid, int ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerAmmo">GetPlayerAmmo on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerAmmo(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerWeaponState">GetPlayerWeaponState on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerWeaponState(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerTargetPlayer">GetPlayerTargetPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerTargetPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerTeam">SetPlayerTeam on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerTeam(int playerid, int teamid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerTeam">GetPlayerTeam on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerTeam(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerScore">SetPlayerScore on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerScore(int playerid, int score));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerScore">GetPlayerScore on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerScore(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerDrunkLevel">GetPlayerDrunkLevel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerDrunkLevel(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerDrunkLevel">SetPlayerDrunkLevel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerDrunkLevel(int playerid, int level));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerColor">SetPlayerColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerColor(int playerid, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerColor">GetPlayerColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerColor(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerSkin">SetPlayerSkin on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerSkin(int playerid, int skinid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerSkin">GetPlayerSkin on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerSkin(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GivePlayerWeapon">GivePlayerWeapon on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GivePlayerWeapon(int playerid, int weaponid, int ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ResetPlayerWeapons">ResetPlayerWeapons on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ResetPlayerWeapons(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerArmedWeapon">SetPlayerArmedWeapon on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerArmedWeapon(int playerid, int weaponid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerWeaponData">GetPlayerWeaponData on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerWeaponData(int playerid, int slot, int * weapon, int * ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GivePlayerMoney">GivePlayerMoney on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GivePlayerMoney(int playerid, int money));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ResetPlayerMoney">ResetPlayerMoney on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ResetPlayerMoney(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerName">SetPlayerName on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, SetPlayerName(int playerid, const char * name));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerMoney">GetPlayerMoney on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerMoney(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerState">GetPlayerState on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerState(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerIp">GetPlayerIp on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerIp(int playerid, char * ip, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerPing">GetPlayerPing on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerPing(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerWeapon">GetPlayerWeapon on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerWeapon(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerKeys">GetPlayerKeys on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerKeys(int playerid, int * keys, int * updown, int * leftright));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerName">GetPlayerName on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerName(int playerid, char * name, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerTime">SetPlayerTime on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerTime(int playerid, int hour, int minute));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerTime">GetPlayerTime on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerTime(int playerid, int * hour, int * minute));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TogglePlayerClock">TogglePlayerClock on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TogglePlayerClock(int playerid, bool toggle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerWeather">SetPlayerWeather on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerWeather(int playerid, int weather));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ForceClassSelection">ForceClassSelection on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ForceClassSelection(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerWantedLevel">SetPlayerWantedLevel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerWantedLevel(int playerid, int level));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerWantedLevel">GetPlayerWantedLevel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerWantedLevel(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerFightingStyle">SetPlayerFightingStyle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerFightingStyle(int playerid, int style));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerFightingStyle">GetPlayerFightingStyle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerFightingStyle(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerVelocity">SetPlayerVelocity on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerVelocity(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVelocity">GetPlayerVelocity on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerVelocity(int playerid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayCrimeReportForPlayer">PlayCrimeReportForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayCrimeReportForPlayer(int playerid, int suspectid, int crime));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayAudioStreamForPlayer">PlayAudioStreamForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayAudioStreamForPlayer(int playerid, const char * url, float posX, float posY, float posZ, float distance, bool usepos));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/StopAudioStreamForPlayer">StopAudioStreamForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, StopAudioStreamForPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerShopName">SetPlayerShopName on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerShopName(int playerid, const char * shopname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerSkillLevel">SetPlayerSkillLevel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerSkillLevel(int playerid, int skill, int level));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerSurfingVehicleID">GetPlayerSurfingVehicleID on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerSurfingVehicleID(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerSurfingObjectID">GetPlayerSurfingObjectID on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerSurfingObjectID(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemoveBuildingForPlayer">RemoveBuildingForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerLastShotVectors">GetPlayerLastShotVectors on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerLastShotVectors(int playerid, float * fOriginX, float * fOriginY, float * fOriginZ, float * fHitPosX, float * fHitPosY, float * fHitPosZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerAttachedObject">SetPlayerAttachedObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ, int materialcolor1, int materialcolor2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemovePlayerAttachedObject">RemovePlayerAttachedObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, RemovePlayerAttachedObject(int playerid, int index));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerAttachedObjectSlotUsed">IsPlayerAttachedObjectSlotUsed on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerAttachedObjectSlotUsed(int playerid, int index));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EditAttachedObject">EditAttachedObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EditAttachedObject(int playerid, int index));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreatePlayerTextDraw">CreatePlayerTextDraw on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreatePlayerTextDraw(int playerid, float x, float y, const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawDestroy">PlayerTextDrawDestroy on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawDestroy(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawLetterSize">PlayerTextDrawLetterSize on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawLetterSize(int playerid, int text, float x, float y));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawTextSize">PlayerTextDrawTextSize on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawTextSize(int playerid, int text, float x, float y));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawAlignment">PlayerTextDrawAlignment on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawAlignment(int playerid, int text, int alignment));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawColor">PlayerTextDrawColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawColor(int playerid, int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawUseBox">PlayerTextDrawUseBox on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawUseBox(int playerid, int text, bool use));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawBoxColor">PlayerTextDrawBoxColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawBoxColor(int playerid, int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetShadow">PlayerTextDrawSetShadow on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetShadow(int playerid, int text, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetOutline">PlayerTextDrawSetOutline on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetOutline(int playerid, int text, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawBackgroundColor">PlayerTextDrawBackgroundColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawBackgroundColor(int playerid, int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawFont">PlayerTextDrawFont on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawFont(int playerid, int text, int font));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetProportional">PlayerTextDrawSetProportional on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetProportional(int playerid, int text, bool set));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetSelectable">PlayerTextDrawSetSelectable on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetSelectable(int playerid, int text, bool set));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawShow">PlayerTextDrawShow on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawShow(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawHide">PlayerTextDrawHide on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawHide(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetString">PlayerTextDrawSetString on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetString(int playerid, int text, const char * string));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetPreviewModel">PlayerTextDrawSetPreviewModel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewModel(int playerid, int text, int modelindex));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetPreviewRot">PlayerTextDrawSetPreviewRot on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewRot(int playerid, int text, float fRotX, float fRotY, float fRotZ, float fZoom));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetPreviewVehCol">PlayerTextDrawSetPreviewVehCol on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewVehCol(int playerid, int text, int color1, int color2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPVarInt">SetPVarInt on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPVarInt(int playerid, const char * varname, int value));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarInt">GetPVarInt on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPVarInt(int playerid, const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPVarString">SetPVarString on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPVarString(int playerid, const char * varname, const char * value));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarString">GetPVarString on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPVarString(int playerid, const char * varname, char * value, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPVarFloat">SetPVarFloat on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPVarFloat(int playerid, const char * varname, float value));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarFloat">GetPVarFloat on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, GetPVarFloat(int playerid, const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DeletePVar">DeletePVar on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DeletePVar(int playerid, const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarsUpperIndex">GetPVarsUpperIndex on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPVarsUpperIndex(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarNameAtIndex">GetPVarNameAtIndex on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPVarNameAtIndex(int playerid, int index, char * varname, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarType">GetPVarType on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPVarType(int playerid, const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerChatBubble">SetPlayerChatBubble on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerChatBubble(int playerid, const char * text, int color, float drawdistance, int expiretime));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PutPlayerInVehicle">PutPlayerInVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PutPlayerInVehicle(int playerid, int vehicleid, int seatid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVehicleID">GetPlayerVehicleID on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerVehicleID(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVehicleSeat">GetPlayerVehicleSeat on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerVehicleSeat(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemovePlayerFromVehicle">RemovePlayerFromVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, RemovePlayerFromVehicle(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TogglePlayerControllable">TogglePlayerControllable on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TogglePlayerControllable(int playerid, bool toggle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerPlaySound">PlayerPlaySound on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerPlaySound(int playerid, int soundid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ApplyAnimation">ApplyAnimation on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ApplyAnimation(int playerid, const char * animlib, const char * animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ClearAnimations">ClearAnimations on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ClearAnimations(int playerid, bool forcesync));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerAnimationIndex">GetPlayerAnimationIndex on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerAnimationIndex(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetAnimationName">GetAnimationName on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetAnimationName(int index, char * animlib, int animlib_size, char * animname, int animname_size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerSpecialAction">GetPlayerSpecialAction on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerSpecialAction(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerSpecialAction">SetPlayerSpecialAction on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerSpecialAction(int playerid, int actionid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerCheckpoint">SetPlayerCheckpoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerCheckpoint(int playerid, float x, float y, float z, float size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisablePlayerCheckpoint">DisablePlayerCheckpoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisablePlayerCheckpoint(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerRaceCheckpoint">SetPlayerRaceCheckpoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisablePlayerRaceCheckpoint">DisablePlayerRaceCheckpoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisablePlayerRaceCheckpoint(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerWorldBounds">SetPlayerWorldBounds on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerMarkerForPlayer">SetPlayerMarkerForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowPlayerNameTagForPlayer">ShowPlayerNameTagForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerMapIcon">SetPlayerMapIcon on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemovePlayerMapIcon">RemovePlayerMapIcon on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, RemovePlayerMapIcon(int playerid, int iconid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AllowPlayerTeleport">AllowPlayerTeleport on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AllowPlayerTeleport(int playerid, bool allow));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerCameraPos">SetPlayerCameraPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerCameraPos(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerCameraLookAt">SetPlayerCameraLookAt on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetCameraBehindPlayer">SetCameraBehindPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetCameraBehindPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraPos">GetPlayerCameraPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerCameraPos(int playerid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraFrontVector">GetPlayerCameraFrontVector on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerCameraFrontVector(int playerid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraMode">GetPlayerCameraMode on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerCameraMode(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraAspectRatio">GetPlayerCameraAspectRatio on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, GetPlayerCameraAspectRatio(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraZoom">GetPlayerCameraZoom on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, GetPlayerCameraZoom(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachCameraToObject">AttachCameraToObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AttachCameraToObject(int playerid, int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachCameraToPlayerObject">AttachCameraToPlayerObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AttachCameraToPlayerObject(int playerid, int playerobjectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/InterpolateCameraPos">InterpolateCameraPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/InterpolateCameraLookAt">InterpolateCameraLookAt on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerConnected">IsPlayerConnected on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerConnected(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInVehicle">IsPlayerInVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerInVehicle(int playerid, int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInAnyVehicle">IsPlayerInAnyVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerInAnyVehicle(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInCheckpoint">IsPlayerInCheckpoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerInCheckpoint(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInRaceCheckpoint">IsPlayerInRaceCheckpoint on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerInRaceCheckpoint(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerVirtualWorld">SetPlayerVirtualWorld on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerVirtualWorld(int playerid, int worldid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVirtualWorld">GetPlayerVirtualWorld on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerVirtualWorld(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableStuntBonusForPlayer">EnableStuntBonusForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EnableStuntBonusForPlayer(int playerid, bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableStuntBonusForAll">EnableStuntBonusForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EnableStuntBonusForAll(bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TogglePlayerSpectating">TogglePlayerSpectating on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TogglePlayerSpectating(int playerid, bool toggle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerSpectatePlayer">PlayerSpectatePlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerSpectatePlayer(int playerid, int targetplayerid, int mode));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerSpectateVehicle">PlayerSpectateVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/StartRecordingPlayerData">StartRecordingPlayerData on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, StartRecordingPlayerData(int playerid, int recordtype, const char * recordname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/StopRecordingPlayerData">StopRecordingPlayerData on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, StopRecordingPlayerData(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreateExplosionForPlayer">CreateExplosionForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, CreateExplosionForPlayer(int playerid, float X, float Y, float Z, int type, float Radius));

#define SPECIAL_ACTION_NONE (0)
#define SPECIAL_ACTION_DUCK (1)
#define SPECIAL_ACTION_USEJETPACK (2)
#define SPECIAL_ACTION_ENTER_VEHICLE (3)
#define SPECIAL_ACTION_EXIT_VEHICLE (4)
#define SPECIAL_ACTION_DANCE1 (5)
#define SPECIAL_ACTION_DANCE2 (6)
#define SPECIAL_ACTION_DANCE3 (7)
#define SPECIAL_ACTION_DANCE4 (8)
#define SPECIAL_ACTION_HANDSUP (10)
#define SPECIAL_ACTION_USECELLPHONE (11)
#define SPECIAL_ACTION_SITTING (12)
#define SPECIAL_ACTION_STOPUSECELLPHONE (13)
#define SPECIAL_ACTION_DRINK_BEER (20)
#define SPECIAL_ACTION_SMOKE_CIGGY (21)
#define SPECIAL_ACTION_DRINK_WINE (22)
#define SPECIAL_ACTION_DRINK_SPRUNK (23)
#define SPECIAL_ACTION_CUFFED (24)
#define SPECIAL_ACTION_CARRY (25)
#define FIGHT_STYLE_NORMAL (4)
#define FIGHT_STYLE_BOXING (5)
#define FIGHT_STYLE_KUNGFU (6)
#define FIGHT_STYLE_KNEEHEAD (7)
#define FIGHT_STYLE_GRABKICK (15)
#define FIGHT_STYLE_ELBOW (16)
#define WEAPONSKILL_PISTOL (0)
#define WEAPONSKILL_PISTOL_SILENCED (1)
#define WEAPONSKILL_DESERT_EAGLE (2)
#define WEAPONSKILL_SHOTGUN (3)
#define WEAPONSKILL_SAWNOFF_SHOTGUN (4)
#define WEAPONSKILL_SPAS12_SHOTGUN (5)
#define WEAPONSKILL_MICRO_UZI (6)
#define WEAPONSKILL_MP5 (7)
#define WEAPONSKILL_AK47 (8)
#define WEAPONSKILL_M4 (9)
#define WEAPONSKILL_SNIPERRIFLE (10)
#define WEAPONSTATE_UNKNOWN (-1)
#define WEAPONSTATE_NO_BULLETS (0)
#define WEAPONSTATE_LAST_BULLET (1)
#define WEAPONSTATE_MORE_BULLETS (2)
#define WEAPONSTATE_RELOADING (3)
#define MAX_PLAYER_ATTACHED_OBJECTS (10)
#define PLAYER_VARTYPE_NONE (0)
#define PLAYER_VARTYPE_INT (1)
#define PLAYER_VARTYPE_STRING (2)
#define PLAYER_VARTYPE_FLOAT (3)
#define MAX_CHATBUBBLE_LENGTH (144)
#define MAPICON_LOCAL (0)
#define MAPICON_GLOBAL (1)
#define MAPICON_LOCAL_CHECKPOINT (2)
#define MAPICON_GLOBAL_CHECKPOINT (3)
#define CAMERA_CUT (2)
#define CAMERA_MOVE (1)
#define SPECTATE_MODE_NORMAL (1)
#define SPECTATE_MODE_FIXED (2)
#define SPECTATE_MODE_SIDE (3)
#define PLAYER_RECORDING_TYPE_NONE (0)
#define PLAYER_RECORDING_TYPE_DRIVER (1)
#define PLAYER_RECORDING_TYPE_ONFOOT (2)


/* #include <sampgdk/bool.h> */
/* #include <sampgdk/export.h> */
/* #include <sampgdk/types.h> */

#ifndef DOXYGEN
#undef  CreateObject
#define CreateObject sampgdk_CreateObject
#undef  AttachObjectToVehicle
#define AttachObjectToVehicle sampgdk_AttachObjectToVehicle
#undef  AttachObjectToObject
#define AttachObjectToObject sampgdk_AttachObjectToObject
#undef  AttachObjectToPlayer
#define AttachObjectToPlayer sampgdk_AttachObjectToPlayer
#undef  SetObjectPos
#define SetObjectPos sampgdk_SetObjectPos
#undef  GetObjectPos
#define GetObjectPos sampgdk_GetObjectPos
#undef  SetObjectRot
#define SetObjectRot sampgdk_SetObjectRot
#undef  GetObjectRot
#define GetObjectRot sampgdk_GetObjectRot
#undef  IsValidObject
#define IsValidObject sampgdk_IsValidObject
#undef  DestroyObject
#define DestroyObject sampgdk_DestroyObject
#undef  MoveObject
#define MoveObject sampgdk_MoveObject
#undef  StopObject
#define StopObject sampgdk_StopObject
#undef  IsObjectMoving
#define IsObjectMoving sampgdk_IsObjectMoving
#undef  EditObject
#define EditObject sampgdk_EditObject
#undef  EditPlayerObject
#define EditPlayerObject sampgdk_EditPlayerObject
#undef  SelectObject
#define SelectObject sampgdk_SelectObject
#undef  CancelEdit
#define CancelEdit sampgdk_CancelEdit
#undef  CreatePlayerObject
#define CreatePlayerObject sampgdk_CreatePlayerObject
#undef  AttachPlayerObjectToPlayer
#define AttachPlayerObjectToPlayer sampgdk_AttachPlayerObjectToPlayer
#undef  AttachPlayerObjectToVehicle
#define AttachPlayerObjectToVehicle sampgdk_AttachPlayerObjectToVehicle
#undef  SetPlayerObjectPos
#define SetPlayerObjectPos sampgdk_SetPlayerObjectPos
#undef  GetPlayerObjectPos
#define GetPlayerObjectPos sampgdk_GetPlayerObjectPos
#undef  SetPlayerObjectRot
#define SetPlayerObjectRot sampgdk_SetPlayerObjectRot
#undef  GetPlayerObjectRot
#define GetPlayerObjectRot sampgdk_GetPlayerObjectRot
#undef  IsValidPlayerObject
#define IsValidPlayerObject sampgdk_IsValidPlayerObject
#undef  DestroyPlayerObject
#define DestroyPlayerObject sampgdk_DestroyPlayerObject
#undef  MovePlayerObject
#define MovePlayerObject sampgdk_MovePlayerObject
#undef  StopPlayerObject
#define StopPlayerObject sampgdk_StopPlayerObject
#undef  IsPlayerObjectMoving
#define IsPlayerObjectMoving sampgdk_IsPlayerObjectMoving
#undef  SetObjectMaterial
#define SetObjectMaterial sampgdk_SetObjectMaterial
#undef  SetPlayerObjectMaterial
#define SetPlayerObjectMaterial sampgdk_SetPlayerObjectMaterial
#undef  SetObjectMaterialText
#define SetObjectMaterialText sampgdk_SetObjectMaterialText
#undef  SetPlayerObjectMaterialText
#define SetPlayerObjectMaterialText sampgdk_SetPlayerObjectMaterialText
#endif


/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreateObject">CreateObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachObjectToVehicle">AttachObjectToVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachObjectToObject">AttachObjectToObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AttachObjectToObject(int objectid, int attachtoid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachObjectToPlayer">AttachObjectToPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AttachObjectToPlayer(int objectid, int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetObjectPos">SetObjectPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetObjectPos(int objectid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetObjectPos">GetObjectPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetObjectPos(int objectid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetObjectRot">SetObjectRot on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetObjectRot(int objectid, float rotX, float rotY, float rotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetObjectRot">GetObjectRot on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetObjectRot(int objectid, float * rotX, float * rotY, float * rotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsValidObject">IsValidObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsValidObject(int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DestroyObject">DestroyObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DestroyObject(int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/MoveObject">MoveObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/StopObject">StopObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, StopObject(int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsObjectMoving">IsObjectMoving on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsObjectMoving(int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EditObject">EditObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EditObject(int playerid, int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EditPlayerObject">EditPlayerObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EditPlayerObject(int playerid, int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SelectObject">SelectObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SelectObject(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CancelEdit">CancelEdit on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, CancelEdit(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreatePlayerObject">CreatePlayerObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachPlayerObjectToPlayer">AttachPlayerObjectToPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachPlayerObjectToVehicle">AttachPlayerObjectToVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerObjectPos">SetPlayerObjectPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerObjectPos">GetPlayerObjectPos on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerObjectPos(int playerid, int objectid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerObjectRot">SetPlayerObjectRot on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerObjectRot">GetPlayerObjectRot on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerObjectRot(int playerid, int objectid, float * rotX, float * rotY, float * rotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsValidPlayerObject">IsValidPlayerObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsValidPlayerObject(int playerid, int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DestroyPlayerObject">DestroyPlayerObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DestroyPlayerObject(int playerid, int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/MovePlayerObject">MovePlayerObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX, float RotY, float RotZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/StopPlayerObject">StopPlayerObject on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, StopPlayerObject(int playerid, int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerObjectMoving">IsPlayerObjectMoving on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerObjectMoving(int playerid, int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetObjectMaterial">SetObjectMaterial on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetObjectMaterial(int objectid, int materialindex, int modelid, const char * txdname, const char * texturename, int materialcolor));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerObjectMaterial">SetPlayerObjectMaterial on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerObjectMaterial(int playerid, int objectid, int materialindex, int modelid, const char * txdname, const char * texturename, int materialcolor));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetObjectMaterialText">SetObjectMaterialText on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetObjectMaterialText(int objectid, const char * text, int materialindex, int materialsize, const char * fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerObjectMaterialText">SetPlayerObjectMaterialText on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetPlayerObjectMaterialText(int playerid, int objectid, const char * text, int materialindex, int materialsize, const char * fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment));

#define OBJECT_MATERIAL_SIZE_32x32 (10)
#define OBJECT_MATERIAL_SIZE_64x32 (20)
#define OBJECT_MATERIAL_SIZE_64x64 (30)
#define OBJECT_MATERIAL_SIZE_128x32 (40)
#define OBJECT_MATERIAL_SIZE_128x64 (50)
#define OBJECT_MATERIAL_SIZE_128x128 (60)
#define OBJECT_MATERIAL_SIZE_256x32 (70)
#define OBJECT_MATERIAL_SIZE_256x64 (80)
#define OBJECT_MATERIAL_SIZE_256x128 (90)
#define OBJECT_MATERIAL_SIZE_256x256 (100)
#define OBJECT_MATERIAL_SIZE_512x64 (110)
#define OBJECT_MATERIAL_SIZE_512x128 (120)
#define OBJECT_MATERIAL_SIZE_512x256 (130)
#define OBJECT_MATERIAL_SIZE_512x512 (140)
#define OBJECT_MATERIAL_TEXT_ALIGN_LEFT (0)
#define OBJECT_MATERIAL_TEXT_ALIGN_CENTER (1)
#define OBJECT_MATERIAL_TEXT_ALIGN_RIGHT (2)


/* #include <sampgdk/bool.h> */
/* #include <sampgdk/export.h> */
/* #include <sampgdk/types.h> */

#ifndef DOXYGEN
#undef  HTTP
#define HTTP sampgdk_HTTP
#endif


/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/HTTP">HTTP on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, HTTP(int index, int type, const char * url, const char * data));

#define HTTP_GET (1)
#define HTTP_POST (2)
#define HTTP_HEAD (3)
#define HTTP_ERROR_BAD_HOST (1)
#define HTTP_ERROR_NO_SOCKET (2)
#define HTTP_ERROR_CANT_CONNECT (3)
#define HTTP_ERROR_CANT_WRITE (4)
#define HTTP_ERROR_CONTENT_TOO_BIG (5)
#define HTTP_ERROR_MALFORMED_RESPONSE (6)


/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnHTTPResponse">OnHTTPResponse on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(void, OnHTTPResponse(int index, int response_code, const char * data));

/* #include <sampgdk/bool.h> */
/* #include <sampgdk/export.h> */
/* #include <sampgdk/types.h> */

#ifndef DOXYGEN
#undef  SendClientMessage
#define SendClientMessage sampgdk_SendClientMessage
#undef  SendClientMessageToAll
#define SendClientMessageToAll sampgdk_SendClientMessageToAll
#undef  SendPlayerMessageToPlayer
#define SendPlayerMessageToPlayer sampgdk_SendPlayerMessageToPlayer
#undef  SendPlayerMessageToAll
#define SendPlayerMessageToAll sampgdk_SendPlayerMessageToAll
#undef  SendDeathMessage
#define SendDeathMessage sampgdk_SendDeathMessage
#undef  SendDeathMessageToPlayer
#define SendDeathMessageToPlayer sampgdk_SendDeathMessageToPlayer
#undef  GameTextForAll
#define GameTextForAll sampgdk_GameTextForAll
#undef  GameTextForPlayer
#define GameTextForPlayer sampgdk_GameTextForPlayer
#undef  GetTickCount
#define GetTickCount sampgdk_GetTickCount
#undef  GetMaxPlayers
#define GetMaxPlayers sampgdk_GetMaxPlayers
#undef  VectorSize
#define VectorSize sampgdk_VectorSize
#undef  SetGameModeText
#define SetGameModeText sampgdk_SetGameModeText
#undef  SetTeamCount
#define SetTeamCount sampgdk_SetTeamCount
#undef  AddPlayerClass
#define AddPlayerClass sampgdk_AddPlayerClass
#undef  AddPlayerClassEx
#define AddPlayerClassEx sampgdk_AddPlayerClassEx
#undef  AddStaticVehicle
#define AddStaticVehicle sampgdk_AddStaticVehicle
#undef  AddStaticVehicleEx
#define AddStaticVehicleEx sampgdk_AddStaticVehicleEx
#undef  AddStaticPickup
#define AddStaticPickup sampgdk_AddStaticPickup
#undef  CreatePickup
#define CreatePickup sampgdk_CreatePickup
#undef  DestroyPickup
#define DestroyPickup sampgdk_DestroyPickup
#undef  ShowNameTags
#define ShowNameTags sampgdk_ShowNameTags
#undef  ShowPlayerMarkers
#define ShowPlayerMarkers sampgdk_ShowPlayerMarkers
#undef  GameModeExit
#define GameModeExit sampgdk_GameModeExit
#undef  SetWorldTime
#define SetWorldTime sampgdk_SetWorldTime
#undef  GetWeaponName
#define GetWeaponName sampgdk_GetWeaponName
#undef  EnableTirePopping
#define EnableTirePopping sampgdk_EnableTirePopping
#undef  EnableVehicleFriendlyFire
#define EnableVehicleFriendlyFire sampgdk_EnableVehicleFriendlyFire
#undef  AllowInteriorWeapons
#define AllowInteriorWeapons sampgdk_AllowInteriorWeapons
#undef  SetWeather
#define SetWeather sampgdk_SetWeather
#undef  SetGravity
#define SetGravity sampgdk_SetGravity
#undef  AllowAdminTeleport
#define AllowAdminTeleport sampgdk_AllowAdminTeleport
#undef  SetDeathDropAmount
#define SetDeathDropAmount sampgdk_SetDeathDropAmount
#undef  CreateExplosion
#define CreateExplosion sampgdk_CreateExplosion
#undef  EnableZoneNames
#define EnableZoneNames sampgdk_EnableZoneNames
#undef  UsePlayerPedAnims
#define UsePlayerPedAnims sampgdk_UsePlayerPedAnims
#undef  DisableInteriorEnterExits
#define DisableInteriorEnterExits sampgdk_DisableInteriorEnterExits
#undef  SetNameTagDrawDistance
#define SetNameTagDrawDistance sampgdk_SetNameTagDrawDistance
#undef  DisableNameTagLOS
#define DisableNameTagLOS sampgdk_DisableNameTagLOS
#undef  LimitGlobalChatRadius
#define LimitGlobalChatRadius sampgdk_LimitGlobalChatRadius
#undef  LimitPlayerMarkerRadius
#define LimitPlayerMarkerRadius sampgdk_LimitPlayerMarkerRadius
#undef  ConnectNPC
#define ConnectNPC sampgdk_ConnectNPC
#undef  IsPlayerNPC
#define IsPlayerNPC sampgdk_IsPlayerNPC
#undef  IsPlayerAdmin
#define IsPlayerAdmin sampgdk_IsPlayerAdmin
#undef  Kick
#define Kick sampgdk_Kick
#undef  Ban
#define Ban sampgdk_Ban
#undef  BanEx
#define BanEx sampgdk_BanEx
#undef  SendRconCommand
#define SendRconCommand sampgdk_SendRconCommand
#undef  GetServerVarAsString
#define GetServerVarAsString sampgdk_GetServerVarAsString
#undef  GetServerVarAsInt
#define GetServerVarAsInt sampgdk_GetServerVarAsInt
#undef  GetServerVarAsBool
#define GetServerVarAsBool sampgdk_GetServerVarAsBool
#undef  GetPlayerNetworkStats
#define GetPlayerNetworkStats sampgdk_GetPlayerNetworkStats
#undef  GetNetworkStats
#define GetNetworkStats sampgdk_GetNetworkStats
#undef  GetPlayerVersion
#define GetPlayerVersion sampgdk_GetPlayerVersion
#undef  BlockIpAddress
#define BlockIpAddress sampgdk_BlockIpAddress
#undef  UnBlockIpAddress
#define UnBlockIpAddress sampgdk_UnBlockIpAddress
#undef  GetServerTickRate
#define GetServerTickRate sampgdk_GetServerTickRate
#undef  NetStats_GetConnectedTime
#define NetStats_GetConnectedTime sampgdk_NetStats_GetConnectedTime
#undef  NetStats_MessagesReceived
#define NetStats_MessagesReceived sampgdk_NetStats_MessagesReceived
#undef  NetStats_BytesReceived
#define NetStats_BytesReceived sampgdk_NetStats_BytesReceived
#undef  NetStats_MessagesSent
#define NetStats_MessagesSent sampgdk_NetStats_MessagesSent
#undef  NetStats_BytesSent
#define NetStats_BytesSent sampgdk_NetStats_BytesSent
#undef  NetStats_MessagesRecvPerSecond
#define NetStats_MessagesRecvPerSecond sampgdk_NetStats_MessagesRecvPerSecond
#undef  NetStats_PacketLossPercent
#define NetStats_PacketLossPercent sampgdk_NetStats_PacketLossPercent
#undef  NetStats_ConnectionStatus
#define NetStats_ConnectionStatus sampgdk_NetStats_ConnectionStatus
#undef  NetStats_GetIpPort
#define NetStats_GetIpPort sampgdk_NetStats_GetIpPort
#undef  CreateMenu
#define CreateMenu sampgdk_CreateMenu
#undef  DestroyMenu
#define DestroyMenu sampgdk_DestroyMenu
#undef  AddMenuItem
#define AddMenuItem sampgdk_AddMenuItem
#undef  SetMenuColumnHeader
#define SetMenuColumnHeader sampgdk_SetMenuColumnHeader
#undef  ShowMenuForPlayer
#define ShowMenuForPlayer sampgdk_ShowMenuForPlayer
#undef  HideMenuForPlayer
#define HideMenuForPlayer sampgdk_HideMenuForPlayer
#undef  IsValidMenu
#define IsValidMenu sampgdk_IsValidMenu
#undef  DisableMenu
#define DisableMenu sampgdk_DisableMenu
#undef  DisableMenuRow
#define DisableMenuRow sampgdk_DisableMenuRow
#undef  GetPlayerMenu
#define GetPlayerMenu sampgdk_GetPlayerMenu
#undef  TextDrawCreate
#define TextDrawCreate sampgdk_TextDrawCreate
#undef  TextDrawDestroy
#define TextDrawDestroy sampgdk_TextDrawDestroy
#undef  TextDrawLetterSize
#define TextDrawLetterSize sampgdk_TextDrawLetterSize
#undef  TextDrawTextSize
#define TextDrawTextSize sampgdk_TextDrawTextSize
#undef  TextDrawAlignment
#define TextDrawAlignment sampgdk_TextDrawAlignment
#undef  TextDrawColor
#define TextDrawColor sampgdk_TextDrawColor
#undef  TextDrawUseBox
#define TextDrawUseBox sampgdk_TextDrawUseBox
#undef  TextDrawBoxColor
#define TextDrawBoxColor sampgdk_TextDrawBoxColor
#undef  TextDrawSetShadow
#define TextDrawSetShadow sampgdk_TextDrawSetShadow
#undef  TextDrawSetOutline
#define TextDrawSetOutline sampgdk_TextDrawSetOutline
#undef  TextDrawBackgroundColor
#define TextDrawBackgroundColor sampgdk_TextDrawBackgroundColor
#undef  TextDrawFont
#define TextDrawFont sampgdk_TextDrawFont
#undef  TextDrawSetProportional
#define TextDrawSetProportional sampgdk_TextDrawSetProportional
#undef  TextDrawSetSelectable
#define TextDrawSetSelectable sampgdk_TextDrawSetSelectable
#undef  TextDrawShowForPlayer
#define TextDrawShowForPlayer sampgdk_TextDrawShowForPlayer
#undef  TextDrawHideForPlayer
#define TextDrawHideForPlayer sampgdk_TextDrawHideForPlayer
#undef  TextDrawShowForAll
#define TextDrawShowForAll sampgdk_TextDrawShowForAll
#undef  TextDrawHideForAll
#define TextDrawHideForAll sampgdk_TextDrawHideForAll
#undef  TextDrawSetString
#define TextDrawSetString sampgdk_TextDrawSetString
#undef  TextDrawSetPreviewModel
#define TextDrawSetPreviewModel sampgdk_TextDrawSetPreviewModel
#undef  TextDrawSetPreviewRot
#define TextDrawSetPreviewRot sampgdk_TextDrawSetPreviewRot
#undef  TextDrawSetPreviewVehCol
#define TextDrawSetPreviewVehCol sampgdk_TextDrawSetPreviewVehCol
#undef  SelectTextDraw
#define SelectTextDraw sampgdk_SelectTextDraw
#undef  CancelSelectTextDraw
#define CancelSelectTextDraw sampgdk_CancelSelectTextDraw
#undef  GangZoneCreate
#define GangZoneCreate sampgdk_GangZoneCreate
#undef  GangZoneDestroy
#define GangZoneDestroy sampgdk_GangZoneDestroy
#undef  GangZoneShowForPlayer
#define GangZoneShowForPlayer sampgdk_GangZoneShowForPlayer
#undef  GangZoneShowForAll
#define GangZoneShowForAll sampgdk_GangZoneShowForAll
#undef  GangZoneHideForPlayer
#define GangZoneHideForPlayer sampgdk_GangZoneHideForPlayer
#undef  GangZoneHideForAll
#define GangZoneHideForAll sampgdk_GangZoneHideForAll
#undef  GangZoneFlashForPlayer
#define GangZoneFlashForPlayer sampgdk_GangZoneFlashForPlayer
#undef  GangZoneFlashForAll
#define GangZoneFlashForAll sampgdk_GangZoneFlashForAll
#undef  GangZoneStopFlashForPlayer
#define GangZoneStopFlashForPlayer sampgdk_GangZoneStopFlashForPlayer
#undef  GangZoneStopFlashForAll
#define GangZoneStopFlashForAll sampgdk_GangZoneStopFlashForAll
#undef  Create3DTextLabel
#define Create3DTextLabel sampgdk_Create3DTextLabel
#undef  Delete3DTextLabel
#define Delete3DTextLabel sampgdk_Delete3DTextLabel
#undef  Attach3DTextLabelToPlayer
#define Attach3DTextLabelToPlayer sampgdk_Attach3DTextLabelToPlayer
#undef  Attach3DTextLabelToVehicle
#define Attach3DTextLabelToVehicle sampgdk_Attach3DTextLabelToVehicle
#undef  Update3DTextLabelText
#define Update3DTextLabelText sampgdk_Update3DTextLabelText
#undef  CreatePlayer3DTextLabel
#define CreatePlayer3DTextLabel sampgdk_CreatePlayer3DTextLabel
#undef  DeletePlayer3DTextLabel
#define DeletePlayer3DTextLabel sampgdk_DeletePlayer3DTextLabel
#undef  UpdatePlayer3DTextLabelText
#define UpdatePlayer3DTextLabelText sampgdk_UpdatePlayer3DTextLabelText
#undef  ShowPlayerDialog
#define ShowPlayerDialog sampgdk_ShowPlayerDialog
#undef  SetTimer
#define SetTimer sampgdk_SetTimer
#undef  KillTimer
#define KillTimer sampgdk_KillTimer
#undef  gpci
#define gpci sampgdk_gpci
#endif


/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendClientMessage">SendClientMessage on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendClientMessage(int playerid, int color, const char * message));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendClientMessageToAll">SendClientMessageToAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendClientMessageToAll(int color, const char * message));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendPlayerMessageToPlayer">SendPlayerMessageToPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendPlayerMessageToPlayer(int playerid, int senderid, const char * message));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendPlayerMessageToAll">SendPlayerMessageToAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendPlayerMessageToAll(int senderid, const char * message));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendDeathMessage">SendDeathMessage on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendDeathMessage(int killer, int killee, int weapon));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendDeathMessageToPlayer">SendDeathMessageToPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendDeathMessageToPlayer(int playerid, int killer, int killee, int weapon));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GameTextForAll">GameTextForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GameTextForAll(const char * text, int time, int style));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GameTextForPlayer">GameTextForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GameTextForPlayer(int playerid, const char * text, int time, int style));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetTickCount">GetTickCount on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetTickCount());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetMaxPlayers">GetMaxPlayers on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetMaxPlayers());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/VectorSize">VectorSize on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, VectorSize(float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetGameModeText">SetGameModeText on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetGameModeText(const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetTeamCount">SetTeamCount on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetTeamCount(int count));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddPlayerClass">AddPlayerClass on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddPlayerClassEx">AddPlayerClassEx on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddStaticVehicle">AddStaticVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddStaticVehicleEx">AddStaticVehicleEx on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddStaticPickup">AddStaticPickup on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddStaticPickup(int model, int type, float x, float y, float z, int virtualworld));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreatePickup">CreatePickup on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreatePickup(int model, int type, float x, float y, float z, int virtualworld));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DestroyPickup">DestroyPickup on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DestroyPickup(int pickup));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowNameTags">ShowNameTags on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowNameTags(bool show));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowPlayerMarkers">ShowPlayerMarkers on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowPlayerMarkers(int mode));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GameModeExit">GameModeExit on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GameModeExit());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetWorldTime">SetWorldTime on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetWorldTime(int hour));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetWeaponName">GetWeaponName on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetWeaponName(int weaponid, char * name, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableTirePopping">EnableTirePopping on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EnableTirePopping(bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableVehicleFriendlyFire">EnableVehicleFriendlyFire on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EnableVehicleFriendlyFire());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AllowInteriorWeapons">AllowInteriorWeapons on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AllowInteriorWeapons(bool allow));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetWeather">SetWeather on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetWeather(int weatherid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetGravity">SetGravity on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetGravity(float gravity));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AllowAdminTeleport">AllowAdminTeleport on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, AllowAdminTeleport(bool allow));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetDeathDropAmount">SetDeathDropAmount on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetDeathDropAmount(int amount));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreateExplosion">CreateExplosion on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, CreateExplosion(float x, float y, float z, int type, float radius));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableZoneNames">EnableZoneNames on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, EnableZoneNames(bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/UsePlayerPedAnims">UsePlayerPedAnims on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, UsePlayerPedAnims());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableInteriorEnterExits">DisableInteriorEnterExits on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisableInteriorEnterExits());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetNameTagDrawDistance">SetNameTagDrawDistance on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetNameTagDrawDistance(float distance));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableNameTagLOS">DisableNameTagLOS on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisableNameTagLOS());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/LimitGlobalChatRadius">LimitGlobalChatRadius on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, LimitGlobalChatRadius(float chat_radius));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/LimitPlayerMarkerRadius">LimitPlayerMarkerRadius on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, LimitPlayerMarkerRadius(float marker_radius));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ConnectNPC">ConnectNPC on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ConnectNPC(const char * name, const char * script));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerNPC">IsPlayerNPC on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerNPC(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerAdmin">IsPlayerAdmin on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsPlayerAdmin(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Kick">Kick on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Kick(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Ban">Ban on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Ban(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/BanEx">BanEx on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, BanEx(int playerid, const char * reason));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SendRconCommand">SendRconCommand on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SendRconCommand(const char * command));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetServerVarAsString">GetServerVarAsString on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetServerVarAsString(const char * varname, char * value, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetServerVarAsInt">GetServerVarAsInt on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetServerVarAsInt(const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetServerVarAsBool">GetServerVarAsBool on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetServerVarAsBool(const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerNetworkStats">GetPlayerNetworkStats on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerNetworkStats(int playerid, char * retstr, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetNetworkStats">GetNetworkStats on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetNetworkStats(char * retstr, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVersion">GetPlayerVersion on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GetPlayerVersion(int playerid, char * version, int len));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/BlockIpAddress">BlockIpAddress on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, BlockIpAddress(const char * ip_address, int timems));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/UnBlockIpAddress">UnBlockIpAddress on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, UnBlockIpAddress(const char * ip_address));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetServerTickRate">GetServerTickRate on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetServerTickRate());

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_GetConnectedTime">NetStats_GetConnectedTime on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_GetConnectedTime(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_MessagesReceived">NetStats_MessagesReceived on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_MessagesReceived(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_BytesReceived">NetStats_BytesReceived on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_BytesReceived(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_MessagesSent">NetStats_MessagesSent on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_MessagesSent(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_BytesSent">NetStats_BytesSent on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_BytesSent(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_MessagesRecvPerSecond">NetStats_MessagesRecvPerSecond on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_MessagesRecvPerSecond(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_PacketLossPercent">NetStats_PacketLossPercent on SA-MP Wiki</a> */
SAMPGDK_NATIVE(float, NetStats_PacketLossPercent(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_ConnectionStatus">NetStats_ConnectionStatus on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, NetStats_ConnectionStatus(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/NetStats_GetIpPort">NetStats_GetIpPort on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, NetStats_GetIpPort(int playerid, char * ip_port, int ip_port_len));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreateMenu">CreateMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreateMenu(const char * title, int columns, float x, float y, float col1width, float col2width));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DestroyMenu">DestroyMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DestroyMenu(int menuid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AddMenuItem">AddMenuItem on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, AddMenuItem(int menuid, int column, const char * menutext));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetMenuColumnHeader">SetMenuColumnHeader on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SetMenuColumnHeader(int menuid, int column, const char * columnheader));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowMenuForPlayer">ShowMenuForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowMenuForPlayer(int menuid, int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/HideMenuForPlayer">HideMenuForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, HideMenuForPlayer(int menuid, int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsValidMenu">IsValidMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, IsValidMenu(int menuid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableMenu">DisableMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisableMenu(int menuid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableMenuRow">DisableMenuRow on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DisableMenuRow(int menuid, int row));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerMenu">GetPlayerMenu on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GetPlayerMenu(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawCreate">TextDrawCreate on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, TextDrawCreate(float x, float y, const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawDestroy">TextDrawDestroy on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawDestroy(int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawLetterSize">TextDrawLetterSize on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawLetterSize(int text, float x, float y));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawTextSize">TextDrawTextSize on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawTextSize(int text, float x, float y));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawAlignment">TextDrawAlignment on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawAlignment(int text, int alignment));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawColor">TextDrawColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawColor(int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawUseBox">TextDrawUseBox on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawUseBox(int text, bool use));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawBoxColor">TextDrawBoxColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawBoxColor(int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetShadow">TextDrawSetShadow on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetShadow(int text, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetOutline">TextDrawSetOutline on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetOutline(int text, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawBackgroundColor">TextDrawBackgroundColor on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawBackgroundColor(int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawFont">TextDrawFont on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawFont(int text, int font));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetProportional">TextDrawSetProportional on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetProportional(int text, bool set));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetSelectable">TextDrawSetSelectable on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetSelectable(int text, bool set));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawShowForPlayer">TextDrawShowForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawShowForPlayer(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawHideForPlayer">TextDrawHideForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawHideForPlayer(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawShowForAll">TextDrawShowForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawShowForAll(int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawHideForAll">TextDrawHideForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawHideForAll(int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetString">TextDrawSetString on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetString(int text, const char * string));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetPreviewModel">TextDrawSetPreviewModel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetPreviewModel(int text, int modelindex));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetPreviewRot">TextDrawSetPreviewRot on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetPreviewRot(int text, float fRotX, float fRotY, float fRotZ, float fZoom));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TextDrawSetPreviewVehCol">TextDrawSetPreviewVehCol on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, TextDrawSetPreviewVehCol(int text, int color1, int color2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SelectTextDraw">SelectTextDraw on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, SelectTextDraw(int playerid, int hovercolor));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CancelSelectTextDraw">CancelSelectTextDraw on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, CancelSelectTextDraw(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneCreate">GangZoneCreate on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, GangZoneCreate(float minx, float miny, float maxx, float maxy));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneDestroy">GangZoneDestroy on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneDestroy(int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneShowForPlayer">GangZoneShowForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneShowForPlayer(int playerid, int zone, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneShowForAll">GangZoneShowForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneShowForAll(int zone, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneHideForPlayer">GangZoneHideForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneHideForPlayer(int playerid, int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneHideForAll">GangZoneHideForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneHideForAll(int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneFlashForPlayer">GangZoneFlashForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneFlashForPlayer(int playerid, int zone, int flashcolor));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneFlashForAll">GangZoneFlashForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneFlashForAll(int zone, int flashcolor));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneStopFlashForPlayer">GangZoneStopFlashForPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneStopFlashForPlayer(int playerid, int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GangZoneStopFlashForAll">GangZoneStopFlashForAll on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, GangZoneStopFlashForAll(int zone));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Create3DTextLabel">Create3DTextLabel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, Create3DTextLabel(const char * text, int color, float x, float y, float z, float DrawDistance, int virtualworld, bool testLOS));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Delete3DTextLabel">Delete3DTextLabel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Delete3DTextLabel(int id));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Attach3DTextLabelToPlayer">Attach3DTextLabelToPlayer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Attach3DTextLabelToVehicle">Attach3DTextLabelToVehicle on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/Update3DTextLabelText">Update3DTextLabelText on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, Update3DTextLabelText(int id, int color, const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreatePlayer3DTextLabel">CreatePlayer3DTextLabel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, CreatePlayer3DTextLabel(int playerid, const char * text, int color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DeletePlayer3DTextLabel">DeletePlayer3DTextLabel on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, DeletePlayer3DTextLabel(int playerid, int id));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/UpdatePlayer3DTextLabelText">UpdatePlayer3DTextLabelText on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, UpdatePlayer3DTextLabelText(int playerid, int id, int color, const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowPlayerDialog">ShowPlayerDialog on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, ShowPlayerDialog(int playerid, int dialogid, int style, const char * caption, const char * info, const char * button1, const char * button2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetTimer">SetTimer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(int, SetTimer(int interval, bool repeat, TimerCallback callback, void * param));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/KillTimer">KillTimer on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, KillTimer(int timerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/gpci">gpci on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, gpci(int playerid, char * buffer, int size));

#define MAX_PLAYER_NAME (24)
#define MAX_CLIENT_MESSAGE (144)
#define MAX_PLAYERS (500)
#define MAX_VEHICLES (2000)
#define INVALID_PLAYER_ID (0xFFFF)
#define INVALID_VEHICLE_ID (0xFFFF)
#define NO_TEAM (255)
#define MAX_OBJECTS (1000)
#define INVALID_OBJECT_ID (0xFFFF)
#define MAX_GANG_ZONES (1024)
#define MAX_TEXT_DRAWS (2048)
#define MAX_PLAYER_TEXT_DRAWS (256)
#define MAX_MENUS (128)
#define MAX_3DTEXT_GLOBAL (1024)
#define MAX_3DTEXT_PLAYER (1024)
#define MAX_PICKUPS (4096)
#define INVALID_MENU (0xFF)
#define INVALID_TEXT_DRAW (0xFFFF)
#define INVALID_GANG_ZONE (-1)
#define INVALID_3DTEXT_ID (0xFFFF)
#define TEXT_DRAW_FONT_SPRITE_DRAW (4)
#define TEXT_DRAW_FONT_MODEL_PREVIEW (5)
#define DIALOG_STYLE_MSGBOX (0)
#define DIALOG_STYLE_INPUT (1)
#define DIALOG_STYLE_LIST (2)
#define DIALOG_STYLE_PASSWORD (3)
#define PLAYER_STATE_NONE (0)
#define PLAYER_STATE_ONFOOT (1)
#define PLAYER_STATE_DRIVER (2)
#define PLAYER_STATE_PASSENGER (3)
#define PLAYER_STATE_EXIT_VEHICLE (4)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER (5)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER (6)
#define PLAYER_STATE_WASTED (7)
#define PLAYER_STATE_SPAWNED (8)
#define PLAYER_STATE_SPECTATING (9)
#define PLAYER_MARKERS_MODE_OFF (0)
#define PLAYER_MARKERS_MODE_GLOBAL (1)
#define PLAYER_MARKERS_MODE_STREAMED (2)
#define WEAPON_BRASSKNUCKLE (1)
#define WEAPON_GOLFCLUB (2)
#define WEAPON_NITESTICK (3)
#define WEAPON_KNIFE (4)
#define WEAPON_BAT (5)
#define WEAPON_SHOVEL (6)
#define WEAPON_POOLSTICK (7)
#define WEAPON_KATANA (8)
#define WEAPON_CHAINSAW (9)
#define WEAPON_DILDO (10)
#define WEAPON_DILDO2 (11)
#define WEAPON_VIBRATOR (12)
#define WEAPON_VIBRATOR2 (13)
#define WEAPON_FLOWER (14)
#define WEAPON_CANE (15)
#define WEAPON_GRENADE (16)
#define WEAPON_TEARGAS (17)
#define WEAPON_MOLTOV (18)
#define WEAPON_COLT45 (22)
#define WEAPON_SILENCED (23)
#define WEAPON_DEAGLE (24)
#define WEAPON_SHOTGUN (25)
#define WEAPON_SAWEDOFF (26)
#define WEAPON_SHOTGSPA (27)
#define WEAPON_UZI (28)
#define WEAPON_MP5 (29)
#define WEAPON_AK47 (30)
#define WEAPON_M4 (31)
#define WEAPON_TEC9 (32)
#define WEAPON_RIFLE (33)
#define WEAPON_SNIPER (34)
#define WEAPON_ROCKETLAUNCHER (35)
#define WEAPON_HEATSEEKER (36)
#define WEAPON_FLAMETHROWER (37)
#define WEAPON_MINIGUN (38)
#define WEAPON_SATCHEL (39)
#define WEAPON_BOMB (40)
#define WEAPON_SPRAYCAN (41)
#define WEAPON_FIREEXTINGUISHER (42)
#define WEAPON_CAMERA (43)
#define WEAPON_PARACHUTE (46)
#define WEAPON_VEHICLE (49)
#define WEAPON_DROWN (53)
#define WEAPON_COLLISION (54)
#define KEY_ACTION (1)
#define KEY_CROUCH (2)
#define KEY_FIRE (4)
#define KEY_SPRINT (8)
#define KEY_SECONDARY_ATTACK (16)
#define KEY_JUMP (32)
#define KEY_LOOK_RIGHT (64)
#define KEY_HANDBRAKE (128)
#define KEY_LOOK_LEFT (256)
#define KEY_SUBMISSION (512)
#define KEY_LOOK_BEHIND (512)
#define KEY_WALK (1024)
#define KEY_ANALOG_UP (2048)
#define KEY_ANALOG_DOWN (4096)
#define KEY_ANALOG_LEFT (8192)
#define KEY_ANALOG_RIGHT (16384)
#define KEY_YES (65536)
#define KEY_NO (131072)
#define KEY_CTRL_BACK (262144)
#define KEY_UP (-128)
#define KEY_DOWN (128)
#define KEY_LEFT (-128)
#define KEY_RIGHT (128)
#define CLICK_SOURCE_SCOREBOARD (0)
#define EDIT_RESPONSE_CANCEL (0)
#define EDIT_RESPONSE_FINAL (1)
#define EDIT_RESPONSE_UPDATE (2)
#define SELECT_OBJECT_GLOBAL_OBJECT (1)
#define SELECT_OBJECT_PLAYER_OBJECT (2)
#define BULLET_HIT_TYPE_NONE (0)
#define BULLET_HIT_TYPE_PLAYER (1)
#define BULLET_HIT_TYPE_VEHICLE (2)
#define BULLET_HIT_TYPE_OBJECT (3)
#define BULLET_HIT_TYPE_PLAYER_OBJECT (4)


/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnGameModeInit">OnGameModeInit on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnGameModeInit());

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnGameModeExit">OnGameModeExit on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnGameModeExit());

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerConnect">OnPlayerConnect on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerConnect(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerDisconnect">OnPlayerDisconnect on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerDisconnect(int playerid, int reason));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerSpawn">OnPlayerSpawn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerSpawn(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerDeath">OnPlayerDeath on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerDeath(int playerid, int killerid, int reason));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleSpawn">OnVehicleSpawn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleSpawn(int vehicleid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleDeath">OnVehicleDeath on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleDeath(int vehicleid, int killerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerText">OnPlayerText on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerText(int playerid, const char * text));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerCommandText">OnPlayerCommandText on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerCommandText(int playerid, const char * cmdtext));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerRequestClass">OnPlayerRequestClass on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerRequestClass(int playerid, int classid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEnterVehicle">OnPlayerEnterVehicle on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerExitVehicle">OnPlayerExitVehicle on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerExitVehicle(int playerid, int vehicleid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerStateChange">OnPlayerStateChange on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerStateChange(int playerid, int newstate, int oldstate));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEnterCheckpoint">OnPlayerEnterCheckpoint on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEnterCheckpoint(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerLeaveCheckpoint">OnPlayerLeaveCheckpoint on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerLeaveCheckpoint(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEnterRaceCheckpoint">OnPlayerEnterRaceCheckpoint on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEnterRaceCheckpoint(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerLeaveRaceCheckpoint">OnPlayerLeaveRaceCheckpoint on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerLeaveRaceCheckpoint(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnRconCommand">OnRconCommand on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnRconCommand(const char * cmd));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerRequestSpawn">OnPlayerRequestSpawn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerRequestSpawn(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnObjectMoved">OnObjectMoved on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnObjectMoved(int objectid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerObjectMoved">OnPlayerObjectMoved on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerObjectMoved(int playerid, int objectid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerPickUpPickup">OnPlayerPickUpPickup on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerPickUpPickup(int playerid, int pickupid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleMod">OnVehicleMod on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleMod(int playerid, int vehicleid, int componentid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnEnterExitModShop">OnEnterExitModShop on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnEnterExitModShop(int playerid, int enterexit, int interiorid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehiclePaintjob">OnVehiclePaintjob on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleRespray">OnVehicleRespray on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleRespray(int playerid, int vehicleid, int color1, int color2));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleDamageStatusUpdate">OnVehicleDamageStatusUpdate on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleDamageStatusUpdate(int vehicleid, int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnUnoccupiedVehicleUpdate">OnUnoccupiedVehicleUpdate on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerSelectedMenuRow">OnPlayerSelectedMenuRow on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerSelectedMenuRow(int playerid, int row));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerExitedMenu">OnPlayerExitedMenu on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerExitedMenu(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerInteriorChange">OnPlayerInteriorChange on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerKeyStateChange">OnPlayerKeyStateChange on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnRconLoginAttempt">OnRconLoginAttempt on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnRconLoginAttempt(const char * ip, const char * password, bool success));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerUpdate">OnPlayerUpdate on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerUpdate(int playerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerStreamIn">OnPlayerStreamIn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerStreamIn(int playerid, int forplayerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerStreamOut">OnPlayerStreamOut on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerStreamOut(int playerid, int forplayerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleStreamIn">OnVehicleStreamIn on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleStreamIn(int vehicleid, int forplayerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnVehicleStreamOut">OnVehicleStreamOut on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnVehicleStreamOut(int vehicleid, int forplayerid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnDialogResponse">OnDialogResponse on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerTakeDamage">OnPlayerTakeDamage on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerGiveDamage">OnPlayerGiveDamage on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerClickMap">OnPlayerClickMap on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerClickMap(int playerid, float fX, float fY, float fZ));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerClickTextDraw">OnPlayerClickTextDraw on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerClickTextDraw(int playerid, int clickedid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerClickPlayerTextDraw">OnPlayerClickPlayerTextDraw on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerClickPlayerTextDraw(int playerid, int playertextid));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnIncomingConnection">OnIncomingConnection on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnIncomingConnection(int playerid, const char * ip_address, int port));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerClickPlayer">OnPlayerClickPlayer on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerClickPlayer(int playerid, int clickedplayerid, int source));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEditObject">OnPlayerEditObject on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerEditAttachedObject">OnPlayerEditAttachedObject on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerSelectObject">OnPlayerSelectObject on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ));

/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnPlayerWeaponShot">OnPlayerWeaponShot on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(bool, OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ));

