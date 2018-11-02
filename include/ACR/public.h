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
/** \file public.h

    All enums and defines are found here. Some of the most
    common functions and typedefs will also be predefined
    by this header.

    --- Preprocessor Defines for Configuration Options ---

    ACR_DEBUG           include debug tools

    ACR_NO_MALLOC       do not include malloc() or free()

    ACR_BIG_ENDIAN      always use big endian without
                        dynamically checking the system
                        endianess

    ACR_LITTLE_ENDIAN   always use little endian without
                        dynamically checking the system
                        endianess

    ACR_NO_TIME         do not include time()

    ACR_NO_64BIT        do not use types of long long

    --- Top Uses ---

    ACR_DEBUG_PRINT     interface to printf() that only
                        writes messages to stdout
                        when ACR_DEBUG is defined in
                        the preprocessor

    ACR_BYTE_ORDER_16   ensures a value is stored
                        in big endian byte order
    ACR_BYTE_ORDER_32   \see ACR_IS_BIG_ENDIAN

    ACR_Buffer_t        a simple struct with macros
                        to handle allocation and freeing
                        of memory safely.

    ACR_VarBuffer_t     a simple struct with macros to 
                        handle allocation of memory
                        safely while freeing memory only
                        when necessary to grow the
                        memory area.

    ACR_String_t        a struct for access to strings
                        with support for UTF8 encoding

    DECIMAL_COMPARE     compare decimal values within a
                        tolerance

*/
#ifndef _ACR_PUBLIC_H_
#define _ACR_PUBLIC_H_

//#define ACR_DEBUG
//#define ACR_NO_MALLOC
//#define ACR_BIG_ENDIAN
//#define ACR_LITTLE_ENDIAN
//#define ACR_NO_TIME
//#define ACR_NO_64BIT

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SYSTEM LEVEL
//
////////////////////////////////////////////////////////////

// included for memset()
#include <string.h>

/** represents a successful program or thread execution

    example:

    int main()
    {
        return ACR_SUCCESS;
    }
    
*/
#define ACR_SUCCESS 0

/** represents a false boolean result

    example:

    if(ACR_BOOL_FALSE)
    {
        // never reaches this code
    }
    else
    {
        // always reaches this code
    }

*/
#define ACR_BOOL_FALSE 0

/** represents a true boolean result
*/
#define ACR_BOOL_TRUE 1

/** represents a null pointer.
    use this instead of 0 to clearly indicate the value
    is being used for a null pointer

    for variable init:

        char* ptr = ACR_NULL;

    for comparison:
    
        if(ptr == ACR_NULL)
        {
            // ptr is a null pointer
        }

*/
#define ACR_NULL 0

// defines ACR_USE_64BIT
#ifndef ACR_NO_64BIT
#define ACR_USE_64BIT ACR_BOOL_TRUE
#else
#define ACR_USE_64BIT ACR_BOOL_FALSE
#endif // #ifndef ACR_NO_64BIT

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - DEBUG
//
////////////////////////////////////////////////////////////

// defines ACR_IS_DEBUG and ACR_DEBUG_PRINT such that
// printed messages are only compiled if desired
#ifdef ACR_DEBUG
#define ACR_IS_DEBUG ACR_BOOL_TRUE
// included for printf
#include <stdio.h>
#define ACR_DEBUG_PRINT(number, format, ...) printf("%4d "format"\n", number, __VA_ARGS__)
#else
#define ACR_IS_DEBUG ACR_BOOL_FALSE
#define ACR_DEBUG_PRINT(number, format, ...)
#endif // #ifdef ACR_DEBUG

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MALLOC
//
////////////////////////////////////////////////////////////

// defines ACR_HAS_MALLOC and includes malloc() and free()
// functions if desired
#ifndef ACR_NO_MALLOC
/** defined when malloc is available
    Note: to remove malloc from this library define
          ACR_NO_MALLOC in your preprocessor
*/
#define ACR_HAS_MALLOC ACR_BOOL_TRUE
// included for malloc and free
#include <stdlib.h>
#else
#define ACR_HAS_MALLOC ACR_BOOL_FALSE
#endif // #ifndef ACR_NO_MALLOC

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - ENDIANNESS
//
// Note: Big Endian means that multibyte values have the
//       bytes stored in memory from least significant 
//       to most significant.
//
// Optional: If you already know the endianess of your
//           system then set the preprocessor define as
//           follows to improve byte order handling
//           performance.
//           Big Endian:    ACR_BIG_ENDIAN
//           Little Endian: ACR_LITTLE_ENDIAN
//
// Sample memory:
//
//   type/bytes
//
//   char/1     memory = [ 0x01 ---- ---- ---- ]
//              binary little endian =
//                  MSB ------------------------00000001 LSB
//              decimal big endian = 1
//              decimal little endian = 1
//
//   short/2    memory = [ 0x01 0x00 ---- ---- ]
//              binary little endian = 
//                  MSB ----------------0000000100000000 LSB
//              decimal big endian = 1
//              decimal little endian = 256
//
//   short/2    memory = [ 0x00 0x01 ---- ---- ]
//              binary little endian = 
//                  MSB ----------------0000000000000001 LSB
//              decimal big endian = 256
//              decimal little endian = 1
//
//   long/4     memory = [ 0x00 0x01 0x00 0x00 ]
//              binary little endian = 
//                  MSB 00000000000000010000000000000000 LSB
//              decimal big endian = 256
//              decimal little endian = 65536
//
// "short" Example:
//
//      // given a local variable with value 1
//      short valueInSystemEndian = 1;
//      // convert the value to big endian 
//      short valueInBigEndian = ACR_BYTE_ORDER_16(valueInSystemEndian);
//      // and use the same macro to convert
//      // a big endian value back to system endianness
//      valueInSystemEndian = ACR_BYTE_ORDER_16(valueInBigEndian);
//
////////////////////////////////////////////////////////////

