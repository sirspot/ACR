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
/** \file common.c

*/
#include "ACR/common.h"

// included for ACR_INFO_STR_*, ACR_DAY_STR_*, and ACR_MONTH_STR_*
#include "ACR/public/public_unique_strings.h"

// included for ACR_PLATFORM_MAC, ACR_PLATFORM_WIN, ACR_PLATFORM_GITPOD
#include "ACR/public/public_config.h"

//#define ACR_USE_UTF8_LOCALE

#ifdef ACR_USE_UTF8_LOCALE
// included for setlocale
#include <locale.h>
#endif

/** info string lookup table
*/
static char* g_ACRInfoStringLookup[ACR_INFO_COUNT+1] =
{
    //
    // COMPARISON
    //
    ACR_INFO_STR_EQUAL,     // ACR_INFO_EQUAL
    ACR_INFO_STR_NOT_EQUAL, // ACR_INFO_NOT_EQUAL
    ACR_INFO_STR_LESS,      // ACR_INFO_LESS
    ACR_INFO_STR_GREATER,   // ACR_INFO_GREATER
    ACR_INFO_STR_UNKNOWN,   // ACR_INFO_UNKNOWN

    //
    // POSITIVE, NEGATIVE
    //
    ACR_INFO_STR_TRUE,      // ACR_INFO_TRUE
    ACR_INFO_STR_FALSE,     // ACR_INFO_FALSE
    ACR_INFO_STR_OK,        // ACR_INFO_OK
    ACR_INFO_STR_ERROR,     // ACR_INFO_ERROR
    ACR_INFO_STR_ENABLED,   // ACR_INFO_ENABLED
    ACR_INFO_STR_DISABLED,  // ACR_INFO_DISABLED
    ACR_INFO_STR_YES,       // ACR_INFO_YES
    ACR_INFO_STR_NO,        // ACR_INFO_NO
    ACR_INFO_STR_ON,        // ACR_INFO_ON
    ACR_INFO_STR_OFF,       // ACR_INFO_OFF
    ACR_INFO_STR_START,     // ACR_INFO_START
    ACR_INFO_STR_STOP,      // ACR_INFO_STOP
    ACR_INFO_STR_ACCEPT,    // ACR_INFO_ACCEPT
    ACR_INFO_STR_IGNORE,    // ACR_INFO_IGNORE
    ACR_INFO_STR_VALID,     // ACR_INFO_VALID
    ACR_INFO_STR_INVALID,   // ACR_INFO_INVALID

    //
    // POSITION
    //
    ACR_INFO_STR_TOP,       // ACR_INFO_TOP
    ACR_INFO_STR_BOTTOM,    // ACR_INFO_BOTTOM
    ACR_INFO_STR_FIRST,     // ACR_INFO_FIRST
    ACR_INFO_STR_LAST,      // ACR_INFO_LAST
    ACR_INFO_STR_PREVIOUS,  // ACR_INFO_PREVIOUS
    ACR_INFO_STR_NEXT,      // ACR_INFO_NEXT
    ACR_INFO_STR_CURRENT,   // ACR_INFO_CURRENT

    // DIRECTION
    ACR_INFO_STR_UP,        // ACR_INFO_UP
    ACR_INFO_STR_DOWN,      // ACR_INFO_DOWN
    ACR_INFO_STR_LEFT,      // ACR_INFO_LEFT
    ACR_INFO_STR_RIGHT,     // ACR_INFO_RIGHT

    // AGE
    ACR_INFO_STR_OLD,       // ACR_INFO_OLD
    ACR_INFO_STR_NEW,       // ACR_INFO_NEW

    // INSTRUCTION
    ACR_INFO_STR_BEGIN,     // ACR_INFO_BEGIN
    ACR_INFO_STR_READY,     // ACR_INFO_READY
    ACR_INFO_STR_WAIT,      // ACR_INFO_WAIT
    ACR_INFO_STR_GO,        // ACR_INFO_GO
    ACR_INFO_STR_END,       // ACR_INFO_END

    // MODE
    ACR_INFO_STR_READ,      // ACR_INFO_READ
    ACR_INFO_STR_WRITE,     // ACR_INFO_WRITE
    ACR_INFO_STR_READ_WRITE,// ACR_INFO_READ_WRITE

    ""                      // ACR_INFO_COUNT
};

