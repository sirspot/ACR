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
/** \file test_public_functions.c

    application to test "ACR/public/public_functions.h"

*/
#include "ACR/public/public_functions.h"

// included for ACR_NULL
#include "ACR/public/public_memory.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_debug.h"

// define a list of all callback names
enum CallbackExample_e
{
    CBEX_1 = 0,
    CBEX_2,
    CBEX_3,

    CBEX_COUNT
};

// define the callback function prototypes
ACR_TYPEDEF_CALLBACK(CallbackExample_t, void)(int, void*);
    void CbEx1(int,void*);
    void CbEx2(int,void*);
    void CbEx3(int,void*);

// create a lookup table of the callback functions
CallbackExample_t g_CbEx[CBEX_COUNT+1] = 
{
    CbEx1, // CBEX_1
    CbEx2, // CBEX_2
    CbEx3, // CBEX_3

    ACR_NULL
};

//
// MAIN
//

int main(int argc, char** argv)
{
	int result = ACR_SUCCESS;

	ACR_UNUSED(argc);
	ACR_UNUSED(argv);

    // just use one callback function
    g_CbEx[CBEX_1](0, "Test one callback function");

    // loop through all callback functions
    unsigned int cbIndex = 0;
    while(cbIndex < CBEX_COUNT)
    {
        g_CbEx[cbIndex]((cbIndex+1), ACR_NULL);
        cbIndex++;
    }

	return result;
}

// complete the definition of the first callback function
void CbEx1(int a, void* b)
{
    if(b)
    {
        ACR_DEBUG_PRINT(a,"CbEx1 has string \"%s\"", (char*)b);
    }
    else
    {
        ACR_DEBUG_PRINT(a,"CbEx1");
    }
}

// complete the definition of the second callback function
void CbEx2(int a, void* b)
{
    ACR_UNUSED(b);
    ACR_DEBUG_PRINT(a,"CbEx2");
}

// complete the definition of the third callback function
void CbEx3(int a, void* b)
{
    ACR_UNUSED(b);
    ACR_DEBUG_PRINT(a,"CbEx3");
}
