/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 Adam C. Rosenberg

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
/** \file public.c

    \see ACR/public.h
    
*/
#include "ACR/public.h"

/** info string lookup table
*/
static ACR_String_t* g_ACRInfoStringLookup[ACR_INFO_COUNT+1] =
{
    //
    // COMPARISON
    //
    ACR_INFO_STR_EQUAL,     // ACR_INFO_EQUAL
    ACR_INFO_STR_NOT_EQUAL, // ACR_INFO_NOT_EQUAL
    ACR_INFO_STR_LESS,      // ACR_INFO_LESS
    ACR_INFO_STR_GREATER,   // ACR_INFO_GREATER
    ACR_INFO_STR_UNKNOWN,   // ACR_INFO_UNKNOWN

    //
    // POSITIVE, NEGATIVE
    //
    ACR_INFO_STR_TRUE,      // ACR_INFO_TRUE
    ACR_INFO_STR_FALSE,     // ACR_INFO_FALSE
    ACR_INFO_STR_OK,        // ACR_INFO_OK
    ACR_INFO_STR_ERROR,     // ACR_INFO_ERROR
    ACR_INFO_STR_ENABLED,   // ACR_INFO_ENABLED
    ACR_INFO_STR_DISABLED,  // ACR_INFO_DISABLED
    ACR_INFO_STR_YES,       // ACR_INFO_YES
    ACR_INFO_STR_NO,        // ACR_INFO_NO
    ACR_INFO_STR_ON,        // ACR_INFO_ON
    ACR_INFO_STR_OFF,       // ACR_INFO_OFF
    ACR_INFO_STR_START,     // ACR_INFO_START
    ACR_INFO_STR_STOP,      // ACR_INFO_STOP
    ACR_INFO_STR_ACCEPT,    // ACR_INFO_ACCEPT
    ACR_INFO_STR_IGNORE,    // ACR_INFO_IGNORE
    ACR_INFO_STR_VALID,     // ACR_INFO_VALID
    ACR_INFO_STR_INVALID,   // ACR_INFO_INVALID

    //
    // POSITION
    //
    ACR_INFO_STR_TOP,       // ACR_INFO_TOP
    ACR_INFO_STR_BOTTOM,    // ACR_INFO_BOTTOM
    ACR_INFO_STR_FIRST,     // ACR_INFO_FIRST
    ACR_INFO_STR_LAST,      // ACR_INFO_LAST
    ACR_INFO_STR_PREVIOUS,  // ACR_INFO_PREVIOUS
    ACR_INFO_STR_NEXT,      // ACR_INFO_NEXT
    ACR_INFO_STR_CURRENT,   // ACR_INFO_CURRENT

    // DIRECTION
    ACR_INFO_STR_UP,        // ACR_INFO_UP
    ACR_INFO_STR_DOWN,      // ACR_INFO_DOWN
    ACR_INFO_STR_LEFT,      // ACR_INFO_LEFT
    ACR_INFO_STR_RIGHT,     // ACR_INFO_RIGHT

    // AGE
    ACR_INFO_STR_OLD,       // ACR_INFO_OLD
    ACR_INFO_STR_NEW,       // ACR_INFO_NEW

    // INSTRUCTION
    ACR_INFO_STR_BEGIN,     // ACR_INFO_BEGIN
    ACR_INFO_STR_READY,     // ACR_INFO_READY
    ACR_INFO_STR_WAIT,      // ACR_INFO_WAIT
    ACR_INFO_STR_GO,        // ACR_INFO_GO
    ACR_INFO_STR_END,       // ACR_INFO_END

    ""                      // ACR_INFO_COUNT
};

/*
int _ACR_UTF8ByteCount(ACR_Byte_t c)
{
    if((c & 0x80) != 0)
    {
        // 1???????
        if((c & 0x40) != 0)
        {
            // 11??????
            if((c & 0x20) != 0)
            {
                // 111?????
                if((c & 0x10) != 0)
                {
                    // 1111????
                    return 4;
                }
                else
                {
                    // 1110????
                    return 3;
                }
            }
            else
            {
                // 110?????
                return 2;
            }
        }
        else
        {
            // 10??????
            // malformed UTF8
        }
    }
    else
    {
        // 0???????
    }
    return 1;
}
*/

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - TEST
//
////////////////////////////////////////////////////////////

