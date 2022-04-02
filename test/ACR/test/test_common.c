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
/** \file test_common.c    
*/
#include "ACR/test/test_common.h"

#include "ACR/common.h"

// included for ACR_BYTE_ORDER_16, ACR_BYTE_ORDER_32, ACR_BYTE_ORDER_64
#include "ACR/public/public_byte_order.h"

// included for ACR_Decimal_t, ACR_DECIMAL_TOLERANCE_COMPARE
#include "ACR/public/public_decimal.h"

// included for ACR_INFO_STR_FALSE, ACR_INFO_STR_TRUE
#include "ACR/public/public_unique_strings.h"

// included for ACR_FAILURE, ACR_SUCCESS
#include "ACR/public/public_functions.h"

// included for ACR_DEBUG_PRINT
#include "ACR/public/public_debug.h"

int _ACR_TestCommonEndian(  int testNumber);
int _ACR_TestCommonByte(    int testNumber);
int _ACR_TestCommonLength(  int testNumber);
int _ACR_TestCommonCount(   int testNumber);
int _ACR_TestCommonDateTime(int testNumber);
int _ACR_TestCommonBuffer(  int testNumber);
int _ACR_TestCommonDecimal( int testNumber);
int _ACR_TestCommonUtf8(    int testNumber);

/**********************************************************/
int ACR_TestCommon(void)
{
    ACR_Timer_t timer;
    ACR_TimerStart(&timer);

    #ifdef ACR_USE_UTF8_LOCALE
    setlocale(LC_ALL, "en_US.utf8");
    #endif

    _ACR_TestCommonEndian(   100);
    _ACR_TestCommonByte(     200);
    _ACR_TestCommonLength(   300);
    _ACR_TestCommonCount(    400);
    _ACR_TestCommonDateTime( 500);
    _ACR_TestCommonBuffer(   600);
    _ACR_TestCommonDecimal(  700);
    _ACR_TestCommonUtf8(     800);

    //
    // ALL TESTS COMPLETE
    //
    ACR_Time_t elapse = ACR_TimerElapse(&timer);
    ACR_DEBUG_PRINT(900, "OK: All tests complete in %d microseconds", (int)elapse);
    return ACR_SUCCESS;
}

/**********************************************************/
int _ACR_TestCommonEndian(int testNumber)
{
    ACR_Unsigned_16bit_t systemEndianValue = 0x0001;
    ACR_Unsigned_16bit_t bigEndian = ACR_BYTE_ORDER_16(systemEndianValue);
    ACR_Unsigned_32bit_t systemEndianValue32 = 0x00000001UL;
    ACR_Unsigned_32bit_t bigEndian32 = ACR_BYTE_ORDER_32(systemEndianValue32);
#if ACR_USE_64BIT == ACR_BOOL_TRUE
    ACR_Unsigned_64bit_t systemEndianValue64 = 0x0000000000000001ULL;
    ACR_Unsigned_64bit_t bigEndian64 = ACR_BYTE_ORDER_64(systemEndianValue64);
#endif

#if ACR_ENDIAN_DYNAMIC == ACR_BOOL_TRUE
    ACR_DEBUG_PRINT(1 + testNumber, "OK: ACR_ENDIAN_DYNAMIC is true");
#else
    ACR_DEBUG_PRINT(2 + testNumber, "OK: ACR_ENDIAN_DYNAMIC is false");
#endif

    // Note: disable warning C4127: conditional expression is constant
    //       for test purposes this cannot be a #if #endif because 
    //       when ACR_ENDIAN_DYNAMIC is ACR_BOOL_TRUE the ACR_IS_BIG_ENDIAN
    //       value must be evaluated at runtime
    if (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)
    {
        // system is little endian
        if (systemEndianValue == bigEndian)
        {
            // ACR_IS_BIG_ENDIAN is not set properly or
            // ACR_BYTE_ORDER_16 is not working properly
            ACR_DEBUG_PRINT(3 + testNumber, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_16 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE) ? ACR_INFO_STR_FALSE : ACR_INFO_STR_TRUE);
            return ACR_FAILURE;
        }
        else
        {
            ACR_DEBUG_PRINT(4 + testNumber, "OK: ACR_IS_BIG_ENDIAN is %s", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE) ? ACR_INFO_STR_FALSE : ACR_INFO_STR_TRUE);
        }
    }
    else
    {
        // system is big endian
        if (systemEndianValue != bigEndian)
        {
            // ACR_IS_BIG_ENDIAN is not set properly or
            // ACR_BYTE_ORDER_16 is not working properly
            ACR_DEBUG_PRINT(5 + testNumber, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_16 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE) ? ACR_INFO_STR_FALSE : ACR_INFO_STR_TRUE);
            return ACR_FAILURE;
        }
        else
        {
            ACR_DEBUG_PRINT(6 + testNumber, "OK: ACR_IS_BIG_ENDIAN is %s", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE) ? ACR_INFO_STR_FALSE : ACR_INFO_STR_TRUE);
        }
    }

    systemEndianValue = ACR_BYTE_ORDER_16(bigEndian);
    if (systemEndianValue != 0x0001)
    {
        // ACR_BYTE_ORDER_16 is not working properly
        ACR_DEBUG_PRINT(7 + testNumber, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_16 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE) ? ACR_INFO_STR_FALSE : ACR_INFO_STR_TRUE);
        return ACR_FAILURE;
    }

    systemEndianValue32 = ACR_BYTE_ORDER_32(bigEndian32);
    if (systemEndianValue32 != 0x00000001UL)
    {
        // ACR_BYTE_ORDER_32 is not working properly
        ACR_DEBUG_PRINT(8 + testNumber, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_32 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE) ? ACR_INFO_STR_FALSE : ACR_INFO_STR_TRUE);
        return ACR_FAILURE;
    }

