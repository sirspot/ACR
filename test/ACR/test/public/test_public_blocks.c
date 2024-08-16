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
/** \file test_public_blocks.c

    application to test "ACR/public/public_blocks.h"

*/
#include "ACR/public/public_blocks.h"

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

    ACR_Block_t maxBlockCount = ACR_MAX_BLOCK;
    if ((maxBlockCount + 1) == 0)
    {
        #if ACR_USE_64BIT == ACR_BOOL_TRUE
            ACR_DEBUG_PRINT(1, "OK max block count is %llu", maxBlockCount);
        #else
            ACR_DEBUG_PRINT(2, "OK max block count is %lu", maxBlockCount);
        #endif
    }
    else
    {
        ACR_DEBUG_PRINT(3, "ERROR max block count is incorrect");
    }

    // calculate the minimum number of blocks needed to store 743 bytes when
    // each block is only 10 bytes
    ACR_Block_t blockCount = ACR_MIN_BLOCKS_NEEDED_BY_SIZE(743, 10);
    if (blockCount == 75)
    {
        ACR_DEBUG_PRINT(4, "OK at least %d blocks needed for 743 bytes taken 10 at a time", (int)blockCount);
    }
    else
    {
        ACR_DEBUG_PRINT(5, "ERROR blocks needed is off by %d", (75-(int)blockCount));
    }

    // calculate the exact number of full blocks needed to store 1800 bytes when
    // each block is only 32 bytes and the number of bytes that will remain not
    // within a full block.
    ACR_Blocks_t blocks;
    ACR_LENGTH_TO_BLOCKS_BY_SIZE(blocks, 1800, 32);
    if (blocks.m_Blocks == 56)
    {
        ACR_DEBUG_PRINT(6, "OK %d blocks needed", (int)blocks.m_Blocks);
    }
    else
    {
        ACR_DEBUG_PRINT(7, "ERROR blocks needed is off by %d", (56 - (int)blocks.m_Blocks));
    }
    if (blocks.m_Bytes == 8)
    {
        ACR_DEBUG_PRINT(8, "OK %d bytes remain", (int)blocks.m_Bytes);
    }
    else
    {
        ACR_DEBUG_PRINT(9, "ERROR bytes remaining is off by %d", (8 - (int)blocks.m_Bytes));
    }

	return result;
}
