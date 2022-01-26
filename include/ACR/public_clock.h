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

/** \file public_clock.h
 
    This header provides access to the real time
    clock when available.
    
    ACR_HAS_RTC as ACR_BOOL_TRUE or ACR_BOOL_FALSE
    

*/
#ifndef _ACR_PUBLIC_CLOCK_H_
#define _ACR_PUBLIC_CLOCK_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public_bool.h"

// included for ACR_SEC_FROM_1900_TO_1970
#include "ACR/public_dates_and_times.h"

// defines ACR_HAS_RTC and includes time()
// functions if desired
#ifndef ACR_CONFIG_NO_RTC
    #ifndef ACR_CONFIG_NO_LIBC
        #ifdef ACR_COMPILER_CLANG
            #include <time.h>
            #define ACR_HAS_RTC ACR_BOOL_TRUE
            #define ACR_TIME_NOW(name) time(&name)
            #define ACR_DATETIME_FROM_TIME(name,time) gmtime_r(&time,&name)
        #endif
        #ifdef ACR_COMPILER_GCC
            #include <time.h>
            #define ACR_HAS_RTC ACR_BOOL_TRUE
            #define ACR_TIME_NOW(name) time(&name)
            #define ACR_DATETIME_FROM_TIME(name,time) gmtime_r(&time,&name)
        #endif
        #ifdef ACR_COMPILER_VS2017
            #pragma warning(push)
            // disable warning C4820: '_timespec64': '4' bytes padding added after data member 'tv_nsec'
            #pragma warning(disable:4820)
            #include <time.h>
            #pragma warning(pop)
            #define ACR_HAS_RTC ACR_BOOL_TRUE
            #define ACR_TIME_NOW(name) time(&name)
            #define ACR_DATETIME_FROM_TIME(name,time) gmtime_s(&name,&time)
        #endif
    #else
        // without libc there is no interface to a standard
        // operating system's real-time clock.
        // see ACR_TimeProcessSecondTick for how to simulate
        // a real-time clock
    #endif // #ifndef ACR_CONFIG_NO_LIBC
#endif // #ifndef ACR_CONFIG_NO_RTC

#ifndef ACR_HAS_RTC
    #define ACR_HAS_RTC ACR_BOOL_FALSE
#endif // #ifndef ACR_HAS_RTC

#if ACR_HAS_RTC == ACR_BOOL_TRUE

    /** time value (seconds since unix epoch Jan 1, 1970)
    */
    typedef time_t ACR_Time_t;

    /** standard date time structure
    */
    typedef struct tm ACR_DateTime_t;

#else

    /** time value (seconds since unix epoch Jan 1, 1970)
    */
    #if ACR_USE_64BIT == ACR_BOOL_TRUE
        // 64bit
        typedef unsigned long long ACR_Time_t;
    #else
        // 32bit
        typedef unsigned long ACR_Time_t;
    #endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

    /// \todo support struct for time with seconds and microseconds

    /** standard date time structure
    */
    typedef struct ACR_DateTime_s
    {
        int tm_sec;          /* seconds, range 0 to 59           */
        int tm_min;          /* minutes, range 0 to 59           */
        int tm_hour;         /* hours, range 0 to 23             */
        int tm_mday;         /* day of the month, range 1 to 31  */
        int tm_mon;          /* month, range 0 to 11             */
        int tm_year;         /* The number of years since 1900   */
        int tm_wday;         /* day of the week, range 0 to 6    */
        int tm_yday;         /* day in the year, range 0 to 365  */
        int tm_isdst;        /* daylight saving time             */	
        int tm_gmtoff;		 /* Seconds east of UTC.             */
        const char *tm_zone; /* Timezone abbreviation.           */
    } ACR_DateTime_t;

    #define ACR_TIME_NOW(name) ACR_TimeNow(&name)
    #define ACR_DATETIME_FROM_TIME(name,time) ACR_DateTimeFromTime(&name,&time)

#endif // #if ACR_HAS_RTC == ACR_BOOL_TRUE

/** get the current date and time
    \param name any ACR_DateTime_t variable
*/
#define ACR_DATETIME_NOW(name) {ACR_Time_t temp; ACR_TIME_NOW(temp); ACR_DATETIME_FROM_TIME(name,temp);}

/** values that represent whether in day light savings time or not
    see tm_isdst in ACR_DateTime_t
*/
enum ACR_DST_e
{
    ACR_DST_UNKNOWN = -1,
    ACR_DST_OFF = 0,
    ACR_DST_ON = 1
};

/** define an empty date time on the stack
*/
#define ACR_DATETIME(name) ACR_DateTime_t name = {0};

/** determine if the specified date time has the time data set

    example:

    ACR_DATETIME(dateTime);
    if(ACR_DATETIME_HAS_TIME(dateTime) == ACR_BOOL_FALSE)
    {
        // no time value set
    }
*/
#define ACR_DATETIME_HAS_TIME(name) ((name.tm_sec|name.tm_min|name.tm_hour) != 0)

/** determine if the specified date time has the date data set

    example:

    ACR_DATETIME(dateTime);
    if(ACR_DATETIME_HAS_DATE(dateTime) == ACR_BOOL_FALSE)
    {
        // no time value set
    }
*/
#define ACR_DATETIME_HAS_DATE(name) ((name.tm_year|name.tm_mon|name.tm_mday) != 0)

#define ACR_DATETIME_YEAR(name) (1900 + name.tm_year)
#define ACR_DATETIME_MONTH(name) ((ACR_Month_t)name.tm_mon)
#define ACR_DATETIME_DAY(name) (name.tm_mday)
#define ACR_DATETIME_DAY_OF_WEEK(name) ((ACR_DayOfWeek_t)name.tm_wday)
#define ACR_DATETIME_HOUR(name) (name.tm_hour)
#define ACR_DATETIME_MIN(name) (name.tm_min)
#define ACR_DATETIME_SEC(name) (name.tm_sec)

/** ntp time is the number of seconds since Jan 1, 1900.
    this will convert NTP time to UNIX timestamp by subtracting
    seventy years in seconds
*/
#define ACR_TIME_FROM_NTP(ntpTime) (ntpTime - ACR_SEC_FROM_1900_TO_1970)


#endif
