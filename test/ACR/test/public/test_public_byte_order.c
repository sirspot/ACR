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
/** \file test_public_byte_order.c

    application to test "ACR/public/public_byte_order.h"

*/
#include "ACR/public/public_byte_order.h"

// included for ACR_UNUSED, ACR_FAILURE, and ACR_SUCCESS
#include "ACR/public/public_functions.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_debug.h"

// included for ACR_INFO_STR_FALSE, ACR_INFO_STR_TRUE
#include "ACR/public/public_unique_strings.h"

//
// MAIN
//

int main(int argc, char** argv)
{
	int result = ACR_SUCCESS;

	ACR_UNUSED(argc);
	ACR_UNUSED(argv);

    #if ACR_ENDIAN_DYNAMIC == ACR_BOOL_TRUE
    ACR_DEBUG_PRINT(1, "OK: ACR_ENDIAN_DYNAMIC is true");
    #endif

    //
    // 16 bit tests
    //
    ACR_Unsigned_16bit_t systemEndianValue = 0x0001;
    ACR_Unsigned_16bit_t bigEndian = ACR_BYTE_ORDER_16(systemEndianValue);
    // Note: disable warning C4127: conditional expression is constant
    if(ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)
    {
        // system is little endian
        if(systemEndianValue == bigEndian)
        {
            // ACR_IS_BIG_ENDIAN is not set properly or
            // ACR_BYTE_ORDER_16 is not working properly
            ACR_DEBUG_PRINT(2, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_16 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_INFO_STR_FALSE:ACR_INFO_STR_TRUE);
            result = ACR_FAILURE;
        }
        else
        {
            ACR_DEBUG_PRINT(3, "OK: Little Endian ACR_IS_BIG_ENDIAN is %s", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_INFO_STR_FALSE:ACR_INFO_STR_TRUE);
        }
    }
    else
    {
        // system is big endian
        if(systemEndianValue != bigEndian)
        {
            // ACR_IS_BIG_ENDIAN is not set properly or
            // ACR_BYTE_ORDER_16 is not working properly
            ACR_DEBUG_PRINT(4, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_16 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_INFO_STR_FALSE:ACR_INFO_STR_TRUE);
            result = ACR_FAILURE;
        }
        else
        {
            ACR_DEBUG_PRINT(5, "OK: Big Endian ACR_IS_BIG_ENDIAN is %s", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_INFO_STR_FALSE:ACR_INFO_STR_TRUE);
        }
    }
    systemEndianValue = ACR_BYTE_ORDER_16(bigEndian);
    if(systemEndianValue != 0x0001)
    {
        // ACR_BYTE_ORDER_16 is not working properly
        ACR_DEBUG_PRINT(6, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_16 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_INFO_STR_FALSE:ACR_INFO_STR_TRUE);
        result = ACR_FAILURE;
    }

    //
    // 32 bit tests
    //
    ACR_Unsigned_32bit_t systemEndianValue32 = 0x00000001UL;
    ACR_Unsigned_32bit_t bigEndian32 = ACR_BYTE_ORDER_32(systemEndianValue32);
    systemEndianValue32 = ACR_BYTE_ORDER_32(bigEndian32);
    if(systemEndianValue32 != 0x00000001UL)
    {
        // ACR_BYTE_ORDER_32 is not working properly
        ACR_DEBUG_PRINT(7, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_32 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_INFO_STR_FALSE:ACR_INFO_STR_TRUE);
        result = ACR_FAILURE;
    }

    //
    // 64 bit tests
    //
    #if ACR_USE_64BIT == ACR_BOOL_TRUE
    ACR_Unsigned_64bit_t systemEndianValue64 = 0x0000000000000001ULL;
    ACR_Unsigned_64bit_t bigEndian64 = ACR_BYTE_ORDER_64(systemEndianValue64);
    systemEndianValue64 = ACR_BYTE_ORDER_32(bigEndian64);
    if(systemEndianValue32 != 0x0000000000000001ULL)
    {
        // ACR_BYTE_ORDER_64 is not working properly
        ACR_DEBUG_PRINT(8, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_64 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_INFO_STR_FALSE:ACR_INFO_STR_TRUE);
        result = ACR_FAILURE;
    }
    #endif

	return result;
}
