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

/** \file public.h
 
   This header is used to include all of the public headers
   and provide a high level explanation of their use.

   ### Getting Started Quickly ###

   Complete example programs are found in "/ACR/example".
   More detailed tests are found in "/ACR/test".
   For those familiar with C, the fastest way to get started
   is to look at ACR_TestCommon() found in
   "/ACR/test/ACR/test/test_common.c"

   Note: That's not a typo, the tests really are placed in
         a folder called "/ACR/test/ACR/test". This
         makes it easy to include test header files like
         any other header file in this library by placing
         "/ACR/test" in the project settings include path.

   ### New to C? ###

   Q: Where can I learn more about this header?
   A: Many topics are covered by this header. Each topic
      begins with a large comment block and will follow
      with additional details. Look for "New to C?" for
      detailed explanations.

   Q: What is a "header"?
   A: A header (.h file) is a file that predefines the 
      names of functions and values that are then fully
      defined by the source file. In many cases it is
      only necessary to read the header file to
      understand what the code in a source file does.
      The header can be thought of as "Public" so that
      any part of a program may use it.

   Q: What is a "source"?
   A: A source (.c file) fully defines variables and functions.
      The source can be thought of as "Private" because
      anything defined within the file cannot safely be used
      in another part of a program without a header.

*/
#ifndef _ACR_PUBLIC_H_
#define _ACR_PUBLIC_H_

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - BOOLEAN (TRUE/FALSE)
//
////////////////////////////////////////////////////////////

/**
   Include the file "ACR/public/public_bool.h" to
   define ACR_BOOL_FALSE and ACR_BOOL_TRUE and the
   data type ACR_Bool_t.

   ### New to C? ###

   Q: What is an "include"?
   A: An include allows a header to be used
      by another header or source file. The
      file to include must be in a path known
      to the compiler. On some platforms,
      the path is case-sensitive so it is
      important to include the file name exactly
      as it appears in the file system.

   Q: What is a "define"?
   A: A define is a name assigned to a value. Before the code
      is compiled, a preprocessor will replace the name with
      the value. The value can be any valid code such as numbers, 
      text "strings", or even code snippets that can accept 
      parameters (these are called Macros)

   Q: What is a "typedef"?
   A: A typedef is a way to expand the types of data that
      can be stored by a variable. It is similar to a define
      in that the name specified by the typedef refers to
      another value, but it is more specific and helps to
      more clearly define the purpose of the data.
      
   Q: What is a boolean?
   A: A boolean is a "true" or "false" value. In C, a value
      of 0 is "false" and all other values are "true".
      A confusing thing about C is that some functions will
      return 0 to mean success while others will return 0
      as an error. This is why ACR defines many more specific
      values that can be used as return codes.
      See the include file "ACR/public/public_info.h" for more details.

*/
#include "ACR/public/public_bool.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - PLATFORM AND COMPILER
//
////////////////////////////////////////////////////////////

/* 
   Include the file "ACR/public/public_config.h" to
   define ACR_HAS_PLATFORM, ACR_PLATFORM_NAME,
   ACR_HAS_IDE, ACR_IDE_NAME, ACR_HAS_COMPILER,
   and ACR_COMPILER_NAME.

   Read the header for details on how to configure
   your project for a specific platform and for
   other global configuraton options of this library.

   ### New to C? ###

   Q: Why are there platform settings?
   A: To allow ACR to be used with as many different types
      of projects as possible. These platform defines provide
      support for Windows, Mac OS X, Linux, or even an embedded
      microprocessor with no operating system. Code is removed or
      added based on the platform settings using the preprocessor
      commands #ifdef and #ifndef.

*/
#include "ACR/public/public_config.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - FUNCTIONS
//
////////////////////////////////////////////////////////////

/**
   Include the file "ACR/public/public_functions.h" to
   define ACR_SUCCESS, ACR_FAILURE, ACR_UNUSED(),
   and ACR_TYPEDEF_CALLBACK()

   ### New to C? ###

      Q: What is a function?
      A: A function is a named block of code
         designed to perform a task. Functions
         can range in complexity from the most
         simple 1 line operation to the most
         complex arrangement of hundreds of
         lines of code.

      Q: What is a callback function?
      A: A callback function is a variable
         that can act as the function it is
         assigned to.

*/
#include "ACR/public/public_functions.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MEMORY
//
////////////////////////////////////////////////////////////

