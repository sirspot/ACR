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
/** \file test_buffer.c

    application to test buffer struct, macros, and functions

*/
#include "ACR/buffer.h"

// comment/uncomment the following line to for testing private buffer functions
#define ACR_TEST_INCLUDE_PRIVATE

#ifdef ACR_TEST_INCLUDE_PRIVATE
// included for ACR_BufferObj_t
#include "ACR/private/private_buffer.h"
#endif

// included for ACR_UNUSED
#include "ACR/public/public_functions.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_debug.h"

//
// PROTOTYPES
//

/** use a buffer on the heap
*/
int HeapTest(void);

/** use a buffer on the heap with a file interface
*/
int FileInterfaceTest(void);

/** use a buffer on the stack
*/
int StackTest(void);

/** use a buffer at a low level
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

	result |= LowLevelTest();
	result |= VerboseTest();

#ifdef ACR_TEST_INCLUDE_PRIVATE
	result |= StackTest();
#else
	// OK - skip private tests
	ACR_DEBUG_PRINT(1, "TEST skipped private tests");
#endif // #ifdef ACR_TEST_INCLUDE_PRIVATE

	result |= HeapTest();
	result |= FileInterfaceTest();

	return result;
}

//
// IMPLEMENTATION
//

/**********************************************************/
int HeapTest(void)
{
	int result = ACR_SUCCESS;
	ACR_BufferObj_t* bufferPtr;

	ACR_BufferNew(&bufferPtr);
	if(ACR_BufferAllocate(bufferPtr, 10) == ACR_INFO_OK)
	{
		ACR_Byte_t compareValue = 0;
		ACR_Length_t shiftBytes = 9;
		ACR_Length_t bufferLength = ACR_BufferGetLength(bufferPtr);
		ACR_Byte_t byteValue;
		//
		// OK - buffer ready for use
		//

		// placing data to test shift right
		for (ACR_Length_t i = 0; i < bufferLength; i++)
		{
			byteValue = (ACR_Byte_t)(i % 256) + 1;
			ACR_BufferSetByteAt(bufferPtr, i, byteValue);
			if (i == (bufferLength - shiftBytes - 1))
			{
				compareValue = byteValue;
			}
		}
		ACR_BufferShift(bufferPtr, shiftBytes, ACR_INFO_RIGHT, ACR_BOOL_FALSE);
		ACR_BufferGetByteAt(bufferPtr, bufferLength - 1, &byteValue);
		if (byteValue != compareValue)
		{
			// failed to move the value at position
			// shiftBytes to the end of the buffer
			result = ACR_FAILURE;
		}

		// placing data to test shift left
		shiftBytes = 9;
		for (ACR_Length_t i = 0; i < bufferLength; i++)
		{
			byteValue = (ACR_Byte_t)(i % 256) + 1;
			ACR_BufferSetByteAt(bufferPtr, i, byteValue);
			if (i == shiftBytes)
			{
				compareValue = byteValue;
			}
		}
		ACR_BufferShift(bufferPtr, shiftBytes, ACR_INFO_LEFT, ACR_BOOL_FALSE);
		ACR_BufferGetByteAt(bufferPtr, 0, &byteValue);
		if (byteValue != compareValue)
		{
			// failed to move the value at position
			// shiftBytes to the start of the buffer
			result = ACR_FAILURE;
		}

		// use the same buffer object for a different
		// area of memory, which will automatically free
		// the dynamically allocated memory
		ACR_Byte_t smallArray[64];
		for (ACR_Length_t i = 0; i < 64; i++)
		{
			smallArray[i] = (ACR_Byte_t)(i + 64);
		}
		ACR_BufferGetByteAt(bufferPtr, 0, &byteValue);
		ACR_BufferSetData(bufferPtr, smallArray, sizeof(smallArray));
		ACR_BufferGetByteAt(bufferPtr, 0, &compareValue);
		if (byteValue == compareValue)
		{
			// failed to select the smallArray as the new buffer data
			result = ACR_FAILURE;
		}
		if (compareValue != 64)
		{
			// smallArray value at pos 0 should have been 64
			result = ACR_FAILURE;
		}

		// optional step to clear the buffer
		ACR_BufferClear(bufferPtr);
	}
	else
	{
		// failed to allocate 5000 bytes
		result = ACR_FAILURE;
	}
	ACR_BufferDelete(&bufferPtr);

	return result;
}

