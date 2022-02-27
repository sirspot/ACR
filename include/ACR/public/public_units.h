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

/** \file public_units.h
 
    This header contains unit conversions.
    It can be used standalone from the entire library or is
    included automatically with public.h

*/
#ifndef _ACR_PUBLIC_UNITS_H_
#define _ACR_PUBLIC_UNITS_H_

#define ACR_TEMPERATURE_C_TO_F(c) ((c*1.8)+32.0)
#define ACR_TEMPERATURE_F_TO_C(f) ((f-32.0)/1.8)

#define ACR_MEASURE_CM_TO_INCHES(cm) (cm/2.54)
#define ACR_MEASURE_INCHES_TO_CM(i) (i*2.54)

#define ACR_WEIGHT_KILOGRAMS_TO_POUNDS(kg) (kg*2.20462262)
#define ACR_WEIGHT_POUNDS_TO_KILOGRAMS(lbs) (lbs*0.45359237)

#define ACR_LIQUID_LITERS_TO_GALLONS(l) (l*0.26417205)
#define ACR_LIQUID_GALLONS_TO_LITERS(g) (g*3.78541178)

#endif
