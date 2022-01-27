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

/** \file public_varbuffer.h
 
    This header provides a data type and macros to
    work with variable length data buffers.
    It is included automatically with public.h

    This header gaurantees the following will be defined:
    ACR_VarBuffer_t          for variable length buffer data
    ACR_VAR_BUFFER_IS_VALID  as a macro to check for valid buffer data

*/
#ifndef _ACR_PUBLIC_VARBUFFER_H_
#define _ACR_PUBLIC_VARBUFFER_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public/public_bool.h"

// included for ACR_Length_t, ACR_MEMCPY, ACR_ZERO_LENGTH, and ACR_NULL
#include "ACR/public/public_memory.h"

// included for ACR_Byte_t, ACR_HAS_FLAG, ACR_ADD_FLAGS, and ACR_REMOVE_FLAGS
#include "ACR/public/public_bytes_and_flags.h"

// included for ACR_HAS_MALLOC, ACR_MALLOC, ACR_REALLOC, and ACR_FREE
#include "ACR/public/public_heap.h"

// included for ACR_Buffer_t, ACR_BUFFER_IS_REF, and ACR_BUFFER_FLAGS_NONE
#include "ACR/public/public_buffer.h"

/** type for reference to a memory area with variable length
	- prevents use of malloc and free directly.
	- prevents use of void pointers without associated memory length
	- include "ACR/varbuffer.h" for easy and safe functions
	- see ACR_VAR_BUFFER defines for safe access via macros
*/
typedef struct ACR_VarBuffer_s
{
    ACR_Buffer_t m_Buffer;
    ACR_Length_t m_MaxLength;
} ACR_VarBuffer_t;

/** define a variable sized buffer on the stack with the specified name
*/
#define ACR_VAR_BUFFER(name) ACR_VarBuffer_t name = {{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE},ACR_ZERO_LENGTH}

/** get the max length of the buffer
*/
#define ACR_VAR_BUFFER_GET_MAX_LENGTH(name) name.m_MaxLength

/** get the length of the buffer
*/
#define ACR_VAR_BUFFER_GET_LENGTH(name) name.m_Buffer.m_Length

/** reset the buffer length to zero
*/
#define ACR_VAR_BUFFER_RESET(name) name.m_Buffer.m_Length = ACR_ZERO_LENGTH

/** set the length of the buffer up to the max length
*/
#define ACR_VAR_BUFFER_SET_LENGTH(name, length)\
		if(length <= name.m_MaxLength)\
		{\
            name.m_Buffer.m_Length = length;\
        }

/** append data to the buffer up to the max length
*/
#define ACR_VAR_BUFFER_APPEND(name, srcPtr, length)\
        if(length <= (name.m_MaxLength - name.m_Buffer.m_Length))\
        {\
             if(srcPtr != ACR_NULL)\
             {\
                 ACR_MEMCPY(((ACR_Byte_t*)name.m_Buffer.m_Pointer) + name.m_Buffer.m_Length, srcPtr, length);\
             }\
             else\
             {\
                ACR_MEMSET(((ACR_Byte_t*)name.m_Buffer.m_Pointer) + name.m_Buffer.m_Length,ACR_EMPTY_VALUE,length);\
             }\
             name.m_Buffer.m_Length += length;\
        }

/** determine if the variable length buffer is valid
*/
#define ACR_VAR_BUFFER_IS_VALID(name) ((name.m_Buffer.m_Pointer != ACR_NULL) && (name.m_MaxLength > 0))

/** assign memory to the buffer
*/
#define ACR_VAR_BUFFER_REFERENCE(name, memory, length)\
        if(name.m_Buffer.m_Pointer != ACR_NULL)\
        {\
            if(ACR_HAS_FLAG(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE)\
            {\
                ACR_FREE(name.m_Buffer.m_Pointer);\
            }\
        }\
        name.m_Buffer.m_Pointer = (void*)memory;\
        name.m_Buffer.m_Length = ACR_ZERO_LENGTH;\
        if(name.m_Buffer.m_Pointer != ACR_NULL)\
        {\
            name.m_MaxLength = length;\
            ACR_ADD_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF);\
        }\
        else\
		{\
		    name.m_MaxLength = ACR_ZERO_LENGTH;\
            ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF);\
        }