/** 
   Include the file "ACR/public/public_memory.h" to
   define ACR_EMPTY_VALUE, ACR_USE_64BIT, ACR_Length_t,
   ACR_ZERO_LENGTH, ACR_MAX_LENGTH, ACR_MEMSET(), ACR_MEMCPY(),
   ACR_NULL, and ACR_PointerValue_t

   To disable the use of 64bit pointers and values,
   define ACR_CONFIG_NO_64BIT in your project settings.

   ### New to C? ###

   Q: What is 64bit?
   A: This refers to the number of bits used for a memory address.
      The majority of consumer-level computers when this was written
      use 64bits for memory addresses so that they can support a
      larger amount of memory than in the past. Some platforms
      do not support 64bit addressing and instead use 32bits, 16bits,
      or even 8bits. In some cases, a platform that does not natively
      support 64bits cannot store a 64bit integer, which changes
      the maximum value that can be stored in a simple type.

   Q: What is uninitialized memory?
   A: When a variable is created in a program, the initial value
      of that variable is unknown and referred to as
      uninitialized. A simple variable can be initialized by
      assigning a value but a variable that represents a larger
      area of memory must be initialized in another way.
      see ACR_MEMSET() and ACR_CLEAR_MEMORY() for more details.
 
*/
#include "ACR/public/public_memory.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - DEBUG
//
////////////////////////////////////////////////////////////

/** 

   Include the file "ACR/public/public_debug.h" to
   define ACR_IS_DEBUG and ACR_DEBUG_PRINT()

   ACR_DEBUG_PRINT() is an especially handy macro that
   will only write to the debug output when the project 
   is configured for debug mode. This is done by defining
   ACR_CONFIG_DEBUG in your project settings.

   ### New to C? ###

   Q: What is debug?
   A: This refers to running a program such that it is easier
      to understand what may be causing a bug/problem.

   Q: Why not always use debug?
   A: There are two main reasons:
      1. it can greatly impact the speed of the program
      2. the users of the program may be confused by the extra information

*/
#include "ACR/public/public_debug.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MEMORY HEAP
//
////////////////////////////////////////////////////////////

/**
   Include the file "ACR/public/public_heap.h" to
   define ACR_MALLOC(), ACR_REALLOC(), and ACR_FREE()

   The heap can be disabled entirely in this library
   by defining ACR_CONFIG_NO_MALLOC in your project settings.

   If you need a heap but your platform doesn't provide one,
   define ACR_CONFIG_NO_LIBC in your project settings
   and ACR will implement a rudimentary heap instead.
   The source file "/ACR/src/ACR/heap.c" must be added to your
   project for this to work. see "ACR/heap.h" for details.

   Instead of using the heap, a program can use global
   variables for large amounts of data and the stack
   for working data. 

   ### New to C? ###

   Q: What is the heap?
   A: This refers to the area of memory reserved for
      the program to use dynamically. This means the
      program can use as much or as little of the heap
      as it wants to but must remain within it's allotted
      address range. Access to the heap is protected
      so that it is possible for the program to gracefully
      handle when it runs out of heap space.

   Q: What is the stack?
   A: This refers to the area of memory reserved for
      program execution that can also be used to store 
      variable data. It is best to use the stack sparingly
      for large datasets because the program will terminate
      unexpectedly if it tries to use more stack memory than
      was allotted. This is called a Stack Overflow and is
      the namesake for the popular website.

   Q: What is a global variable?
   A: A global variable is defined outside of any function
      and thus is accessible by all functions (or at least
      all functions within the same source file). The memory
      for the variable is allocated at run-time and will
      remain available at the same address and same size for
      the life of the program. The opposite of a global
      variable is a local variable.

   Q: What is a local variable?
   A: A local variable is defined within a function. When
      the function is called, memory is allocated on the
      stack for the variable and when the function is
      complete (or returns) the memory is released from
      the stack and made available to future function calls.

*/
#include "ACR/public/public_heap.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - BYTES AND FLAGS
//
////////////////////////////////////////////////////////////

