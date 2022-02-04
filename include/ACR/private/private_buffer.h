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
/** \file buffer_private.h

    private functions for access to the ACR_BufferObj_t type

*/
#ifndef _ACR_PRIVATE_BUFFER_H_
#define _ACR_PRIVATE_BUFFER_H_

#include "ACR/buffer.h"

// included for ACR_Buffer_t
#include "ACR/public/public_buffer.h"

#ifndef ACR_BUFFER_BYTE_COUNT_PER_SHIFT
/** this is used by ACR_BufferShiftLeft() and ACR_BufferShiftRight() to
    determine the amount of stack memory used for a temporary location to
	store data during the shift operation.  the actual shift can be larger
	than this number but will occur in a tight loop instead of a single
	copy operation
*/
#define ACR_BUFFER_BYTE_COUNT_PER_SHIFT 256
#endif

/** private buffer type
*/
struct ACR_BufferObj_s
{
    ACR_Buffer_t m_Base;
};

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
extern "C" {                                              //
#endif                                                    //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS
//
////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
