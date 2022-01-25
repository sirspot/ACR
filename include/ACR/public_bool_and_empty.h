/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2021 Adam C. Rosenberg

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

/** \file public_bool_and_empty.h
 
    This header contains types and values for boolean
    and empty values. It can be used standalone
    from the entire library or is included automatically
    with public.h

    See public.h for more information.

*/
#ifndef _ACR_PUBLIC_BOOL_AND_EMPTY_H_
#define _ACR_PUBLIC_BOOL_AND_EMPTY_H_

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - BOOLEAN (TRUE/FALSE) AND EMPTY VALUES
//
////////////////////////////////////////////////////////////

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
#define ACR_BOOL_FALSE 0

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
#define ACR_BOOL_TRUE 1

/** use this type only for ACR_BOOL_FALSE or ACR_BOOL_TRUE
*/
typedef char ACR_Bool_t;

/** represents an empty value.
    use this instead of 0 to clearly indicate the value
    is being used to identify an empty value

    for memory init:

        char data[64];
        ACR_MEMSET(data, ACR_EMPTY_VALUE, sizeof(data));
        
    for variable init:

        int selected = ACR_EMPTY_VALUE;

    for comparison:

        if(data[0] == ACR_EMPTY_VALUE)
        {
            // nothing has been written to the data
        }

        if(selected == ACR_EMPTY_VALUE)
        {
            // nothing has been selected
        }

*/
#define ACR_EMPTY_VALUE 0

#endif
