#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
using namespace std;

#define MIN_BLOCK 8
#define MAX_ORDER 8
#define BUDDY_SIZE 2048

struct MemoryHeaderStruct {  // MallocHeader -> MemoryHeaderStruct
  size_t size;
  struct MemoryHeaderStruct *nextPointer;   // next -> nextPointer
  bool isBlockfree;         // is_free - isBlockfree
  void* headerAddress;       // header_addr - headerAddress
};

struct MemoryArena {  // MemArena -> MemoryArena
  void *heap;
  struct MemoryHeaderStruct *checkFreeOrderList[MAX_ORDER + 1];   // freeList
  /* order: 0, 1,  2,  ..., 8
     block: 8, 16, 32, ..., 2048 */
};

extern MemoryArena arena;
extern string logFileName;
extern pthread_mutex_t malloc_lock;     // mallocMutexLock -> malloc_lock

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
void *memalign(size_t alignment, size_t size);
int posix_memalign(void **memptr, size_t alignment, size_t size);
void clearLog();
void debugLog(const string &);
void infoLog(const string &);

// #define MALLOC_HEADER_SIZE (sizeof(MemoryHeaderStruct))
// #define MALLOC_BASE(addr) ((void *)((char *)addr - MALLOC_HEADER_SIZE))