#if ACR_USE_64BIT == ACR_BOOL_TRUE
    systemEndianValue64 = ACR_BYTE_ORDER_32(bigEndian64);
    if (systemEndianValue32 != 0x0000000000000001ULL)
    {
        // ACR_BYTE_ORDER_64 is not working properly
        ACR_DEBUG_PRINT(9 + testNumber, "ERROR: ACR_IS_BIG_ENDIAN is %s but ACR_BYTE_ORDER_64 did not work", (ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE) ? ACR_INFO_STR_FALSE : ACR_INFO_STR_TRUE);
        return ACR_FAILURE;
    }
#endif

    return ACR_SUCCESS;
}

/**********************************************************/
int _ACR_TestCommonByte(int testNumber)
{
    ACR_Byte_t byte = ACR_MAX_BYTE;
    byte += 1;
    if (byte != 0)
    {
        // ACR_MAX_BYTE value is incorrect
        ACR_DEBUG_PRINT(1 + testNumber, "ERROR: ACR_MAX_BYTE value is incorrect");
        return ACR_FAILURE;
    }
    else
    {
        ACR_DEBUG_PRINT(2 + testNumber, "OK: ACR_MAX_BYTE value is %u", ACR_MAX_BYTE);
    }

    return ACR_SUCCESS;
}

/**********************************************************/
int _ACR_TestCommonLength(int testNumber)
{
    ACR_Length_t length = ACR_MAX_LENGTH;
    length += 1;
    if (length != 0)
    {
        // ACR_MAX_LENGTH value is incorrect
        ACR_DEBUG_PRINT(1 + testNumber, "ERROR: ACR_MAX_LENGTH value is incorrect");
        return ACR_FAILURE;
    }
    else
    {
#if ACR_USE_64BIT == ACR_BOOL_TRUE
        ACR_DEBUG_PRINT(2 + testNumber, "OK: ACR_MAX_LENGTH value is %llu", ACR_MAX_LENGTH);
#else
        ACR_DEBUG_PRINT(3 + testNumber, "OK: ACR_MAX_LENGTH value is %lu", ACR_MAX_LENGTH);
#endif
    }

    return ACR_SUCCESS;
}

/**********************************************************/
int _ACR_TestCommonCount(int testNumber)
{
    ACR_Count_t count = ACR_MAX_COUNT;
    count += 1;
    if (count > ACR_ZERO_COUNT)
    {
        ACR_DEBUG_PRINT(1 + testNumber, "OK: ACR_MAX_COUNT value is %lu", ACR_MAX_COUNT);
    }
    else
    {
        // ACR_MAX_COUNT value is incorrect
        ACR_DEBUG_PRINT(2 + testNumber, "ERROR: ACR_MAX_COUNT value is incorrect");
        return ACR_FAILURE;
    }

    return ACR_SUCCESS;
}

