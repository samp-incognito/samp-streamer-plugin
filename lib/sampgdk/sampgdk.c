#define IN_SAMPGDK

#include "sampgdk.h"

#if SAMPGDK_WINDOWS
  #ifdef _MSC_VER
    #pragma warning(disable: 4996)
  #endif
  #undef CreateMenu
  #undef DestroyMenu
  #undef GetTickCount
  #undef KillTimer
  #undef SelectObject
  #undef SetTimer
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#endif

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_ARRAY_H
#define SAMPGDK_INTERNAL_ARRAY_H

struct sampgdk_array {
  void *data;
  int   count;
  int   size;
  int   elem_size;
};

/* Element compaison function. */
typedef int (*sampgdk_array_cmp)(const void *x, const void *y);

int sampgdk_array_new(struct sampgdk_array *a, int size, int elem_size);
void sampgdk_array_free(struct sampgdk_array *a);

/* Fills the aray with zeros. */
int sampgdk_array_zero(struct sampgdk_array *a);

int sampgdk_array_resize(struct sampgdk_array *a, int new_size);
int sampgdk_array_grow(struct sampgdk_array *a);
int sampgdk_array_shrink(struct sampgdk_array *a);
int sampgdk_array_pad(struct sampgdk_array *a);

void *sampgdk_array_get(struct sampgdk_array *a, int index);
void sampgdk_array_set(struct sampgdk_array *a,int index, void *elem);

/* Returns the index of the element pointed to by elem. */
int sampgdk_array_get_index(struct sampgdk_array *a, void *elem);

int sampgdk_array_insert(struct sampgdk_array *a, int index,
    int count, void *elems);
int sampgdk_array_append(struct sampgdk_array *a, void *elem);

int sampgdk_array_remove(struct sampgdk_array *a, int index, int count);
int sampgdk_array_clear(struct sampgdk_array *a);

int sampgdk_array_find(struct sampgdk_array *a, const void *key,
    sampgdk_array_cmp cmp);
int sampgdk_array_find_remove(struct sampgdk_array *a, const void *key,
    sampgdk_array_cmp cmp);

#endif /* !SAMPGDK_INTERNAL_ARRAY_H */

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_HOOK_H
#define SAMPGDK_INTERNAL_HOOK_H

struct _sampgdk_hook;
typedef struct _sampgdk_hook *sampgdk_hook_t;

sampgdk_hook_t sampgdk_hook_new(void *src, void *dst);
void sampgdk_hook_free(sampgdk_hook_t hook);
void *sampgdk_hook_trampoline(sampgdk_hook_t hook);

#define SAMPGDK_HOOK_CALL(hook, return_type, args) \
  ((return_type (*)())sampgdk_hook_code(hook))args

#define SAMPGDK_HOOK_CALL_CC(hook, return_type, callconv, args) \
  ((return_type (callconv *)())sampgdk_hook_trampoline(hook))args

#endif /* !SAMPGDK_INTERNAL_HOOK_H */

/* Copyright (C) 2013-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_INIT_H
#define SAMPGDK_INTERNAL_INIT_H

#define SAMPGDK_MODULE_INIT(module) \
  int sampgdk_##module##_init(void)

#define SAMPGDK_MODULE_CLEANUP(module) \
  void sampgdk_##module##_cleanup(void)

int  sampgdk_module_init(void);
void sampgdk_module_cleanup(void);

#endif /* !SAMPGDK_INTERNAL_INIT_H */

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_LIKELY_H
#define SAMPGDK_INTERNAL_LIKELY_H

#if defined __GNUC__
  #define SAMPGDK_LIKELY(x)   __builtin_expect((x), 1)
  #define SAMPGDK_UNLIKELY(x) __builtin_expect((x), 0)
#else
  #define SAMPGDK_LIKELY(x)   (x)
  #define SAMPGDK_UNLIKELY(x) (x)
#endif

#endif /* !SAMPGDK_INTERNAL_LIKELY_H */

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_LOG_H
#define SAMPGDK_INTERNAL_LOG_H

void sampgdk_log_debug(const char *format, ...);
void sampgdk_log_info(const char *format, ...);
void sampgdk_log_warning(const char *format, ...);
void sampgdk_log_error(const char *format, ...);

#endif /* !SAMPGDK_INTERNAL_LOG_H */

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_LOGPRINTF_H
#define SAMPGDK_INTERNAL_LOGPRINTF_H

#include <stdarg.h>

extern void *sampgdk_logprintf_impl;

void sampgdk_do_vlogprintf(const char *format, va_list va);

#endif /* !SAMPGDK_INTERNAL_LOGPRINTF_H */

/* Copyright (C) 2014-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_TYPES_H
#define SAMPGDK_INTERNAL_TYPES_H

#if defined _MSC_VER && _MSC_VER <= 1600
  typedef __int8 int8_t;
  typedef unsigned __int8 uint8_t;
  typedef __int16 int16_t;
  typedef unsigned __int16 uint16_t;
  typedef __int32 int32_t;
  typedef unsigned __int32 uint32_t;
#else
  #include <stdint.h>
#endif

#if SAMPGDK_WINDOWS
  #ifndef PRId32
    #define PRId32 "I32d"
  #endif
  #ifndef PRId64
    #define PRId64 "I64d"
  #endif
#else
  #include <inttypes.h>
#endif

#endif /* !SAMPGDK_INTERNAL_TYPES_H */

int sampgdk_amxhooks_init(void);
int sampgdk_callback_init(void);
int sampgdk_fakeamx_init(void);
int sampgdk_log_init(void);
int sampgdk_native_init(void);
int sampgdk_plugin_init(void);
int sampgdk_timer_init(void);
int sampgdk_a_http_init(void);
int sampgdk_a_objects_init(void);
int sampgdk_a_players_init(void);
int sampgdk_a_samp_init(void);

int sampgdk_module_init(void) {
  int error;
  if ((error = sampgdk_amxhooks_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_fakeamx_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_log_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_native_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_plugin_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_timer_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_a_http_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_a_objects_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_a_players_init()) < 0) {
    return error;
  }
  if ((error = sampgdk_a_samp_init()) < 0) {
    return error;
  }
  return 0;
}

void sampgdk_a_samp_cleanup(void);
void sampgdk_a_players_cleanup(void);
void sampgdk_a_objects_cleanup(void);
void sampgdk_a_http_cleanup(void);
void sampgdk_timer_cleanup(void);
void sampgdk_plugin_cleanup(void);
void sampgdk_native_cleanup(void);
void sampgdk_log_cleanup(void);
void sampgdk_fakeamx_cleanup(void);
void sampgdk_callback_cleanup(void);
void sampgdk_amxhooks_cleanup(void);

void sampgdk_module_cleanup(void) {
  sampgdk_a_samp_cleanup();
  sampgdk_a_players_cleanup();
  sampgdk_a_objects_cleanup();
  sampgdk_a_http_cleanup();
  sampgdk_timer_cleanup();
  sampgdk_plugin_cleanup();
  sampgdk_native_cleanup();
  sampgdk_log_cleanup();
  sampgdk_fakeamx_cleanup();
  sampgdk_callback_cleanup();
  sampgdk_amxhooks_cleanup();
}


/* Copyright (C) 2012-2015 Zeex
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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* #include "array.h" */

static void *_sampgdk_array_get_elem_ptr(struct sampgdk_array *a,
                                         int index) {
  return (unsigned char *)a->data + (index * a->elem_size);
}

static int _sampgdk_array_normalize_index(struct sampgdk_array *a,
                                          int index) {
  if (index >= 0) {
    return index;
  } else {
    return a->count + index;
  }
}

int sampgdk_array_new(struct sampgdk_array *a,
                      int size,
                      int elem_size) {
  assert(a != NULL);
  assert(size > 0);
  assert(elem_size > 0);

  if ((a->data = malloc(elem_size * size)) == NULL) {
    return -ENOMEM;
  }

  a->size = size;
  a->elem_size = elem_size;
  a->count = 0;

  return 0;
}

void sampgdk_array_free(struct sampgdk_array *a) {
  assert(a != NULL);

  free(a->data);
  memset(a, 0, sizeof(*a));
}

int sampgdk_array_zero(struct sampgdk_array *a) {
  assert(a != NULL);

  if (a->data == NULL) {
    return -EINVAL;
  }

  memset(a->data, 0, a->size * a->elem_size);
  return 0;
}

int sampgdk_array_resize(struct sampgdk_array *a, int new_size) {
  void *new_data;

  assert(a != NULL);
  assert(new_size >= 0);
  assert(a->elem_size > 0);

  if (new_size == a->size) {
    return 0;
  }

  if (new_size > 0) {
    new_data = realloc(a->data, a->elem_size * new_size);

    if (new_data == NULL) {
      return -errno;
    }
  } else {
    free(a->data);
    new_data = NULL;
  }

  a->data = new_data;
  a->size = new_size;

  if (a->count > a->size) {
    a->count = a->size;
  }

  return 0;
}

int sampgdk_array_grow(struct sampgdk_array *a) {
  assert(a != NULL);

  if (a->size == 0) {
    return sampgdk_array_resize(a, 1);
  }

  return sampgdk_array_resize(a, (int)(a->size * 2));
}

int sampgdk_array_shrink(struct sampgdk_array *a) {
  assert(a != NULL);

  return sampgdk_array_resize(a, a->count);
}

int sampgdk_array_pad(struct sampgdk_array *a) {
  int space;

  assert(a != NULL);

  if ((space = a->size - a->count) <= 0) {
    return space;
  }

  return (a->count = a->size);
}

void *sampgdk_array_get(struct sampgdk_array *a, int index) {
  assert(a != NULL);

  index = _sampgdk_array_normalize_index(a, index);
  assert(index < a->count);

  return _sampgdk_array_get_elem_ptr(a, index);
}

void sampgdk_array_set(struct sampgdk_array *a, int index, void *elem) {
  assert(a != NULL);

  index = _sampgdk_array_normalize_index(a, index);
  assert(index < a->count);

  memcpy(_sampgdk_array_get_elem_ptr(a, index), elem, a->elem_size);
}

int sampgdk_array_insert(struct sampgdk_array *a,
                         int index,
                         int count,
                         void *elems) {
  int need_count;
  int move_count;

  assert(a != NULL);
  assert(elems != NULL);

  if (count <= 0) {
    return -EINVAL;
  }

  index = _sampgdk_array_normalize_index(a, index);
  assert(index <= a->count);

  need_count = a->count + count - a->size;
  move_count = a->count - index;

  if (need_count > 0) {
    int error;

    if ((error = sampgdk_array_resize(a, a->size + need_count)) < 0) {
      return error;
    }
  }

  if (move_count > 0) {
    memmove(_sampgdk_array_get_elem_ptr(a, index + count),
            _sampgdk_array_get_elem_ptr(a, index),
            move_count * a->elem_size);
  }

  a->count += count;
  memcpy(_sampgdk_array_get_elem_ptr(a, index), elems, count * a->elem_size);

  return index;
}

int sampgdk_array_remove(struct sampgdk_array *a, int index, int count) {
  int move_count;

  assert(a != NULL);

  index = _sampgdk_array_normalize_index(a, index);
  assert(index < a->count);

  if (count <= 0 || count > a->count - index) {
    return -EINVAL;
  }

  move_count = a->count - index - count;

  if (move_count > 0) {
    memmove(_sampgdk_array_get_elem_ptr(a, index),
            _sampgdk_array_get_elem_ptr(a, index + count),
            move_count * a->elem_size);
   }

  a->count -= count;

  if (a->count <= a->size / 4) {
    return sampgdk_array_resize(a, a->size / 2);
  }

  return index;
}

int sampgdk_array_clear(struct sampgdk_array *a) {
  return sampgdk_array_remove(a, 0, a->count);
}

int sampgdk_array_append(struct sampgdk_array *a, void *elem) {
  assert(a != NULL);
  assert(elem != NULL);

  if (a->count == a->size) {
    int error;

    if ((error = sampgdk_array_grow(a)) < 0) {
      return error;
    }
  }

  a->count++;
  sampgdk_array_set(a, a->count - 1, elem);

  return a->count - 1;
}

int sampgdk_array_get_index(struct sampgdk_array *a, void *elem) {
  assert(elem != NULL);
  return ((unsigned char *)elem - (unsigned char *)a->data) / a->elem_size;
}

int sampgdk_array_find(struct sampgdk_array *a,
                       const void *key,
                       sampgdk_array_cmp cmp) {
  int index;
  void *cur;

  assert(a != NULL);
  assert(cmp != NULL);

  for (index = 0; index < a->count; index++) {
    cur = sampgdk_array_get(a, index);
    if (cmp(key, cur) == 0) {
      return index;
    }
  }

  return -EINVAL;
}

int sampgdk_array_find_remove(struct sampgdk_array *a,
                              const void *key,
                              sampgdk_array_cmp cmp) {
  int index;
  void *cur;

  assert(a != NULL);
  assert(cmp != NULL);

  for (index = 0; index < a->count; index++) {
    cur = sampgdk_array_get(a, index);
    if (cmp(key, cur) == 0) {
      sampgdk_array_remove(a, index, 1);
      return index;
    }
  }

  return -EINVAL;
}

/* Copyright (C) 2012-2015 Zeex
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

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "sampgdk.h"

/* #include "init.h" */
/* #include "logprintf.h" */

enum _sampgdk_log_level {
  _SAMPGDK_LOG_DEBUG,
  _SAMPGDK_LOG_INFO,
  _SAMPGDK_LOG_WARNING,
  _SAMPGDK_LOG_ERROR
};

static bool _sampgdk_log_enabled[] = {
  false, /* _SAMPGDK_LOG_DEBUG */
  false, /* _SAMPGDK_LOG_INFO */
  true,  /* _SAMPGDK_LOG_WARNING */
  true , /* _SAMPGDK_LOG_ERROR */
};

static void _sampgdk_log_init_enabled() {
  char *levels;
  char c;
  char op = '\0';

  if ((levels = getenv("SAMPGDK_LOG")) == NULL) {
    return;
  }

  while ((c = *levels++) != '\0') {
    int level = -1;

    switch (c) {
      case '+':
      case '-':
        op = c;
        break;
      case 'd':
        level = _SAMPGDK_LOG_DEBUG;
        break;
      case 'i':
        level = _SAMPGDK_LOG_INFO;
        break;
      case 'w':
        level = _SAMPGDK_LOG_WARNING;
        break;
      case 'e':
        level = _SAMPGDK_LOG_ERROR;
        break;
    }

    if (level >= 0) {
      if (op == '+') {
        _sampgdk_log_enabled[level] = true;
      } else if (op == '-') {
        _sampgdk_log_enabled[level] = false;
      }
    }
  }
}

SAMPGDK_MODULE_INIT(log) {
  _sampgdk_log_init_enabled();
  return 0;
}

SAMPGDK_MODULE_CLEANUP(log) {
  /* nothing to do here */
}

static void _sampgdk_log_message(int level, const char *format, va_list args) {
  const char *level_string;
  char *real_format;

  assert(level >= _SAMPGDK_LOG_DEBUG &&
         level <= _SAMPGDK_LOG_ERROR);

  if (!_sampgdk_log_enabled[level]) {
    return;
  }

  switch (level) {
    case _SAMPGDK_LOG_DEBUG:
      level_string = "debug";
      break;
    case _SAMPGDK_LOG_INFO:
      level_string = "info";
      break;
    case _SAMPGDK_LOG_WARNING:
      level_string = "warning";
      break;
    case _SAMPGDK_LOG_ERROR:
      level_string = "error";
      break;
    default:
      level_string = "";
  }

  real_format = malloc(
    sizeof("[sampgdk:] ") - 1
    + strlen(level_string)
    + strlen(format)
    + 1
  );
  if (real_format == NULL) {
    return;
  }

  strcpy(real_format, "[sampgdk:");
  strcat(real_format, level_string);
  strcat(real_format, "] ");
  strcat(real_format, format);

  sampgdk_do_vlogprintf(real_format, args);

  free(real_format);
}

void sampgdk_log_debug(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _sampgdk_log_message(_SAMPGDK_LOG_DEBUG, format, args);
  va_end(args);
}

void sampgdk_log_info(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _sampgdk_log_message(_SAMPGDK_LOG_INFO, format, args);
  va_end(args);
}

void sampgdk_log_warning(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _sampgdk_log_message(_SAMPGDK_LOG_WARNING, format, args);
  va_end(args);
}

void sampgdk_log_error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _sampgdk_log_message(_SAMPGDK_LOG_ERROR, format, args);
  va_end(args);
}

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_PLUGIN_H
#define SAMPGDK_INTERNAL_PLUGIN_H

#include "sampgdk.h"

int sampgdk_plugin_register(void *plugin);
int sampgdk_plugin_unregister(void *plugin);

void *sampgdk_plugin_get_symbol(void *plugin, const char *name);
void *sampgdk_plugin_get_handle(void *address);

/* Returns all currently registered plugins. */
void **sampgdk_plugin_get_plugins(int *number);

#endif /* !SAMPGDK_INTERNAL_PLUGIN_H */

/* Copyright (C) 2012-2015 Zeex
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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "sampgdk.h"

/* #include "logprintf.h" */

#define _SAMPGDK_LOGPRINTF_BUF_SIZE 1024

#ifdef _MSC_VER
  #define vsnprintf vsprintf_s
#endif

typedef void (SAMPGDK_CDECL *logprintf_t)(const char *format, ...);

/* Gets called before the library is initialized. */
static void _sampgdk_logprintf_stub(const char *format, ...) {
  va_list va;
  va_start(va, format);
  vprintf(format, va);
  printf("\n");
  va_end(va);
}

void *sampgdk_logprintf_impl = &_sampgdk_logprintf_stub;

void sampgdk_do_vlogprintf(const char *format, va_list va) {
  char buffer[_SAMPGDK_LOGPRINTF_BUF_SIZE];
  vsnprintf(buffer, sizeof(buffer), format, va);
  buffer[sizeof(buffer) - 1] = '\0';
  ((logprintf_t)sampgdk_logprintf_impl)("%s", buffer);
}

/* Copyright (C) 2012-2015 Zeex
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

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "sampgdk.h"

#if SAMPGDK_WINDOWS
  #include <windows.h>
#else
  #include <stdint.h>
  #include <unistd.h>
  #include <sys/mman.h>
#endif

/* #include "log.h" */
/* #include "hook.h" */
/* #include "types.h" */

#define _SAMPGDK_HOOK_JMP_SIZE 5
#define _SAMPGDK_HOOK_MAX_INSN_LEN 15
#define _SAMPGDK_HOOK_TRAMPOLINE_SIZE \
  (_SAMPGDK_HOOK_JMP_SIZE + _SAMPGDK_HOOK_MAX_INSN_LEN - 1)

#pragma pack(push, 1)

struct _sampgdk_hook_jmp {
  uint8_t opcode;
  int32_t offset;
};

#pragma pack(pop)

struct _sampgdk_hook {
  uint8_t trampoline[_SAMPGDK_HOOK_TRAMPOLINE_SIZE];
};

#if SAMPGDK_WINDOWS

static void *_sampgdk_hook_unprotect(void *address, size_t size) {
  DWORD old;

  if (VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &old) == 0) {
    return NULL;
  }

  return address;
}

#else /* SAMPGDK_WINDOWS */

