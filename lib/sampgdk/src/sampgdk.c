#include <sampgdk/sampgdk.h>

#if SAMPGDK_WINDOWS
  #undef CreateMenu
  #undef DestroyMenu
  #undef GetTickCount
  #undef KillTimer
  #undef SelectObject
  #undef SetTimer
  #include <windows.h>
#endif

/* Copyright (C) 2012-2014 Zeex
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

sampgdk_hook_t sampgdk_hook_new();
void sampgdk_hook_free(sampgdk_hook_t hook);

void sampgdk_hook_set_src(sampgdk_hook_t hook, void *src);
void *sampgdk_hook_get_src(sampgdk_hook_t hook);

void sampgdk_hook_set_dst(sampgdk_hook_t hook, void *dst);
void *sampgdk_hook_get_dst(sampgdk_hook_t hook);

int sampgdk_hook_install(sampgdk_hook_t hook);
int sampgdk_hook_remove(sampgdk_hook_t hook);

#endif /* !SAMPGDK_INTERNAL_HOOK_H */

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

#ifndef SAMPGDK_INTERNAL_INIT_H
#define SAMPGDK_INTERNAL_INIT_H

#define SAMPGDK_MODULE_INIT(module) \
  int sampgdk_##module##_init(void)

#define SAMPGDK_MODULE_CLEANUP(module) \
  void sampgdk_##module##_cleanup(void)

int  sampgdk_module_init(void);
void sampgdk_module_cleanup(void);

#endif /* !SAMPGDK_INTERNAL_INIT_H */

/* Copyright (C) 2012-2014 Zeex
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
  #define likely(x)   __builtin_expect((x), 1)
  #define unlikely(x) __builtin_expect((x), 0)
#else
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif

#endif /* !SAMPGDK_INTERNAL_LIKELY_H */

/* Copyright (C) 2012-2014 Zeex
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

void sampgdk_log_message(const char *format, ...);
void sampgdk_log_trace(const char *format, ...);
void sampgdk_log_warn(const char *format, ...);
void sampgdk_log_error(const char *format, ...);
void sampgdk_log_error_code(int error);

#endif /* !SAMPGDK_INTERNAL_LOG_H */

/* Copyright (C) 2012-2014 Zeex
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

#ifndef SAMPGDK_INTERNAL_UTILS_H
#define SAMPGDK_INTERNAL_UTILS_H

#include <stddef.h>

void sampgdk_strcpy(char *dst, const char *src, size_t size);

#endif /* !SAMPGDK_INTERNAL_UTILS_H */

int sampgdk_amxhooks_init(void);
int sampgdk_callback_init(void);
int sampgdk_fakeamx_init(void);
int sampgdk_native_init(void);
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
  if ((error = sampgdk_native_init()) < 0) {
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
void sampgdk_native_cleanup(void);
void sampgdk_fakeamx_cleanup(void);
void sampgdk_callback_cleanup(void);
void sampgdk_amxhooks_cleanup(void);

void sampgdk_module_cleanup(void) {
  sampgdk_a_samp_cleanup();
  sampgdk_a_players_cleanup();
  sampgdk_a_objects_cleanup();
  sampgdk_a_http_cleanup();
  sampgdk_timer_cleanup();
  sampgdk_native_cleanup();
  sampgdk_fakeamx_cleanup();
  sampgdk_callback_cleanup();
  sampgdk_amxhooks_cleanup();
}


/* Copyright (C) 2012-2014 Zeex
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
#include <stdlib.h>
#include <string.h>

/* #include "logprintf.h" */

enum _sampgdk_log_level {
  _SAMPGDK_LOG_NORMAL,
  _SAMPGDK_LOG_TRACE,
  _SAMPGDK_LOG_WARNING,
  _SAMPGDK_LOG_ERROR
};

static void _sampgdk_do_log(int level, const char *format, va_list args) {
  const char *prefix;
  char *real_format;

  switch (level) {
    case _SAMPGDK_LOG_TRACE:
      prefix = "trace: ";
      break;
    case _SAMPGDK_LOG_WARNING:
      prefix = "warning: ";
      break;
    case _SAMPGDK_LOG_ERROR:
      prefix = "error: ";
      break;
    default:
      prefix = "";
  }

  real_format = malloc(
    sizeof("[sampgdk] ") - 1
    + strlen(prefix)
    + strlen(format)
    + 1
  );
  if (real_format == NULL) {
    return;
  }

  strcpy(real_format, "[sampgdk] ");
  strcat(real_format, prefix);
  strcat(real_format, format);

  sampgdk_do_vlogprintf(real_format, args);

  free(real_format);
}

void sampgdk_log_message(const char *format, ...) {
  va_list args;

  va_start(args, format);
  _sampgdk_do_log(_SAMPGDK_LOG_NORMAL, format, args);
  va_end(args);
}

void sampgdk_log_trace(const char *format, ...) {
  va_list args;

  va_start(args, format);
  _sampgdk_do_log(_SAMPGDK_LOG_TRACE, format, args);
  va_end(args);
}

void sampgdk_log_warn(const char *format, ...) {
  va_list args;

  va_start(args, format);
  _sampgdk_do_log(_SAMPGDK_LOG_WARNING, format, args);
  va_end(args);
}

void sampgdk_log_error(const char *format, ...) {
  va_list args;

  va_start(args, format);
  _sampgdk_do_log(_SAMPGDK_LOG_ERROR, format, args);
  va_end(args);
}

void sampgdk_log_error_code(int error) {
	_sampgdk_do_log(_SAMPGDK_LOG_ERROR, strerror(-error), NULL);
}

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

/* #include "utils.h" */

void sampgdk_strcpy(char *dst, const char *src, size_t size) {
  if (size > 0) {
    size_t i;
    for (i = 0; i < size - 1 && src[i] != '\0'; i++) {
      dst[i] = src[i];
    }
    dst[i] = '\0';
  }
}

/* Copyright (C) 2012-2014 Zeex
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

#include <stddef.h>

#include <sampgdk/sampgdk.h>

struct sampgdk_plugin_list {
  void                       *plugin;
  struct sampgdk_plugin_list *next;
};

int sampgdk_plugin_register(void *plugin);
int sampgdk_plugin_unregister(void *plugin);
bool sampgdk_plugin_is_registered(void *plugin);
void *sampgdk_plugin_get_symbol(void *plugin, const char *name);
void *sampgdk_plugin_get_handle(void *address);
void sampgdk_plugin_get_filename(void *address, char *filename, size_t size);
struct sampgdk_plugin_list *sampgdk_plugin_get_list(void);

#endif /* !SAMPGDK_INTERNAL_PLUGIN_H */

/* Copyright (C) 2012-2014 Zeex
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

#include <sampgdk/sampgdk.h>

struct sampgdk_array {
  void *data;      /* pointer to array contents */
  int   count;     /* number of elements in array */
  int   size;      /* maximum number of elements */
  int   elem_size; /* size of an element in bytes */
};

int sampgdk_array_new(struct sampgdk_array *a, int size, int elem_size);
void sampgdk_array_free(struct sampgdk_array *a);
bool sampgdk_array_ok(struct sampgdk_array *a);
int sampgdk_array_zero(struct sampgdk_array *a);
int sampgdk_array_resize(struct sampgdk_array *a, int new_size);
int sampgdk_array_grow(struct sampgdk_array *a);
int sampgdk_array_shrink(struct sampgdk_array *a);
int sampgdk_array_pad(struct sampgdk_array *a);
void *sampgdk_array_get(struct sampgdk_array *a, int index);
void sampgdk_array_set(struct sampgdk_array *a,int index, void *elem);
int sampgdk_array_insert(struct sampgdk_array *a, int index, int count, void *elems);
int sampgdk_array_insert_single(struct sampgdk_array *a, int index, void *elem);
int sampgdk_array_insert_ordered(struct sampgdk_array *a, void *elem,
                                 int (*comp)(const void *x, const void *y));
int sampgdk_array_remove(struct sampgdk_array *a, int index, int count);
int sampgdk_array_remove_single(struct sampgdk_array *a, int index);
int sampgdk_array_append(struct sampgdk_array *a, void *elem);

#endif /* !SAMPGDK_INTERNAL_ARRAY_H */

/* Copyright (C) 2012-2014 Zeex
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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <sampgdk/sampgdk.h>

/* #include "logprintf.h" */

#define _SAMPGDK_LOGPRINTF_BUF_SIZE 1024

#ifdef _MSC_VER
  #define vsnprintf vsprintf_s
#endif

typedef void (SAMPGDK_CDECL *logprintf_t)(const char *format, ...);

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

/* Copyright (C) 2012-2014 Zeex
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

#include <sampgdk/sampgdk.h>

#if SAMPGDK_WINDOWS
  #include <windows.h>
#else
  #include <stdint.h>
  #include <unistd.h>
  #include <sys/mman.h>
#endif

/* #include "hook.h" */

#if defined _MSC_VER
  typedef __int32 int32_t;
  typedef __int32 intptr_t;
#else
  #include <stdint.h>
#endif

#define _SAMPGDK_JMP_OPCODE 0xE9

static const unsigned char jmp_opcode = _SAMPGDK_JMP_OPCODE;
static const unsigned char jmp_instr[] =
  { _SAMPGDK_JMP_OPCODE, 0x0, 0x0, 0x0, 0x0 };

struct _sampgdk_hook {
  bool installed;
  void *src;
  void *dst;
  unsigned char code[sizeof(jmp_instr)];
};

#if SAMPGDK_WINDOWS

static void *_sampgdk_hook_unprotect(void *address, size_t size) {
  DWORD old;

  if (VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &old) == 0)
    return NULL;

  return address;
}

#else /* SAMPGDK_WINDOWS */

static void *_sampgdk_hook_unprotect(void *address, size_t size) {
  intptr_t pagesize;

  pagesize = sysconf(_SC_PAGESIZE);
  address = (void *)((intptr_t)address & ~(pagesize - 1));

  if (mprotect(address, size, PROT_READ | PROT_WRITE | PROT_EXEC) != 0)
    return NULL;

  return address;
}

#endif /* !SAMPGDK_WINDOWS */

sampgdk_hook_t sampgdk_hook_new() {
  struct _sampgdk_hook *hook;

  if ((hook = calloc(1, sizeof(*hook))) == NULL)
    return NULL;

  return (sampgdk_hook_t)hook;
}

void sampgdk_hook_free(sampgdk_hook_t hook) {
  free(hook);
}

void *sampgdk_hook_get_src(sampgdk_hook_t hook) {
  return hook->src;
}

void *sampgdk_hook_get_dst(sampgdk_hook_t hook) {
  return hook->dst;
}

void sampgdk_hook_set_src(sampgdk_hook_t hook, void *src) {
  hook->src = src;
}

void sampgdk_hook_set_dst(sampgdk_hook_t hook, void *dst) {
  hook->dst = dst;
}

int sampgdk_hook_install(sampgdk_hook_t hook) {
  void *src;
  void *dst;
  intptr_t offset;

  if (hook->installed)
    return -EINVAL;

  src = hook->src;
  dst = hook->dst;

  _sampgdk_hook_unprotect(src, sizeof(jmp_instr));
  memcpy(hook->code, src, sizeof(jmp_instr));
  memcpy(src, &jmp_instr, sizeof(jmp_instr));

  offset = (intptr_t)dst - ((intptr_t)src + sizeof(jmp_instr));
  memcpy((void *)((intptr_t)src + sizeof(jmp_opcode)), &offset,
        sizeof(jmp_instr) - sizeof(jmp_opcode));

  hook->installed = 1;
  return 0;
}

int sampgdk_hook_remove(sampgdk_hook_t hook) {
  if (!hook->installed)
    return -EINVAL;

  memcpy(hook->src, hook->code, sizeof(jmp_instr));
  hook->installed = 0;
  return 0;
}

/* Copyright (C) 2012-2014 Zeex
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

#include <sampgdk/sampgdk.h>

#if SAMPGDK_WINDOWS
  #include <windows.h>
#else
  #include <dlfcn.h>
  #include <string.h>
#endif

/* #include "plugin.h" */

static struct sampgdk_plugin_list *_sampgdk_plugins;

int sampgdk_plugin_register(void *plugin) {
  struct sampgdk_plugin_list *ptr;

  assert(plugin != NULL);

  if (sampgdk_plugin_is_registered(plugin)) {
    return -EINVAL;
  }

  ptr = malloc(sizeof(*ptr));
  if (ptr == NULL) {
    return -ENOMEM;
  }

  ptr->plugin = plugin;
  ptr->next = _sampgdk_plugins;
  _sampgdk_plugins = ptr;

  return 0;
}

int sampgdk_plugin_unregister(void *plugin) {
  struct sampgdk_plugin_list *prev;
  struct sampgdk_plugin_list *cur;

  assert(plugin != NULL);

  cur = _sampgdk_plugins;
  prev = NULL;

  while (cur != NULL) {
    if (cur->plugin != plugin) {
      continue;
    }

    if (prev != NULL) {
      prev->next = cur->next;
    } else {
      assert(_sampgdk_plugins == cur);
      _sampgdk_plugins = cur->next;
    }

    free(cur);
    return 0;
  }

  return -EINVAL;
}

bool sampgdk_plugin_is_registered(void *plugin) {
  struct sampgdk_plugin_list *cur;

  assert(plugin != NULL);

  cur = _sampgdk_plugins;

  while (cur != NULL) {
    if (cur->plugin == plugin) {
      return true;
    }
    cur = cur->next;
  }

  return false;
}

struct sampgdk_plugin_list *sampgdk_plugin_get_list(void) {
  return _sampgdk_plugins;
}

#if SAMPGDK_WINDOWS

void *sampgdk_plugin_get_symbol(void *plugin, const char *name)  {
  assert(plugin != NULL);
  assert(name != NULL);
  return (void*)GetProcAddress((HMODULE)plugin, name);
}

