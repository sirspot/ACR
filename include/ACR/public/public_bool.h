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

/** \file public_bool.h
 
    This header contains types and values for boolean
    and empty values. It can be used standalone
    from the entire library or is included automatically
    with public.h

*/
#ifndef _ACR_PUBLIC_BOOL_H_
#define _ACR_PUBLIC_BOOL_H_

#include "ACR/public/public_version.h"

#if ACR_C_VERSION < ACR_C_VERSION_23
    // only C23 has the bool datatype built-in.
    // earlier versions such as C99 use an additional header.
    #ifndef ACR_CONFIG_NO_LIBC
        #include <stdbool.h>
        #define ACR_CONFIG_INTERNAL_BOOL_BUILTIN
    #endif
#else
    #define ACR_CONFIG_INTERNAL_BOOL_BUILTIN
#endif

/** represents a false boolean result

    example:

        if(ACR_BOOL_FALSE)
        {
            // never reaches this code
        }
        else
        {
            // always reaches this code
        }

*/
#ifdef ACR_CONFIG_INTERNAL_BOOL_BUILTIN
    #define ACR_BOOL_FALSE false
#else
    #define ACR_BOOL_FALSE 0
#endif

/** represents a true boolean result

    example:

        if(ACR_BOOL_TRUE)
        {
            // always reaches this code
        }
        else
        {
            // never reaches this code
        }

*/
#ifdef ACR_CONFIG_INTERNAL_BOOL_BUILTIN
    #define ACR_BOOL_TRUE true
#else
    #define ACR_BOOL_TRUE 1
#endif

/** use this type only for ACR_BOOL_FALSE or ACR_BOOL_TRUE
*/
#ifdef ACR_CONFIG_INTERNAL_BOOL_BUILTIN
    typedef bool ACR_Bool_t;
#else
    typedef char ACR_Bool_t;
#endif

#endif
