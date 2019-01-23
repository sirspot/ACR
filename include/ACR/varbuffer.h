/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2019 Adam C. Rosenberg

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
/** \file varbuffer.h

    functions for access to the ACR_VarBuffer_t type

*/
#ifndef _ACR_VARBUFFER_H_
#define _ACR_VARBUFFER_H_

#include "ACR/public.h"

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

/** prepare a variable length buffer allocated on the heap
	Note: this automatically calls ACR_VarBufferInit() on the
	      new buffer after allocating its memory
	\param mePtr location to store the pointer for the new buffer
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	Note: this creates the buffer object but the
	      memory for the buffer must be allocated
		  by calling ACR_VarBufferAllocate() or
		  referenced by calling ACR_VarBufferRef()
		  before it can be used effectively.
*/
ACR_Info_t ACR_VarBufferNew(
	ACR_VarBuffer_t** mePtr);

/** free a variable length buffer allocated on the heap
	\param mePtr location of the pointer for the buffer, which will
	       be set to ACR_NULL after the memory is freed

	Note: this automatically calls ACR_VarBufferDeInit() on
		  the buffer before freeing its memory
*/
void ACR_VarBufferDelete(
	ACR_VarBuffer_t** mePtr);

/** prepare a variable length buffer
	
	Note: memory for the buffer must be allocated
	      by calling ACR_VarBufferAllocate() or
		  referenced by calling ACR_VarBufferReference()
		  before it can be used effectively.
*/
void ACR_VarBufferInit(
	ACR_VarBuffer_t* me);

/** free variable length buffer memory
*/
void ACR_VarBufferDeInit(
	ACR_VarBuffer_t* me);

/** get the max length of this variable sized buffer.
    if it is too small, call ACR_VarBufferAllocate()
	with the larger value.
*/
ACR_Length_t ACR_VarBufferGetMaxLength(
	ACR_VarBuffer_t* me);

/** allocate memory and increase the max length only if
	necessary, then reset the variable length buffer to ACR_ZERO_LENGTH
	\param me the buffer
	\param length value 1 to ACR_MAX_LENGTH
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	Note: data loss is possible. if length is greater than
		  ACR_VarBufferGetMaxLength() this will free the
		  existing memory before allocating enough memory for
		  the new length.
*/
ACR_Info_t ACR_VarBufferAllocate(
	ACR_VarBuffer_t* me,
	ACR_Length_t length);

/** set memory reference then reset the variable
    length buffer to ACR_ZERO_LENGTH
	\param ptr pointer to the start of the memory to access
	\length the length of the memory at ptr 1 to ACR_MAX_LENGTH
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	Note: if the buffer already has memory allocated,
	      the memory will be freed before the reference is set
*/
ACR_Info_t ACR_VarBufferRef(
	ACR_VarBuffer_t* me,
	void* ptr,
	ACR_Length_t length);

/** set the length of the variable length buffer
	\param me the variable length buffer
	\param length the new length of the buffer 0 to ACR_VarBufferGetMaxLength()
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	Note: if a larger buffer is needed see ACR_VarBufferAllocate()
*/
ACR_Info_t ACR_VarBufferSetLength(
	ACR_VarBuffer_t* me,
	ACR_Length_t length);

/** copy data to the end of the buffer
	\param me
	\param srcPtr a pointer to the memory location to copy from or
				  ACR_NULL to add to the buffer length without copying data
	\param length the number of bytes to copy from srcPtr
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_VarBufferAppend(
	ACR_VarBuffer_t* me,
	void* srcPtr,
	ACR_Length_t length);

/** copy data to the start of the buffer
	\param me
	\param srcPtr a pointer to the memory location to copy from or
				  ACR_NULL to add to the buffer length without copying data
	\param length the number of bytes to copy from srcPtr
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_VarBufferPrepend(
	ACR_VarBuffer_t* me,
	void* srcPtr,
	ACR_Length_t length);

/** clear the current length of this variable length buffer by filling
    with ACR_EMPTY_VALUE
*/
void ACR_VarBufferClear(
	ACR_VarBuffer_t* me);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