/**********************************************************/
int FileInterfaceTest(void)
{
	int result = ACR_SUCCESS;
	ACR_BufferObj_t* bufferPtr;

	ACR_BufferNew(&bufferPtr);
	if(ACR_BufferAllocate(bufferPtr, 1024) == ACR_INFO_OK)
	{
		ACR_FileInterface_t* bufferAsFile;
		if(ACR_BufferNewFileInterface(bufferPtr, &bufferAsFile) == ACR_INFO_OK)
		{
			

			if(ACR_BufferDeleteFileInterface(bufferPtr, &bufferAsFile) != ACR_INFO_OK)
			{
				// failed to delete file interface.
				// Note: this should only happen if the interface
				//       being deleted does not belong to the buffer
				//       that is trying to perform the deletion
				result = ACR_FAILURE;
			}
		}
		else
		{
			// failed to create file interface
			result = ACR_FAILURE;
		}
	}
	else
	{
		// failed to allocate 1024 bytes
		result = ACR_FAILURE;
	}
	ACR_BufferDelete(&bufferPtr);

	return result;
}

/**********************************************************/
int StackTest(void)
{
#ifdef ACR_TEST_INCLUDE_PRIVATE
	int result = ACR_SUCCESS;
	ACR_BufferObj_t buffer;

	ACR_BufferInit(&buffer);
	if (ACR_BufferAllocate(&buffer, 5000) == ACR_INFO_OK)
	{
		//
		// OK - 5000 byte buffer ready for use
		//

		// optional step to clear the buffer
		ACR_BufferClear(&buffer);
	}
	else
	{
		// failed to allocate 5000 bytes
		// Note: if ACR_CONFIG_NO_LIBC was defined then ACR_CONFIG_HEAP_SIZE
		//       can be defined in your project settings to increase or
		//       decrease the total amount of heap memory available.
		//       the default at this time is 2MB
		result = ACR_FAILURE;
	}
	ACR_BufferDeInit(&buffer);

	return result;
#else
	// OK - skip private tests
	return ACR_SUCCESS;
#endif // #ifdef ACR_TEST_INCLUDE_PRIVATE
}

/**********************************************************/
int LowLevelTest(void)
{
	ACR_BUFFER(buffer);

	ACR_BUFFER_ALLOC(buffer, 5000);
	if(ACR_BUFFER_IS_VALID(buffer))
	{
		//
		// OK - 5000 byte buffer ready for use
		//

		// optional step to clear the buffer
		ACR_BUFFER_CLEAR(buffer);

		// done with the buffer
		ACR_BUFFER_FREE(buffer);
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
	ACR_BUFFER(buffer);
	ACR_Length_t testAllocateBytes = 5000;

	ACR_DEBUG_PRINT(1, "TEST allocate %d bytes", (int)testAllocateBytes);
	ACR_BUFFER_ALLOC(buffer, testAllocateBytes);
	#if ACR_HAS_MALLOC == ACR_BOOL_TRUE
		if(ACR_BUFFER_GET_LENGTH(buffer) != testAllocateBytes)
		{
			ACR_DEBUG_PRINT(2, "FAIL buffer length is %d", (int)buffer.m_Length);
			return ACR_FAILURE;
		}
		else
		{
			ACR_DEBUG_PRINT(3, "PASS allocated %d bytes", (int)buffer.m_Length);
		}
	#else
		if(ACR_BUFFER_GET_LENGTH(buffer) != 0)
		{
			ACR_DEBUG_PRINT(4, "FAIL buffer length is %d", (int)buffer.m_Length);
			return ACR_FAILURE;
		}
		else
		{
			ACR_DEBUG_PRINT(5, "PASS malloc is not available");
		}
	#endif
	ACR_DEBUG_PRINT(6, "TEST free %d bytes", (int)buffer.m_Length);
	ACR_BUFFER_FREE(buffer);

	if(ACR_BUFFER_GET_LENGTH(buffer) != 0)
	{
		ACR_DEBUG_PRINT(7, "FAIL buffer length is %d", (int)buffer.m_Length);
		return ACR_FAILURE;
	}
	else
	{
		ACR_DEBUG_PRINT(8, "PASS buffer length is zero");
	}

	return ACR_SUCCESS;
}
