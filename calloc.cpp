#include "buddyAlgorithmHeader.h"

void *calloc(size_t nmemb, size_t size)
{
    int totalSize = nmemb * size;
    void* memoryReturn = malloc(totalSize);
    if (memoryReturn!=NULL)
    {
        if (memoryReturn!=NULL)
        {
            memset(memoryReturn, 0, totalSize);
        }
    }
    return memoryReturn;
}