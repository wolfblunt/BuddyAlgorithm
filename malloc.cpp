#include "buddyAlgorithmHeader.h"

using namespace std;
unsigned int header_size  = sizeof(MemoryHeaderStruct);
void *genHeapAddr;
size_t Allocation_Size;

void *buddy_malloc(int allocSize)
{
    MemoryHeaderStruct *hdr;
    int blockSize = MIN_BLOCK;// min blok = 8
    int order = 0;//

    while(blockSize < allocSize)
    {
        order++;
        blockSize *= 2;
    }
    
    pthread_mutex_lock(&malloc_lock);  

    if (arena.checkFreeOrderList[order]) 
    {
        hdr = arena.checkFreeOrderList[order];
        // popFront(order);

        MemoryHeaderStruct *frnt_hdr = arena.checkFreeOrderList[order];
        arena.checkFreeOrderList[order] = frnt_hdr->nextPointer;
        frnt_hdr->nextPointer = NULL;
        frnt_hdr->nextPointer = 0;

        pthread_mutex_unlock(&malloc_lock);
        return hdr;
    }

    while (++order <= MAX_ORDER)   //max_order = 8
    {
        if (arena.checkFreeOrderList[order]) 
        {
            MemoryHeaderStruct *blockA = arena.checkFreeOrderList[order];
            blockA->size /= 2;
            blockA->isBlockfree = 1;


            MemoryHeaderStruct *frnt2_hdr = arena.checkFreeOrderList[order];
            arena.checkFreeOrderList[order] = frnt2_hdr->nextPointer;
            frnt2_hdr->nextPointer = NULL;
            frnt2_hdr->nextPointer = 0;

            MemoryHeaderStruct *blockB = (MemoryHeaderStruct *)((char *)blockA + blockA->size);
            blockB->size = blockA->size;
            blockB->isBlockfree = 1;

            blockA->nextPointer = blockB;
            blockB->nextPointer = NULL;
            arena.checkFreeOrderList[order - 1] = blockA;
        
            pthread_mutex_unlock(&malloc_lock);
            return buddy_malloc(allocSize);
        }
    }

  
  hdr = (MemoryHeaderStruct *)sbrk(BUDDY_SIZE);//allocated the memory to buddy in HEAP of 2048 = 2^
  if (hdr == (void *)-1) 
  {//checks if any  error was retruned
    return hdr;
  }
  
  
  
  hdr->isBlockfree = 1;
  hdr->nextPointer = NULL;
  hdr->size = BUDDY_SIZE;
  arena.checkFreeOrderList[MAX_ORDER] = hdr;
  pthread_mutex_unlock(&malloc_lock);
  infoLog("A memory of "+to_string(hdr->size)+ " bytes");
  return buddy_malloc(allocSize);
}


void *malloc(size_t size)
{
    infoLog("Size need to allocate : "+to_string(size)+ " bytes");
    cout<<"header_size : "<<header_size<<endl;
    Allocation_Size = size + header_size;

    if (Allocation_Size < size_t(header_size +1)) 
    {
        return NULL;// returns NULL when zero size is rovided as input
    } 
    if (Allocation_Size < size_t(BUDDY_SIZE+1)) 
    {//Buddy size  = 2048
        genHeapAddr = buddy_malloc(Allocation_Size);
    } 
    else if (Allocation_Size > BUDDY_SIZE)
    {
        return NULL;
    }
    MemoryHeaderStruct *hdr = (MemoryHeaderStruct *)genHeapAddr;
    hdr->size = Allocation_Size;

    if (arena.heap == NULL)
    {
      arena.heap = genHeapAddr;
    }
    void* t = (void *)((unsigned int*)genHeapAddr + header_size);
    return t;
}