static void *_sampgdk_hook_unprotect(void *address, size_t size) {
  long pagesize;

  pagesize = sysconf(_SC_PAGESIZE);
  address = (void *)((long)address & ~(pagesize - 1));

  if (mprotect(address, size, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
    return NULL;
  }

  return address;
}

#endif /* !SAMPGDK_WINDOWS */

static size_t _sampgdk_hook_disasm(uint8_t *code, int *reloc) {
  enum flags {
    MODRM      = 1,
    REG_OPCODE = 1 << 1,
    IMM8       = 1 << 2,
    IMM16      = 1 << 3,
    IMM32      = 1 << 4,
    PLUS_R     = 1 << 5,
    RELOC      = 1 << 6
  };

  static int prefixes[] = {
    0xF0, 0xF2, 0xF3,
    0x2E, 0x36, 0x3E, 0x26, 0x64, 0x65,
    0x66,
    0x67
  };

  struct opcode_info {
    int opcode;
    int reg_opcode;
    int flags;
  };

  static struct opcode_info opcodes[] = {
    /* CALL rel32       */ {0xE8, 0, IMM32 | RELOC},
    /* CALL r/m32       */ {0xFF, 2, MODRM | REG_OPCODE},
    /* JMP rel32        */ {0xE9, 0, IMM32 | RELOC},
    /* JMP r/m32        */ {0xFF, 4, MODRM | REG_OPCODE},
    /* LEA r16,m        */ {0x8D, 0, MODRM},
    /* MOV r/m8,r8      */ {0x88, 0, MODRM},
    /* MOV r/m32,r32    */ {0x89, 0, MODRM},
    /* MOV r8,r/m8      */ {0x8A, 0, MODRM},
    /* MOV r32,r/m32    */ {0x8B, 0, MODRM},
    /* MOV r/m16,Sreg   */ {0x8C, 0, MODRM},
    /* MOV Sreg,r/m16   */ {0x8E, 0, MODRM},
    /* MOV AL,moffs8    */ {0xA0, 0, IMM8},
    /* MOV EAX,moffs32  */ {0xA1, 0, IMM32},
    /* MOV moffs8,AL    */ {0xA2, 0, IMM8},
    /* MOV moffs32,EAX  */ {0xA3, 0, IMM32},
    /* MOV r8, imm8     */ {0xB0, 0, PLUS_R | IMM8},
    /* MOV r32, imm32   */ {0xB8, 0, PLUS_R | IMM32},
    /* MOV r/m8, imm8   */ {0xC6, 0, MODRM | REG_OPCODE | IMM8},
    /* MOV r/m32, imm32 */ {0xC7, 0, MODRM | REG_OPCODE | IMM32},
    /* POP r/m32        */ {0x8F, 0, MODRM | REG_OPCODE},
    /* POP r32          */ {0x58, 0, PLUS_R},
    /* PUSH r/m32       */ {0xFF, 6, MODRM | REG_OPCODE},
    /* PUSH r32         */ {0x50, 0, PLUS_R},
    /* PUSH imm8        */ {0x6A, 0, IMM8},
    /* PUSH imm32       */ {0x68, 0, IMM32},
    /* RET              */ {0xC3, 0, 0},
    /* RET imm16        */ {0xC2, 0, IMM16},
    /* SUB r/m32, imm8  */ {0x83, 5, MODRM | REG_OPCODE | IMM8},
    /* SUB r/m32, r32   */ {0x29, 0, MODRM},
    /* SUB r32, r/m32   */ {0x2B, 0, MODRM}
  };

  int i;
  int len = 0;
  int opcode = 0;

  for (i = 0; i < sizeof(prefixes) / sizeof(*prefixes); i++) {
    if (code[len] == prefixes[i]) {
      len++;
    }
  }

  for (i = 0; i < sizeof(opcodes) / sizeof(*opcodes); i++) {
    bool found = false;

    if (code[len] == opcodes[i].opcode) {
      found = !(opcodes[i].flags & REG_OPCODE)
            || ((code[len + 1] >> 3) & 7) == opcodes[i].reg_opcode;
    }
    if ((opcodes[i].flags & PLUS_R)
        && (code[len] & 0xF8) == opcodes[i].opcode) {
      found = true;
    }

    if (found) {
      opcode = code[len++];
      break;
    }
  }

  if (opcode == 0) {
    return 0;
  }

  if (reloc != NULL && opcodes[i].flags & RELOC) {
    *reloc = len; /* relative call or jump */
  }

  if (opcodes[i].flags & MODRM) {
    int modrm = code[len++];
    int mod = modrm >> 6;
    int rm = modrm & 7;

    if (mod != 3 && rm == 4) {
      len++; /* for SIB */
    }

    if (mod == 1) len += 1; /* [reg + disp8] */
    if (mod == 2) len += 4; /* [reg + disp32] */

    if (mod == 0 && rm == 5) {
      len += 4; /* [disp32] */
    }
  }

  if (opcodes[i].flags & IMM8)  len += 1;
  if (opcodes[i].flags & IMM16) len += 2;
  if (opcodes[i].flags & IMM32) len += 4;

  return len;
}

static void _sampgdk_hook_write_jmp(void *src, void *dst, int32_t offset) {
  struct _sampgdk_hook_jmp jmp;

  jmp.opcode = 0xE9;
  jmp.offset = (uint8_t *)dst - ((uint8_t *)src + sizeof(jmp));

  memcpy((uint8_t *)src + offset, &jmp, sizeof(jmp));
}

sampgdk_hook_t sampgdk_hook_new(void *src, void *dst) {
  struct _sampgdk_hook *hook;
  size_t orig_size = 0;
  size_t insn_len;

  if ((hook = malloc(sizeof(*hook))) == NULL) {
    return NULL;
  }

  _sampgdk_hook_unprotect(src, _SAMPGDK_HOOK_JMP_SIZE);
  _sampgdk_hook_unprotect(hook->trampoline, _SAMPGDK_HOOK_TRAMPOLINE_SIZE);

  /* We can't just jump to src + 5 as we could end up in the middle of
   * some instruction. So we need to determine the instruction length.
   */
  while (orig_size < _SAMPGDK_HOOK_JMP_SIZE) {
    uint8_t *insn = (uint8_t *)src + orig_size;
    int reloc = 0;

    if ((insn_len = _sampgdk_hook_disasm(insn, &reloc)) == 0) {
      sampgdk_log_error("Unsupported instruction");
      break;
    }

    memcpy(hook->trampoline + orig_size, insn, insn_len);

    /* If the original code contains a relative JMP/CALL relocate its
     * destination address.
     */
    if (reloc != 0) {
      int32_t *offset = (int32_t *)(hook->trampoline + orig_size + reloc);
      *offset -= (intptr_t)hook->trampoline - (intptr_t)src;
    }

    orig_size += insn_len;
  }

  if (insn_len > 0) {
    _sampgdk_hook_write_jmp(hook->trampoline, src, orig_size);
    _sampgdk_hook_write_jmp(src, dst, 0);
  } else {
    _sampgdk_hook_write_jmp(hook->trampoline, src, 0);
  }

  return hook;
}

void sampgdk_hook_free(sampgdk_hook_t hook) {
  free(hook);
}

void *sampgdk_hook_trampoline(sampgdk_hook_t hook) {
  return hook->trampoline;
}

/* Copyright (C) 2012-2015 Zeex
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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>

#include "sampgdk.h"

#if SAMPGDK_WINDOWS
  #include <windows.h>
#else
  #include <dlfcn.h>
  #include <string.h>
#endif

/* #include "array.h" */
/* #include "init.h" */
/* #include "plugin.h" */

static struct sampgdk_array _sampgdk_plugins;

SAMPGDK_MODULE_INIT(plugin) {
  return sampgdk_array_new(&_sampgdk_plugins, 1, sizeof(void *));
}

SAMPGDK_MODULE_CLEANUP(plugin) {
  sampgdk_array_free(&_sampgdk_plugins);
}

static int _sampgdk_plugin_compare_handle(const void *key,
                                          const void *elem) {
  const void *handle2 = *(const void **)elem;

  assert(key != NULL);
  assert(elem != NULL);

  if (key < handle2) return -1;
  if (key > handle2) return +1;

  return 0;
}

int sampgdk_plugin_register(void *plugin) {
  assert(plugin != NULL);
  if (sampgdk_array_find(&_sampgdk_plugins,
                         plugin,
                         _sampgdk_plugin_compare_handle) < 0) {
    return sampgdk_array_append(&_sampgdk_plugins, &plugin);
  }
  return -EINVAL;
}

int sampgdk_plugin_unregister(void *plugin) {
  assert(plugin != NULL);
  return sampgdk_array_find_remove(&_sampgdk_plugins,
                                   plugin,
                                   _sampgdk_plugin_compare_handle);
}

void **sampgdk_plugin_get_plugins(int *number) {
  assert(number != NULL);
  *number = _sampgdk_plugins.count;
  return _sampgdk_plugins.data;
}

#if SAMPGDK_WINDOWS

void *sampgdk_plugin_get_symbol(void *plugin, const char *name)  {
  assert(plugin != NULL);
  assert(name != NULL);
  return (void *)GetProcAddress((HMODULE)plugin, name);
}

void *sampgdk_plugin_get_handle(void *address) {
  MEMORY_BASIC_INFORMATION mbi;
  assert(address != NULL);
  if (VirtualQuery(address, &mbi, sizeof(mbi)) == 0) {
    return NULL;
  }
  return (void *)mbi.AllocationBase;
}

#else /* SAMPGDK_WINDOWS */

void *sampgdk_plugin_get_symbol(void *plugin, const char *name)  {
  assert(plugin != NULL);
  assert(name != NULL);
  return dlsym(plugin, name);
}

void *sampgdk_plugin_get_handle(void *address) {
  Dl_info info;
  assert(address != NULL);
  if (dladdr(address, &info) != 0) {
    return dlopen(info.dli_fname, RTLD_NOW);
  }
  return NULL;
}

#endif /* !SAMPGDK_WINDOWS */

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_PARAM_H
#define SAMPGDK_INTERNAL_PARAM_H

#include "sampgdk.h"

void sampgdk_param_get_cell(AMX *amx, int index, cell *param);
void sampgdk_param_get_bool(AMX *amx, int index, bool *param);
void sampgdk_param_get_float(AMX *amx, int index, float *param);
void sampgdk_param_get_string(AMX *amx, int index, char **param);

/* Returns pointer to the start of the parameter list. */
cell *sampgdk_param_get_start(AMX *amx);

#endif /* !SAMPGDK_INTERNAL_PARAM_H */

/* Copyright (C) 2011-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_FAKEAMX_H
#define SAMPGDK_INTERNAL_FAKEAMX_H

#include "sampgdk.h"

/* Returns the global fake AMX instance. */
AMX *sampgdk_fakeamx_amx(void);

/* Changes the size of the fake AMX heap. Used in the amx_Allot() hook. */
int sampgdk_fakeamx_resize_heap(int cells);

/* Push a value onto the fake AMX heap. */
int sampgdk_fakeamx_push(int cells, cell *address);
int sampgdk_fakeamx_push_cell(cell value, cell *address);
int sampgdk_fakeamx_push_float(float value, cell *address);
int sampgdk_fakeamx_push_array(const cell *src, int size, cell *address);
int sampgdk_fakeamx_push_string(const char *src, int *size, cell *address);
void sampgdk_fakeamx_pop(cell address);

/* Get stuff back from the heap. Usually used for output parameters. */
void sampgdk_fakeamx_get_cell(cell address, cell *value);
void sampgdk_fakeamx_get_bool(cell address, bool *value);
void sampgdk_fakeamx_get_float(cell address, float *value);
void sampgdk_fakeamx_get_array(cell address, cell *dest, int size);
void sampgdk_fakeamx_get_string(cell address, char *dest, int size);

#endif /* !SAMPGDK_INTERNAL_FAKEAMX_H */

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_CALLBACK_H
#define SAMPGDK_INTERNAL_CALLBACK_H

#include "sampgdk.h"

/* Callback handler function. */
typedef bool (*sampgdk_callback)(AMX *amx, void *func, cell *retval);

/* Register and unregister a callback in the global callback table.
 *
 * This is usually done only from generated init and cleanup functions of a_*
 * modules. Currently the only module that defines callbacks is a_samp.
 */
int sampgdk_callback_register(const char *name, sampgdk_callback handler);
void sampgdk_callback_unregister(const char *name);

/* Gets the name of the callback with the specified index,
 * similar to amx_GetPublic().
 */
bool sampgdk_callback_get(int index, char **name);

/* Executes the callback handler registered for the specified callback.
 *
 * The return value indicates whether the callback returned a "bad" value,
 * i.e. whether the gamemode is allowed to execute the associated public
 * function. This value is specified in the IDL files via the callback's
 * "badret" attribute.
 */
bool sampgdk_callback_invoke(AMX *amx, const char *name,
    int paramcount, cell *retval);

#endif /* !SAMPGDK_INTERNAL_CALLBACK_H */

/* Copyright (C) 2013-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_AMX_H
#define SAMPGDK_INTERNAL_AMX_H

#include "sampgdk.h"

#define AMX_EXEC_GDK (-10000)

struct sampgdk_amx_api {
  uint16_t *(AMXAPI *Align16)(uint16_t *v);
  uint32_t *(AMXAPI *Align32)(uint32_t *v);
  uint64_t *(AMXAPI *Align64)(uint64_t *v);
  int (AMXAPI *Allot)(AMX *amx, int cells, cell *amx_addr, cell **phys_addr);
  int (AMXAPI *Callback)(AMX *amx, cell index, cell *result, cell *params);
  int (AMXAPI *Cleanup)(AMX *amx);
  int (AMXAPI *Clone)(AMX *amxClone, AMX *amxSource, void *data);
  int (AMXAPI *Exec)(AMX *amx, cell *retval, int index);
  int (AMXAPI *FindNative)(AMX *amx, const char *name, int *index);
  int (AMXAPI *FindPublic)(AMX *amx, const char *funcname, int *index);
  int (AMXAPI *FindPubVar)(AMX *amx, const char *varname, cell *amx_addr);
  int (AMXAPI *FindTagId)(AMX *amx, cell tag_id, char *tagname);
  int (AMXAPI *Flags)(AMX *amx,uint16_t *flags);
  int (AMXAPI *GetAddr)(AMX *amx,cell amx_addr,cell **phys_addr);
  int (AMXAPI *GetNative)(AMX *amx, int index, char *funcname);
  int (AMXAPI *GetPublic)(AMX *amx, int index, char *funcname);
  int (AMXAPI *GetPubVar)(AMX *amx, int index, char *varname, cell *amx_addr);
  int (AMXAPI *GetString)(char *dest,const cell *source, int use_wchar,
                          size_t size);
  int (AMXAPI *GetTag)(AMX *amx, int index, char *tagname, cell *tag_id);
  int (AMXAPI *GetUserData)(AMX *amx, long tag, void **ptr);
  int (AMXAPI *Init)(AMX *amx, void *program);
  int (AMXAPI *InitJIT)(AMX *amx, void *reloc_table, void *native_code);
  int (AMXAPI *MemInfo)(AMX *amx, long *codesize, long *datasize,
                        long *stackheap);
  int (AMXAPI *NameLength)(AMX *amx, int *length);
  AMX_NATIVE_INFO *(AMXAPI *NativeInfo)(const char *name, AMX_NATIVE func);
  int (AMXAPI *NumNatives)(AMX *amx, int *number);
  int (AMXAPI *NumPublics)(AMX *amx, int *number);
  int (AMXAPI *NumPubVars)(AMX *amx, int *number);
  int (AMXAPI *NumTags)(AMX *amx, int *number);
  int (AMXAPI *Push)(AMX *amx, cell value);
  int (AMXAPI *PushArray)(AMX *amx, cell *amx_addr, cell **phys_addr,
                          const cell array[], int numcells);
  int (AMXAPI *PushString)(AMX *amx, cell *amx_addr, cell **phys_addr,
                           const char *string, int pack, int use_wchar);
  int (AMXAPI *RaiseError)(AMX *amx, int error);
  int (AMXAPI *Register)(AMX *amx, const AMX_NATIVE_INFO *nativelist,
                         int number);
  int (AMXAPI *Release)(AMX *amx, cell amx_addr);
  int (AMXAPI *SetCallback)(AMX *amx, AMX_CALLBACK callback);
  int (AMXAPI *SetDebugHook)(AMX *amx, AMX_DEBUG debug);
  int (AMXAPI *SetString)(cell *dest, const char *source, int pack,
                          int use_wchar, size_t size);
  int (AMXAPI *SetUserData)(AMX *amx, long tag, void *ptr);
  int (AMXAPI *StrLen)(const cell *cstring, int *length);
  int (AMXAPI *UTF8Check)(const char *string, int *length);
  int (AMXAPI *UTF8Get)(const char *string, const char **endptr, cell *value);
  int (AMXAPI *UTF8Len)(const cell *cstr, int *length);
  int (AMXAPI *UTF8Put)(char *string, char **endptr, int maxchars, cell value);
};

extern struct sampgdk_amx_api *sampgdk_amx_api_ptr;

#define amx_Align16      sampgdk_amx_api_ptr->Align16
#define amx_Align32      sampgdk_amx_api_ptr->Align32
#define amx_Align64      sampgdk_amx_api_ptr->Align64
#define amx_Allot        sampgdk_amx_api_ptr->Allot
#define amx_Callback     sampgdk_amx_api_ptr->Callback
#define amx_Cleanup      sampgdk_amx_api_ptr->Cleanup
#define amx_Clone        sampgdk_amx_api_ptr->Clone
#define amx_Exec         sampgdk_amx_api_ptr->Exec
#define amx_FindNative   sampgdk_amx_api_ptr->FindNative
#define amx_FindPublic   sampgdk_amx_api_ptr->FindPublic
#define amx_FindPubVar   sampgdk_amx_api_ptr->FindPubVar
#define amx_FindTagId    sampgdk_amx_api_ptr->FindTagId
#define amx_Flags        sampgdk_amx_api_ptr->Flags
#define amx_GetAddr      sampgdk_amx_api_ptr->GetAddr
#define amx_GetNative    sampgdk_amx_api_ptr->GetNative
#define amx_GetPublic    sampgdk_amx_api_ptr->GetPublic
#define amx_GetPubVar    sampgdk_amx_api_ptr->GetPubVar
#define amx_GetString    sampgdk_amx_api_ptr->GetString
#define amx_GetTag       sampgdk_amx_api_ptr->GetTag
#define amx_GetUserData  sampgdk_amx_api_ptr->GetUserData
#define amx_Init         sampgdk_amx_api_ptr->Init
#define amx_InitJIT      sampgdk_amx_api_ptr->InitJIT
#define amx_MemInfo      sampgdk_amx_api_ptr->MemInfo
#define amx_NameLength   sampgdk_amx_api_ptr->NameLength
#define amx_NativeInfo   sampgdk_amx_api_ptr->NativeInfo
#define amx_NumNatives   sampgdk_amx_api_ptr->NumNatives
#define amx_NumPublics   sampgdk_amx_api_ptr->NumPublics
#define amx_NumPubVars   sampgdk_amx_api_ptr->NumPubVars
#define amx_NumTags      sampgdk_amx_api_ptr->NumTags
#define amx_Push         sampgdk_amx_api_ptr->Push
#define amx_PushArray    sampgdk_amx_api_ptr->PushArray
#define amx_PushString   sampgdk_amx_api_ptr->PushString
#define amx_RaiseError   sampgdk_amx_api_ptr->RaiseError
#define amx_Register     sampgdk_amx_api_ptr->Register
#define amx_Release      sampgdk_amx_api_ptr->Release
#define amx_SetCallback  sampgdk_amx_api_ptr->SetCallback
#define amx_SetDebugHook sampgdk_amx_api_ptr->SetDebugHook
#define amx_SetString    sampgdk_amx_api_ptr->SetString
#define amx_SetUserData  sampgdk_amx_api_ptr->SetUserData
#define amx_StrLen       sampgdk_amx_api_ptr->StrLen
#define amx_UTF8Check    sampgdk_amx_api_ptr->UTF8Check
#define amx_UTF8Get      sampgdk_amx_api_ptr->UTF8Get
#define amx_UTF8Len      sampgdk_amx_api_ptr->UTF8Len
#define amx_UTF8Put      sampgdk_amx_api_ptr->UTF8Put

#endif /* !SAMPGDK_INTERNAL_AMX_H */

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_NATIVE_H
#define SAMPGDK_INTERNAL_NATIVE_H

#include <stdarg.h>

#include "sampgdk.h"

/* Register a native function in the internal natives table. */
int sampgdk_native_register(const char *name, AMX_NATIVE func);

AMX_NATIVE sampgdk_native_find(const char *name);
AMX_NATIVE sampgdk_native_find_warn(const char *name);
AMX_NATIVE sampgdk_native_find_stub(const char *name);
AMX_NATIVE sampgdk_native_find_warn_stub(const char *name);
AMX_NATIVE sampgdk_native_find_flexible(const char *name, AMX_NATIVE current);

/* Returns all currently registered natives. */
const AMX_NATIVE_INFO *sampgdk_native_get_natives(int *number);

cell sampgdk_native_call(AMX_NATIVE native, cell *params);
cell sampgdk_native_invoke(AMX_NATIVE native, const char *format, va_list args);
cell sampgdk_native_invoke_array(AMX_NATIVE native, const char *format, void **args);

#endif /* !SAMPGDK_NATIVE_H_ */

/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_TIMER_H
#define SAMPGDK_INTERNAL_TIMER_H

#include "sampgdk.h"

/* Timer callback function.
 * There's also a public typedef TimerCallback in <sampgdk/types.h>.
 */
typedef void (SAMPGDK_CALL *sampgdk_timer_callback)(int id, void *param);

int sampgdk_timer_set(int interval, bool repeat,
    sampgdk_timer_callback calback, void *param);
int sampgdk_timer_kill(int timerid);

/* Processes timers created by the specified plugin. */
void sampgdk_timer_process_timers(void *plugin);

#endif /* !SAMPGDK_INTERNAL_TIMER_H */

/* Copyright (C) 2012-2015 Zeex
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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* #include "array.h" */
/* #include "callback.h" */
/* #include "init.h" */
/* #include "log.h" */
/* #include "param.h" */
/* #include "plugin.h" */

#define _SAMPGDK_CALLBACK_MAX_ARGS 32

typedef bool (PLUGIN_CALL *_sampgdk_callback_filter)(AMX *amx,
                                                     const char *name,
                                                     cell *params,
                                                     cell *retval);

struct _sampgdk_callback_info {
  char *name;
  void *handler;
};

static struct sampgdk_array _sampgdk_callbacks;

SAMPGDK_MODULE_INIT(callback) {
  int error;

  error = sampgdk_array_new(&_sampgdk_callbacks,
                            1,
                            sizeof(struct _sampgdk_callback_info));
  if (error < 0) {
    return error;
  }

  return sampgdk_callback_register("OnPublicCall", NULL);
}

SAMPGDK_MODULE_CLEANUP(callback) {
  int i;
  struct _sampgdk_callback_info *callback;

  for (i = 0; i < _sampgdk_callbacks.count; i++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, i);
    free(callback->name);
  }

  sampgdk_array_free(&_sampgdk_callbacks);
}

static int _sampgdk_callback_compare_name(const void *key,
                                          const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key,
                ((const struct _sampgdk_callback_info *)elem)->name);
}

static struct _sampgdk_callback_info *_sampgdk_callback_find(const char *name) {
  assert(name != NULL);

  if (_sampgdk_callbacks.count == 0) {
    return NULL;
  }

  return bsearch(name,
                 _sampgdk_callbacks.data,
                 _sampgdk_callbacks.count - 1,
                 _sampgdk_callbacks.elem_size,
                 _sampgdk_callback_compare_name);
}

int sampgdk_callback_register(const char *name,
                              sampgdk_callback handler) {
  int error;
  int i;
  struct _sampgdk_callback_info callback;
  struct _sampgdk_callback_info *ptr;

  assert(name != NULL);

  ptr = _sampgdk_callback_find(name);
  if (ptr != NULL) {
    return sampgdk_array_get_index(&_sampgdk_callbacks, ptr);
  }

  callback.name = malloc(strlen(name) + 1);
  if (callback.name == NULL) {
    return -ENOMEM;
  }

  callback.handler = handler;
  strcpy(callback.name, name);

  /* Keep callbacks ordered by name.
   * This allows us to use binary search in sampgdk_callback_find().
   */
  for (i = 0; i < _sampgdk_callbacks.count - 1; i++) {
    ptr = sampgdk_array_get(&_sampgdk_callbacks, i);
    if (strcmp(name, ptr->name) <= 0) {
      break;
    }
  }

  error = sampgdk_array_insert(&_sampgdk_callbacks, i, 1, &callback);
  if (error < 0) {
    free(callback.name);
    return error;
  }

  return error; /* index */
}

void sampgdk_callback_unregister(const char *name) {
  struct _sampgdk_callback_info *callback;

  if ((callback = _sampgdk_callback_find(name)) != NULL) {
    callback->handler = NULL;
  }
}

bool sampgdk_callback_get(int index, char **name) {
  struct _sampgdk_callback_info *callback;

  assert(name != NULL);

  if (index < 0 || index >= _sampgdk_callbacks.count) {
    return false;
  }

  callback = sampgdk_array_get(&_sampgdk_callbacks, index);
  *name = callback->name;

  return true;
}

bool sampgdk_callback_invoke(AMX *amx,
                             const char *name,
                             int paramcount,
                             cell *retval)
{
  struct _sampgdk_callback_info *callback;
  struct _sampgdk_callback_info *callback_filter;
  cell params[_SAMPGDK_CALLBACK_MAX_ARGS + 1];
  void **plugins;
  int num_plugins;
  int i;

  assert(amx != NULL);

  callback = _sampgdk_callback_find(name);
  callback_filter = sampgdk_array_get(&_sampgdk_callbacks, -1);

  assert(callback_filter != NULL);

  if (paramcount > _SAMPGDK_CALLBACK_MAX_ARGS) {
    sampgdk_log_error("Too many callback arguments (at most %d allowed)",
                      _SAMPGDK_CALLBACK_MAX_ARGS);
    return true;
  }

  params[0] = paramcount * sizeof(cell);
  memcpy(&params[1], sampgdk_param_get_start(amx), params[0]);

  plugins = sampgdk_plugin_get_plugins(&num_plugins);

  for (i = 0; i < num_plugins; i++) {
    void *func;

    func = sampgdk_plugin_get_symbol(plugins[i], callback_filter->name);
    if (func != NULL
        && !((_sampgdk_callback_filter)func)(amx, name, params, retval)) {
      continue;
    }

    if (callback == NULL || callback->handler == NULL) {
      continue;
    }

    func = sampgdk_plugin_get_symbol(plugins[i], callback->name);
    if (func != NULL
        && !((sampgdk_callback)callback->handler)(amx, func, retval)) {
      return false;
    }
  }

  return true;
}

/* Copyright (C) 2012-2015 Zeex
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

#include <assert.h>
#include <stdlib.h>

/* #include "amx.h" */
/* #include "param.h" */

void sampgdk_param_get_cell(AMX *amx, int index, cell *param) {
  assert(param != NULL);
  *param = sampgdk_param_get_start(amx)[index];
}

void sampgdk_param_get_bool(AMX *amx, int index, bool *param) {
  assert(param != NULL);
  *param = !!sampgdk_param_get_start(amx)[index];
}

void sampgdk_param_get_float(AMX *amx, int index, float *param) {
  cell p = sampgdk_param_get_start(amx)[index];
  assert(param != NULL);
  *param = amx_ctof(p);
}

void sampgdk_param_get_string(AMX *amx, int index, char **param) {
  cell amx_addr;
  cell *phys_addr;
  int length;
  char *string;

  amx_addr = sampgdk_param_get_start(amx)[index];
  if (amx_GetAddr(amx, amx_addr, &phys_addr) != AMX_ERR_NONE) {
    return;
  }

  amx_StrLen(phys_addr, &length);
  string = malloc((length + 1) * sizeof(char));

  if (amx_GetString(string, phys_addr, 0, length + 1) != AMX_ERR_NONE) {
    free(string);
    return;
  }

  assert(param != NULL);
  *param = string;
}

cell *sampgdk_param_get_start(AMX *amx) {
  unsigned char *data =  amx->data != NULL
    ? amx->data
    : amx->base + ((AMX_HEADER *)amx->base)->dat;
  return (cell *)(data + amx->stk);
}

/* Copyright (C) 2011-2015 Zeex
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

#include <assert.h>
#include <limits.h>
#include <string.h>

/* #include "amx.h" */
/* #include "array.h" */
/* #include "fakeamx.h" */
/* #include "init.h" */

/* Space reserved for the stack. */
#define _SAMPGDK_FAKEAMX_STACK_SIZE 64

/* The initial size of the heap. */
#define _SAMPGDK_FAKEAMX_HEAP_SIZE 1024

static struct {
  AMX                  amx;
  AMX_HEADER           amxhdr;
  struct sampgdk_array heap;
} _sampgdk_fakeamx;

SAMPGDK_MODULE_INIT(fakeamx) {
  int error;

  memset(&_sampgdk_fakeamx, 0, sizeof(_sampgdk_fakeamx));

  error = sampgdk_array_new(&_sampgdk_fakeamx.heap,
                            _SAMPGDK_FAKEAMX_HEAP_SIZE +
                            _SAMPGDK_FAKEAMX_STACK_SIZE,
                            sizeof(cell));
  if (error < 0) {
    return error;
  }

  _sampgdk_fakeamx.amxhdr.magic = AMX_MAGIC;
  _sampgdk_fakeamx.amxhdr.file_version = MIN_FILE_VERSION;
  _sampgdk_fakeamx.amxhdr.amx_version = MIN_AMX_VERSION;
  _sampgdk_fakeamx.amxhdr.dat =
    (cell)_sampgdk_fakeamx.heap.data - (cell)&_sampgdk_fakeamx.amxhdr;
  _sampgdk_fakeamx.amxhdr.defsize = sizeof(AMX_FUNCSTUBNT);

  _sampgdk_fakeamx.amx.base = (unsigned char *)&_sampgdk_fakeamx.amxhdr;
  _sampgdk_fakeamx.amx.data = (unsigned char *)_sampgdk_fakeamx.heap.data;
  _sampgdk_fakeamx.amx.callback = amx_Callback;
  _sampgdk_fakeamx.amx.stp = _sampgdk_fakeamx.heap.size * sizeof(cell);
  _sampgdk_fakeamx.amx.stk = _sampgdk_fakeamx.amx.stp;
  _sampgdk_fakeamx.amx.flags = AMX_FLAG_NTVREG | AMX_FLAG_RELOC;

  sampgdk_array_pad(&_sampgdk_fakeamx.heap);

  return 0;
}

SAMPGDK_MODULE_CLEANUP(fakeamx) {
  sampgdk_array_free(&_sampgdk_fakeamx.heap);
}

AMX *sampgdk_fakeamx_amx(void) {
  return &_sampgdk_fakeamx.amx;
}

int sampgdk_fakeamx_resize_heap(int cells) {
  int error;
  cell old_size;
  cell new_size;
  cell old_stk;
  cell new_stk;
  cell new_stp;

  assert(cells > 0);

  old_size = _sampgdk_fakeamx.heap.size;
  new_size = cells;

  error = sampgdk_array_resize(&_sampgdk_fakeamx.heap, new_size);
  sampgdk_array_pad(&_sampgdk_fakeamx.heap);
  if (error < 0) {
    return error;
  }

  /* Update data pointers to point at the newly allocated heap. */
  _sampgdk_fakeamx.amxhdr.dat = (cell)_sampgdk_fakeamx.heap.data - (cell)&_sampgdk_fakeamx.amxhdr;
  _sampgdk_fakeamx.amx.data = (unsigned char *)_sampgdk_fakeamx.heap.data;

  old_stk = _sampgdk_fakeamx.amx.stk;
  new_stk = _sampgdk_fakeamx.amx.stk + (new_size - old_size) * sizeof(cell);
  new_stp = _sampgdk_fakeamx.amx.stp + (new_size - old_size) * sizeof(cell);

  /* Shift stack contents. */
  memmove((unsigned char *)_sampgdk_fakeamx.heap.data
                           + new_stk - _SAMPGDK_FAKEAMX_STACK_SIZE,
          (unsigned char *)_sampgdk_fakeamx.heap.data
                           + old_stk - _SAMPGDK_FAKEAMX_STACK_SIZE,
          _SAMPGDK_FAKEAMX_STACK_SIZE);

  _sampgdk_fakeamx.amx.stk = new_stk;
  _sampgdk_fakeamx.amx.stp = new_stp;

  return 0;
}

int sampgdk_fakeamx_push(int cells, cell *address) {
  cell old_hea, new_hea;
  cell old_heap_size, new_heap_size;

  assert(cells > 0);

  old_hea = _sampgdk_fakeamx.amx.hea;
  new_hea = _sampgdk_fakeamx.amx.hea + cells * sizeof(cell);

  old_heap_size = _sampgdk_fakeamx.heap.size;
  new_heap_size = (new_hea + _SAMPGDK_FAKEAMX_STACK_SIZE) / sizeof(cell);

  if (new_hea >= (cell)(old_heap_size * sizeof(cell))) {
    int error;

    error = sampgdk_fakeamx_resize_heap(new_heap_size);
    if (error < 0) {
      return error;
    }
  }

  _sampgdk_fakeamx.amx.hea = new_hea;

  if (address != NULL) {
    *address = old_hea;
  }

  return 0;
}

int sampgdk_fakeamx_push_cell(cell value, cell *address) {
  int error;

  assert(address != NULL);

  if ((error = sampgdk_fakeamx_push(1, address)) < 0) {
    return error;
  }

  ((cell *)(_sampgdk_fakeamx.heap.data))[*address / sizeof(cell)] = value;

  return 0;
}

int sampgdk_fakeamx_push_float(float value, cell *address) {
  return sampgdk_fakeamx_push_cell(amx_ftoc(value), address);
}

int sampgdk_fakeamx_push_array(const cell *src, int size, cell *address) {
  int error;
  cell *dest;

  assert(address != NULL);
  assert(src != NULL);
  assert(size > 0);

  if ((error = sampgdk_fakeamx_push(size, address)) < 0) {
    return error;
  }

  dest = sampgdk_array_get(&_sampgdk_fakeamx.heap, *address / sizeof(cell));
  memcpy(dest, src, size * sizeof(cell));

  return 0;
}

int sampgdk_fakeamx_push_string(const char *src, int *size, cell *address) {
  int src_size;
  int error;

  assert(address != NULL);
  assert(src != NULL);

  src_size = (int)strlen(src) + 1;
  if ((error = sampgdk_fakeamx_push(src_size, address)) < 0) {
    return error;
  }

  amx_SetString(sampgdk_array_get(&_sampgdk_fakeamx.heap,
                                 *address / sizeof(cell)),
                src, 0, 0, src_size);

  if (size != NULL) {
    *size = src_size;
  }

  return 0;
}

void sampgdk_fakeamx_get_cell(cell address, cell *value) {
  assert(address % sizeof(cell) == 0);
  assert(value != NULL);

  *value = *(cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap,
                                      address / sizeof(cell));
}

void sampgdk_fakeamx_get_bool(cell address, bool *value) {
  cell tmp;

  assert(address % sizeof(cell) == 0);
  assert(value != NULL);

  sampgdk_fakeamx_get_cell(address, &tmp);
  *value = (bool)tmp;
}

void sampgdk_fakeamx_get_float(cell address, float *value) {
  cell tmp;

  assert(address % sizeof(cell) == 0);
  assert(value != NULL);

  sampgdk_fakeamx_get_cell(address, &tmp);
  *value = amx_ctof(tmp);
}

void sampgdk_fakeamx_get_array(cell address, cell *dest, int size) {
  cell *src;

  assert(address % sizeof(cell) == 0);
  assert(dest != NULL);
  assert(size > 0);

  src = sampgdk_array_get(&_sampgdk_fakeamx.heap, address / sizeof(cell));
  memcpy(dest, src, size * sizeof(cell));
}

void sampgdk_fakeamx_get_string(cell address, char *dest, int size) {
  assert(address % sizeof(cell) == 0);
  assert(dest != NULL);

  amx_GetString(dest, (cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap,
                                                address / sizeof(cell)),
                                                0, size);
}

void sampgdk_fakeamx_pop(cell address) {
  assert(address % sizeof(cell) == 0);

  if (_sampgdk_fakeamx.amx.hea > address) {
    _sampgdk_fakeamx.amx.hea = address;
  }
}

/* Copyright (C) 2013-2015 Zeex
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

/* #include "amx.h" */

struct sampgdk_amx_api *sampgdk_amx_api_ptr;

/* Copyright (C) 2013-2015 Zeex
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

#include "sampgdk.h"

/* #include "internal/native.h" */

SAMPGDK_API(const AMX_NATIVE_INFO *, sampgdk_GetNatives(int *number)) {
  return sampgdk_native_get_natives(number);
}

SAMPGDK_API(AMX_NATIVE, sampgdk_FindNative(const char *name)) {
  if (name != NULL) {
    return sampgdk_native_find(name);
  }
  return NULL;
}

SAMPGDK_API(cell, sampgdk_CallNative(AMX_NATIVE native, cell *params)) {
  return sampgdk_native_call(native, params);
}

SAMPGDK_API(cell, sampgdk_InvokeNative(AMX_NATIVE native,
                                       const char *format, ...)) {
  cell retval;
  va_list args;

  va_start(args, format);
  retval = sampgdk_native_invoke(native, format, args);
  va_end(args);

  return retval;
}

SAMPGDK_API(cell, sampgdk_InvokeNativeV(AMX_NATIVE native,
                                        const char *format, va_list args)) {
  return sampgdk_native_invoke(native, format, args);
}

