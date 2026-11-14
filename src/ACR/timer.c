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
/** \file timer.c

*/
#include "ACR/timer.h"

// included for ACR_Info_t and comparison values
#include "ACR/public/public_info.h"

// included for ACR_MICRO_PER_SEC
#include "ACR/public/public_dates_and_times.h"

// simulated clock state is owned by datetime.c
extern ACR_Bool_t g_ACRSimRtcTimeIsSet;
extern ACR_Time_t g_ACRSimRtcTime;
extern ACR_Bool_t g_ACRSimRtcTimeMicroIsSet;
extern ACR_Time_t g_ACRSimRtcTimeMicro;

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - TIMER
//
////////////////////////////////////////////////////////////

ACR_Bool_t ACR_TimerStart(
    ACR_Timer_t* me)
{
    if(me)
    {
        #if ACR_HAS_TIMER == ACR_BOOL_TRUE

            if(ACR_TIMER_START((*me)))
            {
                return ACR_BOOL_TRUE;
            }

        #else

            if(g_ACRSimRtcTimeIsSet || g_ACRSimRtcTimeMicroIsSet)
            {
                me->tv_sec = g_ACRSimRtcTime + (g_ACRSimRtcTimeMicro / ACR_MICRO_PER_SEC);
                me->tv_usec = g_ACRSimRtcTimeMicro % ACR_MICRO_PER_SEC;
                return ACR_BOOL_TRUE;
            }
            else
            {
                // time has never been set and a timer is not available.
                // set timer to zero.
                me->tv_sec = 0;
                me->tv_usec = 0;
            }

        #endif // #if ACR_HAS_RTC == ACR_BOOL_TRUE
    }

    return ACR_BOOL_FALSE;
}

ACR_Time_t ACR_TimerElapse(
    ACR_Timer_t* me)
{
    ACR_Time_t elapseMicro = 0;
    ACR_Info_t comp;

    if(me)
    {
        ACR_Timer_t newTimer;
        if(ACR_TimerStart(&newTimer))
        {
            // (*me)    = timerA (in the past)
            // newTimer = timerB (current time)
            ACR_TIMER_DIFF_MICRO((*me), newTimer, elapseMicro, comp);
            if(comp == ACR_INFO_GREATER)
            {
                // the timer in the past should not be greater
                // than the current time. return 0 to indicate
                // that effectively no time has elapsed.
                elapseMicro = 0;
            }
        }
    }

    return elapseMicro;
}
