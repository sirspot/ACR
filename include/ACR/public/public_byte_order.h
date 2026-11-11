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

/** \file public_byte_order.h
 
    This header contains commonly used defines for byte order,
    also called endianness. It can be used standalone from 
    the entire library or is included automatically with public.h

*/
#ifndef _ACR_PUBLIC_BYTE_ORDER_H_
#define _ACR_PUBLIC_BYTE_ORDER_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public/public_bool.h"

// included for ACR_USE_64BIT
#include "ACR/public/public_memory.h"

////////////////////////////////////////////////////////////
//
// ### New to C? ###
//
// Even experienced programmers sometimes forget about
// endianess. Read the following details to help understand
// what endianess means and how it changes the way data
// is stored in memory
//
// Q: What is MSB and LSB?
// A: The Most Significant Bit/Byte (MSB) is the bit or byte
//    that changes the value of an integer by the greatest amount.
//    The Least Significant Bit/Byte (LSB) is the bit or byte
//    that changes the value of an integer by the smallest amount.
//    See the Sample Memory illustrations below for details.
//
// Note: Big Endian means that multibyte values have the
//       bytes stored in memory from least significant 
//       to most significant. Little Endian is the opposite.
//
// ### Sample Memory ###
//
//   type/bytes   illustration
//
//   char/1       memory = [ 0x01 ---- ---- ---- ]
//                binary little endian =
//                    MSB -------- -------- -------- 00000001 LSB
//                decimal little endian = 1
//                decimal big endian = 1
//
//   short/2      memory = [ 0x01 0x00 ---- ---- ]
//                binary little endian = 
//                    MSB -------- -------- 00000001 00000000 LSB
//                decimal little endian = 256
//                decimal big endian = 1
//
//   short/2      memory = [ 0x00 0x01 ---- ---- ]
//                binary little endian = 
//                    MSB -------- -------- 00000000 00000001 LSB
//                decimal little endian = 1
//                decimal big endian = 256
//
//   int/4        memory = [ 0x00 0x01 0x00 0x00 ]
//                binary little endian = 
//                    MSB 00000000 00000001 00000000 00000000 LSB
//                decimal little endian = 65536
//                decimal big endian = 256
//
// "int" Example:
//
//      // given a local variable with value 1
//      int valueInSystemEndian = 1;
//      // convert the value to big endian 
//      int valueInBigEndian = ACR_BYTE_ORDER_32(valueInSystemEndian);
//      // and use the same macro to convert
//      // a big endian value back to system endianness
//      valueInSystemEndian = ACR_BYTE_ORDER_32(valueInBigEndian);
//
// "short" example
//
//      // given a value known to be in big endian
//      short valueInBigEndian = 1;
//      // convert the value to system endian
//      short valueInSystemEndian = ACR_BYTE_ORDER_16(valueInBigEndian);
//      
////////////////////////////////////////////////////////////

//
// defines ACR_IS_BIG_ENDIAN
//
// Optional: If you already know the endianess of your
//           system then set the preprocessor define as
//           follows to improve byte order handling
//           performance.
//           Big Endian:    ACR_CONFIG_BIG_ENDIAN
//           Little Endian: ACR_CONFIG_LITTLE_ENDIAN
//
#ifdef ACR_CONFIG_BIG_ENDIAN
    /** the system is big endian because ACR_CONFIG_BIG_ENDIAN
        was set in the preprocessor
    */
    #define ACR_IS_BIG_ENDIAN ACR_BOOL_TRUE
#else
    #ifdef ACR_CONFIG_LITTLE_ENDIAN
        /** the system is NOT big endian because ACR_CONFIG_LITTLE_ENDIAN
            was set in the preprocessor
        */
        #define ACR_IS_BIG_ENDIAN ACR_BOOL_FALSE
    #endif // #ifdef ACR_CONFIG_LITTLE_ENDIAN
#endif // #ifdef ACR_CONFIG_BIG_ENDIAN

