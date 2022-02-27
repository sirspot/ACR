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

/** \file public_decimal.h
 
    This header contains types and values for decimal values.

*/
#ifndef _ACR_PUBLIC_DECIMAL_H_
#define _ACR_PUBLIC_DECIMAL_H_

// included for ACR_INFO_GREATER, ACR_INFO_LESS, and ACR_INFO_EQUAL
#include "ACR/public/public_info.h"

/** stores a decimal value
*/
typedef float ACR_Decimal_t;

/** default tolerance for comparison of decimal values
    \see ACR_DecimalCompare()

    Note: the 'f' at the end indicates this is a float (not a double or long double)
*/
#define ACR_DEFAULT_TOLERANCE 0.0001f

/** compare two decimal values
    \param a
    \param b
    \param t the absolute value of the difference
            between a and b where they will be assumed
            to be equal values. use ACR_DEFAULT_TOLERANCE
            if unsure
    \returns - ACR_INFO_EQUAL if the decimals are equal
               within the specified tolerance (t)
             - ACR_INFO_LESS if a is less than b
             - ACR_INFO_GREATER a is greater than b
*/
#define ACR_DECIMAL_TOLERANCE_COMPARE(a,b,t) (((a-t)>b)?ACR_INFO_GREATER:((a+t)<b)?ACR_INFO_LESS:ACR_INFO_EQUAL)
#define ACR_DECIMAL_COMPARE(a,b) (ACR_DECIMAL_TOLERANCE_COMPARE(a,b,ACR_DEFAULT_TOLERANCE))

#endif