SAMPGDK_API(cell, sampgdk_InvokeNativeArray(AMX_NATIVE native,
                                            const char *format, void **args)) {
  return sampgdk_native_invoke_array(native, format, args);
}

/* Copyright (C) 2012-2015 Zeex
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

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* #include "array.h" */
/* #include "fakeamx.h" */
/* #include "init.h" */
/* #include "likely.h" */
/* #include "native.h" */
/* #include "log.h" */

#define _SAMPGDK_NATIVE_MAX_ARGS     32
#define _SAMPGDK_NATIVE_MAX_ARGS_SIZE 8  /* in bytes */

static struct sampgdk_array _sampgdk_natives;

SAMPGDK_MODULE_INIT(native) {
  int error;
  AMX_NATIVE_INFO null = {NULL, NULL};

  error = sampgdk_array_new(&_sampgdk_natives,
                            100,
                            sizeof(AMX_NATIVE_INFO));
  if (error < 0) {
    return error;
  }

  return sampgdk_array_append(&_sampgdk_natives, &null);
}

SAMPGDK_MODULE_CLEANUP(native) {
  sampgdk_array_free(&_sampgdk_natives);
}

int sampgdk_native_register(const char *name, AMX_NATIVE func) {
  AMX_NATIVE_INFO info;
  AMX_NATIVE_INFO *ptr;
  int i;

  info.name = name;
  info.func = func;

  assert(name != 0);

  /* Keep natives ordered by name.
   * This allows us to use binary search in sampgdk_native_find().
   */
  for (i = 0; i < _sampgdk_natives.count - 1; i++) {
    ptr = sampgdk_array_get(&_sampgdk_natives, i);
    if (strcmp(name, ptr->name) <= 0) {
      break;
    }
  }

  return sampgdk_array_insert(&_sampgdk_natives, i, 1, &info);
}

static int _sampgdk_native_compare_bsearch(const void *key,
                                           const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key, ((const AMX_NATIVE_INFO *)elem)->name);
}

AMX_NATIVE sampgdk_native_find(const char *name) {
  AMX_NATIVE_INFO *info;

  assert(name != NULL);

  if (_sampgdk_natives.data == NULL) {
    /* Perhaps they forgot to initialize? */
    return NULL;
  }

  info = bsearch(name, _sampgdk_natives.data,
                       _sampgdk_natives.count - 1,
                       _sampgdk_natives.elem_size,
                       _sampgdk_native_compare_bsearch);
  if (info == NULL) {
    return NULL;
  }

  return info->func;
}

AMX_NATIVE sampgdk_native_find_warn(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  func = sampgdk_native_find(name);
  if (func == NULL) {
    sampgdk_log_warning("Native function not found: %s", name);
  }

  return func;
}

static cell AMX_NATIVE_CALL native_stub(AMX *amx, cell *params) {
  return 0;
}

AMX_NATIVE sampgdk_native_find_stub(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  if ((func = sampgdk_native_find(name)) == NULL) {
    return native_stub;
  }

  return func;
}

AMX_NATIVE sampgdk_native_find_warn_stub(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  if ((func = sampgdk_native_find_warn(name)) == NULL) {
    return native_stub;
  }

  return func;
}

AMX_NATIVE sampgdk_native_find_flexible(const char *name, AMX_NATIVE current) {
  char *always_search;

  if (SAMPGDK_LIKELY(current != NULL && current != native_stub)) {
    return current;
  }

  if (current == NULL) {
    /* This is the first time this native is searched for, do it as usual.
     */
    return sampgdk_native_find_warn_stub(name);
  }

  if ((always_search = getenv("SAMGDK_NATIVE_SEARCH_ALWAYS")) != NULL
      && atoi(always_search) != 0) {
    /* Previous attempt to find the native failed, but the always search
     * option is set so search again.
     */
    return sampgdk_native_find_warn_stub(name);
  }

  return current;
}

const AMX_NATIVE_INFO *sampgdk_native_get_natives(int *number) {
  if (number != NULL) {
    *number = _sampgdk_natives.count - 1;
  }
  return _sampgdk_natives.data;
}

cell sampgdk_native_call(AMX_NATIVE native, cell *params) {
  AMX *amx = sampgdk_fakeamx_amx();
  assert(native != NULL);
  return native(amx, params);
}

cell sampgdk_native_invoke(AMX_NATIVE native,
                           const char *format,
                           va_list args) {
  cell i = 0;
  const char *format_ptr = format;
  unsigned char args_copy[_SAMPGDK_NATIVE_MAX_ARGS *
                          _SAMPGDK_NATIVE_MAX_ARGS_SIZE];
  unsigned char *args_ptr = args_copy;
  void *args_array[_SAMPGDK_NATIVE_MAX_ARGS];

  assert(format_ptr != NULL);

  while (*format_ptr != '\0' && i < _SAMPGDK_NATIVE_MAX_ARGS) {
    switch (*format_ptr) {
      case 'i': /* integer */
      case 'd': /* integer */
        *(int *)args_ptr = va_arg(args, int);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_NATIVE_MAX_ARGS_SIZE;
        break;
      case 'b': /* boolean */
        *(bool *)args_ptr = !!va_arg(args, int);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_NATIVE_MAX_ARGS_SIZE;
        break;
      case 'f': /* floating-point */
        *(float *)args_ptr = (float)va_arg(args, double);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_NATIVE_MAX_ARGS_SIZE;
        break;
      case 'r': /* const reference */
      case 'R': /* non-const reference */
      case 's': /* const string */
      case 'S': /* non-const string */
      case 'a': /* const array */
      case 'A': /* non-const array */
        args_array[i++] = va_arg(args, void *);
        break;
    }
    format_ptr++;
  }

  return sampgdk_native_invoke_array(native, format, args_array);
}

cell sampgdk_native_invoke_array(AMX_NATIVE native, const char *format,
                                 void **args) {
  AMX *amx = sampgdk_fakeamx_amx();
  const char *format_ptr = format;
  cell i = 0;
  cell params[_SAMPGDK_NATIVE_MAX_ARGS + 1];
  cell size[_SAMPGDK_NATIVE_MAX_ARGS] = {0};
  char type[_SAMPGDK_NATIVE_MAX_ARGS];
  int needs_size = -1;
  enum {
    ST_READ_SPEC,
    ST_NEED_SIZE,
    ST_READING_SIZE,
    ST_READING_SIZE_ARG,
    ST_READ_SIZE
  } state = ST_READ_SPEC;
  cell retval;

  assert(format_ptr != NULL);
  assert(args != NULL);

  while (*format_ptr != '\0' && i < _SAMPGDK_NATIVE_MAX_ARGS) {
    switch (state) {
      case ST_READ_SPEC:
        switch (*format_ptr) {
          case 'i': /* integer */
          case 'd': /* integer */
            params[i + 1] = *(int *)args[i];
            break;
          case 'b': /* boolean */
            params[i + 1] = *(bool *)args[i];
            break;
          case 'f': /* floating-point */ {
            float value = *(float *)args[i];
            params[i + 1] = amx_ftoc(value);
            break;
          }
          case 'r': /* const reference */
          case 'R': /* non-const reference */ {
            cell *ptr = args[i];
            sampgdk_fakeamx_push_cell(*ptr, &params[i + 1]);
            size[i] = sizeof(cell);
            break;
          }
          case 's': /* const string */ {
            char *str = args[i];
            int str_size;
            sampgdk_fakeamx_push_string(str, &str_size, &params[i + 1]);
            size[i] = str_size;
            break;
          }
          case 'S': /* non-const string */
          case 'a': /* const array */
          case 'A': /* non-const array */
            needs_size = i;
            state = ST_NEED_SIZE;
            break;
          default:
            sampgdk_log_warning("Unrecognized type specifier '%c'", *format_ptr);
        }
        type[i++] = *format_ptr++;
        break;
      case ST_NEED_SIZE:
        if (*format_ptr == '[') {
          state = ST_READING_SIZE;
        } else {
          sampgdk_log_warning("Bad format string: expected '[' but got '%c'",
                              *format_ptr);
        }
        format_ptr++;
        break;
      case ST_READING_SIZE:
        if (*format_ptr == '*') {
          format_ptr++;
          state = ST_READING_SIZE_ARG;
        } else {
          size[needs_size] = (int)strtol(format_ptr, (char **)&format_ptr, 10);
          state = ST_READ_SIZE;
        }
        break;
      case ST_READING_SIZE_ARG: {
        int index = (int)strtol(format_ptr, (char **)&format_ptr, 10);
        size[needs_size] = *(int *)args[index];
        state = ST_READ_SIZE;
        break;
      }
      case ST_READ_SIZE: {
        if (*format_ptr == ']') {
          switch (type[needs_size]) {
            case 'a':
            case 'A':
            case 'S':
              if (size[needs_size] > 0) {
                sampgdk_fakeamx_push_array(args[needs_size], size[needs_size],
                                           &params[needs_size + 1]);
              } else {
                sampgdk_log_warning("Invalid buffer size");
              }
              break;
          }
          needs_size = -1;
          state = ST_READ_SPEC;
        } else {
          sampgdk_log_warning("Bad format string (expected ']' but got '%c')",
                              *format_ptr);
        }
        format_ptr++;
        break;
      }
    }
  }

  if (*format_ptr != '\0') {
    sampgdk_log_warning("Too many native arguments (at most %d allowed)",
                        _SAMPGDK_NATIVE_MAX_ARGS);
  }

  params[0] = i * sizeof(cell);
  assert(native != NULL);
  retval = native(amx, params);

  while (--i >= 0) {
    if (size[i] > 0) {
      /* If this is an output parameter we have to write the updated value
       * back to the argument.
       */
      switch (type[i]) {
        case 'R':
          sampgdk_fakeamx_get_cell(params[i + 1], args[i]);
          break;
        case 'S':
          sampgdk_fakeamx_get_string(params[i + 1], args[i], size[i]);
          break;
        case 'A':
          sampgdk_fakeamx_get_array(params[i + 1], args[i], size[i]);
          break;
      }
      sampgdk_fakeamx_pop(params[i + 1]);
    }
  }

  return retval;
}

/* Copyright (C) 2011-2015 Zeex
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

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "sampgdk.h"

/* #include "amx.h" */
/* #include "array.h" */
/* #include "callback.h" */
/* #include "fakeamx.h" */
/* #include "init.h" */
/* #include "log.h" */
/* #include "native.h" */
/* #include "param.h" */
/* #include "hook.h" */

static AMX *_sampgdk_amxhooks_main_amx;

#define _SAMPGDK_AMXHOOKS_FUNC_LIST(C) \
  C(Register) \
  C(FindPublic) \
  C(Exec) \
  C(Allot)

#define _SAMPGDK_AMXHOOKS_DEFINE_HOOK(name) \
  static sampgdk_hook_t _sampgdk_amxhooks_##name##_hook;
_SAMPGDK_AMXHOOKS_FUNC_LIST(_SAMPGDK_AMXHOOKS_DEFINE_HOOK)
#undef _SAMPGDK_AMXHOOKS_DEFINE_HOOK

/* The "funcidx" native uses amx_FindPublic() to get the public function's
 * index but our FindPublic always returns success regardless of the actual
 * result. So here's a fixed version.
 *
 * Thanks to Incognito for finding this bug!
 */
static cell AMX_NATIVE_CALL _sampgdk_amxhooks_funcidx(AMX *amx, cell *params) {
  char *funcname;
  int index;
  int error;

  amx_StrParam(amx, params[1], funcname);
  if (funcname == NULL) {
    return -1;
  }

  error = amx_FindPublic(amx, funcname, &index);
  if (error != AMX_ERR_NONE || index <= AMX_EXEC_GDK) {
    return -1;
  }

  return index;
}

static int AMXAPI _sampgdk_amxhooks_Register(AMX *amx,
                                             const AMX_NATIVE_INFO *nativelist,
                                             int number) {
  int i;
  AMX_HEADER *hdr;
  AMX_FUNCSTUBNT *natives;

  sampgdk_log_debug("amx_Register(%p, %p, %d)", amx, nativelist, number);

  hdr = (AMX_HEADER *)amx->base;
  natives = (AMX_FUNCSTUBNT *)(amx->base + hdr->natives);

  if (amx_FindNative(amx, "funcidx", &i) == AMX_ERR_NONE) {
    natives[i].address = (ucell)_sampgdk_amxhooks_funcidx;
  }

  for (i = 0; nativelist[i].name != 0 && (i < number || number == -1); i++) {
    sampgdk_log_debug("Registering native: %s @ %p", nativelist[i].name,
                                                     nativelist[i].func);
    sampgdk_native_register(nativelist[i].name, nativelist[i].func);
  }

  sampgdk_log_info("Registered %d natives", i);

  return SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_Register_hook, int, AMXAPI,
                              (amx, nativelist, number));
}

static int AMXAPI _sampgdk_amxhooks_FindPublic(AMX *amx,
                                               const char *name,
                                               int *index) {
  int error;
  int index_internal;
  int index_real;

  sampgdk_log_debug("amx_FindPublic(%p, \"%s\", %p)", amx, name, index);

  error = SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_FindPublic_hook, int, AMXAPI,
                               (amx, name, index));
  sampgdk_log_debug("amx_FindPublic returned %d", error);

  /* We are interested in intercepting public calls against the following
   * AMX instances:
   *
   * - the main AMX (the gamemode)
   * - the fake AMX (this is needed for HTTP() to work)
   */
  if (amx != _sampgdk_amxhooks_main_amx &&
      amx != sampgdk_fakeamx_amx()) {
    return error;
  }

  /* If the public was really found (and I mean REALLY) there's no need
   * to mess with the index.
   */
  if (error == AMX_ERR_NONE && *index >= 0) {
    return AMX_ERR_NONE;
  }

  /* OK, this public officially doesn't exist here. Register it in our
   * internal callback table and return success. The table will allow
   * us to keep track of forged publics in amx_Exec().
   */
  index_internal = sampgdk_callback_register(name, NULL);
  index_real = AMX_EXEC_GDK - index_internal;

  if (index_internal < 0) {
    sampgdk_log_error("Error registering callback: %s",
                      strerror(-index_internal));
  } else if (error == AMX_ERR_NONE && *index < 0) {
    /* If there are other plugins running they better return the same
     * index as we do. Otherwise it would be a total mess and we can't
     * let that happen.
     */
    if (*index != index_real) {
      error = AMX_ERR_NOTFOUND;
      sampgdk_log_warning("Index mismatch for %s (%d != %d)",
                          name, *index, index_real);
    }
  } else if (error != AMX_ERR_NONE) {
    error = AMX_ERR_NONE, *index = index_real;
    sampgdk_log_debug("Registered callback: %s, index = %d", name, *index);
  }

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Exec(AMX *amx, cell *retval, int index) {
  int paramcount;
  int error = AMX_ERR_NONE;
  bool do_exec = true;
  bool do_cleanup = false;

  sampgdk_log_debug("amx_Exec(%p, %p, %d), paramcount = %d, stk = %d",
      amx, retval, index, amx->paramcount, amx->stk);

  /* We have to reset amx->paramcount at this point so if the callback
   * itself calls amx_Exec() it won't pop our arguments off the stack.
   */
  paramcount = amx->paramcount;
  amx->paramcount = 0;

  /* Since filterscripts don't use main() we can assume that the AMX
   * that executes main() is indeed the main AMX i.e. the gamemode.
   */
  if (index == AMX_EXEC_MAIN) {
    /* This extra check is needed in order to stop OnGameModeInit()
     * from being called twice in a row after a gmx.
     */
    if (amx != NULL && _sampgdk_amxhooks_main_amx != amx) {
      _sampgdk_amxhooks_main_amx = amx;

      sampgdk_log_info("Found main AMX, callbacks work now");
      sampgdk_log_debug("Main AMX instance: %p", amx);

      /* For some odd reason OnGameModeInit() is called before main().
       * Normally callbacks are handled below but this creates an exception.
       */
      sampgdk_callback_invoke(amx, "OnGameModeInit", paramcount, retval);
    }
  } else if (index != AMX_EXEC_CONT && (amx == _sampgdk_amxhooks_main_amx ||
                                        amx == sampgdk_fakeamx_amx())) {
    char *name = NULL;

    if (index <= AMX_EXEC_GDK) {
      sampgdk_callback_get(AMX_EXEC_GDK - index, &name);
    } else {
      AMX *main_amx = _sampgdk_amxhooks_main_amx;
      AMX_FUNCSTUBNT *publics = (AMX_FUNCSTUBNT *)(main_amx->base +
          ((AMX_HEADER *)main_amx->base)->publics);
      name = (char *)(publics[index].nameofs + amx->base);
    }

    if (name != NULL) {
      do_exec = sampgdk_callback_invoke(amx, name, paramcount, retval);
    } else {
      sampgdk_log_warning("Unknown callback, index = %d", index);
    }
  }

  if (do_exec) {
    amx->paramcount = paramcount;
    error = SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_Exec_hook, int, AMXAPI,
                                 (amx, retval, index));
    sampgdk_log_debug("amx_Exec returned %d", error);
  }

  /* Suppress the error and also let the other plugin(s) know that we
   * handle the cleanup (see below).
   */
  if (error == AMX_ERR_INDEX && index <= AMX_EXEC_GDK) {
    error = AMX_ERR_NONE;
    do_cleanup = true;
  }

  /* Someone has to clean things up if amx_Exec() didn't run after all.
   */
  if (!do_exec || do_cleanup) {
    amx->paramcount = 0;
    amx->stk += paramcount * sizeof(cell);
    sampgdk_log_debug("Popped %d parameter(s), stk = %d", paramcount, amx->stk);
  }

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Allot(AMX *amx,
                                          int cells,
                                          cell *amx_addr,
                                          cell **phys_addr) {
  int error;

  sampgdk_log_debug("amx_Allot(%p, %d, %p, %p)", amx, cells, amx_addr,
                                                 phys_addr);

  /* There is a bug in amx_Allot() where it returns success even though
   * there's not enough space on the heap:
   *
   * if (amx->stk - amx->hea - cells*sizeof(cell) < STKMARGIN)
   *   return AMX_ERR_MEMORY;
   *
   * The expression on the left is always positive because of the conversion
   * to size_t, which is unsigned.
   *
   * The code below code should fix this.
   */
  #define STKMARGIN (cell)(16 * sizeof(cell))
  if ((size_t)amx->stk < (size_t)(amx->hea + cells*sizeof(cell) + STKMARGIN)) {
    error =  AMX_ERR_MEMORY;
  } else {
    error = SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_Allot_hook, int, AMXAPI,
                                 (amx, cells, amx_addr, phys_addr));
    sampgdk_log_debug("amx_Allot returned %d", error);
  }

  /* If called against the fake AMX and failed to allocate the requested
   * amount of space, grow the heap and try again.
   */
  if (error == AMX_ERR_MEMORY && amx == sampgdk_fakeamx_amx()) {
    cell new_size = ((amx->hea + STKMARGIN) / sizeof(cell)) + cells + 2;
    cell resize;

    sampgdk_log_debug("Growing fake AMX heap to %d bytes = %d = %d", new_size);
    resize = sampgdk_fakeamx_resize_heap(new_size);

    if (resize >= 0) {
      error = SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_Allot_hook, int, AMXAPI,
                                   (amx, cells, amx_addr, phys_addr));
    }
  }

  return error;
}

