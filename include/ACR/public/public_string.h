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

/** \file public_string.h
 
    This header provides a data type and macros to
    work with variable length data buffers.
    It is included automatically with public.h

    This header gaurantees the following will be defined:
    ACR_String_t          for string data
    ACR_Unicode_t         for unicode characters

*/
#ifndef _ACR_PUBLIC_STRING_H_
#define _ACR_PUBLIC_STRING_H_

// included for ACR_ZERO_LENGTH and ACR_NULL
#include "ACR/public/public_memory.h"

// included for ACR_Buffer_t, ACR_BUFFER_SET_DATA, and ACR_BUFFER_FLAGS_NONE
#include "ACR/public/public_buffer.h"

// included for ACR_Count_t and ACR_ZERO_COUNT
#include "ACR/public/public_count.h"

/** type for string data

    Note: disable warning C4820: padding added after data member
*/
typedef struct ACR_String_s
{
    ACR_Buffer_t m_Buffer;
    ACR_Count_t m_Count;
} ACR_String_t;

/** define a string on the stack with the specified name
*/
#define ACR_STRING(name) ACR_String_t name = {{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE},ACR_ZERO_COUNT};

/** assign memory to the string
*/
#define ACR_STRING_SET_DATA(name, memory, length, count) ACR_BUFFER_SET_DATA(name.m_Buffer, memory, length); name.m_Count = count;

/** type for unicode characters
*/
typedef unsigned long ACR_Unicode_t;

/** given the first UTF8 byte value determine the number of
    bytes uses to encode the character
*/
#define ACR_UTF8_BYTE_COUNT(c) (((c & 0x80) != 0)?((c & 0x40) != 0)?((c & 0x20) != 0)?((c & 0x10) != 0)?4:3:2:1:1)

/** mark the string as read only
*/
#define ACR_STRING_SET_READ_ONLY(name, readOnly) ACR_BUFFER_SET_READ_ONLY(name.m_Buffer, readOnly)

/** check if the string is marked read only
*/
#define ACR_STRING_IS_READ_ONLY(name) ACR_BUFFER_IS_READ_ONLY(name.m_Buffer)

#endif
