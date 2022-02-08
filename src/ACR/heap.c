/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2022 Adam C. Rosenberg

    Please read LICENSE before using this code

    Please read README.md for instructions on including
    this code in your project and where to find examples

    If you contribute to this code, Please add your name
    and email address to the AUTHORS list below so that
    we know who to thank!

    AUTHORS

    Adam Rosenberg <adam@sirspot.com>

    LICENSE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.


    ******************************************************

*/
/** \file heap.c

    public and private functions for access to a rudimentary heap

*/
#include "ACR/private/private_heap.h"

#ifndef ACR_CONFIG_HEAP_SIZE
    // the project settings did not define a heap size.
    // configure the heap size for 2MB
    #define ACR_CONFIG_HEAP_SIZE (2*1024)
#endif

// included for ACR_Bool_t
#include "ACR/public/public_bool.h"

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

#if ACR_HEAP_IS_GLOBAL == ACR_BOOL_FALSE

/**********************************************************/
void* ACR_GlobalHeapAlloc(
    ACR_Length_t bytes)
{
    return ACR_MALLOC(bytes);
}

/**********************************************************/
void ACR_GlobalHeapFree(
    void* ptr)
{
    ACR_FREE(ptr);
}

/**********************************************************/
void* ACR_GlobalHeapRealloc(
    void* ptr,
    ACR_Length_t bytes)
{
    return ACR_REALLOC(ptr, bytes);
}

#endif // #if ACR_HEAP_IS_GLOBAL == ACR_BOOL_FALSE

#if ACR_HEAP_IS_GLOBAL == ACR_BOOL_TRUE

/** global heap memory
*/
ACR_Byte_t g_ACR_HeapMemory[ACR_CONFIG_HEAP_SIZE];

/** global heap
*/
ACR_HeapObj_t g_ACR_Heap = {(ACR_Byte_t*)&g_ACR_HeapMemory, ACR_CONFIG_HEAP_SIZE, 0, ACR_ZERO_COUNT, ACR_ZERO_COUNT};

/**********************************************************/
void* ACR_GlobalHeapAlloc(
    ACR_Length_t bytes)
{
    return ACR_HeapAlloc(&g_ACR_Heap, bytes);
}

/**********************************************************/
void ACR_GlobalHeapFree(
    void* ptr)
{
    ACR_HeapFree(&g_ACR_Heap, ptr);
}

/**********************************************************/
void* ACR_GlobalHeapRealloc(
    void* ptr,
    ACR_Length_t bytes)
{
    return ACR_HeapRealloc(&g_ACR_Heap, ptr, bytes);
}

/**********************************************************/
void ACR_GlobalHeapFreeAll()
{
    ACR_HeapFreeAll(&g_ACR_Heap);
}

#endif // #if ACR_HEAP_IS_GLOBAL == ACR_BOOL_TRUE

////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
void ACR_HeapInit(
	ACR_HeapObj_t* me,
    void* ptr,
    ACR_Length_t length)
{
    me->m_Heap = ptr;
    me->m_HeapLength = length;
    me->m_NextFreePos = 0;
    me->m_HeaderCount = ACR_ZERO_COUNT;
    me->m_FreeCount = ACR_ZERO_COUNT;
}

/**********************************************************/
void ACR_HeapDeInit(
	ACR_HeapObj_t* me)
{
    me->m_Heap = ACR_NULL;
    me->m_HeapLength = ACR_ZERO_LENGTH;
    me->m_NextFreePos = 0;
    me->m_HeaderCount = ACR_ZERO_COUNT;
    me->m_FreeCount = ACR_ZERO_COUNT;
}

/**********************************************************/
void* ACR_HeapAlloc(
    ACR_HeapObj_t* me,
    ACR_Length_t bytes)
{
    void* ptr = ACR_NULL;
    ACR_Length_t headerPos;
    if(ACR_HeapFindFree(me, bytes, &headerPos))
    {
        // found existing memory that can be reused
        ACR_HeapHeader_t* headerPtr = (ACR_HeapHeader_t*)&me->m_Heap[headerPos];
        ACR_ADD_FLAGS(headerPtr->m_Flags, ACR_HEAP_FLAG_ALLOCATED);
        me->m_FreeCount--;
        // get the new address
        ptr = &me->m_Heap[headerPos + sizeof(ACR_HeapHeader_t)];
    }
    else
    {
        // must allocate more memory
        ACR_Length_t available = ACR_HeapAvailable(me);
        if(bytes <= available)
        {
            // store heap header data before the allocated memory
            ACR_HeapHeader_t* headerPtr = (ACR_HeapHeader_t*)&me->m_Heap[me->m_NextFreePos];
            headerPtr->m_Bytes = bytes;
            ACR_ADD_FLAGS(headerPtr->m_Flags, ACR_HEAP_FLAG_HEADER | ACR_HEAP_FLAG_ALLOCATED);
            me->m_NextFreePos += sizeof(ACR_HeapHeader_t);
            // get the new address and select the next free position
            ptr = &me->m_Heap[me->m_NextFreePos];
            me->m_NextFreePos += bytes;
            me->m_HeaderCount++;
        }
    }
    return ptr;
}

