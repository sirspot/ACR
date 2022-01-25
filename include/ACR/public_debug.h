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

/** \file public_debug.h
 
    This header provides debug printing.
    It is included automatically with public.h

    This header gaurantees the following will be defined:
    ACR_IS_DEBUG   as either ACR_BOOL_TRUE or ACR_BOOL_FALSE

*/
#ifndef _ACR_PUBLIC_DEBUG_H_
#define _ACR_PUBLIC_DEBUG_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public_bool.h"

#ifdef ACR_CONFIG_DEBUG
#define ACR_IS_DEBUG ACR_BOOL_TRUE
#ifdef ACR_COMPILER_VS2017
#pragma warning(push)
// disable warning C4710: 'int printf(const char *const ,...)': function not inlined (when it was requested)
#pragma warning(disable:4710)
#endif
// included for printf
// Note: this ignores ACR_CONFIG_NO_LIBC intentionally for debug only
#include <stdio.h>
#ifdef ACR_COMPILER_VS2017
#pragma warning(pop)
#endif
#define ACR_DEBUG_PRINT(number, format, ...) printf("%4d "format"\n", number, ##__VA_ARGS__)
#else
#define ACR_IS_DEBUG ACR_BOOL_FALSE
#define ACR_DEBUG_PRINT(number, format, ...)
#endif // #ifdef ACR_CONFIG_DEBUG

#endif
