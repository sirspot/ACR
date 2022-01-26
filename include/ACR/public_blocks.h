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

/** \file public_blocks.h
 
    This header provides a data type and macros to
    work with blocks of data.
    It is included automatically with public.h

    This header gaurantees the following will be defined:
    ACR_Block_t           for block data count
    ACR_Blocks_t          for exact block and byte count
    ACR_MIN_BLOCKS_NEEDED as a macro to convert bytes to blocks needed
    ACR_LENGTH_TO_BLOCKS  as a macro to convert bytes to exact blocks and bytes

*/
#ifndef _ACR_PUBLIC_BLOCKS_H_
#define _ACR_PUBLIC_BLOCKS_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public_bool.h"

/** type for an effeciently sized memory block, which is
    probably the largest integer value type
	\see ACR_MAX_BLOCK for the maximum value that can be
	stored by this data type
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
typedef unsigned long long ACR_Block_t;
#else
// 32bit
typedef unsigned long ACR_Block_t;
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

/** max value that can be stored by the ACR_Block_t type
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
#define ACR_MAX_BLOCK 18446744073709551615ULL // hex value 0xFFFFFFFFFFFFFFFF
#else
// 32bit
#define ACR_MAX_BLOCK 4294967295UL // hex value 0xFFFFFFFF
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

/** number of bytes in ACR_Block_t
*/
#define ACR_BYTES_PER_BLOCK sizeof(ACR_Block_t)

/** number of bits in ACR_Block_t
*/
#define ACR_BITS_PER_BLOCK (ACR_BYTES_PER_BLOCK * ACR_BITS_PER_BYTE)

/** get the minimum number of blocks needed for the specified memory length and block size.
    to get a more accurate number of blocks and bytes use ACR_LENGTH_TO_BLOCKS_BY_SIZE
    \param l length is bytes
    \param s number of bytes per block
    \returns the minimum number of blocks needed as ACR_Block_t
*/
#define ACR_MIN_BLOCKS_NEEDED_BY_SIZE(l, s) ((ACR_Block_t)((l / s) + ((l % s) != 0)))

/** get the minimum number of standard sized blocks needed for the specified memory length.
    to get a more accurate number of blocks and bytes use ACR_LENGTH_TO_BLOCKS
*/
#define ACR_MIN_BLOCKS_NEEDED(length) ACR_MIN_BLOCKS_NEEDED_BY_SIZE(length, ACR_BYTES_PER_BLOCK)

/** type that stores the number of full blocks and remaining bytes
*/
typedef struct ACR_Blocks_s
{
	ACR_Block_t m_Blocks;
	ACR_Block_t m_Bytes;
} ACR_Blocks_t;

/** converts a length to ACR_Blocks_t data to provide the
    exact number of blocks and bytes needed for the memory length
    \param b the blocks data
    \param l length is bytes
    \param s number of bytes per block
*/
#define ACR_LENGTH_TO_BLOCKS_BY_SIZE(b, l, s) { b.m_Blocks = (l / s); b.m_Bytes = (l % s); }

/** converts a length to ACR_Blocks_t data to provide the
    exact number of standard sized blocks and bytes needed for the memory length
*/
#define ACR_LENGTH_TO_BLOCKS(blocks, length) ACR_LENGTH_TO_BLOCKS_BY_SIZE(blocks, length, ACR_BYTES_PER_BLOCK)

#endif
