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
/** \file test_public_bool.c

    application to test "ACR/public/public_bool.h"

*/
#include "ACR/public/public_bool.h"

// included for ACR_UNUSED, ACR_FAILURE, and ACR_SUCCESS
#include "ACR/public/public_functions.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_debug.h"

//
// MAIN
//

int main(int argc, char** argv)
{
	int result = ACR_SUCCESS;

	ACR_UNUSED(argc);
	ACR_UNUSED(argv);

	ACR_Bool_t testTrue = ACR_BOOL_TRUE;
	if(testTrue)
	{
		ACR_DEBUG_PRINT(1,"OK Test is true");
	}
	else
	{
		ACR_DEBUG_PRINT(2,"ERROR Test should be true");
		result = ACR_FAILURE;
	}

	ACR_Bool_t testFalse = ACR_BOOL_FALSE;
	if(testFalse)
	{
		ACR_DEBUG_PRINT(3,"ERROR Test should be false");
	}
	else
	{
		ACR_DEBUG_PRINT(4,"OK Test is false");
		result = ACR_FAILURE;
	}

	return result;
}
