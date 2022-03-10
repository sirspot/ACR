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
/** \file json.h

    public functions for access to the ACR_JsonObj_t type

*/
#ifndef _ACR_JSON_H_
#define _ACR_JSON_H_

// included for ACR_String_t
#include "ACR/public/public_string.h"

/** predefined object type
*/
typedef struct ACR_JsonObj_s ACR_JsonObj_t;

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

/** allocate json data
	\param mePtr location to store the pointer
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_JsonNew(
	ACR_JsonObj_t** mePtr);

/** free a json data
	\param mePtr location of the pointer, which will
	       be set to ACR_NULL after the memory is freed
*/
void ACR_JsonDelete(
	ACR_JsonObj_t** mePtr);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
