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
       See the include file ACR/public_bool_and_empty.h for more details.

    Q: What is an "include"?
    A: An include allows a header to be used
       by another header or source file. The
       file to include must be in a path known
       to the compiler. On some platforms,
       the path is case-sensitive so it is
       important to include the file name exactly
       as it appears in the file system.

*/
#include "ACR/public_bool.h"

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
       See the include file ACR/public_config.h for more details.

*/
#include "ACR/public_config.h"

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
           See the include file ACR/public_functions.h for more details.

*/
#include "ACR/public_functions.h"

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
       ACR/public_memory.h for more details.
 
*/
#include "ACR/public_memory.h"

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
#include "ACR/public_debug.h"

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
       See the include file ACR/public_heap.h for more details.

    Q: What is the stack?
    A: This refers to the area of memory reserved for
       program execution that can also be used to store 
       variable data. It is best to use the stack sparingly
       for large datasets because the program will terminate
       unexpectedly if it tries to use more stack memory than
       was allotted. This is called a Stack Overflow.

*/
#include "ACR/public_heap.h"

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
       See the include file ACR/public_byte_order.h for more details.
*/
#include "ACR/public_byte_order.h"

#if ACR_USE_64BIT == ACR_BOOL_TRUE

    /** byte order swap of 64 bit value
    */
    #define ACR_BYTE_ORDER_SWAP_64(x)   ((((unsigned long long)(x) & 0x00000000000000ffULL) << 56) | \
                                        (((unsigned long long)(x) & 0x000000000000ff00ULL) << 40) | \
                                        (((unsigned long long)(x) & 0x0000000000ff0000ULL) << 24) | \
                                        (((unsigned long long)(x) & 0x00000000ff000000ULL) <<  8) | \
                                        (((unsigned long long)(x) & 0x000000ff00000000ULL) >>  8) | \
                                        (((unsigned long long)(x) & 0x0000ff0000000000ULL) >> 24) | \
                                        (((unsigned long long)(x) & 0x00ff000000000000ULL) >> 40) | \
                                        (((unsigned long long)(x) & 0xff00000000000000ULL) >> 56))
    #ifdef ACR_ENDIAN_DYNAMIC
        #define ACR_BYTE_ORDER_64(x) ((ACR_IS_BIG_ENDIAN == 0)?ACR_BYTE_ORDER_SWAP_64(x):x)
    #else
        #if ACR_IS_BIG_ENDIAN == 0
            #define ACR_BYTE_ORDER_64(x) (ACR_BYTE_ORDER_SWAP_64(x))
        #else
            #define ACR_BYTE_ORDER_64(x) (x)
        #endif // #if ACR_IS_BIG_ENDIAN == 0
    #endif // #ifdef ACR_ENDIAN_DYNAMIC

#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

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
       See the include file ACR/public_bytes_and_flags.h for more details.
*/
#include "ACR/public_bytes_and_flags.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - COUNTING
//
////////////////////////////////////////////////////////////

/** type for a typical count such as the number of items in an array
	\see ACR_MAX_COUNT for the maximum value that can be
	stored by this data type
*/
typedef unsigned long ACR_Count_t;

/** used for setting a count explicitly to zero
*/
#define ACR_ZERO_COUNT 0

/** max value that can be stored by the ACR_Count_t type such that
    it will not overflow when added to 1 
    (this allows ACR_MAX_COUNT+1 to be greater than ACR_ZERO_COUNT)
*/
#define ACR_MAX_COUNT 4294967294UL // hex value 0xFFFFFFFE

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
       See the include file ACR/public_blocks.h for more details.
*/
#include "ACR/public_blocks.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - DATE AND TIME VALUES
//
////////////////////////////////////////////////////////////
#include "ACR/public_dates_and_times.h"