void *sampgdk_plugin_get_handle(void *address) {
  HMODULE module;
  if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT |
                        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                        address, &module) != 0) {
    return module;
  }
  return NULL;
}

void sampgdk_plugin_get_filename(void *address, char *filename, size_t size) {
  HMODULE module = (HMODULE)sampgdk_plugin_get_handle(address);
  assert(address != NULL);
  assert(filename != NULL);
  GetModuleFileName(module, filename, size);
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

void sampgdk_plugin_get_filename(void *address, char *filename, size_t size) {
  Dl_info info;
  assert(address != NULL);
  assert(filename != NULL);
  if (dladdr(address, &info) != 0) {
    strncpy(filename, info.dli_fname, size);
  }
}

#endif /* !SAMPGDK_WINDOWS */

/* Copyright (C) 2012-2014 Zeex
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
  return (unsigned char*)a->data + (index * a->elem_size);
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

bool sampgdk_array_ok(struct sampgdk_array *a) {
  return a->data != NULL && a->elem_size > 0;
}

int sampgdk_array_zero(struct sampgdk_array *a) {
  assert(a != NULL);
  assert(a->data != NULL);

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
  assert(index >= 0);
  assert(index < a->count);
  return _sampgdk_array_get_elem_ptr(a, index);
}

void sampgdk_array_set(struct sampgdk_array *a, int index, void *elem) {
  assert(a != NULL);
  assert(elem != NULL);
  assert(index >= 0);
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
  assert(index >= 0);
  assert(index < a->count);

  if (count <= 0) {
    return -EINVAL;
  }

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

  return 0;
}

int sampgdk_array_insert_single(struct sampgdk_array *a,
                                int index,
                                void *elem) {
  assert(a != NULL);
  assert(elem != NULL);
  return sampgdk_array_insert(a, index, 1, elem);
}

int sampgdk_array_insert_ordered(struct sampgdk_array *a,
                                 void *elem,
                                 int (*comp)(const void *x, const void *y))
{
  int index;

  for (index = 0; index < a->count; index++) {
    if (comp(sampgdk_array_get(a, index), elem) >= 0) {
      return sampgdk_array_insert_single(a, index, elem);
    }
  }

  return sampgdk_array_append(a, elem);
}

int sampgdk_array_remove(struct sampgdk_array *a, int index, int count) {
  int move_count;

  assert(a != NULL);
  assert(index >= 0);
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

  return 0;
}

int sampgdk_array_remove_single(struct sampgdk_array *a, int index) {
  assert(a != NULL);
  assert(index >= 0);
  assert(index < a->count);
  return sampgdk_array_remove(a, index, 1);
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

  return 0;
}

/* Copyright (C) 2012-2014 Zeex
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

#include <sampgdk/sampgdk.h>

int sampgdk_native_register(const char *name, AMX_NATIVE func);
AMX_NATIVE sampgdk_native_find(const char *name);
AMX_NATIVE sampgdk_native_find_warn(const char *name);
AMX_NATIVE sampgdk_native_find_stub(const char *name);
AMX_NATIVE sampgdk_native_find_warn_stub(const char *name);
const AMX_NATIVE_INFO *sampgdk_native_get_table(int *number);
cell sampgdk_native_call(AMX_NATIVE native, cell *params);
cell sampgdk_native_invoke(AMX_NATIVE native, const char *format, va_list args);
cell sampgdk_native_invoke_array(AMX_NATIVE native, const char *format, void **args);

#endif /* !SAMPGDK_NATIVE_H_ */

/* Copyright (C) 2012-2014 Zeex
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

#include <sampgdk/sampgdk.h>

void sampgdk_param_get_all(AMX *amx, bool exec, cell **params);
void sampgdk_param_get_cell(AMX *amx, int index, cell *param);
void sampgdk_param_get_bool(AMX *amx, int index, bool *param);
void sampgdk_param_get_float(AMX *amx, int index, float *param);
void sampgdk_param_get_string(AMX *amx, int index, char **param);

#endif /* !SAMPGDK_INTERNAL_PARAM_H */

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

#ifndef SAMPGDK_INTERNAL_AMX_H
#define SAMPGDK_INTERNAL_AMX_H

#include <sampgdk/sampgdk.h>

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

/* Copyright (C) 2012-2014 Zeex
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

#include <sampgdk/sampgdk.h>

typedef bool (*sampgdk_callback_handler)(AMX *amx, void *func, cell *retval);

struct sampgdk_callback {
  char                     *name;
  sampgdk_callback_handler  handler;
};

struct sampgdk_callback *sampgdk_callback_find(const char *name);
int sampgdk_callback_register(const char *name, sampgdk_callback_handler handler);
int sampgdk_callback_register_table(const struct sampgdk_callback *table);
void sampgdk_callback_unregister(const char *name);
void sampgdk_callback_unregister_table(const struct sampgdk_callback *table);
bool sampgdk_callback_invoke(AMX *amx, const char *name, cell *retval);

#endif /* !SAMPGDK_INTERNAL_CALLBACK_H */

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

#ifndef SAMPGDK_INTERNAL_FAKEAMX_H
#define SAMPGDK_INTERNAL_FAKEAMX_H

#include <sampgdk/sampgdk.h>

AMX *sampgdk_fakeamx_amx(void);
int sampgdk_fakeamx_resize_heap(int cells);
int sampgdk_fakeamx_push(int cells, cell *address);
int sampgdk_fakeamx_push_cell(cell value, cell *address);
int sampgdk_fakeamx_push_float(float value, cell *address);
int sampgdk_fakeamx_push_array(const cell *src, int size, cell *address);
int sampgdk_fakeamx_push_string(const char *src, int *size, cell *address);
void sampgdk_fakeamx_get_cell(cell address, cell *value);
void sampgdk_fakeamx_get_bool(cell address, bool *value);
void sampgdk_fakeamx_get_float(cell address, float *value);
void sampgdk_fakeamx_get_array(cell address, cell *dest, int size);
void sampgdk_fakeamx_get_string(cell address, char *dest, int size);
void sampgdk_fakeamx_pop(cell address);

#endif /* !SAMPGDK_INTERNAL_FAKEAMX_H */

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

/* #include "amx.h" */

struct sampgdk_amx_api *sampgdk_amx_api_ptr;

/* Copyright (C) 2012-2014 Zeex
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

static unsigned char *_sampgdk_param_get_data(AMX *amx) {
  if (amx->data != 0) {
    return amx->data;
  } else {
    return amx->base + ((AMX_HEADER*)amx->base)->dat;
  }
}

static cell *_sampgdk_param_get_stack(AMX *amx) {
  return (cell*)(_sampgdk_param_get_data(amx) + amx->stk);
}

static cell _sampgdk_param_get_by_index(AMX *amx, int index) {
  return _sampgdk_param_get_stack(amx)[index];
}

void sampgdk_param_get_all(AMX *amx, bool exec, cell **params) {
  assert(params != NULL);
  if (exec) {
    *params = _sampgdk_param_get_stack(amx) - 1;
    *params[0] = amx->paramcount * sizeof(cell);
  } else {
    *params = _sampgdk_param_get_stack(amx);
  }
}

void sampgdk_param_get_cell(AMX *amx, int index, cell *param) {
  assert(param != NULL);
  *param = _sampgdk_param_get_by_index(amx, index);
}

void sampgdk_param_get_bool(AMX *amx, int index, bool *param) {
  assert(param != NULL);
  *param = !!_sampgdk_param_get_by_index(amx, index);
}

void sampgdk_param_get_float(AMX *amx, int index, float *param) {
  cell p = _sampgdk_param_get_by_index(amx, index);
  assert(param != NULL);
  *param = amx_ctof(p);
}

void sampgdk_param_get_string(AMX *amx, int index, char **param) {
  cell amx_addr;
  cell *phys_addr;
  int length;
  char *string;
 
  amx_addr = _sampgdk_param_get_by_index(amx, index);
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

#include <sampgdk/sampgdk.h>

/* #include "internal/native.h" */

SAMPGDK_API(const AMX_NATIVE_INFO *, sampgdk_GetNatives(int *number)) {
  return sampgdk_native_get_table(number);
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

/* Copyright (C) 2012-2014 Zeex
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

#include <sampgdk/sampgdk.h>

typedef void (SAMPGDK_CALL *sampgdk_timer_callback)(int id, void *param);

int sampgdk_timer_set(long interval, bool repeat,
                      sampgdk_timer_callback calback, void *param);
int sampgdk_timer_kill(int timerid);
void sampgdk_timer_process_timers(void *plugin);
long sampgdk_timer_now(void);

#endif /* !SAMPGDK_INTERNAL_TIMER_H */

/* Copyright (C) 2012-2014 Zeex
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
/* #include "param.h" */
/* #include "plugin.h" */

static struct sampgdk_array _sampgdk_callbacks;

SAMPGDK_MODULE_INIT(callback) {
  int error;

  if (_sampgdk_callbacks.data != NULL) {
    return 0; /* already initialized */
  }

  error = sampgdk_array_new(&_sampgdk_callbacks,
                            1,
                            sizeof(struct sampgdk_callback));
  if (error < 0) {
    return error;
  }

  return 0;
}

SAMPGDK_MODULE_CLEANUP(callback) {
  int index;

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    struct sampgdk_callback *info =
      (struct sampgdk_callback *)sampgdk_array_get(&_sampgdk_callbacks,
                                                   index);
    free(info->name);
  }

  sampgdk_array_free(&_sampgdk_callbacks);
}

static int _sampgdk_callback_compare(const void *c1, const void *c2) {
  return strcmp(((const struct sampgdk_callback*)c1)->name,
                ((const struct sampgdk_callback*)c2)->name);
}

static int _sampgdk_callback_compare_bsearch(const void *key,
                                             const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key,
                ((const struct sampgdk_callback *)elem)->name);
}

struct sampgdk_callback *sampgdk_callback_find(const char *name) {
  assert(name != NULL);
  return bsearch(name, _sampgdk_callbacks.data,
                       _sampgdk_callbacks.count,
                       _sampgdk_callbacks.elem_size,
                       _sampgdk_callback_compare_bsearch);
}

int sampgdk_callback_register(const char *name,
                              sampgdk_callback_handler handler) {
  int error;
  struct sampgdk_callback info;
  struct sampgdk_callback *ptr;
 
  assert(name != NULL);
  assert(handler != NULL);

  ptr = sampgdk_callback_find(name);
  if (ptr != NULL) {
    ptr->handler = handler;
    return 0;
  }

  info.name = malloc(strlen(name) + 1);
  if (info.name == NULL) {
    return -ENOMEM;
  }

  info.handler = handler;
  strcpy(info.name, name);

  error = sampgdk_array_insert_ordered(&_sampgdk_callbacks,
                                       &info,
                                       _sampgdk_callback_compare);

  if (error < 0) {
    free(info.name);
    return error;
  }

  return 0;
}

int sampgdk_callback_register_table(const struct sampgdk_callback *table) {
  const struct sampgdk_callback *ptr;
  int error;

  for (ptr = table; ptr->name != NULL; ptr++) {
    error = sampgdk_callback_register(ptr->name, ptr->handler);
    if (error < 0) {
      return error;
    }
  }

  return 0;
}

void sampgdk_callback_unregister(const char *name) {
  const struct sampgdk_callback *ptr;
  int index;

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    ptr = (const struct sampgdk_callback *)
      sampgdk_array_get(&_sampgdk_callbacks, index);
    if (strcmp(ptr->name, name) == 0) {
      sampgdk_array_remove_single(&_sampgdk_callbacks, index);
      break;
    }
  }
}

void sampgdk_callback_unregister_table(const struct sampgdk_callback *table) {
  const struct sampgdk_callback *ptr;

  for (ptr = table; ptr->name != NULL; ptr++) {
    sampgdk_callback_unregister(ptr->name);
  }
}

static bool call_public_filter(void *plugin, AMX *amx, const char *name,
                               cell *retval) {
  void *func;
  cell *params;

  func = sampgdk_plugin_get_symbol(plugin, "OnPublicCall");
  if (func != NULL) {
    typedef bool (PLUGIN_CALL *public_filter)(AMX *amx, const char *name,
                                              cell *params, cell *retval);
    sampgdk_param_get_all(amx, true, &params);
    return ((public_filter)func)(amx, name, params, retval);
  }

  return true;
}

static bool call_public_handler(void *plugin, AMX *amx, const char *name,
                                cell *retval) {
  void *func;
  struct sampgdk_callback *callback;

  func = sampgdk_plugin_get_symbol(plugin, name);
  if (func != NULL) {
    callback = sampgdk_callback_find(name);
    if (callback != NULL) {
      return callback->handler(amx, func, retval);
    }
  }

  return true;
}

bool sampgdk_callback_invoke(AMX *amx, const char *name, cell *retval) {
  struct sampgdk_plugin_list *plugin_list;
  
  assert(amx != NULL);
  assert(name != NULL);

  plugin_list = sampgdk_plugin_get_list();
  while (plugin_list != NULL) {
    if (call_public_filter(plugin_list->plugin, amx, name, retval) &&
        !call_public_handler(plugin_list->plugin, amx, name, retval)) {
      return false;
    }
    plugin_list = plugin_list->next;
  }

  return true;
}

/* Copyright (C) 2012-2014 Zeex
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
/* #include "native.h" */
/* #include "log.h" */

#define _SAMPGDK_MAX_NATIVE_ARGS     32
#define _SAMPGDK_MAX_NATIVE_ARG_SIZE 8  /* in bytes */

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
  int index;

  info.name = name;
  info.func = func;

  assert(name != 0);

  /* Always keep _sampgdk_natives ordered by name.
   * This allows us to use binary search in sampgdk_native_find().
   */
  for (index = 0; index < _sampgdk_natives.count - 1; index++) {
    ptr = (AMX_NATIVE_INFO *)sampgdk_array_get(&_sampgdk_natives, index);
    if (strcmp(name, ptr->name) <= 0) {
      break;
    }
  }

  return sampgdk_array_insert_single(&_sampgdk_natives, index, &info);
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
    sampgdk_log_warn("Native function not found: %s", name);
  }

  return func;
}

