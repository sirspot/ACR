/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2019 Adam C. Rosenberg

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
/** \file string.h

    functions for access to the ACR_String_t type

*/
#ifndef _ACR_STRING_H_
#define _ACR_STRING_H_

#include "ACR/public.h"

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
extern "C" {                                              //
#endif                                                    //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/** prepare a string allocated on the heap
	Note: this automatically calls ACR_StringInit() on the
	      new string after allocating its memory
	\param mePtr location to store the pointer for the new string
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_StringNew(
	ACR_String_t** mePtr);

/** free a string allocated on the heap
    Note: this automatically calls ACR_StringDeInit() on
	      the string before freeing its memory
	\param mePtr location of the pointer for the string, which will
	       be set to ACR_NULL after the memory is freed
*/
void ACR_StringDelete(
	ACR_String_t** mePtr);

/** prepare a string
*/
void ACR_StringInit(
	ACR_String_t* me);

/** free string memory
*/
void ACR_StringDeInit(
	ACR_String_t* me);



////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