#define ACR_DAYS_PER_MONTH(fourDigitYear, month) (ACR_DaysPerMonth(month, ACR_YearIsLeapYear(fourDigitYear)))
#define ACR_DAYS_PER_YEAR(fourDigitYear) (ACR_YearIsLeapYear(fourDigitYear)?ACR_DAYS_PER_LEAP_YEAR:ACR_DAYS_PER_STANDARD_YEAR)

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
       See the include file ACR/public_clock.h for more details.
*/
#include "ACR/public_clock.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SIMPLE MEMORY BUFFER
//
////////////////////////////////////////////////////////////

// included for ACR_Length_t
#include "ACR/public_memory.h"

// included for ACR_Flags_t
#include "ACR/public_bytes_and_flags.h"

#ifdef ACR_COMPILER_VS2017
#pragma warning(push)
// disable warning C4820: padding added after data member
#pragma warning(disable:4820)
#endif
/** type for reference to a memory area.
    - prevents use of malloc and free directly.
    - prevents use of void pointers without associated memory length
	- include "ACR/buffer.h" for easy and safe functions
	- see ACR_BUFFER defines for safe access via macros
*/
typedef struct ACR_Buffer_s
{
    /** points to a memory location or ACR_NULL
    */
    void* m_Pointer;

    /** length of the memory in bytes
        that m_Pointer points to
    */
    ACR_Length_t m_Length;

	/** flags to change the default operation of the buffer
	    see enum ACR_BufferFlags_e
	*/
	ACR_Flags_t m_Flags;

} ACR_Buffer_t;
#ifdef ACR_COMPILER_VS2017
#pragma warning(pop)
#endif

/** buffer flags to change default behavior
*/
enum ACR_BufferFlags_e
{
	ACR_BUFFER_FLAGS_NONE = 0x00,
	ACR_BUFFER_IS_REF     = 0x01
};

/** define a buffer on the stack with the specified name
*/
#define ACR_BUFFER(name) ACR_Buffer_t name = {ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE};

/** define a buffer using memory of the specified size on the stack and with the specified name
*/
#define ACR_BUFFER_USE_DATA(name, data, length) ACR_Buffer_t name = {data,length,ACR_BUFFER_IS_REF};

/** determine if the buffer is valid
*/
#define ACR_BUFFER_IS_VALID(name) ((name.m_Pointer != ACR_NULL) && (name.m_Length > 0))

/** get the length of the buffer
*/
#define ACR_BUFFER_GET_LENGTH(name) name.m_Length

/** clear the buffer
/// \todo make a version without sizet
*/
#define ACR_BUFFER_CLEAR(name) ACR_CLEAR_MEMORY(name.m_Pointer, (size_t)name.m_Length)

/** assign memory to the buffer
    /// \todo make a version of this without free()
*/
#define ACR_BUFFER_REFERENCE(name, memory, length) \
        if(name.m_Pointer != ACR_NULL) \
		{ \
			if(ACR_HAS_FLAG(name.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE) \
			{ \
				free(name.m_Pointer); \
			} \
		} \
		name.m_Pointer = (void*)memory; \
		if(name.m_Pointer != ACR_NULL) \
		{ \
			name.m_Length = length; \
			ACR_ADD_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF); \
		} \
		else \
		{ \
			name.m_Length = ACR_ZERO_LENGTH; \
			ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF); \
		}

#if ACR_HAS_MALLOC == ACR_BOOL_TRUE

/** free memory used by the buffer
*/
#define ACR_BUFFER_FREE(name) \
        if(name.m_Pointer != ACR_NULL) \
		{ \
			if(ACR_HAS_FLAG(name.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE) \
			{ \
				free(name.m_Pointer); \
			} \
			name.m_Pointer = ACR_NULL; \
		} \
		name.m_Length = ACR_ZERO_LENGTH; \
		ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF);

