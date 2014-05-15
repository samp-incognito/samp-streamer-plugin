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

#include <sampgdk/bool.h>
#include <sampgdk/export.h>

/**
 * \addtogroup interop
 * @{
 */

/**
 * \brief Returns all currently registered native functions.
 *
 * This function can be used to retrieve the names and addresses of all native
 * functions that were registered with amx_Register() by the server and plugins
 * loaded prior to the call. The \p number parameter is filled with the total
 * number of functions.
 *
 * \param number The number of elements in the returned array.
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
 * \note The first element of \p params should contain the number of arguments
 * multiplied by \c sizeof(cell). If the function takes no arguments, \p params
 * may be \c NULL.
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
 * r         | const cell *  | const reference (input-only)
 * R         | cell *        | non-const reference (input and output)
 * s         | const char *  | const string (input-only)
 * S         | char *        | non-const string (input and output)
 *
 * \note For the 'S' specifier, the argument passed next to it specifies
 * the size of the string buffer. Fortunately all current SA-MP natives
 * follow this convention.
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
 */
SAMPGDK_API(cell, sampgdk_InvokeNativeV(AMX_NATIVE native,
                                        const char *format, va_list args));

/**
 * \brief Gets called on every public function call.
 *
 * This is the public filter callback. It is called whenever the server
 * calls \c amx_Exec(), which practiacally means that you can use it to
 * hook *any* callback, even those that are called by other plugins.
 *
 * \param amx The AMX instance on which the public function is called.
 * \param name The name of the function.
 * \param params The function's arguments as stored on the AMX stack, with the
 * \c params[0] equal to the number of arguments multiplied by \c sizeof(cell).
 *
 * \returns If returns \c true the callback is executed, otherwise it's ignored.
 */
SAMPGDK_CALLBACK(bool, OnPublicCall(AMX *amx, const char *name, cell *params));

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
inline cell InvokeNative(AMX_NATIVE native, const char *format, va_list args) {
  return sampgdk_InvokeNativeV(native, format, args);
}

/** @} */

} // namespace sampgdk

#endif /* __cplusplus */

#endif /* !SAMPGDK_INTEROP_H */
