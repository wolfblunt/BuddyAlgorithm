#include "buddyAlgorithmHeader.h"

int powerOfTwo(size_t size)
{
	while (size > 1) {
		if (size % 2 != 0) {
			return -1;
		}
		size = size / 2;
	}
	return 0;
}

void *round_up(void *addr, size_t alignment)
{
    return (void *)((((unsigned long)addr + sizeof(unsigned long)) & ~(unsigned long)(alignment - 1)) + alignment);
}

// The obsolete function memalign() allocates size bytes and returns a pointer to the allocated memory.
// The memory address will be a multiple of alignment, which must be a power of two.
void *memalign(size_t alignment, size_t size)
{
    if(size == 0 || powerOfTwo(alignment) != 0)
    {
        // *memorypointer = NULL;
        return (void *)EINVAL;
    }
    void *ptr = malloc(size + alignment + sizeof(MemoryHeaderStruct));
    if (ptr)
    {
        void *ret = round_up(ptr, alignment);
        ((MemoryHeaderStruct *)((void *)((char *)ret - sizeof(MemoryHeaderStruct))))->headerAddress = ptr;
        return ret;
    }
    else
    {
        return NULL;
    }
}