#if ACR_HAS_MALLOC == ACR_BOOL_TRUE

/** free memory used by the buffer
*/
#define ACR_VAR_BUFFER_FREE(name)\
        if(name.m_Buffer.m_Pointer != ACR_NULL)\
        {\
            if(ACR_HAS_FLAG(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE)\
            {\
                ACR_FREE(name.m_Buffer.m_Pointer);\
            }\
            name.m_Buffer.m_Pointer = ACR_NULL;\
        }\
        name.m_Buffer.m_Length = ACR_ZERO_LENGTH;\
        name.m_MaxLength = ACR_ZERO_LENGTH;\
        ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF)

/** allocate memory for the buffer and change the max length only if needed

    Note: this will always effectively clear all data.
          see ACR_VAR_BUFFER_CHANGE_MAX_LENGTH to change the max length
          without losing any data
*/
#define ACR_VAR_BUFFER_ALLOC(name, length)\
        if(name.m_MaxLength < length)\
		{\
			if(name.m_Buffer.m_Pointer != ACR_NULL)\
			{\
				if(ACR_HAS_FLAG(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE)\
				{\
					ACR_FREE(name.m_Buffer.m_Pointer);\
				}\
			}\
			name.m_Buffer.m_Pointer = (void*)ACR_MALLOC(length+1);\
			if(name.m_Buffer.m_Pointer != ACR_NULL)\
			{\
                ((ACR_Byte_t*)name.m_Buffer.m_Pointer)[length] = 0;\
				name.m_MaxLength = length;\
			}\
			else\
			{\
				name.m_MaxLength = ACR_ZERO_LENGTH;\
			}\
		    ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF);\
		}\
		name.m_Buffer.m_Length = ACR_ZERO_LENGTH

/** allocate memory for the buffer and change the max length
 *  while maintaining all data that is currently in the buffer
*/
#define ACR_VAR_BUFFER_CHANGE_MAX_LENGTH(name, length)\
        if(name.m_MaxLength != length)\
		{\
            if(length >= name.m_Buffer.m_Length)\
            {\
                void* tempPtr = name.m_Buffer.m_Pointer;\
                if(tempPtr != ACR_NULL)\
                {\
                    if(ACR_HAS_FLAG(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF))\
                    {\
                        tempPtr = ACR_NULL;\
                    }\
                }\
                tempPtr = (void*)ACR_REALLOC(tempPtr, length+1);\
                if(tempPtr != ACR_NULL)\
                {\
                    ((ACR_Byte_t*)tempPtr)[length] = 0;\
                    name.m_MaxLength = length;\
                    name.m_Buffer.m_Pointer = tempPtr;\
                    ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF);\
                }\
            }\
		}

#else

/** free is not available
*/
#define ACR_VAR_BUFFER_FREE(name) name.m_Buffer.m_Pointer = ACR_NULL; name.m_Buffer.m_Length = ACR_ZERO_LENGTH; name.m_MaxLength = ACR_ZERO_LENGTH; ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF)

/** malloc is not available
*/
#define ACR_VAR_BUFFER_ALLOC(name, length) name.m_Buffer.m_Pointer = ACR_NULL; name.m_Buffer.m_Length = ACR_ZERO_LENGTH; name.m_MaxLength = ACR_ZERO_LENGTH; ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF)

/** realloc is not available
*/
#define ACR_VAR_BUFFER_CHANGE_MAX_LENGTH(name, length)

#endif // #if ACR_HAS_MALLOC == ACR_BOOL_TRUE

#endif