/**
    Include the file "ACR/public/public_byte_order.h" to
    define ACR_Byte_t, ACR_Flags_t, ACR_HAS_FLAG(),
    ACR_ADD_FLAGS(), and ACR_REMOVE_FLAGS()

    ### New to C? ###

    Q: What is a byte?
    A: A byte is a group of 8 bits and is typically the smallest
       amount of memory that a variable can use to store a value.

    Q: What are flags?
    A: Flags are a method of setting, clearing, and checking
       the state of individual bits within one or more bytes

*/
#include "ACR/public/public_bytes_and_flags.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - ENDIANNESS
//
////////////////////////////////////////////////////////////

/**
    Include the file "ACR/public/public_byte_order.h" to
    define ACR_Unsigned_16bit_t, ACR_Unsigned_32bit_t, 
    ACR_IS_BIG_ENDIAN, ACR_BYTE_ORDER_16(), ACR_BYTE_ORDER_32(),
    and ACR_BYTE_ORDER_64()

    ### New to C? ###

    Q: What is endianness?
    A: This refers to the order that multi-byte values
       are stored in memory. It is only necessary to
       understand when a program must work with itself
       or other programs on platforms that differ in
       endianness.
       See the include file "ACR/public/public_byte_order.h" for more details.

    Q: What is a multi-byte value?
    A: A multi-byte value is any value that requires
       more than 8 bits to represent. Standard sizes
       include 16 bit, 32 bit, and 64 bit but there
       are times where other sizes may be used.
       Some examples:

       A 16 bit value such as one stored by the ACR_16bit_t
       type can store decimal values -32,768 to 32,767
       but is not used often because the simple int type can
       usually store that or more.

       ACR_Unsigned_16bit_t can store decimal values 0 to 65,535
       and is most used for IP (Internet Protocol) port numbers

       ACR_32bit_t can store decimal values -2,147,483,648 to 2,147,483,647
       and is most famously used for Unix Timestamps to count the
       number of seconds since January 1st, 1970. There is a problem in
       the near future similar to the Y2K problem when this type will rollover
       to its smallest negative value on Tuesday, January 19th, 2038.

       ACR_Unsigned_32bit_t can store decimal values 0 to 4,294,967,295
       and that's why the FAT32 filesystem's max file size is 4GB.

       Examples of non-standard multibyte values are:
       256bit - commonly used for encryption
        24bit - commonly used for high definition digital audio
        10bit - commonly used to represent colors in digital video

*/
#include "ACR/public/public_byte_order.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - COUNTING
//
////////////////////////////////////////////////////////////

/**

    Include the file "ACR/public/public_count.h" to define
    ACR_Count_t, ACR_ZERO_COUNT, ACR_MAX_COUNT, ACR_POINTER_AT(),
    ACR_VALUE_AT()

    ### New to C? ###

    Q: What is an array?
    A: An array is an ordered list of data. Each position
       within the list contains the same type of data.
       The type can be a single byte or can be an entire
       data structure.

       A nice way to represent an array is as a single row
       of a spreadsheet like this. Note that the position
       of column A is 0 and the position of column H is 7

       0    1    2    3    4    5    6    7
       -----------------------------------------
       | A  | B  | C  | D  | E  | F  | G  | H  |
       -----------------------------------------

    Q: What is zero-indexed?
    A: In C, the position of each data item in an array
       begins at index 0 and ends at the array length minus 1.
       See the include file "ACR/public/public_count.h" for more details.

*/
#include "ACR/public/public_count.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MEMORY BLOCKS
//
////////////////////////////////////////////////////////////

/**
    Include the file "ACR/public/public_blocks.h" to define
    ACR_Block_t, ACR_Blocks_t, ACR_MIN_BLOCKS_NEEDED(), 
    ACR_MIN_BLOCKS_NEEDED_BY_SIZE(), ACR_LENGTH_TO_BLOCKS(), and
    ACR_LENGTH_TO_BLOCKS_BY_SIZE()

    Use ACR_Block_t to store the number of blocks when counting
    by block number. Use ACR_Blocks_t to store not only the number
    of blocks but also the number of extra bytes when working
    with data that is not a multiple of the block size.

    ### New to C? ###

    Q: What is a memory block?
    A: This refers to sequential memory addresses. Although
       a block size varies depending on the purpose, each
       platform has a standard block size that it uses for
       addressing and copying data. It is good to know this
       size when performing optimized copy operations or
       when placing data in memory where it can be accessed 
       by specialized hardware.
       See the include file "ACR/public/public_blocks.h" and
       "ACR/public/public_alignedbuffer.h" for more details.
*/
#include "ACR/public/public_blocks.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - DATE AND TIME VALUES
//
////////////////////////////////////////////////////////////

