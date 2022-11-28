#include "buddyAlgorithmHeader.h"

int powerOfTwoPosix(size_t size)
{
	while (size > 1) {
		if (size % 2 != 0) {
			return -1;
		}
		size = size / 2;
	}
	return 0;
}

int posix_memalign(void **memorypointer, size_t alignment, size_t size) 
{
    if(size == 0 || powerOfTwoPosix(alignment) != 0)
    {
        *memorypointer = NULL;
        return -1;
    }
    void *ret = memalign(alignment, size);
    if (ret == NULL) 
      return errno;
    else 
    {
      *memorypointer = ret;
      return 0;
    } 
}