static cell AMX_NATIVE_CALL native_stub(AMX *amx, cell *params) {
  sampgdk_log_warn("Native stub");
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

const AMX_NATIVE_INFO *sampgdk_native_get_table(int *number) {
  if (number != NULL) {
    *number = _sampgdk_natives.count - 1;
  }
  return (const AMX_NATIVE_INFO*)_sampgdk_natives.data;
}

cell sampgdk_native_call(AMX_NATIVE native, cell *params) {
  AMX *amx = sampgdk_fakeamx_amx();
  return native(amx, params);
}

cell sampgdk_native_invoke(AMX_NATIVE native,
                           const char *format,
                           va_list args) {
  cell i = 0;
  const char *format_ptr = format;
  unsigned char args_copy[_SAMPGDK_MAX_NATIVE_ARGS *
                          _SAMPGDK_MAX_NATIVE_ARG_SIZE];
  unsigned char *args_ptr = args_copy;
  void *args_array[_SAMPGDK_MAX_NATIVE_ARGS];

  while (*format_ptr != '\0' && i < _SAMPGDK_MAX_NATIVE_ARGS) {
    switch (*format_ptr) {
      case 'i': /* integer */
      case 'd': /* integer */
        *(int *)args_ptr = va_arg(args, int);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_MAX_NATIVE_ARG_SIZE;
        break;
      case 'b': /* boolean */
        *(bool *)args_ptr = !!va_arg(args, int);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_MAX_NATIVE_ARG_SIZE;
        break;
      case 'f': /* floating-point */
        *(float *)args_ptr = (float)va_arg(args, double);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_MAX_NATIVE_ARG_SIZE;
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
  char *format_ptr = (char *)format; /* cast away const for strtol() */
  cell i = 0;
  cell params[_SAMPGDK_MAX_NATIVE_ARGS + 1];
  cell size[_SAMPGDK_MAX_NATIVE_ARGS] = {0};
  char type[_SAMPGDK_MAX_NATIVE_ARGS];
  int needs_size = -1;
  enum {
    ST_READ_SPEC,
    ST_NEED_SIZE,
    ST_READING_SIZE,
    ST_READING_SIZE_ARG,
    ST_READ_SIZE
  } state = ST_READ_SPEC;
  cell retval;

  while (*format_ptr != '\0' && i < _SAMPGDK_MAX_NATIVE_ARGS) {
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
            sampgdk_log_warn("Unrecognized type specifier '%c'", *format_ptr);
        }
        type[i++] = *format_ptr++;
        break;
      case ST_NEED_SIZE:
        if (*format_ptr == '[') {
          state = ST_READING_SIZE;
        } else {
          sampgdk_log_warn("Bad format string: expected '[' but got '%c'",
                           *format_ptr);
        }
        format_ptr++;
        break;
      case ST_READING_SIZE:
        if (*format_ptr == '*') {
          format_ptr++;
          state = ST_READING_SIZE_ARG;
        } else {
          size[needs_size] = (int)strtol(format_ptr, &format_ptr, 10);
          state = ST_READ_SIZE;
        }
        break;
      case ST_READING_SIZE_ARG: {
        int index = (int)strtol(format_ptr, &format_ptr, 10);
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
                sampgdk_log_warn("Invalid buffer size");
              }
              break;
          }
          needs_size = -1;
          state = ST_READ_SPEC;
        } else {
          sampgdk_log_warn("Bad format string (expected ']' but got '%c')",
                           *format_ptr);
        }
        format_ptr++;
        break;
      }
    }
  }

  if (*format_ptr != '\0') {
    sampgdk_log_warn("Too many native arguments (at most %d allowed)",
                     _SAMPGDK_MAX_NATIVE_ARGS);
  }

  params[0] = i * sizeof(cell);
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

static bool is_cell_aligned(cell address) {
  return address % sizeof(cell) == 0;
}

void sampgdk_fakeamx_get_cell(cell address, cell *value) {
  assert(is_cell_aligned(address));
  assert(value != NULL);

  *value = *(cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap,
                                      address / sizeof(cell));
}

void sampgdk_fakeamx_get_bool(cell address, bool *value) {
  cell tmp;

  assert(is_cell_aligned(address));
  assert(value != NULL);

  sampgdk_fakeamx_get_cell(address, &tmp);
  *value = (bool)tmp;
}

void sampgdk_fakeamx_get_float(cell address, float *value) {
  cell tmp;

  assert(is_cell_aligned(address));
  assert(value != NULL);

  sampgdk_fakeamx_get_cell(address, &tmp);
  *value = amx_ctof(tmp);
}

void sampgdk_fakeamx_get_array(cell address, cell *dest, int size) {
  cell *src;

  assert(is_cell_aligned(address));
  assert(dest != NULL);
  assert(size > 0);

  src = sampgdk_array_get(&_sampgdk_fakeamx.heap, address / sizeof(cell));
  memcpy(dest, src, size * sizeof(cell));
}

void sampgdk_fakeamx_get_string(cell address, char *dest, int size) {
  assert(is_cell_aligned(address));
  assert(dest != NULL);

  amx_GetString(dest, (cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap,
                                                address / sizeof(cell)),
                                                0, size);
}

void sampgdk_fakeamx_pop(cell address) {
  assert(is_cell_aligned(address));

  if (_sampgdk_fakeamx.amx.hea > address) {
    _sampgdk_fakeamx.amx.hea = address;
  }
}

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

#include <sampgdk/sampgdk.h>

SAMPGDK_API(int, sampgdk_GetVersion(void)) {
  return SAMPGDK_VERSION_ID;
}

SAMPGDK_API(const char *, sampgdk_GetVersionString(void)) {
  return SAMPGDK_VERSION_STRING;
}

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

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <sampgdk/sampgdk.h>

/* #include "amx.h" */
/* #include "callback.h" */
/* #include "fakeamx.h" */
/* #include "init.h" */
/* #include "log.h" */
/* #include "native.h" */
/* #include "param.h" */
/* #include "hook.h" */
/* #include "utils.h" */

#define _SAMPGDK_AMXHOOKS_MAX_PUBLIC_NAME 32

static AMX *_sampgdk_amxhooks_main_amx;
static char _sampgdk_amxhooks_public_name[_SAMPGDK_AMXHOOKS_MAX_PUBLIC_NAME];

#define _SAMPGDK_AMXHOOKS_LIST(C) \
  C(Register) \
  C(FindPublic) \
  C(Exec) \
  C(Callback) \
  C(Allot)

#define _SAMPGDK_AMXHOOKS_LIST_2(C) \
  C(Register) \
  C(FindPublic) \
  C(Exec) \
  C(Allot)

#define _SAMPGDK_AMXHOOKS_DEFINE_HOOK(name) \
  static sampgdk_hook_t _sampgdk_amxhooks_##name##_hook;
_SAMPGDK_AMXHOOKS_LIST(_SAMPGDK_AMXHOOKS_DEFINE_HOOK)
#undef _SAMPGDK_AMXHOOKS_DEFINE_HOOK

/* The "funcidx" native uses amx_FindPublic() to get public function index
 * but our FindPublic always succeeds regardless of public existence, so
 * here's a fixed version.
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
  if (error != AMX_ERR_NONE || (error == AMX_ERR_NONE &&
      index == AMX_EXEC_GDK)) {
    return -1;
  }

  return index;
}

static void _sampgdk_amxhooks_hook_native(AMX *amx,
                                          const char *name,
                                          AMX_NATIVE address) {
  int index;
  AMX_HEADER *hdr = (AMX_HEADER *)amx->base;
  AMX_FUNCSTUBNT *natives = (AMX_FUNCSTUBNT *)(amx->base + hdr->natives);

  if (amx_FindNative(amx, name, &index) == AMX_ERR_NONE) {
    natives[index].address = (ucell)address;
  }
}

static int AMXAPI _sampgdk_amxhooks_Register(AMX *amx,
                                             const AMX_NATIVE_INFO *nativelist,
                                             int number) {
  int i;
  int error;

  sampgdk_hook_remove(_sampgdk_amxhooks_Register_hook);

  _sampgdk_amxhooks_hook_native(amx, "funcidx", _sampgdk_amxhooks_funcidx);

  for (i = 0; nativelist[i].name != 0 && (i < number || number == -1); i++) {
    sampgdk_native_register(nativelist[i].name, nativelist[i].func);
  }

  error = amx_Register(amx, nativelist, number);
  sampgdk_hook_install(_sampgdk_amxhooks_Register_hook);

  return error;
}

/* The SA-MP server always makes a call to amx_FindPublic() before executing
 * a callback and depending the return value it may or may not run amx_Exec().
 *
 * In order to have amx_Exec() called for *all* publics i.e. regardless of
 * whether they actually exist in the gamemode, we can simply always return
 * success.
 *
 * Now you might be thinking "OK, that sounds like it should work", but there
 * is one fundamental flaw in this "algorithm": if the caller didn't bother
 * to initialize the retval variable prior to the call to amx_Exec(), which
 * makes perfect sense, it will end up with random garbage and you might get
 * unexpected results.
 */