/** allocate memory for the buffer
*/
#define ACR_BUFFER_ALLOC(name, length) \
        if(name.m_Pointer != ACR_NULL) \
		{ \
			if(ACR_HAS_FLAG(name.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE) \
			{ \
				free(name.m_Pointer); \
			} \
		} \
		name.m_Pointer = malloc((size_t)(length)+1); \
		if(name.m_Pointer != ACR_NULL) \
		{ \
            ((ACR_Byte_t*)name.m_Pointer)[length] = 0; \
			name.m_Length = length; \
		} \
		else \
		{ \
			name.m_Length = ACR_ZERO_LENGTH; \
		} \
		ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF);

#else

/** free is not available
*/
#define ACR_BUFFER_FREE(name) name.m_Pointer = ACR_NULL; name.m_Length = ACR_ZERO_LENGTH; ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF);

/** malloc is not available
*/
#define ACR_BUFFER_ALLOC(name, length) name.m_Pointer = ACR_NULL; name.m_Length = ACR_ZERO_LENGTH; ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF);

#endif // #if ACR_HAS_MALLOC == ACR_BOOL_TRUE        

/** explicitly free the memory this buffer references
*/
#define ACR_BUFFER_FORCE_FREE(name)\
        ACR_REMOVE_FLAGS(name.m_Flags, ACR_BUFFER_IS_REF); \
        ACR_BUFFER_FREE(name);

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - VARIABLE LENGTH MEMORY BUFFER
//
////////////////////////////////////////////////////////////

/** type for reference to a memory area with variable length
	- prevents use of malloc and free directly.
	- prevents use of void pointers without associated memory length
	- include "ACR/varbuffer.h" for easy and safe functions
	- see ACR_VAR_BUFFER defines for safe access via macros
*/
typedef struct ACR_VarBuffer_s
{
    ACR_Buffer_t m_Buffer;
    ACR_Length_t m_MaxLength;
} ACR_VarBuffer_t;

/** define a variable sized buffer on the stack with the
    specified name
*/
#define ACR_VAR_BUFFER(name) ACR_VarBuffer_t name = {{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE},ACR_LENGTH_ZERO};

/** get the max length of the buffer
*/
#define ACR_VAR_BUFFER_GET_MAX_LENGTH(name) name.m_MaxLength

/** get the length of the buffer
*/
#define ACR_VAR_BUFFER_GET_LENGTH(name) name.m_Buffer.m_Length

/** reset the buffer length to zero
*/
#define ACR_VAR_BUFFER_RESET(name) name.m_Buffer.m_Length = ACR_ZERO_LENGTH;

/** set the length of the buffer up to the max length
*/
#define ACR_VAR_BUFFER_SET_LENGTH(name, length) \
		if(length <= name.m_MaxLength) \
		{ \
            name.m_Buffer.m_Length = length; \
        }

/** append data to the buffer up to the max length
*/
#define ACR_VAR_BUFFER_APPEND(name, srcPtr, length) \
        if(length <= (name.m_MaxLength - name.m_Buffer.m_Length)) \
        { \
             if(srcPtr != ACR_NULL) \
             { \
                 ACR_MEMCPY(((ACR_Byte_t*)name.m_Buffer.m_Pointer) + name.m_Buffer.m_Length, srcPtr, (size_t)length); \
             } \
             name.m_Buffer.m_Length += length; \
        }

/** determine if the variable length buffer is valid
*/
#define ACR_VAR_BUFFER_IS_VALID(name) ((name.m_Buffer.m_Pointer != ACR_NULL) && (name.m_MaxLength > 0))

/** assign memory to the buffer
*/
#define ACR_VAR_BUFFER_REFERENCE(name, memory, length) \
        if(name.m_Buffer.m_Pointer != ACR_NULL) \
        { \
            if(ACR_HAS_FLAG(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE) \
            { \
                free(name.m_Buffer.m_Pointer); \
            } \
        } \
        name.m_Buffer.m_Pointer = (void*)memory; \
        name.m_Buffer.m_Length = ACR_ZERO_LENGTH; \
        if(name.m_Buffer.m_Pointer != ACR_NULL) \
        { \
            name.m_MaxLength = length; \
            ACR_ADD_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF); \
        } \
        else \
		{ \
		    name.m_MaxLength = ACR_ZERO_LENGTH; \
            ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF); \
        }

