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

/** \file public_version.h
 
    This header contains the version of the library
    and performs checks for the version of the compiler standard

*/
#ifndef _ACR_PUBLIC_VERSION_H_
#define _ACR_PUBLIC_VERSION_H_

/*

    ACR LIBRARY VERSION INFORMATION

*/

/** 2026-11-09 1.1.1 added ACR library version info
*/
#define ACR_MAJOR_VERSION 1

/** 2026-11-09 1.1.1 added ACR library version info
*/
#define ACR_MINOR_VERSION 1

/** 2026-11-09 1.1.1 added ACR library version info
*/
#define ACR_PATCH_VERSION 1

/*

    C STANDARD VERSION INFORMATION

*/

/** C89 released in 1989 was first formal standard approved
    by ANSI ( American National Standards Institute ).
    this is considered strict ANSI C by most compilers
*/
#define ACR_C_VERSION_89 0

/** C90 released in 1990 was the same as C89 but approved 
    by ISO ( International Organization for Standardization )
*/
#define ACR_C_VERSION_90 2

/** C95 released in 1995 added support for wide character data 
    type and digraphs ( like <% %> instead of { } ).
    Note: trigraphs already existed, but those have been removed
          from C23 while digraphs are still supported at the time
          this was written. the only reason for these preprocessor
          sequences is for keyboards that don't have the
          symbols available directly.
*/
#define ACR_C_VERSION_95 4

/** C99 released in 1999 added declarations allowed anywhere
    in code. This means variables don't have to be defined at the
    start of a block. It also introduced the long long type and 
    single line comments. This version is a good choice when
    the highest level of compatibility to desired.
*/
#define ACR_C_VERSION_99 6

/** C11 released in 2011 added thread support and atomic types.
    It also expanded macro support by adding _Generic to provide 
    type checking.
*/
#define ACR_C_VERSION_11 8

/** C17 released in 2018 fixes some undefined behaviors in C11
    but is essentially the same. As of 2026, most compilers support
    this version.
*/
#define ACR_C_VERSION_17 10

/** C23 released in 2024 added #embed for including binaries in code.
    it also adds typeof, bit utilities, %b for binary formatting in printf,
    and more features. The problem is that implementation lags behind the
    standard so even at the end of 2026 there are some compilers that have
    not yet implemented the entire standard.
*/
#define ACR_C_VERSION_23 12

/* determine which version of the C standard is in use.
   and store it as ACR_C_VERSION for easy reference
*/
#if defined(__cplusplus)
    // C++ does not define __STDC_VERSION__; use the C99 compatibility baseline.
    // Note: since ACR is designed to be used as a C library, it is better to
    //       compile it with a C compiler and link it to your C++ program instead
    #define ACR_C_VERSION ACR_C_VERSION_99
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
    #define ACR_C_VERSION ACR_C_VERSION_23
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201710L
    #define ACR_C_VERSION ACR_C_VERSION_17
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #define ACR_C_VERSION ACR_C_VERSION_11
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define ACR_C_VERSION ACR_C_VERSION_99
#else
    // unknown standard C version.
    // defaulting to strict ANSI C (which, unfortunately,
    // is not supported by this library)
    #define ACR_C_VERSION ACR_C_VERSION_89
#endif

#if ACR_C_VERSION < ACR_C_VERSION_99
    #error "The ACR library requires C99 or higher. Check ACR_C_VERSION in public_version.h for details."
#endif

#endif
