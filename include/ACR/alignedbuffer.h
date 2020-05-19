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
/** \file alignedbuffer.h

    functions for access to the ACR_AlignedBuffer_t type

*/
#ifndef _ACR_ALIGNEDBUFFER_H_
#define _ACR_ALIGNEDBUFFER_H_

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

/** prepare an aligned buffer allocated on the heap
	Note: this automatically calls ACR_AlignedBufferInit() on the
	      new buffer after allocating its memory
	\param mePtr location to store the pointer for the new buffer
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	Note: this creates the buffer object but the
	      memory for the buffer must be allocated
		  by calling ACR_AlignedBufferAllocate() or
		  referenced by calling ACR_AlignedBufferRef()
		  before it can be used effectively.
*/
ACR_Info_t ACR_AlignedBufferNew(
	ACR_AlignedBuffer_t** mePtr);

/** free an aligned buffer allocated on the heap
	\param mePtr location of the pointer for the buffer, which will
	       be set to ACR_NULL after the memory is freed

	Note: this automatically calls ACR_AlignedBufferDeInit() on
		  the buffer before freeing its memory
*/
void ACR_AlignedBufferDelete(
	ACR_AlignedBuffer_t** mePtr);

/** prepare an aligned buffer
	
	Note: memory for the buffer must be allocated
	      by calling ACR_AlignedBufferAllocate() or
		  referenced by calling ACR_AlignedBufferReference()
		  before it can be used effectively.
*/
void ACR_AlignedBufferInit(
	ACR_AlignedBuffer_t* me);

/** free aligned buffer memory
*/
void ACR_AlignedBufferDeInit(
	ACR_AlignedBuffer_t* me);

/// \todo ACR_AlignedBufferAllocate

/** set aligned memory by reference
	\param ptr pointer to the start of the memory to access
	\length the length of the memory at ptr 1 to ACR_MAX_LENGTH
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	Note: if the buffer already has memory allocated,
	      the memory will be freed before the reference is set
*/
ACR_Info_t ACR_AlignedBufferRef(
	ACR_AlignedBuffer_t* me,
	void* ptr,
	ACR_Length_t length);

/** get a reference to the aligned buffer
	\param me
	\param buffer location to store a reference to the aligned memory
	\returns ACR_INFO_OK or ACR_INFO_ERROR

	Note: the reference is only valid as long as the aligned buffer remains valid
	      so it is best to call ACR_AlignedBufferGet() each time access to the
		  aligned buffer is needed
*/
ACR_Info_t ACR_AlignedBufferGetRef(
	ACR_AlignedBuffer_t* me,
	ACR_Buffer_t* buffer);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
