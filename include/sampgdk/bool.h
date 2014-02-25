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