/** byte order swap of 16 bit value
*/
#define ACR_BYTE_ORDER_SWAP_16(x)   (((((unsigned short)(x)) & 0x00ff) << 8) | \
                                     ((((unsigned short)(x)) & 0xff00) >> 8))

/** byte order swap of 32 bit value
*/
#define ACR_BYTE_ORDER_SWAP_32(x)   ((((unsigned long)(x) & 0x000000ffUL) << 24) | \
                                     (((unsigned long)(x) & 0x0000ff00UL) <<  8) | \
                                     (((unsigned long)(x) & 0x00ff0000UL) >>  8) | \
                                     (((unsigned long)(x) & 0xff000000UL) >> 24))

#if ACR_USE_64BIT == ACR_BOOL_TRUE

#define ACR_BYTE_ORDER_SWAP_64(x)   ((((unsigned long long)(x) & 0x00000000000000ffULL) << 56) | \
                                     (((unsigned long long)(x) & 0x000000000000ff00ULL) << 40) | \
                                     (((unsigned long long)(x) & 0x0000000000ff0000ULL) << 24) | \
                                     (((unsigned long long)(x) & 0x00000000ff000000ULL) <<  8) | \
                                     (((unsigned long long)(x) & 0x000000ff00000000ULL) >>  8) | \
                                     (((unsigned long long)(x) & 0x0000ff0000000000ULL) >> 24) | \
                                     (((unsigned long long)(x) & 0x00ff000000000000ULL) >> 40) | \
                                     (((unsigned long long)(x) & 0xff00000000000000ULL) >> 56))

#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

//
// defines ACR_IS_BIG_ENDIAN as ACR_BOOL_TRUE or
// ACR_BOOL_FALSE
//
#ifdef ACR_BIG_ENDIAN
/** the system is big endian because ACR_BIG_ENDIAN
    was set in the preprocessor
*/
#define ACR_IS_BIG_ENDIAN ACR_BOOL_TRUE
#else
#ifdef ACR_LITTLE_ENDIAN
/** the system is NOT big endian because ACR_LITTLE_ENDIAN
    was set in the preprocessor
*/
#define ACR_IS_BIG_ENDIAN ACR_BOOL_FALSE
#endif // #ifdef ACR_LITTLE_ENDIAN
#endif // #ifdef ACR_BIG_ENDIAN

//
// defines ACR_IS_BIG_ENDIAN as ACR_BOOL_TRUE or
// ACR_BOOL_FALSE if not previously defined
//
#ifndef ACR_IS_BIG_ENDIAN
#ifdef BIG_ENDIAN
/** the system is big endian because BIG_ENDIAN
    was set in the preprocessor
*/
#define ACR_IS_BIG_ENDIAN ACR_BOOL_TRUE
#else
#ifdef LITTLE_ENDIAN
/** the system is NOT big endian because LITTLE_ENDIAN
    was set in the preprocessor
*/
#define ACR_IS_BIG_ENDIAN ACR_BOOL_FALSE
#else
#define ACR_IS_BIG_ENDIAN (*(unsigned short *)"\0\xff" < 0x100)
#define ACR_ENDIAN_DYNAMIC ACR_BOOL_TRUE
#endif // #ifdef LITTLE_ENDIAN
#endif // #ifdef BIG_ENDIAN
#endif // #ifndef ACR_IS_BIG_ENDIAN

//
// defines ACR_BYTE_ORDER_16 and ACR_BYTE_ORDER_32
// to swap byte order to big endian when needed
//
#ifdef ACR_ENDIAN_DYNAMIC
#define ACR_BYTE_ORDER_16(x) ((ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_BYTE_ORDER_SWAP_16(x):x)
#define ACR_BYTE_ORDER_32(x) ((ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_BYTE_ORDER_SWAP_32(x):x)
#if ACR_USE_64BIT == ACR_BOOL_TRUE
#define ACR_BYTE_ORDER_64(x) ((ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE)?ACR_BYTE_ORDER_SWAP_64(x):x)
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE
#else
#if ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE
#define ACR_BYTE_ORDER_16(x) (ACR_BYTE_ORDER_SWAP_16(x))
#define ACR_BYTE_ORDER_32(x) (ACR_BYTE_ORDER_SWAP_32(x))
#if ACR_USE_64BIT == ACR_BOOL_TRUE
#define ACR_BYTE_ORDER_64(x) (ACR_BYTE_ORDER_SWAP_64(x))
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE
#else
#define ACR_BYTE_ORDER_16(x) (x)
#define ACR_BYTE_ORDER_32(x) (x)
#if ACR_USE_64BIT == ACR_BOOL_TRUE
#define ACR_BYTE_ORDER_64(x) (x)
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE
#endif // #if ACR_IS_BIG_ENDIAN == ACR_BOOL_FALSE
#endif // #ifdef ACR_ENDIAN_DYNAMIC

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - BYTES
//
////////////////////////////////////////////////////////////