/**********************************************************/
void ACR_HeapFree(
    ACR_HeapObj_t* me,
    void* ptr)
{
    ACR_Length_t ptrPos;
    if(ACR_HeapPointerPos(me, ptr, &ptrPos))
    {
        ACR_Length_t headerPos = (ptrPos - sizeof(ACR_HeapHeader_t));
        ACR_HeapHeader_t* headerPtr = (ACR_HeapHeader_t*)&me->m_Heap[headerPos];
        if(ACR_HAS_FLAG(headerPtr->m_Flags, ACR_HEAP_FLAG_HEADER))
        {
            if(ACR_HAS_FLAG(headerPtr->m_Flags, ACR_HEAP_FLAG_ALLOCATED))
            {
                ACR_REMOVE_FLAGS(headerPtr->m_Flags, ACR_HEAP_FLAG_ALLOCATED);
                me->m_FreeCount++;
            }
            else
            {
                // already freed
            }
        }
        else
        {
            // not a valid heap memory pointer
        }
    }
    else
    {
        // pointer is not in this heap
    }
}

/**********************************************************/
void* ACR_HeapRealloc(
    ACR_HeapObj_t* me,
    void* ptr,
    ACR_Length_t bytes)
{
    void* newPtr = ACR_NULL;
    ACR_Length_t ptrPos;
    if(ACR_HeapPointerPos(me, ptr, &ptrPos))
    {
        ACR_Length_t headerPos = (ptrPos - sizeof(ACR_HeapHeader_t));
        ACR_HeapHeader_t* headerPtr = (ACR_HeapHeader_t*)&me->m_Heap[headerPos];
        if(bytes <= headerPtr->m_Bytes)
        {
            // plenty of space already allocated
            newPtr = ptr;
        }
        else
        {
            // this is a very rudimentary heap so there is no way
            // to realloc anything larger than currently allocated.
            // in theory, a search could be performed to see if
            // the next N headers were free and could be merged
            // into the requested reallocation. But, instead,
            // just try to allocate like normal and copy
            // the existing data to the new location
            newPtr = ACR_HeapAlloc(me, bytes);
            if(newPtr)
            {
                ACR_MEMCPY(newPtr, ptr, headerPtr->m_Bytes);
                ACR_HeapFree(me, ptr);
            }
            else
            {
                // failed to realloc
            }
        }
    }
    else
    {
        // invalid pointer cannot
        // be reallocated
    }

    return newPtr;
}

/**********************************************************/
void ACR_HeapFreeAll(
    ACR_HeapObj_t* me)
{
    me->m_NextFreePos = 0;
    me->m_HeaderCount = ACR_ZERO_COUNT;
    me->m_FreeCount = ACR_ZERO_COUNT;
}

/**********************************************************/
ACR_Length_t ACR_HeapAvailable(
    ACR_HeapObj_t* me)
{
    ACR_Length_t result = 0;
    ACR_Length_t maxHeapAvailable = (me->m_HeapLength - sizeof(ACR_HeapHeader_t));
    if(maxHeapAvailable > me->m_NextFreePos)
    {
        result = (maxHeapAvailable - me->m_NextFreePos);
    }
    return result;
}

/**********************************************************/
ACR_Bool_t ACR_HeapPointerPos(
    ACR_HeapObj_t* me,
    const void* ptr,
    ACR_Length_t* pos)
{
    ACR_Bool_t result = ACR_BOOL_FALSE;
    if(me->m_HeapLength > sizeof(ACR_HeapHeader_t))
    {
        if(ptr)
        {
            ACR_PointerValue_t ptrAddr = (ACR_PointerValue_t)ptr;
            ACR_PointerValue_t heapAddr = (ACR_PointerValue_t)me->m_Heap;
            ACR_PointerValue_t minHeapAddr = (heapAddr + sizeof(ACR_HeapHeader_t));
            if(ptrAddr >= minHeapAddr)
            {
                ACR_PointerValue_t heapEndAddr = (heapAddr + me->m_HeapLength);
                if(ptrAddr < heapEndAddr)
                {
                    if(pos)
                    {
                        (*pos) = (ACR_Length_t)(ptrAddr - heapAddr);
                    }
                    result = ACR_BOOL_TRUE;
                }
                else
                {
                    // pointer address is too high
                }
            }
            else
            {
                // pointer address is too low
            }
        }
        else
        {
            // null pointer
        }
    }
    else
    {
        // no heap available
    }
    return result;
}

/**********************************************************/
ACR_Bool_t ACR_HeapFindFree(
    ACR_HeapObj_t* me,
    ACR_Length_t minBytes,
    ACR_Length_t* pos)
{
    ACR_Bool_t result = ACR_BOOL_FALSE;
    ACR_Length_t heapPos = 0;
    ACR_Count_t currentHeader = 0;
    ACR_Count_t freeFound = 0;
    while((currentHeader < me->m_HeaderCount) &&
          (freeFound < me->m_FreeCount))
    {
        ACR_HeapHeader_t* headerPtr = (ACR_HeapHeader_t*)&me->m_Heap[heapPos];
        if(ACR_HAS_FLAG(headerPtr->m_Flags, ACR_HEAP_FLAG_HEADER))
        {
            if(ACR_HAS_FLAG(headerPtr->m_Flags, ACR_HEAP_FLAG_ALLOCATED))
            {
                // this memory is in use.
                heapPos += headerPtr->m_Bytes;
            }
            else
            {
                freeFound++;
                if(headerPtr->m_Bytes >= minBytes)
                {
                    // found free memory with enough space
                    // break out of this loop
                    result = ACR_BOOL_TRUE;
                    if(pos)
                    {
                        (*pos) = heapPos;
                    }
                    break;
                }
                else
                {
                    // this memory is too small
                    heapPos += headerPtr->m_Bytes;
                }
            }
        }
        else
        {
            // sanity check failed.
            // the heap is corrupt
            /// \todo what is the best way to handle this?
            break;
        }
        currentHeader++;
    }

    return result;
}