/** day of week string lookup table
*/
static char* g_ACRDayOfWeekStringLookup[ACR_DAY_COUNT+1] =
{
    ACR_DAY_STR_SUNDAY,     // ACR_DAY_SUNDAY
    ACR_DAY_STR_MONDAY,     // ACR_DAY_MONDAY
    ACR_DAY_STR_TUESDAY,    // ACR_DAY_TUESDAY
    ACR_DAY_STR_WEDNESDAY,  // ACR_DAY_WEDNESDAY
    ACR_DAY_STR_THURSDAY,   // ACR_DAY_THURSDAY
    ACR_DAY_STR_FRIDAY,     // ACR_DAY_FRIDAY
    ACR_DAY_STR_SATURDAY,   // ACR_DAY_SATURDAY 
    ""                      // ACR_DAY_COUNT
};

/** month string lookup table
*/
static char* g_ACRMonthStringLookup[ACR_MONTH_COUNT+1] =
{
    ACR_MONTH_STR_JANUARY,  // ACR_MONTH_JANUARY
    ACR_MONTH_STR_FEBRUARY, // ACR_MONTH_FEBRUARY
    ACR_MONTH_STR_MARCH,    // ACR_MONTH_MARCH
    ACR_MONTH_STR_APRIL,    // ACR_MONTH_APRIL
    ACR_MONTH_STR_MAY,      // ACR_MONTH_MAY
    ACR_MONTH_STR_JUNE,     // ACR_MONTH_JUNE
    ACR_MONTH_STR_JULY,     // ACR_MONTH_JULY
    ACR_MONTH_STR_AUGUST,   // ACR_MONTH_AUGUST
    ACR_MONTH_STR_SEPTEMBER,// ACR_MONTH_SEPTEMBER
    ACR_MONTH_STR_OCTOBER,  // ACR_MONTH_OCTOBER
    ACR_MONTH_STR_NOVEMBER, // ACR_MONTH_NOVEMBER
    ACR_MONTH_STR_DECEMBER, // ACR_MONTH_DECEMBER
    ""                      // ACR_MONTH_COUNT
};

/** months to days lookup table
*/
unsigned char g_ACRMonthDaysLookup[ACR_MONTH_COUNT+1] =
{
    31, // ACR_MONTH_JANUARY      0      A
    28, // ACR_MONTH_FEBRUARY     1           C
    31, // ACR_MONTH_MARCH        2      A
    30, // ACR_MONTH_APRIL        3         B
    31, // ACR_MONTH_MAY          4      A
    30, // ACR_MONTH_JUNE         5         B
    31, // ACR_MONTH_JULY         6      A
    31, // ACR_MONTH_AUGUST       7      A
    30, // ACR_MONTH_SEPTEMBER    8         B
    31, // ACR_MONTH_OCTOBER      9      A
    30, // ACR_MONTH_NOVEMBER     10        B
    31, // ACR_MONTH_DECEMBER     11     A
    0   // ACR_MONTH_COUNT
};

ACR_Bool_t g_ACRSimRtcTimeIsSet = ACR_BOOL_FALSE;
ACR_Time_t g_ACRSimRtcTime = 0;
ACR_Bool_t g_ACRSimRtcTimeMilliIsSet = ACR_BOOL_FALSE;
ACR_Time_t g_ACRSimRtcTimeMilli = 0;

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - COMMON INFORMATIONAL VALUES
//
////////////////////////////////////////////////////////////