static int AMXAPI _sampgdk_amxhooks_FindPublic(AMX *amx,
                                               const char *name,
                                               int *index) {
  bool proceed;
  int error;

  sampgdk_hook_remove(_sampgdk_amxhooks_FindPublic_hook);

  /* We are interested in calling publics against two AMX instances:
   * - the main AMX (the gamemode)
   * - the fake AMX (this is needed for HTTP() to work)
   */
  proceed = (amx == _sampgdk_amxhooks_main_amx ||
             amx == sampgdk_fakeamx_amx());
  error = amx_FindPublic(amx, name, index);

  if (proceed) {
    sampgdk_strcpy(_sampgdk_amxhooks_public_name,
                   name,
                   sizeof(_sampgdk_amxhooks_public_name));
    if (error != AMX_ERR_NONE) {
      error = AMX_ERR_NONE;
      *index = AMX_EXEC_GDK;
    }
  }

  sampgdk_hook_install(_sampgdk_amxhooks_FindPublic_hook);

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Exec(AMX *amx, cell *retval, int index) {
  bool proceed = true;
  int error = AMX_ERR_NONE;

  /* Since filterscripts don't use main() we can assume that the AMX
   * that executes main() is indeed the main AMX i.e. the gamemode.
   */
  if (index == AMX_EXEC_MAIN) {
    /* This extra check is needed in order to stop OnGameModeInit()
     * from being called twice in a row after a gmx.
     */
    if (_sampgdk_amxhooks_main_amx != amx && amx != NULL) {
      sampgdk_callback_invoke(amx, "OnGameModeInit", retval);
      _sampgdk_amxhooks_main_amx = amx;
    }
  } else {
    if (index != AMX_EXEC_CONT && _sampgdk_amxhooks_public_name != NULL
        && (amx == _sampgdk_amxhooks_main_amx || amx == sampgdk_fakeamx_amx())) {
      proceed = sampgdk_callback_invoke(amx,
                                        _sampgdk_amxhooks_public_name,
                                        retval);
    }
  }

  sampgdk_hook_remove(_sampgdk_amxhooks_Exec_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Callback_hook);

  if (proceed && index != AMX_EXEC_GDK) {
    error = amx_Exec(amx, retval, index);
  } else {
    amx->stk += amx->paramcount * sizeof(cell);
  }

  amx->paramcount = 0;

  sampgdk_hook_remove(_sampgdk_amxhooks_Callback_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Exec_hook);

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Callback(AMX *amx,
                                             cell index,
                                             cell *result,
                                             cell *params) {
  int error;

  sampgdk_hook_remove(_sampgdk_amxhooks_Callback_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Exec_hook);

  /* Prevent the default AMX callback from replacing SYSREQ.C instructions
   * with SYSREQ.D.
   */
  amx->sysreq_d = 0;

  error = amx_Callback(amx, index, result, params);

  sampgdk_hook_remove(_sampgdk_amxhooks_Exec_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Callback_hook);

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Allot(AMX *amx,
                                          int cells,
                                          cell *amx_addr,
                                          cell **phys_addr) {
  int error;

  sampgdk_hook_remove(_sampgdk_amxhooks_Allot_hook);

  /* There is a bug in amx_Allot() where it returns success even though
   * there's no enough space on the heap:
   *
   * if (amx->stk - amx->hea - cells*sizeof(cell) < STKMARGIN)
   *   return AMX_ERR_MEMORY;
   *
   * The expression on the left is always positive because of the conversion
   * to size_t, which is unsigned.
   */
  #define STKMARGIN (cell)(16 * sizeof(cell))
  if ((size_t)amx->stk < (size_t)(amx->hea + cells*sizeof(cell) + STKMARGIN)) {
    error =  AMX_ERR_MEMORY;
  } else {
    error = amx_Allot(amx, cells, amx_addr, phys_addr);
  }

  /* If called against the fake AMX and failed to allocate the requested
   * amount of space, grow the heap and try again.
   */
  if (error == AMX_ERR_MEMORY && amx == sampgdk_fakeamx_amx()) {
    cell new_size = ((amx->hea + STKMARGIN) / sizeof(cell)) + cells + 2;
    if (sampgdk_fakeamx_resize_heap(new_size) >= 0) {
      error = amx_Allot(amx, cells, amx_addr, phys_addr);
    }
  }

  sampgdk_hook_install(_sampgdk_amxhooks_Allot_hook);

  return error;
}

static int _sampgdk_amxhooks_create(void) {
#define _SAMPGDK_AMXHOOKS_CREATE_HOOK(name) \
    if ((_sampgdk_amxhooks_##name##_hook = sampgdk_hook_new()) == NULL) \
      goto no_memory; \
    sampgdk_hook_set_src(_sampgdk_amxhooks_##name##_hook, \
                         sampgdk_amx_api_ptr->name); \
    sampgdk_hook_set_dst(_sampgdk_amxhooks_##name##_hook, \
                         (void*)_sampgdk_amxhooks_##name);
	_SAMPGDK_AMXHOOKS_LIST(_SAMPGDK_AMXHOOKS_CREATE_HOOK)
		return 0;
no_memory:
	return -ENOMEM;
#undef _SAMPGDK_AMXHOOKS_CREATE_HOOK
}

static void _sampgdk_amxhooks_destroy(void) {
  #define _SAMPGDK_AMXHOOKS_DESTROY_HOOK(name) \
    sampgdk_hook_free(_sampgdk_amxhooks_##name##_hook);
  _SAMPGDK_AMXHOOKS_LIST(_SAMPGDK_AMXHOOKS_DESTROY_HOOK)
  #undef _SAMPGDK_AMXHOOKS_DESTROY_HOOK
}

static void _sampgdk_amxhooks_install(void) {
#define _SAMPGDK_AMXHOOKS_INSTALL_HOOK(name) \
    sampgdk_hook_install(_sampgdk_amxhooks_##name##_hook);
	_SAMPGDK_AMXHOOKS_LIST_2(_SAMPGDK_AMXHOOKS_INSTALL_HOOK)
#undef _SAMPGDK_AMXHOOKS_INSTALL_HOOK
}

static void _sampgdk_amxhooks_remove(void) {
#define _SAMPGDK_AMXHOOKS_REMOVE_HOOK(name) \
    sampgdk_hook_remove(_sampgdk_amxhooks_##name##_hook);
	_SAMPGDK_AMXHOOKS_LIST_2(_SAMPGDK_AMXHOOKS_REMOVE_HOOK)
#undef _SAMPGDK_AMXHOOKS_REMOVE_HOOK
}

SAMPGDK_MODULE_INIT(amxhooks) {
  int error;

  error = _sampgdk_amxhooks_create();
  if (error < 0) {
    _sampgdk_amxhooks_destroy();
    return error;
  }

  _sampgdk_amxhooks_install();
  return 0;
}

SAMPGDK_MODULE_CLEANUP(amxhooks) {
  _sampgdk_amxhooks_remove();
  _sampgdk_amxhooks_destroy();
}

/* Copyright (C) 2012-2014 Zeex
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
#include <time.h>

#include <sampgdk/sampgdk.h>

#if SAMPGDK_WINDOWS
  #include <windows.h>
#endif

/* #include "array.h" */
/* #include "init.h" */
/* #include "plugin.h" */
/* #include "timer.h" */

struct _sampgdk_timer_info {
  bool  is_set;
  long  interval;
  bool  repeat;
  void *callback;
  void *param;
  long  started;
  void *plugin;
};

static struct sampgdk_array _sampgdk_timers;

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

static void _sampgdk_timer_fire(int timerid, long elapsed) {
  struct _sampgdk_timer_info *timer;

  assert(timerid > 0 && timerid <= _sampgdk_timers.count);

  timer = sampgdk_array_get(&_sampgdk_timers, timerid - 1);
  if (!timer->is_set) {
    return;
  }

  ((sampgdk_timer_callback)(timer->callback))(timerid, timer->param);

  /* At this point the could be killed by the timer callback,
   * so the timer pointer may be no longer valid.
   */
  if (timer->is_set) {
    if (timer->repeat) {
      timer->started = sampgdk_timer_now() - (elapsed - timer->interval);
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

int sampgdk_timer_set(long interval,
                      bool repeat,
                      sampgdk_timer_callback callback,
                      void *param) {
  struct _sampgdk_timer_info timer;
  int slot;
  int error;

  assert(callback != NULL);

  timer.is_set   = true;
  timer.interval = interval;
  timer.repeat   = repeat;
  timer.callback = callback;
  timer.param    = param;
  timer.started  = sampgdk_timer_now();
  timer.plugin   = sampgdk_plugin_get_handle(callback);

  slot = _sampgdk_timer_find_slot();
  if (slot >= 0) {
    sampgdk_array_set(&_sampgdk_timers, slot, &timer);
  } else {
    error = sampgdk_array_append(&_sampgdk_timers, &timer);
    if (error < 0) {
      return -error;
    }
    slot = _sampgdk_timers.count - 1;
  }

  /* Timer IDs returned by the SA:MP's SetTimer() API begin
   * with 1, and so do they here.
   */
  return slot + 1;
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
  return 0;
}

void sampgdk_timer_process_timers(void *plugin) {
  long now;
  long elapsed;
  int i;
  struct _sampgdk_timer_info *timer;

  assert(plugin != NULL);

  now = sampgdk_timer_now();

  for (i = 0; i < _sampgdk_timers.count; i++) {
    timer = sampgdk_array_get(&_sampgdk_timers, i);

    if (!timer->is_set) {
      continue;
    }

    if (plugin != NULL && timer->plugin != plugin) {
      continue;
    }

    elapsed = now - timer->started;

    if (elapsed >= timer->interval) {
      _sampgdk_timer_fire(i + 1, elapsed);
    }
  }
}

#if SAMPGDK_WINDOWS

long sampgdk_timer_now(void) {
  LARGE_INTEGER freq;
  LARGE_INTEGER counter;

  if (!QueryPerformanceFrequency(&freq) ||
      !QueryPerformanceCounter(&counter)) {
    return 0;
  }

  return (long)(1000.0L / freq.QuadPart * counter.QuadPart);;
}

#else /* SAMPGDK_WINDOWS */

long sampgdk_timer_now(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000L);
}

#endif /* !SAMPGDK_WINDOWS */

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

#include <assert.h>

#include <sampgdk/sampgdk.h>

/* #include "internal/amx.h" */
/* #include "internal/init.h" */
/* #include "internal/log.h" */
/* #include "internal/logprintf.h" */
/* #include "internal/plugin.h" */
/* #include "internal/timer.h" */

#ifdef _MSC_VER
  #define _SAMPGDK_RETURN_ADDRESS() _ReturnAddress()
#else
  #define _SAMPGDK_RETURN_ADDRESS() __builtin_return_address(0)
#endif

static void _sampgdk_init(void **plugin_data) {
  int error;

  sampgdk_logprintf_impl = plugin_data[PLUGIN_DATA_LOGPRINTF];
  sampgdk_amx_api_ptr = plugin_data[PLUGIN_DATA_AMX_EXPORTS];

  error = sampgdk_module_init();
  if (error  < 0) {
    sampgdk_log_error_code(error);
  }
}

static int _sampgdk_init_plugin(void *plugin, void **plugin_data) {
  int error;

  assert(plugin != NULL);

  if (sampgdk_plugin_get_list() == NULL) {
    _sampgdk_init(plugin_data);
  }

  error = sampgdk_plugin_register(plugin);
  if (error < 0) {
    sampgdk_log_error_code(error);
  }

  return error;
}

static void _sampgdk_cleanup(void) {
  sampgdk_module_cleanup();
}

static void _sampgdk_cleanup_plugin(void *plugin) {
  int error;

  assert(plugin != NULL);

  error = sampgdk_plugin_unregister(plugin);
  if (error < 0) {
    sampgdk_log_error_code(error);
  }

  if (sampgdk_plugin_get_list() == NULL) {
    _sampgdk_cleanup();
  }
}

SAMPGDK_API(unsigned int, sampgdk_Supports(void)) {
  return SUPPORTS_VERSION;
}

SAMPGDK_API(bool, sampgdk_Load(void **ppData)) {
  void *plugin = sampgdk_plugin_get_handle(_SAMPGDK_RETURN_ADDRESS());
  return _sampgdk_init_plugin(plugin, ppData) >= 0;
}

SAMPGDK_API(void, sampgdk_Unload(void)) {
  void *plugin = sampgdk_plugin_get_handle(_SAMPGDK_RETURN_ADDRESS());
  _sampgdk_cleanup_plugin(plugin);
}

SAMPGDK_API(void, sampgdk_ProcessTick(void)) {
  void *plugin = sampgdk_plugin_get_handle(_SAMPGDK_RETURN_ADDRESS());
  sampgdk_timer_process_timers(plugin);
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

#include <sampgdk/sampgdk.h>

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/likely.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(bool, SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[14];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetSpawnInfo");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SpawnPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SpawnPlayer");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerPos(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerPos");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerPosFindZ(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerPosFindZ");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerPos(int playerid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerPos");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerFacingAngle(int playerid, float angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerFacingAngle");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(angle);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerFacingAngle(int playerid, float * angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell angle_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerFacingAngle");
  }
  sampgdk_fakeamx_push(1, &angle_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = angle_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(angle_, angle);
  sampgdk_fakeamx_pop(angle_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerInRangeOfPoint");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(range);
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(float, GetPlayerDistanceFromPoint(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerDistanceFromPoint");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerStreamedIn");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)forplayerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerInterior(int playerid, int interiorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerInterior");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)interiorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerInterior(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerInterior");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerHealth(int playerid, float health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerHealth");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(health);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerHealth(int playerid, float * health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell health_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerHealth");
  }
  sampgdk_fakeamx_push(1, &health_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = health_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(health_, health);
  sampgdk_fakeamx_pop(health_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerArmour(int playerid, float armour)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerArmour");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(armour);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerArmour(int playerid, float * armour)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell armour_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerArmour");
  }
  sampgdk_fakeamx_push(1, &armour_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = armour_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(armour_, armour);
  sampgdk_fakeamx_pop(armour_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerAmmo(int playerid, int weaponid, int ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerAmmo");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)weaponid;
  params[3] = (cell)ammo;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerAmmo(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerAmmo");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerWeaponState(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerWeaponState");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerTargetPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerTargetPlayer");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerTeam(int playerid, int teamid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerTeam");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)teamid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerTeam(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerTeam");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerScore(int playerid, int score)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerScore");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)score;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerScore(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerScore");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerDrunkLevel(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerDrunkLevel");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerDrunkLevel(int playerid, int level)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerDrunkLevel");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)level;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerColor(int playerid, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerColor");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerColor(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerColor");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerSkin(int playerid, int skinid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerSkin");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)skinid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerSkin(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerSkin");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, GivePlayerWeapon(int playerid, int weaponid, int ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GivePlayerWeapon");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)weaponid;
  params[3] = (cell)ammo;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ResetPlayerWeapons(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ResetPlayerWeapons");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerArmedWeapon(int playerid, int weaponid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerArmedWeapon");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)weaponid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerWeaponData(int playerid, int slot, int * weapon, int * ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell weapon_;
  cell ammo_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerWeaponData");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GivePlayerMoney(int playerid, int money)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GivePlayerMoney");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)money;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ResetPlayerMoney(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ResetPlayerMoney");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, SetPlayerName(int playerid, const char * name)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell name_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerName");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerMoney");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerState(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerState");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerIp");
  }
  sampgdk_fakeamx_push(size, &ip_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = ip_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(ip_, ip, size);
  sampgdk_fakeamx_pop(ip_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerPing(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerPing");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerWeapon(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerWeapon");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerKeys");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerName(int playerid, char * name, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell name_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerName");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerTime");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)hour;
  params[3] = (cell)minute;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerTime(int playerid, int * hour, int * minute)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell hour_;
  cell minute_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerTime");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TogglePlayerClock(int playerid, bool toggle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TogglePlayerClock");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)toggle;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerWeather(int playerid, int weather)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerWeather");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)weather;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ForceClassSelection(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ForceClassSelection");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerWantedLevel(int playerid, int level)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerWantedLevel");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)level;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerWantedLevel(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerWantedLevel");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerFightingStyle(int playerid, int style)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerFightingStyle");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)style;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerFightingStyle(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerFightingStyle");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerVelocity(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerVelocity");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerVelocity(int playerid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerVelocity");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayCrimeReportForPlayer(int playerid, int suspectid, int crime)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayCrimeReportForPlayer");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)suspectid;
  params[3] = (cell)crime;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayAudioStreamForPlayer(int playerid, const char * url, float posX, float posY, float posZ, float distance, bool usepos)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[8];
  cell url_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayAudioStreamForPlayer");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, StopAudioStreamForPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("StopAudioStreamForPlayer");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerShopName(int playerid, const char * shopname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell shopname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerShopName");
  }
  sampgdk_fakeamx_push_string(shopname, NULL, &shopname_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = shopname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(shopname_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerSkillLevel(int playerid, int skill, int level)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerSkillLevel");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)skill;
  params[3] = (cell)level;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerSurfingVehicleID(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerSurfingVehicleID");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerSurfingObjectID(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerSurfingObjectID");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("RemoveBuildingForPlayer");
  }
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)modelid;
  params[3] = amx_ftoc(fX);
  params[4] = amx_ftoc(fY);
  params[5] = amx_ftoc(fZ);
  params[6] = amx_ftoc(fRadius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerLastShotVectors");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ, int materialcolor1, int materialcolor2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[16];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerAttachedObject");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, RemovePlayerAttachedObject(int playerid, int index)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("RemovePlayerAttachedObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerAttachedObjectSlotUsed(int playerid, int index)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerAttachedObjectSlotUsed");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, EditAttachedObject(int playerid, int index)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("EditAttachedObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, CreatePlayerTextDraw(int playerid, float x, float y, const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell text_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreatePlayerTextDraw");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawDestroy");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawLetterSize(int playerid, int text, float x, float y)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawLetterSize");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawTextSize(int playerid, int text, float x, float y)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawTextSize");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawAlignment(int playerid, int text, int alignment)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawAlignment");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)alignment;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawColor(int playerid, int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawColor");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawUseBox(int playerid, int text, bool use)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawUseBox");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)use;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawBoxColor(int playerid, int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawBoxColor");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetShadow(int playerid, int text, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawSetShadow");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetOutline(int playerid, int text, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawSetOutline");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawBackgroundColor(int playerid, int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawBackgroundColor");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawFont(int playerid, int text, int font)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawFont");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)font;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetProportional(int playerid, int text, bool set)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawSetProportional");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)set;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetSelectable(int playerid, int text, bool set)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawSetSelectable");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)set;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawShow(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawShow");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawHide(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawHide");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetString(int playerid, int text, const char * string)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell string_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawSetString");
  }
  sampgdk_fakeamx_push_string(string, NULL, &string_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = string_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(string_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewModel(int playerid, int text, int modelindex)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawSetPreviewModel");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)modelindex;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewRot(int playerid, int text, float fRotX, float fRotY, float fRotZ, float fZoom)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawSetPreviewRot");
  }
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = amx_ftoc(fRotX);
  params[4] = amx_ftoc(fRotY);
  params[5] = amx_ftoc(fRotZ);
  params[6] = amx_ftoc(fZoom);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewVehCol(int playerid, int text, int color1, int color2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerTextDrawSetPreviewVehCol");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  params[3] = (cell)color1;
  params[4] = (cell)color2;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPVarInt(int playerid, const char * varname, int value)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell varname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPVarInt");
  }
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  params[3] = (cell)value;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPVarInt(int playerid, const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell varname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPVarInt");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPVarString");
  }
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  sampgdk_fakeamx_push_string(value, NULL, &value_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  params[3] = value_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(value_);
  sampgdk_fakeamx_pop(varname_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPVarString(int playerid, const char * varname, char * value, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell varname_;
  cell value_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPVarString");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPVarFloat(int playerid, const char * varname, float value)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell varname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPVarFloat");
  }
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  params[3] = amx_ftoc(value);
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(float, GetPVarFloat(int playerid, const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell varname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPVarFloat");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DeletePVar");
  }
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = varname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPVarsUpperIndex(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPVarsUpperIndex");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPVarNameAtIndex");
  }
  sampgdk_fakeamx_push(size, &varname_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)index;
  params[3] = varname_;
  params[4] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(varname_, varname, size);
  sampgdk_fakeamx_pop(varname_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPVarType(int playerid, const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell varname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPVarType");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerChatBubble");
  }
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = text_;
  params[3] = (cell)color;
  params[4] = amx_ftoc(drawdistance);
  params[5] = (cell)expiretime;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PutPlayerInVehicle(int playerid, int vehicleid, int seatid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PutPlayerInVehicle");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)vehicleid;
  params[3] = (cell)seatid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerVehicleID(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerVehicleID");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerVehicleSeat(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerVehicleSeat");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, RemovePlayerFromVehicle(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("RemovePlayerFromVehicle");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TogglePlayerControllable(int playerid, bool toggle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TogglePlayerControllable");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)toggle;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerPlaySound(int playerid, int soundid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerPlaySound");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)soundid;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ApplyAnimation(int playerid, const char * animlib, const char * animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[11];
  cell animlib_;
  cell animname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ApplyAnimation");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ClearAnimations(int playerid, bool forcesync)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ClearAnimations");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)forcesync;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerAnimationIndex(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerAnimationIndex");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetAnimationName");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerSpecialAction(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerSpecialAction");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerSpecialAction(int playerid, int actionid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerSpecialAction");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)actionid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerCheckpoint(int playerid, float x, float y, float z, float size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerCheckpoint");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  params[5] = amx_ftoc(size);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DisablePlayerCheckpoint(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DisablePlayerCheckpoint");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerRaceCheckpoint");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DisablePlayerRaceCheckpoint(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DisablePlayerRaceCheckpoint");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerWorldBounds");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x_max);
  params[3] = amx_ftoc(x_min);
  params[4] = amx_ftoc(y_max);
  params[5] = amx_ftoc(y_min);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerMarkerForPlayer");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)showplayerid;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ShowPlayerNameTagForPlayer");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)showplayerid;
  params[3] = (cell)show;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerMapIcon");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, RemovePlayerMapIcon(int playerid, int iconid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("RemovePlayerMapIcon");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)iconid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AllowPlayerTeleport(int playerid, bool allow)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AllowPlayerTeleport");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)allow;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerCameraPos(int playerid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerCameraPos");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerCameraLookAt");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  params[5] = (cell)cut;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetCameraBehindPlayer(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetCameraBehindPlayer");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerCameraPos(int playerid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerCameraPos");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerCameraFrontVector(int playerid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerCameraFrontVector");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerCameraMode(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerCameraMode");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(float, GetPlayerCameraAspectRatio(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerCameraAspectRatio");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(float, GetPlayerCameraZoom(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerCameraZoom");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(bool, AttachCameraToObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AttachCameraToObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AttachCameraToPlayerObject(int playerid, int playerobjectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AttachCameraToPlayerObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)playerobjectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("InterpolateCameraPos");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("InterpolateCameraLookAt");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerConnected(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerConnected");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInVehicle(int playerid, int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerInVehicle");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInAnyVehicle(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerInAnyVehicle");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInCheckpoint(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerInCheckpoint");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerInRaceCheckpoint(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerInRaceCheckpoint");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerVirtualWorld(int playerid, int worldid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerVirtualWorld");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)worldid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerVirtualWorld(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerVirtualWorld");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, EnableStuntBonusForPlayer(int playerid, bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("EnableStuntBonusForPlayer");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, EnableStuntBonusForAll(bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("EnableStuntBonusForAll");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TogglePlayerSpectating(int playerid, bool toggle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TogglePlayerSpectating");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)toggle;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerSpectatePlayer(int playerid, int targetplayerid, int mode)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerSpectatePlayer");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)targetplayerid;
  params[3] = (cell)mode;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("PlayerSpectateVehicle");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)targetvehicleid;
  params[3] = (cell)mode;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, StartRecordingPlayerData(int playerid, int recordtype, const char * recordname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell recordname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("StartRecordingPlayerData");
  }
  sampgdk_fakeamx_push_string(recordname, NULL, &recordname_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)recordtype;
  params[3] = recordname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(recordname_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, StopRecordingPlayerData(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("StopRecordingPlayerData");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, CreateExplosionForPlayer(int playerid, float X, float Y, float Z, int type, float Radius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreateExplosionForPlayer");
  }
  params[0] = 6 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = amx_ftoc(X);
  params[3] = amx_ftoc(Y);
  params[4] = amx_ftoc(Z);
  params[5] = (cell)type;
  params[6] = amx_ftoc(Radius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

static const struct sampgdk_callback _a_players_callback_table[] = {
  {NULL, NULL}
};

SAMPGDK_MODULE_INIT(a_players) {
  return sampgdk_callback_register_table(_a_players_callback_table);
}
SAMPGDK_MODULE_CLEANUP(a_players) {
  sampgdk_callback_unregister_table(_a_players_callback_table);
}

#include <sampgdk/sampgdk.h>

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/likely.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(bool, SendClientMessage(int playerid, int color, const char * message)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell message_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SendClientMessage");
  }
  sampgdk_fakeamx_push_string(message, NULL, &message_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)color;
  params[3] = message_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(message_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SendClientMessageToAll(int color, const char * message)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell message_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SendClientMessageToAll");
  }
  sampgdk_fakeamx_push_string(message, NULL, &message_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)color;
  params[2] = message_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(message_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SendPlayerMessageToPlayer(int playerid, int senderid, const char * message)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell message_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SendPlayerMessageToPlayer");
  }
  sampgdk_fakeamx_push_string(message, NULL, &message_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)senderid;
  params[3] = message_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(message_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SendPlayerMessageToAll(int senderid, const char * message)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell message_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SendPlayerMessageToAll");
  }
  sampgdk_fakeamx_push_string(message, NULL, &message_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)senderid;
  params[2] = message_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(message_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SendDeathMessage(int killer, int killee, int weapon)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SendDeathMessage");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)killer;
  params[2] = (cell)killee;
  params[3] = (cell)weapon;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SendDeathMessageToPlayer(int playerid, int killer, int killee, int weapon)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SendDeathMessageToPlayer");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)killer;
  params[3] = (cell)killee;
  params[4] = (cell)weapon;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GameTextForAll(const char * text, int time, int style)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell text_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GameTextForAll");
  }
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 3 * sizeof(cell);
  params[1] = text_;
  params[2] = (cell)time;
  params[3] = (cell)style;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GameTextForPlayer(int playerid, const char * text, int time, int style)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell text_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GameTextForPlayer");
  }
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = text_;
  params[3] = (cell)time;
  params[4] = (cell)style;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetTickCount()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetTickCount");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetMaxPlayers()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetMaxPlayers");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(float, VectorSize(float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("VectorSize");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = amx_ftoc(x);
  params[2] = amx_ftoc(y);
  params[3] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(bool, SetGameModeText(const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell text_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetGameModeText");
  }
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 1 * sizeof(cell);
  params[1] = text_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetTeamCount(int count)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetTeamCount");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)count;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[12];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AddPlayerClass");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AddPlayerClassEx");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AddStaticVehicle");
  }
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

SAMPGDK_NATIVE(int, AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AddStaticVehicleEx");
  }
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)modelid;
  params[2] = amx_ftoc(spawn_x);
  params[3] = amx_ftoc(spawn_y);
  params[4] = amx_ftoc(spawn_z);
  params[5] = amx_ftoc(z_angle);
  params[6] = (cell)color1;
  params[7] = (cell)color2;
  params[8] = (cell)respawn_delay;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, AddStaticPickup(int model, int type, float x, float y, float z, int virtualworld)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AddStaticPickup");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreatePickup");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DestroyPickup");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)pickup;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ShowNameTags(bool show)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ShowNameTags");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)show;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ShowPlayerMarkers(int mode)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ShowPlayerMarkers");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)mode;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GameModeExit()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GameModeExit");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetWorldTime(int hour)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetWorldTime");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)hour;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetWeaponName(int weaponid, char * name, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell name_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetWeaponName");
  }
  sampgdk_fakeamx_push(size, &name_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)weaponid;
  params[2] = name_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(name_, name, size);
  sampgdk_fakeamx_pop(name_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, EnableTirePopping(bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("EnableTirePopping");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, EnableVehicleFriendlyFire()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("EnableVehicleFriendlyFire");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AllowInteriorWeapons(bool allow)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AllowInteriorWeapons");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)allow;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetWeather(int weatherid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetWeather");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)weatherid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetGravity(float gravity)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetGravity");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = amx_ftoc(gravity);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AllowAdminTeleport(bool allow)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AllowAdminTeleport");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)allow;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetDeathDropAmount(int amount)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetDeathDropAmount");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)amount;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, CreateExplosion(float x, float y, float z, int type, float radius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreateExplosion");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = amx_ftoc(x);
  params[2] = amx_ftoc(y);
  params[3] = amx_ftoc(z);
  params[4] = (cell)type;
  params[5] = amx_ftoc(radius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, EnableZoneNames(bool enable)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("EnableZoneNames");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)enable;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, UsePlayerPedAnims()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("UsePlayerPedAnims");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DisableInteriorEnterExits()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DisableInteriorEnterExits");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetNameTagDrawDistance(float distance)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetNameTagDrawDistance");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = amx_ftoc(distance);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DisableNameTagLOS()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DisableNameTagLOS");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, LimitGlobalChatRadius(float chat_radius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("LimitGlobalChatRadius");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = amx_ftoc(chat_radius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, LimitPlayerMarkerRadius(float marker_radius)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("LimitPlayerMarkerRadius");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = amx_ftoc(marker_radius);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ConnectNPC(const char * name, const char * script)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell name_;
  cell script_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ConnectNPC");
  }
  sampgdk_fakeamx_push_string(name, NULL, &name_);
  sampgdk_fakeamx_push_string(script, NULL, &script_);
  params[0] = 2 * sizeof(cell);
  params[1] = name_;
  params[2] = script_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(script_);
  sampgdk_fakeamx_pop(name_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerNPC(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerNPC");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerAdmin(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerAdmin");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, Kick(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("Kick");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, Ban(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("Ban");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, BanEx(int playerid, const char * reason)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell reason_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("BanEx");
  }
  sampgdk_fakeamx_push_string(reason, NULL, &reason_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = reason_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(reason_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SendRconCommand(const char * command)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell command_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SendRconCommand");
  }
  sampgdk_fakeamx_push_string(command, NULL, &command_);
  params[0] = 1 * sizeof(cell);
  params[1] = command_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(command_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetServerVarAsString(const char * varname, char * value, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell varname_;
  cell value_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetServerVarAsString");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetServerVarAsInt(const char * varname)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell varname_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetServerVarAsInt");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetServerVarAsBool");
  }
  sampgdk_fakeamx_push_string(varname, NULL, &varname_);
  params[0] = 1 * sizeof(cell);
  params[1] = varname_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(varname_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerNetworkStats(int playerid, char * retstr, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell retstr_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerNetworkStats");
  }
  sampgdk_fakeamx_push(size, &retstr_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = retstr_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(retstr_, retstr, size);
  sampgdk_fakeamx_pop(retstr_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetNetworkStats(char * retstr, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell retstr_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetNetworkStats");
  }
  sampgdk_fakeamx_push(size, &retstr_);
  params[0] = 2 * sizeof(cell);
  params[1] = retstr_;
  params[2] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(retstr_, retstr, size);
  sampgdk_fakeamx_pop(retstr_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerVersion(int playerid, char * version, int len)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell version_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerVersion");
  }
  sampgdk_fakeamx_push(len, &version_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = version_;
  params[3] = (cell)len;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(version_, version, len);
  sampgdk_fakeamx_pop(version_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, BlockIpAddress(const char * ip_address, int timems)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell ip_address_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("BlockIpAddress");
  }
  sampgdk_fakeamx_push_string(ip_address, NULL, &ip_address_);
  params[0] = 2 * sizeof(cell);
  params[1] = ip_address_;
  params[2] = (cell)timems;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(ip_address_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, UnBlockIpAddress(const char * ip_address)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  cell ip_address_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("UnBlockIpAddress");
  }
  sampgdk_fakeamx_push_string(ip_address, NULL, &ip_address_);
  params[0] = 1 * sizeof(cell);
  params[1] = ip_address_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(ip_address_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetServerTickRate()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetServerTickRate");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_GetConnectedTime(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_GetConnectedTime");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_MessagesReceived(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_MessagesReceived");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_BytesReceived(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_BytesReceived");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_MessagesSent(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_MessagesSent");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_BytesSent(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_BytesSent");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, NetStats_MessagesRecvPerSecond(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_MessagesRecvPerSecond");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(float, NetStats_PacketLossPercent(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_PacketLossPercent");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(int, NetStats_ConnectionStatus(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_ConnectionStatus");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("NetStats_GetIpPort");
  }
  sampgdk_fakeamx_push(ip_port_len, &ip_port_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = ip_port_;
  params[3] = (cell)ip_port_len;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(ip_port_, ip_port, ip_port_len);
  sampgdk_fakeamx_pop(ip_port_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, CreateMenu(const char * title, int columns, float x, float y, float col1width, float col2width)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  cell title_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreateMenu");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DestroyMenu");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)menuid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, AddMenuItem(int menuid, int column, const char * menutext)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell menutext_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AddMenuItem");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetMenuColumnHeader");
  }
  sampgdk_fakeamx_push_string(columnheader, NULL, &columnheader_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)column;
  params[3] = columnheader_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(columnheader_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ShowMenuForPlayer(int menuid, int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ShowMenuForPlayer");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, HideMenuForPlayer(int menuid, int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("HideMenuForPlayer");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsValidMenu(int menuid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsValidMenu");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)menuid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DisableMenu(int menuid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DisableMenu");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)menuid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DisableMenuRow(int menuid, int row)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DisableMenuRow");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)menuid;
  params[2] = (cell)row;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetPlayerMenu(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerMenu");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawCreate");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawDestroy");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawLetterSize(int text, float x, float y)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawLetterSize");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawTextSize(int text, float x, float y)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawTextSize");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawAlignment(int text, int alignment)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawAlignment");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)alignment;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawColor(int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawColor");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawUseBox(int text, bool use)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawUseBox");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)use;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawBoxColor(int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawBoxColor");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetShadow(int text, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawSetShadow");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetOutline(int text, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawSetOutline");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawBackgroundColor(int text, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawBackgroundColor");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawFont(int text, int font)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawFont");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)font;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetProportional(int text, bool set)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawSetProportional");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)set;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetSelectable(int text, bool set)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawSetSelectable");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)set;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawShowForPlayer(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawShowForPlayer");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawHideForPlayer(int playerid, int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawHideForPlayer");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawShowForAll(int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawShowForAll");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawHideForAll(int text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawHideForAll");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)text;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetString(int text, const char * string)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell string_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawSetString");
  }
  sampgdk_fakeamx_push_string(string, NULL, &string_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = string_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(string_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetPreviewModel(int text, int modelindex)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawSetPreviewModel");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)modelindex;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetPreviewRot(int text, float fRotX, float fRotY, float fRotZ, float fZoom)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawSetPreviewRot");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = amx_ftoc(fRotX);
  params[3] = amx_ftoc(fRotY);
  params[4] = amx_ftoc(fRotZ);
  params[5] = amx_ftoc(fZoom);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, TextDrawSetPreviewVehCol(int text, int color1, int color2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("TextDrawSetPreviewVehCol");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)text;
  params[2] = (cell)color1;
  params[3] = (cell)color2;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SelectTextDraw(int playerid, int hovercolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SelectTextDraw");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)hovercolor;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, CancelSelectTextDraw(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CancelSelectTextDraw");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GangZoneCreate(float minx, float miny, float maxx, float maxy)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneCreate");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneDestroy");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneShowForPlayer(int playerid, int zone, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneShowForPlayer");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)zone;
  params[3] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneShowForAll(int zone, int color)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneShowForAll");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)zone;
  params[2] = (cell)color;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneHideForPlayer(int playerid, int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneHideForPlayer");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneHideForAll(int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneHideForAll");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneFlashForPlayer(int playerid, int zone, int flashcolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneFlashForPlayer");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)zone;
  params[3] = (cell)flashcolor;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneFlashForAll(int zone, int flashcolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneFlashForAll");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)zone;
  params[2] = (cell)flashcolor;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneStopFlashForPlayer(int playerid, int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneStopFlashForPlayer");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GangZoneStopFlashForAll(int zone)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GangZoneStopFlashForAll");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)zone;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, Create3DTextLabel(const char * text, int color, float x, float y, float z, float DrawDistance, int virtualworld, bool testLOS)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  cell text_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("Create3DTextLabel");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("Delete3DTextLabel");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)id;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("Attach3DTextLabelToPlayer");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)id;
  params[2] = (cell)playerid;
  params[3] = amx_ftoc(OffsetX);
  params[4] = amx_ftoc(OffsetY);
  params[5] = amx_ftoc(OffsetZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("Attach3DTextLabelToVehicle");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)id;
  params[2] = (cell)vehicleid;
  params[3] = amx_ftoc(OffsetX);
  params[4] = amx_ftoc(OffsetY);
  params[5] = amx_ftoc(OffsetZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, Update3DTextLabelText(int id, int color, const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell text_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("Update3DTextLabelText");
  }
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)id;
  params[2] = (cell)color;
  params[3] = text_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, CreatePlayer3DTextLabel(int playerid, const char * text, int color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[11];
  cell text_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreatePlayer3DTextLabel");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DeletePlayer3DTextLabel");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)id;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, UpdatePlayer3DTextLabelText(int playerid, int id, int color, const char * text)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell text_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("UpdatePlayer3DTextLabelText");
  }
  sampgdk_fakeamx_push_string(text, NULL, &text_);
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)id;
  params[3] = (cell)color;
  params[4] = text_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(text_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ShowPlayerDialog(int playerid, int dialogid, int style, const char * caption, const char * info, const char * button1, const char * button2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[8];
  cell caption_;
  cell info_;
  cell button1_;
  cell button2_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ShowPlayerDialog");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, gpci(int playerid, char * buffer, int size)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  cell buffer_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("gpci");
  }
  sampgdk_fakeamx_push(size, &buffer_);
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = buffer_;
  params[3] = (cell)size;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_string(buffer_, buffer, size);
  sampgdk_fakeamx_pop(buffer_);
  return (bool)(retval);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnGameModeInit_type)();