/** type for a single byte
*/
typedef unsigned char ACR_Byte_t;

/** number of bits in ACR_Byte_t
*/
#define ACR_BITS_PER_BYTE 8

/** max value that can be stored by the ACR_Byte_t type 
*/
#define ACR_MAX_BYTE 255 // hex value 0xFF

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MEMORY LENGTHS
//
////////////////////////////////////////////////////////////

/** type for a typical length
    \see ACR_MAX_LENGTH for the maximum value that can be
    stored by this data type
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
typedef unsigned long long ACR_Length_t;
#else
// 32bit
typedef unsigned long ACR_Length_t;
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

/** represents zero length.
    use this instead of 0 to clearly indicate the value
    is being used for a length

    for variable init:

        int length = ACR_ZERO_LENGTH;

    for comparison:

        if(length == ACR_ZERO_LENGTH)
        {
            // length is zero
        }
    
*/
#define ACR_ZERO_LENGTH 0

/** max value that can be stored by the ACR_Length_t type 
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
#define ACR_MAX_LENGTH 18446744073709551615ULL // hex value 0xFFFFFFFFFFFFFFFF
#else
// 32bit
#define ACR_MAX_LENGTH 4294967295UL // hex value 0xFFFFFFFF
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - COUNTING
//
////////////////////////////////////////////////////////////

/** type for a typical count
    \see ACR_MAX_COUNT for the maximum value that can be
    stored by this data type
*/
typedef unsigned long ACR_Count_t;

/** max value that can be stored by the ACR_Count_t type 
*/
#define ACR_MAX_COUNT 4294967295UL // hex value 0xFFFF

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - COMMMON VALUES
//
////////////////////////////////////////////////////////////

/** represents an empty value.
    use this instead of 0 to clearly indicate the value
    is being used to identify an empty value

    for memory init:

        char data[64];
        memset(data, ACR_EMPTY_VALUE, sizeof(data));
        
    for variable init:

        int selected = ACR_EMPTY_VALUE;

    for comparison:

        if(data[0] == ACR_EMPTY_VALUE)
        {
            // nothing has been written to the data
        }

        if(selected == ACR_EMPTY_VALUE)
        {
            // nothing has been selected
        }

*/
#define ACR_EMPTY_VALUE 0

/** the value of pie
*/
#define ACR_PI 3.14159265359

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - TIME VALUES
//
////////////////////////////////////////////////////////////

#define ACR_MICRO_PER_MILLI 1000
#define ACR_MILLI_PER_SEC   1000
#define ACR_SEC_PER_MIN     60
#define ACR_MIN_PER_HOUR    60
#define ACR_HOUR_PER_DAY    24

// MINUTES
#define ACR_MIN_PER_DAY (ACR_MIN_PER_HOUR*ACR_HOUR_PER_DAY)
// SECONDS
#define ACR_SEC_PER_HOUR (ACR_SEC_PER_MIN*ACR_MIN_PER_HOUR)
#define ACR_SEC_PER_DAY (ACR_SEC_PER_HOUR*ACR_HOUR_PER_DAY)
// MILLISECONDS
#define ACR_MILLI_PER_MIN (ACR_MILLI_PER_SEC*ACR_SEC_PER_MIN)
#define ACR_MILLI_PER_HOUR (ACR_MILLI_PER_MIN*ACR_MIN_PER_HOUR)
// MICROSECONDS
#define ACR_MICRO_PER_SEC (ACR_MICRO_PER_MILLI*ACR_MILLI_PER_SEC)
#define ACR_MICRO_PER_MIN (ACR_MICRO_PER_SEC*ACR_SEC_PER_MIN)

/** days of the week
*/
typedef enum ACR_DayOfWeek_e
{
    ACR_DAY_SUNDAY = 0,
    ACR_DAY_MONDAY,
    ACR_DAY_TUESDAY,
    ACR_DAY_WEDNESDAY,
    ACR_DAY_THURSDAY,
    ACR_DAY_FRIDAY,
    ACR_DAY_SATURDAY,
    ACR_DAY_COUNT
} ACR_DayOfWeek_t;

#define ACR_DAY_OF_WEEK_UNKNOWN ACR_DAY_COUNT
#define ACR_DAY_PER_WEEK ACR_DAY_COUNT
#define ACR_MIN_PER_WEEK (ACR_MIN_PER_DAY*ACR_DAY_PER_WEEK)

