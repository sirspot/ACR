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

/** \file timer.h

    Functions for working with timers.

*/
#ifndef _ACR_TIMER_H_
#define _ACR_TIMER_H_

// included for ACR_Bool_t
#include "ACR/public/public_bool.h"

// included for ACR_Timer_t and timer macros
#include "ACR/public/public_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

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
ACR_Time_t ACR_TimerElapse(
    ACR_Timer_t* me);

#ifdef __cplusplus
}
#endif

#endif
