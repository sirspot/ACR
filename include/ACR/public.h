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
 
    This header includes many common defines, enums, functions, and typedefs.
    In many cases, this is the only header needed for the ACR library to
    be a useful addition to your project.

    ### New to C? ###

    Q: What is a "header"?
    A: A header (.h file) is a file that predefines the names of
       various functions and values that are then fully
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

    Q: What is a "define"?
    A: A define is a name assigned to a value. Before the code
       is compiled, a preprocessor will replace the name with
       the value. The value can be any valid code such as numbers, 
       "strings", or even code snippets that can accept parameters
       (these are called Macros)

    Q: What is an "enum"?
    A: An enum, short for enumeration, is a list of names
       with a number assigned to each name. The names are
       used by the preprocessor just like a define.

    Q: What is a "typedef"?
    A: A typedef is a way to expand the types of data that
       can be stored by a variable. It is similar to a define
       in that the name specified by the typedef refers to
       another value, but it is more specific and helps to
       more clearly define the purpose of the data.

    Q: Where can I learn more about this header?
    A: Many topics are covered by this header. Each topic
       begins with a large comment block and will follow
       with additional details. Look for "New to C?" for
       detailed explanations of each topic.

    ### Getting Started Quickly ###

    An example of how to use many of the featues of this header
    are included in the function called ACR_Test(). For those
    familiar with C, the fastest way to get started is to look
    at the source code for that function in "src/ACR/public.c"

    In addition to the ACR_Test() function, you may want to
    skim this header before using it. There is a lot here, roughly
    organized by large comment blocks that look like this:

    /////
    //
    // TOPIC GOES HERE
    //
    /////

*/
#ifndef _ACR_PUBLIC_H_
#define _ACR_PUBLIC_H_

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - BOOLEAN (TRUE/FALSE)
//
////////////////////////////////////////////////////////////

/**
    ### New to C? ###

    Q: What is a boolean?
    A: A boolean is a "true" or "false" value. In C, a value
       of 0 is "false" and all other values are "true".
       A confusing thing about C is that some functions will
       return 0 to mean success while others will return 0
       as an error. This is why ACR defines many more specific
       values that can be used as return codes.
       See the include file ACR/public/public_bool_and_empty.h for more details.

    Q: What is an "include"?
    A: An include allows a header to be used
       by another header or source file. The
       file to include must be in a path known
       to the compiler. On some platforms,
       the path is case-sensitive so it is
       important to include the file name exactly
       as it appears in the file system.

*/
#include "ACR/public/public_bool.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - PLATFORM AND COMPILER
//
////////////////////////////////////////////////////////////

/* 
    ### New to C? ###

    Q: Why are there platform settings?
    A: To allow ACR to be used with as many different types
       of projects as possible. These platform defines provide
       support for Windows, Mac OS X, Linux, or even an embedded
       microprocessor with no operating system. Code is removed or
       added based on the platform settings using the preprocessor
       commands #ifdef and #ifndef.
       See the include file ACR/public/public_config.h for more details.

*/
#include "ACR/public/public_config.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - FUNCTIONS
//
////////////////////////////////////////////////////////////

/**
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
           See the include file ACR/public/public_functions.h for more details.

*/
#include "ACR/public/public_functions.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MEMORY
//
////////////////////////////////////////////////////////////

/** 
    ### New to C? ###

    Q: What is 64bit?
    A: This refers to the number of bits used for a memory address.
       The majority of consumer-level computers when this was written
       use 64bits for memory addresses so that they can support a
       larger amount of memory than in the past. Some platforms
       do not support 64bit addressing and instead use 32bits, 16bits,
       or even 8bits. In some cases, a platform that does not support
       64bits cannot store a 64bit integer, which changes the maximum
       value that can be stored in a simple type.

    Q: What is uninitialized memory?
    A: When a variable is created in a program, the initial value
       of that variable is unknown and is referred to as
       uninitialized. A simple variable can be initialized by
       assigning a value but a variable that represents a larger
       area of memory must be initialized in another way.
       see ACR_MEMSET and ACR_CLEAR_MEMORY in the include file
       ACR/public/public_memory.h for more details.
 
*/
#include "ACR/public/public_memory.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - DEBUG
//
////////////////////////////////////////////////////////////

/** defines ACR_IS_DEBUG and ACR_DEBUG_PRINT such that
    printed messages are only compiled if desired

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
    ### New to C? ###

    Q: What is the heap?
    A: This refers to the area of memory reserved for
       the program to use dynamically. This means the
       program can use as much or as little of the heap
       as it wants to but must remain within it's allotted
       address range. Access to the heap is protected
       so that it is possible for the program to gracefully
       handle when it runs out of heap space.
       See the include file ACR/public/public_heap.h for more details.

    Q: What is the stack?
    A: This refers to the area of memory reserved for
       program execution that can also be used to store 
       variable data. It is best to use the stack sparingly
       for large datasets because the program will terminate
       unexpectedly if it tries to use more stack memory than
       was allotted. This is called a Stack Overflow.

*/
#include "ACR/public/public_heap.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - ENDIANNESS
//
////////////////////////////////////////////////////////////

/**
    ### New to C? ###

    Q: What is endianness?
    A: This refers to the order bytes are stored in memory.
       It is only necessary to understand when a program
       must work with itself or other programs on various
       hardware platforms.
       See the include file ACR/public/public_byte_order.h for more details.
*/
#include "ACR/public/public_byte_order.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - BYTES AND FLAGS
//
////////////////////////////////////////////////////////////

/**
    ### New to C? ###

    Q: What is a byte?
    A: A byte is a group of 8 bits.
       
    Q: What are flags?
    A: Flags are a method of setting, clearing, and checking
       the state of individual bits
       See the include file ACR/public/public_bytes_and_flags.h for more details.
*/
#include "ACR/public/public_bytes_and_flags.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - COUNTING
//
////////////////////////////////////////////////////////////
#include "ACR/public/public_count.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MEMORY BLOCKS
//
////////////////////////////////////////////////////////////

/**
    ### New to C? ###

    Q: What is a memory block?
    A: This refers to the smallest addressable memory size.
       It is good to know this size when performing optimized
       copy operations or when placing data in memory where
       it can be accessed by specialized hardware.
       See the include file ACR/public/public_blocks.h for more details.
*/
#include "ACR/public/public_blocks.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - DATE AND TIME VALUES
//
////////////////////////////////////////////////////////////
#include "ACR/public/public_dates_and_times.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - REAL TIME CLOCK
//
////////////////////////////////////////////////////////////

/**
    ### New to C? ###

    Q: What is a Real Time Clock (RTC)?
    A: This refers to the physical part of the computer
       that is tasked with keeping an accurate count of
       the amount of time that has past since the time
       was last set. Devices that do not have an RTC
       can simulate one using a 1 aecond timer but will
       have to correct the time more often due to drift.
       See the include file ACR/public/public_clock.h for more details.
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
