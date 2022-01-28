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

/** \file public_buffer.h
 
    This header provides a data type and macros to
    work with simple data buffers.
    It is included automatically with public.h

    This header gaurantees the following will be defined:
    ACR_Buffer_t           for buffer data
    ACR_BUFFER_IS_VALID    as a macro to check for valid buffer data
    ACR_BUFFER_SET_DATA    as a macro to reference an area of memory
    ACR_BUFFER_ALLOC       as a macro to allocate memory using ACR_MALLOC
    ACR_BUFFER_FREE        as a macro to free memory that was allocated by ACR_BUFFER_ALLOC

*/
#ifndef _ACR_PUBLIC_BUFFER_H_
#define _ACR_PUBLIC_BUFFER_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public/public_bool.h"

// included for ACR_Length_t, ACR_ZERO_LENGTH, ACR_CLEAR_MEMORY, and ACR_NULL
#include "ACR/public/public_memory.h"

// included for ACR_Byte_t, ACR_Flags_t, ACR_HAS_FLAG, ACR_ADD_FLAGS, and ACR_REMOVE_FLAGS
#include "ACR/public/public_bytes_and_flags.h"

// included for ACR_HAS_MALLOC, ACR_MALLOC and ACR_FREE
#include "ACR/public/public_heap.h"

/** type for reference to a memory area.
    - prevents use of malloc and free directly.
    - prevents use of void pointers without associated memory length
	- include "ACR/buffer.h" for easy and safe functions
	- see ACR_BUFFER defines for safe access via macros

	Note: disable warning C4820: padding added after data member
*/
typedef struct ACR_Buffer_s
{
    /** points to a memory location or ACR_NULL
    */
    void* m_Pointer;

    /** length of the memory in bytes
        that m_Pointer points to
    */
    ACR_Length_t m_Length;

	/** flags to change the default operation of the buffer
	    see enum ACR_BufferFlags_e
	*/
	ACR_Flags_t m_Flags;

} ACR_Buffer_t;

/** buffer flags to change default behavior
*/
enum ACR_BufferFlags_e
{
	ACR_BUFFER_FLAGS_NONE = 0x00,
	ACR_BUFFER_IS_REF     = 0x01
};

/** define a buffer on the stack with the specified name
*/
#define ACR_BUFFER(name) ACR_Buffer_t name = {ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE}

/** define a buffer on the stack and with the specified name using the data of the specified size 
*/
#define ACR_BUFFER_FROM_DATA(name, data, length) ACR_Buffer_t name = {data,length,ACR_BUFFER_IS_REF}

/** determine if the buffer is valid
*/
#define ACR_BUFFER_IS_VALID(name) ((name.m_Pointer != ACR_NULL) && (name.m_Length > 0))

/** get the length of the buffer
*/
#define ACR_BUFFER_GET_LENGTH(name) name.m_Length

/** clear the buffer
*/
#define ACR_BUFFER_CLEAR(name) ACR_CLEAR_MEMORY(name.m_Pointer, name.m_Length)

/** assign memory to the existing buffer
*/
#define ACR_BUFFER_SET_DATA(name, data, length)\
        if(name.m_Pointer != ACR_NULL)\
		{\
			if(ACR_HAS_FLAG(name.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE)\
			{\
				ACR_FREE(name.m_Pointer);\
			}\
		}\
		name.m_Pointer = (void*)data;\
		if(name.m_Pointer != ACR_NULL)\
		{\
			name.m_Length = length;\
			ACR_ADD_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF);\
		}\
		else\
		{\
			name.m_Length = ACR_ZERO_LENGTH;\
			ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF);\
		}

#if ACR_HAS_MALLOC == ACR_BOOL_TRUE

/** free memory used by the buffer
*/
#define ACR_BUFFER_FREE(name) \
        if(name.m_Pointer != ACR_NULL) \
		{ \
			if(ACR_HAS_FLAG(name.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE) \
			{ \
				ACR_FREE(name.m_Pointer); \
			} \
			name.m_Pointer = ACR_NULL; \
		} \
		name.m_Length = ACR_ZERO_LENGTH; \
		ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF)

/** allocate memory for the buffer

    Note that 1 extra byte will be allocated as a safety
    precaution to ensure the buffer will always be null-terminated
    regardless of the data stored up to the size of the buffer.
*/
#define ACR_BUFFER_ALLOC(name, length) \
        if(name.m_Pointer != ACR_NULL) \
		{ \
			if(ACR_HAS_FLAG(name.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE) \
			{ \
				ACR_FREE(name.m_Pointer); \
			} \
		} \
		name.m_Pointer = ACR_MALLOC(length+1); \
		if(name.m_Pointer != ACR_NULL) \
		{ \
            ((ACR_Byte_t*)name.m_Pointer)[length] = 0; \
			name.m_Length = length; \
		} \
		else \
		{ \
			name.m_Length = ACR_ZERO_LENGTH; \
		} \
		ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF)

#else

/** free is not available
*/
#define ACR_BUFFER_FREE(name) name.m_Pointer = ACR_NULL; name.m_Length = ACR_ZERO_LENGTH; ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF)

/** malloc is not available
*/
#define ACR_BUFFER_ALLOC(name, length) name.m_Pointer = ACR_NULL; name.m_Length = ACR_ZERO_LENGTH; ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF)

#endif // #if ACR_HAS_MALLOC == ACR_BOOL_TRUE        

/** explicitly free the memory this buffer references
*/
#define ACR_BUFFER_FORCE_FREE(name)\
        ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF); \
        ACR_BUFFER_FREE(name)

#endif