#if ACR_HAS_MALLOC == ACR_BOOL_TRUE

/** free memory used by the buffer
*/
#define ACR_VAR_BUFFER_FREE(name) \
        if(name.m_Buffer.m_Pointer != ACR_NULL) \
        { \
            if(ACR_HAS_FLAG(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE) \
            { \
                free(name.m_Buffer.m_Pointer); \
            } \
            name.m_Buffer.m_Pointer = ACR_NULL; \
        } \
        name.m_Buffer.m_Length = ACR_ZERO_LENGTH; \
        name.m_MaxLength = ACR_ZERO_LENGTH; \
        ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF);

/** allocate memory for the buffer only if needed
*/
#define ACR_VAR_BUFFER_ALLOC(name, length) \
        if(name.m_MaxLength < length) \
		{ \
			if(name.m_Buffer.m_Pointer != ACR_NULL) \
			{ \
				if(ACR_HAS_FLAG(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF) == ACR_BOOL_FALSE) \
				{ \
					free(name.m_Buffer.m_Pointer); \
				} \
			} \
			name.m_Buffer.m_Pointer = (void*)malloc((size_t)(length+1)); \
			if(name.m_Buffer.m_Pointer != ACR_NULL) \
			{ \
                ((ACR_Byte_t*)name.m_Buffer.m_Pointer)[length] = 0; \
				name.m_MaxLength = length; \
			} \
			else \
			{ \
				name.m_MaxLength = ACR_ZERO_LENGTH; \
			} \
		    ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF); \
		} \
		name.m_Buffer.m_Length = ACR_ZERO_LENGTH;

#else

/** free is not available
*/
#define  ACR_VAR_BUFFER_FREE(name) name.m_Buffer.m_Pointer = ACR_NULL; name.m_Buffer.m_Length = ACR_ZERO_LENGTH; name.m_MaxLength = ACR_ZERO_LENGTH; ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF);

/** malloc is not available
*/
#define  ACR_VAR_BUFFER_ALLOC(name, length) name.m_Buffer.m_Pointer = ACR_NULL; name.m_Buffer.m_Length = ACR_ZERO_LENGTH; name.m_MaxLength = ACR_ZERO_LENGTH; ACR_REMOVE_FLAGS(name.m_Buffer.m_Flags, ACR_BUFFER_IS_REF);

#endif // #if ACR_HAS_MALLOC == ACR_BOOL_TRUE

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - ALIGNED MEMORY BUFFER
//
////////////////////////////////////////////////////////////

/** type for reference to ACR_Block_t aligned memory area
	- prevents use of malloc and free directly.
	- prevents use of void pointers without associated memory length
	- include "ACR/alignedbuffer.h" for easy and safe functions
	- see ACR_ALIGNED_BUFFER defines for safe access via macros
*/
typedef struct ACR_AlignedBuffer_s
{
	/** the aligned memory buffer
	*/
	ACR_Buffer_t m_AlignedBuffer;

	/** stores the original memory before alignement
	*/
	ACR_Buffer_t m_UnalignedBuffer;

} ACR_AlignedBuffer_t;

/** define an empty aligned buffer on the stack with the specified name
*/
#define ACR_ALIGNED_BUFFER(name) ACR_AlignedBuffer_t name = {{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE},{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE}};

/** check if the aligned buffer is valid
*/
#define ACR_ALIGNED_BUFFER_IS_VALID(name) ACR_BUFFER_IS_VALID(name.m_AlignedBuffer)