#ifdef ACR_PLATFORM_WIN
    // most windows platforms are little endian so
    // make this assumption now
    #define ACR_IS_BIG_ENDIAN ACR_BOOL_FALSE
#endif

//
// defines ACR_IS_BIG_ENDIAN as ACR_BOOL_TRUE or
// ACR_BOOL_FALSE using defines built into the compiler
// or by including a platform-specific c header because
// no C standard currently defines endianess at the time
// this was written
//
#ifndef ACR_IS_BIG_ENDIAN

    #ifdef  __BYTE_ORDER__
        // the compiler has already specified byte order
        #ifdef __ORDER_LITTLE_ENDIAN__
            // the compiler as also specified a known value for __BYTE_ORDER__
            #undef BYTE_ORDER
            #undef LITTLE_ENDIAN
            #undef BIG_ENDIAN
            #define LITTLE_ENDIAN 1234
            #define BIG_ENDIAN 4321
            #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
                #define BYTE_ORDER LITTLE_ENDIAN
            #else
                #define BYTE_ORDER BIG_ENDIAN
            #endif
        #endif
    #else
        #if defined(_WIN32) || defined(_WIN64)
            // Windows is (historically) always little endian
            #undef BYTE_ORDER
            #undef LITTLE_ENDIAN
            #undef BIG_ENDIAN
            #define LITTLE_ENDIAN 1234
            #define BIG_ENDIAN 4321
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif

    // check for compiler defined values such as those normally provided by clang
    #if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define ACR_IS_BIG_ENDIAN ACR_BOOL_TRUE
    #elif defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define ACR_IS_BIG_ENDIAN ACR_BOOL_FALSE
    #else

        // no compiler defined values found, try the c library instead
        #ifndef ACR_CONFIG_NO_LIBC
            // included for BYTE_ORDER, BIG_ENDIAN, and LITTLE_ENDIAN
            #if defined(ACR_PLATFORM_MAC)
                #include <machine/endian.h>
            #elif defined(ACR_PLATFORM_WIN)
                #include <endian.h>
            #elif defined(ACR_PLATFORM_GITPOD)
                #include <endian.h>
            #elif defined(ACR_PLATFORM_LINUX)
                #include <endian.h>
            #endif
        #endif

        #ifdef BYTE_ORDER
            #if BYTE_ORDER == BIG_ENDIAN
                /** the system is big endian
                */
                #define ACR_IS_BIG_ENDIAN ACR_BOOL_TRUE
            #else
                #if BYTE_ORDER == LITTLE_ENDIAN
                    /** the system is NOT big endian
                    */
                    #define ACR_IS_BIG_ENDIAN ACR_BOOL_FALSE
                #endif // #if BYTE_ORDER == LITTLE_ENDIAN
            #endif // #if BYTE_ORDER == BIG_ENDIAN
        #endif // #ifdef BYTE_ORDER

    #endif
#endif // #ifndef ACR_IS_BIG_ENDIAN

//
// using dynamic endian if ACR_IS_BIG_ENDIAN is not known
//
#ifndef ACR_IS_BIG_ENDIAN
    #define ACR_ENDIAN_DYNAMIC ACR_BOOL_TRUE
    /** Determine whether the current system stores the most significant byte first.
        \return ACR_BOOL_TRUE for big-endian systems; otherwise ACR_BOOL_FALSE.
    */
    static inline ACR_Bool_t ACR_DYNAMIC_IS_BIG_ENDIAN(void)
    {
        const unsigned short value = 1;
        const unsigned char *first_byte = (const unsigned char *)&value;
        return first_byte[0] == 0 ? ACR_BOOL_TRUE : ACR_BOOL_FALSE;
    }
    #define ACR_IS_BIG_ENDIAN ACR_DYNAMIC_IS_BIG_ENDIAN()
#else
    #define ACR_ENDIAN_DYNAMIC ACR_BOOL_FALSE
#endif

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

