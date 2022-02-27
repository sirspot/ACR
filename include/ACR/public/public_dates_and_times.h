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

/** \file public_dates_and_times.h
 
    This header contains commonly used values for date and
    time. It can be used standalone from the entire library or
    is included automatically with public.h

    See public.h for more information.

*/
#ifndef _ACR_PUBLIC_DATES_AND_TIMES_H_
#define _ACR_PUBLIC_DATES_AND_TIMES_H_

/** months of the year

    ### New to C? ###

    Q: Why not just use the number of the month?
    A: Best practice is to avoid the user of "magic numbers",
       which is any number present in the code that does
       not have a name attached to it. Some numbers, like
       the number of the month, seem so simple that you may
       think it is ok to just use a number, but this is how
       many off-by-one errors occur.

    Q: What is an off-by-one error?
    A: This is one of the most common programming mistakes and
       typically involves a simple mistake caused by counting
       starting with the number 0 or the number 1. The result
       is a value that is either 1 too big or 1 too small. In
       the best case it just causes some display errors and in
       the worst case it can crash the program.

    Q: What is a buffer overrun or overflow?
    A: This occurs when accessing an index of an array that 
       is greater than the size of the array. This almost always
       causes the program to crash but it is also possible for
       the program to continue running with undefined behavior.
       An off-by-one error can easily cause a buffer overrun.

*/
typedef enum ACR_Month_e
{
    ACR_MONTH_JANUARY = 0,
    ACR_MONTH_FEBRUARY,
    ACR_MONTH_MARCH,
    ACR_MONTH_APRIL,
    ACR_MONTH_MAY,
    ACR_MONTH_JUNE,
    ACR_MONTH_JULY,
    ACR_MONTH_AUGUST,
    ACR_MONTH_SEPTEMBER,
    ACR_MONTH_OCTOBER,
    ACR_MONTH_NOVEMBER,
    ACR_MONTH_DECEMBER,
    ACR_MONTH_COUNT
} ACR_Month_t;

#define ACR_MONTH_UNKNOWN (ACR_MONTH_COUNT+1)
#define ACR_MONTHS_PER_YEAR ACR_MONTH_COUNT

#define ACR_YEAR_IS_LEAP_YEAR(fourDigitYear) ((fourDigitYear % 400 == 0) || ((fourDigitYear % 100 != 0) && (fourDigitYear % 4 == 0)))

/** days of the week
*/
typedef enum ACR_DayOfWeek_e
{
    ACR_DAY_SUNDAY = 0,
    ACR_DAY_MONDAY,
    ACR_DAY_TUESDAY,
    ACR_DAY_WEDNESDAY,
    ACR_DAY_THURSDAY,
    ACR_DAY_FRIDAY,
    ACR_DAY_SATURDAY,
    ACR_DAY_COUNT
} ACR_DayOfWeek_t;

#define ACR_DAY_OF_WEEK_UNKNOWN (ACR_DAY_COUNT+1)
#define ACR_DAYS_PER_WEEK ACR_DAY_COUNT
#define ACR_DAYS_PER_STANDARD_YEAR 365
#define ACR_DAYS_PER_LEAP_YEAR 366
#define ACR_DAYS_PER_YEAR(fourDigitYear) (ACR_YEAR_IS_LEAP_YEAR(fourDigitYear)?ACR_DAYS_PER_LEAP_YEAR:ACR_DAYS_PER_STANDARD_YEAR)

// HOURS
#define ACR_HOUR_PER_DAY 24

// MINUTES
#define ACR_MIN_PER_HOUR 60
#define ACR_MIN_PER_DAY (ACR_MIN_PER_HOUR*ACR_HOUR_PER_DAY)
#define ACR_MIN_PER_WEEK (ACR_MIN_PER_DAY*ACR_DAY_PER_WEEK)

// SECONDS
#define ACR_SEC_PER_MIN 60
#define ACR_SEC_PER_HOUR (ACR_SEC_PER_MIN*ACR_MIN_PER_HOUR)
#define ACR_SEC_PER_DAY (ACR_SEC_PER_HOUR*ACR_HOUR_PER_DAY)
#define ACR_SEC_PER_STANDARD_YEAR (ACR_SEC_PER_DAY*ACR_DAYS_PER_STANDARD_YEAR)
#define ACR_SEC_PER_LEAP_YEAR (ACR_SEC_PER_DAY*ACR_DAYS_PER_LEAP_YEAR)
#define ACR_SEC_FROM_1900_TO_1970 2208988800UL
#define ACR_SEC_FROM_1970_TO_2000  946684800UL
#define ACR_SEC_FROM_1970_TO_2020 1577836800UL

// MILLISECONDS
#define ACR_MILLI_PER_SEC 1000
#define ACR_MILLI_PER_MIN (ACR_MILLI_PER_SEC*ACR_SEC_PER_MIN)
#define ACR_MILLI_PER_HOUR (ACR_MILLI_PER_MIN*ACR_MIN_PER_HOUR)

// MICROSECONDS
#define ACR_MICRO_PER_MILLI 1000
#define ACR_MICRO_PER_SEC (ACR_MICRO_PER_MILLI*ACR_MILLI_PER_SEC)
#define ACR_MICRO_PER_MIN (ACR_MICRO_PER_SEC*ACR_SEC_PER_MIN)

// NANOSECONDS
#define ACR_NANO_PER_MICRO 1000
#define ACR_NANO_PER_MILLI (ACR_NANO_PER_MICRO*ACR_MICRO_PER_MILLI)
#define ACR_NANO_PER_SEC (ACR_NANO_PER_MILLI*ACR_MILLI_PER_SEC)

/** ntp time is the number of seconds since Jan 1, 1900.
    this will convert NTP time to UNIX timestamp by subtracting
    seventy years in seconds
*/
#define ACR_TIME_FROM_NTP(ntpTime) (ntpTime - ACR_SEC_FROM_1900_TO_1970)

#endif