/**
    Include the file ACR/public/public_dates_and_times.h to
    define months as an enum and type ACR_Month_t,
    day of the week as an enum and type ACR_DayOfWeek_t,
    ACR_HOUR_PER_DAY, ACR_MIN_PER_HOUR, ACR_SEC_PER_MIN,
    ACR_MILLI_PER_SEC, and many more time constants

    If you are looking for the current date or time, this isn't it.
    See "ACR/public/public_clock.h" for more details.

    ### New to C? ###

    Q: What is an "enum"?
    A: An enum, short for enumeration, is a list of names
        with a number assigned to each name. The names are
        used by the preprocessor just like a define.

*/
#include "ACR/public/public_dates_and_times.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - REAL TIME CLOCK
//
////////////////////////////////////////////////////////////

/**
    Include the file ACR/public/public_clock.h to define
    ACR_HAS_RTC, ACR_TIME_NOW(), ACR_DATETIME_FROM_TIME(),
    ACR_Time_t, ACR_DateTime_t, ACR_DATETIME_NOW(), 
    ACR_DATETIME_YEAR(), ACR_DATETIME_MONTH(), ACR_DATETIME_HOUR(),
    and more

    If your platform doesn't have an RTC, define ACR_CONFIG_NO_RTC
    in your project settings and see ACR_TimeProcessSecondTick() in
    "ACR/common.h" for how to simulate a real-time clock

    ### New to C? ###

    Q: What is a Real Time Clock (RTC)?
    A: This refers to the physical part of the computer
       that is tasked with keeping an accurate count of
       the amount of time that has past since the time
       was last set. Devices that do not have an RTC
       can simulate one using a 1 second timer but will
       have to correct the time more often due to drift.
       See the include file ACR/public/public_clock.h for
       more details.
*/
#include "ACR/public/public_clock.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SIMPLE MEMORY BUFFER
//
////////////////////////////////////////////////////////////

/**
    ### New to C? ###

    Q: What is a buffer?
    A: A buffer is a reference to an area of memory that
       includes the exact address of the memory and the number
       of bytes allocated, which is called the length or
       size of the buffer.
       See the include file ACR/public/public_buffer.h for more details.
*/
#include "ACR/public/public_buffer.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - VARIABLE LENGTH MEMORY BUFFER
//
////////////////////////////////////////////////////////////

/**
    ### New to C? ###

    Q: Why can't a simple memory buffer change size?
    A: Sometimes it can, but sometimes there is not
       enough space between the start of one buffer and
       the start of the next. When there isn't enough
       space, a new address must be selected and all of
       the existing data must be copied. This can be
       complicated to manage using a simple memory buffer
       so a variable buffer may be used instead.
       See the include file ACR/public/public_varbuffer.h for more details.
*/
#include "ACR/public/public_varbuffer.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - ALIGNED MEMORY BUFFER
//
////////////////////////////////////////////////////////////

/**
    ### New to C? ###

    Q: What does it mean for memory to be aligned?
    A: Computers work with memory in blocks. There are some hardware components
       that require data to be stored at the start of one of these blocks in
       order to operate correctly. An aligned buffer makes it easy to
       placing data in memory where it can be accessed by specialized hardware
       See the include file ACR/public/public_alignedbuffer.h for more details.
*/
#include "ACR/public/public_alignedbuffer.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - COMMON INFORMATIONAL VALUES
//
////////////////////////////////////////////////////////////
#include "ACR/public/public_info.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - DECIMAL VALUES
//
////////////////////////////////////////////////////////////
#include "ACR/public/public_decimal.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MATH
//
////////////////////////////////////////////////////////////
#include "ACR/public/public_math.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SIMPLE UTF8 STRINGS AND UNICODE CHARACTERS
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
#include "ACR/public/public_string.h"

/////////////////////////////////////////////////////////
//                                                     //
// TYPES AND DEFINES - UNITS OF MEASURE                //
//                                                     //
/////////////////////////////////////////////////////////
#include "ACR/public/public_units.h"

/////////////////////////////////////////////////////////
//                                                     //
// TYPES AND DEFINES - UNIQUE STRING VALUES            //
//                                                     //
/////////////////////////////////////////////////////////
#include "ACR/public/public_unique_strings.h"

#endif
