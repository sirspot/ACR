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
/** \file test_public_alignedbuffer.c

    application to test "ACR/public/public_alignedbuffer.h"

*/
#include "ACR/public/public_alignedbuffer.h"

// included for ACR_UNUSED, ACR_FAILURE, and ACR_SUCCESS
#include "ACR/public/public_functions.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_debug.h"

// included for ACR_Length_t and ACR_PointerValue_t
#include "ACR/public/public_memory.h"

//
// MAIN
//

int main(int argc, char** argv)
{
	int result = ACR_SUCCESS;

	ACR_UNUSED(argc);
	ACR_UNUSED(argv);

    char memoryForAlignedBuffer[800] = { 0 };
    ACR_Length_t lengthForAlignedBuffer = (800 - 0xFF);
    char* alignedBufferPointer = (char*)(((ACR_PointerValue_t)memoryForAlignedBuffer) & (~0xFF));

    ACR_DEBUG_PRINT(1, "OK testing with %d bytes at %p", (int)lengthForAlignedBuffer, alignedBufferPointer);

    char* alignedBufferPointer0 = &alignedBufferPointer[0];
    char* alignedBufferPointer16 = &alignedBufferPointer[16];
    ACR_Length_t lengthAvailable;
    char* alignedPointer;
    int bits;

    ACR_ALIGNED_BUFFER(alignedBuffer);

    bits = 32;
    ACR_ALIGNED_BUFFER_SET_MEMORY_ALIGNED_TO(alignedBuffer, alignedBufferPointer, lengthForAlignedBuffer, bits);
    alignedPointer = (char*)ACR_ALIGNED_BUFFER_GET_MEMORY(alignedBuffer);
    lengthAvailable = ACR_ALIGNED_BUFFER_GET_LENGTH(alignedBuffer);
    if(alignedPointer == alignedBufferPointer0)
    {
        ACR_Length_t lengthForAlignedBufferExpected = (ACR_Length_t)(alignedBuffer.m_UnalignedBuffer.m_Length - ((ACR_PointerValue_t)alignedBufferPointer0 - (ACR_PointerValue_t)alignedBuffer.m_UnalignedBuffer.m_Pointer));
        if(lengthAvailable == lengthForAlignedBufferExpected)
        {
            ACR_DEBUG_PRINT(2, "OK %dbit aligned buffer at %p has length %d", bits, alignedPointer, (int)lengthAvailable);
        }
        else
        {
            ACR_DEBUG_PRINT(3, "ERROR %dbit aligned buffer length is off by %d", bits, (int)(lengthForAlignedBufferExpected - lengthAvailable));
        }
    }
    else
    {
        ACR_DEBUG_PRINT(4, "ERROR %dbit aligned buffer pointer is %p but expected %p", bits, alignedPointer, alignedBufferPointer0);
    }

    bits = 16;
    ACR_ALIGNED_BUFFER_SET_MEMORY_ALIGNED_TO(alignedBuffer, alignedBufferPointer + 1, lengthForAlignedBuffer - 1, bits);
    alignedPointer = (char*)ACR_ALIGNED_BUFFER_GET_MEMORY(alignedBuffer);
    lengthAvailable = ACR_ALIGNED_BUFFER_GET_LENGTH(alignedBuffer);
    if(alignedPointer == alignedBufferPointer16)
    {
        ACR_Length_t lengthForAlignedBufferExpected = (ACR_Length_t)(alignedBuffer.m_UnalignedBuffer.m_Length - ((ACR_PointerValue_t)alignedBufferPointer16 - (ACR_PointerValue_t)alignedBuffer.m_UnalignedBuffer.m_Pointer));
        if(lengthAvailable == lengthForAlignedBufferExpected)
        {
            ACR_DEBUG_PRINT(5, "OK %dbit aligned buffer at %p has length %d", bits, alignedPointer, (int)lengthAvailable);
        }
        else
        {
            ACR_DEBUG_PRINT(6, "ERROR %dbit aligned buffer length is off by %d", bits, (int)(lengthForAlignedBufferExpected - lengthAvailable));
        }
    }
    else
    {
        ACR_DEBUG_PRINT(7, "ERROR %dbit aligned buffer pointer is %p but expected %p", bits, alignedPointer, alignedBufferPointer0);
    }

	ACR_ALIGNED_BUFFER_FREE(alignedBuffer);

	return result;
}
