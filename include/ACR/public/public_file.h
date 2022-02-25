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

/** \file public_file.h
 
    This header helps define a generic interface to files whether
    they are in memory, part of a file system, or streamed across
    a network connection.
    It is included automatically with public.h
    
*/
#ifndef _ACR_PUBLIC_FILE_H_
#define _ACR_PUBLIC_FILE_H_

// included for ACR_TYPEDEF_CALLBACK()
#include "ACR/public/public_functions.h"

// included for ACR_VarBuffer_t
#include "ACR/public/public_varbuffer.h"

// included for ACR_Info_t
#include "ACR/public/public_info.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

// included for ACR_String_t
#include "ACR/public/public_string.h"

/** callback function type for reading data from a file
    \param dest destination of the data
        dest->m_MaxLength must be set before calling this function to
                          the max number of bytes to read
        dest->m_Buffer.m_Pointer must be set before calling this function
                                 to the location for the callback 
                                 to store the data read from the file
        dest->m_Buffer.m_Length must be set by the callback 
                                to the number of bytes actually read
                                if the return value is ACR_INFO_OK
    \param userPtr optional user pointer
    \returns ACR_INFO_OK if 0 or more bytes are read
             Note: check src->m_Buffer.m_Length for
                   the exact number of bytes.
            ACR_INFO_ERROR if any error occurs.
*/
ACR_TYPEDEF_CALLBACK(ACR_FileCallbackRead_t, ACR_Info_t)(
    ACR_VarBuffer_t* dest,
    void* userPtr);

/** callback function type for writing data to a file
    \param src source of the data
        src->m_MaxLength must be set before calling this function to
                         the max number of bytes to write
        src->m_Buffer.m_Pointer must be set before calling this function
                                to the location of the data that the
                                callback will to write to the file
        src->m_Buffer.m_Length must be set by the callback
                               to the number of bytes actually written
                               if the return value is ACR_INFO_OK
    \param userPtr optional user pointer
    \returns ACR_INFO_OK if 0 or more bytes are written
             Note: check src->m_Buffer.m_Length for
                   the exact number of bytes.
             ACR_INFO_ERROR if any error occurs.
*/
ACR_TYPEDEF_CALLBACK(ACR_FileCallbackWrite_t, ACR_Info_t)(
    ACR_VarBuffer_t* src,
    void* userPtr);

/** callback function type for moving the read or write position within a file
    \param moveBy number of bytes to move the position
    \param fromPos starting position ACR_INFO_FIRST, ACR_INFO_CURRENT, or ACR_INFO_LAST
                   Note: when ACR_INFO_LAST is set the moveBy value must move
                         the position backwards from the end of the file
    \param userPtr optional user pointer
    \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_TYPEDEF_CALLBACK(ACR_FileCallbackSeek_t, ACR_Info_t)(
    ACR_Length_t moveBy,
    ACR_Info_t fromPos,
    void* userPtr);

/** callback function type for opening a file
    \param path path to the file
    \param mode ACR_INFO_READ, ACR_INFO_WRITE, or ACR_INFO_READ_WRITE
    \param fileHandle optional location for the callback to store
                      a file handle for the open file 
                      if ACR_INFO_OK is returned
    \param userPtr optional user pointer
    \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_TYPEDEF_CALLBACK(ACR_FileCallbackOpen_t, ACR_Info_t)(
    ACR_String_t path,
    ACR_Info_t mode,
    void** fileHandle,
    void* userPtr);

/** callback function type for closing a file
    \param fileHandle optional location of the file handle for
                      the open file to be closed
    \param userPtr optional user pointer
    \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_TYPEDEF_CALLBACK(ACR_FileCallbackClose_t, ACR_Info_t)(
    void** fileHandle,
    void* userPtr);

/** type for a complete interface to a file
*/
typedef struct ACR_InterfaceFile_s
{
    ACR_FileCallbackOpen_t m_Open;
    ACR_FileCallbackClose_t m_Close;
    ACR_FileCallbackRead_t m_Read;
    ACR_FileCallbackWrite_t m_Write;
    ACR_FileCallbackSeek_t m_Seek;
} ACR_FileInterface_t;

/** define a file interface on the stack with the specified name
*/
#define ACR_FILE_INTERFACE(name) ACR_FileInterface_t name = {ACR_NULL,ACR_NULL,ACR_NULL,ACR_NULL,ACR_NULL}

#endif
