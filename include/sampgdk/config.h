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

#ifndef SAMPGDK_CONFIG_H
#define SAMPGDK_CONFIG_H
#pragma once

/* Make sure architecture is x86 */
#if !(defined _M_IX86 || defined __i386__)
	#error Unsupported architecture
#endif

/* Windows */
#if defined WIN32 || defined _WIN32 || defined __WIN32__
	#define SAMPGDK_WINDOWS 1
#endif

/* Linux */
#if defined __linux__ || defined __linux || defined linux
	#if !defined LINUX
		#define LINUX
	#endif
	#define SAMPGDK_LINUX 1
#endif

/* stdint.h */
#if !defined HAVE_STDINT_H
	#if (!defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L /* C99 or newer */)\
		|| (defined _MSC_VER && _MSC_VER >= 1600 /* Visual Studio 2010 and later */)\
		|| defined __GNUC__ /* GCC, MinGW, etc */
		#define HAVE_STDINT_H 1
	#endif
#endif

#define SAMPGDK_STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(COND)?1:-1]

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
	/* Make sure their "bool" is one byte in size. */
	SAMPGDK_STATIC_ASSERT(sizeof(bool) == 1, size_of_bool_must_be_1_byte);
#endif

/* Ensure "int", "float" and "void*" are all of the same size as "cell". */
SAMPGDK_STATIC_ASSERT(sizeof(int) == 4, sizeof_int_must_be_4);
SAMPGDK_STATIC_ASSERT(sizeof(float) == 4, sizeof_float_must_be_4);
SAMPGDK_STATIC_ASSERT(sizeof(void*) == 4, sizeof_void_ptr_must_be_4);

#endif /* !SAMPGDK_CONFIG_H */