/** assign memory to the buffer aligned on a block boundary

    Note: the buffer length available may be up to 1 full block less than the length specified.
	      use ACR_ALIGNED_BUFFER_GET_LENGTH to get the actual length available
*/
#define ACR_ALIGNED_BUFFER_REFERENCE(name, memory, length) \
        { \
			ACR_BUFFER_REFERENCE(name.m_UnalignedBuffer, memory, length); \
			if((name.m_UnalignedBuffer.m_Pointer != ACR_NULL) && (name.m_UnalignedBuffer.m_Length >= ACR_BYTES_PER_BLOCK)) \
			{ \
				ACR_PointerValue_t alignMask = (~(ACR_BITS_PER_BLOCK-1)); \
				ACR_PointerValue_t memValue = (ACR_PointerValue_t)memory; \
				memValue += (ACR_BITS_PER_BLOCK-1); \
				memValue &= alignMask; \
				name.m_AlignedBuffer.m_Pointer = (void*)memValue; \
				name.m_AlignedBuffer.m_Length = (length - (ACR_Length_t)((ACR_PointerValue_t)name.m_AlignedBuffer.m_Pointer - (ACR_PointerValue_t)memory)); \
				ACR_ADD_FLAGS(name.m_AlignedBuffer.m_Flags, ACR_BUFFER_IS_REF); \
			} \
			else \
			{ \
				name.m_AlignedBuffer.m_Pointer = ACR_NULL; \
				name.m_AlignedBuffer.m_Length = ACR_ZERO_LENGTH; \
				ACR_REMOVE_FLAGS(name.m_AlignedBuffer.m_Flags, ACR_BUFFER_IS_REF); \
			} \
        }

/** free memory used by the buffer
*/
#define ACR_ALIGNED_BUFFER_FREE(name) \
        ACR_BUFFER_FREE(name.m_UnalignedBuffer); \
		name.m_AlignedBuffer.m_Pointer = ACR_NULL; \
		name.m_AlignedBuffer.m_Length = ACR_ZERO_LENGTH; \
        ACR_REMOVE_FLAGS(name.m_AlignedBuffer.m_Flags, ACR_BUFFER_IS_REF);

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
// TYPES AND DEFINES - MATH
//
////////////////////////////////////////////////////////////

/** the value of pie
*/
#define ACR_PI 3.14159265359

/** the circumference of a circle with the specified radius
*/
#define ACR_CIRCUMFERENCE(radius) (2*ACR_PI*radius)

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

#ifdef ACR_COMPILER_VS2017
#pragma warning(push)
// disable warning C4820: padding added after data member
#pragma warning(disable:4820)
#endif
/** type for string data
*/
typedef struct ACR_String_s
{
    ACR_Buffer_t m_Buffer;
    ACR_Count_t m_Count;
} ACR_String_t;
#ifdef ACR_COMPILER_VS2017
#pragma warning(pop)
#endif

/** define a string on the stack with the specified name
*/
#define ACR_STRING(name) ACR_String_t name = {{ACR_NULL,ACR_ZERO_LENGTH,ACR_BUFFER_FLAGS_NONE},ACR_ZERO_COUNT};

/** assign memory to the string
*/
#define ACR_STRING_REFERENCE(name, memory, length, count) ACR_BUFFER_REFERENCE(name.m_Buffer, memory, length); name.m_Count = count;

/** type for unicode characters
*/
typedef unsigned long ACR_Unicode_t;

/** given the first UTF8 byte value determine the number of
    bytes uses to encode the character
*/
#define ACR_UTF8_BYTE_COUNT(c) (((c & 0x80) != 0)?((c & 0x40) != 0)?((c & 0x20) != 0)?((c & 0x10) != 0)?4:3:2:1:1)

/////////////////////////////////////////////////////////
//                                                     //
// TYPES AND DEFINES - UNITS OF MEASURE                //
//                                                     //
/////////////////////////////////////////////////////////