static bool _OnGameModeInit_handler(AMX *amx, void *callback, cell *retval) {
  ((OnGameModeInit_type)callback)();
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnGameModeExit_type)();
static bool _OnGameModeExit_handler(AMX *amx, void *callback, cell *retval) {
  ((OnGameModeExit_type)callback)();
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerConnect_type)(int playerid);
static bool _OnPlayerConnect_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  retval_ = ((OnPlayerConnect_type)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerDisconnect_type)(int playerid, int reason);
static bool _OnPlayerDisconnect_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int reason;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&reason);
  retval_ = ((OnPlayerDisconnect_type)callback)(playerid, reason);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerSpawn_type)(int playerid);
static bool _OnPlayerSpawn_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  retval_ = ((OnPlayerSpawn_type)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerDeath_type)(int playerid, int killerid, int reason);
static bool _OnPlayerDeath_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int killerid;
  int reason;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&killerid);
  sampgdk_param_get_cell(amx, 2, (void*)&reason);
  ((OnPlayerDeath_type)callback)(playerid, killerid, reason);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleSpawn_type)(int vehicleid);
static bool _OnVehicleSpawn_handler(AMX *amx, void *callback, cell *retval) {
  int vehicleid;
  sampgdk_param_get_cell(amx, 0, (void*)&vehicleid);
  ((OnVehicleSpawn_type)callback)(vehicleid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleDeath_type)(int vehicleid, int killerid);
static bool _OnVehicleDeath_handler(AMX *amx, void *callback, cell *retval) {
  int vehicleid;
  int killerid;
  sampgdk_param_get_cell(amx, 0, (void*)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void*)&killerid);
  ((OnVehicleDeath_type)callback)(vehicleid, killerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerText_type)(int playerid, const char * text);
static bool _OnPlayerText_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  const char * text;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_string(amx, 1, (void*)&text);
  retval_ = ((OnPlayerText_type)callback)(playerid, text);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void*)text);
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerCommandText_type)(int playerid, const char * cmdtext);
static bool _OnPlayerCommandText_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  const char * cmdtext;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_string(amx, 1, (void*)&cmdtext);
  retval_ = ((OnPlayerCommandText_type)callback)(playerid, cmdtext);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void*)cmdtext);
  return (retval_ != true);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerRequestClass_type)(int playerid, int classid);
