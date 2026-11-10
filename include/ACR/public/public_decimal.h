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

// included for ACR_INFO_GREATER, ACR_INFO_LESS, ACR_INFO_EQUAL,
// ACR_INFO_UNKNOWN, and ACR_INFO_UNDEFINED
#include "ACR/public/public_info.h"

/** stores a decimal value
*/
typedef float ACR_Decimal_t;

/** check for NaN
    Note: NaN ("Not a Number") is an unordered floating-point value. It can result
          from invalid operations such as 0.0f / 0.0f, INFINITY - INFINITY, or
          sqrtf(-1.0f) on IEEE-754 systems. Comparisons with NaN are false in both
          directions, so without this check the function would incorrectly return
          ACR_INFO_EQUAL at the end.
*/
#ifndef ACR_CONFIG_NO_LIBC
    #include <math.h>
    // use the standard library to check for NaN
    #define ACR_DECIMAL_IS_NOT_A_NUMBER(n) isnan(n)
#else
    // use a trick that the compiler *should not* optimize out
    // to determine if the tolerance value is NaN
    #define ACR_DECIMAL_IS_NOT_A_NUMBER(n) (!((n) >= 0.0f))
#endif

/** default tolerance for comparison of decimal values
    \see ACR_DECIMAL_COMPARE()

    Note: the 'f' at the end indicates this is a float (not a double or long double)
*/
#define ACR_DEFAULT_TOLERANCE 0.00001f

/** Compare two decimal values within an absolute tolerance.
    see ACR_DECIMAL_COMPARE() for a simple version with example usage.
    \param a The first value to compare.
    \param b The second value to compare.
    \param tolerance Non-negative maximum absolute difference treated as equal.
    \return ACR_INFO_EQUAL if the values are identical or within tolerance,
            ACR_INFO_LESS if a is less, ACR_INFO_GREATER if a is greater,
            ACR_INFO_UNDEFINED if a value is NaN, or if tolerance is NaN and the
            values are not identical, or ACR_INFO_UNKNOWN if tolerance is negative
            and the values are not identical.
*/
static inline ACR_Info_t ACR_DECIMAL_TOLERANCE_COMPARE(ACR_Decimal_t a, ACR_Decimal_t b, ACR_Decimal_t tolerance)
{
    if (a == b)
    {
        // identical values are equal without consulting the tolerance
        return ACR_INFO_EQUAL;
    }

    if (tolerance < 0.0f)
    {
        // a negative tolerance is invalid
        return ACR_INFO_UNKNOWN;
    }

    if (ACR_DECIMAL_IS_NOT_A_NUMBER(tolerance))
    {
        // NaN tolerance cannot define an equality range
        return ACR_INFO_UNDEFINED;
    }

    if (a > b)
    {
        // a might be greater than b.
        // check if difference exceeds tolerance
        return (a - b) > tolerance ? ACR_INFO_GREATER : ACR_INFO_EQUAL;
    }

    if (a < b)
    {
        // a might me less than b.
        // check if difference exceeds tolerance
        return (b - a) > tolerance ? ACR_INFO_LESS : ACR_INFO_EQUAL;
    }

    // ordering comparison failed.
    // at least one value is NaN
    return ACR_INFO_UNDEFINED;
}

/** compare decimals using the default tolerance.
    see the table below for examples:

    equality        use instead
    --------------- ------------------------------------------------------
    if(a >  b)      if(ACR_DECIMAL_COMPARE(a,b) == ACR_INFO_GREATER)
    if(a <  b)      if(ACR_DECIMAL_COMPARE(a,b) == ACR_INFO_LESS)
    if(a <= b)      if(ACR_DECIMAL_COMPARE(b,a) == ACR_INFO_GREATER)
    if(a >= b)      if(ACR_DECIMAL_COMPARE(b,a) == ACR_INFO_LESS)
    if(a == b)      if(ACR_DECIMAL_COMPARE(b,a) == ACR_INFO_EQUAL)

*/
#define ACR_DECIMAL_COMPARE(a,b) (ACR_DECIMAL_TOLERANCE_COMPARE(a,b,ACR_DEFAULT_TOLERANCE))

#endif