/** months of the year
*/
typedef enum ACR_Month_e
{
    ACR_MONTH_JANUARY = 0,
    ACR_MONTH_FEBRUARY,
    ACR_MONTH_MARCH,
    ACR_MONTH_APRIL,
    ACR_MONTH_MAY,
    ACR_MONTH_JUNE,
    ACR_MONTH_JULY,
    ACR_MONTH_AUGUST,
    ACR_MONTH_SEPTEMBER,
    ACR_MONTH_OCTOBER,
    ACR_MONTH_NOVEMBER,
    ACR_MONTH_DECEMBER,
    ACR_MONTH_COUNT
} ACR_Month_t;

#define ACR_MONTH_UNKNOWN ACR_MONTH_COUNT
#define ACR_MONTH_PER_YEAR ACR_MONTH_COUNT

// defines ACR_HAS_RTC and includes time()
// functions if desired
#ifndef ACR_NO_TIME
#define ACR_HAS_RTC ACR_BOOL_TRUE
#include <time.h>
#else
#define ACR_HAS_RTC ACR_BOOL_FALSE
#endif

#if ACR_HAS_RTC == ACR_BOOL_TRUE

/** time value
*/
typedef time_t ACR_Time_t;

/** standard date time structure
*/
typedef struct tm ACR_DateTime_t;

/** set the specified date time to the current date and time

    example:
    ACR_DATETIME(current);
    ACR_DATETIME_NOW(current);

*/
#define ACR_DATETIME_NOW(name) {time_t temp; time(&temp); name = (*(gmtime(&temp)));}

#else

/** time value
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
typedef unsigned long long ACR_Time_t;
#else
// 32bit
typedef unsigned long ACR_Time_t;
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

/** standard date time structure
*/
typedef struct ACR_DateTime_s {
   int tm_sec;         /* seconds,  range 0 to 59          */
   int tm_min;         /* minutes, range 0 to 59           */
   int tm_hour;        /* hours, range 0 to 23             */
   int tm_mday;        /* day of the month, range 1 to 31  */
   int tm_mon;         /* month, range 0 to 11             */
   int tm_year;        /* The number of years since 1900   */
   int tm_wday;        /* day of the week, range 0 to 6    */
   int tm_yday;        /* day in the year, range 0 to 365  */
   int tm_isdst;       /* daylight saving time             */	
} ACR_DateTime_t;

/** RTC is not available so this macro just clears the date time
*/
#define ACR_DATETIME_NOW(name) memset(&name,ACR_EMPTY_VALUE,sizeof(ACR_DateTime_t));

#endif // #if ACR_HAS_RTC == ACR_BOOL_TRUE

/** define an empty date time on the stack
*/
#define ACR_DATETIME(name) ACR_DateTime_t name = {ACR_EMPTY_VALUE};

/** determine if the specified date time has the time data set

    example:

    ACR_DATETIME(dateTime);
    if(ACR_DATETIME_HAS_TIME(dateTime) == ACR_BOOL_FALSE)
    {
        // no time value set
    }
*/
#define ACR_DATETIME_HAS_TIME(name) ((name.tm_sec|name.tm_min|name.tm_hour) != 0)

/** determine if the specified date time has the date data set

    example:

    ACR_DATETIME(dateTime);
    if(ACR_DATETIME_HAS_DATE(dateTime) == ACR_BOOL_FALSE)
    {
        // no time value set
    }
*/
#define ACR_DATETIME_HAS_DATE(name) ((name.tm_year|name.tm_mon|name.tm_mday) != 0)

#define ACR_DATETIME_YEAR(name) (1900 + name.tm_year)
#define ACR_DATETIME_MONTH(name) ((ACR_Month_t)name.tm_mon)
#define ACR_DATETIME_DAY(name) (name.tm_mday)
#define ACR_DATETIME_DAY_OF_WEEK(name) ((ACR_DayOfWeek_t)name.tm_wday)
#define ACR_DATETIME_HOUR(name) (name.tm_hour)
#define ACR_DATETIME_MIN(name) (name.tm_min)
#define ACR_DATETIME_SEC(name) (name.tm_sec)

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SIMPLE MEMORY BUFFER
//
////////////////////////////////////////////////////////////

/** type for reference to a buffer.
    - never use malloc or free directly.
    - never use void pointers.
    - always use ACR_Buffer_t and \see ACR_BUFFER defines 
      for easy and safe usage

    example:

        int main()
        {
            ACR_BUFFER(text);
            ACR_BUFFER_ALLOC(text, 255);
            if(ACR_BUFFER_GET_LENGTH(text) > ACR_ZERO_LENGTH)
            {
                // this buffer is safe to use with
                // up to ACR_BUFFER_GET_LENGTH() bytes
            }
            ACR_BUFFER_FREE(text);
            return ACR_SUCCESS;
        }
*/
typedef struct ACR_Buffer_s
{
    /** points to a memory location or ACR_NULL
    */
    ACR_Byte_t* m_Pointer;

    /** length of the memory in bytes
        that m_Pointer points to
    */
    ACR_Length_t m_Length;

} ACR_Buffer_t;

