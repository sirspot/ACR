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

/** \file public_info.h
 
    This header contains types and values for common informational
    values. These are useful for making code more readable.
    It can be used standalone from the entire library or is
    included automatically with public.h

*/
#ifndef _ACR_PUBLIC_INFO_H_
#define _ACR_PUBLIC_INFO_H_

/** info values that can be used instead of
    true or false for options and return values

    for variable init:

        ACR_Info_t result = ACR_INFO_UNKNOWN;

    for comparison:

        if(result == ACR_INFO_YES)
        {
            // the result is yes
        }
        else if(result == ACR_INFO_NO)
        {
            // the result is no
        }
        else
        {
            // an unexpected result
        }

    special case for boolean values

        only use ACR_INFO_TRUE and ACR_INFO_FALSE to check
        explicitly for those values. see notes on
        ACR_BOOL_FALSE for other boolean comparisons

        good example:

        ACR_Info_t success = ACR_INFO_FALSE;
        if(success == ACR_INFO_TRUE)
        {
            // success
        }
        else
        {
            // no success
        }

        bad example:

        ACR_Info_t success = ACR_INFO_FALSE;
        // Note: this is a bad example because this non-zero
        //       success value will be interpreted as "true"
        //       even though the intention was for it to be
        //       a false value
        if(success)
        {
            // success
        }
        else
        {
            // no success
        }

    special case for program or thread return value:

        use ACR_SUCCESS for successful execution
        and any other return codes can be used as
        an error.
        see ACR/public/public_functions.h for details.

        do not use 0, ACR_INFO_EQUAL, or ACR_INFO_OK as
        a program or thread return code because they are
        either confusing or will not have the intended
        results

        good example:

        // program or thread exit with no error
        return ACR_SUCCESS;

        good example:

        // program or thread exit error
        return ACR_INFO_ERROR;

        bad example:

        // program or thread exit with no error
        // Note: this is a bad example because this non-zero
        //       return value will be interpreted as an
        //       error
        return ACR_INFO_OK;

*/
typedef enum ACR_Info_e
{
    //
    // COMPARISON
    //
    ACR_INFO_EQUAL = 0,
    ACR_INFO_NOT_EQUAL,
    ACR_INFO_LESS,
    ACR_INFO_GREATER,
    ACR_INFO_UNKNOWN,

    //
    // POSITIVE,       NEGATIVE
    //
    ACR_INFO_TRUE, ACR_INFO_FALSE,
    ACR_INFO_OK, ACR_INFO_ERROR,
    ACR_INFO_ENABLED, ACR_INFO_DISABLED,
    ACR_INFO_YES, ACR_INFO_NO,
    ACR_INFO_ON, ACR_INFO_OFF,
    ACR_INFO_START, ACR_INFO_STOP,
    ACR_INFO_ACCEPT, ACR_INFO_IGNORE,
    ACR_INFO_VALID, ACR_INFO_INVALID,
    ACR_INFO_ALL, ACR_INFO_NONE,
    ACR_INFO_OPEN, ACR_INFO_CLOSED,

    //
    // POSITION
    //
    ACR_INFO_TOP, ACR_INFO_BOTTOM,
    ACR_INFO_FIRST, ACR_INFO_LAST,
    ACR_INFO_PREVIOUS, ACR_INFO_NEXT,
    ACR_INFO_CURRENT,

    // DIRECTION
    ACR_INFO_UP, ACR_INFO_DOWN,
    ACR_INFO_LEFT, ACR_INFO_RIGHT,

    // AGE
    ACR_INFO_OLD, ACR_INFO_NEW,

    // INSTRUCTION
    ACR_INFO_BEGIN,
    ACR_INFO_READY,
    ACR_INFO_WAIT,
    ACR_INFO_GO,
    ACR_INFO_END,

    // MODE
    ACR_INFO_READ,
    ACR_INFO_WRITE,
    ACR_INFO_READ_WRITE,

    ACR_INFO_COUNT

} ACR_Info_t;

#endif
