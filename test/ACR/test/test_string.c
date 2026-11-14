/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2020 Adam C. Rosenberg

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
/** \file test_string.c
    
*/
#include "ACR/string.h"

// included for ACR_UNUSED
#include "ACR/public/public_functions.h"

//
// PROTOTYPES
//

/** simple example to use a string on the stack
*/
int StackTest(void);

/** verify UTF-8 byte count helper behavior
*/
int Utf8ByteCountTest(void);

//
// MAIN
//

int main(int argc, char** argv)
{
	int result = ACR_SUCCESS;

	ACR_UNUSED(argc);
	ACR_UNUSED(argv);

	result |= StackTest();
	result |= Utf8ByteCountTest();

	return result;
}

//
// IMPLEMENTATION
//

/**********************************************************/
int StackTest(void)
{
	int result = ACR_SUCCESS;
	ACR_String_t str;

	ACR_StringInit(&str);
	ACR_StringDeInit(&str);

	return result;
}

/**********************************************************/
int Utf8ByteCountTest(void)
{
	int result = ACR_SUCCESS;
	ACR_Byte_t nextByte = 0xE2;
	ACR_Length_t byteCount;

	if(ACR_UTF8_BYTE_COUNT(0x41) != 1)
	{
		ACR_DEBUG_PRINT(1, "FAIL ASCII UTF-8 byte count");
		result = ACR_FAILURE;
	}
	else
	{
		ACR_DEBUG_PRINT(2, "PASS ASCII UTF-8 byte count");
	}

	if(ACR_UTF8_BYTE_COUNT(0xC2) != 2)
	{
		ACR_DEBUG_PRINT(3, "FAIL two-byte UTF-8 byte count");
		result = ACR_FAILURE;
	}
	else
	{
		ACR_DEBUG_PRINT(4, "PASS two-byte UTF-8 byte count");
	}

	if(ACR_UTF8_BYTE_COUNT(0xE2) != 3)
	{
		ACR_DEBUG_PRINT(5, "FAIL three-byte UTF-8 byte count");
		result = ACR_FAILURE;
	}
	else
	{
		ACR_DEBUG_PRINT(6, "PASS three-byte UTF-8 byte count");
	}

	if(ACR_UTF8_BYTE_COUNT(0xF0) != 4)
	{
		ACR_DEBUG_PRINT(7, "FAIL four-byte UTF-8 byte count");
		result = ACR_FAILURE;
	}
	else
	{
		ACR_DEBUG_PRINT(8, "PASS four-byte UTF-8 byte count");
	}

	byteCount = ACR_UTF8_BYTE_COUNT(nextByte++);
	if(byteCount != 3 || nextByte != 0xE3)
	{
		ACR_DEBUG_PRINT(9, "FAIL UTF-8 byte count evaluates argument once");
		result = ACR_FAILURE;
	}
	else
	{
		ACR_DEBUG_PRINT(10, "PASS UTF-8 byte count evaluates argument once");
	}

	return result;
}

