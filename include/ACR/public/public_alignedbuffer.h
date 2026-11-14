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

/** \file public_alignedbuffer.h
 
    This header provides a data type and macros to
    work with memory aligned data buffers.
    It is included automatically with public.h

    This header guarantees the following will be defined:
    ACR_AlignedBuffer_t      for memory aligned buffer data
    ACR_VAR_BUFFER_IS_VALID  as a macro to check for valid buffer data

*/
#ifndef _ACR_PUBLIC_ALIGNEDBUFFER_H_
#define _ACR_PUBLIC_ALIGNEDBUFFER_H_

// included for ACR_Length_t, ACR_PointerValue_t, ACR_ZERO_LENGTH, and ACR_NULL
#include "ACR/public/public_memory.h"

// included for ACR_BITS_PER_BYTE, ACR_ADD_FLAGS, and ACR_REMOVE_FLAGS
#include "ACR/public/public_bytes_and_flags.h"

// included for ACR_Buffer_t, ACR_BUFFER_IS_REF, and ACR_BUFFER_NO_FLAGS
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

	/** stores the original memory before alignment
	*/
	ACR_Buffer_t m_UnalignedBuffer;

} ACR_AlignedBuffer_t;

/** define an empty aligned buffer on the stack with the specified name
*/
#define ACR_ALIGNED_BUFFER(name) ACR_AlignedBuffer_t name = {{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_NO_FLAGS},{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_NO_FLAGS}}

/** check if the aligned buffer is valid
*/
#define ACR_ALIGNED_BUFFER_IS_VALID(name) ACR_BUFFER_IS_VALID(name.m_AlignedBuffer)

/** assign existing memory to the buffer aligned on a boundary determined by the specified number of bytes

    Note: the buffer length available may be up to 1 full block less than the length specified.
	      use ACR_ALIGNED_BUFFER_GET_LENGTH to get the actual length available and
          use ACR_ALIGNED_BUFFER_GET_MEMORY to get the actual memory address
*/
static inline void ACR_ALIGNED_BUFFER_PTR_SET_MEMORY_ALIGNED_TO(ACR_AlignedBuffer_t* me, void* memory, ACR_Length_t length, ACR_Length_t alignmentBytes)
{
    if(me == ACR_NULL)
    {
        return;
    }

    ACR_BUFFER_PTR_SET_DATA(&me->m_UnalignedBuffer, memory, length);
    if(alignmentBytes < 1)
    {
        // cannot align to less than 1 byte
        ACR_BUFFER_PTR_SET_DATA(&me->m_AlignedBuffer, ACR_NULL, ACR_ZERO_LENGTH);
    }
    else if(alignmentBytes == 1)
    {
        // align to 1 byte is the same as using the pointer as-is
        ACR_BUFFER_PTR_SET_DATA(&me->m_AlignedBuffer, memory, length);
    }
    else if(ACR_BUFFER_PTR_IS_VALID(&me->m_UnalignedBuffer))
    {
        ACR_PointerValue_t pointerValue = (ACR_PointerValue_t)me->m_UnalignedBuffer.m_Pointer;
        ACR_Length_t remainder = (ACR_Length_t)(pointerValue % alignmentBytes);
        ACR_Length_t offset = (remainder == ACR_ZERO_LENGTH) ? ACR_ZERO_LENGTH : (alignmentBytes - remainder);
        if(offset < me->m_UnalignedBuffer.m_Length)
        {
            char* alignedPointer = ((char*)me->m_UnalignedBuffer.m_Pointer) + offset;
            ACR_Length_t alignedLength = (me->m_UnalignedBuffer.m_Length - offset);
            ACR_BUFFER_PTR_SET_DATA(&me->m_AlignedBuffer, alignedPointer, alignedLength);
        }
        else
        {
            // there is not enough memory to align to the requested number of bytes
            ACR_BUFFER_PTR_SET_DATA(&me->m_AlignedBuffer, ACR_NULL, ACR_ZERO_LENGTH);
        }
    }
    else
    {
        // cannot align to an invalid buffer
        ACR_BUFFER_PTR_SET_DATA(&me->m_AlignedBuffer, ACR_NULL, ACR_ZERO_LENGTH);
    }
}
#define ACR_ALIGNED_BUFFER_SET_MEMORY_ALIGNED_TO(name, memory, length, alignmentBytes) ACR_ALIGNED_BUFFER_PTR_SET_MEMORY_ALIGNED_TO(&(name), (memory), (length), (alignmentBytes))

/** assign existing memory to the buffer aligned on a ACR_Block_t boundary
*/
#define ACR_ALIGNED_BUFFER_SET_MEMORY(name, memory, length) ACR_ALIGNED_BUFFER_PTR_SET_MEMORY_ALIGNED_TO(&(name), (memory), (length), ACR_BYTES_PER_BLOCK)

/** get the number of bytes of memory available to the aligned buffer
*/
#define ACR_ALIGNED_BUFFER_GET_LENGTH(name) name.m_AlignedBuffer.m_Length

/** get the memory pointer to the aligned buffer
*/
#define ACR_ALIGNED_BUFFER_GET_MEMORY(name) name.m_AlignedBuffer.m_Pointer

/** free memory used by the buffer
*/
#define ACR_ALIGNED_BUFFER_FREE(name) \
        ACR_BUFFER_PTR_FREE(&name.m_UnalignedBuffer); \
        ACR_BUFFER_PTR_FREE(&name.m_AlignedBuffer);

#endif