static bool _OnPlayerRequestClass_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int classid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&classid);
  retval_ = ((OnPlayerRequestClass_type)callback)(playerid, classid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEnterVehicle_type)(int playerid, int vehicleid, bool ispassenger);
static bool _OnPlayerEnterVehicle_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int vehicleid;
  bool ispassenger;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&vehicleid);
  sampgdk_param_get_bool(amx, 2, (void*)&ispassenger);
  ((OnPlayerEnterVehicle_type)callback)(playerid, vehicleid, ispassenger);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerExitVehicle_type)(int playerid, int vehicleid);
static bool _OnPlayerExitVehicle_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int vehicleid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&vehicleid);
  ((OnPlayerExitVehicle_type)callback)(playerid, vehicleid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerStateChange_type)(int playerid, int newstate, int oldstate);
static bool _OnPlayerStateChange_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int newstate;
  int oldstate;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&newstate);
  sampgdk_param_get_cell(amx, 2, (void*)&oldstate);
  ((OnPlayerStateChange_type)callback)(playerid, newstate, oldstate);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEnterCheckpoint_type)(int playerid);
static bool _OnPlayerEnterCheckpoint_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  retval_ = ((OnPlayerEnterCheckpoint_type)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerLeaveCheckpoint_type)(int playerid);
static bool _OnPlayerLeaveCheckpoint_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  ((OnPlayerLeaveCheckpoint_type)callback)(playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEnterRaceCheckpoint_type)(int playerid);
static bool _OnPlayerEnterRaceCheckpoint_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  retval_ = ((OnPlayerEnterRaceCheckpoint_type)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerLeaveRaceCheckpoint_type)(int playerid);
static bool _OnPlayerLeaveRaceCheckpoint_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  ((OnPlayerLeaveRaceCheckpoint_type)callback)(playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnRconCommand_type)(const char * cmd);
static bool _OnRconCommand_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  const char * cmd;
  sampgdk_param_get_string(amx, 0, (void*)&cmd);
  retval_ = ((OnRconCommand_type)callback)(cmd);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void*)cmd);
  return (retval_ != true);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerRequestSpawn_type)(int playerid);
static bool _OnPlayerRequestSpawn_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  retval_ = ((OnPlayerRequestSpawn_type)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnObjectMoved_type)(int objectid);
static bool _OnObjectMoved_handler(AMX *amx, void *callback, cell *retval) {
  int objectid;
  sampgdk_param_get_cell(amx, 0, (void*)&objectid);
  ((OnObjectMoved_type)callback)(objectid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerObjectMoved_type)(int playerid, int objectid);
static bool _OnPlayerObjectMoved_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int objectid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&objectid);
  ((OnPlayerObjectMoved_type)callback)(playerid, objectid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerPickUpPickup_type)(int playerid, int pickupid);
static bool _OnPlayerPickUpPickup_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int pickupid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&pickupid);
  ((OnPlayerPickUpPickup_type)callback)(playerid, pickupid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleMod_type)(int playerid, int vehicleid, int componentid);
static bool _OnVehicleMod_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int vehicleid;
  int componentid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&vehicleid);
  sampgdk_param_get_cell(amx, 2, (void*)&componentid);
  retval_ = ((OnVehicleMod_type)callback)(playerid, vehicleid, componentid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnEnterExitModShop_type)(int playerid, int enterexit, int interiorid);
static bool _OnEnterExitModShop_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int enterexit;
  int interiorid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&enterexit);
  sampgdk_param_get_cell(amx, 2, (void*)&interiorid);
  ((OnEnterExitModShop_type)callback)(playerid, enterexit, interiorid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehiclePaintjob_type)(int playerid, int vehicleid, int paintjobid);
static bool _OnVehiclePaintjob_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int vehicleid;
  int paintjobid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&vehicleid);
  sampgdk_param_get_cell(amx, 2, (void*)&paintjobid);
  ((OnVehiclePaintjob_type)callback)(playerid, vehicleid, paintjobid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleRespray_type)(int playerid, int vehicleid, int color1, int color2);
static bool _OnVehicleRespray_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int vehicleid;
  int color1;
  int color2;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&vehicleid);
  sampgdk_param_get_cell(amx, 2, (void*)&color1);
  sampgdk_param_get_cell(amx, 3, (void*)&color2);
  ((OnVehicleRespray_type)callback)(playerid, vehicleid, color1, color2);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleDamageStatusUpdate_type)(int vehicleid, int playerid);
static bool _OnVehicleDamageStatusUpdate_handler(AMX *amx, void *callback, cell *retval) {
  int vehicleid;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void*)&playerid);
  ((OnVehicleDamageStatusUpdate_type)callback)(vehicleid, playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnUnoccupiedVehicleUpdate_type)(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z);
