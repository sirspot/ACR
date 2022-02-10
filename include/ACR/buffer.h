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
/** \file buffer.h

    public functions for access to the ACR_BufferObj_t type

*/
#ifndef _ACR_BUFFER_H_
#define _ACR_BUFFER_H_

// included for ACR_Info_t
#include "ACR/public/public_info.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

// included for ACR_Byte_t
#include "ACR/public/public_bytes_and_flags.h"

/** predefined object type
*/
typedef struct ACR_BufferObj_s ACR_BufferObj_t;

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

/** prepare a buffer allocated on the heap
	Note: this automatically calls ACR_BufferInit() on the
	      new buffer after allocating its memory
	\param mePtr location to store the pointer for the new buffer
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	Note: memory for the buffer must be allocated
		  by calling ACR_BufferAllocate() or
		  referenced by calling ACR_BufferSetData()
		  before the buffer can be used effectively.
*/
ACR_Info_t ACR_BufferNew(
	ACR_BufferObj_t** mePtr);

/** free a buffer allocated on the heap
    Note: this automatically calls ACR_BufferDeInit() on
	      the buffer before freeing its memory
	\param mePtr location of the pointer for the buffer, which will
	       be set to ACR_NULL after the memory is freed
*/
void ACR_BufferDelete(
	ACR_BufferObj_t** mePtr);

/** allocate memory for the buffer
	\param me the buffer
	\param length value 1 to ACR_MAX_LENGTH
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	IMPORTANT: if the buffer already has memory allocated,
	           the memory will be freed before any new memory is allocated
*/
ACR_Info_t ACR_BufferAllocate(
	ACR_BufferObj_t* me,
	ACR_Length_t length);

/** use the specified memory for the buffer
	\param me the buffer
	\param ptr pointer to the start of the memory to access
	\param length the length of the memory at ptr 1 to ACR_MAX_LENGTH
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	IMPORTANT: if the buffer has memory allocated,
			   the memory will be freed before the reference is set
*/
ACR_Info_t ACR_BufferSetData(
	ACR_BufferObj_t* me,
	void* ptr,
	ACR_Length_t length);

/** get the buffer length
	\param me the buffer
	\returns the buffer length
	Note: if me is ACR_NULL the buffer length returned is still 0
*/
ACR_Length_t ACR_BufferGetLength(
	ACR_BufferObj_t* me);

/** clear the buffer by filling with ACR_EMPTY_VALUE
	\param me the buffer
*/
void ACR_BufferClear(
	ACR_BufferObj_t* me);

/** copy from one buffer to another
	\param me the buffer to copy from. this is the source of the data
	\param srcPos the position within the source buffer to copy from
	\param dest the buffer to copy to. this is the destination of the data
	\param destPos the position in the destination buffer to copy to
	\param length the number of bytes to copy
	\returns ACR_INFO_OK on success
	         or ACR_INFO_GREATER if srcPos + length is greater than the source buffer length
	         or ACR_INFO_LESS if destPos + length is greater than the destination buffer length
			 or ACR_INFO_INVALID if either buffer has no memory
			 or ACR_INFO_ERROR
*/
ACR_Info_t ACR_BufferCopyToBuffer(
	ACR_BufferObj_t* me,
	ACR_Length_t srcPos,
	ACR_BufferObj_t* dest,
	ACR_Length_t destPos,
	ACR_Length_t length);

/** copy from a buffer into any memory location
	\param me the buffer to copy from. this is the source of the data
	\param srcPos the position within the source buffer to copy from
	\param destPtr a pointer to the location in memory to copy to.
	               this is the destination of the data
	\param destLength the amount of space available at the destination
	                  memory address. this value must be greater than
					  or equal to length or the copy will not occur
	\param length the number of bytes to copy
	\returns ACR_INFO_OK on success
	         or ACR_INFO_GREATER if srcPos + length is greater than the source buffer length
	         or ACR_INFO_LESS if destLength is less than length
			 or ACR_INFO_INVALID if either buffer has no memory or destPtr is ACR_NULL
			 or ACR_INFO_ERROR
*/
ACR_Info_t ACR_BufferCopyToMemory(
	ACR_BufferObj_t* me,
	ACR_Length_t srcPos,
	void* destPtr,
	ACR_Length_t destLength,
	ACR_Length_t length);

/** set the byte value at the specified position
	\param me the buffer
	\param pos the position in the buffer
	\param value the value
	\returns ACR_INFO_OK
	         or ACR_INFO_GREATER if pos is too large
			 or ACR_INFO_INVALID if the buffer has no memory
	         or ACR_INFO_ERROR
*/
ACR_Info_t ACR_BufferSetByteAt(
	ACR_BufferObj_t* me,
	ACR_Length_t pos,
	ACR_Byte_t value);

/** get the byte value at the specified position
	\param me the buffer
	\param pos the position in the buffer
	\param value the location to store the value
	\returns ACR_INFO_OK
	         or ACR_INFO_GREATER if pos is too large
			 or ACR_INFO_INVALID if the buffer has no memory
	         or ACR_INFO_ERROR
*/
ACR_Info_t ACR_BufferGetByteAt(
	ACR_BufferObj_t* me,
	ACR_Length_t pos,
	ACR_Byte_t* value);

/** shift all data in the buffer
	\param me the buffer
	\param shiftBytes the number of bytes to shift by
	       Note: if this value is larger than ACR_BUFFER_BYTE_COUNT_PER_SHIFT
		         defined in ACR/private/private_buffer.h then a shift with
				 wrap set to ACR_BOOL_TRUE will be less effecient. you may
				 override this value in your project settings to find the
				 best per-shift maximum for your application
	\param direction ACR_INFO_LEFT or ACR_INFO_RIGHT
	\param wrap set to ACR_BOOL_TRUE if the data shifted right should
		   be copied to the left or ACR_BOOL_FALSE to make no effort
		   to save the data shifted out of the buffer, which will fill
		   the free space with empty data
*/
void ACR_BufferShift(
	ACR_BufferObj_t* me,
	ACR_Length_t shiftBytes,
	ACR_Info_t direction,
	ACR_Bool_t wrap);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
