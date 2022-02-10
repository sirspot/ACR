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
/** \file private_heap.h

    private functions for access to ACR_Heap_t

*/
#ifndef _ACR_PRIVATE_HEAP_H_
#define _ACR_PRIVATE_HEAP_H_

#include "ACR/heap.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

// included for ACR_Byte_t and ACR_Flags_t
#include "ACR/public/public_bytes_and_flags.h"

// included for ACR_Count_t and ACR_ZERO_COUNT
#include "ACR/public/public_count.h"

/** heap data structure
*/
typedef struct ACR_HeapObj_s
{
    ACR_Byte_t* m_Heap;
    ACR_Length_t m_HeapLength;
    ACR_Length_t m_NextFreePos;
    ACR_Count_t m_HeaderCount;
    ACR_Count_t m_FreeCount;
} ACR_HeapObj_t;

/** heap header data structure placed
    in heap memory before each allocation
*/
typedef struct ACR_HeapHeader_s
{
    ACR_Length_t m_Bytes;
    ACR_Flags_t m_Flags;
} ACR_HeapHeader_t;

/** ACR_HeapHeader_t m_Flags sets this to indicate the header has been set
*/
#define ACR_HEAP_FLAG_HEADER    ACR_FLAG_ONE

/** ACR_HeapHeader_t m_Flags sets this to indicate the memory is in use
*/
#define ACR_HEAP_FLAG_ALLOCATED ACR_FLAG_TWO

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
extern "C" {                                              //
#endif                                                    //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS
//
////////////////////////////////////////////////////////////

/** prepare a heap
    \param me the heap
*/
void ACR_HeapInit(
	ACR_HeapObj_t* me,
    void* ptr,
    ACR_Length_t length);

/** deinit a heap
    \param me the heap
*/
void ACR_HeapDeInit(
	ACR_HeapObj_t* me);

/** allocate this many bytes on the heap
    and return a pointer to the memory
    \param me the heap
    \param bytes the number of bytes to attempt to allocated
    \returns a pointer to the newly allocated memory or ACR_NULL on failure
*/
void* ACR_HeapAlloc(
    ACR_HeapObj_t* me,
    ACR_Length_t bytes);

/** free the specified memory of the heap
    \param me the heap
    \param ptr existing allocated memory pointer
*/
void ACR_HeapFree(
    ACR_HeapObj_t* me,
    void* ptr);

/** reallocate the specified memory of the heap
    to make the amount allocated larger or smaller.
    \param me the heap
    \param ptr existing allocated memory pointer
    \param bytes new size desired
    \returns either a pointer to the newly allocated memory and ptr is no longer valid
             or on failure ACR_NULL and ptr remains valid but at its original allocation size.    
*/
void* ACR_HeapRealloc(
    ACR_HeapObj_t* me,
    void* ptr,
    ACR_Length_t bytes);

/** non-standard but very fast function to free all
    allocated heap memory.
    \param me the heap
*/
void ACR_HeapFreeAll(
    ACR_HeapObj_t* me);

/** get the maximum heap space available to the next ACR_HeapAlloc() call
    \param me the heap
    \returns the number of unused bytes of heap memory
*/
ACR_Length_t ACR_HeapAvailable(
    ACR_HeapObj_t* me);

/** get the pointer position within the heap
    \param me the heap
    \param ptr the pointer
    \param pos stores the position value of the pointer as the
               number of bytes from the start of heap memory
    \returns ACR_BOOL_TRUE if the pointer is within the heap memory
*/
ACR_Bool_t ACR_HeapPointerPos(
    ACR_HeapObj_t* me,
    const void* ptr,
    ACR_Length_t* pos);

/** find the position of an existing header
    with the min number of bytes available
    that has been freed
    \param me the heap
    \param minBytes the minimum number of free bytes to find
                    Note: set to zero to find the first
                          freed memory
    \param pos stores the position of the header as the
               number of bytes from the start of heap memory
*/
ACR_Bool_t ACR_HeapFindFree(
    ACR_HeapObj_t* me,
    ACR_Length_t minBytes,
    ACR_Length_t* pos);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
