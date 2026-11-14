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
/** \file datetime.c

*/
#include "ACR/datetime.h"

// included for ACR_StringFromReadOnlyMemory and ACR_StringCompareToMemory
#include "ACR/string.h"

// included for ACR_INFO_NO and ACR_INFO_EQUAL
#include "ACR/public/public_info.h"

// included for ACR_DAY_STR_*, ACR_MONTH_STR_*
#include "ACR/public/public_unique_strings.h"

// included for ACR_PLATFORM_MAC, ACR_PLATFORM_WIN, ACR_PLATFORM_GITPOD
#include "ACR/public/public_config.h"

// included for ACR_CLEAR_MEMORY
#include "ACR/public/public_memory.h"

ACR_Bool_t g_ACRSimRtcTimeIsSet = ACR_BOOL_FALSE;
ACR_Time_t g_ACRSimRtcTime = 0;
ACR_Bool_t g_ACRSimRtcTimeMicroIsSet = ACR_BOOL_FALSE;
ACR_Time_t g_ACRSimRtcTimeMicro = 0;

/** day of week string lookup table
*/
static const char* g_ACRDayOfWeekStringLookup[ACR_DAY_COUNT+1] =
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
static const char* g_ACRMonthStringLookup[ACR_MONTH_COUNT+1] =
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
static unsigned char g_ACRMonthDaysLookup[ACR_MONTH_COUNT+1] =
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
    return ACR_StringFromReadOnlyMemory((const ACR_Byte_t*)g_ACRDayOfWeekStringLookup[dayOfWeek], ACR_MAX_LENGTH, ACR_MAX_COUNT);
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
    while(i < ACR_DAY_COUNT);
    return ACR_DAY_OF_WEEK_UNKNOWN;
}

ACR_String_t ACR_MonthToString(
    ACR_Month_t month)
{
    return ACR_StringFromReadOnlyMemory((const ACR_Byte_t*)g_ACRMonthStringLookup[month], ACR_MAX_LENGTH, ACR_MAX_COUNT);
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
    while(i < ACR_MONTH_COUNT);
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

            if(ACR_TIME_NOW((*me)))
            {
                return ACR_BOOL_TRUE;
            }

            // failed to get the current time.
            // set time to zero seconds.
            (*me) = 0;

        #else

            if(g_ACRSimRtcTimeIsSet)
            {
                (*me) = g_ACRSimRtcTime;
                return ACR_BOOL_TRUE;
            }
            else
            {
                // time has never been set and a RTC is not available.
                // set time to zero seconds.
                (*me) = 0;
            }

        #endif // #if ACR_HAS_RTC == ACR_BOOL_TRUE
    }

    return ACR_BOOL_FALSE;
}

ACR_Bool_t ACR_TimeSet(
    const ACR_Time_t* me)
{
    ACR_Bool_t result = ACR_BOOL_FALSE;

    if(!me)
    {
        return result;
    }

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
    g_ACRSimRtcTimeIsSet = ACR_BOOL_TRUE;
    g_ACRSimRtcTime += seconds;
}

void ACR_TimeProcessMicroTick(
    ACR_Time_t microseconds)
{
    g_ACRSimRtcTimeMicroIsSet = ACR_BOOL_TRUE;
    g_ACRSimRtcTimeMicro += microseconds;
}

ACR_Bool_t ACR_DateTimeFromTime(
    ACR_DateTime_t* me,
    const ACR_Time_t* time)
{
    if(me)
    {
        if(time)
        {
            if((*time) >= 0)
            {
                #if ACR_HAS_RTC == ACR_BOOL_TRUE

                    if(ACR_DATETIME_FROM_TIME((*me), (*time)))
                    {
                        return ACR_BOOL_TRUE;
                    }

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
                    // subtract complete years until less than a year of seconds remains
                    while(1)
                    {
                        ACR_Time_t secondsInYear = (ACR_SEC_PER_DAY * ACR_DAYS_PER_YEAR(tempYear));
                        if(tempTime >= secondsInYear)
                        {
                            tempTime -= secondsInYear;
                            tempYear++;
                        }
                        else
                        {
                            // found the year
                            me->tm_year = (tempYear-1900);
                            break;
                        }
                    }

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
                        tempYear -= (me->tm_mon < 2);
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
                    me->tm_isdst = 0;
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
