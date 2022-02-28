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

/** \file public_timer.h
 
    This header provides access to a high precision clock when available.
    It is included automatically with public.h
    
    This header gaurantees the following will be defined:
    ACR_HAS_TIMER          as either ACR_BOOL_TRUE or ACR_BOOL_FALSE
    ACR_Timer_t            for timer data
    ACR_TIME_START         as a macro that accepts a ACR_Timer_t variable
    ACR_TIMER_AS_MICROSECONDS as a macro that accepts a ACR_Timer_t variable and returns an ACR_Time_t 
                              value of the timer represented as microseconds for use only when comparing timers
    ACR_TIMER_DIFF_MICRO   as a macro to compare 2 timers

*/
#ifndef _ACR_PUBLIC_TIMER_H_
#define _ACR_PUBLIC_TIMER_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public/public_bool.h"

// included for ACR_COMPILER_CLANG, ACR_COMPILER_GCC, ACR_COMPILER_VS2017
#include "ACR/public/public_config.h"

// included for ACR_SEC_FROM_1601_TO_1970, ACR_NANO_X100_PER_SEC, ACR_MICRO_PER_SEC
#include "ACR/public/public_dates_and_times.h"

// included for ACR_Time_t
#include "ACR/public/public_clock.h"

// defines ACR_HAS_RTC and includes time()
// functions if desired
#ifndef ACR_CONFIG_NO_TIMER
    #ifndef ACR_CONFIG_NO_LIBC
        #ifdef ACR_COMPILER_CLANG
            // included for gettimeofday()
            #include <sys/time.h>
            #define ACR_HAS_TIMER ACR_BOOL_TRUE
            typedef struct timeval ACR_Timer_t;
            #define ACR_TIMER_START(timer) gettimeofday(&timer,ACR_NULL)
            #define ACR_TIMER_AS_MICROSECONDS(timer, micro) micro = (ACR_Time_t)((timer.tv_sec*ACR_MICRO_PER_SEC)+timer.tv_usec)
        #endif
        #ifdef ACR_COMPILER_GCC
            // included for gettimeofday()
            #include <sys/time.h>
            #define ACR_HAS_TIMER ACR_BOOL_TRUE
            typedef struct timeval ACR_Timer_t;
            #define ACR_TIMER_START(timer) gettimeofday(&timer,ACR_NULL)
            #define ACR_TIMER_AS_MICROSECONDS(timer, micro) micro = (ACR_Time_t)((timer.tv_sec*ACR_MICRO_PER_SEC)+timer.tv_usec)
        #endif
    #endif // #ifndef ACR_CONFIG_NO_LIBC

    #ifndef ACR_HAS_TIMER
        #ifdef ACR_CONFIG_WIN_NATIVE
            #define ACR_HAS_TIMER ACR_BOOL_TRUE
            typedef LARGE_INTEGER ACR_Timer_t;
            #define ACR_TIMER_START(timer) QueryPerformanceCounter(&timer)
            #define ACR_TIMER_AS_MICROSECONDS(timer, micro)\
                    {\
                        LARGE_INTEGER countsPerSecond;\
                        QueryPerformanceFrequency(&countsPerSecond);\
                        micro = 0;\
                        if(countsPerSecond.QuadPart > 0)\
                        {\
                            micro += (ACR_Time_t)((timer.QuadPart / countsPerSecond.QuadPart) * ACR_MICRO_PER_SEC);\
                            micro += (ACR_Time_t)(((timer.QuadPart % countsPerSecond.QuadPart) * ACR_MICRO_PER_SEC) / (countsPerSecond.QuadPart * ACR_MICRO_PER_SEC));\
                        }\
                    }
        #endif // #ifdef ACR_CONFIG_WIN_NATIVE
    #endif // #if ACR_HAS_TIMER == ACR_BOOL_FALSE

#endif // #ifndef ACR_CONFIG_NO_RTC

#ifndef ACR_HAS_TIMER
    #define ACR_HAS_TIMER ACR_BOOL_FALSE
#endif // #ifndef ACR_HAS_RTC

#if ACR_HAS_TIMER == ACR_BOOL_FALSE

    /** struct to store seconds and microseconds
    */
    typedef struct ACR_Timer_s
    {
        // Note: standard definition is type long but to avoid
        //       the year 2038 problem its better to use the
        //       standardized time type.
        //       see the discussion about "What is a multi-byte value?"
        //       under TYPES AND DEFINES - ENDIANNESS in public.h for details
        ACR_Time_t tv_sec;
        ACR_Time_t tv_usec;
    } ACR_Timer_t;

    // without libc or windows there is no 
    // interface to a standard operating 
    // system's real-time clock.
    // see ACR_TimeProcessMicroTick() for how
    // to simulate a timer
    // Note: src/ACR/common.c must be added to any project
    //       that wishes to use ACR/common.h
    #include "ACR/common.h"

    #define ACR_TIMER_START(timer) ACR_TimerStart(&timer);

    /** converts a timer to a microseconds value
        \param timer the timer
        \param micro the number of microseconds
    */
    #define ACR_TIMER_AS_MICROSECONDS(timer, micro) micro = (ACR_Time_t)((timer.tv_sec*ACR_MICRO_PER_SEC)+timer.tv_usec)

#endif // #if ACR_HAS_TIMER == ACR_BOOL_FALSE

/** get the number of microseconds difference between two timers
    \param timerA a timer
    \param timerB a timer
    \param diff the number of microseconds as ACR_Time_t between timerA and timerB
    \param comp as ACR_Info_t value ACR_INFO_GREATER if timerA is greater
                ACR_INFO_LESS if timerA is less
                ACR_INFO_EQUAL if timerA and timerB are equal
*/
#define ACR_TIMER_DIFF_MICRO(timerA, timerB, diff, comp)\
        {\
            ACR_Time_t timerAMicro;\
            ACR_Time_t timerBMicro;\
            ACR_TIMER_AS_MICROSECONDS(timerA,timerAMicro);\
            ACR_TIMER_AS_MICROSECONDS(timerB,timerBMicro);\
            if(timerAMicro > timerBMicro)\
            {\
                diff = (ACR_Time_t)(timerAMicro - timerBMicro);\
                comp = ACR_INFO_GREATER;\
            }\
            else if (timerAMicro < timerBMicro)\
            {\
                diff = (ACR_Time_t)(timerBMicro - timerAMicro);\
                comp = ACR_INFO_LESS;\
            }\
            else\
            {\
                diff = 0;\
                comp = ACR_INFO_EQUAL;\
            }\
        }

#endif