/** define a buffer on the stack with the specified name
*/
#define ACR_BUFFER(name) ACR_Buffer_t name = {ACR_EMPTY_VALUE};

/** get the length of the buffer
*/
#define ACR_BUFFER_GET_LENGTH(name) name.m_Length

/** assign memory to the buffer
    IMPORTANT: do not use ACR_BUFFER_FREE() after using
               ACR_BUFFER_REFERENCE()
*/
#define ACR_BUFFER_REFERENCE(name, memory, length) name.m_Pointer = (ACR_Byte_t*)memory; if(name.m_Pointer != ACR_NULL){ name.m_Length = length; }else{ name.m_Length = ACR_ZERO_LENGTH; };

#if ACR_HAS_MALLOC == ACR_BOOL_TRUE

/** free memory used by the buffer
*/
#define ACR_BUFFER_FREE(name) if(name.m_Pointer != ACR_NULL){ free(name.m_Pointer); name.m_Pointer = ACR_NULL; } name.m_Length = ACR_ZERO_LENGTH;

/** allocate memory for the buffer
    IMPORTANT: do not use ACR_BUFFER_REFERENCE() after using
               ACR_BUFFER_ALLOC()
*/
#define ACR_BUFFER_ALLOC(name, length) if(name.m_Pointer != ACR_NULL){ free(name.m_Pointer); } name.m_Pointer = (ACR_Byte_t*)malloc(length); if(name.m_Pointer != ACR_NULL){ name.m_Length = length; }else{ name.m_Length = ACR_ZERO_LENGTH; };

#else

/** free is not available
*/
#define  ACR_BUFFER_FREE(name) name.m_Pointer = ACR_NULL; name.m_Length = ACR_ZERO_LENGTH;

/** alloc is not available
*/
#define  ACR_BUFFER_ALLOC(name, length) name.m_Pointer = ACR_NULL; name.m_Length = ACR_ZERO_LENGTH;

#endif // #if ACR_HAS_MALLOC == ACR_BOOL_TRUE

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - VARIABLE LENGTH MEMORY BUFFER
//
////////////////////////////////////////////////////////////

/** type for reference to a buffer with variable length
    - never use malloc or free directly.
    - never use void pointers.
    - always use ACR_VarBuffer_t and \see ACR_VAR_BUFFER
      defines for easy and safe usage

    example:

        int main()
        {
            ACR_VAR_BUFFER(text);

            // example text length will never exceed 32 bytes
            ACR_VAR_BUFFER_ALLOC(text, 32);
            
            // just use 1 byte without changing allocated memory
            ACR_VAR_BUFFER_ALLOC(text, 1);
            if(ACR_VAR_BUFFER_GET_MAX_LENGTH(text) >= 1)
            {
                // this buffer is safe to use with up to ACR_VAR_BUFFER_GET_MAX_LENGTH() bytes
                // use ACR_VAR_BUFFER_GET_LENGTH() to get the number of bytes in the buffer
                // copy some data to the buffer
                text.m_Buffer.m_Pointer[0] = 'a';
            }

            // now use 2 bytes without changing allocated memory
            ACR_VAR_BUFFER_ALLOC(text, 2);
            if(ACR_VAR_BUFFER_GET_MAX_LENGTH(text) >= 2)
            {
                // this buffer is safe to use with up to ACR_VAR_BUFFER_GET_MAX_LENGTH() bytes
                // use ACR_VAR_BUFFER_GET_LENGTH() to get the number of bytes in the buffer
                // copy some data to the buffer
                text.m_Buffer.m_Pointer[0] = 'a';
                text.m_Buffer.m_Pointer[1] = 'b';
            }

            // use ACR_VAR_BUFFER_GET_LENGTH() to get the number of bytes in the buffer

            ACR_BUFFER_FREE(text);
            return ACR_SUCCESS;
        }
*/
typedef struct ACR_VarBuffer_s
{
    ACR_Buffer_t m_Buffer;
    ACR_Length_t m_Length;
} ACR_VarBuffer_t;

/** define a variable sized buffer on the stack with the
    specified name
*/
#define ACR_VAR_BUFFER(name) ACR_VarBuffer_t name = {ACR_EMPTY_VALUE};

/** get the max length of the buffer
*/
#define ACR_VAR_BUFFER_GET_MAX_LENGTH(name) name.m_Buffer.m_Length

/** get the length of the buffer
*/
#define ACR_VAR_BUFFER_GET_LENGTH(name) name.m_Length

#if ACR_HAS_MALLOC == ACR_BOOL_TRUE

/** free memory used by the buffer
*/
#define ACR_VAR_BUFFER_FREE(name) if(name.m_Buffer.m_Pointer != ACR_NULL){ free(name.m_Buffer.m_Pointer); name.m_Buffer.m_Pointer = ACR_NULL; } name.m_Buffer.m_Length = ACR_ZERO_LENGTH; name.m_Length = ACR_ZERO_LENGTH;