static int _sampgdk_amxhooks_create(void) {
  #define _SAMPGDK_AMXHOOKS_CREATE_HOOK(name) \
    if ((_sampgdk_amxhooks_##name##_hook = \
        sampgdk_hook_new((void *)sampgdk_amx_api_ptr->name, \
                         (void *)_sampgdk_amxhooks_##name)) == NULL) \
      goto no_memory;
  _SAMPGDK_AMXHOOKS_FUNC_LIST(_SAMPGDK_AMXHOOKS_CREATE_HOOK)
  return 0;
no_memory:
  return -ENOMEM;
  #undef _SAMPGDK_AMXHOOKS_CREATE_HOOK
}

static void _sampgdk_amxhooks_destroy(void) {
  #define _SAMPGDK_AMXHOOKS_DESTROY_HOOK(name) \
    sampgdk_hook_free(_sampgdk_amxhooks_##name##_hook);
  _SAMPGDK_AMXHOOKS_FUNC_LIST(_SAMPGDK_AMXHOOKS_DESTROY_HOOK)
  #undef _SAMPGDK_AMXHOOKS_DESTROY_HOOK
}

SAMPGDK_MODULE_INIT(amxhooks) {
  int error;

  error = _sampgdk_amxhooks_create();
  if (error < 0) {
    _sampgdk_amxhooks_destroy();
    return error;
  }

  return 0;
}

SAMPGDK_MODULE_CLEANUP(amxhooks) {
  _sampgdk_amxhooks_destroy();
}

/* Copyright (C) 2011-2015 Zeex
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

#include "sampgdk.h"

SAMPGDK_API(int, sampgdk_GetVersion(void)) {
  return SAMPGDK_VERSION_ID;
}

SAMPGDK_API(const char *, sampgdk_GetVersionString(void)) {
  return SAMPGDK_VERSION_STRING;
}

/* Copyright (C) 2011-2015 Zeex
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

#include <assert.h>
#include <string.h>

#include "sampgdk.h"

/* #include "internal/amx.h" */
/* #include "internal/init.h" */
/* #include "internal/log.h" */
/* #include "internal/logprintf.h" */
/* #include "internal/plugin.h" */
/* #include "internal/timer.h" */

#undef sampgdk_Load
#undef sampgdk_Unload
#undef sampgdk_ProcessTick

#ifdef _MSC_VER
  #define _SAMPGDK_RETURN_ADDRESS() _ReturnAddress()
#else
  #define _SAMPGDK_RETURN_ADDRESS() __builtin_return_address(0)
#endif

#ifdef SAMPGDK_EMBEDDED
  #define _SAMPGDK_CALLER_HANDLE() \
    sampgdk_plugin_get_handle(((void *)_sampgdk_init))
#else
  #define _SAMPGDK_CALLER_HANDLE() \
    sampgdk_plugin_get_handle(_SAMPGDK_RETURN_ADDRESS())
#endif

static void _sampgdk_init(void **plugin_data) {
  int error;

  sampgdk_logprintf_impl = plugin_data[PLUGIN_DATA_LOGPRINTF];
  sampgdk_amx_api_ptr = plugin_data[PLUGIN_DATA_AMX_EXPORTS];

  error = sampgdk_module_init();
  if (error  < 0) {
    sampgdk_log_error("Initialization failed: %s", error);
  }
}

static int _sampgdk_init_plugin(void *plugin, void **plugin_data) {
  int error;
  int num_plugins;

  assert(plugin != NULL);

  (void)sampgdk_plugin_get_plugins(&num_plugins);
  if (num_plugins == 0) {
    _sampgdk_init(plugin_data);
  }

  error = sampgdk_plugin_register(plugin);
  if (error < 0) {
    sampgdk_log_error("Error registering plugin: %s", strerror(-error));
  }

  return error;
}

static void _sampgdk_cleanup(void) {
  sampgdk_module_cleanup();
}

static void _sampgdk_cleanup_plugin(void *plugin) {
  int error;
  int num_plugins;

  assert(plugin != NULL);

  error = sampgdk_plugin_unregister(plugin);
  if (error < 0) {
    sampgdk_log_error("Error unregistering plugin: %s", strerror(-error));
  }

  (void)sampgdk_plugin_get_plugins(&num_plugins);
  if (num_plugins == 0) {
    _sampgdk_cleanup();
  }
}

SAMPGDK_API(unsigned int, sampgdk_Supports(void)) {
  return SUPPORTS_VERSION;
}

SAMPGDK_API(bool, sampgdk_Load(void **ppData, sampgdk_hidden_t hidden)) {
  return _sampgdk_init_plugin(_SAMPGDK_CALLER_HANDLE(), ppData) >= 0;
}

SAMPGDK_API(void, sampgdk_Unload(sampgdk_hidden_t hidden)) {
  _sampgdk_cleanup_plugin(_SAMPGDK_CALLER_HANDLE());
}

SAMPGDK_API(void, sampgdk_ProcessTick(sampgdk_hidden_t hidden)) {
  sampgdk_timer_process_timers(_SAMPGDK_CALLER_HANDLE());
}

SAMPGDK_API(void, sampgdk_logprintf(const char *format, ...)) {
  va_list args;
  va_start(args, format);
  sampgdk_do_vlogprintf(format, args);
  va_end(args);
}

SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args)) {
  sampgdk_do_vlogprintf(format, args);
}

/* Copyright (C) 2012-2015 Zeex
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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sampgdk.h"

#if SAMPGDK_WINDOWS
  #include <windows.h>
#endif

/* #include "array.h" */
/* #include "init.h" */
/* #include "log.h" */
/* #include "plugin.h" */
/* #include "timer.h" */
/* #include "types.h" */

struct _sampgdk_timer_info {
  bool    is_set;
  void   *plugin;
  int64_t started;
  int     interval;
  void   *callback;
  void   *param;
  bool    repeat;
};

static struct sampgdk_array _sampgdk_timers;

#if SAMPGDK_WINDOWS

static int64_t _sampgdk_timer_now(void) {
  LARGE_INTEGER freq;
  LARGE_INTEGER counter;

  if (QueryPerformanceFrequency(&freq) == 0) {
    sampgdk_log_error("QueryPerformanceFrequency: error %d", GetLastError());
    return 0;
  }
  if (QueryPerformanceCounter(&counter) == 0) {
    sampgdk_log_error("QueryPerformanceCounter: error %d", GetLastError());
    return 0;
  }

  return (int64_t)(1000.0L / freq.QuadPart * counter.QuadPart);
}

#else /* SAMPGDK_WINDOWS */

static int64_t _sampgdk_timer_now(void) {
  struct timespec ts;
  int64_t msec;
  int64_t msec_fract;

  if (clock_gettime(CLOCK_MONOTONIC, &ts) < 0) {
    sampgdk_log_error("clock_gettime: %s", strerror(errno));
    return 0;
  }

  msec = (int64_t)ts.tv_sec * 1000;
  msec_fract = (int64_t)ts.tv_nsec / 1000000L;

  return msec + msec_fract;
}

#endif /* !SAMPGDK_WINDOWS */

static int _sampgdk_timer_find_slot(void) {
  int i;

  for (i = 0; i < _sampgdk_timers.count; i++) {
    struct _sampgdk_timer_info *timer;

    timer = sampgdk_array_get(&_sampgdk_timers, i);
    if (!timer->is_set) {
      return i;
    }
  }

  return -1;
}

static void _sampgdk_timer_fire(int timerid, int64_t elapsed) {
  struct _sampgdk_timer_info *timer;
  int64_t now = _sampgdk_timer_now();
  int64_t started;

  assert(timerid > 0 && timerid <= _sampgdk_timers.count);
  timer = sampgdk_array_get(&_sampgdk_timers, timerid - 1);

  assert(timer->is_set);
  started = timer->started;

  sampgdk_log_debug("Firing timer %d, now = %"PRId64", elapsed = %"PRId64,
      timerid, now, elapsed);
  ((sampgdk_timer_callback)timer->callback)(timerid, timer->param);

  /* We don't want to kill the same timer twice, so make sure it's not
   * been killed inside the timer callback.
   */
  if (timer->is_set && timer->started == started) {
    if (timer->repeat) {
      timer->started = now - (elapsed - timer->interval);
    } else {
      sampgdk_timer_kill(timerid);
    }
  }
}

SAMPGDK_MODULE_INIT(timer) {
  int error;

  error = sampgdk_array_new(&_sampgdk_timers,
                            10,
                            sizeof(struct _sampgdk_timer_info));
  if (error < 0) {
    return error;
  }

  sampgdk_array_zero(&_sampgdk_timers);

  return 0;
}

SAMPGDK_MODULE_CLEANUP(timer) {
  sampgdk_array_free(&_sampgdk_timers);
}

int sampgdk_timer_set(int interval,
                      bool repeat,
                      sampgdk_timer_callback callback,
                      void *param) {
  struct _sampgdk_timer_info timer;
  int slot;
  int error;
  int timerid;

  assert(callback != NULL);

  timer.is_set   = true;
  timer.interval = interval;
  timer.repeat   = repeat;
  timer.callback = callback;
  timer.param    = param;
  timer.started  = _sampgdk_timer_now();
  timer.plugin   = sampgdk_plugin_get_handle(callback);

  if (timer.started == 0) {
    return 0; /* error already logged */
  }

  slot = _sampgdk_timer_find_slot();
  if (slot >= 0) {
    sampgdk_array_set(&_sampgdk_timers, slot, &timer);
  } else {
    error = sampgdk_array_append(&_sampgdk_timers, &timer);
    if (error < 0) {
      sampgdk_log_error("Error setting timer: %s", strerror(-error));
      return 0;
    }
    slot = _sampgdk_timers.count - 1;
  }

  /* Timer IDs returned by the SA:MP's SetTimer() API begin
   * with 1, and so do they here.
   */
  timerid = slot + 1;

  sampgdk_log_debug("Created timer: ID = %d, interval = %d, repeat = %s",
      timerid, interval, repeat ? "true" : "false");

  return timerid;
}

int sampgdk_timer_kill(int timerid) {
  struct _sampgdk_timer_info *timer;

  if (timerid <= 0 || timerid > _sampgdk_timers.count) {
    return -EINVAL;
  }

  timer = sampgdk_array_get(&_sampgdk_timers, timerid - 1);
  if (!timer->is_set) {
    return -EINVAL;
  }

  timer->is_set = false;

  sampgdk_log_debug("Killed timer %d", timerid);

  return 0;
}

void sampgdk_timer_process_timers(void *plugin) {
  int64_t now;
  int64_t elapsed;
  int i;
  struct _sampgdk_timer_info *timer;

  assert(plugin != NULL);

  now = _sampgdk_timer_now();

  for (i = 0; i < _sampgdk_timers.count; i++) {
    timer = sampgdk_array_get(&_sampgdk_timers, i);

    if (!timer->is_set
        || (plugin != NULL && timer->plugin != plugin)) {
      continue;
    }

    elapsed = now - timer->started;

    if (elapsed >= timer->interval) {
      _sampgdk_timer_fire(i + 1, elapsed);
    }
  }
}

#include "sampgdk.h"

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/log.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(bool, SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[14];
  sampgdk_log_debug("SetSpawnInfo(%d, %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d)", playerid, team, skin, x, y, z, rotation, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
  native = sampgdk_native_find_flexible("SetSpawnInfo", native);
  params[0] = 13 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)team;
  params[3] = (cell)skin;
  params[4] = amx_ftoc(x);
  params[5] = amx_ftoc(y);
  params[6] = amx_ftoc(z);
  params[7] = amx_ftoc(rotation);
  params[8] = (cell)weapon1;
  params[9] = (cell)weapon1_ammo;
  params[10] = (cell)weapon2;
  params[11] = (cell)weapon2_ammo;
  params[12] = (cell)weapon3;
  params[13] = (cell)weapon3_ammo;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SpawnPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SpawnPlayer(%d)", playerid);
  native = sampgdk_native_find_flexible("SpawnPlayer", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerPos(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetPlayerPos(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("SetPlayerPos", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerPosFindZ(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetPlayerPosFindZ(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("SetPlayerPosFindZ", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerPos(int playerid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetPlayerPos(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("GetPlayerPos", native);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = x_;
  params[3] = y_;
  params[4] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerFacingAngle(int playerid, float angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerFacingAngle(%d, %f)", playerid, angle);
  native = sampgdk_native_find_flexible("SetPlayerFacingAngle", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(angle);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerFacingAngle(int playerid, float * angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell angle_;
  sampgdk_log_debug("GetPlayerFacingAngle(%d, %f)", playerid, angle);
  native = sampgdk_native_find_flexible("GetPlayerFacingAngle", native);
  sampgdk_fakeamx_push(1, &angle_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = angle_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(angle_, angle);
  sampgdk_fakeamx_pop(angle_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("IsPlayerInRangeOfPoint(%d, %f, %f, %f, %f)", playerid, range, x, y, z);
  native = sampgdk_native_find_flexible("IsPlayerInRangeOfPoint", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(range);
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(float, GetPlayerDistanceFromPoint(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("GetPlayerDistanceFromPoint(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("GetPlayerDistanceFromPoint", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerStreamedIn(int playerid, int forplayerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("IsPlayerStreamedIn(%d, %d)", playerid, forplayerid);
  native = sampgdk_native_find_flexible("IsPlayerStreamedIn", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)forplayerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerInterior(int playerid, int interiorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerInterior(%d, %d)", playerid, interiorid);
  native = sampgdk_native_find_flexible("SetPlayerInterior", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)interiorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerInterior(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerInterior(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerInterior", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerHealth(int playerid, float health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerHealth(%d, %f)", playerid, health);
  native = sampgdk_native_find_flexible("SetPlayerHealth", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(health);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerHealth(int playerid, float * health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell health_;
  sampgdk_log_debug("GetPlayerHealth(%d, %f)", playerid, health);
  native = sampgdk_native_find_flexible("GetPlayerHealth", native);
  sampgdk_fakeamx_push(1, &health_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = health_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(health_, health);
  sampgdk_fakeamx_pop(health_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerArmour(int playerid, float armour)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerArmour(%d, %f)", playerid, armour);
  native = sampgdk_native_find_flexible("SetPlayerArmour", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(armour);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerArmour(int playerid, float * armour)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell armour_;
  sampgdk_log_debug("GetPlayerArmour(%d, %f)", playerid, armour);
  native = sampgdk_native_find_flexible("GetPlayerArmour", native);
  sampgdk_fakeamx_push(1, &armour_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = armour_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(armour_, armour);
  sampgdk_fakeamx_pop(armour_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerAmmo(int playerid, int weaponid, int ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("SetPlayerAmmo(%d, %d, %d)", playerid, weaponid, ammo);
  native = sampgdk_native_find_flexible("SetPlayerAmmo", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)weaponid;
  params[3] = (cell)ammo;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerAmmo(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerAmmo(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerAmmo", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerWeaponState(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerWeaponState(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerWeaponState", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerTargetPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerTargetPlayer(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerTargetPlayer", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerTargetActor(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerTargetActor(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerTargetActor", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerTeam(int playerid, int teamid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerTeam(%d, %d)", playerid, teamid);
  native = sampgdk_native_find_flexible("SetPlayerTeam", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)teamid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerTeam(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerTeam(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerTeam", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerScore(int playerid, int score)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerScore(%d, %d)", playerid, score);
  native = sampgdk_native_find_flexible("SetPlayerScore", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)score;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerScore(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerScore(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerScore", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerDrunkLevel(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerDrunkLevel(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerDrunkLevel", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerDrunkLevel(int playerid, int level)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerDrunkLevel(%d, %d)", playerid, level);
  native = sampgdk_native_find_flexible("SetPlayerDrunkLevel", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)level;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerColor(int playerid, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerColor(%d, %d)", playerid, color);
  native = sampgdk_native_find_flexible("SetPlayerColor", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerColor(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerColor(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerColor", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerSkin(int playerid, int skinid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerSkin(%d, %d)", playerid, skinid);
  native = sampgdk_native_find_flexible("SetPlayerSkin", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)skinid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerSkin(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerSkin(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerSkin", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GivePlayerWeapon(int playerid, int weaponid, int ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("GivePlayerWeapon(%d, %d, %d)", playerid, weaponid, ammo);
  native = sampgdk_native_find_flexible("GivePlayerWeapon", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)weaponid;
  params[3] = (cell)ammo;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ResetPlayerWeapons(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("ResetPlayerWeapons(%d)", playerid);
  native = sampgdk_native_find_flexible("ResetPlayerWeapons", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerArmedWeapon(int playerid, int weaponid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerArmedWeapon(%d, %d)", playerid, weaponid);
  native = sampgdk_native_find_flexible("SetPlayerArmedWeapon", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)weaponid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerWeaponData(int playerid, int slot, int * weapon, int * ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell weapon_;
  cell ammo_;
  sampgdk_log_debug("GetPlayerWeaponData(%d, %d, %d, %d)", playerid, slot, weapon, ammo);
  native = sampgdk_native_find_flexible("GetPlayerWeaponData", native);
  sampgdk_fakeamx_push(1, &weapon_);
  sampgdk_fakeamx_push(1, &ammo_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)slot;
  params[3] = weapon_;
  params[4] = ammo_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_cell(weapon_, weapon);
  sampgdk_fakeamx_get_cell(ammo_, ammo);
  sampgdk_fakeamx_pop(ammo_);
  sampgdk_fakeamx_pop(weapon_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GivePlayerMoney(int playerid, int money)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("GivePlayerMoney(%d, %d)", playerid, money);
  native = sampgdk_native_find_flexible("GivePlayerMoney", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)money;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ResetPlayerMoney(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("ResetPlayerMoney(%d)", playerid);
  native = sampgdk_native_find_flexible("ResetPlayerMoney", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, SetPlayerName(int playerid, const char * name)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell name_;
  sampgdk_log_debug("SetPlayerName(%d, \"%s\")", playerid, name);
  native = sampgdk_native_find_flexible("SetPlayerName", native);
  sampgdk_fakeamx_push_string(name, NULL, &name_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = name_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(name_);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerMoney(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerMoney(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerMoney", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerState(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerState(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerState", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerIp(int playerid, char * ip, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell ip_;
  sampgdk_log_debug("GetPlayerIp(%d, \"%s\", %d)", playerid, ip, size);
  native = sampgdk_native_find_flexible("GetPlayerIp", native);
  sampgdk_fakeamx_push(size, &ip_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = ip_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(ip_, ip, size);
  sampgdk_fakeamx_pop(ip_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerPing(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerPing(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerPing", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerWeapon(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerWeapon(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerWeapon", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerKeys(int playerid, int * keys, int * updown, int * leftright)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell keys_;
  cell updown_;
  cell leftright_;
  sampgdk_log_debug("GetPlayerKeys(%d, %d, %d, %d)", playerid, keys, updown, leftright);
  native = sampgdk_native_find_flexible("GetPlayerKeys", native);
  sampgdk_fakeamx_push(1, &keys_);
  sampgdk_fakeamx_push(1, &updown_);
  sampgdk_fakeamx_push(1, &leftright_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = keys_;
  params[3] = updown_;
  params[4] = leftright_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_cell(keys_, keys);
  sampgdk_fakeamx_get_cell(updown_, updown);
  sampgdk_fakeamx_get_cell(leftright_, leftright);
  sampgdk_fakeamx_pop(leftright_);
  sampgdk_fakeamx_pop(updown_);
  sampgdk_fakeamx_pop(keys_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerName(int playerid, char * name, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell name_;
  sampgdk_log_debug("GetPlayerName(%d, \"%s\", %d)", playerid, name, size);
  native = sampgdk_native_find_flexible("GetPlayerName", native);
  sampgdk_fakeamx_push(size, &name_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = name_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(name_, name, size);
  sampgdk_fakeamx_pop(name_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerTime(int playerid, int hour, int minute)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("SetPlayerTime(%d, %d, %d)", playerid, hour, minute);
  native = sampgdk_native_find_flexible("SetPlayerTime", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)hour;
  params[3] = (cell)minute;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerTime(int playerid, int * hour, int * minute)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell hour_;
  cell minute_;
  sampgdk_log_debug("GetPlayerTime(%d, %d, %d)", playerid, hour, minute);
  native = sampgdk_native_find_flexible("GetPlayerTime", native);
  sampgdk_fakeamx_push(1, &hour_);
  sampgdk_fakeamx_push(1, &minute_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = hour_;
  params[3] = minute_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_cell(hour_, hour);
  sampgdk_fakeamx_get_cell(minute_, minute);
  sampgdk_fakeamx_pop(minute_);
  sampgdk_fakeamx_pop(hour_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TogglePlayerClock(int playerid, bool toggle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TogglePlayerClock(%d, %d)", playerid, toggle);
  native = sampgdk_native_find_flexible("TogglePlayerClock", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)toggle;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerWeather(int playerid, int weather)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerWeather(%d, %d)", playerid, weather);
  native = sampgdk_native_find_flexible("SetPlayerWeather", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)weather;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ForceClassSelection(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("ForceClassSelection(%d)", playerid);
  native = sampgdk_native_find_flexible("ForceClassSelection", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerWantedLevel(int playerid, int level)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerWantedLevel(%d, %d)", playerid, level);
  native = sampgdk_native_find_flexible("SetPlayerWantedLevel", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)level;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerWantedLevel(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerWantedLevel(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerWantedLevel", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerFightingStyle(int playerid, int style)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerFightingStyle(%d, %d)", playerid, style);
  native = sampgdk_native_find_flexible("SetPlayerFightingStyle", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)style;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerFightingStyle(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerFightingStyle(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerFightingStyle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerVelocity(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetPlayerVelocity(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("SetPlayerVelocity", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerVelocity(int playerid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetPlayerVelocity(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("GetPlayerVelocity", native);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = x_;
  params[3] = y_;
  params[4] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayCrimeReportForPlayer(int playerid, int suspectid, int crime)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayCrimeReportForPlayer(%d, %d, %d)", playerid, suspectid, crime);
  native = sampgdk_native_find_flexible("PlayCrimeReportForPlayer", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)suspectid;
  params[3] = (cell)crime;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayAudioStreamForPlayer(int playerid, const char * url, float posX, float posY, float posZ, float distance, bool usepos)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[8];
  cell url_;
  sampgdk_log_debug("PlayAudioStreamForPlayer(%d, \"%s\", %f, %f, %f, %f, %d)", playerid, url, posX, posY, posZ, distance, usepos);
  native = sampgdk_native_find_flexible("PlayAudioStreamForPlayer", native);
  sampgdk_fakeamx_push_string(url, NULL, &url_);
  params[0] = 7 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = url_;
  params[3] = amx_ftoc(posX);
  params[4] = amx_ftoc(posY);
  params[5] = amx_ftoc(posZ);
  params[6] = amx_ftoc(distance);
  params[7] = (cell)usepos;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(url_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, StopAudioStreamForPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("StopAudioStreamForPlayer(%d)", playerid);
  native = sampgdk_native_find_flexible("StopAudioStreamForPlayer", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerShopName(int playerid, const char * shopname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell shopname_;
  sampgdk_log_debug("SetPlayerShopName(%d, \"%s\")", playerid, shopname);
  native = sampgdk_native_find_flexible("SetPlayerShopName", native);
  sampgdk_fakeamx_push_string(shopname, NULL, &shopname_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = shopname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(shopname_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerSkillLevel(int playerid, int skill, int level)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("SetPlayerSkillLevel(%d, %d, %d)", playerid, skill, level);
  native = sampgdk_native_find_flexible("SetPlayerSkillLevel", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)skill;
  params[3] = (cell)level;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerSurfingVehicleID(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerSurfingVehicleID(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerSurfingVehicleID", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerSurfingObjectID(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerSurfingObjectID(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerSurfingObjectID", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  sampgdk_log_debug("RemoveBuildingForPlayer(%d, %d, %f, %f, %f, %f)", playerid, modelid, fX, fY, fZ, fRadius);
  native = sampgdk_native_find_flexible("RemoveBuildingForPlayer", native);
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)modelid;
  params[3] = amx_ftoc(fX);
  params[4] = amx_ftoc(fY);
  params[5] = amx_ftoc(fZ);
  params[6] = amx_ftoc(fRadius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerLastShotVectors(int playerid, float * fOriginX, float * fOriginY, float * fOriginZ, float * fHitPosX, float * fHitPosY, float * fHitPosZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[8];
  cell fOriginX_;
  cell fOriginY_;
  cell fOriginZ_;
  cell fHitPosX_;
  cell fHitPosY_;
  cell fHitPosZ_;
  sampgdk_log_debug("GetPlayerLastShotVectors(%d, %f, %f, %f, %f, %f, %f)", playerid, fOriginX, fOriginY, fOriginZ, fHitPosX, fHitPosY, fHitPosZ);
  native = sampgdk_native_find_flexible("GetPlayerLastShotVectors", native);
  sampgdk_fakeamx_push(1, &fOriginX_);
  sampgdk_fakeamx_push(1, &fOriginY_);
  sampgdk_fakeamx_push(1, &fOriginZ_);
  sampgdk_fakeamx_push(1, &fHitPosX_);
  sampgdk_fakeamx_push(1, &fHitPosY_);
  sampgdk_fakeamx_push(1, &fHitPosZ_);
  params[0] = 7 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = fOriginX_;
  params[3] = fOriginY_;
  params[4] = fOriginZ_;
  params[5] = fHitPosX_;
  params[6] = fHitPosY_;
  params[7] = fHitPosZ_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(fOriginX_, fOriginX);
  sampgdk_fakeamx_get_float(fOriginY_, fOriginY);
  sampgdk_fakeamx_get_float(fOriginZ_, fOriginZ);
  sampgdk_fakeamx_get_float(fHitPosX_, fHitPosX);
  sampgdk_fakeamx_get_float(fHitPosY_, fHitPosY);
  sampgdk_fakeamx_get_float(fHitPosZ_, fHitPosZ);
  sampgdk_fakeamx_pop(fHitPosZ_);
  sampgdk_fakeamx_pop(fHitPosY_);
  sampgdk_fakeamx_pop(fHitPosX_);
  sampgdk_fakeamx_pop(fOriginZ_);
  sampgdk_fakeamx_pop(fOriginY_);
  sampgdk_fakeamx_pop(fOriginX_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ, int materialcolor1, int materialcolor2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[16];
  sampgdk_log_debug("SetPlayerAttachedObject(%d, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d, %d)", playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2);
  native = sampgdk_native_find_flexible("SetPlayerAttachedObject", native);
  params[0] = 15 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  params[3] = (cell)modelid;
  params[4] = (cell)bone;
  params[5] = amx_ftoc(fOffsetX);
  params[6] = amx_ftoc(fOffsetY);
  params[7] = amx_ftoc(fOffsetZ);
  params[8] = amx_ftoc(fRotX);
  params[9] = amx_ftoc(fRotY);
  params[10] = amx_ftoc(fRotZ);
  params[11] = amx_ftoc(fScaleX);
  params[12] = amx_ftoc(fScaleY);
  params[13] = amx_ftoc(fScaleZ);
  params[14] = (cell)materialcolor1;
  params[15] = (cell)materialcolor2;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, RemovePlayerAttachedObject(int playerid, int index)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("RemovePlayerAttachedObject(%d, %d)", playerid, index);
  native = sampgdk_native_find_flexible("RemovePlayerAttachedObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerAttachedObjectSlotUsed(int playerid, int index)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("IsPlayerAttachedObjectSlotUsed(%d, %d)", playerid, index);
  native = sampgdk_native_find_flexible("IsPlayerAttachedObjectSlotUsed", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, EditAttachedObject(int playerid, int index)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("EditAttachedObject(%d, %d)", playerid, index);
  native = sampgdk_native_find_flexible("EditAttachedObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, CreatePlayerTextDraw(int playerid, float x, float y, const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell text_;
  sampgdk_log_debug("CreatePlayerTextDraw(%d, %f, %f, \"%s\")", playerid, x, y, text);
  native = sampgdk_native_find_flexible("CreatePlayerTextDraw", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = text_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawDestroy(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("PlayerTextDrawDestroy(%d, %d)", playerid, text);
  native = sampgdk_native_find_flexible("PlayerTextDrawDestroy", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawLetterSize(int playerid, int text, float x, float y)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("PlayerTextDrawLetterSize(%d, %d, %f, %f)", playerid, text, x, y);
  native = sampgdk_native_find_flexible("PlayerTextDrawLetterSize", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawTextSize(int playerid, int text, float x, float y)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("PlayerTextDrawTextSize(%d, %d, %f, %f)", playerid, text, x, y);
  native = sampgdk_native_find_flexible("PlayerTextDrawTextSize", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawAlignment(int playerid, int text, int alignment)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawAlignment(%d, %d, %d)", playerid, text, alignment);
  native = sampgdk_native_find_flexible("PlayerTextDrawAlignment", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)alignment;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawColor(int playerid, int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawColor(%d, %d, %d)", playerid, text, color);
  native = sampgdk_native_find_flexible("PlayerTextDrawColor", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawUseBox(int playerid, int text, bool use)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawUseBox(%d, %d, %d)", playerid, text, use);
  native = sampgdk_native_find_flexible("PlayerTextDrawUseBox", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)use;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawBoxColor(int playerid, int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawBoxColor(%d, %d, %d)", playerid, text, color);
  native = sampgdk_native_find_flexible("PlayerTextDrawBoxColor", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetShadow(int playerid, int text, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawSetShadow(%d, %d, %d)", playerid, text, size);
  native = sampgdk_native_find_flexible("PlayerTextDrawSetShadow", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetOutline(int playerid, int text, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawSetOutline(%d, %d, %d)", playerid, text, size);
  native = sampgdk_native_find_flexible("PlayerTextDrawSetOutline", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawBackgroundColor(int playerid, int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawBackgroundColor(%d, %d, %d)", playerid, text, color);
  native = sampgdk_native_find_flexible("PlayerTextDrawBackgroundColor", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawFont(int playerid, int text, int font)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawFont(%d, %d, %d)", playerid, text, font);
  native = sampgdk_native_find_flexible("PlayerTextDrawFont", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)font;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetProportional(int playerid, int text, bool set)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawSetProportional(%d, %d, %d)", playerid, text, set);
  native = sampgdk_native_find_flexible("PlayerTextDrawSetProportional", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)set;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetSelectable(int playerid, int text, bool set)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawSetSelectable(%d, %d, %d)", playerid, text, set);
  native = sampgdk_native_find_flexible("PlayerTextDrawSetSelectable", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)set;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawShow(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("PlayerTextDrawShow(%d, %d)", playerid, text);
  native = sampgdk_native_find_flexible("PlayerTextDrawShow", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawHide(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("PlayerTextDrawHide(%d, %d)", playerid, text);
  native = sampgdk_native_find_flexible("PlayerTextDrawHide", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetString(int playerid, int text, const char * string)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell string_;
  sampgdk_log_debug("PlayerTextDrawSetString(%d, %d, \"%s\")", playerid, text, string);
  native = sampgdk_native_find_flexible("PlayerTextDrawSetString", native);
  sampgdk_fakeamx_push_string(string, NULL, &string_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = string_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(string_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewModel(int playerid, int text, int modelindex)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerTextDrawSetPreviewModel(%d, %d, %d)", playerid, text, modelindex);
  native = sampgdk_native_find_flexible("PlayerTextDrawSetPreviewModel", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)modelindex;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewRot(int playerid, int text, float fRotX, float fRotY, float fRotZ, float fZoom)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  sampgdk_log_debug("PlayerTextDrawSetPreviewRot(%d, %d, %f, %f, %f, %f)", playerid, text, fRotX, fRotY, fRotZ, fZoom);
  native = sampgdk_native_find_flexible("PlayerTextDrawSetPreviewRot", native);
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = amx_ftoc(fRotX);
  params[4] = amx_ftoc(fRotY);
  params[5] = amx_ftoc(fRotZ);
  params[6] = amx_ftoc(fZoom);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewVehCol(int playerid, int text, int color1, int color2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("PlayerTextDrawSetPreviewVehCol(%d, %d, %d, %d)", playerid, text, color1, color2);
  native = sampgdk_native_find_flexible("PlayerTextDrawSetPreviewVehCol", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)color1;
  params[4] = (cell)color2;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPVarInt(int playerid, const char * varname, int value)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell varname_;
  sampgdk_log_debug("SetPVarInt(%d, \"%s\", %d)", playerid, varname, value);
  native = sampgdk_native_find_flexible("SetPVarInt", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  params[3] = (cell)value;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPVarInt(int playerid, const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell varname_;
  sampgdk_log_debug("GetPVarInt(%d, \"%s\")", playerid, varname);
  native = sampgdk_native_find_flexible("GetPVarInt", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPVarString(int playerid, const char * varname, const char * value)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell varname_;
  cell value_;
  sampgdk_log_debug("SetPVarString(%d, \"%s\", \"%s\")", playerid, varname, value);
  native = sampgdk_native_find_flexible("SetPVarString", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  sampgdk_fakeamx_push_string(value, NULL, &value_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  params[3] = value_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(value_);
  sampgdk_fakeamx_pop(varname_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPVarString(int playerid, const char * varname, char * value, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell varname_;
  cell value_;
  sampgdk_log_debug("GetPVarString(%d, \"%s\", \"%s\", %d)", playerid, varname, value, size);
  native = sampgdk_native_find_flexible("GetPVarString", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  sampgdk_fakeamx_push(size, &value_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  params[3] = value_;
  params[4] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(value_, value, size);
  sampgdk_fakeamx_pop(value_);
  sampgdk_fakeamx_pop(varname_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPVarFloat(int playerid, const char * varname, float value)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell varname_;
  sampgdk_log_debug("SetPVarFloat(%d, \"%s\", %f)", playerid, varname, value);
  native = sampgdk_native_find_flexible("SetPVarFloat", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  params[3] = amx_ftoc(value);
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return !!(retval);
}

SAMPGDK_NATIVE(float, GetPVarFloat(int playerid, const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell varname_;
  sampgdk_log_debug("GetPVarFloat(%d, \"%s\")", playerid, varname);
  native = sampgdk_native_find_flexible("GetPVarFloat", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(bool, DeletePVar(int playerid, const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell varname_;
  sampgdk_log_debug("DeletePVar(%d, \"%s\")", playerid, varname);
  native = sampgdk_native_find_flexible("DeletePVar", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPVarsUpperIndex(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPVarsUpperIndex(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPVarsUpperIndex", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GetPVarNameAtIndex(int playerid, int index, char * varname, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell varname_;
  sampgdk_log_debug("GetPVarNameAtIndex(%d, %d, \"%s\", %d)", playerid, index, varname, size);
  native = sampgdk_native_find_flexible("GetPVarNameAtIndex", native);
  sampgdk_fakeamx_push(size, &varname_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  params[3] = varname_;
  params[4] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(varname_, varname, size);
  sampgdk_fakeamx_pop(varname_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPVarType(int playerid, const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell varname_;
  sampgdk_log_debug("GetPVarType(%d, \"%s\")", playerid, varname);
  native = sampgdk_native_find_flexible("GetPVarType", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerChatBubble(int playerid, const char * text, int color, float drawdistance, int expiretime)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell text_;
  sampgdk_log_debug("SetPlayerChatBubble(%d, \"%s\", %d, %f, %d)", playerid, text, color, drawdistance, expiretime);
  native = sampgdk_native_find_flexible("SetPlayerChatBubble", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = text_;
  params[3] = (cell)color;
  params[4] = amx_ftoc(drawdistance);
  params[5] = (cell)expiretime;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PutPlayerInVehicle(int playerid, int vehicleid, int seatid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PutPlayerInVehicle(%d, %d, %d)", playerid, vehicleid, seatid);
  native = sampgdk_native_find_flexible("PutPlayerInVehicle", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)vehicleid;
  params[3] = (cell)seatid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerVehicleID(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerVehicleID(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerVehicleID", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerVehicleSeat(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerVehicleSeat(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerVehicleSeat", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, RemovePlayerFromVehicle(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("RemovePlayerFromVehicle(%d)", playerid);
  native = sampgdk_native_find_flexible("RemovePlayerFromVehicle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TogglePlayerControllable(int playerid, bool toggle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TogglePlayerControllable(%d, %d)", playerid, toggle);
  native = sampgdk_native_find_flexible("TogglePlayerControllable", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)toggle;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerPlaySound(int playerid, int soundid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("PlayerPlaySound(%d, %d, %f, %f, %f)", playerid, soundid, x, y, z);
  native = sampgdk_native_find_flexible("PlayerPlaySound", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)soundid;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ApplyAnimation(int playerid, const char * animlib, const char * animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[11];
  cell animlib_;
  cell animname_;
  sampgdk_log_debug("ApplyAnimation(%d, \"%s\", \"%s\", %f, %d, %d, %d, %d, %d, %d)", playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
  native = sampgdk_native_find_flexible("ApplyAnimation", native);
  sampgdk_fakeamx_push_string(animlib, NULL, &animlib_);
  sampgdk_fakeamx_push_string(animname, NULL, &animname_);
  params[0] = 10 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = animlib_;
  params[3] = animname_;
  params[4] = amx_ftoc(fDelta);
  params[5] = (cell)loop;
  params[6] = (cell)lockx;
  params[7] = (cell)locky;
  params[8] = (cell)freeze;
  params[9] = (cell)time;
  params[10] = (cell)forcesync;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(animname_);
  sampgdk_fakeamx_pop(animlib_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ClearAnimations(int playerid, bool forcesync)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("ClearAnimations(%d, %d)", playerid, forcesync);
  native = sampgdk_native_find_flexible("ClearAnimations", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)forcesync;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerAnimationIndex(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerAnimationIndex(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerAnimationIndex", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GetAnimationName(int index, char * animlib, int animlib_size, char * animname, int animname_size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell animlib_;
  cell animname_;
  sampgdk_log_debug("GetAnimationName(%d, \"%s\", %d, \"%s\", %d)", index, animlib, animlib_size, animname, animname_size);
  native = sampgdk_native_find_flexible("GetAnimationName", native);
  sampgdk_fakeamx_push(animlib_size, &animlib_);
  sampgdk_fakeamx_push(animname_size, &animname_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)index;
  params[2] = animlib_;
  params[3] = (cell)animlib_size;
  params[4] = animname_;
  params[5] = (cell)animname_size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(animlib_, animlib, animlib_size);
  sampgdk_fakeamx_get_string(animname_, animname, animname_size);
  sampgdk_fakeamx_pop(animname_);
  sampgdk_fakeamx_pop(animlib_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerSpecialAction(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerSpecialAction(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerSpecialAction", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerSpecialAction(int playerid, int actionid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerSpecialAction(%d, %d)", playerid, actionid);
  native = sampgdk_native_find_flexible("SetPlayerSpecialAction", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)actionid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DisableRemoteVehicleCollisions(int playerid, bool disable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("DisableRemoteVehicleCollisions(%d, %d)", playerid, disable);
  native = sampgdk_native_find_flexible("DisableRemoteVehicleCollisions", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)disable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerCheckpoint(int playerid, float x, float y, float z, float size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("SetPlayerCheckpoint(%d, %f, %f, %f, %f)", playerid, x, y, z, size);
  native = sampgdk_native_find_flexible("SetPlayerCheckpoint", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  params[5] = amx_ftoc(size);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DisablePlayerCheckpoint(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DisablePlayerCheckpoint(%d)", playerid);
  native = sampgdk_native_find_flexible("DisablePlayerCheckpoint", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("SetPlayerRaceCheckpoint(%d, %d, %f, %f, %f, %f, %f, %f, %f)", playerid, type, x, y, z, nextx, nexty, nextz, size);
  native = sampgdk_native_find_flexible("SetPlayerRaceCheckpoint", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)type;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  params[6] = amx_ftoc(nextx);
  params[7] = amx_ftoc(nexty);
  params[8] = amx_ftoc(nextz);
  params[9] = amx_ftoc(size);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DisablePlayerRaceCheckpoint(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DisablePlayerRaceCheckpoint(%d)", playerid);
  native = sampgdk_native_find_flexible("DisablePlayerRaceCheckpoint", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("SetPlayerWorldBounds(%d, %f, %f, %f, %f)", playerid, x_max, x_min, y_max, y_min);
  native = sampgdk_native_find_flexible("SetPlayerWorldBounds", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x_max);
  params[3] = amx_ftoc(x_min);
  params[4] = amx_ftoc(y_max);
  params[5] = amx_ftoc(y_min);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("SetPlayerMarkerForPlayer(%d, %d, %d)", playerid, showplayerid, color);
  native = sampgdk_native_find_flexible("SetPlayerMarkerForPlayer", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)showplayerid;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("ShowPlayerNameTagForPlayer(%d, %d, %d)", playerid, showplayerid, show);
  native = sampgdk_native_find_flexible("ShowPlayerNameTagForPlayer", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)showplayerid;
  params[3] = (cell)show;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  sampgdk_log_debug("SetPlayerMapIcon(%d, %d, %f, %f, %f, %d, %d, %d)", playerid, iconid, x, y, z, markertype, color, style);
  native = sampgdk_native_find_flexible("SetPlayerMapIcon", native);
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)iconid;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  params[6] = (cell)markertype;
  params[7] = (cell)color;
  params[8] = (cell)style;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, RemovePlayerMapIcon(int playerid, int iconid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("RemovePlayerMapIcon(%d, %d)", playerid, iconid);
  native = sampgdk_native_find_flexible("RemovePlayerMapIcon", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)iconid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, AllowPlayerTeleport(int playerid, bool allow)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("AllowPlayerTeleport(%d, %d)", playerid, allow);
  native = sampgdk_native_find_flexible("AllowPlayerTeleport", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)allow;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerCameraPos(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetPlayerCameraPos(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("SetPlayerCameraPos", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("SetPlayerCameraLookAt(%d, %f, %f, %f, %d)", playerid, x, y, z, cut);
  native = sampgdk_native_find_flexible("SetPlayerCameraLookAt", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  params[5] = (cell)cut;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetCameraBehindPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetCameraBehindPlayer(%d)", playerid);
  native = sampgdk_native_find_flexible("SetCameraBehindPlayer", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerCameraPos(int playerid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetPlayerCameraPos(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("GetPlayerCameraPos", native);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = x_;
  params[3] = y_;
  params[4] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerCameraFrontVector(int playerid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetPlayerCameraFrontVector(%d, %f, %f, %f)", playerid, x, y, z);
  native = sampgdk_native_find_flexible("GetPlayerCameraFrontVector", native);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = x_;
  params[3] = y_;
  params[4] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerCameraMode(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerCameraMode(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerCameraMode", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, EnablePlayerCameraTarget(int playerid, bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("EnablePlayerCameraTarget(%d, %d)", playerid, enable);
  native = sampgdk_native_find_flexible("EnablePlayerCameraTarget", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerCameraTargetObject(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerCameraTargetObject(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerCameraTargetObject", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerCameraTargetVehicle(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerCameraTargetVehicle(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerCameraTargetVehicle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerCameraTargetPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerCameraTargetPlayer(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerCameraTargetPlayer", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerCameraTargetActor(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerCameraTargetActor(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerCameraTargetActor", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(float, GetPlayerCameraAspectRatio(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerCameraAspectRatio(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerCameraAspectRatio", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(float, GetPlayerCameraZoom(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerCameraZoom(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerCameraZoom", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(bool, AttachCameraToObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("AttachCameraToObject(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("AttachCameraToObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, AttachCameraToPlayerObject(int playerid, int playerobjectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("AttachCameraToPlayerObject(%d, %d)", playerid, playerobjectid);
  native = sampgdk_native_find_flexible("AttachCameraToPlayerObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)playerobjectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("InterpolateCameraPos(%d, %f, %f, %f, %f, %f, %f, %d, %d)", playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, time, cut);
  native = sampgdk_native_find_flexible("InterpolateCameraPos", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(FromX);
  params[3] = amx_ftoc(FromY);
  params[4] = amx_ftoc(FromZ);
  params[5] = amx_ftoc(ToX);
  params[6] = amx_ftoc(ToY);
  params[7] = amx_ftoc(ToZ);
  params[8] = (cell)time;
  params[9] = (cell)cut;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("InterpolateCameraLookAt(%d, %f, %f, %f, %f, %f, %f, %d, %d)", playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, time, cut);
  native = sampgdk_native_find_flexible("InterpolateCameraLookAt", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(FromX);
  params[3] = amx_ftoc(FromY);
  params[4] = amx_ftoc(FromZ);
  params[5] = amx_ftoc(ToX);
  params[6] = amx_ftoc(ToY);
  params[7] = amx_ftoc(ToZ);
  params[8] = (cell)time;
  params[9] = (cell)cut;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerConnected(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsPlayerConnected(%d)", playerid);
  native = sampgdk_native_find_flexible("IsPlayerConnected", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInVehicle(int playerid, int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("IsPlayerInVehicle(%d, %d)", playerid, vehicleid);
  native = sampgdk_native_find_flexible("IsPlayerInVehicle", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInAnyVehicle(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsPlayerInAnyVehicle(%d)", playerid);
  native = sampgdk_native_find_flexible("IsPlayerInAnyVehicle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInCheckpoint(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsPlayerInCheckpoint(%d)", playerid);
  native = sampgdk_native_find_flexible("IsPlayerInCheckpoint", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInRaceCheckpoint(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsPlayerInRaceCheckpoint(%d)", playerid);
  native = sampgdk_native_find_flexible("IsPlayerInRaceCheckpoint", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerVirtualWorld(int playerid, int worldid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerVirtualWorld(%d, %d)", playerid, worldid);
  native = sampgdk_native_find_flexible("SetPlayerVirtualWorld", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)worldid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerVirtualWorld(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerVirtualWorld(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerVirtualWorld", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, EnableStuntBonusForPlayer(int playerid, bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("EnableStuntBonusForPlayer(%d, %d)", playerid, enable);
  native = sampgdk_native_find_flexible("EnableStuntBonusForPlayer", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, EnableStuntBonusForAll(bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("EnableStuntBonusForAll(%d)", enable);
  native = sampgdk_native_find_flexible("EnableStuntBonusForAll", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TogglePlayerSpectating(int playerid, bool toggle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TogglePlayerSpectating(%d, %d)", playerid, toggle);
  native = sampgdk_native_find_flexible("TogglePlayerSpectating", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)toggle;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerSpectatePlayer(int playerid, int targetplayerid, int mode)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerSpectatePlayer(%d, %d, %d)", playerid, targetplayerid, mode);
  native = sampgdk_native_find_flexible("PlayerSpectatePlayer", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)targetplayerid;
  params[3] = (cell)mode;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("PlayerSpectateVehicle(%d, %d, %d)", playerid, targetvehicleid, mode);
  native = sampgdk_native_find_flexible("PlayerSpectateVehicle", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)targetvehicleid;
  params[3] = (cell)mode;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, StartRecordingPlayerData(int playerid, int recordtype, const char * recordname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell recordname_;
  sampgdk_log_debug("StartRecordingPlayerData(%d, %d, \"%s\")", playerid, recordtype, recordname);
  native = sampgdk_native_find_flexible("StartRecordingPlayerData", native);
  sampgdk_fakeamx_push_string(recordname, NULL, &recordname_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)recordtype;
  params[3] = recordname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(recordname_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, StopRecordingPlayerData(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("StopRecordingPlayerData(%d)", playerid);
  native = sampgdk_native_find_flexible("StopRecordingPlayerData", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, CreateExplosionForPlayer(int playerid, float X, float Y, float Z, int type, float Radius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  sampgdk_log_debug("CreateExplosionForPlayer(%d, %f, %f, %f, %d, %f)", playerid, X, Y, Z, type, Radius);
  native = sampgdk_native_find_flexible("CreateExplosionForPlayer", native);
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(X);
  params[3] = amx_ftoc(Y);
  params[4] = amx_ftoc(Z);
  params[5] = (cell)type;
  params[6] = amx_ftoc(Radius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_MODULE_INIT(a_players) {
  return 0;
}

SAMPGDK_MODULE_CLEANUP(a_players) {
}


#include "sampgdk.h"

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/log.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(int, CreateActor(int modelid, float x, float y, float z, float rotation)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("CreateActor(%d, %f, %f, %f, %f)", modelid, x, y, z, rotation);
  native = sampgdk_native_find_flexible("CreateActor", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)modelid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  params[5] = amx_ftoc(rotation);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, DestroyActor(int actorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DestroyActor(%d)", actorid);
  native = sampgdk_native_find_flexible("DestroyActor", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)actorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsActorStreamedIn(int actorid, int forplayerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("IsActorStreamedIn(%d, %d)", actorid, forplayerid);
  native = sampgdk_native_find_flexible("IsActorStreamedIn", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = (cell)forplayerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetActorVirtualWorld(int actorid, int vworld)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetActorVirtualWorld(%d, %d)", actorid, vworld);
  native = sampgdk_native_find_flexible("SetActorVirtualWorld", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = (cell)vworld;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetActorVirtualWorld(int actorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetActorVirtualWorld(%d)", actorid);
  native = sampgdk_native_find_flexible("GetActorVirtualWorld", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)actorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, ApplyActorAnimation(int actorid, const char * animlib, const char * animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  cell animlib_;
  cell animname_;
  sampgdk_log_debug("ApplyActorAnimation(%d, \"%s\", \"%s\", %f, %d, %d, %d, %d, %d)", actorid, animlib, animname, fDelta, loop, lockx, locky, freeze, time);
  native = sampgdk_native_find_flexible("ApplyActorAnimation", native);
  sampgdk_fakeamx_push_string(animlib, NULL, &animlib_);
  sampgdk_fakeamx_push_string(animname, NULL, &animname_);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = animlib_;
  params[3] = animname_;
  params[4] = amx_ftoc(fDelta);
  params[5] = (cell)loop;
  params[6] = (cell)lockx;
  params[7] = (cell)locky;
  params[8] = (cell)freeze;
  params[9] = (cell)time;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(animname_);
  sampgdk_fakeamx_pop(animlib_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ClearActorAnimations(int actorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("ClearActorAnimations(%d)", actorid);
  native = sampgdk_native_find_flexible("ClearActorAnimations", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)actorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetActorPos(int actorid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetActorPos(%d, %f, %f, %f)", actorid, x, y, z);
  native = sampgdk_native_find_flexible("SetActorPos", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetActorPos(int actorid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetActorPos(%d, %f, %f, %f)", actorid, x, y, z);
  native = sampgdk_native_find_flexible("GetActorPos", native);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = x_;
  params[3] = y_;
  params[4] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetActorFacingAngle(int actorid, float angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetActorFacingAngle(%d, %f)", actorid, angle);
  native = sampgdk_native_find_flexible("SetActorFacingAngle", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = amx_ftoc(angle);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetActorFacingAngle(int actorid, float * angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell angle_;
  sampgdk_log_debug("GetActorFacingAngle(%d, %f)", actorid, angle);
  native = sampgdk_native_find_flexible("GetActorFacingAngle", native);
  sampgdk_fakeamx_push(1, &angle_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = angle_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(angle_, angle);
  sampgdk_fakeamx_pop(angle_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetActorHealth(int actorid, float health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetActorHealth(%d, %f)", actorid, health);
  native = sampgdk_native_find_flexible("SetActorHealth", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = amx_ftoc(health);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetActorHealth(int actorid, float * health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell health_;
  sampgdk_log_debug("GetActorHealth(%d, %f)", actorid, health);
  native = sampgdk_native_find_flexible("GetActorHealth", native);
  sampgdk_fakeamx_push(1, &health_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = health_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(health_, health);
  sampgdk_fakeamx_pop(health_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetActorInvulnerable(int actorid, bool invulnerable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetActorInvulnerable(%d, %d)", actorid, invulnerable);
  native = sampgdk_native_find_flexible("SetActorInvulnerable", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)actorid;
  params[2] = (cell)invulnerable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsActorInvulnerable(int actorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsActorInvulnerable(%d)", actorid);
  native = sampgdk_native_find_flexible("IsActorInvulnerable", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)actorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsValidActor(int actorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsValidActor(%d)", actorid);
  native = sampgdk_native_find_flexible("IsValidActor", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)actorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_MODULE_INIT(a_actor) {
  return 0;
}

SAMPGDK_MODULE_CLEANUP(a_actor) {
}


#include "sampgdk.h"

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/log.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(bool, HTTP(int index, int type, const char * url, const char * data)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell url_;
  cell data_;
  cell callback_;
  sampgdk_log_debug("HTTP(%d, %d, \"%s\", \"%s\", \"%s\")", index, type, url, data);
  native = sampgdk_native_find_flexible("HTTP", native);
  sampgdk_fakeamx_push_string(url, NULL, &url_);
  sampgdk_fakeamx_push_string(data, NULL, &data_);
  sampgdk_fakeamx_push_string("OnHTTPResponse", NULL, &callback_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)index;
  params[2] = (cell)type;
  params[3] = url_;
  params[4] = data_;
  params[5] = callback_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(callback_);
  sampgdk_fakeamx_pop(data_);
  sampgdk_fakeamx_pop(url_);
  return !!(retval);
}

typedef void (SAMPGDK_CALLBACK_CALL *OnHTTPResponse_callback)(int index, int response_code, const char * data);
static bool _OnHTTPResponse(AMX *amx, void *callback, cell *retval) {
  int index;
  int response_code;
  const char * data;
  sampgdk_param_get_cell(amx, 0, (void *)&index);
  sampgdk_param_get_cell(amx, 1, (void *)&response_code);
  sampgdk_param_get_string(amx, 2, (void *)&data);
  sampgdk_log_debug("OnHTTPResponse(%d, %d, \"%s\")", index, response_code, data);
  ((OnHTTPResponse_callback)callback)(index, response_code, data);
  free((void *)data);
  return true;
}

SAMPGDK_MODULE_INIT(a_http) {
  int error;
  if ((error = sampgdk_callback_register("OnHTTPResponse", _OnHTTPResponse)) < 0) {
    return error;
  }
  return 0;
}

SAMPGDK_MODULE_CLEANUP(a_http) {
  sampgdk_callback_unregister("OnHTTPResponse");
}


#include "sampgdk.h"

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/log.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(bool, IsValidVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsValidVehicle(%d)", vehicleid);
  native = sampgdk_native_find_flexible("IsValidVehicle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(float, GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("GetVehicleDistanceFromPoint(%d, %f, %f, %f)", vehicleid, x, y, z);
  native = sampgdk_native_find_flexible("GetVehicleDistanceFromPoint", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(int, CreateVehicle(int vehicletype, float x, float y, float z, float rotation, int color1, int color2, int respawn_delay, bool addsiren)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("CreateVehicle(%d, %f, %f, %f, %f, %d, %d, %d, %d)", vehicletype, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
  native = sampgdk_native_find_flexible("CreateVehicle", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)vehicletype;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  params[5] = amx_ftoc(rotation);
  params[6] = (cell)color1;
  params[7] = (cell)color2;
  params[8] = (cell)respawn_delay;
  params[9] = (cell)addsiren;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, DestroyVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DestroyVehicle(%d)", vehicleid);
  native = sampgdk_native_find_flexible("DestroyVehicle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsVehicleStreamedIn(int vehicleid, int forplayerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("IsVehicleStreamedIn(%d, %d)", vehicleid, forplayerid);
  native = sampgdk_native_find_flexible("IsVehicleStreamedIn", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)forplayerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehiclePos(int vehicleid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetVehiclePos(%d, %f, %f, %f)", vehicleid, x, y, z);
  native = sampgdk_native_find_flexible("GetVehiclePos", native);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = x_;
  params[3] = y_;
  params[4] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehiclePos(int vehicleid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetVehiclePos(%d, %f, %f, %f)", vehicleid, x, y, z);
  native = sampgdk_native_find_flexible("SetVehiclePos", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleZAngle(int vehicleid, float * z_angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell z_angle_;
  sampgdk_log_debug("GetVehicleZAngle(%d, %f)", vehicleid, z_angle);
  native = sampgdk_native_find_flexible("GetVehicleZAngle", native);
  sampgdk_fakeamx_push(1, &z_angle_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = z_angle_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(z_angle_, z_angle);
  sampgdk_fakeamx_pop(z_angle_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleRotationQuat(int vehicleid, float * w, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell w_;
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetVehicleRotationQuat(%d, %f, %f, %f, %f)", vehicleid, w, x, y, z);
  native = sampgdk_native_find_flexible("GetVehicleRotationQuat", native);
  sampgdk_fakeamx_push(1, &w_);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = w_;
  params[3] = x_;
  params[4] = y_;
  params[5] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(w_, w);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  sampgdk_fakeamx_pop(w_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleZAngle(int vehicleid, float z_angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetVehicleZAngle(%d, %f)", vehicleid, z_angle);
  native = sampgdk_native_find_flexible("SetVehicleZAngle", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(z_angle);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetVehicleParamsForPlayer(%d, %d, %d, %d)", vehicleid, playerid, objective, doorslocked);
  native = sampgdk_native_find_flexible("SetVehicleParamsForPlayer", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)playerid;
  params[3] = (cell)objective;
  params[4] = (cell)doorslocked;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ManualVehicleEngineAndLights()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("ManualVehicleEngineAndLights()");
  native = sampgdk_native_find_flexible("ManualVehicleEngineAndLights", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  sampgdk_log_debug("SetVehicleParamsEx(%d, %d, %d, %d, %d, %d, %d, %d)", vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
  native = sampgdk_native_find_flexible("SetVehicleParamsEx", native);
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)engine;
  params[3] = (cell)lights;
  params[4] = (cell)alarm;
  params[5] = (cell)doors;
  params[6] = (cell)bonnet;
  params[7] = (cell)boot;
  params[8] = (cell)objective;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleParamsEx(int vehicleid, int * engine, int * lights, int * alarm, int * doors, int * bonnet, int * boot, int * objective)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  cell engine_;
  cell lights_;
  cell alarm_;
  cell doors_;
  cell bonnet_;
  cell boot_;
  cell objective_;
  sampgdk_log_debug("GetVehicleParamsEx(%d, %d, %d, %d, %d, %d, %d, %d)", vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
  native = sampgdk_native_find_flexible("GetVehicleParamsEx", native);
  sampgdk_fakeamx_push(1, &engine_);
  sampgdk_fakeamx_push(1, &lights_);
  sampgdk_fakeamx_push(1, &alarm_);
  sampgdk_fakeamx_push(1, &doors_);
  sampgdk_fakeamx_push(1, &bonnet_);
  sampgdk_fakeamx_push(1, &boot_);
  sampgdk_fakeamx_push(1, &objective_);
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = engine_;
  params[3] = lights_;
  params[4] = alarm_;
  params[5] = doors_;
  params[6] = bonnet_;
  params[7] = boot_;
  params[8] = objective_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_cell(engine_, engine);
  sampgdk_fakeamx_get_cell(lights_, lights);
  sampgdk_fakeamx_get_cell(alarm_, alarm);
  sampgdk_fakeamx_get_cell(doors_, doors);
  sampgdk_fakeamx_get_cell(bonnet_, bonnet);
  sampgdk_fakeamx_get_cell(boot_, boot);
  sampgdk_fakeamx_get_cell(objective_, objective);
  sampgdk_fakeamx_pop(objective_);
  sampgdk_fakeamx_pop(boot_);
  sampgdk_fakeamx_pop(bonnet_);
  sampgdk_fakeamx_pop(doors_);
  sampgdk_fakeamx_pop(alarm_);
  sampgdk_fakeamx_pop(lights_);
  sampgdk_fakeamx_pop(engine_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetVehicleParamsSirenState(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetVehicleParamsSirenState(%d)", vehicleid);
  native = sampgdk_native_find_flexible("GetVehicleParamsSirenState", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleParamsCarDoors(int vehicleid, bool driver, bool passenger, bool backleft, bool backright)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("SetVehicleParamsCarDoors(%d, %d, %d, %d, %d)", vehicleid, driver, passenger, backleft, backright);
  native = sampgdk_native_find_flexible("SetVehicleParamsCarDoors", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)driver;
  params[3] = (cell)passenger;
  params[4] = (cell)backleft;
  params[5] = (cell)backright;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleParamsCarDoors(int vehicleid, int * driver, int * passenger, int * backleft, int * backright)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell driver_;
  cell passenger_;
  cell backleft_;
  cell backright_;
  sampgdk_log_debug("GetVehicleParamsCarDoors(%d, %d, %d, %d, %d)", vehicleid, driver, passenger, backleft, backright);
  native = sampgdk_native_find_flexible("GetVehicleParamsCarDoors", native);
  sampgdk_fakeamx_push(1, &driver_);
  sampgdk_fakeamx_push(1, &passenger_);
  sampgdk_fakeamx_push(1, &backleft_);
  sampgdk_fakeamx_push(1, &backright_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = driver_;
  params[3] = passenger_;
  params[4] = backleft_;
  params[5] = backright_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_cell(driver_, driver);
  sampgdk_fakeamx_get_cell(passenger_, passenger);
  sampgdk_fakeamx_get_cell(backleft_, backleft);
  sampgdk_fakeamx_get_cell(backright_, backright);
  sampgdk_fakeamx_pop(backright_);
  sampgdk_fakeamx_pop(backleft_);
  sampgdk_fakeamx_pop(passenger_);
  sampgdk_fakeamx_pop(driver_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleParamsCarWindows(int vehicleid, bool driver, bool passenger, bool backleft, bool backright)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("SetVehicleParamsCarWindows(%d, %d, %d, %d, %d)", vehicleid, driver, passenger, backleft, backright);
  native = sampgdk_native_find_flexible("SetVehicleParamsCarWindows", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)driver;
  params[3] = (cell)passenger;
  params[4] = (cell)backleft;
  params[5] = (cell)backright;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleParamsCarWindows(int vehicleid, int * driver, int * passenger, int * backleft, int * backright)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell driver_;
  cell passenger_;
  cell backleft_;
  cell backright_;
  sampgdk_log_debug("GetVehicleParamsCarWindows(%d, %d, %d, %d, %d)", vehicleid, driver, passenger, backleft, backright);
  native = sampgdk_native_find_flexible("GetVehicleParamsCarWindows", native);
  sampgdk_fakeamx_push(1, &driver_);
  sampgdk_fakeamx_push(1, &passenger_);
  sampgdk_fakeamx_push(1, &backleft_);
  sampgdk_fakeamx_push(1, &backright_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = driver_;
  params[3] = passenger_;
  params[4] = backleft_;
  params[5] = backright_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_cell(driver_, driver);
  sampgdk_fakeamx_get_cell(passenger_, passenger);
  sampgdk_fakeamx_get_cell(backleft_, backleft);
  sampgdk_fakeamx_get_cell(backright_, backright);
  sampgdk_fakeamx_pop(backright_);
  sampgdk_fakeamx_pop(backleft_);
  sampgdk_fakeamx_pop(passenger_);
  sampgdk_fakeamx_pop(driver_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleToRespawn(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetVehicleToRespawn(%d)", vehicleid);
  native = sampgdk_native_find_flexible("SetVehicleToRespawn", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, LinkVehicleToInterior(int vehicleid, int interiorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("LinkVehicleToInterior(%d, %d)", vehicleid, interiorid);
  native = sampgdk_native_find_flexible("LinkVehicleToInterior", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)interiorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, AddVehicleComponent(int vehicleid, int componentid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("AddVehicleComponent(%d, %d)", vehicleid, componentid);
  native = sampgdk_native_find_flexible("AddVehicleComponent", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)componentid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, RemoveVehicleComponent(int vehicleid, int componentid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("RemoveVehicleComponent(%d, %d)", vehicleid, componentid);
  native = sampgdk_native_find_flexible("RemoveVehicleComponent", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)componentid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ChangeVehicleColor(int vehicleid, int color1, int color2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("ChangeVehicleColor(%d, %d, %d)", vehicleid, color1, color2);
  native = sampgdk_native_find_flexible("ChangeVehicleColor", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)color1;
  params[3] = (cell)color2;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ChangeVehiclePaintjob(int vehicleid, int paintjobid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("ChangeVehiclePaintjob(%d, %d)", vehicleid, paintjobid);
  native = sampgdk_native_find_flexible("ChangeVehiclePaintjob", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)paintjobid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleHealth(int vehicleid, float health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetVehicleHealth(%d, %f)", vehicleid, health);
  native = sampgdk_native_find_flexible("SetVehicleHealth", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(health);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleHealth(int vehicleid, float * health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell health_;
  sampgdk_log_debug("GetVehicleHealth(%d, %f)", vehicleid, health);
  native = sampgdk_native_find_flexible("GetVehicleHealth", native);
  sampgdk_fakeamx_push(1, &health_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = health_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(health_, health);
  sampgdk_fakeamx_pop(health_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, AttachTrailerToVehicle(int trailerid, int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("AttachTrailerToVehicle(%d, %d)", trailerid, vehicleid);
  native = sampgdk_native_find_flexible("AttachTrailerToVehicle", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)trailerid;
  params[2] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DetachTrailerFromVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DetachTrailerFromVehicle(%d)", vehicleid);
  native = sampgdk_native_find_flexible("DetachTrailerFromVehicle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsTrailerAttachedToVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsTrailerAttachedToVehicle(%d)", vehicleid);
  native = sampgdk_native_find_flexible("IsTrailerAttachedToVehicle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetVehicleTrailer(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetVehicleTrailer(%d)", vehicleid);
  native = sampgdk_native_find_flexible("GetVehicleTrailer", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleNumberPlate(int vehicleid, const char * numberplate)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell numberplate_;
  sampgdk_log_debug("SetVehicleNumberPlate(%d, \"%s\")", vehicleid, numberplate);
  native = sampgdk_native_find_flexible("SetVehicleNumberPlate", native);
  sampgdk_fakeamx_push_string(numberplate, NULL, &numberplate_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = numberplate_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(numberplate_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetVehicleModel(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetVehicleModel(%d)", vehicleid);
  native = sampgdk_native_find_flexible("GetVehicleModel", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetVehicleComponentInSlot(int vehicleid, int slot)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("GetVehicleComponentInSlot(%d, %d)", vehicleid, slot);
  native = sampgdk_native_find_flexible("GetVehicleComponentInSlot", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)slot;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetVehicleComponentType(int component)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetVehicleComponentType(%d)", component);
  native = sampgdk_native_find_flexible("GetVehicleComponentType", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)component;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, RepairVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("RepairVehicle(%d)", vehicleid);
  native = sampgdk_native_find_flexible("RepairVehicle", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleVelocity(int vehicleid, float * X, float * Y, float * Z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell X_;
  cell Y_;
  cell Z_;
  sampgdk_log_debug("GetVehicleVelocity(%d, %f, %f, %f)", vehicleid, X, Y, Z);
  native = sampgdk_native_find_flexible("GetVehicleVelocity", native);
  sampgdk_fakeamx_push(1, &X_);
  sampgdk_fakeamx_push(1, &Y_);
  sampgdk_fakeamx_push(1, &Z_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = X_;
  params[3] = Y_;
  params[4] = Z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(X_, X);
  sampgdk_fakeamx_get_float(Y_, Y);
  sampgdk_fakeamx_get_float(Z_, Z);
  sampgdk_fakeamx_pop(Z_);
  sampgdk_fakeamx_pop(Y_);
  sampgdk_fakeamx_pop(X_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleVelocity(int vehicleid, float X, float Y, float Z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetVehicleVelocity(%d, %f, %f, %f)", vehicleid, X, Y, Z);
  native = sampgdk_native_find_flexible("SetVehicleVelocity", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(X);
  params[3] = amx_ftoc(Y);
  params[4] = amx_ftoc(Z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetVehicleAngularVelocity(%d, %f, %f, %f)", vehicleid, X, Y, Z);
  native = sampgdk_native_find_flexible("SetVehicleAngularVelocity", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(X);
  params[3] = amx_ftoc(Y);
  params[4] = amx_ftoc(Z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleDamageStatus(int vehicleid, int * panels, int * doors, int * lights, int * tires)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell panels_;
  cell doors_;
  cell lights_;
  cell tires_;
  sampgdk_log_debug("GetVehicleDamageStatus(%d, %d, %d, %d, %d)", vehicleid, panels, doors, lights, tires);
  native = sampgdk_native_find_flexible("GetVehicleDamageStatus", native);
  sampgdk_fakeamx_push(1, &panels_);
  sampgdk_fakeamx_push(1, &doors_);
  sampgdk_fakeamx_push(1, &lights_);
  sampgdk_fakeamx_push(1, &tires_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = panels_;
  params[3] = doors_;
  params[4] = lights_;
  params[5] = tires_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_cell(panels_, panels);
  sampgdk_fakeamx_get_cell(doors_, doors);
  sampgdk_fakeamx_get_cell(lights_, lights);
  sampgdk_fakeamx_get_cell(tires_, tires);
  sampgdk_fakeamx_pop(tires_);
  sampgdk_fakeamx_pop(lights_);
  sampgdk_fakeamx_pop(doors_);
  sampgdk_fakeamx_pop(panels_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, UpdateVehicleDamageStatus(int vehicleid, int panels, int doors, int lights, int tires)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("UpdateVehicleDamageStatus(%d, %d, %d, %d, %d)", vehicleid, panels, doors, lights, tires);
  native = sampgdk_native_find_flexible("UpdateVehicleDamageStatus", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)panels;
  params[3] = (cell)doors;
  params[4] = (cell)lights;
  params[5] = (cell)tires;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleVirtualWorld(int vehicleid, int worldid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetVehicleVirtualWorld(%d, %d)", vehicleid, worldid);
  native = sampgdk_native_find_flexible("SetVehicleVirtualWorld", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)worldid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetVehicleVirtualWorld(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetVehicleVirtualWorld(%d)", vehicleid);
  native = sampgdk_native_find_flexible("GetVehicleVirtualWorld", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleModelInfo(int model, int infotype, float * X, float * Y, float * Z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell X_;
  cell Y_;
  cell Z_;
  sampgdk_log_debug("GetVehicleModelInfo(%d, %d, %f, %f, %f)", model, infotype, X, Y, Z);
  native = sampgdk_native_find_flexible("GetVehicleModelInfo", native);
  sampgdk_fakeamx_push(1, &X_);
  sampgdk_fakeamx_push(1, &Y_);
  sampgdk_fakeamx_push(1, &Z_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)model;
  params[2] = (cell)infotype;
  params[3] = X_;
  params[4] = Y_;
  params[5] = Z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(X_, X);
  sampgdk_fakeamx_get_float(Y_, Y);
  sampgdk_fakeamx_get_float(Z_, Z);
  sampgdk_fakeamx_pop(Z_);
  sampgdk_fakeamx_pop(Y_);
  sampgdk_fakeamx_pop(X_);
  return !!(retval);
}

SAMPGDK_MODULE_INIT(a_vehicles) {
  return 0;
}

SAMPGDK_MODULE_CLEANUP(a_vehicles) {
}


#include "sampgdk.h"

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/log.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(int, CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  sampgdk_log_debug("CreateObject(%d, %f, %f, %f, %f, %f, %f, %f)", modelid, x, y, z, rX, rY, rZ, DrawDistance);
  native = sampgdk_native_find_flexible("CreateObject", native);
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)modelid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  params[5] = amx_ftoc(rX);
  params[6] = amx_ftoc(rY);
  params[7] = amx_ftoc(rZ);
  params[8] = amx_ftoc(DrawDistance);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  sampgdk_log_debug("AttachObjectToVehicle(%d, %d, %f, %f, %f, %f, %f, %f)", objectid, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
  native = sampgdk_native_find_flexible("AttachObjectToVehicle", native);
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = (cell)vehicleid;
  params[3] = amx_ftoc(fOffsetX);
  params[4] = amx_ftoc(fOffsetY);
  params[5] = amx_ftoc(fOffsetZ);
  params[6] = amx_ftoc(fRotX);
  params[7] = amx_ftoc(fRotY);
  params[8] = amx_ftoc(fRotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, AttachObjectToObject(int objectid, int attachtoid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("AttachObjectToObject(%d, %d, %f, %f, %f, %f, %f, %f, %d)", objectid, attachtoid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, SyncRotation);
  native = sampgdk_native_find_flexible("AttachObjectToObject", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = (cell)attachtoid;
  params[3] = amx_ftoc(fOffsetX);
  params[4] = amx_ftoc(fOffsetY);
  params[5] = amx_ftoc(fOffsetZ);
  params[6] = amx_ftoc(fRotX);
  params[7] = amx_ftoc(fRotY);
  params[8] = amx_ftoc(fRotZ);
  params[9] = (cell)SyncRotation;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, AttachObjectToPlayer(int objectid, int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  sampgdk_log_debug("AttachObjectToPlayer(%d, %d, %f, %f, %f, %f, %f, %f)", objectid, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
  native = sampgdk_native_find_flexible("AttachObjectToPlayer", native);
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = (cell)playerid;
  params[3] = amx_ftoc(fOffsetX);
  params[4] = amx_ftoc(fOffsetY);
  params[5] = amx_ftoc(fOffsetZ);
  params[6] = amx_ftoc(fRotX);
  params[7] = amx_ftoc(fRotY);
  params[8] = amx_ftoc(fRotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetObjectPos(int objectid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetObjectPos(%d, %f, %f, %f)", objectid, x, y, z);
  native = sampgdk_native_find_flexible("SetObjectPos", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetObjectPos(int objectid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetObjectPos(%d, %f, %f, %f)", objectid, x, y, z);
  native = sampgdk_native_find_flexible("GetObjectPos", native);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = x_;
  params[3] = y_;
  params[4] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetObjectRot(int objectid, float rotX, float rotY, float rotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SetObjectRot(%d, %f, %f, %f)", objectid, rotX, rotY, rotZ);
  native = sampgdk_native_find_flexible("SetObjectRot", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = amx_ftoc(rotX);
  params[3] = amx_ftoc(rotY);
  params[4] = amx_ftoc(rotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetObjectRot(int objectid, float * rotX, float * rotY, float * rotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell rotX_;
  cell rotY_;
  cell rotZ_;
  sampgdk_log_debug("GetObjectRot(%d, %f, %f, %f)", objectid, rotX, rotY, rotZ);
  native = sampgdk_native_find_flexible("GetObjectRot", native);
  sampgdk_fakeamx_push(1, &rotX_);
  sampgdk_fakeamx_push(1, &rotY_);
  sampgdk_fakeamx_push(1, &rotZ_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = rotX_;
  params[3] = rotY_;
  params[4] = rotZ_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(rotX_, rotX);
  sampgdk_fakeamx_get_float(rotY_, rotY);
  sampgdk_fakeamx_get_float(rotZ_, rotZ);
  sampgdk_fakeamx_pop(rotZ_);
  sampgdk_fakeamx_pop(rotY_);
  sampgdk_fakeamx_pop(rotX_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetObjectModel(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetObjectModel(%d)", objectid);
  native = sampgdk_native_find_flexible("GetObjectModel", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetObjectNoCameraCol(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetObjectNoCameraCol(%d)", objectid);
  native = sampgdk_native_find_flexible("SetObjectNoCameraCol", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsValidObject(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsValidObject(%d)", objectid);
  native = sampgdk_native_find_flexible("IsValidObject", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DestroyObject(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DestroyObject(%d)", objectid);
  native = sampgdk_native_find_flexible("DestroyObject", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  sampgdk_log_debug("MoveObject(%d, %f, %f, %f, %f, %f, %f, %f)", objectid, X, Y, Z, Speed, RotX, RotY, RotZ);
  native = sampgdk_native_find_flexible("MoveObject", native);
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = amx_ftoc(X);
  params[3] = amx_ftoc(Y);
  params[4] = amx_ftoc(Z);
  params[5] = amx_ftoc(Speed);
  params[6] = amx_ftoc(RotX);
  params[7] = amx_ftoc(RotY);
  params[8] = amx_ftoc(RotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, StopObject(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("StopObject(%d)", objectid);
  native = sampgdk_native_find_flexible("StopObject", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsObjectMoving(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsObjectMoving(%d)", objectid);
  native = sampgdk_native_find_flexible("IsObjectMoving", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, EditObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("EditObject(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("EditObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, EditPlayerObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("EditPlayerObject(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("EditPlayerObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SelectObject(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SelectObject(%d)", playerid);
  native = sampgdk_native_find_flexible("SelectObject", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, CancelEdit(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("CancelEdit(%d)", playerid);
  native = sampgdk_native_find_flexible("CancelEdit", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("CreatePlayerObject(%d, %d, %f, %f, %f, %f, %f, %f, %f)", playerid, modelid, x, y, z, rX, rY, rZ, DrawDistance);
  native = sampgdk_native_find_flexible("CreatePlayerObject", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)modelid;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  params[6] = amx_ftoc(rX);
  params[7] = amx_ftoc(rY);
  params[8] = amx_ftoc(rZ);
  params[9] = amx_ftoc(DrawDistance);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("AttachPlayerObjectToPlayer(%d, %d, %d, %f, %f, %f, %f, %f, %f)", objectplayer, objectid, attachplayer, OffsetX, OffsetY, OffsetZ, rX, rY, rZ);
  native = sampgdk_native_find_flexible("AttachPlayerObjectToPlayer", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)objectplayer;
  params[2] = (cell)objectid;
  params[3] = (cell)attachplayer;
  params[4] = amx_ftoc(OffsetX);
  params[5] = amx_ftoc(OffsetY);
  params[6] = amx_ftoc(OffsetZ);
  params[7] = amx_ftoc(rX);
  params[8] = amx_ftoc(rY);
  params[9] = amx_ftoc(rZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("AttachPlayerObjectToVehicle(%d, %d, %d, %f, %f, %f, %f, %f, %f)", playerid, objectid, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, RotZ);
  native = sampgdk_native_find_flexible("AttachPlayerObjectToVehicle", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = (cell)vehicleid;
  params[4] = amx_ftoc(fOffsetX);
  params[5] = amx_ftoc(fOffsetY);
  params[6] = amx_ftoc(fOffsetZ);
  params[7] = amx_ftoc(fRotX);
  params[8] = amx_ftoc(fRotY);
  params[9] = amx_ftoc(RotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("SetPlayerObjectPos(%d, %d, %f, %f, %f)", playerid, objectid, x, y, z);
  native = sampgdk_native_find_flexible("SetPlayerObjectPos", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerObjectPos(int playerid, int objectid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell x_;
  cell y_;
  cell z_;
  sampgdk_log_debug("GetPlayerObjectPos(%d, %d, %f, %f, %f)", playerid, objectid, x, y, z);
  native = sampgdk_native_find_flexible("GetPlayerObjectPos", native);
  sampgdk_fakeamx_push(1, &x_);
  sampgdk_fakeamx_push(1, &y_);
  sampgdk_fakeamx_push(1, &z_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = x_;
  params[4] = y_;
  params[5] = z_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(x_, x);
  sampgdk_fakeamx_get_float(y_, y);
  sampgdk_fakeamx_get_float(z_, z);
  sampgdk_fakeamx_pop(z_);
  sampgdk_fakeamx_pop(y_);
  sampgdk_fakeamx_pop(x_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("SetPlayerObjectRot(%d, %d, %f, %f, %f)", playerid, objectid, rotX, rotY, rotZ);
  native = sampgdk_native_find_flexible("SetPlayerObjectRot", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = amx_ftoc(rotX);
  params[4] = amx_ftoc(rotY);
  params[5] = amx_ftoc(rotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerObjectRot(int playerid, int objectid, float * rotX, float * rotY, float * rotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell rotX_;
  cell rotY_;
  cell rotZ_;
  sampgdk_log_debug("GetPlayerObjectRot(%d, %d, %f, %f, %f)", playerid, objectid, rotX, rotY, rotZ);
  native = sampgdk_native_find_flexible("GetPlayerObjectRot", native);
  sampgdk_fakeamx_push(1, &rotX_);
  sampgdk_fakeamx_push(1, &rotY_);
  sampgdk_fakeamx_push(1, &rotZ_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = rotX_;
  params[4] = rotY_;
  params[5] = rotZ_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(rotX_, rotX);
  sampgdk_fakeamx_get_float(rotY_, rotY);
  sampgdk_fakeamx_get_float(rotZ_, rotZ);
  sampgdk_fakeamx_pop(rotZ_);
  sampgdk_fakeamx_pop(rotY_);
  sampgdk_fakeamx_pop(rotX_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerObjectModel(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("GetPlayerObjectModel(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("GetPlayerObjectModel", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectNoCameraCol(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SetPlayerObjectNoCameraCol(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("SetPlayerObjectNoCameraCol", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsValidPlayerObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("IsValidPlayerObject(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("IsValidPlayerObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DestroyPlayerObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("DestroyPlayerObject(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("DestroyPlayerObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX, float RotY, float RotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("MovePlayerObject(%d, %d, %f, %f, %f, %f, %f, %f, %f)", playerid, objectid, x, y, z, Speed, RotX, RotY, RotZ);
  native = sampgdk_native_find_flexible("MovePlayerObject", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  params[6] = amx_ftoc(Speed);
  params[7] = amx_ftoc(RotX);
  params[8] = amx_ftoc(RotY);
  params[9] = amx_ftoc(RotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, StopPlayerObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("StopPlayerObject(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("StopPlayerObject", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerObjectMoving(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("IsPlayerObjectMoving(%d, %d)", playerid, objectid);
  native = sampgdk_native_find_flexible("IsPlayerObjectMoving", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetObjectMaterial(int objectid, int materialindex, int modelid, const char * txdname, const char * texturename, int materialcolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  cell txdname_;
  cell texturename_;
  sampgdk_log_debug("SetObjectMaterial(%d, %d, %d, \"%s\", \"%s\", %d)", objectid, materialindex, modelid, txdname, texturename, materialcolor);
  native = sampgdk_native_find_flexible("SetObjectMaterial", native);
  sampgdk_fakeamx_push_string(txdname, NULL, &txdname_);
  sampgdk_fakeamx_push_string(texturename, NULL, &texturename_);
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = (cell)materialindex;
  params[3] = (cell)modelid;
  params[4] = txdname_;
  params[5] = texturename_;
  params[6] = (cell)materialcolor;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(texturename_);
  sampgdk_fakeamx_pop(txdname_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectMaterial(int playerid, int objectid, int materialindex, int modelid, const char * txdname, const char * texturename, int materialcolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[8];
  cell txdname_;
  cell texturename_;
  sampgdk_log_debug("SetPlayerObjectMaterial(%d, %d, %d, %d, \"%s\", \"%s\", %d)", playerid, objectid, materialindex, modelid, txdname, texturename, materialcolor);
  native = sampgdk_native_find_flexible("SetPlayerObjectMaterial", native);
  sampgdk_fakeamx_push_string(txdname, NULL, &txdname_);
  sampgdk_fakeamx_push_string(texturename, NULL, &texturename_);
  params[0] = 7 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = (cell)materialindex;
  params[4] = (cell)modelid;
  params[5] = txdname_;
  params[6] = texturename_;
  params[7] = (cell)materialcolor;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(texturename_);
  sampgdk_fakeamx_pop(txdname_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetObjectMaterialText(int objectid, const char * text, int materialindex, int materialsize, const char * fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[11];
  cell text_;
  cell fontface_;
  sampgdk_log_debug("SetObjectMaterialText(%d, \"%s\", %d, %d, \"%s\", %d, %d, %d, %d, %d)", objectid, text, materialindex, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
  native = sampgdk_native_find_flexible("SetObjectMaterialText", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  sampgdk_fakeamx_push_string(fontface, NULL, &fontface_);
  params[0] = 10 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = text_;
  params[3] = (cell)materialindex;
  params[4] = (cell)materialsize;
  params[5] = fontface_;
  params[6] = (cell)fontsize;
  params[7] = (cell)bold;
  params[8] = (cell)fontcolor;
  params[9] = (cell)backcolor;
  params[10] = (cell)textalignment;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(fontface_);
  sampgdk_fakeamx_pop(text_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectMaterialText(int playerid, int objectid, const char * text, int materialindex, int materialsize, const char * fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[12];
  cell text_;
  cell fontface_;
  sampgdk_log_debug("SetPlayerObjectMaterialText(%d, %d, \"%s\", %d, %d, \"%s\", %d, %d, %d, %d, %d)", playerid, objectid, text, materialindex, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
  native = sampgdk_native_find_flexible("SetPlayerObjectMaterialText", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  sampgdk_fakeamx_push_string(fontface, NULL, &fontface_);
  params[0] = 11 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = text_;
  params[4] = (cell)materialindex;
  params[5] = (cell)materialsize;
  params[6] = fontface_;
  params[7] = (cell)fontsize;
  params[8] = (cell)bold;
  params[9] = (cell)fontcolor;
  params[10] = (cell)backcolor;
  params[11] = (cell)textalignment;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(fontface_);
  sampgdk_fakeamx_pop(text_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetObjectsDefaultCameraCol(bool disable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetObjectsDefaultCameraCol(%d)", disable);
  native = sampgdk_native_find_flexible("SetObjectsDefaultCameraCol", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)disable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_MODULE_INIT(a_objects) {
  return 0;
}

SAMPGDK_MODULE_CLEANUP(a_objects) {
}


/* Copyright (C) 2012-2015 Zeex
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

#include "sampgdk.h"

/* #include "internal/timer.h" */

SAMPGDK_NATIVE(int, SetTimer(int interval, bool repeat, TimerCallback callback,
                             void *param)) {
  return sampgdk_timer_set(interval, repeat, callback, param);
}

SAMPGDK_NATIVE(bool, KillTimer(int timerid)) {
  return sampgdk_timer_kill(timerid) >= 0;
}

#include "sampgdk.h"

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/log.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(bool, SendClientMessage(int playerid, int color, const char * message)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell message_;
  sampgdk_log_debug("SendClientMessage(%d, %d, \"%s\")", playerid, color, message);
  native = sampgdk_native_find_flexible("SendClientMessage", native);
  sampgdk_fakeamx_push_string(message, NULL, &message_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)color;
  params[3] = message_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(message_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SendClientMessageToAll(int color, const char * message)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell message_;
  sampgdk_log_debug("SendClientMessageToAll(%d, \"%s\")", color, message);
  native = sampgdk_native_find_flexible("SendClientMessageToAll", native);
  sampgdk_fakeamx_push_string(message, NULL, &message_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)color;
  params[2] = message_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(message_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SendPlayerMessageToPlayer(int playerid, int senderid, const char * message)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell message_;
  sampgdk_log_debug("SendPlayerMessageToPlayer(%d, %d, \"%s\")", playerid, senderid, message);
  native = sampgdk_native_find_flexible("SendPlayerMessageToPlayer", native);
  sampgdk_fakeamx_push_string(message, NULL, &message_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)senderid;
  params[3] = message_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(message_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SendPlayerMessageToAll(int senderid, const char * message)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell message_;
  sampgdk_log_debug("SendPlayerMessageToAll(%d, \"%s\")", senderid, message);
  native = sampgdk_native_find_flexible("SendPlayerMessageToAll", native);
  sampgdk_fakeamx_push_string(message, NULL, &message_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)senderid;
  params[2] = message_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(message_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SendDeathMessage(int killer, int killee, int weapon)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("SendDeathMessage(%d, %d, %d)", killer, killee, weapon);
  native = sampgdk_native_find_flexible("SendDeathMessage", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)killer;
  params[2] = (cell)killee;
  params[3] = (cell)weapon;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SendDeathMessageToPlayer(int playerid, int killer, int killee, int weapon)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("SendDeathMessageToPlayer(%d, %d, %d, %d)", playerid, killer, killee, weapon);
  native = sampgdk_native_find_flexible("SendDeathMessageToPlayer", native);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)killer;
  params[3] = (cell)killee;
  params[4] = (cell)weapon;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GameTextForAll(const char * text, int time, int style)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell text_;
  sampgdk_log_debug("GameTextForAll(\"%s\", %d, %d)", text, time, style);
  native = sampgdk_native_find_flexible("GameTextForAll", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 3 * sizeof(cell);
  params[1] = text_;
  params[2] = (cell)time;
  params[3] = (cell)style;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GameTextForPlayer(int playerid, const char * text, int time, int style)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell text_;
  sampgdk_log_debug("GameTextForPlayer(%d, \"%s\", %d, %d)", playerid, text, time, style);
  native = sampgdk_native_find_flexible("GameTextForPlayer", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = text_;
  params[3] = (cell)time;
  params[4] = (cell)style;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetTickCount()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("GetTickCount()");
  native = sampgdk_native_find_flexible("GetTickCount", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetMaxPlayers()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("GetMaxPlayers()");
  native = sampgdk_native_find_flexible("GetMaxPlayers", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(float, VectorSize(float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("VectorSize(%f, %f, %f)", x, y, z);
  native = sampgdk_native_find_flexible("VectorSize", native);
  params[0] = 3 * sizeof(cell);
  params[1] = amx_ftoc(x);
  params[2] = amx_ftoc(y);
  params[3] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(int, GetPlayerPoolSize()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("GetPlayerPoolSize()");
  native = sampgdk_native_find_flexible("GetPlayerPoolSize", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetVehiclePoolSize()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("GetVehiclePoolSize()");
  native = sampgdk_native_find_flexible("GetVehiclePoolSize", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetActorPoolSize()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("GetActorPoolSize()");
  native = sampgdk_native_find_flexible("GetActorPoolSize", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetGameModeText(const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell text_;
  sampgdk_log_debug("SetGameModeText(\"%s\")", text);
  native = sampgdk_native_find_flexible("SetGameModeText", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 1 * sizeof(cell);
  params[1] = text_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetTeamCount(int count)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetTeamCount(%d)", count);
  native = sampgdk_native_find_flexible("SetTeamCount", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)count;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[12];
  sampgdk_log_debug("AddPlayerClass(%d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d)", modelid, spawn_x, spawn_y, spawn_z, z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
  native = sampgdk_native_find_flexible("AddPlayerClass", native);
  params[0] = 11 * sizeof(cell);
  params[1] = (cell)modelid;
  params[2] = amx_ftoc(spawn_x);
  params[3] = amx_ftoc(spawn_y);
  params[4] = amx_ftoc(spawn_z);
  params[5] = amx_ftoc(z_angle);
  params[6] = (cell)weapon1;
  params[7] = (cell)weapon1_ammo;
  params[8] = (cell)weapon2;
  params[9] = (cell)weapon2_ammo;
  params[10] = (cell)weapon3;
  params[11] = (cell)weapon3_ammo;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[13];
  sampgdk_log_debug("AddPlayerClassEx(%d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d)", teamid, modelid, spawn_x, spawn_y, spawn_z, z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
  native = sampgdk_native_find_flexible("AddPlayerClassEx", native);
  params[0] = 12 * sizeof(cell);
  params[1] = (cell)teamid;
  params[2] = (cell)modelid;
  params[3] = amx_ftoc(spawn_x);
  params[4] = amx_ftoc(spawn_y);
  params[5] = amx_ftoc(spawn_z);
  params[6] = amx_ftoc(z_angle);
  params[7] = (cell)weapon1;
  params[8] = (cell)weapon1_ammo;
  params[9] = (cell)weapon2;
  params[10] = (cell)weapon2_ammo;
  params[11] = (cell)weapon3;
  params[12] = (cell)weapon3_ammo;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[8];
  sampgdk_log_debug("AddStaticVehicle(%d, %f, %f, %f, %f, %d, %d)", modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2);
  native = sampgdk_native_find_flexible("AddStaticVehicle", native);
  params[0] = 7 * sizeof(cell);
  params[1] = (cell)modelid;
  params[2] = amx_ftoc(spawn_x);
  params[3] = amx_ftoc(spawn_y);
  params[4] = amx_ftoc(spawn_z);
  params[5] = amx_ftoc(z_angle);
  params[6] = (cell)color1;
  params[7] = (cell)color2;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay, bool addsiren)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  sampgdk_log_debug("AddStaticVehicleEx(%d, %f, %f, %f, %f, %d, %d, %d, %d)", modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay, addsiren);
  native = sampgdk_native_find_flexible("AddStaticVehicleEx", native);
  params[0] = 9 * sizeof(cell);
  params[1] = (cell)modelid;
  params[2] = amx_ftoc(spawn_x);
  params[3] = amx_ftoc(spawn_y);
  params[4] = amx_ftoc(spawn_z);
  params[5] = amx_ftoc(z_angle);
  params[6] = (cell)color1;
  params[7] = (cell)color2;
  params[8] = (cell)respawn_delay;
  params[9] = (cell)addsiren;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, AddStaticPickup(int model, int type, float x, float y, float z, int virtualworld)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  sampgdk_log_debug("AddStaticPickup(%d, %d, %f, %f, %f, %d)", model, type, x, y, z, virtualworld);
  native = sampgdk_native_find_flexible("AddStaticPickup", native);
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)model;
  params[2] = (cell)type;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  params[6] = (cell)virtualworld;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, CreatePickup(int model, int type, float x, float y, float z, int virtualworld)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  sampgdk_log_debug("CreatePickup(%d, %d, %f, %f, %f, %d)", model, type, x, y, z, virtualworld);
  native = sampgdk_native_find_flexible("CreatePickup", native);
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)model;
  params[2] = (cell)type;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  params[6] = (cell)virtualworld;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, DestroyPickup(int pickup)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DestroyPickup(%d)", pickup);
  native = sampgdk_native_find_flexible("DestroyPickup", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)pickup;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ShowNameTags(bool show)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("ShowNameTags(%d)", show);
  native = sampgdk_native_find_flexible("ShowNameTags", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)show;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ShowPlayerMarkers(int mode)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("ShowPlayerMarkers(%d)", mode);
  native = sampgdk_native_find_flexible("ShowPlayerMarkers", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)mode;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GameModeExit()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("GameModeExit()");
  native = sampgdk_native_find_flexible("GameModeExit", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetWorldTime(int hour)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetWorldTime(%d)", hour);
  native = sampgdk_native_find_flexible("SetWorldTime", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)hour;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetWeaponName(int weaponid, char * name, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell name_;
  sampgdk_log_debug("GetWeaponName(%d, \"%s\", %d)", weaponid, name, size);
  native = sampgdk_native_find_flexible("GetWeaponName", native);
  sampgdk_fakeamx_push(size, &name_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)weaponid;
  params[2] = name_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(name_, name, size);
  sampgdk_fakeamx_pop(name_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, EnableTirePopping(bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("EnableTirePopping(%d)", enable);
  native = sampgdk_native_find_flexible("EnableTirePopping", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, EnableVehicleFriendlyFire()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("EnableVehicleFriendlyFire()");
  native = sampgdk_native_find_flexible("EnableVehicleFriendlyFire", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, AllowInteriorWeapons(bool allow)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("AllowInteriorWeapons(%d)", allow);
  native = sampgdk_native_find_flexible("AllowInteriorWeapons", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)allow;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetWeather(int weatherid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetWeather(%d)", weatherid);
  native = sampgdk_native_find_flexible("SetWeather", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)weatherid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetGravity(float gravity)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetGravity(%f)", gravity);
  native = sampgdk_native_find_flexible("SetGravity", native);
  params[0] = 1 * sizeof(cell);
  params[1] = amx_ftoc(gravity);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(float, GetGravity()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("GetGravity()");
  native = sampgdk_native_find_flexible("GetGravity", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(bool, AllowAdminTeleport(bool allow)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("AllowAdminTeleport(%d)", allow);
  native = sampgdk_native_find_flexible("AllowAdminTeleport", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)allow;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetDeathDropAmount(int amount)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetDeathDropAmount(%d)", amount);
  native = sampgdk_native_find_flexible("SetDeathDropAmount", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)amount;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, CreateExplosion(float x, float y, float z, int type, float radius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("CreateExplosion(%f, %f, %f, %d, %f)", x, y, z, type, radius);
  native = sampgdk_native_find_flexible("CreateExplosion", native);
  params[0] = 5 * sizeof(cell);
  params[1] = amx_ftoc(x);
  params[2] = amx_ftoc(y);
  params[3] = amx_ftoc(z);
  params[4] = (cell)type;
  params[5] = amx_ftoc(radius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, EnableZoneNames(bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("EnableZoneNames(%d)", enable);
  native = sampgdk_native_find_flexible("EnableZoneNames", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, UsePlayerPedAnims()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("UsePlayerPedAnims()");
  native = sampgdk_native_find_flexible("UsePlayerPedAnims", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DisableInteriorEnterExits()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("DisableInteriorEnterExits()");
  native = sampgdk_native_find_flexible("DisableInteriorEnterExits", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SetNameTagDrawDistance(float distance)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("SetNameTagDrawDistance(%f)", distance);
  native = sampgdk_native_find_flexible("SetNameTagDrawDistance", native);
  params[0] = 1 * sizeof(cell);
  params[1] = amx_ftoc(distance);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DisableNameTagLOS()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("DisableNameTagLOS()");
  native = sampgdk_native_find_flexible("DisableNameTagLOS", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, LimitGlobalChatRadius(float chat_radius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("LimitGlobalChatRadius(%f)", chat_radius);
  native = sampgdk_native_find_flexible("LimitGlobalChatRadius", native);
  params[0] = 1 * sizeof(cell);
  params[1] = amx_ftoc(chat_radius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, LimitPlayerMarkerRadius(float marker_radius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("LimitPlayerMarkerRadius(%f)", marker_radius);
  native = sampgdk_native_find_flexible("LimitPlayerMarkerRadius", native);
  params[0] = 1 * sizeof(cell);
  params[1] = amx_ftoc(marker_radius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ConnectNPC(const char * name, const char * script)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell name_;
  cell script_;
  sampgdk_log_debug("ConnectNPC(\"%s\", \"%s\")", name, script);
  native = sampgdk_native_find_flexible("ConnectNPC", native);
  sampgdk_fakeamx_push_string(name, NULL, &name_);
  sampgdk_fakeamx_push_string(script, NULL, &script_);
  params[0] = 2 * sizeof(cell);
  params[1] = name_;
  params[2] = script_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(script_);
  sampgdk_fakeamx_pop(name_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerNPC(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsPlayerNPC(%d)", playerid);
  native = sampgdk_native_find_flexible("IsPlayerNPC", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerAdmin(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsPlayerAdmin(%d)", playerid);
  native = sampgdk_native_find_flexible("IsPlayerAdmin", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, Kick(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("Kick(%d)", playerid);
  native = sampgdk_native_find_flexible("Kick", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, Ban(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("Ban(%d)", playerid);
  native = sampgdk_native_find_flexible("Ban", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, BanEx(int playerid, const char * reason)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell reason_;
  sampgdk_log_debug("BanEx(%d, \"%s\")", playerid, reason);
  native = sampgdk_native_find_flexible("BanEx", native);
  sampgdk_fakeamx_push_string(reason, NULL, &reason_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = reason_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(reason_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SendRconCommand(const char * command)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell command_;
  sampgdk_log_debug("SendRconCommand(\"%s\")", command);
  native = sampgdk_native_find_flexible("SendRconCommand", native);
  sampgdk_fakeamx_push_string(command, NULL, &command_);
  params[0] = 1 * sizeof(cell);
  params[1] = command_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(command_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetServerVarAsString(const char * varname, char * value, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell varname_;
  cell value_;
  sampgdk_log_debug("GetServerVarAsString(\"%s\", \"%s\", %d)", varname, value, size);
  native = sampgdk_native_find_flexible("GetServerVarAsString", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  sampgdk_fakeamx_push(size, &value_);
  params[0] = 3 * sizeof(cell);
  params[1] = varname_;
  params[2] = value_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(value_, value, size);
  sampgdk_fakeamx_pop(value_);
  sampgdk_fakeamx_pop(varname_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetServerVarAsInt(const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell varname_;
  sampgdk_log_debug("GetServerVarAsInt(\"%s\")", varname);
  native = sampgdk_native_find_flexible("GetServerVarAsInt", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 1 * sizeof(cell);
  params[1] = varname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GetServerVarAsBool(const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell varname_;
  sampgdk_log_debug("GetServerVarAsBool(\"%s\")", varname);
  native = sampgdk_native_find_flexible("GetServerVarAsBool", native);
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 1 * sizeof(cell);
  params[1] = varname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerNetworkStats(int playerid, char * retstr, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell retstr_;
  sampgdk_log_debug("GetPlayerNetworkStats(%d, \"%s\", %d)", playerid, retstr, size);
  native = sampgdk_native_find_flexible("GetPlayerNetworkStats", native);
  sampgdk_fakeamx_push(size, &retstr_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = retstr_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(retstr_, retstr, size);
  sampgdk_fakeamx_pop(retstr_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetNetworkStats(char * retstr, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell retstr_;
  sampgdk_log_debug("GetNetworkStats(\"%s\", %d)", retstr, size);
  native = sampgdk_native_find_flexible("GetNetworkStats", native);
  sampgdk_fakeamx_push(size, &retstr_);
  params[0] = 2 * sizeof(cell);
  params[1] = retstr_;
  params[2] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(retstr_, retstr, size);
  sampgdk_fakeamx_pop(retstr_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerVersion(int playerid, char * version, int len)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell version_;
  sampgdk_log_debug("GetPlayerVersion(%d, \"%s\", %d)", playerid, version, len);
  native = sampgdk_native_find_flexible("GetPlayerVersion", native);
  sampgdk_fakeamx_push(len, &version_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = version_;
  params[3] = (cell)len;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(version_, version, len);
  sampgdk_fakeamx_pop(version_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, BlockIpAddress(const char * ip_address, int timems)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell ip_address_;
  sampgdk_log_debug("BlockIpAddress(\"%s\", %d)", ip_address, timems);
  native = sampgdk_native_find_flexible("BlockIpAddress", native);
  sampgdk_fakeamx_push_string(ip_address, NULL, &ip_address_);
  params[0] = 2 * sizeof(cell);
  params[1] = ip_address_;
  params[2] = (cell)timems;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(ip_address_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, UnBlockIpAddress(const char * ip_address)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell ip_address_;
  sampgdk_log_debug("UnBlockIpAddress(\"%s\")", ip_address);
  native = sampgdk_native_find_flexible("UnBlockIpAddress", native);
  sampgdk_fakeamx_push_string(ip_address, NULL, &ip_address_);
  params[0] = 1 * sizeof(cell);
  params[1] = ip_address_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(ip_address_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetServerTickRate()) {
  static AMX_NATIVE native;
  cell retval;
  sampgdk_log_debug("GetServerTickRate()");
  native = sampgdk_native_find_flexible("GetServerTickRate", native);
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_GetConnectedTime(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("NetStats_GetConnectedTime(%d)", playerid);
  native = sampgdk_native_find_flexible("NetStats_GetConnectedTime", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_MessagesReceived(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("NetStats_MessagesReceived(%d)", playerid);
  native = sampgdk_native_find_flexible("NetStats_MessagesReceived", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_BytesReceived(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("NetStats_BytesReceived(%d)", playerid);
  native = sampgdk_native_find_flexible("NetStats_BytesReceived", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_MessagesSent(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("NetStats_MessagesSent(%d)", playerid);
  native = sampgdk_native_find_flexible("NetStats_MessagesSent", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_BytesSent(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("NetStats_BytesSent(%d)", playerid);
  native = sampgdk_native_find_flexible("NetStats_BytesSent", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_MessagesRecvPerSecond(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("NetStats_MessagesRecvPerSecond(%d)", playerid);
  native = sampgdk_native_find_flexible("NetStats_MessagesRecvPerSecond", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(float, NetStats_PacketLossPercent(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("NetStats_PacketLossPercent(%d)", playerid);
  native = sampgdk_native_find_flexible("NetStats_PacketLossPercent", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(int, NetStats_ConnectionStatus(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("NetStats_ConnectionStatus(%d)", playerid);
  native = sampgdk_native_find_flexible("NetStats_ConnectionStatus", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, NetStats_GetIpPort(int playerid, char * ip_port, int ip_port_len)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell ip_port_;
  sampgdk_log_debug("NetStats_GetIpPort(%d, \"%s\", %d)", playerid, ip_port, ip_port_len);
  native = sampgdk_native_find_flexible("NetStats_GetIpPort", native);
  sampgdk_fakeamx_push(ip_port_len, &ip_port_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = ip_port_;
  params[3] = (cell)ip_port_len;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(ip_port_, ip_port, ip_port_len);
  sampgdk_fakeamx_pop(ip_port_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, CreateMenu(const char * title, int columns, float x, float y, float col1width, float col2width)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  cell title_;
  sampgdk_log_debug("CreateMenu(\"%s\", %d, %f, %f, %f, %f)", title, columns, x, y, col1width, col2width);
  native = sampgdk_native_find_flexible("CreateMenu", native);
  sampgdk_fakeamx_push_string(title, NULL, &title_);
  params[0] = 6 * sizeof(cell);
  params[1] = title_;
  params[2] = (cell)columns;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(col1width);
  params[6] = amx_ftoc(col2width);
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(title_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, DestroyMenu(int menuid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DestroyMenu(%d)", menuid);
  native = sampgdk_native_find_flexible("DestroyMenu", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)menuid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, AddMenuItem(int menuid, int column, const char * menutext)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell menutext_;
  sampgdk_log_debug("AddMenuItem(%d, %d, \"%s\")", menuid, column, menutext);
  native = sampgdk_native_find_flexible("AddMenuItem", native);
  sampgdk_fakeamx_push_string(menutext, NULL, &menutext_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)column;
  params[3] = menutext_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(menutext_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetMenuColumnHeader(int menuid, int column, const char * columnheader)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell columnheader_;
  sampgdk_log_debug("SetMenuColumnHeader(%d, %d, \"%s\")", menuid, column, columnheader);
  native = sampgdk_native_find_flexible("SetMenuColumnHeader", native);
  sampgdk_fakeamx_push_string(columnheader, NULL, &columnheader_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)column;
  params[3] = columnheader_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(columnheader_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ShowMenuForPlayer(int menuid, int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("ShowMenuForPlayer(%d, %d)", menuid, playerid);
  native = sampgdk_native_find_flexible("ShowMenuForPlayer", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, HideMenuForPlayer(int menuid, int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("HideMenuForPlayer(%d, %d)", menuid, playerid);
  native = sampgdk_native_find_flexible("HideMenuForPlayer", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, IsValidMenu(int menuid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("IsValidMenu(%d)", menuid);
  native = sampgdk_native_find_flexible("IsValidMenu", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)menuid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DisableMenu(int menuid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("DisableMenu(%d)", menuid);
  native = sampgdk_native_find_flexible("DisableMenu", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)menuid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, DisableMenuRow(int menuid, int row)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("DisableMenuRow(%d, %d)", menuid, row);
  native = sampgdk_native_find_flexible("DisableMenuRow", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)row;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GetPlayerMenu(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GetPlayerMenu(%d)", playerid);
  native = sampgdk_native_find_flexible("GetPlayerMenu", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, TextDrawCreate(float x, float y, const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell text_;
  sampgdk_log_debug("TextDrawCreate(%f, %f, \"%s\")", x, y, text);
  native = sampgdk_native_find_flexible("TextDrawCreate", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 3 * sizeof(cell);
  params[1] = amx_ftoc(x);
  params[2] = amx_ftoc(y);
  params[3] = text_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawDestroy(int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("TextDrawDestroy(%d)", text);
  native = sampgdk_native_find_flexible("TextDrawDestroy", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawLetterSize(int text, float x, float y)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("TextDrawLetterSize(%d, %f, %f)", text, x, y);
  native = sampgdk_native_find_flexible("TextDrawLetterSize", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawTextSize(int text, float x, float y)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("TextDrawTextSize(%d, %f, %f)", text, x, y);
  native = sampgdk_native_find_flexible("TextDrawTextSize", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawAlignment(int text, int alignment)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawAlignment(%d, %d)", text, alignment);
  native = sampgdk_native_find_flexible("TextDrawAlignment", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)alignment;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawColor(int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawColor(%d, %d)", text, color);
  native = sampgdk_native_find_flexible("TextDrawColor", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawUseBox(int text, bool use)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawUseBox(%d, %d)", text, use);
  native = sampgdk_native_find_flexible("TextDrawUseBox", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)use;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawBoxColor(int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawBoxColor(%d, %d)", text, color);
  native = sampgdk_native_find_flexible("TextDrawBoxColor", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetShadow(int text, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawSetShadow(%d, %d)", text, size);
  native = sampgdk_native_find_flexible("TextDrawSetShadow", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetOutline(int text, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawSetOutline(%d, %d)", text, size);
  native = sampgdk_native_find_flexible("TextDrawSetOutline", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawBackgroundColor(int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawBackgroundColor(%d, %d)", text, color);
  native = sampgdk_native_find_flexible("TextDrawBackgroundColor", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawFont(int text, int font)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawFont(%d, %d)", text, font);
  native = sampgdk_native_find_flexible("TextDrawFont", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)font;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetProportional(int text, bool set)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawSetProportional(%d, %d)", text, set);
  native = sampgdk_native_find_flexible("TextDrawSetProportional", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)set;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetSelectable(int text, bool set)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawSetSelectable(%d, %d)", text, set);
  native = sampgdk_native_find_flexible("TextDrawSetSelectable", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)set;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawShowForPlayer(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawShowForPlayer(%d, %d)", playerid, text);
  native = sampgdk_native_find_flexible("TextDrawShowForPlayer", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawHideForPlayer(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawHideForPlayer(%d, %d)", playerid, text);
  native = sampgdk_native_find_flexible("TextDrawHideForPlayer", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawShowForAll(int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("TextDrawShowForAll(%d)", text);
  native = sampgdk_native_find_flexible("TextDrawShowForAll", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawHideForAll(int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("TextDrawHideForAll(%d)", text);
  native = sampgdk_native_find_flexible("TextDrawHideForAll", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetString(int text, const char * string)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell string_;
  sampgdk_log_debug("TextDrawSetString(%d, \"%s\")", text, string);
  native = sampgdk_native_find_flexible("TextDrawSetString", native);
  sampgdk_fakeamx_push_string(string, NULL, &string_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = string_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(string_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetPreviewModel(int text, int modelindex)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("TextDrawSetPreviewModel(%d, %d)", text, modelindex);
  native = sampgdk_native_find_flexible("TextDrawSetPreviewModel", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)modelindex;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetPreviewRot(int text, float fRotX, float fRotY, float fRotZ, float fZoom)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("TextDrawSetPreviewRot(%d, %f, %f, %f, %f)", text, fRotX, fRotY, fRotZ, fZoom);
  native = sampgdk_native_find_flexible("TextDrawSetPreviewRot", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = amx_ftoc(fRotX);
  params[3] = amx_ftoc(fRotY);
  params[4] = amx_ftoc(fRotZ);
  params[5] = amx_ftoc(fZoom);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetPreviewVehCol(int text, int color1, int color2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("TextDrawSetPreviewVehCol(%d, %d, %d)", text, color1, color2);
  native = sampgdk_native_find_flexible("TextDrawSetPreviewVehCol", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)color1;
  params[3] = (cell)color2;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, SelectTextDraw(int playerid, int hovercolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("SelectTextDraw(%d, %d)", playerid, hovercolor);
  native = sampgdk_native_find_flexible("SelectTextDraw", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)hovercolor;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, CancelSelectTextDraw(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("CancelSelectTextDraw(%d)", playerid);
  native = sampgdk_native_find_flexible("CancelSelectTextDraw", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, GangZoneCreate(float minx, float miny, float maxx, float maxy)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  sampgdk_log_debug("GangZoneCreate(%f, %f, %f, %f)", minx, miny, maxx, maxy);
  native = sampgdk_native_find_flexible("GangZoneCreate", native);
  params[0] = 4 * sizeof(cell);
  params[1] = amx_ftoc(minx);
  params[2] = amx_ftoc(miny);
  params[3] = amx_ftoc(maxx);
  params[4] = amx_ftoc(maxy);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneDestroy(int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GangZoneDestroy(%d)", zone);
  native = sampgdk_native_find_flexible("GangZoneDestroy", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GangZoneShowForPlayer(int playerid, int zone, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("GangZoneShowForPlayer(%d, %d, %d)", playerid, zone, color);
  native = sampgdk_native_find_flexible("GangZoneShowForPlayer", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)zone;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GangZoneShowForAll(int zone, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("GangZoneShowForAll(%d, %d)", zone, color);
  native = sampgdk_native_find_flexible("GangZoneShowForAll", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)zone;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GangZoneHideForPlayer(int playerid, int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("GangZoneHideForPlayer(%d, %d)", playerid, zone);
  native = sampgdk_native_find_flexible("GangZoneHideForPlayer", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GangZoneHideForAll(int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GangZoneHideForAll(%d)", zone);
  native = sampgdk_native_find_flexible("GangZoneHideForAll", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GangZoneFlashForPlayer(int playerid, int zone, int flashcolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  sampgdk_log_debug("GangZoneFlashForPlayer(%d, %d, %d)", playerid, zone, flashcolor);
  native = sampgdk_native_find_flexible("GangZoneFlashForPlayer", native);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)zone;
  params[3] = (cell)flashcolor;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GangZoneFlashForAll(int zone, int flashcolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("GangZoneFlashForAll(%d, %d)", zone, flashcolor);
  native = sampgdk_native_find_flexible("GangZoneFlashForAll", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)zone;
  params[2] = (cell)flashcolor;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GangZoneStopFlashForPlayer(int playerid, int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("GangZoneStopFlashForPlayer(%d, %d)", playerid, zone);
  native = sampgdk_native_find_flexible("GangZoneStopFlashForPlayer", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, GangZoneStopFlashForAll(int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("GangZoneStopFlashForAll(%d)", zone);
  native = sampgdk_native_find_flexible("GangZoneStopFlashForAll", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(int, Create3DTextLabel(const char * text, int color, float x, float y, float z, float DrawDistance, int virtualworld, bool testLOS)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  cell text_;
  sampgdk_log_debug("Create3DTextLabel(\"%s\", %d, %f, %f, %f, %f, %d, %d)", text, color, x, y, z, DrawDistance, virtualworld, testLOS);
  native = sampgdk_native_find_flexible("Create3DTextLabel", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 8 * sizeof(cell);
  params[1] = text_;
  params[2] = (cell)color;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  params[6] = amx_ftoc(DrawDistance);
  params[7] = (cell)virtualworld;
  params[8] = (cell)testLOS;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, Delete3DTextLabel(int id)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  sampgdk_log_debug("Delete3DTextLabel(%d)", id);
  native = sampgdk_native_find_flexible("Delete3DTextLabel", native);
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)id;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("Attach3DTextLabelToPlayer(%d, %d, %f, %f, %f)", id, playerid, OffsetX, OffsetY, OffsetZ);
  native = sampgdk_native_find_flexible("Attach3DTextLabelToPlayer", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)id;
  params[2] = (cell)playerid;
  params[3] = amx_ftoc(OffsetX);
  params[4] = amx_ftoc(OffsetY);
  params[5] = amx_ftoc(OffsetZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  sampgdk_log_debug("Attach3DTextLabelToVehicle(%d, %d, %f, %f, %f)", id, vehicleid, OffsetX, OffsetY, OffsetZ);
  native = sampgdk_native_find_flexible("Attach3DTextLabelToVehicle", native);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)id;
  params[2] = (cell)vehicleid;
  params[3] = amx_ftoc(OffsetX);
  params[4] = amx_ftoc(OffsetY);
  params[5] = amx_ftoc(OffsetZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, Update3DTextLabelText(int id, int color, const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell text_;
  sampgdk_log_debug("Update3DTextLabelText(%d, %d, \"%s\")", id, color, text);
  native = sampgdk_native_find_flexible("Update3DTextLabelText", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)id;
  params[2] = (cell)color;
  params[3] = text_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return !!(retval);
}

SAMPGDK_NATIVE(int, CreatePlayer3DTextLabel(int playerid, const char * text, int color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[11];
  cell text_;
  sampgdk_log_debug("CreatePlayer3DTextLabel(%d, \"%s\", %d, %f, %f, %f, %f, %d, %d, %d)", playerid, text, color, x, y, z, DrawDistance, attachedplayer, attachedvehicle, testLOS);
  native = sampgdk_native_find_flexible("CreatePlayer3DTextLabel", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 10 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = text_;
  params[3] = (cell)color;
  params[4] = amx_ftoc(x);
  params[5] = amx_ftoc(y);
  params[6] = amx_ftoc(z);
  params[7] = amx_ftoc(DrawDistance);
  params[8] = (cell)attachedplayer;
  params[9] = (cell)attachedvehicle;
  params[10] = (cell)testLOS;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, DeletePlayer3DTextLabel(int playerid, int id)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  sampgdk_log_debug("DeletePlayer3DTextLabel(%d, %d)", playerid, id);
  native = sampgdk_native_find_flexible("DeletePlayer3DTextLabel", native);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)id;
  retval = native(sampgdk_fakeamx_amx(), params);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, UpdatePlayer3DTextLabelText(int playerid, int id, int color, const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell text_;
  sampgdk_log_debug("UpdatePlayer3DTextLabelText(%d, %d, %d, \"%s\")", playerid, id, color, text);
  native = sampgdk_native_find_flexible("UpdatePlayer3DTextLabelText", native);
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)id;
  params[3] = (cell)color;
  params[4] = text_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, ShowPlayerDialog(int playerid, int dialogid, int style, const char * caption, const char * info, const char * button1, const char * button2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[8];
  cell caption_;
  cell info_;
  cell button1_;
  cell button2_;
  sampgdk_log_debug("ShowPlayerDialog(%d, %d, %d, \"%s\", \"%s\", \"%s\", \"%s\")", playerid, dialogid, style, caption, info, button1, button2);
  native = sampgdk_native_find_flexible("ShowPlayerDialog", native);
  sampgdk_fakeamx_push_string(caption, NULL, &caption_);
  sampgdk_fakeamx_push_string(info, NULL, &info_);
  sampgdk_fakeamx_push_string(button1, NULL, &button1_);
  sampgdk_fakeamx_push_string(button2, NULL, &button2_);
  params[0] = 7 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)dialogid;
  params[3] = (cell)style;
  params[4] = caption_;
  params[5] = info_;
  params[6] = button1_;
  params[7] = button2_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(button2_);
  sampgdk_fakeamx_pop(button1_);
  sampgdk_fakeamx_pop(info_);
  sampgdk_fakeamx_pop(caption_);
  return !!(retval);
}

SAMPGDK_NATIVE(bool, gpci(int playerid, char * buffer, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell buffer_;
  sampgdk_log_debug("gpci(%d, \"%s\", %d)", playerid, buffer, size);
  native = sampgdk_native_find_flexible("gpci", native);
  sampgdk_fakeamx_push(size, &buffer_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = buffer_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(buffer_, buffer, size);
  sampgdk_fakeamx_pop(buffer_);
  return !!(retval);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnGameModeInit_callback)();
static bool _OnGameModeInit(AMX *amx, void *callback, cell *retval) {
  sampgdk_log_debug("OnGameModeInit()");
  ((OnGameModeInit_callback)callback)();
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnGameModeExit_callback)();
static bool _OnGameModeExit(AMX *amx, void *callback, cell *retval) {
  sampgdk_log_debug("OnGameModeExit()");
  ((OnGameModeExit_callback)callback)();
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerConnect_callback)(int playerid);
static bool _OnPlayerConnect(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerConnect(%d)", playerid);
  retval_ = ((OnPlayerConnect_callback)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerDisconnect_callback)(int playerid, int reason);
static bool _OnPlayerDisconnect(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int reason;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&reason);
  sampgdk_log_debug("OnPlayerDisconnect(%d, %d)", playerid, reason);
  retval_ = ((OnPlayerDisconnect_callback)callback)(playerid, reason);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerSpawn_callback)(int playerid);
static bool _OnPlayerSpawn(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerSpawn(%d)", playerid);
  retval_ = ((OnPlayerSpawn_callback)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerDeath_callback)(int playerid, int killerid, int reason);
static bool _OnPlayerDeath(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int killerid;
  int reason;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&killerid);
  sampgdk_param_get_cell(amx, 2, (void *)&reason);
  sampgdk_log_debug("OnPlayerDeath(%d, %d, %d)", playerid, killerid, reason);
  retval_ = ((OnPlayerDeath_callback)callback)(playerid, killerid, reason);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleSpawn_callback)(int vehicleid);
static bool _OnVehicleSpawn(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int vehicleid;
  sampgdk_param_get_cell(amx, 0, (void *)&vehicleid);
  sampgdk_log_debug("OnVehicleSpawn(%d)", vehicleid);
  retval_ = ((OnVehicleSpawn_callback)callback)(vehicleid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleDeath_callback)(int vehicleid, int killerid);
static bool _OnVehicleDeath(AMX *amx, void *callback, cell *retval) {
  int vehicleid;
  int killerid;
  sampgdk_param_get_cell(amx, 0, (void *)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void *)&killerid);
  sampgdk_log_debug("OnVehicleDeath(%d, %d)", vehicleid, killerid);
  ((OnVehicleDeath_callback)callback)(vehicleid, killerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerText_callback)(int playerid, const char * text);
static bool _OnPlayerText(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  const char * text;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_string(amx, 1, (void *)&text);
  sampgdk_log_debug("OnPlayerText(%d, \"%s\")", playerid, text);
  retval_ = ((OnPlayerText_callback)callback)(playerid, text);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void *)text);
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerCommandText_callback)(int playerid, const char * cmdtext);
static bool _OnPlayerCommandText(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  const char * cmdtext;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_string(amx, 1, (void *)&cmdtext);
  sampgdk_log_debug("OnPlayerCommandText(%d, \"%s\")", playerid, cmdtext);
  retval_ = ((OnPlayerCommandText_callback)callback)(playerid, cmdtext);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void *)cmdtext);
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerRequestClass_callback)(int playerid, int classid);
static bool _OnPlayerRequestClass(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int classid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&classid);
  sampgdk_log_debug("OnPlayerRequestClass(%d, %d)", playerid, classid);
  ((OnPlayerRequestClass_callback)callback)(playerid, classid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEnterVehicle_callback)(int playerid, int vehicleid, bool ispassenger);
static bool _OnPlayerEnterVehicle(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int vehicleid;
  bool ispassenger;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&vehicleid);
  sampgdk_param_get_bool(amx, 2, (void *)&ispassenger);
  sampgdk_log_debug("OnPlayerEnterVehicle(%d, %d, %d)", playerid, vehicleid, ispassenger);
  ((OnPlayerEnterVehicle_callback)callback)(playerid, vehicleid, ispassenger);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerExitVehicle_callback)(int playerid, int vehicleid);
static bool _OnPlayerExitVehicle(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int vehicleid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&vehicleid);
  sampgdk_log_debug("OnPlayerExitVehicle(%d, %d)", playerid, vehicleid);
  ((OnPlayerExitVehicle_callback)callback)(playerid, vehicleid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerStateChange_callback)(int playerid, int newstate, int oldstate);
static bool _OnPlayerStateChange(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int newstate;
  int oldstate;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&newstate);
  sampgdk_param_get_cell(amx, 2, (void *)&oldstate);
  sampgdk_log_debug("OnPlayerStateChange(%d, %d, %d)", playerid, newstate, oldstate);
  ((OnPlayerStateChange_callback)callback)(playerid, newstate, oldstate);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEnterCheckpoint_callback)(int playerid);
static bool _OnPlayerEnterCheckpoint(AMX *amx, void *callback, cell *retval) {
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerEnterCheckpoint(%d)", playerid);
  ((OnPlayerEnterCheckpoint_callback)callback)(playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerLeaveCheckpoint_callback)(int playerid);
static bool _OnPlayerLeaveCheckpoint(AMX *amx, void *callback, cell *retval) {
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerLeaveCheckpoint(%d)", playerid);
  ((OnPlayerLeaveCheckpoint_callback)callback)(playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEnterRaceCheckpoint_callback)(int playerid);
static bool _OnPlayerEnterRaceCheckpoint(AMX *amx, void *callback, cell *retval) {
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerEnterRaceCheckpoint(%d)", playerid);
  ((OnPlayerEnterRaceCheckpoint_callback)callback)(playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerLeaveRaceCheckpoint_callback)(int playerid);
static bool _OnPlayerLeaveRaceCheckpoint(AMX *amx, void *callback, cell *retval) {
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerLeaveRaceCheckpoint(%d)", playerid);
  ((OnPlayerLeaveRaceCheckpoint_callback)callback)(playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnRconCommand_callback)(const char * cmd);
static bool _OnRconCommand(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  const char * cmd;
  sampgdk_param_get_string(amx, 0, (void *)&cmd);
  sampgdk_log_debug("OnRconCommand(\"%s\")", cmd);
  retval_ = ((OnRconCommand_callback)callback)(cmd);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void *)cmd);
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerRequestSpawn_callback)(int playerid);
static bool _OnPlayerRequestSpawn(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerRequestSpawn(%d)", playerid);
  retval_ = ((OnPlayerRequestSpawn_callback)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnObjectMoved_callback)(int objectid);
static bool _OnObjectMoved(AMX *amx, void *callback, cell *retval) {
  int objectid;
  sampgdk_param_get_cell(amx, 0, (void *)&objectid);
  sampgdk_log_debug("OnObjectMoved(%d)", objectid);
  ((OnObjectMoved_callback)callback)(objectid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerObjectMoved_callback)(int playerid, int objectid);
static bool _OnPlayerObjectMoved(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int objectid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&objectid);
  sampgdk_log_debug("OnPlayerObjectMoved(%d, %d)", playerid, objectid);
  ((OnPlayerObjectMoved_callback)callback)(playerid, objectid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerPickUpPickup_callback)(int playerid, int pickupid);
static bool _OnPlayerPickUpPickup(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int pickupid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&pickupid);
  sampgdk_log_debug("OnPlayerPickUpPickup(%d, %d)", playerid, pickupid);
  ((OnPlayerPickUpPickup_callback)callback)(playerid, pickupid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleMod_callback)(int playerid, int vehicleid, int componentid);
static bool _OnVehicleMod(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int vehicleid;
  int componentid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&vehicleid);
  sampgdk_param_get_cell(amx, 2, (void *)&componentid);
  sampgdk_log_debug("OnVehicleMod(%d, %d, %d)", playerid, vehicleid, componentid);
  retval_ = ((OnVehicleMod_callback)callback)(playerid, vehicleid, componentid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnEnterExitModShop_callback)(int playerid, int enterexit, int interiorid);
static bool _OnEnterExitModShop(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int enterexit;
  int interiorid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&enterexit);
  sampgdk_param_get_cell(amx, 2, (void *)&interiorid);
  sampgdk_log_debug("OnEnterExitModShop(%d, %d, %d)", playerid, enterexit, interiorid);
  ((OnEnterExitModShop_callback)callback)(playerid, enterexit, interiorid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehiclePaintjob_callback)(int playerid, int vehicleid, int paintjobid);
static bool _OnVehiclePaintjob(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int vehicleid;
  int paintjobid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&vehicleid);
  sampgdk_param_get_cell(amx, 2, (void *)&paintjobid);
  sampgdk_log_debug("OnVehiclePaintjob(%d, %d, %d)", playerid, vehicleid, paintjobid);
  retval_ = ((OnVehiclePaintjob_callback)callback)(playerid, vehicleid, paintjobid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleRespray_callback)(int playerid, int vehicleid, int color1, int color2);
static bool _OnVehicleRespray(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int vehicleid;
  int color1;
  int color2;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&vehicleid);
  sampgdk_param_get_cell(amx, 2, (void *)&color1);
  sampgdk_param_get_cell(amx, 3, (void *)&color2);
  sampgdk_log_debug("OnVehicleRespray(%d, %d, %d, %d)", playerid, vehicleid, color1, color2);
  ((OnVehicleRespray_callback)callback)(playerid, vehicleid, color1, color2);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleDamageStatusUpdate_callback)(int vehicleid, int playerid);
static bool _OnVehicleDamageStatusUpdate(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int vehicleid;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void *)&playerid);
  sampgdk_log_debug("OnVehicleDamageStatusUpdate(%d, %d)", vehicleid, playerid);
  retval_ = ((OnVehicleDamageStatusUpdate_callback)callback)(vehicleid, playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnUnoccupiedVehicleUpdate_callback)(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z);
static bool _OnUnoccupiedVehicleUpdate(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int vehicleid;
  int playerid;
  int passenger_seat;
  float new_x;
  float new_y;
  float new_z;
  float vel_x;
  float vel_y;
  float vel_z;
  sampgdk_param_get_cell(amx, 0, (void *)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void *)&playerid);
  sampgdk_param_get_cell(amx, 2, (void *)&passenger_seat);
  sampgdk_param_get_float(amx, 3, (void *)&new_x);
  sampgdk_param_get_float(amx, 4, (void *)&new_y);
  sampgdk_param_get_float(amx, 5, (void *)&new_z);
  sampgdk_param_get_float(amx, 6, (void *)&vel_x);
  sampgdk_param_get_float(amx, 7, (void *)&vel_y);
  sampgdk_param_get_float(amx, 8, (void *)&vel_z);
  sampgdk_log_debug("OnUnoccupiedVehicleUpdate(%d, %d, %d, %f, %f, %f, %f, %f, %f)", vehicleid, playerid, passenger_seat, new_x, new_y, new_z, vel_x, vel_y, vel_z);
  retval_ = ((OnUnoccupiedVehicleUpdate_callback)callback)(vehicleid, playerid, passenger_seat, new_x, new_y, new_z, vel_x, vel_y, vel_z);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerSelectedMenuRow_callback)(int playerid, int row);
static bool _OnPlayerSelectedMenuRow(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int row;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&row);
  sampgdk_log_debug("OnPlayerSelectedMenuRow(%d, %d)", playerid, row);
  ((OnPlayerSelectedMenuRow_callback)callback)(playerid, row);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerExitedMenu_callback)(int playerid);
static bool _OnPlayerExitedMenu(AMX *amx, void *callback, cell *retval) {
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerExitedMenu(%d)", playerid);
  ((OnPlayerExitedMenu_callback)callback)(playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerInteriorChange_callback)(int playerid, int newinteriorid, int oldinteriorid);
static bool _OnPlayerInteriorChange(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int newinteriorid;
  int oldinteriorid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&newinteriorid);
  sampgdk_param_get_cell(amx, 2, (void *)&oldinteriorid);
  sampgdk_log_debug("OnPlayerInteriorChange(%d, %d, %d)", playerid, newinteriorid, oldinteriorid);
  ((OnPlayerInteriorChange_callback)callback)(playerid, newinteriorid, oldinteriorid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerKeyStateChange_callback)(int playerid, int newkeys, int oldkeys);
static bool _OnPlayerKeyStateChange(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int newkeys;
  int oldkeys;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&newkeys);
  sampgdk_param_get_cell(amx, 2, (void *)&oldkeys);
  sampgdk_log_debug("OnPlayerKeyStateChange(%d, %d, %d)", playerid, newkeys, oldkeys);
  ((OnPlayerKeyStateChange_callback)callback)(playerid, newkeys, oldkeys);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnRconLoginAttempt_callback)(const char * ip, const char * password, bool success);
static bool _OnRconLoginAttempt(AMX *amx, void *callback, cell *retval) {
  const char * ip;
  const char * password;
  bool success;
  sampgdk_param_get_string(amx, 0, (void *)&ip);
  sampgdk_param_get_string(amx, 1, (void *)&password);
  sampgdk_param_get_bool(amx, 2, (void *)&success);
  sampgdk_log_debug("OnRconLoginAttempt(\"%s\", \"%s\", %d)", ip, password, success);
  ((OnRconLoginAttempt_callback)callback)(ip, password, success);
  free((void *)ip);
  free((void *)password);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerUpdate_callback)(int playerid);
static bool _OnPlayerUpdate(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_log_debug("OnPlayerUpdate(%d)", playerid);
  retval_ = ((OnPlayerUpdate_callback)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerStreamIn_callback)(int playerid, int forplayerid);
static bool _OnPlayerStreamIn(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&forplayerid);
  sampgdk_log_debug("OnPlayerStreamIn(%d, %d)", playerid, forplayerid);
  ((OnPlayerStreamIn_callback)callback)(playerid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerStreamOut_callback)(int playerid, int forplayerid);
static bool _OnPlayerStreamOut(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&forplayerid);
  sampgdk_log_debug("OnPlayerStreamOut(%d, %d)", playerid, forplayerid);
  ((OnPlayerStreamOut_callback)callback)(playerid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleStreamIn_callback)(int vehicleid, int forplayerid);
static bool _OnVehicleStreamIn(AMX *amx, void *callback, cell *retval) {
  int vehicleid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void *)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void *)&forplayerid);
  sampgdk_log_debug("OnVehicleStreamIn(%d, %d)", vehicleid, forplayerid);
  ((OnVehicleStreamIn_callback)callback)(vehicleid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleStreamOut_callback)(int vehicleid, int forplayerid);
static bool _OnVehicleStreamOut(AMX *amx, void *callback, cell *retval) {
  int vehicleid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void *)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void *)&forplayerid);
  sampgdk_log_debug("OnVehicleStreamOut(%d, %d)", vehicleid, forplayerid);
  ((OnVehicleStreamOut_callback)callback)(vehicleid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnActorStreamIn_callback)(int actorid, int forplayerid);
static bool _OnActorStreamIn(AMX *amx, void *callback, cell *retval) {
  int actorid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void *)&actorid);
  sampgdk_param_get_cell(amx, 1, (void *)&forplayerid);
  sampgdk_log_debug("OnActorStreamIn(%d, %d)", actorid, forplayerid);
  ((OnActorStreamIn_callback)callback)(actorid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnActorStreamOut_callback)(int actorid, int forplayerid);
static bool _OnActorStreamOut(AMX *amx, void *callback, cell *retval) {
  int actorid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void *)&actorid);
  sampgdk_param_get_cell(amx, 1, (void *)&forplayerid);
  sampgdk_log_debug("OnActorStreamOut(%d, %d)", actorid, forplayerid);
  ((OnActorStreamOut_callback)callback)(actorid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnDialogResponse_callback)(int playerid, int dialogid, int response, int listitem, const char * inputtext);
static bool _OnDialogResponse(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int dialogid;
  int response;
  int listitem;
  const char * inputtext;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&dialogid);
  sampgdk_param_get_cell(amx, 2, (void *)&response);
  sampgdk_param_get_cell(amx, 3, (void *)&listitem);
  sampgdk_param_get_string(amx, 4, (void *)&inputtext);
  sampgdk_log_debug("OnDialogResponse(%d, %d, %d, %d, \"%s\")", playerid, dialogid, response, listitem, inputtext);
  retval_ = ((OnDialogResponse_callback)callback)(playerid, dialogid, response, listitem, inputtext);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void *)inputtext);
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerTakeDamage_callback)(int playerid, int issuerid, float amount, int weaponid, int bodypart);
static bool _OnPlayerTakeDamage(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int issuerid;
  float amount;
  int weaponid;
  int bodypart;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&issuerid);
  sampgdk_param_get_float(amx, 2, (void *)&amount);
  sampgdk_param_get_cell(amx, 3, (void *)&weaponid);
  sampgdk_param_get_cell(amx, 4, (void *)&bodypart);
  sampgdk_log_debug("OnPlayerTakeDamage(%d, %d, %f, %d, %d)", playerid, issuerid, amount, weaponid, bodypart);
  retval_ = ((OnPlayerTakeDamage_callback)callback)(playerid, issuerid, amount, weaponid, bodypart);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerGiveDamage_callback)(int playerid, int damagedid, float amount, int weaponid, int bodypart);
static bool _OnPlayerGiveDamage(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int damagedid;
  float amount;
  int weaponid;
  int bodypart;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&damagedid);
  sampgdk_param_get_float(amx, 2, (void *)&amount);
  sampgdk_param_get_cell(amx, 3, (void *)&weaponid);
  sampgdk_param_get_cell(amx, 4, (void *)&bodypart);
  sampgdk_log_debug("OnPlayerGiveDamage(%d, %d, %f, %d, %d)", playerid, damagedid, amount, weaponid, bodypart);
  retval_ = ((OnPlayerGiveDamage_callback)callback)(playerid, damagedid, amount, weaponid, bodypart);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerGiveDamageActor_callback)(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart);
static bool _OnPlayerGiveDamageActor(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int damaged_actorid;
  float amount;
  int weaponid;
  int bodypart;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&damaged_actorid);
  sampgdk_param_get_float(amx, 2, (void *)&amount);
  sampgdk_param_get_cell(amx, 3, (void *)&weaponid);
  sampgdk_param_get_cell(amx, 4, (void *)&bodypart);
  sampgdk_log_debug("OnPlayerGiveDamageActor(%d, %d, %f, %d, %d)", playerid, damaged_actorid, amount, weaponid, bodypart);
  retval_ = ((OnPlayerGiveDamageActor_callback)callback)(playerid, damaged_actorid, amount, weaponid, bodypart);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerClickMap_callback)(int playerid, float fX, float fY, float fZ);
static bool _OnPlayerClickMap(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  float fX;
  float fY;
  float fZ;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_float(amx, 1, (void *)&fX);
  sampgdk_param_get_float(amx, 2, (void *)&fY);
  sampgdk_param_get_float(amx, 3, (void *)&fZ);
  sampgdk_log_debug("OnPlayerClickMap(%d, %f, %f, %f)", playerid, fX, fY, fZ);
  retval_ = ((OnPlayerClickMap_callback)callback)(playerid, fX, fY, fZ);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerClickTextDraw_callback)(int playerid, int clickedid);
static bool _OnPlayerClickTextDraw(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int clickedid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&clickedid);
  sampgdk_log_debug("OnPlayerClickTextDraw(%d, %d)", playerid, clickedid);
  retval_ = ((OnPlayerClickTextDraw_callback)callback)(playerid, clickedid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerClickPlayerTextDraw_callback)(int playerid, int playertextid);
static bool _OnPlayerClickPlayerTextDraw(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int playertextid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&playertextid);
  sampgdk_log_debug("OnPlayerClickPlayerTextDraw(%d, %d)", playerid, playertextid);
  retval_ = ((OnPlayerClickPlayerTextDraw_callback)callback)(playerid, playertextid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnIncomingConnection_callback)(int playerid, const char * ip_address, int port);
static bool _OnIncomingConnection(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  const char * ip_address;
  int port;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_string(amx, 1, (void *)&ip_address);
  sampgdk_param_get_cell(amx, 2, (void *)&port);
  sampgdk_log_debug("OnIncomingConnection(%d, \"%s\", %d)", playerid, ip_address, port);
  retval_ = ((OnIncomingConnection_callback)callback)(playerid, ip_address, port);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void *)ip_address);
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnTrailerUpdate_callback)(int playerid, int vehicleid);
static bool _OnTrailerUpdate(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int vehicleid;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&vehicleid);
  sampgdk_log_debug("OnTrailerUpdate(%d, %d)", playerid, vehicleid);
  retval_ = ((OnTrailerUpdate_callback)callback)(playerid, vehicleid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleSirenStateChange_callback)(int playerid, int vehicleid, bool newstate);
static bool _OnVehicleSirenStateChange(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int vehicleid;
  bool newstate;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&vehicleid);
  sampgdk_param_get_bool(amx, 2, (void *)&newstate);
  sampgdk_log_debug("OnVehicleSirenStateChange(%d, %d, %d)", playerid, vehicleid, newstate);
  ((OnVehicleSirenStateChange_callback)callback)(playerid, vehicleid, newstate);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerClickPlayer_callback)(int playerid, int clickedplayerid, int source);
static bool _OnPlayerClickPlayer(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int clickedplayerid;
  int source;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&clickedplayerid);
  sampgdk_param_get_cell(amx, 2, (void *)&source);
  sampgdk_log_debug("OnPlayerClickPlayer(%d, %d, %d)", playerid, clickedplayerid, source);
  retval_ = ((OnPlayerClickPlayer_callback)callback)(playerid, clickedplayerid, source);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEditObject_callback)(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ);
static bool _OnPlayerEditObject(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  bool playerobject;
  int objectid;
  int response;
  float fX;
  float fY;
  float fZ;
  float fRotX;
  float fRotY;
  float fRotZ;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_bool(amx, 1, (void *)&playerobject);
  sampgdk_param_get_cell(amx, 2, (void *)&objectid);
  sampgdk_param_get_cell(amx, 3, (void *)&response);
  sampgdk_param_get_float(amx, 4, (void *)&fX);
  sampgdk_param_get_float(amx, 5, (void *)&fY);
  sampgdk_param_get_float(amx, 6, (void *)&fZ);
  sampgdk_param_get_float(amx, 7, (void *)&fRotX);
  sampgdk_param_get_float(amx, 8, (void *)&fRotY);
  sampgdk_param_get_float(amx, 9, (void *)&fRotZ);
  sampgdk_log_debug("OnPlayerEditObject(%d, %d, %d, %d, %f, %f, %f, %f, %f, %f)", playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);
  retval_ = ((OnPlayerEditObject_callback)callback)(playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEditAttachedObject_callback)(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ);
static bool _OnPlayerEditAttachedObject(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int response;
  int index;
  int modelid;
  int boneid;
  float fOffsetX;
  float fOffsetY;
  float fOffsetZ;
  float fRotX;
  float fRotY;
  float fRotZ;
  float fScaleX;
  float fScaleY;
  float fScaleZ;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&response);
  sampgdk_param_get_cell(amx, 2, (void *)&index);
  sampgdk_param_get_cell(amx, 3, (void *)&modelid);
  sampgdk_param_get_cell(amx, 4, (void *)&boneid);
  sampgdk_param_get_float(amx, 5, (void *)&fOffsetX);
  sampgdk_param_get_float(amx, 6, (void *)&fOffsetY);
  sampgdk_param_get_float(amx, 7, (void *)&fOffsetZ);
  sampgdk_param_get_float(amx, 8, (void *)&fRotX);
  sampgdk_param_get_float(amx, 9, (void *)&fRotY);
  sampgdk_param_get_float(amx, 10, (void *)&fRotZ);
  sampgdk_param_get_float(amx, 11, (void *)&fScaleX);
  sampgdk_param_get_float(amx, 12, (void *)&fScaleY);
  sampgdk_param_get_float(amx, 13, (void *)&fScaleZ);
  sampgdk_log_debug("OnPlayerEditAttachedObject(%d, %d, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f)", playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
  retval_ = ((OnPlayerEditAttachedObject_callback)callback)(playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerSelectObject_callback)(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ);
static bool _OnPlayerSelectObject(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int type;
  int objectid;
  int modelid;
  float fX;
  float fY;
  float fZ;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&type);
  sampgdk_param_get_cell(amx, 2, (void *)&objectid);
  sampgdk_param_get_cell(amx, 3, (void *)&modelid);
  sampgdk_param_get_float(amx, 4, (void *)&fX);
  sampgdk_param_get_float(amx, 5, (void *)&fY);
  sampgdk_param_get_float(amx, 6, (void *)&fZ);
  sampgdk_log_debug("OnPlayerSelectObject(%d, %d, %d, %d, %f, %f, %f)", playerid, type, objectid, modelid, fX, fY, fZ);
  retval_ = ((OnPlayerSelectObject_callback)callback)(playerid, type, objectid, modelid, fX, fY, fZ);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerWeaponShot_callback)(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ);
static bool _OnPlayerWeaponShot(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int weaponid;
  int hittype;
  int hitid;
  float fX;
  float fY;
  float fZ;
  sampgdk_param_get_cell(amx, 0, (void *)&playerid);
  sampgdk_param_get_cell(amx, 1, (void *)&weaponid);
  sampgdk_param_get_cell(amx, 2, (void *)&hittype);
  sampgdk_param_get_cell(amx, 3, (void *)&hitid);
  sampgdk_param_get_float(amx, 4, (void *)&fX);
  sampgdk_param_get_float(amx, 5, (void *)&fY);
  sampgdk_param_get_float(amx, 6, (void *)&fZ);
  sampgdk_log_debug("OnPlayerWeaponShot(%d, %d, %d, %d, %f, %f, %f)", playerid, weaponid, hittype, hitid, fX, fY, fZ);
  retval_ = ((OnPlayerWeaponShot_callback)callback)(playerid, weaponid, hittype, hitid, fX, fY, fZ);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return !!retval_ != false;
}

SAMPGDK_MODULE_INIT(a_samp) {
  int error;
  if ((error = sampgdk_callback_register("OnVehicleStreamOut", _OnVehicleStreamOut)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnVehicleStreamIn", _OnVehicleStreamIn)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnVehicleSpawn", _OnVehicleSpawn)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnVehicleSirenStateChange", _OnVehicleSirenStateChange)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnVehicleRespray", _OnVehicleRespray)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnVehiclePaintjob", _OnVehiclePaintjob)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnVehicleMod", _OnVehicleMod)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnVehicleDeath", _OnVehicleDeath)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnVehicleDamageStatusUpdate", _OnVehicleDamageStatusUpdate)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnUnoccupiedVehicleUpdate", _OnUnoccupiedVehicleUpdate)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnTrailerUpdate", _OnTrailerUpdate)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnRconLoginAttempt", _OnRconLoginAttempt)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnRconCommand", _OnRconCommand)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerWeaponShot", _OnPlayerWeaponShot)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerUpdate", _OnPlayerUpdate)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerText", _OnPlayerText)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerTakeDamage", _OnPlayerTakeDamage)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerStreamOut", _OnPlayerStreamOut)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerStreamIn", _OnPlayerStreamIn)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerStateChange", _OnPlayerStateChange)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerSpawn", _OnPlayerSpawn)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerSelectedMenuRow", _OnPlayerSelectedMenuRow)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerSelectObject", _OnPlayerSelectObject)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerRequestSpawn", _OnPlayerRequestSpawn)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerRequestClass", _OnPlayerRequestClass)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerPickUpPickup", _OnPlayerPickUpPickup)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerObjectMoved", _OnPlayerObjectMoved)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerLeaveRaceCheckpoint", _OnPlayerLeaveRaceCheckpoint)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerLeaveCheckpoint", _OnPlayerLeaveCheckpoint)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerKeyStateChange", _OnPlayerKeyStateChange)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerInteriorChange", _OnPlayerInteriorChange)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerGiveDamageActor", _OnPlayerGiveDamageActor)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerGiveDamage", _OnPlayerGiveDamage)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerExitedMenu", _OnPlayerExitedMenu)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerExitVehicle", _OnPlayerExitVehicle)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerEnterVehicle", _OnPlayerEnterVehicle)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerEnterRaceCheckpoint", _OnPlayerEnterRaceCheckpoint)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerEnterCheckpoint", _OnPlayerEnterCheckpoint)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerEditObject", _OnPlayerEditObject)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerEditAttachedObject", _OnPlayerEditAttachedObject)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerDisconnect", _OnPlayerDisconnect)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerDeath", _OnPlayerDeath)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerConnect", _OnPlayerConnect)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerCommandText", _OnPlayerCommandText)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerClickTextDraw", _OnPlayerClickTextDraw)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerClickPlayerTextDraw", _OnPlayerClickPlayerTextDraw)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerClickPlayer", _OnPlayerClickPlayer)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnPlayerClickMap", _OnPlayerClickMap)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnObjectMoved", _OnObjectMoved)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnIncomingConnection", _OnIncomingConnection)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnGameModeInit", _OnGameModeInit)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnGameModeExit", _OnGameModeExit)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnEnterExitModShop", _OnEnterExitModShop)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnDialogResponse", _OnDialogResponse)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnActorStreamOut", _OnActorStreamOut)) < 0) {
    return error;
  }
  if ((error = sampgdk_callback_register("OnActorStreamIn", _OnActorStreamIn)) < 0) {
    return error;
  }
  return 0;
}

SAMPGDK_MODULE_CLEANUP(a_samp) {
  sampgdk_callback_unregister("OnVehicleStreamOut");
  sampgdk_callback_unregister("OnVehicleStreamIn");
  sampgdk_callback_unregister("OnVehicleSpawn");
  sampgdk_callback_unregister("OnVehicleSirenStateChange");
  sampgdk_callback_unregister("OnVehicleRespray");
  sampgdk_callback_unregister("OnVehiclePaintjob");
  sampgdk_callback_unregister("OnVehicleMod");
  sampgdk_callback_unregister("OnVehicleDeath");
  sampgdk_callback_unregister("OnVehicleDamageStatusUpdate");
  sampgdk_callback_unregister("OnUnoccupiedVehicleUpdate");
  sampgdk_callback_unregister("OnTrailerUpdate");
  sampgdk_callback_unregister("OnRconLoginAttempt");
  sampgdk_callback_unregister("OnRconCommand");
  sampgdk_callback_unregister("OnPlayerWeaponShot");
  sampgdk_callback_unregister("OnPlayerUpdate");
  sampgdk_callback_unregister("OnPlayerText");
  sampgdk_callback_unregister("OnPlayerTakeDamage");
  sampgdk_callback_unregister("OnPlayerStreamOut");
  sampgdk_callback_unregister("OnPlayerStreamIn");
  sampgdk_callback_unregister("OnPlayerStateChange");
  sampgdk_callback_unregister("OnPlayerSpawn");
  sampgdk_callback_unregister("OnPlayerSelectedMenuRow");
  sampgdk_callback_unregister("OnPlayerSelectObject");
  sampgdk_callback_unregister("OnPlayerRequestSpawn");
  sampgdk_callback_unregister("OnPlayerRequestClass");
  sampgdk_callback_unregister("OnPlayerPickUpPickup");
  sampgdk_callback_unregister("OnPlayerObjectMoved");
  sampgdk_callback_unregister("OnPlayerLeaveRaceCheckpoint");
  sampgdk_callback_unregister("OnPlayerLeaveCheckpoint");
  sampgdk_callback_unregister("OnPlayerKeyStateChange");
  sampgdk_callback_unregister("OnPlayerInteriorChange");
  sampgdk_callback_unregister("OnPlayerGiveDamageActor");
  sampgdk_callback_unregister("OnPlayerGiveDamage");
  sampgdk_callback_unregister("OnPlayerExitedMenu");
  sampgdk_callback_unregister("OnPlayerExitVehicle");
  sampgdk_callback_unregister("OnPlayerEnterVehicle");
  sampgdk_callback_unregister("OnPlayerEnterRaceCheckpoint");
  sampgdk_callback_unregister("OnPlayerEnterCheckpoint");
  sampgdk_callback_unregister("OnPlayerEditObject");
  sampgdk_callback_unregister("OnPlayerEditAttachedObject");
  sampgdk_callback_unregister("OnPlayerDisconnect");
  sampgdk_callback_unregister("OnPlayerDeath");
  sampgdk_callback_unregister("OnPlayerConnect");
  sampgdk_callback_unregister("OnPlayerCommandText");
  sampgdk_callback_unregister("OnPlayerClickTextDraw");
  sampgdk_callback_unregister("OnPlayerClickPlayerTextDraw");
  sampgdk_callback_unregister("OnPlayerClickPlayer");
  sampgdk_callback_unregister("OnPlayerClickMap");
  sampgdk_callback_unregister("OnObjectMoved");
  sampgdk_callback_unregister("OnIncomingConnection");
  sampgdk_callback_unregister("OnGameModeInit");
  sampgdk_callback_unregister("OnGameModeExit");
  sampgdk_callback_unregister("OnEnterExitModShop");
  sampgdk_callback_unregister("OnDialogResponse");
  sampgdk_callback_unregister("OnActorStreamOut");
  sampgdk_callback_unregister("OnActorStreamIn");
}