#define ACR_DEGREES_C_TO_F(c) ((c*1.8)+32.0)
#define ACR_DEGREES_F_TO_C(f) ((f-32.0)/1.8)
#define ACR_MEASURE_INCHES_TO_CM(i) (i*2.54)
#define ACR_MEASURE_CM_TO_INCHES(cm) (cm/2.54)

/////////////////////////////////////////////////////////
//                                                     //
// TYPES AND DEFINES - UNIQUE STRING VALUES            //
//                                                     //
/////////////////////////////////////////////////////////
#include "ACR/public_unique_strings.h"

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
extern "C" {                                              //
#endif                                                    //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
// Note: warning C4711: function selected for automatic inline expansion can be
//       ignored in project settings to avoid unnecessary warnings for these function
//
////////////////////////////////////////////////////////////

/** internal test of ACR library functions
    \returns ACR_SUCCESS or ACR_FAILURE
*/
int ACR_Test(void);

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

/** get the number of days in the specified month
    \param month the month
           \see enum ACR_Month_e
    \param isLeapYear set to ACR_BOOL_TRUE to get leap year days (only affects February)
           \see ACR_YearIsLeapYear()
    \returns the number of days in the month
*/
int ACR_DaysPerMonth(
    ACR_Month_t month,
    ACR_Bool_t isLeapYear);

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

/** \param fourDigitYear any four digit year
    \returns ACR_BOOL_TRUE if the year is a leap year
*/
ACR_Bool_t ACR_YearIsLeapYear(
    int fourDigitYear);

/** set the time to the current system time
    \param me the time
    \returns ACR_BOOL_TRUE if successful
*/
ACR_Bool_t ACR_TimeNow(
    ACR_Time_t* me);

/** attempt to set the RTC to the specified time
    \param me the time to set the RTC to
    \returns ACR_BOOL_TRUE if successful
*/
ACR_Bool_t ACR_TimeSet(
    ACR_Time_t* me);

/** when there is no RTC, call this function
    once per second (or as close as possible)
    to simulate the time
    \param seconds the number of seconds since the last call to this function (typically 1 is desired)
*/
void ACR_TimeProcessSecondTick(
    ACR_Time_t seconds);

/** where there is no RTC, call this function
    once per millisecond (or as close as possible)
    to simulate the time
    \param milliseconds the number of milliseconds since the last call to this function (typically 10 or less is desired)
*/
void ACR_TimeProcessMilliTick(
    ACR_Time_t milliseconds);

/** set the date time data from the specified time
    \param me the date time
    \param time the time
    \returns ACR_BOOL_TRUE if successful
*/
ACR_Bool_t ACR_DateTimeFromTime(
    ACR_DateTime_t* me,
    ACR_Time_t* time);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - SIMPLE UTF8 STRINGS
//                    AND UNICODE CHARACTERS
//
////////////////////////////////////////////////////////////

/** selects the position of the next character
  \param mem the start of the UTF8 encoded string data
  \param memLength the length of mem (use ACR_MAX_LENGTH if unsure)
  \param pos current byte offset into the string, which
         will be updated to that of the next character if
         successful
  \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_Utf8NextChar(
        const ACR_Byte_t* mem,
        ACR_Length_t memLength,
        ACR_Length_t* pos);

/** selects the position of the previous character
  \param mem start of the UTF8 encoded string data
  \param memLength the length of mem (use ACR_MAX_LENGTH if unsure)
  \param pos current byte offset in the string, which will
         be updated to that of the previous character if
         successful
  \returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_Utf8PrevChar(
        const ACR_Byte_t* mem,
        ACR_Length_t memLength,
        ACR_Length_t* pos);

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
    const ACR_Byte_t* mem,
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
    ACR_Byte_t* src,
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
    const ACR_Byte_t* src,
    ACR_Length_t srcLength,
    ACR_Count_t maxCharacters,
    ACR_Info_t caseSensitive);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - OTHER
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
