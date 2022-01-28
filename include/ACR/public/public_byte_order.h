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

/** \file public_byte_order.h
 
    This header contains commonly used defines for byte order,
    also called endianness. It can be used standalone from 
    the entire library or is included automatically with public.h

*/
#ifndef _ACR_PUBLIC_BYTE_ORDER_H_
#define _ACR_PUBLIC_BYTE_ORDER_H_

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
//   long/4       memory = [ 0x00 0x01 0x00 0x00 ]
//                binary little endian = 
//                    MSB 00000000 00000001 00000000 00000000 LSB
//                decimal little endian = 65536
//                decimal big endian = 256
//
// "long" Example:
//
//      // given a local variable with value 1
//      long valueInSystemEndian = 1;
//      // convert the value to big endian 
//      long valueInBigEndian = ACR_BYTE_ORDER_32(valueInSystemEndian);
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

/** byte order swap of 16 bit value
*/
#define ACR_BYTE_ORDER_SWAP_16(x)   (((((unsigned short)(x)) & 0x00ff) << 8) | \
                                     ((((unsigned short)(x)) & 0xff00) >> 8))

/** byte order swap of 32 bit value
*/
#define ACR_BYTE_ORDER_SWAP_32(x)   ((((unsigned long)(x) & 0x000000ffUL) << 24) | \
                                     (((unsigned long)(x) & 0x0000ff00UL) <<  8) | \
                                     (((unsigned long)(x) & 0x00ff0000UL) >>  8) | \
                                     (((unsigned long)(x) & 0xff000000UL) >> 24))

//
// defines ACR_IS_BIG_ENDIAN as 1 or 0
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
#define ACR_IS_BIG_ENDIAN 1
#else
#ifdef ACR_CONFIG_LITTLE_ENDIAN
/** the system is NOT big endian because ACR_CONFIG_LITTLE_ENDIAN
    was set in the preprocessor
*/
#define ACR_IS_BIG_ENDIAN 0
#endif // #ifdef ACR_CONFIG_LITTLE_ENDIAN
#endif // #ifdef ACR_CONFIG_BIG_ENDIAN

//
// defines ACR_IS_BIG_ENDIAN as 1 or
// 0 if not previously defined
//
#ifndef ACR_IS_BIG_ENDIAN
#ifdef BIG_ENDIAN
/** the system is big endian because BIG_ENDIAN
    was set in the preprocessor
*/
#define ACR_IS_BIG_ENDIAN 1
#else
#ifdef LITTLE_ENDIAN
/** the system is NOT big endian because LITTLE_ENDIAN
    was set in the preprocessor
*/
#define ACR_IS_BIG_ENDIAN 0
#else
// Note: warning C4906: string literal cast to 'unsigned short *' should be
//       ignored in project settings to use dynamic endianess detection
#define ACR_IS_BIG_ENDIAN (*(unsigned short *)"\0\xff" < 0x100)
#define ACR_ENDIAN_DYNAMIC 1
#endif // #ifdef LITTLE_ENDIAN
#endif // #ifdef BIG_ENDIAN
#endif // #ifndef ACR_IS_BIG_ENDIAN

//
// defines ACR_BYTE_ORDER_16 and ACR_BYTE_ORDER_32
// to swap byte order to big endian when needed
//
// Note: public.h also defines ACR_BYTE_ORDER_64 when 64bit support is enabled
//
#ifdef ACR_ENDIAN_DYNAMIC
    #define ACR_BYTE_ORDER_16(x) ((ACR_IS_BIG_ENDIAN == 0)?ACR_BYTE_ORDER_SWAP_16(x):x)
    #define ACR_BYTE_ORDER_32(x) ((ACR_IS_BIG_ENDIAN == 0)?ACR_BYTE_ORDER_SWAP_32(x):x)
#else
    #if ACR_IS_BIG_ENDIAN == 0
        #define ACR_BYTE_ORDER_16(x) (ACR_BYTE_ORDER_SWAP_16(x))
        #define ACR_BYTE_ORDER_32(x) (ACR_BYTE_ORDER_SWAP_32(x))
    #else
        #define ACR_BYTE_ORDER_16(x) (x)
        #define ACR_BYTE_ORDER_32(x) (x)
    #endif // #if ACR_IS_BIG_ENDIAN == 0
#endif // #ifdef ACR_ENDIAN_DYNAMIC

#if ACR_USE_64BIT != 0

    /** byte order swap of 64 bit value
    */
    #define ACR_BYTE_ORDER_SWAP_64(x)   ((((unsigned long long)(x) & 0x00000000000000ffULL) << 56) | \
                                        (((unsigned long long)(x) & 0x000000000000ff00ULL) << 40) | \
                                        (((unsigned long long)(x) & 0x0000000000ff0000ULL) << 24) | \
                                        (((unsigned long long)(x) & 0x00000000ff000000ULL) <<  8) | \
                                        (((unsigned long long)(x) & 0x000000ff00000000ULL) >>  8) | \
                                        (((unsigned long long)(x) & 0x0000ff0000000000ULL) >> 24) | \
                                        (((unsigned long long)(x) & 0x00ff000000000000ULL) >> 40) | \
                                        (((unsigned long long)(x) & 0xff00000000000000ULL) >> 56))
    #ifdef ACR_ENDIAN_DYNAMIC
        #define ACR_BYTE_ORDER_64(x) ((ACR_IS_BIG_ENDIAN == 0)?ACR_BYTE_ORDER_SWAP_64(x):x)
    #else
        #if ACR_IS_BIG_ENDIAN == 0
            #define ACR_BYTE_ORDER_64(x) (ACR_BYTE_ORDER_SWAP_64(x))
        #else
            #define ACR_BYTE_ORDER_64(x) (x)
        #endif // #if ACR_IS_BIG_ENDIAN == 0
    #endif // #ifdef ACR_ENDIAN_DYNAMIC

#endif // #if ACR_USE_64BIT != 0

#endif
