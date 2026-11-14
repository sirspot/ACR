/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2026 Adam C. Rosenberg

    Please read LICENSE before using this code

    Please read README.md for instructions on including
    this code in your project and where to find examples

    If you contribute to this code, Please add your name
    and email address to the AUTHORS list below so that
    we know who to thank!

    AUTHORS

    Adam C. Rosenberg <adam@sirspot.com>

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

/** \file unicode.h

    Functions for working with UTF8 and Unicode characters.

*/
#ifndef _ACR_UNICODE_H_
#define _ACR_UNICODE_H_

// included for ACR_Info_t
#include "ACR/public/public_info.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

// included for ACR_Byte_t and ACR_Unicode_t
#include "ACR/public/public_string.h"

#ifdef __cplusplus
extern "C" {
#endif

/** selects the position of the next character
  \param mem the start of the UTF8 encoded string data
  \param memLength the length of mem (use ACR_MAX_LENGTH if unsure)
  \param pos current byte offset into the string, which
         will be updated to that of the next character if
         successful
  \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_Utf8NextChar(
    const ACR_Byte_t* mem,
    ACR_Length_t memLength,
    ACR_Length_t* pos);

/** selects the position of the previous character
  \param mem start of the UTF8 encoded string data
  \param memLength the length of mem (use ACR_MAX_LENGTH if unsure)
  \param pos current byte offset in the string, which will
         be updated to that of the previous character if
         successful
  \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_Utf8PrevChar(
    const ACR_Byte_t* mem,
    ACR_Length_t memLength,
    ACR_Length_t* pos);

/** convert a unicode character to its lower-case representation
*/
ACR_Unicode_t ACR_UnicodeToLower(
    ACR_Unicode_t unicode);

/** convert a unicode character to its upper-case representation
*/
ACR_Unicode_t ACR_UnicodeToUpper(
    ACR_Unicode_t unicode);

/** convert UTF8 encoded data to a unicode value
    \param mem a valid pointer to the UTF8 encoded character
           in memory
    \param bytes the number of bytes for this UTF8 encoded
           unicode value. use ACR_UTF8_BYTE_COUNT(mem[0])
           if unsure
    \returns the unicode value
*/
ACR_Unicode_t ACR_Utf8ToUnicode(
    const ACR_Byte_t* mem,
    int bytes);

#ifdef __cplusplus
}
#endif

#endif
