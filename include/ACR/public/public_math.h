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

/** \file public_math.h
 
    This header contains math constants and operations.
    It can be used standalone from the entire library or is
    included automatically with public.h

*/
#ifndef _ACR_PUBLIC_MATH_H_
#define _ACR_PUBLIC_MATH_H_

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

// included for ACR_Decimal_t
#include "ACR/public/public_decimal.h"

// included for ACR_Count_t recommended for use by ACR_RUNNING_MEAN()
#include "ACR/public/public_count.h"

/** the value of pi
*/
#define ACR_PI 3.14159265359

/** the value of e (Euler's number)
*/
#define ACR_E 2.71828

/** calculating power using exponents
*/
#ifdef ACR_CONFIG_NO_LIBC
    /** take an unsigned integer to the power of another unsigned integer.
        this uses ACR_Length_t because it is known to be the largest
        unsigned integer type supported by the current platform.
        \param b the base value
        \param e the exponent
        \returns the result or 0 if an overflow occurs
    */
    static inline ACR_Length_t ACR_POWER_OF_UNSIGNED_INT(ACR_Length_t b, ACR_Length_t e)
    {
        ACR_Length_t result = 1;
        while(e > 0)
        {
            ACR_Length_t nextValue = (result * b);
            if(nextValue < result)
            {
                // overflow
                return 0;
            }
            result = nextValue;
            e -= 1;
        }
        return result;
    }
#else
    // included for powl()
    #include <math.h>
    #define ACR_POWER_OF_UNSIGNED_INT(b,e) (ACR_Length_t)powl((ACR_Length_t)(b),(ACR_Length_t)(e))
#endif

/** the area of the rectangle with the specified length and width
*/
#define ACR_AREA_RECTANGLE(length,width) (length*width)

/** the area of the circle with the specified radius
*/
#define ACR_AREA_CIRCLE(radius) (ACR_PI*(radius*radius))

/** the circumference of a circle with the specified radius
*/
#define ACR_CIRCUMFERENCE(radius) (2*ACR_PI*radius)

/** update the running mean
    example:
    ACR_Decimal_t value = 0;
    ACR_Count_t count = 0;

    ACR_RUNNING_MEAN(value, count, 5);    // value += ((5 - 0) / 1);    // value = 5
    ACR_RUNNING_MEAN(value, count, 5.5);  // value += ((5.5 - 5) / 2)   // value = 5.25
    ACR_RUNNING_MEAN(value, count, 6);    // value += ((6 - 5.25) / 3)  // value = 5.50
    ACR_RUNNING_MEAN(value, count, 10);   // value += ((10 - 5.50) / 4) // value = 6.625

    \param runningMean the variable that stores the runningMean.
                       It will be updated with the new runningMean.
                       This can start at zero.
    \param count the variable that stores the number of values that have been included in the runningMean.
                 It will be updated with the new count.
                 This value can start at zero.
    \param newValue the value to include in the runningMean
*/
#define ACR_RUNNING_MEAN(runningMean, count, newValue) (runningMean += (((ACR_Decimal_t)(newValue) - (ACR_Decimal_t)runningMean) / ((ACR_Decimal_t)(++count))))

#endif