static bool _OnUnoccupiedVehicleUpdate_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int vehicleid;
  int playerid;
  int passenger_seat;
  float new_x;
  float new_y;
  float new_z;
  sampgdk_param_get_cell(amx, 0, (void*)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void*)&playerid);
  sampgdk_param_get_cell(amx, 2, (void*)&passenger_seat);
  sampgdk_param_get_float(amx, 3, (void*)&new_x);
  sampgdk_param_get_float(amx, 4, (void*)&new_y);
  sampgdk_param_get_float(amx, 5, (void*)&new_z);
  retval_ = ((OnUnoccupiedVehicleUpdate_type)callback)(vehicleid, playerid, passenger_seat, new_x, new_y, new_z);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerSelectedMenuRow_type)(int playerid, int row);
static bool _OnPlayerSelectedMenuRow_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int row;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&row);
  ((OnPlayerSelectedMenuRow_type)callback)(playerid, row);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerExitedMenu_type)(int playerid);
static bool _OnPlayerExitedMenu_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  ((OnPlayerExitedMenu_type)callback)(playerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerInteriorChange_type)(int playerid, int newinteriorid, int oldinteriorid);
static bool _OnPlayerInteriorChange_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int newinteriorid;
  int oldinteriorid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&newinteriorid);
  sampgdk_param_get_cell(amx, 2, (void*)&oldinteriorid);
  ((OnPlayerInteriorChange_type)callback)(playerid, newinteriorid, oldinteriorid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerKeyStateChange_type)(int playerid, int newkeys, int oldkeys);
static bool _OnPlayerKeyStateChange_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int newkeys;
  int oldkeys;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&newkeys);
  sampgdk_param_get_cell(amx, 2, (void*)&oldkeys);
  retval_ = ((OnPlayerKeyStateChange_type)callback)(playerid, newkeys, oldkeys);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnRconLoginAttempt_type)(const char * ip, const char * password, bool success);
static bool _OnRconLoginAttempt_handler(AMX *amx, void *callback, cell *retval) {
  const char * ip;
  const char * password;
  bool success;
  sampgdk_param_get_string(amx, 0, (void*)&ip);
  sampgdk_param_get_string(amx, 1, (void*)&password);
  sampgdk_param_get_bool(amx, 2, (void*)&success);
  ((OnRconLoginAttempt_type)callback)(ip, password, success);
  free((void*)ip);
  free((void*)password);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerUpdate_type)(int playerid);
static bool _OnPlayerUpdate_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  retval_ = ((OnPlayerUpdate_type)callback)(playerid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerStreamIn_type)(int playerid, int forplayerid);
static bool _OnPlayerStreamIn_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&forplayerid);
  ((OnPlayerStreamIn_type)callback)(playerid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerStreamOut_type)(int playerid, int forplayerid);
static bool _OnPlayerStreamOut_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&forplayerid);
  ((OnPlayerStreamOut_type)callback)(playerid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleStreamIn_type)(int vehicleid, int forplayerid);
static bool _OnVehicleStreamIn_handler(AMX *amx, void *callback, cell *retval) {
  int vehicleid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void*)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void*)&forplayerid);
  ((OnVehicleStreamIn_type)callback)(vehicleid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnVehicleStreamOut_type)(int vehicleid, int forplayerid);
static bool _OnVehicleStreamOut_handler(AMX *amx, void *callback, cell *retval) {
  int vehicleid;
  int forplayerid;
  sampgdk_param_get_cell(amx, 0, (void*)&vehicleid);
  sampgdk_param_get_cell(amx, 1, (void*)&forplayerid);
  ((OnVehicleStreamOut_type)callback)(vehicleid, forplayerid);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnDialogResponse_type)(int playerid, int dialogid, int response, int listitem, const char * inputtext);
static bool _OnDialogResponse_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int dialogid;
  int response;
  int listitem;
  const char * inputtext;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&dialogid);
  sampgdk_param_get_cell(amx, 2, (void*)&response);
  sampgdk_param_get_cell(amx, 3, (void*)&listitem);
  sampgdk_param_get_string(amx, 4, (void*)&inputtext);
  retval_ = ((OnDialogResponse_type)callback)(playerid, dialogid, response, listitem, inputtext);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  free((void*)inputtext);
  return (retval_ != true);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerTakeDamage_type)(int playerid, int issuerid, float amount, int weaponid, int bodypart);
static bool _OnPlayerTakeDamage_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int issuerid;
  float amount;
  int weaponid;
  int bodypart;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&issuerid);
  sampgdk_param_get_float(amx, 2, (void*)&amount);
  sampgdk_param_get_cell(amx, 3, (void*)&weaponid);
  sampgdk_param_get_cell(amx, 4, (void*)&bodypart);
  retval_ = ((OnPlayerTakeDamage_type)callback)(playerid, issuerid, amount, weaponid, bodypart);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerGiveDamage_type)(int playerid, int damagedid, float amount, int weaponid, int bodypart);
static bool _OnPlayerGiveDamage_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int damagedid;
  float amount;
  int weaponid;
  int bodypart;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&damagedid);
  sampgdk_param_get_float(amx, 2, (void*)&amount);
  sampgdk_param_get_cell(amx, 3, (void*)&weaponid);
  sampgdk_param_get_cell(amx, 4, (void*)&bodypart);
  ((OnPlayerGiveDamage_type)callback)(playerid, damagedid, amount, weaponid, bodypart);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerClickMap_type)(int playerid, float fX, float fY, float fZ);
static bool _OnPlayerClickMap_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  float fX;
  float fY;
  float fZ;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_float(amx, 1, (void*)&fX);
  sampgdk_param_get_float(amx, 2, (void*)&fY);
  sampgdk_param_get_float(amx, 3, (void*)&fZ);
  ((OnPlayerClickMap_type)callback)(playerid, fX, fY, fZ);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerClickTextDraw_type)(int playerid, int clickedid);
static bool _OnPlayerClickTextDraw_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int clickedid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&clickedid);
  retval_ = ((OnPlayerClickTextDraw_type)callback)(playerid, clickedid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != true);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerClickPlayerTextDraw_type)(int playerid, int playertextid);
static bool _OnPlayerClickPlayerTextDraw_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int playertextid;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&playertextid);
  retval_ = ((OnPlayerClickPlayerTextDraw_type)callback)(playerid, playertextid);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != true);
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnIncomingConnection_type)(int playerid, const char * ip_address, int port);
static bool _OnIncomingConnection_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  const char * ip_address;
  int port;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_string(amx, 1, (void*)&ip_address);
  sampgdk_param_get_cell(amx, 2, (void*)&port);
  ((OnIncomingConnection_type)callback)(playerid, ip_address, port);
  free((void*)ip_address);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerClickPlayer_type)(int playerid, int clickedplayerid, int source);
static bool _OnPlayerClickPlayer_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int clickedplayerid;
  int source;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&clickedplayerid);
  sampgdk_param_get_cell(amx, 2, (void*)&source);
  ((OnPlayerClickPlayer_type)callback)(playerid, clickedplayerid, source);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEditObject_type)(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ);
static bool _OnPlayerEditObject_handler(AMX *amx, void *callback, cell *retval) {
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
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_bool(amx, 1, (void*)&playerobject);
  sampgdk_param_get_cell(amx, 2, (void*)&objectid);
  sampgdk_param_get_cell(amx, 3, (void*)&response);
  sampgdk_param_get_float(amx, 4, (void*)&fX);
  sampgdk_param_get_float(amx, 5, (void*)&fY);
  sampgdk_param_get_float(amx, 6, (void*)&fZ);
  sampgdk_param_get_float(amx, 7, (void*)&fRotX);
  sampgdk_param_get_float(amx, 8, (void*)&fRotY);
  sampgdk_param_get_float(amx, 9, (void*)&fRotZ);
  ((OnPlayerEditObject_type)callback)(playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerEditAttachedObject_type)(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ);
static bool _OnPlayerEditAttachedObject_handler(AMX *amx, void *callback, cell *retval) {
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
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&response);
  sampgdk_param_get_cell(amx, 2, (void*)&index);
  sampgdk_param_get_cell(amx, 3, (void*)&modelid);
  sampgdk_param_get_cell(amx, 4, (void*)&boneid);
  sampgdk_param_get_float(amx, 5, (void*)&fOffsetX);
  sampgdk_param_get_float(amx, 6, (void*)&fOffsetY);
  sampgdk_param_get_float(amx, 7, (void*)&fOffsetZ);
  sampgdk_param_get_float(amx, 8, (void*)&fRotX);
  sampgdk_param_get_float(amx, 9, (void*)&fRotY);
  sampgdk_param_get_float(amx, 10, (void*)&fRotZ);
  sampgdk_param_get_float(amx, 11, (void*)&fScaleX);
  sampgdk_param_get_float(amx, 12, (void*)&fScaleY);
  sampgdk_param_get_float(amx, 13, (void*)&fScaleZ);
  ((OnPlayerEditAttachedObject_type)callback)(playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerSelectObject_type)(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ);
static bool _OnPlayerSelectObject_handler(AMX *amx, void *callback, cell *retval) {
  int playerid;
  int type;
  int objectid;
  int modelid;
  float fX;
  float fY;
  float fZ;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&type);
  sampgdk_param_get_cell(amx, 2, (void*)&objectid);
  sampgdk_param_get_cell(amx, 3, (void*)&modelid);
  sampgdk_param_get_float(amx, 4, (void*)&fX);
  sampgdk_param_get_float(amx, 5, (void*)&fY);
  sampgdk_param_get_float(amx, 6, (void*)&fZ);
  ((OnPlayerSelectObject_type)callback)(playerid, type, objectid, modelid, fX, fY, fZ);
  return true;
}

typedef bool (SAMPGDK_CALLBACK_CALL *OnPlayerWeaponShot_type)(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ);
static bool _OnPlayerWeaponShot_handler(AMX *amx, void *callback, cell *retval) {
  bool retval_;
  int playerid;
  int weaponid;
  int hittype;
  int hitid;
  float fX;
  float fY;
  float fZ;
  sampgdk_param_get_cell(amx, 0, (void*)&playerid);
  sampgdk_param_get_cell(amx, 1, (void*)&weaponid);
  sampgdk_param_get_cell(amx, 2, (void*)&hittype);
  sampgdk_param_get_cell(amx, 3, (void*)&hitid);
  sampgdk_param_get_float(amx, 4, (void*)&fX);
  sampgdk_param_get_float(amx, 5, (void*)&fY);
  sampgdk_param_get_float(amx, 6, (void*)&fZ);
  retval_ = ((OnPlayerWeaponShot_type)callback)(playerid, weaponid, hittype, hitid, fX, fY, fZ);
  if (retval != NULL) {
    *retval = (cell)retval_;
  }
  return (retval_ != false);
}

static const struct sampgdk_callback _a_samp_callback_table[] = {
  {"OnVehicleStreamOut", _OnVehicleStreamOut_handler},
  {"OnVehicleStreamIn", _OnVehicleStreamIn_handler},
  {"OnVehicleSpawn", _OnVehicleSpawn_handler},
  {"OnVehicleRespray", _OnVehicleRespray_handler},
  {"OnVehiclePaintjob", _OnVehiclePaintjob_handler},
  {"OnVehicleMod", _OnVehicleMod_handler},
  {"OnVehicleDeath", _OnVehicleDeath_handler},
  {"OnVehicleDamageStatusUpdate", _OnVehicleDamageStatusUpdate_handler},
  {"OnUnoccupiedVehicleUpdate", _OnUnoccupiedVehicleUpdate_handler},
  {"OnRconLoginAttempt", _OnRconLoginAttempt_handler},
  {"OnRconCommand", _OnRconCommand_handler},
  {"OnPlayerWeaponShot", _OnPlayerWeaponShot_handler},
  {"OnPlayerUpdate", _OnPlayerUpdate_handler},
  {"OnPlayerText", _OnPlayerText_handler},
  {"OnPlayerTakeDamage", _OnPlayerTakeDamage_handler},
  {"OnPlayerStreamOut", _OnPlayerStreamOut_handler},
  {"OnPlayerStreamIn", _OnPlayerStreamIn_handler},
  {"OnPlayerStateChange", _OnPlayerStateChange_handler},
  {"OnPlayerSpawn", _OnPlayerSpawn_handler},
  {"OnPlayerSelectedMenuRow", _OnPlayerSelectedMenuRow_handler},
  {"OnPlayerSelectObject", _OnPlayerSelectObject_handler},
  {"OnPlayerRequestSpawn", _OnPlayerRequestSpawn_handler},
  {"OnPlayerRequestClass", _OnPlayerRequestClass_handler},
  {"OnPlayerPickUpPickup", _OnPlayerPickUpPickup_handler},
  {"OnPlayerObjectMoved", _OnPlayerObjectMoved_handler},
  {"OnPlayerLeaveRaceCheckpoint", _OnPlayerLeaveRaceCheckpoint_handler},
  {"OnPlayerLeaveCheckpoint", _OnPlayerLeaveCheckpoint_handler},
  {"OnPlayerKeyStateChange", _OnPlayerKeyStateChange_handler},
  {"OnPlayerInteriorChange", _OnPlayerInteriorChange_handler},
  {"OnPlayerGiveDamage", _OnPlayerGiveDamage_handler},
  {"OnPlayerExitedMenu", _OnPlayerExitedMenu_handler},
  {"OnPlayerExitVehicle", _OnPlayerExitVehicle_handler},
  {"OnPlayerEnterVehicle", _OnPlayerEnterVehicle_handler},
  {"OnPlayerEnterRaceCheckpoint", _OnPlayerEnterRaceCheckpoint_handler},
  {"OnPlayerEnterCheckpoint", _OnPlayerEnterCheckpoint_handler},
  {"OnPlayerEditObject", _OnPlayerEditObject_handler},
  {"OnPlayerEditAttachedObject", _OnPlayerEditAttachedObject_handler},
  {"OnPlayerDisconnect", _OnPlayerDisconnect_handler},
  {"OnPlayerDeath", _OnPlayerDeath_handler},
  {"OnPlayerConnect", _OnPlayerConnect_handler},
  {"OnPlayerCommandText", _OnPlayerCommandText_handler},
  {"OnPlayerClickTextDraw", _OnPlayerClickTextDraw_handler},
  {"OnPlayerClickPlayerTextDraw", _OnPlayerClickPlayerTextDraw_handler},
  {"OnPlayerClickPlayer", _OnPlayerClickPlayer_handler},
  {"OnPlayerClickMap", _OnPlayerClickMap_handler},
  {"OnObjectMoved", _OnObjectMoved_handler},
  {"OnIncomingConnection", _OnIncomingConnection_handler},
  {"OnGameModeInit", _OnGameModeInit_handler},
  {"OnGameModeExit", _OnGameModeExit_handler},
  {"OnEnterExitModShop", _OnEnterExitModShop_handler},
  {"OnDialogResponse", _OnDialogResponse_handler},
  {NULL, NULL}
};

