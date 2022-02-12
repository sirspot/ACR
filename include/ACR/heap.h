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
/** \file heap.h

    public functions for access to a rudimentary heap

    The default heap size is 2mb but can changed by your
    project settings by defining ACR_CONFIG_HEAP_SIZE as
    the number of bytes to use for global heap data.

*/
#ifndef _ACR_HEAP_H_
#define _ACR_HEAP_H_

// included for ACR_HAS_MALLOC
#include "ACR/public/public_heap.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

// remove ACR_HAS_MALLOC if it is FALSE
#ifdef ACR_HAS_MALLOC
    #if ACR_HAS_MALLOC == ACR_BOOL_FALSE
        // the project settings must have defined ACR_CONFIG_NO_MALLOC,
        // but ACR/heap.h was included explictly in this program
        // so undefine everything before overriding the project
        // settings to use the heap
        #undef ACR_HAS_MALLOC
        #undef ACR_HEAP_IS_GLOBAL
        #undef ACR_MALLOC
        #undef ACR_FREE
        #undef ACR_REALLOC
    #endif
#endif

// define ACR_HAS_MALLOC, ACR_MALLOC(), ACR_FREE(), and ACR_REALLOC()
#ifndef ACR_HAS_MALLOC
    #define ACR_HAS_MALLOC ACR_BOOL_TRUE
    #define ACR_HEAP_IS_GLOBAL ACR_BOOL_TRUE
    #define ACR_MALLOC(s) ACR_GlobalHeapAlloc((ACR_Length_t)s)
    #define ACR_FREE(p) ACR_GlobalHeapFree(p)
    #define ACR_REALLOC(p,s) ACR_GlobalHeapRealloc(p, (ACR_Length_t)s)
#else
    // ACR_HAS_MALLOC is already ACR_BOOL_TRUE
    // so the macros do not need to be redefined.
    // To maintain the functionality of this module
    // the functions will instead, use the macros
    #undef ACR_HEAP_IS_GLOBAL
    #define ACR_HEAP_IS_GLOBAL ACR_BOOL_FALSE
#endif

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
extern "C" {                                              //
#endif                                                    //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/** allocate this many bytes on the global heap
    and return a pointer to the memory
    \param bytes the number of bytes to attempt to allocated
    \returns a pointer to the newly allocated memory or ACR_NULL on failure
*/
void* ACR_GlobalHeapAlloc(
    ACR_Length_t bytes);

/** free the specified memory of the global heap
    \param ptr existing allocated memory pointer
*/
void ACR_GlobalHeapFree(
    void* ptr);

/** reallocate the specified memory of the global heap
    to make the amount allocated larger or smaller.
    \param ptr existing allocated memory pointer
    \param bytes new size desired
    \returns either a pointer to the newly allocated memory and ptr is no longer valid
             or on failure ACR_NULL and ptr remains valid but at its original allocation size.    
*/
void* ACR_GlobalHeapRealloc(
    void* ptr,
    ACR_Length_t bytes);

#if ACR_HEAP_IS_GLOBAL == ACR_BOOL_TRUE

/** non-standard but very fast function to free all
    allocated global heap memory.
*/
void ACR_GlobalHeapFreeAll(void);

#endif

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
