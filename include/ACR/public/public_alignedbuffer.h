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

/** \file public_alignedbuffer.h
 
    This header provides a data type and macros to
    work with memory aligned data buffers.
    It is included automatically with public.h

    This header gaurantees the following will be defined:
    ACR_AlignedBuffer_t      for memory aligned buffer data
    ACR_VAR_BUFFER_IS_VALID  as a macro to check for valid buffer data

*/
#ifndef _ACR_PUBLIC_ALIGNEDBUFFER_H_
#define _ACR_PUBLIC_ALIGNEDBUFFER_H_

// included for ACR_Length_t, ACR_PointerValue_t, ACR_ZERO_LENGTH, and ACR_NULL
#include "ACR/public/public_memory.h"

// included for ACR_ADD_FLAGS, and ACR_REMOVE_FLAGS
#include "ACR/public/public_bytes_and_flags.h"

// included for ACR_Buffer_t, ACR_BUFFER_IS_REF, and ACR_BUFFER_FLAGS_NONE
#include "ACR/public/public_buffer.h"

// included for ACR_BYTES_PER_BLOCK and ACR_BITS_PER_BLOCK
#include "ACR/public/public_blocks.h"

/** type for reference to ACR_Block_t aligned memory area
	- prevents use of malloc and free directly.
	- prevents use of void pointers without associated memory length
	- include "ACR/alignedbuffer.h" for easy and safe functions
	- see ACR_ALIGNED_BUFFER defines for safe access via macros
*/
typedef struct ACR_AlignedBuffer_s
{
	/** the aligned memory buffer
	*/
	ACR_Buffer_t m_AlignedBuffer;

	/** stores the original memory before alignement
	*/
	ACR_Buffer_t m_UnalignedBuffer;

} ACR_AlignedBuffer_t;

/** define an empty aligned buffer on the stack with the specified name
*/
#define ACR_ALIGNED_BUFFER(name) ACR_AlignedBuffer_t name = {{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE},{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE}}

/** check if the aligned buffer is valid
*/
#define ACR_ALIGNED_BUFFER_IS_VALID(name) ACR_BUFFER_IS_VALID(name.m_AlignedBuffer)

/** allocate memory to the buffer aligned on a block boundary

    Note: the buffer length available may be up to 1 full block less than the length specified.
	      use ACR_ALIGNED_BUFFER_GET_LENGTH to get the actual length available and
          use ACR_ALIGNED_BUFFER_GET_MEMORY to get the actual memory address
*/
#define ACR_ALIGNED_BUFFER_SET_MEMORY(name, memory, length) \
        { \
			ACR_BUFFER_SET_DATA(name.m_UnalignedBuffer, memory, length); \
			if((name.m_UnalignedBuffer.m_Pointer != ACR_NULL) && (name.m_UnalignedBuffer.m_Length > ACR_BYTES_PER_BLOCK)) \
			{ \
				ACR_PointerValue_t alignMask = (~(ACR_BITS_PER_BLOCK-1)); \
				ACR_PointerValue_t memValue = (ACR_PointerValue_t)memory; \
				memValue += (ACR_BITS_PER_BLOCK-1); \
				memValue &= alignMask; \
				name.m_AlignedBuffer.m_Pointer = (void*)memValue; \
				name.m_AlignedBuffer.m_Length = (length - (ACR_Length_t)((ACR_PointerValue_t)name.m_AlignedBuffer.m_Pointer - (ACR_PointerValue_t)memory)); \
				ACR_ADD_FLAGS(name.m_AlignedBuffer.m_Flags, ACR_BUFFER_IS_REF); \
			} \
			else \
			{ \
				name.m_AlignedBuffer.m_Pointer = ACR_NULL; \
				name.m_AlignedBuffer.m_Length = ACR_ZERO_LENGTH; \
				ACR_REMOVE_FLAGS(name.m_AlignedBuffer.m_Flags, ACR_BUFFER_IS_REF); \
			} \
        }

/** get the number of bytes of memory available to the aligned buffer
*/
#define ACR_ALIGNED_BUFFER_GET_LENGTH(name) name.m_AlignedBuffer.m_Length

/** get the memory pointer to the aligned buffer
*/
#define ACR_ALIGNED_BUFFER_GET_MEMORY(name) name.m_AlignedBuffer.m_Pointer

/** free memory used by the buffer
*/
#define ACR_ALIGNED_BUFFER_FREE(name) \
        ACR_BUFFER_FREE(name.m_UnalignedBuffer); \
		name.m_AlignedBuffer.m_Pointer = ACR_NULL; \
		name.m_AlignedBuffer.m_Length = ACR_ZERO_LENGTH; \
        ACR_REMOVE_FLAGS(name.m_AlignedBuffer.m_Flags, ACR_BUFFER_IS_REF)

#endif
