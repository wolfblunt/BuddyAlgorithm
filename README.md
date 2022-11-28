# Overview
 A malloc library that provides the following dynamic memory allocation routines (as defined in man 3 malloc):

- void *malloc(size_t size);
- void free(void *ptr);
- void *calloc(size_t nmemb, size_t size);
- void *realloc(void *ptr, size_t size);
- int posix_memalign(void **memptr, size_t alignment, size_t size);
- void *memalign(size_t alignment, size_t size);
- struct mallinfo mallinfo();
- void malloc_stats(void);

# How to run
- Existing tests
  - make
  - ./test1
  - ./t-test1
