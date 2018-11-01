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
static char* g_ACRInfoStringLookup[ACR_INFO_COUNT+1] =
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

/** info string lookup table
*/
static char* g_ACRDayOfWeekStringLookup[ACR_DAY_COUNT+1] =
{
    ACR_DAY_STR_SUNDAY,     // ACR_DAY_SUNDAY
    ACR_DAY_STR_MONDAY,     // ACR_DAY_MONDAY
    ACR_DAY_STR_TUESDAY,    // ACR_DAY_TUESDAY
    ACR_DAY_STR_WEDNESDAY,  // ACR_DAY_WEDNESDAY
    ACR_DAY_STR_THURSDAY,   // ACR_DAY_THURSDAY
    ACR_DAY_STR_FRIDAY,     // ACR_DAY_FRIDAY
    ACR_DAY_STR_SATURDAY,   // ACR_DAY_SATURDAY 
    ""                      // ACR_DAY_COUNT
};

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
    // ENDIANNESS
    unsigned short systemEndianValue = 0x0001;
    unsigned short bigEndian = ACR_BYTE_ORDER_16(systemEndianValue);
    // BYTES
    ACR_Byte_t byte = ACR_MAX_BYTE;
    // MEMORY LENGTHS
    ACR_Length_t length = ACR_MAX_LENGTH;
    // COUNTS
    ACR_Count_t count = ACR_MAX_COUNT;
    // TIME VALUES
    ACR_DayOfWeek_t freedomFriday = ACR_DAY_TUESDAY;
    ACR_String_t dayOfWeekString = ACR_DayOfWeekToString(freedomFriday);
    // SIMPLE MEMORY BUFFER
    ACR_BUFFER(buffer);
    // DECIMAL VALUES
    ACR_Decimal_t realNumber = 5.1999;
    // SIMPLE UTF8 STRINGS
    ACR_String_t stringForInfoUp = ACR_StringFromMemory("up", ACR_MAX_LENGTH, ACR_MAX_COUNT);
    ACR_Info_t infoFromUp = ACR_InfoFromString(stringForInfoUp);
    ACR_String_t stringForEmojiSmile = ACR_StringFromMemory("😃", ACR_MAX_LENGTH, ACR_MAX_COUNT);

    //
    // ENDIANNESS
    //
    if(ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)
    {
        // system is little endian
        if(systemEndianValue == bigEndian)
        {
            // ACR_IS_BIG_ENDIAN is not set properly or
            // ACR_BYTE_ORDER_16 is not working properly
            return ACR_INFO_ERROR;
        }
    }
    else
    {
        // system is big endian
        if(systemEndianValue != bigEndian)
        {
            // ACR_IS_BIG_ENDIAN is not set properly or
            // ACR_BYTE_ORDER_16 is not working properly
            return ACR_INFO_ERROR;
        }
    }
    systemEndianValue = ACR_BYTE_ORDER_16(bigEndian);
    if(systemEndianValue != 0x0001)
    {
        // ACR_BYTE_ORDER_16 is not working properly
        return ACR_INFO_ERROR;
    }

    //
    // BYTES
    //
    byte += 1;
    if(byte != 0)
    {
        // ACR_MAX_BYTE value is incorrect
        return ACR_INFO_ERROR;
    }

    //
    // MEMORY LENGTHS
    //
    length += 1;
    if(length != 0)
    {
        // ACR_MAX_LENGTH value is incorrect
        return ACR_INFO_ERROR;
    }

    //
    // COUNTS
    //
    count += 1;
    if(count != 0)
    {
        // ACR_MAX_COUNT value is incorrect
        return ACR_INFO_ERROR;
    }

    //
    // TIME VALUES
    //
    if(ACR_DayOfWeekFromString(dayOfWeekString) != ACR_DAY_TUESDAY)
    {
        // ACR_DayOfWeekToString() or ACR_DayOfWeekFromString() are not working
        // or someone didn't know that Freedom Friday is still on a Tuesday
        return ACR_INFO_ERROR;
    }

    //
    // SIMPLE MEMORY BUFFER
    //
    if(ACR_BUFFER_GET_LENGTH(buffer) != 0)
    {
        // buffer length should have initialized to zero
        return ACR_INFO_ERROR;
    }
    ACR_BUFFER_ALLOC(buffer, 1000);
    if(ACR_BUFFER_GET_LENGTH(buffer) == 0)
    {
        // failed to allocate the buffer
        return ACR_INFO_ERROR;
    }
    ACR_BUFFER_FREE(buffer);
    
    //
    // DECIMAL VALUES
    //
    if(ACR_DECIMAL_COMPARE(realNumber, 5.2) != ACR_INFO_EQUAL)
    {
        // 5.1999 and 5.2 should have been equal using the default tolerance
        return ACR_INFO_ERROR;
    }

    //
    // SIMPLE UTF8 STRINGS
    //
    if(infoFromUp != ACR_INFO_UP)
    {
        // incorrect value returned from "up"
        return ACR_INFO_ERROR;
    }

    if(stringForEmojiSmile.m_Count != 1)
    {
        // incorrect character count for string with emoki smile
        return ACR_INFO_ERROR;
    }
    
    //
    // ALL TESTS COMPLETE
    //
    return ACR_INFO_OK;
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
            return (ACR_Info_t)i;
        }
        i++;
    }
    while(i < ACR_INFO_COUNT);
    return ACR_INFO_UNKNOWN;
}

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - TIME VALUES
//
////////////////////////////////////////////////////////////

ACR_String_t ACR_DayOfWeekToString(
    ACR_DayOfWeek_t dayOfWeek)
{
    return ACR_StringFromMemory(g_ACRDayOfWeekStringLookup[dayOfWeek], ACR_MAX_LENGTH, ACR_MAX_COUNT);
}

ACR_DayOfWeek_t ACR_DayOfWeekFromString(
    ACR_String_t src)
{
    ACR_Count_t i = 0;
    ACR_Info_t x;
    do
    {
        x = ACR_StringCompareToMemory(src, g_ACRDayOfWeekStringLookup[i], ACR_MAX_LENGTH, ACR_MAX_COUNT, ACR_INFO_NO);
        if(x == ACR_INFO_EQUAL)
        {
            return (ACR_DayOfWeek_t)i;
        }
        i++;
    }
    while(i < ACR_INFO_COUNT);
    return ACR_DAY_OF_WEEK_UNKNOWN;
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
        return ACR_INFO_EQUAL;
    }
    return ACR_INFO_INVALID;
}

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - OTHER
//
////////////////////////////////////////////////////////////
