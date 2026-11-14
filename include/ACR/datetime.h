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

/** \file datetime.h

    Functions for working with dates and times.

*/
#ifndef _ACR_DATETIME_H_
#define _ACR_DATETIME_H_

// included for ACR_Bool_t
#include "ACR/public/public_bool.h"

// included for ACR_Month_t and ACR_DayOfWeek_t
#include "ACR/public/public_dates_and_times.h"

// included for ACR_Time_t and ACR_DateTime_t
#include "ACR/public/public_clock.h"

// included for ACR_String_t
#include "ACR/public/public_string.h"

#ifdef __cplusplus
extern "C" {
#endif

/** get the number of days in the specified month
    \param month the month
           \see enum ACR_Month_e
    \param isLeapYear set to ACR_BOOL_TRUE to get leap year days (only affects February)
           \see ACR_YearIsLeapYear()
    \returns the number of days in the month
*/
int ACR_DaysPerMonth(
    ACR_Month_t month,
    ACR_Bool_t isLeapYear);

/** get the day of week value as a string
    \param dayOfWeek the day of week value
           \see enum ACR_DayOfWeek_e
    \returns a reference to a string
*/
ACR_String_t ACR_DayOfWeekToString(
    ACR_DayOfWeek_t dayOfWeek);

/** get the day of week value from a string
    \param src a reference to a string
    \returns a value from \see enum ACR_DayOfWeek_e or
             ACR_DAY_OF_WEEK_UNKNOWN if not found
*/
ACR_DayOfWeek_t ACR_DayOfWeekFromString(
    ACR_String_t src);

/** get the month value as a string
    \param month the month
           \see enum ACR_Month_e
    \returns a reference to a string
*/
ACR_String_t ACR_MonthToString(
    ACR_Month_t month);

/** get the month value from a string
    \param src a reference to a string
    \returns a value from \see enum ACR_Month_e or
             ACR_MONTH_UNKNOWN if not found
*/
ACR_Month_t ACR_MonthFromString(
    ACR_String_t src);

/** \param fourDigitYear any four digit year
    \returns ACR_BOOL_TRUE if the year is a leap year
*/
ACR_Bool_t ACR_YearIsLeapYear(
    int fourDigitYear);

/** set the time to the current system time
    \param me the time
    \returns ACR_BOOL_TRUE if successful
*/
ACR_Bool_t ACR_TimeNow(
    ACR_Time_t* me);

/** attempt to set the RTC to the specified time
    \param me the time to set the RTC to
    \returns ACR_BOOL_TRUE if successful
*/
ACR_Bool_t ACR_TimeSet(
    const ACR_Time_t* me);

/** when there is no RTC, call this function
    once per second (or as close as possible)
    to simulate the time
    \param seconds the number of seconds since the last call to this function (typically 1 is desired)
*/
void ACR_TimeProcessSecondTick(
    ACR_Time_t seconds);

/** when there is no timer, call this function
    to simulate the time that has passed
    \param microseconds the number of microseconds since the last call to this function
           (typically 1000 microseconds or less is desired)
*/
void ACR_TimeProcessMicroTick(
    ACR_Time_t microseconds);

/** set the date time data from the specified time
    \param me the date time
    \param time the time
    \returns ACR_BOOL_TRUE if successful
*/
ACR_Bool_t ACR_DateTimeFromTime(
    ACR_DateTime_t* me,
    const ACR_Time_t* time);

#ifdef __cplusplus
}
#endif

#endif