/** allocate memory for the buffer only if needed
*/
#define ACR_VAR_BUFFER_ALLOC(name, length) if(name.m_Buffer.m_Length < length){ if(name.m_Buffer.m_Pointer != ACR_NULL){ free(name.m_Buffer.m_Pointer); } name.m_Buffer.m_Pointer = (ACR_Byte_t*)malloc(length); if(name.m_Buffer.m_Pointer != ACR_NULL){ name.m_Buffer.m_Length = length; }else{ name.m_Buffer.m_Length = ACR_ZERO_LENGTH; } name.m_Length = name.m_Buffer.m_Length; }else{ name.m_Length = length; };

#else

/** free is not available
*/
#define  ACR_VAR_BUFFER_FREE(name) name.m_Buffer.m_Pointer = ACR_NULL; name.m_Buffer.m_Length = ACR_ZERO_LENGTH; name.m_Length = ACR_ZERO_LENGTH;

/** alloc is not available
*/
#define  ACR_VAR_BUFFER_ALLOC(name, length) name.m_Buffer.m_Pointer = ACR_NULL; name.m_Buffer.m_Length = ACR_ZERO_LENGTH; name.m_Length = ACR_ZERO_LENGTH;

#endif // #if ACR_HAS_MALLOC == ACR_BOOL_TRUE

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - COMMON INFORMATIONAL VALUES
//
////////////////////////////////////////////////////////////

/** info values that can be used instead of
    true or false for options and return values

    for variable init:

        ACR_Info_t result = ACR_INFO_UNKNOWN;

    for comparison:
        
        if(result == ACR_INFO_YES)
        {
            // the result is yes
        }
        else if(result == ACR_INFO_NO)
        {
            // the result is no
        }
        else
        {
            // an unexpected result
        }

    special case for boolean values

        only use ACR_INFO_TRUE and ACR_INFO_FALSE to check
        explicitly for those values. see notes on
        ACR_BOOL_FALSE for other boolean comparisons

        good example:

        ACR_Info_t success = ACR_INFO_FALSE;
        if(success == ACR_INFO_TRUE)
        {
            // success
        }
        else
        {
            // no success
        }

        bad example:

        ACR_Info_t success = ACR_INFO_FALSE;
        // Note: this is a bad example because this non-zero
        //       success value will be interpreted as "true"
        //       even though the intention was for it to be
        //       a false value
        if(success)
        {
            // success
        }
        else
        {
            // no success
        }

    special case for program or thread return value:

        use ACR_SUCCESS for successful execution
        and any other return codes can be used as
        an error.

        do not use 0, ACR_INFO_EQUAL, or ACR_INFO_OK as
        a program or thread return code because they are
        either confusing or will not have the intended
        results

        good example:        
        
        // program or thread exit with no error
        return ACR_SUCCESS;

        good example:

        // program or thread exit error
        return ACR_INFO_ERROR;
        
        bad example:

        // program or thread exit with no error
        // Note: this is a bad example because this non-zero
        //       return value will be interpreted as an
        //       error
        return ACR_INFO_OK;

*/
typedef enum ACR_Info_e
{
    //
    // COMPARISON
    //
    ACR_INFO_EQUAL = 0,
    ACR_INFO_NOT_EQUAL,
    ACR_INFO_LESS,
    ACR_INFO_GREATER,
    ACR_INFO_UNKNOWN,

    //
    // POSITIVE,       NEGATIVE
    //
    ACR_INFO_TRUE,     ACR_INFO_FALSE,
    ACR_INFO_OK,       ACR_INFO_ERROR,
    ACR_INFO_ENABLED,  ACR_INFO_DISABLED,
    ACR_INFO_YES,      ACR_INFO_NO,
    ACR_INFO_ON,       ACR_INFO_OFF,
    ACR_INFO_START,    ACR_INFO_STOP,
    ACR_INFO_ACCEPT,   ACR_INFO_IGNORE,
    ACR_INFO_VALID,    ACR_INFO_INVALID,

    //
    // POSITION
    //
    ACR_INFO_TOP,      ACR_INFO_BOTTOM,
    ACR_INFO_FIRST,    ACR_INFO_LAST,
    ACR_INFO_PREVIOUS, ACR_INFO_NEXT,
    ACR_INFO_CURRENT,

    // DIRECTION
    ACR_INFO_UP,       ACR_INFO_DOWN,
    ACR_INFO_LEFT,     ACR_INFO_RIGHT,

    // AGE
    ACR_INFO_OLD,      ACR_INFO_NEW,

    // INSTRUCTION
    ACR_INFO_BEGIN,
    ACR_INFO_READY,
    ACR_INFO_WAIT,
    ACR_INFO_GO,
    ACR_INFO_END,

    ACR_INFO_COUNT

} ACR_Info_t;

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - DECIMAL VALUES
//
////////////////////////////////////////////////////////////

/** stores a decimal value
*/
typedef float ACR_Decimal_t;

/** default tolerance for comparison of decimal values
    \see ACR_DecimalCompare()
*/
#define ACR_DEFAULT_TOLERANCE 0.0001

