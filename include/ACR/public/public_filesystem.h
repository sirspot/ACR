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

/** \file public_filesystem.h
 
    This header provides access to the file system when available.
    It is included automatically with public.h
    
    This header gaurantees the following will be defined:
    ACR_HAS_FILESYSTEM     as either ACR_BOOL_TRUE or ACR_BOOL_FALSE
    ACR_File_t             for file data

*/
#ifndef _ACR_PUBLIC_FILESYSTEM_H_
#define _ACR_PUBLIC_FILESYSTEM_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public/public_bool.h"

// included for ACR_COMPILER_CLANG, ACR_COMPILER_GCC, ACR_COMPILER_VS2017
#include "ACR/public/public_config.h"

// included for ACR_Buffer_t
#include "ACR/public/public_buffer.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

// defines ACR_HAS_FILESYSTEM and includes stdio.h if desired
#ifndef ACR_CONFIG_NO_FILESYSTEM
    #ifndef ACR_CONFIG_NO_LIBC

        #define ACR_HAS_FILESYSTEM ACR_BOOL_TRUE

        // included for FILE, fopen(), fclose(), fread(), fwrite(), and fseek()
        #include <stdio.h>

        /** get the file length in bytes
            \param path path as a null-terminated string
            \param length ACR_Length_t to store the file length is bytes
        */
        #define ACR_FILESYSTEM_FILE_LENGTH(path,length)\
        {\
            FILE* file = fopen(path,"r");\
            if(file)\
            {\
                fseek(file, 0, SEEK_END);\
                length = (ACR_Length_t)ftell(file);\
                fclose(file);\
            }\
            else\
            {\
                length = 0;\
            }\
        }

        /** read from the file system
            \param path path as a null-terminated string
            \param length ACR_Length_t to store the number of bytes read
            \param buffer ACR_Buffer_t to read into
            \param startPos position to begin reading within the file starting at 0
        */
        #define ACR_FILESYSTEM_FILE_READ(path,length,buffer,startPos)\
        {\
            FILE* file = fopen(path,"r");\
            length = 0;\
            if(file)\
            {\
                ACR_Byte_t* bytePtr = (ACR_Byte_t*)buffer.m_Pointer;\
                fseek(file,startPos,SEEK_SET);\
                while(length < buffer.m_Length)\
                {\
                    int byte = fgetc(file);\
                    if(byte == EOF)\
                    {\
                        break;\
                    }\
                    length += 1;\
                    (*bytePtr) = (ACR_Byte_t)byte;\
                    bytePtr += 1;\
                }\
                fclose(file);\
            }\
        }

        /** write to the file system
            \param path path as a null-terminated string
            \param length ACR_Length_t to store the number of bytes written
            \param buffer ACR_Buffer_t to write from
            \param append ACR_BOOL_TRUE to append to any existing file or
                          ACR_BOOL_FALSE to clear any existing file before writing
        */
        #define ACR_FILESYSTEM_FILE_WRITE(path,length,buffer,append)\
        {\
            FILE* file = fopen(path,append?"a":"w");\
            length = 0;\
            if(file)\
            {\
                ACR_Byte_t* bytePtr = (ACR_Byte_t*)buffer.m_Pointer;\
                while(length < buffer.m_Length)\
                {\
                    int byte = fputc((int)(*bytePtr),file);\
                    if(byte == EOF)\
                    {\
                        break;\
                    }\
                    length += 1;\
                    bytePtr += 1;\
                }\
                fclose(file);\
            }\
        }

    #else
        // without libc there is no interface to a standard
        // operating system's file system.
    #endif // #ifndef ACR_CONFIG_NO_LIBC
#endif // #ifndef ACR_CONFIG_NO_FILESYSTEM

#ifndef ACR_HAS_FILESYSTEM
    #define ACR_HAS_FILESYSTEM ACR_BOOL_FALSE
#endif // #ifndef ACR_HAS_FILESYSTEM

#if ACR_HAS_FILESYSTEM == ACR_BOOL_FALSE

    #define ACR_FILESYSTEM_FILE_LENGTH(path,length) length = 0
    #define ACR_FILESYSTEM_FILE_READ(path,length,buffer,startPos) length = 0
    #define ACR_FILESYSTEM_FILE_WRITE(path,length,buffer,append) length = 0

#endif // #if ACR_HAS_FILESYSTEM == ACR_BOOL_TRUE

#endif
