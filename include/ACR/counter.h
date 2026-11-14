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

/** \file counter.h

    Functions for accessing global and local counters.

*/
#ifndef _ACR_COUNTER_H_
#define _ACR_COUNTER_H_

// included for ACR_Bool_t
#include "ACR/public/public_bool.h"

// included for ACR_Count_t and ACR_Counter_t
#include "ACR/public/public_count.h"

#ifdef __cplusplus
extern "C" {
#endif

/** get the current global counter
    \returns a value ACR_ZERO_COUNT to (ACR_MAX_COUNT-1)
*/
ACR_Count_t ACR_GlobalCounter(void);

/** get the next global counter value
    \param value location to store the value
    \returns ACR_BOOL_TRUE if the value is ok or ACR_BOOL_FALSE if
             no more values exist, which means value has been set
             back to the first value
*/
ACR_Bool_t ACR_GlobalCounterNext(
    ACR_Count_t* value);

/** get the first counter value
    \param me the counter
    \param value location to store the value
    \returns ACR_BOOL_TRUE if the value is ok or ACR_BOOL_FALSE if
             no values exist which means the counter is invalid
*/
ACR_Bool_t ACR_CounterFirst(
    ACR_Counter_t* me,
    ACR_Count_t* value);

/** get the next counter value
    \param me the counter
    \param value location to store the value
    \returns ACR_BOOL_TRUE if the value is ok or ACR_BOOL_FALSE if
             no more values exist, which means value has been set
             back to the first value
*/
ACR_Bool_t ACR_CounterNext(
    ACR_Counter_t* me,
    ACR_Count_t* value);

#ifdef __cplusplus
}
#endif

#endif
