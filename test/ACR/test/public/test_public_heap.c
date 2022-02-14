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
/** \file test_public_heap.c

    application to test "ACR/public/public_heap.h"

*/
#include "ACR/public/public_heap.h"

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

#if ACR_HEAP_IS_GLOBAL == ACR_BOOL_FALSE
	ACR_DEBUG_PRINT(1,"OK using libC heap");
#else
	ACR_DEBUG_PRINT(2,"OK using ACR defined heap");
#endif

    void* memory = ACR_MALLOC(64);
    if(memory)
    {
	    ACR_DEBUG_PRINT(3,"OK 64 bytes allocated");
        void* newMemory = ACR_REALLOC(memory, 128);
        if(newMemory)
        {
            if(newMemory == memory)
            {
                ACR_DEBUG_PRINT(4,"OK expanded to 128 bytes");
            }
            else
            {
                ACR_DEBUG_PRINT(5,"OK reallocated to 128 bytes");
            }

            ACR_DEBUG_PRINT(6,"OK freeing new memory");
            ACR_FREE(newMemory);

            ACR_DEBUG_PRINT(7,"OK new memory freed");
        }
        else
        {
            ACR_DEBUG_PRINT(8,"ERROR could not reallocate to 128 bytes");
            
            ACR_DEBUG_PRINT(9,"OK freeing memory");
            ACR_FREE(memory);
            ACR_DEBUG_PRINT(10,"OK memory freed");
        }
    }
    else
    {
	    ACR_DEBUG_PRINT(11,"ERROR failed to allocated memory");
    }

	return result;
}
