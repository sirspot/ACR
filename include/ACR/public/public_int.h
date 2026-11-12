/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2026 Adam C. Rosenberg

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

/** \file public_int.h
 
    This header contains commonly used types for integers.
    It can be used standalone from the entire library or is
    included automatically with public.h

*/
#ifndef _ACR_PUBLIC_INT_H_
#define _ACR_PUBLIC_INT_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public/public_bool.h"

// included for ACR_USE_64BIT
#include "ACR/public/public_memory.h"

// included for ACR_BITS_PER_BYTE
#include "ACR/public/public_bytes_and_flags.h"

////////////////////////////////////////////////////////////
//
// ### New to C? ###
//
// Integers are whole numbers like 5, 10, and 42. In most cases,
// an integer variable can just be of type int, which selects
// the most typical number storage type for your platform.
//
// Sometimes it is more appropriate to use a variable type that
// is unsigned, meaning it cannot store negative numbers. There
// are also types that use an exact number of bits to either limit 
// the range of numbers that can be stored, or meet a specific need.
//      
////////////////////////////////////////////////////////////

/** 16 bit signed value
*/
#ifndef ACR_CONFIG_NO_LIBC
    #include <stdint.h>
    typedef int16_t ACR_16bit_t;
#else
    typedef short ACR_16bit_t;
#endif

/** 16 bit unsigned value
*/
#ifndef ACR_CONFIG_NO_LIBC
    #include <stdint.h>
    typedef uint16_t ACR_Unsigned_16bit_t;
#else
    typedef unsigned short ACR_Unsigned_16bit_t;
#endif

/** create a bit mask
    \param bits the number of least significant bits to mask
    \returns the mask value
*/
static inline ACR_Unsigned_16bit_t ACR_INT_16_MASK(ACR_Unsigned_16bit_t bits) 
{
    ACR_Unsigned_16bit_t mask = 0;
    ACR_Unsigned_16bit_t bit = 0;

    if(bits >= (sizeof(ACR_Unsigned_16bit_t) * ACR_BITS_PER_BYTE))
    {
        return ~((ACR_Unsigned_16bit_t)0);
    }

    while(bit < bits)
    {
        mask |= (ACR_Unsigned_16bit_t)((ACR_Unsigned_16bit_t)1 << bit);
        bit += 1;
    }

    return mask;
}

/** 32 bit signed value
*/
#ifndef ACR_CONFIG_NO_LIBC
    #include <stdint.h>
    typedef int32_t ACR_32bit_t;
#else
    typedef int ACR_32bit_t;
#endif

/** 32 bit unsigned value
*/
#ifndef ACR_CONFIG_NO_LIBC
    #include <stdint.h>
    typedef uint32_t ACR_Unsigned_32bit_t;
#else
    typedef unsigned int ACR_Unsigned_32bit_t;
#endif

/** create a bit mask
    \param bits the number of least significant bits to mask
    \returns the mask value
*/
static inline ACR_Unsigned_32bit_t ACR_INT_32_MASK(ACR_Unsigned_32bit_t bits) 
{
    ACR_Unsigned_32bit_t mask = 0;
    ACR_Unsigned_32bit_t bit = 0;

    if(bits >= (sizeof(ACR_Unsigned_32bit_t) * ACR_BITS_PER_BYTE))
    {
        return ~((ACR_Unsigned_32bit_t)0);
    }

    while(bit < bits)
    {
        mask |= (ACR_Unsigned_32bit_t)((ACR_Unsigned_32bit_t)1 << bit);
        bit += 1;
    }

    return mask;
}

#if ACR_USE_64BIT == ACR_BOOL_TRUE

    /** 64 bit signed value
    */
    #ifndef ACR_CONFIG_NO_LIBC
        #include <stdint.h>
        typedef int64_t ACR_64bit_t;
    #else
        typedef long long ACR_64bit_t;
    #endif

    /** 64 bit unsigned value
    */
    #ifndef ACR_CONFIG_NO_LIBC
        #include <stdint.h>
        typedef uint64_t ACR_Unsigned_64bit_t;
    #else
        typedef unsigned long long ACR_Unsigned_64bit_t;
    #endif

    /** create a bit mask
        \param bits the number of least significant bits to mask
        \returns the mask value
    */
    static inline ACR_Unsigned_64bit_t ACR_INT_64_MASK(ACR_Unsigned_64bit_t bits) 
    {
        ACR_Unsigned_64bit_t mask = 0;
        ACR_Unsigned_64bit_t bit = 0;

        if(bits >= (sizeof(ACR_Unsigned_64bit_t) * ACR_BITS_PER_BYTE))
        {
            return ~((ACR_Unsigned_64bit_t)0);
        }

        while(bit < bits)
        {
            mask |= (ACR_Unsigned_64bit_t)((ACR_Unsigned_64bit_t)1 << bit);
            bit += 1;
        }

        return mask;
    }

#endif // ACR_USE_64BIT == ACR_BOOL_TRUE

#endif
