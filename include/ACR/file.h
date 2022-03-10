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
/** \file file.h

    public functions that perform common operations on ACR_FileInterface_t

*/
#ifndef _ACR_FILE_H_
#define _ACR_FILE_H_

// included for ACR_String_t
#include "ACR/public/public_string.h"

// included for ACR_Info_t
#include "ACR/public/public_info.h"

// included for ACR_FileInterface_t
#include "ACR/public/public_file.h"

// included for ACR_VarBuffer_t
#include "ACR/public/public_varbuffer.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

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

/** get the file length.
    requires me->m_Position and me->m_Seek callbacks
    \param me the file interface, which must not be closed
    \returns the file length in bytes
    Note: 0 length can indicate the file has no bytes but
          may also indicate missing or failure of
          me->m_Position or me->m_Seek callbacks
*/
ACR_Length_t ACR_FileGetLength(
	ACR_FileInterface_t* me);

/** read the entire file into a buffer.
    requires me->m_Read callback and those required by ACR_FileGetLength()
    \param me the file interface, which must be ready to read
    \param buffer the buffer to read into. 
    \returns ACR_INFO_OK if buffer was allocated to the exact
             file size reported by ACR_FileGetLength() and
             the m_Read callback was able to read the reported
             number of bytes (other than 0).
             otherwise ACR_INFO_ERROR is returned.

             Note: if ACR_INFO_OK is returned the caller must
                   call ACR_BUFFER_FREE() or similar when done
                   with the data to release the allocated memory
*/
ACR_Info_t ACR_FileReadAll(
	ACR_FileInterface_t* me,
    ACR_Buffer_t* buffer);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