/**********************************************************/
int _ACR_TestCommonDateTime(int testNumber)
{
    ACR_DayOfWeek_t freedomFriday = ACR_DAY_TUESDAY;
    ACR_String_t dayOfWeekString = ACR_DayOfWeekToString(freedomFriday);
    ACR_Month_t monthOfMarch = ACR_MONTH_MARCH;
    ACR_String_t monthString = ACR_MonthToString(monthOfMarch);
    ACR_DATETIME(dateTime);
    if (ACR_DayOfWeekFromString(dayOfWeekString) != ACR_DAY_TUESDAY)
    {
        // ACR_DayOfWeekToString() or ACR_DayOfWeekFromString() are not working
        // or someone didn't know that Freedom Friday is still on a Tuesday
        ACR_DEBUG_PRINT(1 + testNumber, "ERROR: ACR_DayOfWeekFromString(%.*s) did not return ACR_DAY_TUESDAY", (int)dayOfWeekString.m_Buffer.m_Length, (const char*)dayOfWeekString.m_Buffer.m_Pointer);
        return ACR_FAILURE;
    }
    else
    {
        ACR_DEBUG_PRINT(2 + testNumber, "OK: ACR_DayOfWeekFromString(%.*s) is ACR_DAY_TUESDAY", (int)dayOfWeekString.m_Buffer.m_Length, (const char*)dayOfWeekString.m_Buffer.m_Pointer);
    }

    if (ACR_MonthFromString(monthString) != ACR_MONTH_MARCH)
    {
        // ACR_MonthToString() or ACR_MonthFromString() are not working
        ACR_DEBUG_PRINT(3 + testNumber, "ERROR: ACR_MonthFromString(%.*s) did not return ACR_MONTH_MARCH", (int)monthString.m_Buffer.m_Length, (const char*)monthString.m_Buffer.m_Pointer);
        return ACR_FAILURE;
    }
    else
    {
        ACR_DEBUG_PRINT(4 + testNumber, "OK: ACR_MonthFromString(%.*s) is ACR_MONTH_MARCH", (int)monthString.m_Buffer.m_Length, (const char*)monthString.m_Buffer.m_Pointer);
    }

    ACR_DATETIME_NOW(dateTime);
    if (ACR_DATETIME_HAS_TIME(dateTime) == ACR_BOOL_FALSE)
    {
        if (ACR_DATETIME_HAS_DATE(dateTime) == ACR_BOOL_FALSE)
        {
#if ACR_HAS_RTC == ACR_BOOL_TRUE
            ACR_DEBUG_PRINT(5 + testNumber, "ERROR: ACR_DATETIME_NOW did not provide time or date");
            return ACR_FAILURE;
#else
            ACR_DEBUG_PRINT(6 + testNumber, "OK: No RTC so ACR_DATETIME_NOW did not provide time or date");
#endif
    }
        else
        {
            ACR_DEBUG_PRINT(7 + testNumber, "ERROR: ACR_DATETIME_NOW did not provide time");
            return ACR_FAILURE;
        }
}
    else
    {
        if (ACR_DATETIME_HAS_DATE(dateTime) == ACR_BOOL_FALSE)
        {
            ACR_DEBUG_PRINT(8 + testNumber, "ERROR: ACR_DATETIME_NOW did not provide date");
            return ACR_FAILURE;
        }
        else
        {
            monthString = ACR_MonthToString(ACR_DATETIME_MONTH(dateTime));
            dayOfWeekString = ACR_DayOfWeekToString(ACR_DATETIME_DAY_OF_WEEK(dateTime));
            ACR_DEBUG_PRINT(9 + testNumber, "OK: ACR_DATETIME_NOW has provided date and time of %.*s %.*s %d %d %d:%02d:%02d",
                (int)dayOfWeekString.m_Buffer.m_Length, (const char*)dayOfWeekString.m_Buffer.m_Pointer,
                (int)monthString.m_Buffer.m_Length, (const char*)monthString.m_Buffer.m_Pointer,
                ACR_DATETIME_DAY(dateTime), ACR_DATETIME_YEAR(dateTime),
                ACR_DATETIME_HOUR(dateTime), ACR_DATETIME_MIN(dateTime), ACR_DATETIME_SEC(dateTime));
        }
    }

    return ACR_SUCCESS;
}

