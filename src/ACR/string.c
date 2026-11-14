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
/** \file string.c

    functions for access to the ACR_String_t type

*/
#include "ACR/string.h"

// included for ACR_Utf8ToUnicode and Unicode case conversion functions
#include "ACR/unicode.h"

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
ACR_Info_t ACR_StringNew(
	ACR_String_t** mePtr)
{
	ACR_Info_t result = ACR_INFO_ERROR;
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_BUFFER_ALLOC(buffer, sizeof(ACR_String_t));
		if(ACR_BUFFER_IS_VALID(buffer))
		{
			ACR_StringInit((ACR_String_t*)buffer.m_Pointer);
			result = ACR_INFO_OK;
		}
		(*mePtr) = (ACR_String_t*)buffer.m_Pointer;
	}
	return result;
}

/**********************************************************/
void ACR_StringDelete(
	ACR_String_t** mePtr)
{
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_StringDeInit((*mePtr));
		ACR_BUFFER_SET_DATA(buffer, (*mePtr), sizeof(ACR_String_t));
		ACR_BUFFER_FORCE_FREE(buffer);
		(*mePtr) = ACR_NULL;
	}
}

/**********************************************************/
void ACR_StringInit(
	ACR_String_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	me->m_Count = ACR_EMPTY_VALUE;
	me->m_Buffer.m_Pointer = ACR_NULL;
	me->m_Buffer.m_Length = ACR_ZERO_LENGTH;
}

/**********************************************************/
void ACR_StringDeInit(
	ACR_String_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_BUFFER_FREE(me->m_Buffer);
}

/**********************************************************/
ACR_String_t ACR_StringFromMemory(
    ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters)
{
    ACR_STRING(s);
    if(src != ACR_NULL)
    {
        ACR_Length_t remaining = srcLength;
        ACR_Byte_t* srcPtr = src;
        while((remaining > 0) && (s.m_Count < maxCharacters) && ((*srcPtr) != 0))
        {
            ACR_Length_t bytes = ACR_UTF8_BYTE_COUNT((*srcPtr));
            if(bytes > remaining)
            {
                break;
            }
            s.m_Count++;
            srcPtr += bytes;
            remaining -= bytes;
        }
        ACR_BUFFER_SET_DATA(s.m_Buffer, src, (srcLength - remaining));
    }
    return s;
}

/**********************************************************/
ACR_String_t ACR_StringFromReadOnlyMemory(
    const ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters)
{
    ACR_String_t s = ACR_StringFromMemory((ACR_Byte_t*)src, srcLength, maxCharacters);
    ACR_STRING_SET_READ_ONLY(s, ACR_BOOL_TRUE);
    return s;
}

/**********************************************************/
ACR_Info_t ACR_StringCompareToMemory(
    ACR_String_t string,
    const ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters,
    ACR_Info_t caseSensitive)
{
    if(src != ACR_NULL)
    {
        ACR_Count_t count = 0;
        // 0 = string
        // 1 = src
        ACR_Byte_t* srcPtr[2];
        ACR_Length_t bytes[2];
        int strIndex;
        ACR_Unicode_t c[2];
        srcPtr[0] = (ACR_Byte_t*)string.m_Buffer.m_Pointer;
        srcPtr[1] = (ACR_Byte_t*)src;
        while((srcLength > 0) && ((srcPtr[1][0]) != 0))
        {
            if(count == maxCharacters)
            {
                // finished comparing the max number of characters
                return ACR_INFO_EQUAL;
            }
            // count the next character using UTF8 byte counts
            bytes[1] = ACR_UTF8_BYTE_COUNT(srcPtr[1][0]);
            if(bytes[1] > srcLength)
            {
                // src is malformed UTF8 at the last
                // character so the last character of
                // src will be ignored
                break;
            }
            count++;
            if(count > string.m_Count)
            {
                // src has more characters than string
                return ACR_INFO_GREATER;
            }
            bytes[0] = ACR_UTF8_BYTE_COUNT(srcPtr[0][0]);
            // create the utf8 characters to compare
            strIndex = 0;
            do
            {
                c[strIndex] = ACR_Utf8ToUnicode(srcPtr[strIndex], (int)bytes[strIndex]);
                strIndex++;
            }
            while(strIndex < 2);
            if(caseSensitive != ACR_INFO_YES)
            {
                c[0] = ACR_UnicodeToLower(c[0]);
                c[1] = ACR_UnicodeToLower(c[1]);
            }
            if(c[0] > c[1])
            {
                // src is a smaller value than string
                return ACR_INFO_LESS;
            }
            else if(c[0] < c[1])
            {
                // src is a greater value than string
                return ACR_INFO_GREATER;
            }
            srcPtr[0] += bytes[0];
            srcPtr[1] += bytes[1];
            srcLength -= bytes[1];
        }
        // no more src characters to count
        if(count < string.m_Count)
        {
            // src has less characters than string
            return ACR_INFO_LESS;
        }
        return ACR_INFO_EQUAL;
    }
    return ACR_INFO_INVALID;
}