/** Swap the byte order of a 16-bit value.
    \param value The value whose bytes are to be swapped.
    \return The value with its two bytes reversed.
*/
static inline ACR_Unsigned_16bit_t ACR_BYTE_ORDER_SWAP_16(ACR_Unsigned_16bit_t value)
{
    return (ACR_Unsigned_16bit_t)(((value & 0x00ffU) << 8) |
                                  ((value & 0xff00U) >> 8));
}

/** 32 bit signed value
*/
#ifndef ACR_CONFIG_NO_LIBC
    #include <stdint.h>
    typedef int32_t ACR_32bit_t;
#else
    typedef long ACR_32bit_t;
#endif

/** 32 bit unsigned value
*/
#ifndef ACR_CONFIG_NO_LIBC
    #include <stdint.h>
    typedef uint32_t ACR_Unsigned_32bit_t;
#else
    typedef unsigned long ACR_Unsigned_32bit_t;
#endif

/** Swap the byte order of a 32-bit value.
    \param value The value whose bytes are to be swapped.
    \return The value with its four bytes reversed.
*/
static inline ACR_Unsigned_32bit_t ACR_BYTE_ORDER_SWAP_32(ACR_Unsigned_32bit_t value)
{
    return ((value & 0x000000ffUL) << 24) |
           ((value & 0x0000ff00UL) <<  8) |
           ((value & 0x00ff0000UL) >>  8) |
           ((value & 0xff000000UL) >> 24);
}

//
// defines ACR_BYTE_ORDER_16 and ACR_BYTE_ORDER_32
// to swap byte order to big endian when needed
//
#if ACR_ENDIAN_DYNAMIC == ACR_BOOL_TRUE
    #define ACR_BYTE_ORDER_16(x) ((ACR_DYNAMIC_IS_BIG_ENDIAN() == ACR_BOOL_FALSE)?ACR_BYTE_ORDER_SWAP_16(x):x)
    #define ACR_BYTE_ORDER_32(x) ((ACR_DYNAMIC_IS_BIG_ENDIAN() == ACR_BOOL_FALSE)?ACR_BYTE_ORDER_SWAP_32(x):x)
#else
    #if ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE
        #define ACR_BYTE_ORDER_16(x) (ACR_BYTE_ORDER_SWAP_16(x))
        #define ACR_BYTE_ORDER_32(x) (ACR_BYTE_ORDER_SWAP_32(x))
    #else
        #define ACR_BYTE_ORDER_16(x) (x)
        #define ACR_BYTE_ORDER_32(x) (x)
    #endif // #if ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE
#endif // #if ACR_ENDIAN_DYNAMIC == ACR_BOOL_TRUE

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

    /** swap the byte order of a 64-bit value.
        \param value the value
        \return value with its eight bytes reversed.
    */
    static inline ACR_Unsigned_64bit_t ACR_BYTE_ORDER_SWAP_64(ACR_Unsigned_64bit_t value)
    {
        return ((value & 0x00000000000000ffULL) << 56) |
               ((value & 0x000000000000ff00ULL) << 40) |
               ((value & 0x0000000000ff0000ULL) << 24) |
               ((value & 0x00000000ff000000ULL) <<  8) |
               ((value & 0x000000ff00000000ULL) >>  8) |
               ((value & 0x0000ff0000000000ULL) >> 24) |
               ((value & 0x00ff000000000000ULL) >> 40) |
               ((value & 0xff00000000000000ULL) >> 56);
    }
    #if ACR_ENDIAN_DYNAMIC == ACR_BOOL_TRUE
        #define ACR_BYTE_ORDER_64(x) ((ACR_DYNAMIC_IS_BIG_ENDIAN() == 0)?ACR_BYTE_ORDER_SWAP_64(x):x)
    #else
        #if ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE
            #define ACR_BYTE_ORDER_64(x) (ACR_BYTE_ORDER_SWAP_64(x))
        #else
            #define ACR_BYTE_ORDER_64(x) (x)
        #endif // #if ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE
    #endif // #if ACR_ENDIAN_DYNAMIC == ACR_BOOL_TRUE

#endif // ACR_USE_64BIT == ACR_BOOL_TRUE

#endif