SAMPGDK_MODULE_INIT(a_samp) {
  return sampgdk_callback_register_table(_a_samp_callback_table);
}
SAMPGDK_MODULE_CLEANUP(a_samp) {
  sampgdk_callback_unregister_table(_a_samp_callback_table);
}

/* Copyright (C) 2012-2014 Zeex
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

#include <sampgdk/sampgdk.h>

/* #include "internal/timer.h" */

SAMPGDK_NATIVE(int, SetTimer(int interval, bool repeat, TimerCallback callback,
                             void *param)) {
  return sampgdk_timer_set(interval, repeat, callback, param);
}

SAMPGDK_NATIVE(bool, KillTimer(int timerid)) {
  return sampgdk_timer_kill(timerid) >= 0;
}

#include <sampgdk/sampgdk.h>

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/likely.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(bool, IsValidVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsValidVehicle");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(float, GetVehicleDistanceFromPoint(int vehicleid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleDistanceFromPoint");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return amx_ctof(retval);
}

SAMPGDK_NATIVE(int, CreateVehicle(int vehicletype, float x, float y, float z, float rotation, int color1, int color2, int respawn_delay)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreateVehicle");
  }
  params[0] = 8 * sizeof(cell);
  params[1] = (cell)vehicletype;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  params[5] = amx_ftoc(rotation);
  params[6] = (cell)color1;
  params[7] = (cell)color2;
  params[8] = (cell)respawn_delay;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, DestroyVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DestroyVehicle");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsVehicleStreamedIn(int vehicleid, int forplayerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsVehicleStreamedIn");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)forplayerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetVehiclePos(int vehicleid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehiclePos");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehiclePos(int vehicleid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehiclePos");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleZAngle(int vehicleid, float * z_angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell z_angle_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleZAngle");
  }
  sampgdk_fakeamx_push(1, &z_angle_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = z_angle_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(z_angle_, z_angle);
  sampgdk_fakeamx_pop(z_angle_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleRotationQuat(int vehicleid, float * w, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell w_;
  cell x_;
  cell y_;
  cell z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleRotationQuat");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleZAngle(int vehicleid, float z_angle)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleZAngle");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(z_angle);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleParamsForPlayer(int vehicleid, int playerid, bool objective, bool doorslocked)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleParamsForPlayer");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)playerid;
  params[3] = (cell)objective;
  params[4] = (cell)doorslocked;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ManualVehicleEngineAndLights()) {
  static AMX_NATIVE native;
  cell retval;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ManualVehicleEngineAndLights");
  }
  retval = native(sampgdk_fakeamx_amx(), NULL);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleParamsEx(int vehicleid, bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleParamsEx");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleParamsEx(int vehicleid, bool * engine, bool * lights, bool * alarm, bool * doors, bool * bonnet, bool * boot, bool * objective)) {
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleParamsEx");
  }
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
  sampgdk_fakeamx_get_bool(engine_, engine);
  sampgdk_fakeamx_get_bool(lights_, lights);
  sampgdk_fakeamx_get_bool(alarm_, alarm);
  sampgdk_fakeamx_get_bool(doors_, doors);
  sampgdk_fakeamx_get_bool(bonnet_, bonnet);
  sampgdk_fakeamx_get_bool(boot_, boot);
  sampgdk_fakeamx_get_bool(objective_, objective);
  sampgdk_fakeamx_pop(objective_);
  sampgdk_fakeamx_pop(boot_);
  sampgdk_fakeamx_pop(bonnet_);
  sampgdk_fakeamx_pop(doors_);
  sampgdk_fakeamx_pop(alarm_);
  sampgdk_fakeamx_pop(lights_);
  sampgdk_fakeamx_pop(engine_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleToRespawn(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleToRespawn");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, LinkVehicleToInterior(int vehicleid, int interiorid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("LinkVehicleToInterior");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)interiorid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AddVehicleComponent(int vehicleid, int componentid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AddVehicleComponent");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)componentid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, RemoveVehicleComponent(int vehicleid, int componentid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("RemoveVehicleComponent");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)componentid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ChangeVehicleColor(int vehicleid, int color1, int color2)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[4];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ChangeVehicleColor");
  }
  params[0] = 3 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)color1;
  params[3] = (cell)color2;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, ChangeVehiclePaintjob(int vehicleid, int paintjobid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("ChangeVehiclePaintjob");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)paintjobid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleHealth(int vehicleid, float health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleHealth");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(health);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleHealth(int vehicleid, float * health)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  cell health_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleHealth");
  }
  sampgdk_fakeamx_push(1, &health_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = health_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_get_float(health_, health);
  sampgdk_fakeamx_pop(health_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AttachTrailerToVehicle(int trailerid, int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AttachTrailerToVehicle");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)trailerid;
  params[2] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DetachTrailerFromVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DetachTrailerFromVehicle");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsTrailerAttachedToVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsTrailerAttachedToVehicle");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetVehicleTrailer(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleTrailer");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleNumberPlate");
  }
  sampgdk_fakeamx_push_string(numberplate, NULL, &numberplate_);
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = numberplate_;
  retval = native(sampgdk_fakeamx_amx(), params);
  sampgdk_fakeamx_pop(numberplate_);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetVehicleModel(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleModel");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(int, GetVehicleComponentInSlot(int vehicleid, int slot)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleComponentInSlot");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleComponentType");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)component;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (int)(retval);
}

SAMPGDK_NATIVE(bool, RepairVehicle(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("RepairVehicle");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)vehicleid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleVelocity(int vehicleid, float * X, float * Y, float * Z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell X_;
  cell Y_;
  cell Z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleVelocity");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleVelocity(int vehicleid, float X, float Y, float Z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleVelocity");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(X);
  params[3] = amx_ftoc(Y);
  params[4] = amx_ftoc(Z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleAngularVelocity(int vehicleid, float X, float Y, float Z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleAngularVelocity");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = amx_ftoc(X);
  params[3] = amx_ftoc(Y);
  params[4] = amx_ftoc(Z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetVehicleDamageStatus(int vehicleid, int * panels, int * doors, int * lights, int * tires)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell panels_;
  cell doors_;
  cell lights_;
  cell tires_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleDamageStatus");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, UpdateVehicleDamageStatus(int vehicleid, int panels, int doors, int lights, int tires)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("UpdateVehicleDamageStatus");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)panels;
  params[3] = (cell)doors;
  params[4] = (cell)lights;
  params[5] = (cell)tires;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetVehicleVirtualWorld(int vehicleid, int worldid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetVehicleVirtualWorld");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)vehicleid;
  params[2] = (cell)worldid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, GetVehicleVirtualWorld(int vehicleid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleVirtualWorld");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetVehicleModelInfo");
  }
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
  return (bool)(retval);
}

static const struct sampgdk_callback _a_vehicles_callback_table[] = {
  {NULL, NULL}
};

SAMPGDK_MODULE_INIT(a_vehicles) {
  return sampgdk_callback_register_table(_a_vehicles_callback_table);
}
SAMPGDK_MODULE_CLEANUP(a_vehicles) {
  sampgdk_callback_unregister_table(_a_vehicles_callback_table);
}

#include <sampgdk/sampgdk.h>

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/likely.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(int, CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreateObject");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AttachObjectToVehicle");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AttachObjectToObject(int objectid, int attachtoid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AttachObjectToObject");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AttachObjectToPlayer(int objectid, int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AttachObjectToPlayer");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetObjectPos(int objectid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetObjectPos");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = amx_ftoc(x);
  params[3] = amx_ftoc(y);
  params[4] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetObjectPos(int objectid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell x_;
  cell y_;
  cell z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetObjectPos");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetObjectRot(int objectid, float rotX, float rotY, float rotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetObjectRot");
  }
  params[0] = 4 * sizeof(cell);
  params[1] = (cell)objectid;
  params[2] = amx_ftoc(rotX);
  params[3] = amx_ftoc(rotY);
  params[4] = amx_ftoc(rotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetObjectRot(int objectid, float * rotX, float * rotY, float * rotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[5];
  cell rotX_;
  cell rotY_;
  cell rotZ_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetObjectRot");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsValidObject(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsValidObject");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DestroyObject(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DestroyObject");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, MoveObject(int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[9];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("MoveObject");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("StopObject");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsObjectMoving(int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsObjectMoving");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, EditObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("EditObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, EditPlayerObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("EditPlayerObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SelectObject(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SelectObject");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, CancelEdit(int playerid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[2];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CancelEdit");
  }
  params[0] = 1 * sizeof(cell);
  params[1] = (cell)playerid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("CreatePlayerObject");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AttachPlayerObjectToPlayer");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("AttachPlayerObjectToVehicle");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerObjectPos");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = amx_ftoc(x);
  params[4] = amx_ftoc(y);
  params[5] = amx_ftoc(z);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerObjectPos(int playerid, int objectid, float * x, float * y, float * z)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell x_;
  cell y_;
  cell z_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerObjectPos");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerObjectRot");
  }
  params[0] = 5 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  params[3] = amx_ftoc(rotX);
  params[4] = amx_ftoc(rotY);
  params[5] = amx_ftoc(rotZ);
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, GetPlayerObjectRot(int playerid, int objectid, float * rotX, float * rotY, float * rotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell rotX_;
  cell rotY_;
  cell rotZ_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("GetPlayerObjectRot");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsValidPlayerObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsValidPlayerObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, DestroyPlayerObject(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("DestroyPlayerObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(int, MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed, float RotX, float RotY, float RotZ)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[10];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("MovePlayerObject");
  }
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
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("StopPlayerObject");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, IsPlayerObjectMoving(int playerid, int objectid)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[3];
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("IsPlayerObjectMoving");
  }
  params[0] = 2 * sizeof(cell);
  params[1] = (cell)playerid;
  params[2] = (cell)objectid;
  retval = native(sampgdk_fakeamx_amx(), params);
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetObjectMaterial(int objectid, int materialindex, int modelid, const char * txdname, const char * texturename, int materialcolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[7];
  cell txdname_;
  cell texturename_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetObjectMaterial");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectMaterial(int playerid, int objectid, int materialindex, int modelid, const char * txdname, const char * texturename, int materialcolor)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[8];
  cell txdname_;
  cell texturename_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerObjectMaterial");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetObjectMaterialText(int objectid, const char * text, int materialindex, int materialsize, const char * fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[11];
  cell text_;
  cell fontface_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetObjectMaterialText");
  }
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
  return (bool)(retval);
}

SAMPGDK_NATIVE(bool, SetPlayerObjectMaterialText(int playerid, int objectid, const char * text, int materialindex, int materialsize, const char * fontface, int fontsize, bool bold, int fontcolor, int backcolor, int textalignment)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[12];
  cell text_;
  cell fontface_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("SetPlayerObjectMaterialText");
  }
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
  return (bool)(retval);
}

static const struct sampgdk_callback _a_objects_callback_table[] = {
  {NULL, NULL}
};

SAMPGDK_MODULE_INIT(a_objects) {
  return sampgdk_callback_register_table(_a_objects_callback_table);
}
SAMPGDK_MODULE_CLEANUP(a_objects) {
  sampgdk_callback_unregister_table(_a_objects_callback_table);
}

#include <sampgdk/sampgdk.h>

/* #include "internal/callback.h" */
/* #include "internal/fakeamx.h" */
/* #include "internal/init.h" */
/* #include "internal/likely.h" */
/* #include "internal/native.h" */
/* #include "internal/param.h" */

SAMPGDK_NATIVE(bool, HTTP(int index, int type, const char * url, const char * data)) {
  static AMX_NATIVE native;
  cell retval;
  cell params[6];
  cell url_;
  cell data_;
  cell callback_;
  if (unlikely(native == NULL)) {
    native = sampgdk_native_find_warn_stub("HTTP");
  }
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
  return (bool)(retval);
}

typedef void (SAMPGDK_CALLBACK_CALL *OnHTTPResponse_type)(int index, int response_code, const char * data);
static bool _OnHTTPResponse_handler(AMX *amx, void *callback, cell *retval) {
  int index;
  int response_code;
  const char * data;
  sampgdk_param_get_cell(amx, 0, (void*)&index);
  sampgdk_param_get_cell(amx, 1, (void*)&response_code);
  sampgdk_param_get_string(amx, 2, (void*)&data);
  ((OnHTTPResponse_type)callback)(index, response_code, data);
  free((void*)data);
  return true;
}

static const struct sampgdk_callback _a_http_callback_table[] = {
  {"OnHTTPResponse", _OnHTTPResponse_handler},
  {NULL, NULL}
};

SAMPGDK_MODULE_INIT(a_http) {
  return sampgdk_callback_register_table(_a_http_callback_table);
}
SAMPGDK_MODULE_CLEANUP(a_http) {
  sampgdk_callback_unregister_table(_a_http_callback_table);
}