ACR_String_t ACR_InfoToString(
    ACR_Info_t info)
{
    return ACR_StringFromMemory((ACR_Byte_t*)g_ACRInfoStringLookup[info], ACR_MAX_LENGTH, ACR_MAX_COUNT);
}

ACR_Info_t ACR_InfoFromString(
    ACR_String_t src)
{
    ACR_Count_t i = 0;
    ACR_Info_t x;
    do
    {
        x = ACR_StringCompareToMemory(src, (const ACR_Byte_t*)g_ACRInfoStringLookup[i], ACR_MAX_LENGTH, ACR_MAX_COUNT, ACR_INFO_NO);
        if(x == ACR_INFO_EQUAL)
        {
            return (ACR_Info_t)i;
        }
        i++;
    }
    while(i < ACR_INFO_COUNT);
    return ACR_INFO_UNKNOWN;
}

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - DATE AND TIME VALUES
//
////////////////////////////////////////////////////////////

int ACR_DaysPerMonth(
    ACR_Month_t month,
    ACR_Bool_t isLeapYear)
{
    int days = g_ACRMonthDaysLookup[month];
    if(isLeapYear)
    {
        if(month == ACR_MONTH_FEBRUARY)
        {
            days++;
        }
    }
    return days;
}

ACR_String_t ACR_DayOfWeekToString(
    ACR_DayOfWeek_t dayOfWeek)
{
    return ACR_StringFromMemory((ACR_Byte_t*)g_ACRDayOfWeekStringLookup[dayOfWeek], ACR_MAX_LENGTH, ACR_MAX_COUNT);
}

ACR_DayOfWeek_t ACR_DayOfWeekFromString(
    ACR_String_t src)
{
    ACR_Count_t i = 0;
    ACR_Info_t x;
    do
    {
        x = ACR_StringCompareToMemory(src, (const ACR_Byte_t*)g_ACRDayOfWeekStringLookup[i], ACR_MAX_LENGTH, ACR_MAX_COUNT, ACR_INFO_NO);
        if(x == ACR_INFO_EQUAL)
        {
            return (ACR_DayOfWeek_t)i;
        }
        i++;
    }
    while(i < ACR_INFO_COUNT);
    return ACR_DAY_OF_WEEK_UNKNOWN;
}

ACR_String_t ACR_MonthToString(
    ACR_Month_t month)
{
    return ACR_StringFromMemory((ACR_Byte_t*)g_ACRMonthStringLookup[month], ACR_MAX_LENGTH, ACR_MAX_COUNT);
}

ACR_Month_t ACR_MonthFromString(
    ACR_String_t src)
{
    ACR_Count_t i = 0;
    ACR_Info_t x;
    do
    {
        x = ACR_StringCompareToMemory(src, (const ACR_Byte_t*)g_ACRMonthStringLookup[i], ACR_MAX_LENGTH, ACR_MAX_COUNT, ACR_INFO_NO);
        if(x == ACR_INFO_EQUAL)
        {
            return (ACR_Month_t)i;
        }
        i++;
    }
    while(i < ACR_INFO_COUNT);
    return ACR_MONTH_UNKNOWN;
}

ACR_Bool_t ACR_YearIsLeapYear(
    int fourDigitYear)
{
    return (ACR_Bool_t)ACR_YEAR_IS_LEAP_YEAR(fourDigitYear);
}

ACR_Bool_t ACR_TimeNow(
    ACR_Time_t* me)
{
    if(me)
    {
        #if ACR_HAS_RTC == ACR_BOOL_TRUE

            ACR_TIME_NOW((*me));
            return ACR_BOOL_TRUE;

        #else

            if(g_ACRSimRtcTimeIsSet)
            {
                (*me) = g_ACRSimRtcTime;
                return ACR_BOOL_TRUE;
            }

        #endif // #if ACR_HAS_RTC == ACR_BOOL_TRUE

        #if ACR_HAS_RTC == ACR_BOOL_FALSE
        // time has never been set and a RTC is not available.
        // set time to zero seconds.
        (*me) = 0;
        #endif // #if ACR_HAS_RTC == ACR_BOOL_FALSE
    }

    return ACR_BOOL_FALSE;
}

