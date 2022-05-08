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

/** \file public_count.h
 
    This header contains types and values for counting.
    It can be used standalone from the entire library or is
    included automatically with public.h

*/
#ifndef _ACR_PUBLIC_COUNT_H_
#define _ACR_PUBLIC_COUNT_H_

/** type for a typical count such as the number of items in an array
    \see ACR_MAX_COUNT for the maximum value that can be
    stored by this data type
*/
typedef unsigned long ACR_Count_t;

/** used for setting a count explicitly to zero
*/
#define ACR_ZERO_COUNT 0

/** max value that can be stored by the ACR_Count_t type such that
    it will not overflow when added to 1
    (this allows ACR_MAX_COUNT+1 to be greater than ACR_ZERO_COUNT)
*/
#define ACR_MAX_COUNT 4294967294UL // hex value 0xFFFFFFFE

/** get a pointer to a data item in an array
    \param t the data type
    \param p the pointer
    \param i the position 0 to length-1 where
             length is the number of data items in the array
*/
#define ACR_VALUE_AT(t,p,i) ((t*)p)[i]

/** get a pointer to a data item in an array
    \param t the data type
    \param p the pointer
    \param i the position 0 to length-1 where
             length is the number of data items in the array
*/
#define ACR_POINTER_AT(t,p,i) (&ACR_VALUE_AT(t,p,i))

/** data used for counting from a start value to an end value
*/
typedef struct ACR_Counter_s
{
    ACR_Count_t m_Start;
    ACR_Count_t m_End;
    ACR_Count_t m_Current;
} ACR_Counter_t;

/** setup an existing counter
*/
#define ACR_COUNTER_SETUP(c, s, e) c = {s,e,s}

/** reset an existing counter
*/
#define ACR_COUNTER_RESET(c) c.m_Current = c.m_Start

/** check if a counter is valid
*/
#define ACR_COUNTER_IS_VALID(c) (c.m_Start <= c.m_End)

/** define a new counter
*/
#define ACR_COUNTER(c, s, e) ACR_Counter_t ACR_COUNTER_SETUP(c,s,e)

/** get the current counter value
    \param c the counter
    \param v the ACR_Count_t to store the value
*/
#define ACR_COUNTER_CURRENT(c, v) v = c.m_Current

/** increment the counter and get the value 
    \param c the counter
    \param v the ACR_Count_t to store the next value
    \param k ACR_Bool_t value will be set to ACR_BOOL_FALSE if there is no next value
             in which case the counter is reset so that this macro will return the
             start value again
*/
#define ACR_COUNTER_NEXT(c, v, k)\
{\
    if(c.m_Current < c.m_End)\
    {\
        c.m_Current += 1;\
        k = ACR_BOOL_TRUE;\
    }\
    else\
    {\
        c.m_Current = c.m_Start;\
        k = ACR_BOOL_FALSE;\
    }\
    v = c.m_Current;\
}

#endif
