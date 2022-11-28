#include "buddyAlgorithmHeader.h"
#define struct_size sizeof(MemoryHeaderStruct)

void * fun_ptr(void * ptr)
{
  return (void *)((char *) ptr - struct_size) ;
}


void *realloc(void *ptr, size_t size)
{
  if (ptr == NULL)
    return malloc(size);
    
  void * pointer = fun_ptr(ptr); //((void *)((char *)ptr - sizeof(MemoryHeaderStruct)));
  MemoryHeaderStruct *headr = (MemoryHeaderStruct *) pointer;
  if (headr->size < size)
  {
  void *array_addr = malloc(size);
  memcpy((char *)array_addr, ptr, headr->size);
  free(ptr);
  return array_addr;
  }
  else{
    return ptr;
  }

  

  
}


