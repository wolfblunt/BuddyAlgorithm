#include "buddyAlgorithmHeader.h"

MemoryArena arena;

#define MALLOC_HEADER_SIZE (sizeof(MemoryHeaderStruct))
#define MALLOC_BASE(addr) ((void *)((char *)addr - MALLOC_HEADER_SIZE))

void pushFront(int index, MemoryHeaderStruct *blck) 
{
  blck->nextPointer = arena.checkFreeOrderList[index];
  arena.checkFreeOrderList[index] = blck;
  blck->isBlockfree = 1;
}
void mergememory(MemoryHeaderStruct *blck)
{
    int index;
    index = log2(blck->size/MIN_BLOCK);
    if(index <= MAX_ORDER - 1) 
    {
       
    }
    else{
         pushFront(index, blck);
    }
}
void free(void *pointer)
{   
    if(pointer!=NULL)
    {
        MemoryHeaderStruct *h = (MemoryHeaderStruct *)MALLOC_BASE(pointer);
        if (h->headerAddress != NULL) 
            return free(h->headerAddress);
        if(h->size < BUDDY_SIZE + 1)
        {
            if(h->isBlockfree == false)
            {
                h->nextPointer = NULL;
                h->isBlockfree = true;
                pthread_mutex_lock(&malloc_lock);
                mergememory(h);
                pthread_mutex_unlock(&malloc_lock);
            }
        }
    }
    else{
        return;
    }
}