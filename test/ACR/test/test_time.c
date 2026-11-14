/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2026 Adam C. Rosenberg

    Please read LICENSE before using this code

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
/** \file test_time.c

    tests date conversion, simulated clocks, and timer differences

*/
#include <assert.h>
#include <stdint.h>
#include <time.h>

#include "ACR/datetime.h"
#include "ACR/timer.h"

static void TestDateConversion(void)
{
    int64_t timestamp;

    assert(ACR_MIN_PER_WEEK == 10080);
    assert(ACR_YEAR_IS_LEAP_YEAR(1999 + 1));
    assert(ACR_TIME_FROM_NTP(2208988800ULL) == 0);

    for(timestamp = 0; timestamp < INT64_C(2145916800); timestamp += ACR_SEC_PER_DAY)
    {
        int secondsIntoDay;
        const int timesOfDay[] = {0, 43200, 86399};

        for(secondsIntoDay = 0; secondsIntoDay < 3; secondsIntoDay++)
        {
            ACR_Time_t value = (ACR_Time_t)(timestamp + timesOfDay[secondsIntoDay]);
            time_t oracleValue = (time_t)value;
            struct tm* expected = gmtime(&oracleValue);
            ACR_DateTime_t actual = {0};

            assert(expected != NULL);
            assert(ACR_DateTimeFromTime(&actual, &value) == ACR_BOOL_TRUE);
            assert(actual.tm_sec == expected->tm_sec);
            assert(actual.tm_min == expected->tm_min);
            assert(actual.tm_hour == expected->tm_hour);
            assert(actual.tm_mday == expected->tm_mday);
            assert(actual.tm_mon == expected->tm_mon);
            assert(actual.tm_year == expected->tm_year);
            assert(actual.tm_wday == expected->tm_wday);
            assert(actual.tm_yday == expected->tm_yday);
            assert(actual.tm_isdst == 0);
        }
    }

#if ACR_USE_64BIT == ACR_BOOL_TRUE
    {
        ACR_Time_t value = (ACR_Time_t)INT64_C(4107542400);
        time_t oracleValue = (time_t)value;
        struct tm* expected = gmtime(&oracleValue);
        ACR_DateTime_t actual = {0};

        assert(expected != NULL);
        assert(ACR_DateTimeFromTime(&actual, &value) == ACR_BOOL_TRUE);
        assert(actual.tm_sec == expected->tm_sec);
        assert(actual.tm_min == expected->tm_min);
        assert(actual.tm_hour == expected->tm_hour);
        assert(actual.tm_mday == expected->tm_mday);
        assert(actual.tm_mon == expected->tm_mon);
        assert(actual.tm_year == expected->tm_year);
        assert(actual.tm_wday == expected->tm_wday);
        assert(actual.tm_yday == expected->tm_yday);
    }
#endif
}

static void TestSimulatedClockAndTimer(void)
{
    ACR_Time_t start = (ACR_Time_t)1709251200;

    assert(ACR_TimeNow(NULL) == ACR_BOOL_FALSE);
    assert(ACR_TimeSet(NULL) == ACR_BOOL_FALSE);

#if ACR_HAS_RTC == ACR_BOOL_FALSE
    ACR_Time_t now = 0;
    ACR_DateTime_t dateTime = {0};

    dateTime.tm_sec = 1;
    ACR_DATETIME_NOW(dateTime);
    assert(dateTime.tm_sec == 0);
    assert(dateTime.tm_mday == 0);
    assert(ACR_TimeNow(&now) == ACR_BOOL_FALSE);
    ACR_TimeProcessSecondTick(1);
    assert(ACR_TimeNow(&now) == ACR_BOOL_TRUE);
    assert(now == 1);
    assert(ACR_TimeSet(&start) == ACR_BOOL_TRUE);
    assert(ACR_TimeNow(&now) == ACR_BOOL_TRUE);
    assert(now == start);
#else
    ACR_Time_t now = 0;
    ACR_DateTime_t dateTime = {0};

    assert(ACR_TimeNow(&now) == ACR_BOOL_TRUE);
    assert(now > 0);
    ACR_DATETIME_NOW(dateTime);
    assert(dateTime.tm_mday > 0);
    ACR_TimeSet(&start);
#endif

#if ACR_HAS_TIMER == ACR_BOOL_FALSE
    {
        ACR_Timer_t timer;

        assert(ACR_TimerStart(NULL) == ACR_BOOL_FALSE);
        assert(ACR_TimerStart(&timer) == ACR_BOOL_TRUE);
        ACR_TimeProcessMicroTick(2000250);
        assert(ACR_TimerElapse(&timer) == 2000250);

        ACR_Timer_t later;
        ACR_Time_t difference;
        ACR_Info_t comparison;

        ACR_TimeProcessSecondTick(3600);
        assert(ACR_TimerStart(&later) == ACR_BOOL_TRUE);
        ACR_TIMER_DIFF_MICRO(timer, later, difference, comparison);
        if(sizeof(ACR_Time_t) <= 4)
        {
            assert(difference == (ACR_Time_t)INT32_MAX);
            assert(comparison == ACR_INFO_UNKNOWN);
        }
        else
        {
            assert(difference == 3602000250LL);
            assert(comparison == ACR_INFO_LESS);
        }
    }
#else
    {
        ACR_Timer_t timerA;
        ACR_Timer_t timerB;
        ACR_Time_t difference;
        ACR_Info_t comparison;

        assert(ACR_TimerStart(&timerA) == ACR_BOOL_TRUE);
        assert(ACR_TimerStart(&timerB) == ACR_BOOL_TRUE);
        ACR_TIMER_DIFF_MICRO(timerA, timerB, difference, comparison);
        assert(comparison != ACR_INFO_UNKNOWN);
        assert(difference >= 0);
    }
#endif
}

int main(void)
{
    ACR_DateTime_t dateTime = {0};
    ACR_Time_t epoch = 0;

    assert(ACR_DateTimeFromTime(&dateTime, &epoch) == ACR_BOOL_TRUE);
    assert(dateTime.tm_year == 70);
    assert(dateTime.tm_mon == ACR_MONTH_JANUARY);
    assert(dateTime.tm_mday == 1);
    assert(dateTime.tm_wday == ACR_DAY_THURSDAY);
    assert(dateTime.tm_yday == 0);

    dateTime.tm_sec = 59;
    {
        ACR_Time_t invalid = -1;
        assert(ACR_DateTimeFromTime(&dateTime, &invalid) == ACR_BOOL_FALSE);
        assert(dateTime.tm_sec == 0);
    }

    TestDateConversion();
    TestSimulatedClockAndTimer();
    return 0;
}
