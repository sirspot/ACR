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

    functions for access to the ACR_Buffer_t type

*/
#ifndef _ACR_BUFFER_H_
#define _ACR_BUFFER_H_

#include "ACR/public.h"

#ifndef ACR_BUFFER_BYTE_COUNT_PER_SHIFT
/** this is used by ACR_BufferShiftLeft() and ACR_BufferShiftRight() to
    determine the amount of stack memory used for a temporary location to
	store data during the shift operation.  the actual shift can be larger
	than this number but will occur in a tight loop instead of a single
	copy operation
*/
#define ACR_BUFFER_BYTE_COUNT_PER_SHIFT 256
#endif

/** predefined buffer object type
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
		  referenced by calling ACR_BufferRef()
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

/** prepare a buffer

	Note: memory for the buffer must be allocated
		  by calling ACR_BufferAllocate() or
		  referenced by calling ACR_BufferRef()
		  before the buffer can be used effectively.
*/
void ACR_BufferInit(
	ACR_BufferObj_t* me);

/** free buffer memory
*/
void ACR_BufferDeInit(
	ACR_BufferObj_t* me);

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
	\length the length of the memory at ptr 1 to ACR_MAX_LENGTH
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	IMPORTANT: if the buffer has memory allocated,
			   the memory will be freed before the reference is set
*/
ACR_Info_t ACR_BufferRef(
	ACR_BufferObj_t* me,
	void* ptr,
	ACR_Length_t length);

/** clear the buffer by filling with ACR_EMPTY_VALUE
*/
void ACR_BufferClear(
	ACR_BufferObj_t* me);

/** shift all data in the buffer to the left by the specified length
*/
void ACR_BufferShiftLeft(
	ACR_BufferObj_t* me,
	ACR_Length_t length);

/** shift all data in the buffer to the right by the specified length
*/
void ACR_BufferShiftRight(
	ACR_BufferObj_t* me,
	ACR_Length_t length);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
