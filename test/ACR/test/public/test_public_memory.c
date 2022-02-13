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
/** \file test_public_memory.c

    application to test "ACR/public/public_memory.h"

*/
#include "ACR/public/public_memory.h"

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

    if(ACR_USE_64BIT)
    {
        if(sizeof(ACR_Length_t) == 8)
        {
	        ACR_DEBUG_PRINT(1,"OK: ACR_Length_t is %d bytes", (int)sizeof(ACR_Length_t));
        }
        else
        {
	        ACR_DEBUG_PRINT(2,"ERROR: ACR_Length_t is %d bytes", (int)sizeof(ACR_Length_t));
        }
    }
    else
    {
        if(sizeof(ACR_Length_t) == 4)
        {
	        ACR_DEBUG_PRINT(3,"OK: ACR_Length_t is %d bytes", (int)sizeof(ACR_Length_t));
        }
        else
        {
	        ACR_DEBUG_PRINT(4,"ERROR: ACR_Length_t is %d bytes", (int)sizeof(ACR_Length_t));
        }
    }

    ACR_Length_t length = ACR_MAX_LENGTH;
    length += 1;
    if(length != 0)
    {
        // ACR_MAX_LENGTH value is incorrect
        ACR_DEBUG_PRINT(5, "ERROR: ACR_MAX_LENGTH value is incorrect");
        result = ACR_FAILURE;
    }
    else
    {
        #if ACR_USE_64BIT == ACR_BOOL_TRUE
        ACR_DEBUG_PRINT(6, "OK: ACR_MAX_LENGTH value is %llu", ACR_MAX_LENGTH);
        #else
        ACR_DEBUG_PRINT(7, "OK: ACR_MAX_LENGTH value is %lu", ACR_MAX_LENGTH);
        #endif
    }

    #ifndef ACR_CONFIG_NO_LIBC
    ACR_DEBUG_PRINT(8, "OK: Continue test with libC");
    #else
    ACR_DEBUG_PRINT(9, "OK: Continue test without libC");
    #endif

    // create 2 buffers and make sure no values are empty
    unsigned char clearCheck1 = ACR_EMPTY_VALUE;
    unsigned char clearCheck2 = ACR_EMPTY_VALUE;
    unsigned char buffer1[8] = {0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7};
    unsigned char buffer2[8] = {0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7};
    for(int i = 0; i < sizeof(buffer1); i++)
    {
        clearCheck1 |= buffer1[i];
        clearCheck2 |= buffer2[i];
        if(buffer1[i] == ACR_EMPTY_VALUE)
        {
            ACR_DEBUG_PRINT(10, "ERROR: buffer1[%d] is empty", i);
            result = ACR_FAILURE;
        }
        if(buffer2[i] == ACR_EMPTY_VALUE)
        {
            ACR_DEBUG_PRINT(11, "ERROR: buffer2[%d] is empty", i);
            result = ACR_FAILURE;
        }
    }
    if(clearCheck1 != ACR_EMPTY_VALUE)
    {
        ACR_DEBUG_PRINT(12, "OK: buffer1 is not clear");
    }
    if(clearCheck2 != ACR_EMPTY_VALUE)
    {
        ACR_DEBUG_PRINT(13, "OK: buffer2 is not clear");
    }

    // clear buffer1 to test ACR_MEMSET
    ACR_DEBUG_PRINT(11, "OK: clearing buffer1");
    ACR_MEMSET(buffer1, ACR_EMPTY_VALUE, sizeof(buffer1));

    // make sure buffer1 is now cleared
    clearCheck1 = ACR_EMPTY_VALUE;
    for(int i = 0; i < sizeof(buffer1); i++)
    {
        clearCheck1 |= buffer1[i];
        if(buffer1[i] != ACR_EMPTY_VALUE)
        {
            ACR_DEBUG_PRINT(14, "ERROR: buffer1[%d] is %d but expected %d", i, (int)buffer1[i], ACR_EMPTY_VALUE);
            result = ACR_FAILURE;
            break;
        }
    }
    if(clearCheck1 == ACR_EMPTY_VALUE)
    {
        ACR_DEBUG_PRINT(15, "OK: buffer1 is clear");
    }

    // copy buffer2 into buffer1 to test ACR_MEMCPY
    ACR_DEBUG_PRINT(16, "OK: copying buffer2 to buffer1");
    ACR_MEMCPY(buffer1, buffer2, sizeof(buffer1));

    // make sure buffer1 has the same values as buffer2
    int mismatchIndex = -1;
    for(int i = 0; i < sizeof(buffer1); i++)
    {
        if(buffer1[i] != buffer2[i])
        {
            mismatchIndex = i;
            ACR_DEBUG_PRINT(16, "ERROR: buffer1[%d] is %d but expected %d", i, (int)buffer1[i], (int)buffer2[i]);
            result = ACR_FAILURE;
            break;
        }
    }
    if(mismatchIndex == -1)
    {
        ACR_DEBUG_PRINT(17, "OK: buffer1 has same data as buffer2");
    }

	return result;
}
