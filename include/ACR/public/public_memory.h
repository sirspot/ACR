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

/** \file public_memory.h
 
    This header provides basic memory length types and the
    ability to set, copy, and clear memory.
    It is included automatically with public.h

*/
#ifndef _ACR_PUBLIC_MEMORY_H_
#define _ACR_PUBLIC_MEMORY_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public/public_bool.h"

/** represents an empty value.
    use this instead of 0 to clearly indicate the value
    is being used to identify an empty value

    for memory init:

        char data[64];
        ACR_MEMSET(data, ACR_EMPTY_VALUE, sizeof(data));
        
    for variable init:

        int selected = ACR_EMPTY_VALUE;

    for comparison:

        if(data[0] == ACR_EMPTY_VALUE)
        {
            // nothing has been written to the data
        }

        if(selected == ACR_EMPTY_VALUE)
        {
            // nothing has been selected
        }

*/
#define ACR_EMPTY_VALUE 0

#ifdef ACR_CONFIG_NO_64BIT
#define ACR_USE_64BIT ACR_BOOL_FALSE
#else
/// \todo is there a way to determine, at compile time, whether or not the platform uses 64bit addresses?
#define ACR_USE_64BIT ACR_BOOL_TRUE
#endif // #ifndef ACR_CONFIG_NO_64BIT

/** type for a typical length such as the size of a file or
    the size of an area of memory
	\see ACR_MAX_LENGTH for the maximum value that can be
	stored by this data type
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
typedef unsigned long long ACR_Length_t;
#else
// 32bit
typedef unsigned long ACR_Length_t;
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

/** represents zero length.
	use this instead of 0 to clearly indicate the value
	is being used for a length

	for variable init:

		ACR_Length_t length = ACR_ZERO_LENGTH;

	for comparison:

		if(length == ACR_ZERO_LENGTH)
		{
			// length is zero
		}

*/
#define ACR_ZERO_LENGTH 0

/** max value that can be stored by the ACR_Length_t type
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
#define ACR_MAX_LENGTH 18446744073709551615ULL // hex value 0xFFFFFFFFFFFFFFFF
#else
// 32bit
#define ACR_MAX_LENGTH 4294967295UL // hex value 0xFFFFFFFF
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

/*
    ### New to C? ###

    Q: What does memset do?
    A: memset is a function that changes an entire
        area of memory to be a single value. It is
        typically used to set a region of memory
        that has unknown or undesired values to all
        zeros so that the values of all memory in
        that region are known and valid.

*/
#ifndef ACR_CONFIG_NO_LIBC

    // included for memset()
    #include <string.h>
    #define ACR_MEMSET(p,v,s) memset(p,v,(size_t)s)

#else

    /** ACR_CONFIG_NO_LIBC is defined so this is a 
        generic (slow) memset but gets the job done
    */
    #define ACR_MEMSET(p,v,s) \
    {\
        char* c=(char*)p;\
        char d=(char)v;\
        ACR_Length_t l=(ACR_Length_t)s;\
        while(l>0)\
        {\
            (*c)=d;\
            c++;\
            l--;\
        }\
    }

#endif // #ifndef ACR_CONFIG_NO_LIBC

/** clears a region of memory
    \param p a pointer to the memory to clear
    \param s the number of bytes of data to clear
*/
#define ACR_CLEAR_MEMORY(p,s) if(p){ACR_MEMSET(p,ACR_EMPTY_VALUE,s);}

/*
    ### New to C? ###

    Q: What does memcpy do?
    A: memcpy is a function that copies memory from
        one address to another. It is generally best
        to avoid copying memory unless necessary since
        it can be a relatively slow process. What this
        means is that if there is way to work with the
        data without copying it first, then that is
        preferred over making a copy.

*/
#ifndef ACR_CONFIG_NO_LIBC

    // included for memcpy()
    #include <string.h>
    #define ACR_MEMCPY(d,s,l) memcpy(d,s,(size_t)l);

#else

    /** ACR_CONFIG_NO_LIBC is defined so this is a 
        generic (slow) memcpy but gets the job done
    */
    #define ACR_MEMCPY(d,s,l) \
    {\
        char* c=(char*)d;\
        char* v=(char*)s;\
        ACR_Length_t n=(ACR_Length_t)l;\
        while(n>0)\
        {\
            (*c)=(*v);\
            c++;\
            v++;\
            n--;\
        }\
    }

#endif // #ifndef ACR_CONFIG_NO_LIBC

/** represents a null pointer.
    use this instead of 0 to clearly indicate the value
    is being used for a null pointer

    for variable init:

        char* ptr = ACR_NULL;

    for comparison:
    
        if(ptr == ACR_NULL)
        {
            // ptr is a null pointer
        }

    ### New to C? ###

    Q: What is a pointer?
    A: A pointer is a variable except
       that the value of the variable
       is a memory address.

    Q: What is a null pointer?
    A: A null pointer is a pointer variable with
       value 0. Memory address 0 is invalid
       and if an attempt to access the memory is made
       by a null pointer it will cause the program to crash.
       This is why it is important to always check
       if a pointer is null before using it.

    Q: What is a SEGFAULT or Segmentation fault?
    A: This occurs when attempting to access memory that
       does not belong to your program. In almost all cases
       this will cause your program to crash. The most common
       SEGFAULT is caused by trying to access a null pointer.

*/
#ifdef __cplusplus
#define ACR_NULL nullptr
#endif

#ifndef ACR_NULL
#define ACR_NULL 0
#endif

/** the value of a pointer (used for pointer math)
    can always be stored within the ACR_Length_t type
	but for clarity it is best to use a type that
	specifically designates the use as a pointer's value
*/
typedef ACR_Length_t ACR_PointerValue_t;

#endif
