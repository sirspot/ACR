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

/** \file public_math.h
 
    This header contains math constants and operations.
    It can be used standalone from the entire library or is
    included automatically with public.h

*/
#ifndef _ACR_PUBLIC_DECIMAL_H_
#define _ACR_PUBLIC_DECIMAL_H_

/** the value of pie
*/
#define ACR_PI 3.14159265359

/** the value of e (Euler's number)
*/
#define ACR_E 2.71828

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
    \param runningMean the variable that stores the runningMean.
                       It will be updated with the new runningMean.
                       This can start at zero.
    \param count the variable that stores the number of values that have been included in the runningMean.
                 It will be updated with the new count.
                 This value can start at zero.
    \param newValue the value to include in the runningMean
*/
#define ACR_RUNNING_MEAN(runningMean, count, newValue) (runningMean += ((newValue - runningMean) / ((ACR_Decimal_t)(++count))))

#endif