/**********************************************************/
int _ACR_TestCommonBuffer(int testNumber)
{
    ACR_BUFFER(buffer);
    if (ACR_BUFFER_GET_LENGTH(buffer) != 0)
    {
        // buffer length should have initialized to zero
#if ACR_USE_64BIT == ACR_BOOL_TRUE
        ACR_DEBUG_PRINT(1 + testNumber, "ERROR: buffer length is %llu when it should be 0", buffer.m_Length);
#else
        ACR_DEBUG_PRINT(2 + testNumber, "ERROR: buffer length is %lu when it should be 0", buffer.m_Length);
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE
        return ACR_FAILURE;
    }
    ACR_BUFFER_ALLOC(buffer, 1000);
    if (ACR_BUFFER_GET_LENGTH(buffer) == 0)
    {
        // failed to allocate the buffer
#if ACR_HAS_MALLOC != ACR_BOOL_FALSE
        {
            ACR_DEBUG_PRINT(3 + testNumber, "ERROR: ACR_BUFFER_ALLOC failed to allocate memory");
            return ACR_FAILURE;
        }
#else
        {
            ACR_DEBUG_PRINT(4 + testNumber, "OK: ACR_HAS_MALLOC is not defined so buffer length is 0");
        }
#endif
    }
    else
    {
#if ACR_USE_64BIT == ACR_BOOL_TRUE
        ACR_DEBUG_PRINT(5 + testNumber, "OK: ACR_BUFFER_ALLOC allocated %llu bytes", buffer.m_Length);
#else
        ACR_DEBUG_PRINT(6 + testNumber, "OK: ACR_BUFFER_ALLOC allocated %lu bytes", buffer.m_Length);
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE
    }
    ACR_BUFFER_FREE(buffer);
    if (ACR_BUFFER_GET_LENGTH(buffer) != 0)
    {
        ACR_DEBUG_PRINT(7 + testNumber, "ERROR: ACR_BUFFER_FREE failed to free buffer memory");
        return ACR_FAILURE;
    }
    else
    {
        ACR_DEBUG_PRINT(8 + testNumber, "OK: ACR_BUFFER_FREE freed buffer memory");
    }

    return ACR_SUCCESS;
}

/**********************************************************/
int _ACR_TestCommonDecimal(int testNumber)
{
    ACR_Decimal_t realNumber = (ACR_Decimal_t)5.1999;
    if (ACR_DECIMAL_TOLERANCE_COMPARE(realNumber, (ACR_Decimal_t)5.2, (ACR_Decimal_t)0.0001) != ACR_INFO_EQUAL)
    {
        // 5.1999 and 5.2 should have been equal using the tolerance
        ACR_DEBUG_PRINT(1 + testNumber, "ERROR: ACR_DECIMAL_COMPARE should have found %0.4f to be equal to %0.4f", realNumber, 5.2);
        return ACR_FAILURE;
    }
    else
    {
        ACR_DEBUG_PRINT(2 + testNumber, "OK: ACR_DECIMAL_COMPARE found %0.4f is within %0.4f of %0.4f", realNumber, 0.0001, 5.2);
    }

    return ACR_SUCCESS;
}

/**********************************************************/
int _ACR_TestCommonUtf8(int testNumber)
{
    ACR_String_t stringForInfoUp = ACR_StringFromMemory((ACR_Byte_t*)"up", ACR_MAX_LENGTH, ACR_MAX_COUNT);
    ACR_Info_t infoFromUp = ACR_InfoFromString(stringForInfoUp);
    ACR_String_t stringForEmojiSmile;
    if (infoFromUp != ACR_INFO_UP)
    {
        // incorrect value returned from "up"
        ACR_DEBUG_PRINT(1 + testNumber, "ERROR: ACR_InfoFromString(%.*s) did not find ACR_INFO_UP", (int)stringForInfoUp.m_Buffer.m_Length, (const char*)stringForInfoUp.m_Buffer.m_Pointer);
        return ACR_FAILURE;
    }
    else
    {
        ACR_DEBUG_PRINT(2 + testNumber, "OK: %.*s is ACR_INFO_UP", (int)stringForInfoUp.m_Buffer.m_Length, (const char*)stringForInfoUp.m_Buffer.m_Pointer);
    }

    stringForEmojiSmile = ACR_StringFromMemory((ACR_Byte_t*)"Smile 🙂", ACR_MAX_LENGTH, ACR_MAX_COUNT);
    if (stringForEmojiSmile.m_Count != 7)
    {
        // incorrect character count for string with emoji smile
        ACR_DEBUG_PRINT(3 + testNumber, "ERROR: ACR_StringFromMemory() says the smile emoji is %lu characters", stringForEmojiSmile.m_Count);
        return ACR_FAILURE;
    }
    else
    {
        ACR_DEBUG_PRINT(4 + testNumber, "OK: %.*s with a single character smile emoji", (int)stringForEmojiSmile.m_Buffer.m_Length, (const char*)stringForEmojiSmile.m_Buffer.m_Pointer);
    }

    return ACR_SUCCESS;
}