/** compare two decimal values
    \param a
    \param b
    \param t the absolute value of the difference
            between a and b where they will be assumed
            to be equal values. use ACR_DEFAULT_TOLERANCE
            if unsure
    \returns - ACR_INFO_EQUAL if the decimals are equal
               within the specified tolerance (t)
             - ACR_INFO_LESS if a is less than b
             - ACR_INFO_GREATER a is greater than b
*/
#define ACR_DECIMAL_TOLERANCE_COMPARE(a,b,t) (((a-t)>b)?ACR_INFO_GREATER:((a+t)<b)?ACR_INFO_LESS:ACR_INFO_EQUAL)
#define ACR_DECIMAL_COMPARE(a,b) (ACR_DECIMAL_TOLERANCE_COMPARE(a,b,ACR_DEFAULT_TOLERANCE))

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SIMPLE FORMULAS
//
////////////////////////////////////////////////////////////

/** the circumference of a circle with the specified radius
*/
#define ACR_CIRCUMFERENCE(radius) (2*ACR_PI*radius)

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SIMPLE UTF8 STRINGS 
//                     AND UNICODE CHARACTERS
//
// Note: for UTF8 to display properly in a Windows
//       terminal you must use 
//       "Windowes Powershell ISE"
//       and first run this command:
//       chcp
//       followed by:
//       $OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
//       confirm the command worked:
//       chcp (again) should return 65001
//
////////////////////////////////////////////////////////////

/** type for string data
*/
typedef struct ACR_String_s
{
    ACR_Buffer_t m_Buffer;
    ACR_Count_t m_Count;
} ACR_String_t;

/** define a string on the stack with the specified name
*/
#define ACR_STRING(name) ACR_String_t name = {ACR_EMPTY_VALUE};

/** type for unicode characters
*/
typedef unsigned long ACR_Unicode_t;

/** given the first UTF8 byte value determine the number of
    bytes uses to encode the character
*/
#define ACR_UTF8_BYTE_COUNT(c) (((c & 0x80) != 0)?((c & 0x40) != 0)?((c & 0x20) != 0)?((c & 0x10) != 0)?4:3:2:1:1)

/////////////////////////////////////////////////////////
//                                                     //
// TYPES AND DEFINES - UNIQUE STRING VALUES            //
//                                                     //
// note: keep these in alphabetical order so that it   //
//       is easy to determine which have been used     //
//       and no duplicates will be created by accident //
//                                                     //
/////////////////////////////////////////////////////////

// *** A ***
#define ACR_INFO_STR_ACCEPT "accept"
#define ACR_MONTH_STR_APRIL "april"
#define ACR_MONTH_STR_AUGUST "august"

// *** B ***
#define ACR_INFO_STR_BEGIN "begin"
#define ACR_INFO_STR_BOTTOM "bottom"

// *** C ***
#define ACR_INFO_STR_CURRENT "current"

// *** D ***
#define ACR_MONTH_STR_DECEMBER "december"
#define ACR_INFO_STR_DISABLED "disabled"
#define ACR_INFO_STR_DOWN "down"

// *** E ***
#define ACR_INFO_STR_ENABLED "enabled"
#define ACR_INFO_STR_END "end"
#define ACR_INFO_STR_EQUAL "equal"
#define ACR_INFO_STR_ERROR "error"

// *** F ***
#define ACR_INFO_STR_FALSE "false"
#define ACR_MONTH_STR_FEBRUARY "february"
#define ACR_INFO_STR_FIRST "first"
#define ACR_DAY_STR_FRIDAY "friday"

// *** G ***
#define ACR_INFO_STR_GO "go"
#define ACR_INFO_STR_GREATER "greater"

// *** H ***

// *** I ***
#define ACR_INFO_STR_IGNORE "ignore"
#define ACR_INFO_STR_INVALID "invalid"

// *** J ***
#define ACR_MONTH_STR_JANUARY "january"
#define ACR_MONTH_STR_JULY "july"
#define ACR_MONTH_STR_JUNE "june"

// *** K ***

// *** L ***
#define ACR_INFO_STR_LAST "last"
#define ACR_INFO_STR_LEFT "left"
#define ACR_INFO_STR_LESS "less"

// *** M ***
#define ACR_MONTH_STR_MARCH "march"
#define ACR_MONTH_STR_MAY "may"
#define ACR_DAY_STR_MONDAY "monday"

// *** N ***
#define ACR_INFO_STR_NEW "new"
#define ACR_INFO_STR_NEXT "next"
#define ACR_INFO_STR_NO "no"
#define ACR_INFO_STR_NOT_EQUAL "not_equal"
#define ACR_MONTH_STR_NOVEMBER "november"

// *** O ***
#define ACR_MONTH_STR_OCTOBER "october"
#define ACR_INFO_STR_OFF "off"
#define ACR_INFO_STR_OK "ok"
#define ACR_INFO_STR_OLD "old"
#define ACR_INFO_STR_ON "on"

// *** P ***
#define ACR_INFO_STR_PREVIOUS "previous"

// *** Q ***

// *** R ***
#define ACR_INFO_STR_READY "ready"
#define ACR_INFO_STR_RIGHT "right"

