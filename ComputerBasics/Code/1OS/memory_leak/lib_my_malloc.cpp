// #define _GNU_SOURCE
#include <dlfcn.h>
#include <execinfo.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static void *(*real_malloc)(size_t) = NULL;
static void *(*real_calloc)(size_t, size_t) = NULL;
static void *(*real_realloc)(void *, size_t) = NULL;
static void (*real_free)(void *) = NULL;

/*init 函数被标记为 __attribute__((constructor))
 * 属性，这表示它会在库加载时自动调用*/
static void __attribute__((constructor)) init(void) {
  /* dlfcn 库的 dlsym 函数获取原始 malloc 和 free 函数的地址 */
  real_malloc = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
  real_calloc = (void *(*)(size_t, size_t))dlsym(RTLD_NEXT, "calloc");
  real_realloc = (void *(*)(void *, size_t))dlsym(RTLD_NEXT, "realloc");
  real_free = (void (*)(void *))dlsym(RTLD_NEXT, "free");
}

void *malloc(size_t len) {
  static __thread int no_hook = 0;
  /*hook 是否启用 */
  if (no_hook) {
    return (*real_malloc)(len);
  }
  /*__builtin_return_address(0) 获取调用者的地址 */
  void *caller = (void *)(long)__builtin_return_address(0);
  /*将 no_hook 设置为1，以在 printf 调用中禁用进一步的挂钩，防止对 malloc
   * 的递归调用和潜在的无限循环。*/
  no_hook = 1;
  printf("malloc call  from %p,len:%zu\n", caller,
         len);  // printf call malloc internally
  no_hook = 0;

  void *ret = (*real_malloc)(len);
  return ret;
}

void *calloc(size_t len, size_t size) {
  static __thread int no_hook = 0;
  /*hook 是否启用 */
  if (no_hook) {
    return (*real_calloc)(len, size);
  }
  /*__builtin_return_address(0) 获取调用者的地址 */
  void *caller = (void *)(long)__builtin_return_address(0);
  /*将 no_hook 设置为1，以在 printf 调用中禁用进一步的挂钩，防止对 malloc
   * 的递归调用和潜在的无限循环。*/
  no_hook = 1;
  printf("calloc call  from %p,len:%zu,size:%zu\n", caller, len,
         size);  // printf call malloc internally
  no_hook = 0;

  void *ret = (*real_calloc)(len, size);
  return ret;
}

void *realloc(void *ptr, size_t size) {
  static __thread int no_hook = 0;
  /*hook 是否启用 */
  if (no_hook) {
    return (*real_realloc)(ptr, size);
  }
  /*__builtin_return_address(0) 获取调用者的地址 */
  void *caller = (void *)(long)__builtin_return_address(0);
  /*将 no_hook 设置为1，以在 printf 调用中禁用进一步的挂钩，防止对 malloc
   * 的递归调用和潜在的无限循环。*/
  no_hook = 1;
  printf("realloc call  from %p,ptr:%p,size:%zu\n", caller, ptr,
         size);  // printf call malloc internally
  no_hook = 0;

  void *ret = (*real_realloc)(ptr, size);
  return ret;
}

void free(void *ptr) {
  void *caller = (void *)(long)__builtin_return_address(0);
  printf("free call %p from %p\n", ptr, caller);
  (*real_free)(ptr);
  
}