ACR_Bool_t ACR_TimeSet(
    const ACR_Time_t* me)
{
    ACR_Bool_t result = ACR_BOOL_FALSE;

    g_ACRSimRtcTimeIsSet = ACR_BOOL_TRUE;
    g_ACRSimRtcTime = (*me);

    #if ACR_HAS_RTC == ACR_BOOL_TRUE

        #ifdef ACR_PLATFORM_MAC
            /// \todo try to set the RTC to the specified time for this platform
        #endif

        #ifdef ACR_PLATFORM_WIN
            /// \todo try to set the RTC to the specified time for this platform
        #endif

        #ifdef ACR_PLATFORM_GITPOD
            /// \todo try to set the RTC to the specified time for this platform
        #endif

    #else
        // there is no RTC.
        // the simulated RTC is always set.
        result = ACR_BOOL_TRUE;
    #endif

    return result;
}

void ACR_TimeProcessSecondTick(
    ACR_Time_t seconds)
{
    g_ACRSimRtcTime += seconds;
}

void ACR_TimeProcessMilliTick(
    ACR_Time_t milliseconds)
{
    g_ACRSimRtcTimeMilliIsSet = ACR_BOOL_TRUE;
    g_ACRSimRtcTimeMilli += milliseconds;
}

ACR_Bool_t ACR_DateTimeFromTime(
    ACR_DateTime_t* me,
    const ACR_Time_t* time)
{
    if(me)
    {
        if(time)
        {
            if((*time) > 0)
            {
                #if ACR_HAS_RTC == ACR_BOOL_TRUE

                    ACR_DATETIME_FROM_TIME((*me), (*time));
                    return ACR_BOOL_TRUE;

                #else

                    ACR_Time_t tempTime = (*time);
                    int tempYear = 1970;

                    if((*time) >= ACR_SEC_FROM_1970_TO_2020)
                    {
                        // year 2020 or later
                        tempYear = 2020;
                        tempTime -= ACR_SEC_FROM_1970_TO_2020;
                    }
                    else if((*time) >= ACR_SEC_FROM_1970_TO_2000)
                    {
                        // year 2000 to 2019
                        tempYear = 2000;
                        tempTime -= ACR_SEC_FROM_1970_TO_2000;
                    }
                    else
                    {
                        // year 1970 to 1999
                    }

                    //
                    // tempTime contains at least the number of seconds necessary for the
                    // the current value of the tempYear variable
                    //
                    // subtract the seconds for each year until less than a year of seconds remains
                    do
                    {
                        ACR_Time_t secondsInYear = (ACR_SEC_PER_DAY * ACR_DAYS_PER_YEAR(tempYear));
                        if(secondsInYear >= tempTime)
                        {
                            tempYear++;
                            tempTime -= secondsInYear;
                        }
                        else
                        {
                            // found the year
                            me->tm_year = (tempYear-1900);
                            // break out of this loop.
                            break;
                        }
                    }
                    while (tempTime >= ACR_SEC_PER_STANDARD_YEAR);

                    //
                    // calculate the day of the year from the tempTime
                    //
                    me->tm_yday = (int)(tempTime / ACR_SEC_PER_DAY);
                    tempTime -= (me->tm_yday * ACR_SEC_PER_DAY);

                    //
                    // find the month and day from the day of the year
                    // by counting the days of each month and finding the remainder
                    //
                    {
                        int tempDays = 0;
                        int tempMonth = ACR_MONTH_JANUARY;
                        int tempDaysToFirstOfMonth = 0;
                        ACR_Bool_t isLeapYear = ACR_YearIsLeapYear(tempYear);
                        do
                        {
                            int daysInMonth = ACR_DaysPerMonth(tempMonth, isLeapYear);
                            tempDays += daysInMonth;
                            if(tempDays > me->tm_yday)
                            {
                                // found the month
                                // break out of this loop.
                                break;
                            }
                            tempDaysToFirstOfMonth += daysInMonth;
                            tempMonth++;
                        }
                        while (tempMonth < ACR_MONTH_DECEMBER);
                        me->tm_mon = tempMonth;
                        me->tm_mday = (me->tm_yday - tempDaysToFirstOfMonth) + 1;
                    }

                    //
                    // calculate the day of the week using Tomohiko Sakamoto's method
                    // as defined on Wikipedia https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
                    //
                    {
                        static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
                        tempYear -= ((me->tm_mon-1) < 3);
                        me->tm_wday = (tempYear + tempYear/4 - tempYear/100 + tempYear/400 + t[me->tm_mon] + me->tm_mday) % 7;
                    }

                    //
                    // temp time is now just the time of day in seconds.
                    // covert to hours, minutes, seconds.
                    //
                    me->tm_hour = (int)(tempTime / ACR_SEC_PER_HOUR);
                    tempTime -= (me->tm_hour * ACR_SEC_PER_HOUR);
                    me->tm_min = (int)(tempTime / ACR_SEC_PER_MIN);
                    tempTime -= (me->tm_min * ACR_SEC_PER_MIN);
                    me->tm_sec = (int)tempTime;

                    // indicate using UTC time
                    me->tm_gmtoff = 0;
                    me->tm_zone = "UTC";
                    
                    return ACR_BOOL_TRUE;

                #endif // #if ACR_HAS_RTC == ACR_BOOL_TRUE
            }
            else
            {
                // invalid time
            }
        }
        else
        {
            // time is null
        }

        ACR_CLEAR_MEMORY(me, sizeof(ACR_DateTime_t));
    }

    return ACR_BOOL_FALSE;
}

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - SIMPLE UTF8 STRINGS
//                    AND UNICODE CHARACTERS
//
////////////////////////////////////////////////////////////

