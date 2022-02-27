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

/** \file common.h
 
    This header defines functions that are commonly used
    along with the features found in public.h

    Note: warning C4711: function selected for automatic
          inline expansion can be safely ignored

*/
#ifndef _ACR_COMMON_H_
#define _ACR_COMMON_H_

// included for ACR_String_t and ACR_Unicode_t
#include "ACR/public/public_string.h"

// included for ACR_Info_t
#include "ACR/public/public_info.h"

// included for ACR_Month_t and ACR_DayOfWeek_t
#include "ACR/public/public_dates_and_times.h"

// included for ACR_Time_t and ACR_DateTime_t
#include "ACR/public/public_clock.h"

// included for ACR_Bool_t
#include "ACR/public/public_bool.h"

// included for ACR_Byte_t
#include "ACR/public/public_bytes_and_flags.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

// included for ACR_Count_t
#include "ACR/public/public_count.h"

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
extern "C" {                                              //
#endif                                                    //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - COMMON INFORMATIONAL VALUES
//
////////////////////////////////////////////////////////////

/** get the info value as a string
    \param info the info value \see enum ACR_Info_e
    \returns a reference to a string
*/
ACR_String_t ACR_InfoToString(
    ACR_Info_t info);

/** get the info value from a string
    \param src a reference to a string
    \returns an info value from \see enum ACR_Info_e or
             ACR_INFO_UNKNOWN if not found
*/
ACR_Info_t ACR_InfoFromString(
    ACR_String_t src);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - TIMER
//
////////////////////////////////////////////////////////////

/** start or restart a timer
    \param me the timer
    \returns ACR_BOOL_TRUE if successful
*/
ACR_Bool_t ACR_TimerStart(
    ACR_Timer_t* me);

/** get the time that has past since ACR_TimerStart() was called
    \param me the timer
    \returns the number of microseconds that have past
*/
long ACR_TimerElapse(
    ACR_Timer_t* me);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - DATE AND TIME VALUES
//
////////////////////////////////////////////////////////////

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

/** where there is no RTC, call this function
    once per millisecond (or as close as possible)
    to simulate the time
    \param milliseconds the number of milliseconds since the last call to this function (typically 10 or less is desired)
*/
void ACR_TimeProcessMilliTick(
    ACR_Time_t milliseconds);

/** set the date time data from the specified time
    \param me the date time
    \param time the time
    \returns ACR_BOOL_TRUE if successful
*/
ACR_Bool_t ACR_DateTimeFromTime(
    ACR_DateTime_t* me,
    const ACR_Time_t* time);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - SIMPLE UTF8 STRINGS
//                    AND UNICODE CHARACTERS
//
////////////////////////////////////////////////////////////

/** selects the position of the next character
  \param mem the start of the UTF8 encoded string data
  \param memLength the length of mem (use ACR_MAX_LENGTH if unsure)
  \param pos current byte offset into the string, which
         will be updated to that of the next character if
         successful
  \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_Utf8NextChar(
        const ACR_Byte_t* mem,
        ACR_Length_t memLength,
        ACR_Length_t* pos);

/** selects the position of the previous character
  \param mem start of the UTF8 encoded string data
  \param memLength the length of mem (use ACR_MAX_LENGTH if unsure)
  \param pos current byte offset in the string, which will
         be updated to that of the previous character if
         successful
  \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_Utf8PrevChar(
        const ACR_Byte_t* mem,
        ACR_Length_t memLength,
        ACR_Length_t* pos);

/** convert a unicode charcter to its lower-case
    representation
*/
ACR_Unicode_t ACR_UnicodeToLower(
    ACR_Unicode_t u);

/** convert a unicode charcter to its upper-case
    representation
*/
ACR_Unicode_t ACR_UnicodeToUpper(
    ACR_Unicode_t u);

/** convert UTF8 encoded data to a unicode value
    \param mem a valid pointer to the UTF8 encoded character
           in memory
    \param bytes the number of bytes for this UTF8 encoded
           unicode value. use ACR_UTF8_BYTE_COUNT(mem[0])
           if unsure
    \returns the unicode value
*/
ACR_Unicode_t ACR_Utf8ToUnicode(
    const ACR_Byte_t* mem,
    int bytes);

/** get a reference to a null-terminated string in memory 
    with support for UTF8 encoding
    \param src a pointer to a null-terminated string in
           memory
    \param srcLength the max number of bytes from src this
           function will search. use ACR_MAX_LENGTH if
           unsure
    \param maxCharacters the max number of characters this
           function will count. use ACR_MAX_COUNT if unsure
    \returns a string referennce
*/
ACR_String_t ACR_StringFromMemory(
    ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters);

/** \see ACR_StringFromMemory()

    the string returned will have the read only flag set
*/
ACR_String_t ACR_StringFromReadOnlyMemory(
    const ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters);

/** compare a string to a null-terminated string in memory
    with support for UTF8 encoding
    \param string the known string to compare to
    \param src a pointer to a null-terminated string in
           memory
    \param srcLength the max number of bytes from mem this
           function will search. use ACR_MAX_LENGTH if 
           unsure
    \param maxCharacters the max number of characters this
           function will compare. use ACR_MAX_COUNT if 
           unsure
    \param caseSensitive set to ACR_INFO_YES for 
           case-sensitive comparison (faster) or ACR_INFO_NO
           for case-insensitive (slower)
    \returns - ACR_INFO_EQUAL if the strings are equal up
               to maxCharacters
             - ACR_INFO_LESS if src has less characters or
               is less than string
             - ACR_INFO_GREATER if src has more characters
               or is greater than string
             - ACR_INFO_INVALID if src is invalid
*/
ACR_Info_t ACR_StringCompareToMemory(
    ACR_String_t string,
    const ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters,
    ACR_Info_t caseSensitive);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