// *** S ***
#define ACR_DAY_STR_SATURDAY "saturday"
#define ACR_MONTH_STR_SEPTEMBER "september"
#define ACR_INFO_STR_START "start"
#define ACR_INFO_STR_STOP "stop"
#define ACR_DAY_STR_SUNDAY "sunday"

// *** T ***
#define ACR_DAY_STR_THURSDAY "thursday"
#define ACR_INFO_STR_TOP "top"
#define ACR_INFO_STR_TRUE "true"
#define ACR_DAY_STR_TUESDAY "tuesday"

// *** U ***
#define ACR_INFO_STR_UNKNOWN "unknown"
#define ACR_INFO_STR_UP "up"

// *** V ***
#define ACR_INFO_STR_VALID "valid"

// *** W ***
#define ACR_INFO_STR_WAIT "wait"
#define ACR_DAY_STR_WEDNESDAY "wednesday"

// *** X ***
// *** Y ***
#define ACR_INFO_STR_YES "yes"

// *** Z ***

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - TEST
//
////////////////////////////////////////////////////////////

/** internal test of ACR library functions
    \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_Test(void);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - COMMON INFORMATIONAL VALUES
//
////////////////////////////////////////////////////////////

/** get the info value as a string
    \param info the info value \see enum ACR_Info_e
    \returns a reference to a string
*/
ACR_String_t ACR_InfoToString(
    ACR_Info_t info);

/** get the info value from a string
    \param src a reference to a string
    \returns an info value from \see enum ACR_Info_e or
             ACR_INFO_UNKNOWN if not found
*/
ACR_Info_t ACR_InfoFromString(
    ACR_String_t src);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - DATE AND TIME VALUES
//
////////////////////////////////////////////////////////////

/** get the day of week value as a string
    \param dayOfWeek the day of week value
           \see enum ACR_DayOfWeek_e
    \returns a reference to a string
*/
ACR_String_t ACR_DayOfWeekToString(
    ACR_DayOfWeek_t dayOfWeek);

/** get the day of week value from a string
    \param src a reference to a string
    \returns a value from \see enum ACR_DayOfWeek_e or
             ACR_DAY_OF_WEEK_UNKNOWN if not found
*/
ACR_DayOfWeek_t ACR_DayOfWeekFromString(
    ACR_String_t src);

/** get the month value as a string
    \param month the month
           \see enum ACR_Month_e
    \returns a reference to a string
*/
ACR_String_t ACR_MonthToString(
    ACR_Month_t month);

/** get the month value from a string
    \param src a reference to a string
    \returns a value from \see enum ACR_Month_e or
             ACR_MONTH_UNKNOWN if not found
*/
ACR_Month_t ACR_MonthFromString(
    ACR_String_t src);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - SIMPLE UTF8 STRINGS
//                    AND UNICODE CHARACTERS
//
////////////////////////////////////////////////////////////

/** convert a unicode charcter to its lower-case
    representation
*/
ACR_Unicode_t ACR_UnicodeToLower(
    ACR_Unicode_t u);

/** convert a unicode charcter to its upper-case
    representation
*/
ACR_Unicode_t ACR_UnicodeToUpper(
    ACR_Unicode_t u);

/** convert UTF8 encoded data to a unicode value
    \param mem a valid pointer to the UTF8 encoded character
           in memory
    \param bytes the number of bytes for this UTF8 encoded
           unicode value. use ACR_UTF8_BYTE_COUNT(mem[0])
           if unsure
    \returns the unicode value
*/
ACR_Unicode_t ACR_Utf8ToUnicode(
    ACR_Byte_t* mem,
    int bytes);

/** get a reference to a null-terminated string in memory 
    with support for UTF8 encoding
    \param src a pointer to a null-terminated string in
           memory
    \param srcLength the max number of bytes from src this
           function will search. use ACR_MAX_LENGTH if
           unsure
    \param maxCharacters the max number of characters this
           function will count. use ACR_MAX_COUNT if unsure
    \returns a string referennce
*/
ACR_String_t ACR_StringFromMemory(
    void* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters);

/** compare a string to a null-terminated string in memory
    with support for UTF8 encoding
    \param string the known string to compare to
    \param src a pointer to a null-terminated string in
           memory
    \param srcLength the max number of bytes from mem this
           function will search. use ACR_MAX_LENGTH if 
           unsure
    \param maxCharacters the max number of characters this
           function will compare. use ACR_MAX_COUNT if 
           unsure
    \param caseSensitive set to ACR_INFO_YES for 
           case-sensitive comparison (faster) or ACR_INFO_NO
           for case-insensitive (slower)
    \returns - ACR_INFO_EQUAL if the strings are equal up
               to maxCharacters
             - ACR_INFO_LESS if src has less characters or
               is less than string
             - ACR_INFO_GREATER if src has more characters
               or is greater than string
             - ACR_INFO_INVALID if src is invalid
*/
ACR_Info_t ACR_StringCompareToMemory(
    ACR_String_t string,
    void* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters,
    ACR_Info_t caseSensitive);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - OTHER
//
////////////////////////////////////////////////////////////


#endif