ACR_Info_t ACR_Utf8NextChar(
        const ACR_Byte_t* mem,
        ACR_Length_t memLength,
        ACR_Length_t* pos)
{
    if((*pos) < memLength)
    {
        ACR_Byte_t c = mem[(*pos)];
        if(c != 0)
        {
            ACR_Length_t p = (*pos) + ACR_UTF8_BYTE_COUNT(c);
            if(p < memLength)
            {
                (*pos) = p;
                return ACR_INFO_OK;
            }
        }
        else
        {
            // already at end of string
        }
    }
    return ACR_INFO_ERROR;
}

ACR_Info_t ACR_Utf8PrevChar(
        const ACR_Byte_t* mem,
        ACR_Length_t memLength,
        ACR_Length_t* pos)
{
    if(((*pos) > 0) && ((*pos) <= memLength))
    {
        ACR_Byte_t c;
        (*pos) -= 1;
        c = mem[(*pos)];
        if((c & 0x80) == 0)
        {
            // [0xxxxxxx]
            return ACR_INFO_OK;
        }
        else
        {
            // [1xxxxxxx]
            while((c & 0x40) == 0)
            {
                // [?0xxxxxx]
                if((*pos) == 0)
                {
                    return ACR_INFO_ERROR;
                }
                (*pos) -= 1;
                c = mem[(*pos)];
            }
            // [?1xxxxxx]
            return ACR_INFO_OK;
        }
    }
    return ACR_INFO_ERROR;
}

ACR_Unicode_t ACR_UnicodeToLower(
    ACR_Unicode_t u)
{
    /// \todo use a conversion table instead to handle additional unicode characters
    
    // handle ASCII characters
    if((u >= 65) && (u <= 90))
    {
        u += 32;
    }

    return u;
}

ACR_Unicode_t ACR_UnicodeToUpper(
    ACR_Unicode_t u)
{
    /// \todo use a conversion table instead to handle additional unicode characters
    
    // handle ASCII characters
    if((u >= 97) && (u <= 122))
    {
        u -= 32;
    }

    return u;
}

