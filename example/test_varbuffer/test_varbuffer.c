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
/** \file test_varbuffer.c

    application to test buffer struct, macros, and functions

*/
#include "ACR/varbuffer.h"

//
// PROTOTYPES
//

/** simple example to use a variable length buffer on the stack
*/
int StackTest(void);

/** simple example to use a variable length buffer on the heap
*/
int HeapTest(void);

/** simple example to use a variable length buffer at a low level
*/
int LowLevelTest(void);

/** a more complex test that takes into account malloc
    option and prints debug messages as the test is run
*/
int VerboseTest(void);

//
// MAIN
//

int main(int argc, char** argv)
{
	int result = ACR_SUCCESS;

	ACR_UNUSED(argc);
	ACR_UNUSED(argv);

	result |= StackTest();
	result |= HeapTest();
	result |= LowLevelTest();

	result |= VerboseTest();

	return result;
}

//
// IMPLEMENTATION
//

/**********************************************************/
int StackTest(void)
{
	int result = ACR_SUCCESS;
	ACR_VarBuffer_t varbuffer;

	ACR_VarBufferInit(&varbuffer);
	if(ACR_VarBufferAllocate(&varbuffer, 5000) == ACR_INFO_OK)
	{
		//
		// OK - 5000 byte buffer allocated
		//

		// set the length and clear the buffer
		ACR_VarBufferSetLength(&varbuffer, 1000);
		ACR_VarBufferClear(&varbuffer);

		// set the length and append some data
		ACR_VarBufferSetLength(&varbuffer, 0);
		ACR_VarBufferAppend(&varbuffer, "data", 4);
	}
	else
	{
		// failed to allocate 5000 bytes
		result = ACR_FAILURE;
	}
	ACR_VarBufferDeInit(&varbuffer);

	return result;
}

/**********************************************************/
int HeapTest(void)
{
	int result = ACR_SUCCESS;
	ACR_VarBuffer_t* varbufferPtr;

	ACR_VarBufferNew(&varbufferPtr);
	if(ACR_VarBufferAllocate(varbufferPtr, 5000) == ACR_INFO_OK)
	{
		//
		// OK - 5000 byte buffer ready for use
		//

		// set the length and clear the buffer
		ACR_VarBufferSetLength(varbufferPtr, 1000);
		ACR_VarBufferClear(varbufferPtr);

		// set the length and append some data
		ACR_VarBufferSetLength(varbufferPtr, 0);
		ACR_VarBufferAppend(varbufferPtr, "data", 4);
	}
	else
	{
		// failed to allocate 5000 bytes
		result = ACR_FAILURE;
	}
	ACR_VarBufferDelete(&varbufferPtr);

	return result;
}

/**********************************************************/
int LowLevelTest(void)
{
	ACR_VAR_BUFFER(varbuffer);

	ACR_VAR_BUFFER_ALLOC(varbuffer, 5000);
	if(ACR_VAR_BUFFER_IS_VALID(varbuffer))
	{
		//
		// OK - 5000 byte buffer ready for use
		//

		// set the length and clear the buffer
		ACR_VAR_BUFFER_SET_LENGTH(varbuffer, 1000);
		ACR_BUFFER_CLEAR(varbuffer.m_Buffer);

		// reset the length and append some data
		ACR_VAR_BUFFER_RESET(varbuffer);
		ACR_VAR_BUFFER_APPEND(varbuffer, (void*)"data", 4);

		// done with the buffer
		ACR_VAR_BUFFER_FREE(varbuffer);
	}
	else
	{
		// cannot allocate 5000 bytes
		return ACR_FAILURE;
	}

	return ACR_SUCCESS;
}

/**********************************************************/
int VerboseTest(void)
{
	ACR_VAR_BUFFER(varbuffer);
	ACR_Length_t testAllocateBytes = 5000;

	ACR_DEBUG_PRINT(1, "TEST allocate %d bytes", (int)testAllocateBytes);
	ACR_VAR_BUFFER_ALLOC(varbuffer, testAllocateBytes);

	#if ACR_HAS_MALLOC == ACR_BOOL_TRUE
		if(ACR_VAR_BUFFER_GET_MAX_LENGTH(varbuffer) != testAllocateBytes)
		{
			ACR_DEBUG_PRINT(2, "FAIL varbuffer max length is %d", (int)varbuffer.m_MaxLength);
			return ACR_FAILURE;
		}
		else
		{
			ACR_DEBUG_PRINT(3, "PASS allocated %d bytes", (int)varbuffer.m_MaxLength);
		}
	#else
		if(ACR_VAR_BUFFER_GET_MAX_LENGTH(varbuffer) != 0)
		{
			ACR_DEBUG_PRINT(4, "FAIL varbuffer max length is %d", (int)varbuffer.m_MaxLength);
			return ACR_FAILURE;
		}
		else
		{
			ACR_DEBUG_PRINT(5, "PASS malloc is not available");
		}
	#endif

	ACR_DEBUG_PRINT(6, "TEST free %d bytes", (int)varbuffer.m_MaxLength);
	ACR_VAR_BUFFER_FREE(varbuffer);

	if(ACR_VAR_BUFFER_GET_MAX_LENGTH(varbuffer) != 0)
	{
		ACR_DEBUG_PRINT(7, "FAIL varbuffer max length is %d", (int)varbuffer.m_MaxLength);
		return ACR_FAILURE;
	}
	else
	{
		ACR_DEBUG_PRINT(8, "PASS varbuffer max length is zero");
	}

	return ACR_SUCCESS;
}
