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
/** \file filesystem.h

    public functions for access to the ACR_FilesystemObj_t type

*/
#ifndef _ACR_FILESYSTEM_H_
#define _ACR_FILESYSTEM_H_

// included for ACR_String_t
#include "ACR/public/public_string.h"

/** predefined object type for the filesystem
*/
typedef struct ACR_FilesystemObj_s ACR_FilesystemObj_t;

/** predefined object type for files
*/
typedef struct ACR_FilesystemFileObj_s ACR_FilesystemFileObj_t;

/** predefined object type for folders
*/
typedef struct ACR_FilesystemFolderObj_s ACR_FilesystemFolderObj_t;

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
extern "C" {                                              //
#endif                                                    //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - FILESYSTEM
//
////////////////////////////////////////////////////////////

/** allocate filesystem data
	\param mePtr location to store the pointer
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_FilesystemNew(
	ACR_FilesystemObj_t** mePtr);

/** free a filesystem data
	\param mePtr location of the pointer, which will
	       be set to ACR_NULL after the memory is freed

    Note: all ACR_FilesystemFileObj_t and ACR_FilesystemFolderObj_t
          objects from this file system will also be deleted
*/
void ACR_FilesystemDelete(
	ACR_FilesystemObj_t** mePtr);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - FILES
//
////////////////////////////////////////////////////////////

/** get a file object for the specified path
    \param me the filesystem
    \param path the path to the file. it does not need to exist.
    \returns a pointer to a file object or ACR_NULL if an error occurs
*/
ACR_FilesystemFileObj_t* ACR_FilesystemGetFile(
    ACR_FilesystemObj_t* me,
    ACR_String_t path);

/** get the parent filesystem of this file object
    \param me the file
    \returns a pointer to the filesystem object
*/
ACR_FilesystemObj_t* ACR_FilesystemFileGetParent(
    ACR_FilesystemFileObj_t* me);

/** get the folder of this file object
    \param me the file
    \returns a pointer to the folder object or ACR_NULL if an error occurs
*/
ACR_FilesystemFolderObj_t* ACR_FilesystemFileGetFolder(
    ACR_FilesystemFileObj_t* me);

/** get the path of this file object
    \param me the file
    \returns the file path as a string
*/
ACR_String_t ACR_FilesystemFileGetPath(
    ACR_FilesystemFileObj_t* me);

/** check if the file exists
    \param me the file
    \returns ACR_BOOL_TRUE or ACR_BOOL_FALSE
*/
ACR_Bool_t ACR_FilesystemFileExists(
    ACR_FilesystemFileObj_t* me);

/** get the length of the file in bytes
    \param me the file
    \returns the length or 0 if the file does not exist
    \see ACR_FilesystemFileExists()
*/
ACR_Length_t ACR_FilesystemFileGetLength(
    ACR_FilesystemFileObj_t* me);

/** attempt to remove the file from the filesystem
    such as moving it to the trash or deleting it entirely
    depending on what the operating system allows
    \param me the file
    \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_FilesystemFileRemove(
    ACR_FilesystemFileObj_t* me);
    
/** attempt to rename the file by moving it from
    its current path to the specified path
    \param me the file
    \param path the new path
    \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_FilesystemFileRename(
    ACR_FilesystemFileObj_t* me,
    AMI_String_t path);
    
/** check if the file is open
    \param me the file
    \returns ACR_BOOL_TRUE or ACR_BOOL_FALSE
    Note: this is the same as calling (ACR_FilesystemFileGetMode() != ACR_INFO_CLOSED)
*/
ACR_Bool_t ACR_FilesystemFileIsOpen(
    ACR_FilesystemFileObj_t* me);

/** get the file mode
    \param me the file
    \returns ACR_INFO_CLOSED or ACR_INFO_READ or ACR_INFO_WRITE or ACR_INFO_READ_WRITE
*/
ACR_Info_t ACR_FilesystemFileGetMode(
    ACR_FilesystemFileObj_t* me);
    
/** seek within an open file
    \param me the file
    \param moveBy the number of bytes to move by
    \param fromPos starting position ACR_INFO_FIRST, ACR_INFO_CURRENT, or ACR_INFO_LAST
                   Note: when ACR_INFO_LAST is set the moveBy value moves
                         the position backwards from the end of the file
    \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_FilesystemFileSeek(
    ACR_FilesystemFileObj_t* me,
    ACR_Length_t moveBy,
    ACR_Info_t fromPos);
    
/** get the current position within the open file as
    bytes from the start of the file
    \param me the file
    \returns the position or 0 if the file is not open
    \see ACR_FilesystemFileIsOpen()
*/
ACR_Length_t ACR_FilesystemFileGetLength(
    ACR_FilesystemFileObj_t* me);

/**
*/
ACR_Info_t ACR_FilesystemFileRead(
    ACR_FilesystemFileObj_t* me,
    ACR_VarBuffer_t* dest);
    
/**
*/
ACR_Info_t ACR_FilesystemFileWrite(
    ACR_FilesystemFileObj_t* me,
    ACR_VarBuffer_t* src);
    
/**
*/
ACR_Info_t ACR_FilesystemFileOpen(
    ACR_FilesystemFileObj_t* me,
    ACR_Info_t mode);
    
/**
*/
ACR_Info_t ACR_FilesystemFileClose(
    ACR_FilesystemFileObj_t* me);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - FOLDERS
//
////////////////////////////////////////////////////////////

/** get a folder object for the specified path
    \param me the filesystem
    \param path the path to the folder. it does not need to exist.
    \returns a pointer to a folder object or ACR_NULL if an error occurs
*/
ACR_FilesystemFolderObj_t* ACR_FilesystemGetFolder(
    ACR_FilesystemObj_t* me,
    AMIString_t* path);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
