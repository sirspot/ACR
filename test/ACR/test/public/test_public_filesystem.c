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
/** \file test_public_filesystem.c

    application to test "ACR/public/public_filesystem.h"

*/
#include "ACR/public/public_filesystem.h"

// included for ACR_UNUSED, ACR_FAILURE, and ACR_SUCCESS
#include "ACR/public/public_functions.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_debug.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

//
// MAIN
//

int main(int argc, char** argv)
{
	int result = ACR_SUCCESS;

	ACR_UNUSED(argc);
	ACR_UNUSED(argv);

    const char path[] = "test_public_filesystem.txt";
    ACR_Length_t length;
    ACR_BUFFER(buffer);
    ACR_Bool_t append;
    ACR_Length_t startPos;

    append = ACR_BOOL_FALSE;
    ACR_BUFFER_SET_DATA(buffer, path, sizeof(path)-1);
    ACR_FILESYSTEM_FILE_WRITE(path,length,buffer,append);
	ACR_DEBUG_PRINT(1,"OK %d bytes written to %s", (int)length, path);

    ACR_FILESYSTEM_FILE_LENGTH(path,length);
	ACR_DEBUG_PRINT(1,"OK %s length is %d", path, (int)length);

    startPos = 0;
    ACR_BUFFER_ALLOC(buffer,length);
    ACR_FILESYSTEM_FILE_READ(path,length,buffer,startPos);
	ACR_DEBUG_PRINT(1,"OK %d bytes read from %s", (int)length, path);
	ACR_DEBUG_PRINT(1,"OK read: \"%.*s\"", (int)buffer.m_Length, (const char*)buffer.m_Pointer);
    ACR_BUFFER_FREE(buffer);
  
	return result;
}
