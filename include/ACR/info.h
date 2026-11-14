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

/** \file info.h

    Functions for converting informational values to and from strings.

*/
#ifndef _ACR_INFO_H_
#define _ACR_INFO_H_

// included for ACR_Info_t
#include "ACR/public/public_info.h"

// included for ACR_String_t
#include "ACR/public/public_string.h"

#ifdef __cplusplus
extern "C" {
#endif

/** get the info value as a string
    \param info the info value \see enum ACR_Info_e
    \returns a reference to a string
*/
ACR_String_t ACR_InfoToString(
    ACR_Info_t info);

/** get the info value from a string
    \param src a reference to a string
    \returns an info value from \see enum ACR_Info_e or
             ACR_INFO_UNKNOWN if not found
*/
ACR_Info_t ACR_InfoFromString(
    ACR_String_t src);

#ifdef __cplusplus
}
#endif

#endif