/** internal test of quick test of ACR library functions
    \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_Test(void)
{
    ACR_String_t s = ACR_StringFromMemory("up", ACR_MAX_LENGTH, ACR_MAX_COUNT);
    ACR_Info_t i = ACR_InfoFromString(s);
    if(i == ACR_INFO_UP)
    {
        return ACR_INFO_OK;
    }
    
    return ACR_INFO_ERROR;
}

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - COMMON INFORMATIONAL VALUES
//
////////////////////////////////////////////////////////////

ACR_String_t ACR_InfoToString(
    ACR_Info_t info)
{
    return ACR_StringFromMemory(g_ACRInfoStringLookup[info], ACR_MAX_LENGTH, ACR_MAX_COUNT);
}

ACR_Info_t ACR_InfoFromString(
    ACR_String_t src)
{
    ACR_Count_t i = 0;
    ACR_Info_t x;
    do
    {
        x = ACR_StringCompareToMemory(src, g_ACRInfoStringLookup[i], ACR_MAX_LENGTH, ACR_MAX_COUNT, ACR_INFO_NO);
        if(x == ACR_INFO_EQUAL)
        {
            return i;
        }
        i++;
    }
    while(i < ACR_INFO_COUNT);
    return ACR_INFO_UNKNOWN;
}

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - SIMPLE UTF8 STRINGS
//                    AND UNICODE CHARACTERS
//
////////////////////////////////////////////////////////////

ACR_Unicode_t ACR_UnicodeToLower(
    ACR_Unicode_t u)
{
    /// \todo use a conversion table instead to handle additional unicode characters
    
    // handle ASCII characters
    if((u >= 65) && (u <= 90))
    {
        u += 32;
    }

    return u;
}

ACR_Unicode_t ACR_Utf8ToUnicode(
    ACR_Byte_t* mem,
    int bytes)
{
    int offset = (bytes-1);
    if(offset > 0)
    {
        ACR_Unicode_t c = (((ACR_Unicode_t)(mem[0] & (0x3F>>offset))) << (offset*6));
        int byteNum = 1;
        do
        {
            offset -= 1;
            c |= (((ACR_Unicode_t)(mem[byteNum] & 0x3F)) << (offset*6));
            byteNum += 1;
        }
        while(offset > 0);
        return c;
    }
    return (ACR_Unicode_t)mem[0];
}

ACR_String_t ACR_StringFromMemory(
    void* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters)
{
    ACR_STRING(s);
    if(src != ACR_NULL)
    {
        ACR_Length_t remaining = srcLength;
        ACR_Byte_t* srcPtr = (ACR_Byte_t*)src;
        while((remaining > 0) && (s.m_Count < maxCharacters) && ((*srcPtr) != 0))
        {
            int bytes = ACR_UTF8_BYTE_COUNT((*srcPtr));
            if(bytes > remaining)
            {
                break;
            }
            s.m_Count++;
            srcPtr += bytes;
            remaining -= bytes;
        }
        ACR_BUFFER_REFERENCE(s.m_Buffer, src, (srcLength - remaining));
    }
    return s;
}

ACR_Info_t ACR_StringCompareToMemory(
    ACR_String_t string,
    void* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters,
    ACR_Info_t caseSensitive)
{
    if(src != ACR_NULL)
    {
        ACR_Count_t count = 0;
        // 0 = string
        // 1 = src
        ACR_Byte_t* srcPtr[2] = {string.m_Buffer.m_Pointer, (ACR_Byte_t*)src};
        int bytes[2];
        int strIndex;
        ACR_Unicode_t c[2];
        while((srcLength > 0) && ((*srcPtr) != 0))
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
                c[strIndex] = ACR_Utf8ToUnicode(srcPtr[strIndex], bytes[strIndex]);
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
    }
    return ACR_INFO_INVALID;
}
