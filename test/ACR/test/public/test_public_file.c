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
/** \file test_public_file.c

    application to test "ACR/public/public_file.h"

*/
#include "ACR/public/public_file.h"

// included for ACR_UNUSED, ACR_FAILURE, and ACR_SUCCESS
#include "ACR/public/public_functions.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_debug.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_unique_strings.h"

//
// MAIN
//

ACR_Info_t _TestFileRead(
    ACR_VarBuffer_t* dest,
    void* userPtr)
{
    int* callCount = (int*)userPtr;
    if(callCount)
    {
        (*callCount) = (*callCount) + 1;
    }
    return ACR_INFO_OK;
}

int main(int argc, char** argv)
{
	int result = ACR_SUCCESS;

	ACR_UNUSED(argc);
	ACR_UNUSED(argv);

    ACR_FILE_INTERFACE(fileInterface);
    fileInterface.m_Read = _TestFileRead;
    int callCount = 0;
    ACR_VAR_BUFFER(varBuffer);
    ACR_Info_t readResult = fileInterface.m_Read(&varBuffer, &callCount);

	ACR_DEBUG_PRINT(1,"OK read result is %s and call count is %d", readResult == ACR_INFO_OK ? (const char*)ACR_INFO_STR_OK : (const char*)ACR_INFO_STR_ERROR, callCount);

	return result;
}