ACR_Unicode_t ACR_Utf8ToUnicode(
    const ACR_Byte_t* mem,
    int bytes)
{
    int offset = (bytes-1);
    if(offset > 0)
    {
        ACR_Unicode_t c = (((ACR_Unicode_t)(mem[0] & (0x3F>>offset))) << (offset*6));
        int byteNum = 1;
        do
        {
            offset -= 1;
            c |= (((ACR_Unicode_t)(mem[byteNum] & 0x3F)) << (offset*6));
            byteNum += 1;
        }
        while(offset > 0);
        // Note: warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
        //       can be safely ignored here as it only serves to notify the user that
        //       the mitigation code will be used if desired
        return c;
    }
    return (ACR_Unicode_t)mem[0];
}

ACR_String_t ACR_StringFromMemory(
    ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters)
{
    ACR_STRING(s);
    if(src != ACR_NULL)
    {
        ACR_Length_t remaining = srcLength;
        ACR_Byte_t* srcPtr = src;
        while((remaining > 0) && (s.m_Count < maxCharacters) && ((*srcPtr) != 0))
        {
			ACR_Length_t bytes = ACR_UTF8_BYTE_COUNT((*srcPtr));
            if(bytes > remaining)
            {
                break;
            }
            s.m_Count++;
            srcPtr += bytes;
            remaining -= bytes;
        }
        ACR_BUFFER_SET_DATA(s.m_Buffer, src, (srcLength - remaining));
    }
    return s;
}

ACR_Info_t ACR_StringCompareToMemory(
    ACR_String_t string,
    const ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters,
    ACR_Info_t caseSensitive)
{
    if(src != ACR_NULL)
    {
        ACR_Count_t count = 0;
        // 0 = string
        // 1 = src
		ACR_Byte_t* srcPtr[2];
		ACR_Length_t bytes[2];
        int strIndex;
        ACR_Unicode_t c[2];
        srcPtr[0] = (ACR_Byte_t*)string.m_Buffer.m_Pointer;
		srcPtr[1] = (ACR_Byte_t*)src;
        while((srcLength > 0) && ((srcPtr[1][0]) != 0))
        {
            if(count == maxCharacters)
            {
                // finished comparing the max number of characters
                return ACR_INFO_EQUAL;
            }
            // count the next character using UTF8 byte counts
            bytes[1] = ACR_UTF8_BYTE_COUNT(srcPtr[1][0]);
            if(bytes[1] > srcLength)
            {
                // src is malformed UTF8 at the last
                // character so the last character of
                // src will be ignored
                break;
            }
            count++;
            if(count > string.m_Count)
            {
                // src has more characters than string
                return ACR_INFO_GREATER;
            }
            bytes[0] = ACR_UTF8_BYTE_COUNT(srcPtr[0][0]);
            // create the utf8 characters to compare
            strIndex = 0;
            do
            {
                c[strIndex] = ACR_Utf8ToUnicode(srcPtr[strIndex], (int)bytes[strIndex]);
                strIndex++;
            }
            while(strIndex < 2);
            if(caseSensitive != ACR_INFO_YES)
            {
                c[0] = ACR_UnicodeToLower(c[0]);
                c[1] = ACR_UnicodeToLower(c[1]);
            }
            if(c[0] > c[1])
            {
                // src is a smaller value than string
                return ACR_INFO_LESS;
            }
            else if(c[0] < c[1])
            {
                // src is a greater value than string
                return ACR_INFO_GREATER;
            }
            srcPtr[0] += bytes[0];
            srcPtr[1] += bytes[1];
            srcLength -= bytes[1];
        }
        // no more src characters to count
        if(count < string.m_Count)
        {
            // src has less characters than string
            return ACR_INFO_LESS;
        }
        return ACR_INFO_EQUAL;
    }
    return ACR_INFO_INVALID;
}

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - OTHER
//
////////////////////////////////////////////////////////////
