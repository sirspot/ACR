/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2021 Adam C. Rosenberg

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
 
    This header contains many common defines, enums, functions, and typedefs.
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

    ### Preprocessor Defines For Confguration Options ###

    Hopefully you are able to use one of the development environments
    that have been preconfigured such as Gitpod, Visual Studio, or Qt Creator.
    These platforms are described by this header in detail in the
    "TYPES AND DEFINES - PLATFORM AND COMPILER" section.

    For additional control over the configuration or if using an
    alternate development environment, the following are the most
    useful options to define in your preprocessor flags.

    ACR_DEBUG           include debug tools.
                        see "TYPES AND DEFINES - DEBUG" for details.

    ACR_NO_MALLOC       do not include malloc() or free() and disables
                        ACR_MALLOC and ACR_FREE macros.
                        see "TYPES AND DEFINES - MALLOC" for details.

    ACR_BIG_ENDIAN      always assume big endian without
                        dynamically checking the system
                        endianess.
                        see "TYPES AND DEFINES - ENDIANNESS" for details.

    ACR_LITTLE_ENDIAN   always assume little endian without
                        dynamically checking the system
                        endianess.
                        see "TYPES AND DEFINES - ENDIANNESS" for details.

    ACR_NO_RTC          do not include <time.h> for time_t, struct tm,
                        time(), and gmtime_s() or gmtime_r()
                        Note: this never completely disables support
                              for times and dates but does limit it.
                        see "TYPES AND DEFINES - REAL TIME CLOCK" for details.

    ACR_NO_64BIT        do not use types of long long
                        Note: only use this setting if you know that your
                              compiler does not support 64bit values
                              so that 32bit values will be used as the
                              largest integer and pointer size instead.
                        see "TYPES AND DEFINES - MEMORY LENGTHS" for details.

    ACR_NO_LIBC         do not include any headers from the system
                        including but not limited to <stdlib.h>,
                        <string.h>, and <time.h>. when ACR_DEBUG is
                        defined there may be some system headers
                        included only to allow the debug featues.
                        Note: features provided by these headers will
                              attempt to be made available but may
                              be limited or require additional user
                              setup to be functional.
                              each section may use this define to prevent
                              system headers from being included and will
                              provide additional details upon use.

    ### Top Uses ###

    ACR_DEBUG_PRINT     interface to printf() that only
                        writes messages to stdout
                        when ACR_DEBUG is defined.
                        see "TYPES AND DEFINES - DEBUG" for details.

    ACR_BYTE_ORDER_16   ensures a value is stored
    ACR_BYTE_ORDER_32   in big endian byte order
    ACR_BYTE_ORDER_64   see "TYPES AND DEFINES - ENDIANNESS" for details.

    ACR_Buffer_t        a simple struct with macros
                        to handle allocation and freeing
                        of memory safely.
                        see "TYPES AND DEFINES - SIMPLE MEMORY BUFFER" for details.
                        for ease of use see "ACR/buffer.h"

    ACR_VarBuffer_t     a simple struct with macros to 
                        handle allocation of memory
                        safely while freeing memory only
                        when necessary to grow the
                        memory area.
                        see "TYPES AND DEFINES - VARIABLE LENGTH MEMORY BUFFER" for details.
                        for ease of use see "ACR/varbuffer.h"

    ACR_String_t        a struct for access to strings
                        with support for UTF8 encoding.
                        see "TYPES AND DEFINES - SIMPLE UTF8 STRINGS AND UNICODE CHARACTERS" for details.
                        for ease of use see "ACR/string.h"

    ACR_DECIMAL_COMPARE compare decimal values within a
                        default tolerance of 0.0001 which
                        is many cases is safer than performing
                        a direct if(a==b) type of comparison
                        because of possible rounding.
                        see "TYPES AND DEFINES - DECIMAL VALUES" for details.

*/
#ifndef _ACR_PUBLIC_H_
#define _ACR_PUBLIC_H_

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - BOOLEAN (TRUE/FALSE) AND EMPTY VALUES
//
////////////////////////////////////////////////////////////

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

    ### New to C? ###

    Q: What is a boolean?
    A: A boolean is a "true" or "false" value. In C, a value
       of 0 is "false" and all other values are "true".
       A confusing thing about C is that some functions will
       return 0 to mean success while others will return 0
       as an error. This is why ACR defines many more specific
       values that can be used as return codes.

*/
#define ACR_BOOL_FALSE 0

/** represents a true boolean result

    example:

        if(ACR_BOOL_TRUE)
        {
            // always reaches this code
        }
        else
        {
            // never reaches this code
        }

*/
#define ACR_BOOL_TRUE 1

/** use this type only for ACR_BOOL_FALSE or ACR_BOOL_TRUE
*/
typedef char ACR_Bool_t;

/** represents an empty value.
    use this instead of 0 to clearly indicate the value
    is being used to identify an empty value

    for memory init:

        char data[64];
        ACR_MEMSET(data, ACR_EMPTY_VALUE, sizeof(data));
        
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

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - PLATFORM AND COMPILER
//
////////////////////////////////////////////////////////////

/* The following preprocessor defines can be used to
   automatically select the correct features for your
   development environment

   ACR_PLATFORM_MAC
       ACR_IDE_XCODE
           ACR_COMPILER_CLANG
       ACR_IDE_QTCREATOR
           ACR_COMPILER_CLANG

   ACR_PLATFORM_WIN
        ACR_IDE_QTCREATOR
            ACR_COMPILER_MINGW
            ACR_COMPILER_MSVC
      ACR_IDE_VS2017
            ACR_COMPILER_MSVC

    ACR_PLATFORM_GITPOD
        ACR_IDE_THEIA
            ACR_COMPILER_GCC

    ### New to C? ###

    Q: Why are there so many different platform settings?
    A: To allow ACR to be used with as many different types
       of projects as possible. These platform defines provide
       support for Windows, Mac OS X, Linux, or even an embedded
       microprocessor with no operating system. Code is removed or
       added based on the platform settings using the preprocessor
       commands #ifdef and #ifndef.

*/

/** MAC OS X
*/
#ifdef ACR_PLATFORM_MAC

    #define ACR_HAS_PLATFORM ACR_BOOL_TRUE
    #define ACR_PLATFORM_NAME "mac"
    #ifdef ACR_IDE_QTCREATOR
        #define ACR_HAS_IDE ACR_BOOL_TRUE
        #define ACR_IDE_NAME "qt_creator"
        #ifdef ACR_COMPILER_CLANG
            #define ACR_HAS_COMPILER ACR_BOOL_TRUE
            #define ACR_COMPILER_NAME "clang"
        #endif // ACR_COMPILER_CLANG
    #endif // ACR_IDE_QTCREATOR
    #ifdef ACR_IDE_XCODE
        #define ACR_HAS_IDE ACR_BOOL_TRUE
        #define ACR_IDE_NAME "xcode"
        #ifdef ACR_COMPILER_CLANG
            #define ACR_HAS_COMPILER ACR_BOOL_TRUE
            #define ACR_COMPILER_NAME "clang"
        #endif // ACR_COMPILER_CLANG
    #endif // ACR_IDE_XCODE

#endif // ACR_PLATFORM_MAC

/** WINDOWS
*/
#ifdef ACR_PLATFORM_WIN

    #define ACR_HAS_PLATFORM ACR_BOOL_TRUE
    #define ACR_PLATFORM_NAME "win64"
    #ifdef ACR_IDE_QTCREATOR
        #define ACR_HAS_IDE ACR_BOOL_TRUE
        #define ACR_IDE_NAME "qt_creator"
        #ifdef ACR_COMPILER_MINGW
            #define ACR_HAS_COMPILER ACR_BOOL_TRUE
            #define ACR_COMPILER_NAME "mingw"
        #endif // ACR_COMPILER_MINGW
        #ifdef ACR_COMPILER_MSVC
            #define ACR_HAS_COMPILER ACR_BOOL_TRUE
            #define ACR_COMPILER_NAME "msvc"
        #endif // ACR_COMPILER_MSVC
    #endif // ACR_IDE_QTCREATOR
    #ifdef ACR_IDE_VS2017
        #define ACR_HAS_IDE ACR_BOOL_TRUE
        #define ACR_IDE_NAME "vs2017"
        #ifdef ACR_COMPILER_MSVC
            #define ACR_HAS_COMPILER ACR_BOOL_TRUE
            #define ACR_COMPILER_NAME "msvc"
        #endif // ACR_COMPILER_MSVC
    #endif // ACR_IDE_VS2017

#endif // ACR_PLATFORM_WIN

/** GITPOD (LINUX)
*/
#ifdef ACR_PLATFORM_GITPOD

        #define ACR_HAS_PLATFORM ACR_BOOL_TRUE
        #define ACR_PLATFORM_NAME "gitpod"
        #define ACR_HAS_IDE ACR_BOOL_TRUE
        #define ACR_IDE_THEIA
        #define ACR_IDE_NAME "theia"
        #define ACR_HAS_COMPILER ACR_BOOL_TRUE
        #define ACR_COMPILER_GCC
        #define ACR_COMPILER_NAME "gcc"

#endif // ACR_PLATFORM_GITPOD

#ifndef ACR_HAS_PLATFORM

    #define ACR_PLATFORM_UNKNOWN
    #define ACR_HAS_PLATFORM ACR_BOOL_FALSE
    #define ACR_PLATFORM_NAME "unknown"

#endif // #ifndef ACR_HAS_PLATFORM

#ifndef ACR_HAS_COMPILER

    #define ACR_COMPILER_UNKNOWN
    #define ACR_HAS_COMPILER ACR_BOOL_FALSE
    #define ACR_COMPILER_NAME "unknown"

#endif // #ifndef ACR_HAS_COMPILER

#ifndef ACR_HAS_IDE

    #define ACR_IDE_UNKNOWN
    #define ACR_HAS_IDE ACR_BOOL_FALSE
    #define ACR_IDE_NAME "unknown"

#endif // #ifndef ACR_HAS_IDE

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SYSTEM LEVEL
//
////////////////////////////////////////////////////////////

#ifndef ACR_NO_LIBC

    // included for memset()
    #include <string.h>
    #define ACR_MEMSET(p,v,s) memset(p,v,s)

    /*
        ### New to C? ###

        Q: What does memset do?
        A: memset is a function that changes an entire
           area of memory to be a single value. It is
           typically used to set a region of memory
           that has unknown or undesired values to all
           zeros so that the values of all memory in
           that region are known and valid.

    */

#else

    /** ACR_NO_LIBC is defined so this is a 
        generic (slow) memset but gets the job done
    */
    #define ACR_MEMSET(p,v,s) \
    {\
        char* pc=(char*)p;\
        size_t sz=(size_t)s;\
        while(sz>0)\
        {\
            sz--;\
            pc[sz]=(char)v;\
        }\
    }

#endif // #ifndef ACR_NO_LIBC

/** clears a region of memory
    \param p a pointer to the memory to clear
    \param s the number of bytes of data to clear
*/
#define ACR_CLEAR_MEMORY(p,s) if(p){ACR_MEMSET(p,ACR_EMPTY_VALUE,s);}

/** defines a callback function type
    \param t the name of the type to define
    \param r the return type or void if there is none
  
    ### New to C? ###

        Q: What is a callback function?
        A: A callback function is a variable
           that can act as the function it is
           assigned to.

	example:

        // define a list of all callback names
        enum CallbackExample_e
        {
            CBEX_1 = 0,
            CBEX_2,
            CBEX_3,

            CBEX_COUNT
        };

        // define the callback function prototypes
        ACR_TYPEDEF_CALLBACK(CallbackExample_t, void)(int, void*);
            void CbEx1(int,void*);
            void CbEx2(int,void*);
            void CbEx3(int,void*);

        // create a lookup table of the callback functions
        CallbackExample_t g_CbEx[CBEX_COUNT+1] = 
        {
            CbEx1, // CBEX_1
            CbEx2, // CBEX_2
            CbEx3, // CBEX_3

            ACR_NULL
        };

        int main()
        {
            unsigned int cbIndex;

            // just use one callback function
            g_CbEx[CBEX_1](0, ACR_NULL);

            // loop through all callback functions
            cbIndex = 0;
            while(cbIndex < CBEX_COUNT)
            {
                g_CbEx[cbIndex](cbIndex, ACR_NULL);
            }

            return ACR_SUCCESS;
        }

        // complete the definition of the first callback function
        void CbEx1(int a, void* b)
        {
            ACR_UNUSED(a);
            ACR_UNUSED(b);
            ACR_DEBUG_PRINT(1,"One");
        }

        // complete the definition of the second callback function
        void CbEx2(int a, void* b)
        {
            ACR_UNUSED(a);
            ACR_UNUSED(b);
            ACR_DEBUG_PRINT(2,"Two");
        }
        
        // complete the definition of the third callback function
        void CbEx3(int a, void* b)
        {
            ACR_UNUSED(a);
            ACR_UNUSED(b);
            ACR_DEBUG_PRINT(3,"Three");
        }

*/
#define ACR_TYPEDEF_CALLBACK(t,r) typedef r (*t)

/** represents a successful program or thread execution

	example:

	int main()
	{
		return ACR_SUCCESS;
	}
*/
#define ACR_SUCCESS 0

/** represents a failed program or thread execution

	example:

	int main()
	{
		return ACR_FAILURE;
	}
*/
#define ACR_FAILURE -1

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

    ### New to C? ###

    Q: What is a pointer?
    A: A pointer is a variable except
       that the value of the variable
       is a memory address.

    Q: What is a null pointer?
    A: A null pointer is a pointer variable with
       value 0. Memory address 0 is invalid
       and if an attempt to access the memory is made
       by a null pointer it will cause the program to crash.
       This is why it is important to always check
       if a pointer is null before using it.

    Q: What is a SEGFAULT or Segmentation fault?
    A: This occurs when attempting to access memory that
       does not belong to your program. In almost all cases
       this will cause your program to crash. The most common
       SEGFAULT is caused by trying to access a null pointer.

*/
#ifdef __cplusplus
#define ACR_NULL nullptr
#endif

#ifndef ACR_NULL
#define ACR_NULL 0
#endif

/** explicitly states that a variable or parameter is not used

    ### New to C? ###

    Q: Why would a variable or parameter exist that is not used?
    A: There are many reasons to not use a variable or parameter
       when it has already been defined. One example is a callback
       function that doesn't need to use all of the parameters.

*/
#define ACR_UNUSED(arg) (void)arg

/** defines ACR_USE_64BIT
    see TYPES AND DEFINES - MEMORY LENGTHS for more details

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
 
*/
#ifdef ACR_NO_64BIT
#define ACR_USE_64BIT ACR_BOOL_FALSE
#else
/// \todo is there a way to determine, at compile time, whether or not the platform uses 64bit addresses?
#define ACR_USE_64BIT ACR_BOOL_TRUE
#endif // #ifndef ACR_NO_64BIT

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
#ifdef ACR_DEBUG
#define ACR_IS_DEBUG ACR_BOOL_TRUE
#ifdef ACR_COMPILER_VS2017
#pragma warning(push)
// disable warning C4710: 'int printf(const char *const ,...)': function not inlined (when it was requested)
#pragma warning(disable:4710)
#endif
// included for printf
// Note: this ignores ACR_NO_LIBC intentionally for debug only
#include <stdio.h>
#ifdef ACR_COMPILER_VS2017
#pragma warning(pop)
#endif
#define ACR_DEBUG_PRINT(number, format, ...) printf("%4d "format"\n", number, ##__VA_ARGS__)
#else
#define ACR_IS_DEBUG ACR_BOOL_FALSE
#define ACR_DEBUG_PRINT(number, format, ...)
#endif // #ifdef ACR_DEBUG

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MALLOC
//
////////////////////////////////////////////////////////////

#ifndef ACR_NO_MALLOC

    #ifndef ACR_NO_LIBC
        /** defined when malloc is available
            Note: to remove malloc from this library define
                  ACR_NO_LIBC in your preprocessor
        */
        #define ACR_HAS_MALLOC ACR_BOOL_TRUE
        // included for malloc and free
        #include <stdlib.h>
        #define ACR_MALLOC(s) malloc((size_t)s)
        #define ACR_FREE(p) free(p);
    #else
        // ACR_BOOL_TRUE
        #define ACR_HAS_MALLOC ACR_BOOL_FALSE
        /// \todo create a simple built-in malloc
        #define ACR_MALLOC(s) ACR_NULL
        /// \todo create a simple built-in free
        #define ACR_FREE(p) 
    #endif // #ifndef ACR_NO_LIBC
#else
    #define ACR_HAS_MALLOC ACR_BOOL_FALSE
    #define ACR_MALLOC(s) ACR_NULL
    #define ACR_FREE(p)
#endif // #ifndef ACR_NO_MALLOC

/** similar to malloc but automatically defines the variable and clears the memory
 
    example:

        int main()
        {
            ACR_NEW_BY_SIZE(oneHundredNumbers, int, sizeof(int)*100);

            oneHundredNumbers[0] = 42;
            oneHundredNumbers[1] = 3000;
            // etc
        }
*/
#define ACR_NEW_BY_SIZE(n, t, s) t* n = (t*)ACR_MALLOC(s);ACR_CLEAR_MEMORY(n,s);

/** similar to malloc but automatically defines the variable and clears the memory
 
    example:

        int main()
        {
            ACR_NEW_BY_TYPE(oneDateTime, ACR_DateTime_t);

            oneDateTime->tm_sec = 30;
            oneDateTime->tm_min = 1;
            // etc
        }
*/
#define ACR_NEW_BY_TYPE(n, t) ACR_NEW_BY_SIZE(n,t,sizeof(t));

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - ENDIANNESS
//
// ### New to C? ###
//
// Even experienced programmers sometimes forget about
// endianess. Read the following details to help understand
// what endianess means and how it changes the way data
// is stored in memory
//
// Q: What is MSB and LSB?
// A: The Most Significant Bit/Byte (MSB) is the bit or byte
//    that changes the value of an integer by the greatest amount.
//    The Least Significant Bit/Byte (LSB) is the bit or byte
//    that changes the value of an integer by the smallest amount.
//    See the Sample Memory illustrations below for details.
//
// Note: Big Endian means that multibyte values have the
//       bytes stored in memory from least significant 
//       to most significant. Little Endian is the opposite.
//
// ### Sample Memory ###
//
//   type/bytes   illustration
//
//   char/1       memory = [ 0x01 ---- ---- ---- ]
//                binary little endian =
//                    MSB -------- -------- -------- 00000001 LSB
//                decimal little endian = 1
//                decimal big endian = 1
//
//   short/2      memory = [ 0x01 0x00 ---- ---- ]
//                binary little endian = 
//                    MSB -------- -------- 00000001 00000000 LSB
//                decimal little endian = 256
//                decimal big endian = 1
//
//   short/2      memory = [ 0x00 0x01 ---- ---- ]
//                binary little endian = 
//                    MSB -------- -------- 00000000 00000001 LSB
//                decimal little endian = 1
//                decimal big endian = 256
//
//   long/4       memory = [ 0x00 0x01 0x00 0x00 ]
//                binary little endian = 
//                    MSB 00000000 00000001 00000000 00000000 LSB
//                decimal little endian = 65536
//                decimal big endian = 256
//
// "long" Example:
//
//      // given a local variable with value 1
//      long valueInSystemEndian = 1;
//      // convert the value to big endian 
//      long valueInBigEndian = ACR_BYTE_ORDER_32(valueInSystemEndian);
//      // and use the same macro to convert
//      // a big endian value back to system endianness
//      valueInSystemEndian = ACR_BYTE_ORDER_32(valueInBigEndian);
//
// "short" example
//
//      // given a value known to be in big endian
//      short valueInBigEndian = 1;
//      // convert the value to system endian
//      short valueInSystemEndian = ACR_BYTE_ORDER_16(valueInBigEndian);
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

#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

//
// defines ACR_IS_BIG_ENDIAN as ACR_BOOL_TRUE or
// ACR_BOOL_FALSE
//
// Optional: If you already know the endianess of your
//           system then set the preprocessor define as
//           follows to improve byte order handling
//           performance.
//           Big Endian:    ACR_BIG_ENDIAN
//           Little Endian: ACR_LITTLE_ENDIAN
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
// Note: warning C4906: string literal cast to 'unsigned short *' must be
//       ignored in project settings to use dynamic endianess detection
#define ACR_IS_BIG_ENDIAN (*(unsigned short *)"\0\xff" < 0x100)
#define ACR_ENDIAN_DYNAMIC ACR_BOOL_TRUE
#endif // #ifdef LITTLE_ENDIAN
#endif // #ifdef BIG_ENDIAN
#endif // #ifndef ACR_IS_BIG_ENDIAN

//
// defines ACR_BYTE_ORDER_16 and ACR_BYTE_ORDER_32 and ACR_BYTE_ORDER_64
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
#include "ACR/public_bytes_and_flags.h"

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MEMORY LENGTHS
//
////////////////////////////////////////////////////////////

/** type for a typical length such as the size of a file or
    the size of an area of memory
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

		ACR_Length_t length = ACR_ZERO_LENGTH;

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

/** the value of a pointer (used for pointer math)
    can always be stored within the ACR_Length_t type
	but for clarity it is best to use a type that
	specifically designates the use as a pointer's value
*/
typedef ACR_Length_t ACR_PointerValue_t;

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - COUNTING
//
////////////////////////////////////////////////////////////

/** type for a typical count such as the number of items
	in an array or blocks of memory
	\see ACR_MAX_COUNT for the maximum value that can be
	stored by this data type
*/
typedef unsigned long ACR_Count_t;

/** used for setting a count explicitly to zero
*/
#define ACR_ZERO_COUNT 0

/** max value that can be stored by the ACR_Count_t type such that it will not overflow when added to 1 (this allows ACR_MAX_COUNT+1 to be greater than ACR_ZERO_COUNT)
*/
#define ACR_MAX_COUNT 4294967294UL // hex value ‭0xFFFFFFFE‬

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - MEMORY BLOCKS
//
////////////////////////////////////////////////////////////

/** type for an effeciently sized memory block, which is
    probably the largest integer value type
	\see ACR_MAX_BLOCK for the maximum value that can be
	stored by this data type
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
typedef unsigned long long ACR_Block_t;
#else
// 32bit
typedef unsigned long ACR_Block_t;
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

/** max value that can be stored by the ACR_Block_t type
*/
#if ACR_USE_64BIT == ACR_BOOL_TRUE
// 64bit
#define ACR_MAX_BLOCK 18446744073709551615ULL // hex value 0xFFFFFFFFFFFFFFFF
#else
// 32bit
#define ACR_MAX_BLOCK 4294967295UL // hex value 0xFFFFFFFF
#endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

/** number of bytes in ACR_Block_t
*/
#define ACR_BYTES_PER_BLOCK sizeof(ACR_Block_t)

/** number of bits in ACR_Block_t
*/
#define ACR_BITS_PER_BLOCK (ACR_BYTES_PER_BLOCK * ACR_BITS_PER_BYTE)

/** get the minimum number of blocks needed for the specified memory length.
    to get a more accurate number of blocks and bytes use ACR_LENGTH_TO_BLOCKS
*/
#define ACR_MIN_BLOCKS_NEEDED(length) ((ACR_Count_t)((length / ACR_BYTES_PER_BLOCK) + ((length % ACR_BYTES_PER_BLOCK) != 0)))

/** type that stores the number of full blocks and remaining bytes
*/
typedef struct ACR_Blocks_s
{
	ACR_Count_t m_Blocks;
	ACR_Count_t m_Bytes;
} ACR_Blocks_t;

/** converts a length to ACR_Blocks_t data to provide the
    exact number of blocks and bytes needed for the memory length
*/
#define ACR_LENGTH_TO_BLOCKS(blocks, length) { blocks.m_Blocks = (length / ACR_BYTES_PER_BLOCK); blocks.m_Bytes = (length % ACR_BYTES_PER_BLOCK); }

#ifndef ACR_NO_LIBC

    // included for memcpy()
    #include <string.h>
    #define ACR_MEMCPY(d,s,l) memcpy(d,s,l);

    /*
        ### New to C? ###

        Q: What does memcpy do?
        A: memcpy is a function that copies memory from
           one address to another. It is generally best
           to avoid copying memory unless necessary since
           it can be a relatively slow process. What this
           means is that if there is way to work with the
           data without copying it first, then that is
           preferred over making a copy.

    */

#else

    /** ACR_NO_LIBC is defined so this is a 
        generic (slow) memcpy but gets the job done
    */
    #define ACR_MEMCPY(d,s,l) \
    {\
        char* pd=(char*)d;\
        char* ps=(char*)s;\
        size_t ln=(size_t)l;\
        while(ln>0)\
        {\
            ln--;\
            pd[ln]=ps[ln];\
        }\
    }


#endif // #ifndef ACR_NO_LIBC

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - FLAGS
//
////////////////////////////////////////////////////////////
#include "ACR/public_bytes_and_flags.h"

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

// defines ACR_HAS_RTC and includes time()
// functions if desired
#ifndef ACR_NO_RTC
    #ifndef ACR_NO_LIBC
        #ifdef ACR_COMPILER_CLANG
            #include <time.h>
            #define ACR_HAS_RTC ACR_BOOL_TRUE
            #define ACR_TIME_NOW(name) time(&name)
            #define ACR_DATETIME_FROM_TIME(name,time) gmtime_r(&time,&name)
        #endif
        #ifdef ACR_COMPILER_GCC
            #include <time.h>
            #define ACR_HAS_RTC ACR_BOOL_TRUE
            #define ACR_TIME_NOW(name) time(&name)
            #define ACR_DATETIME_FROM_TIME(name,time) gmtime_r(&time,&name)
        #endif
        #ifdef ACR_COMPILER_VS2017
            #pragma warning(push)
            // disable warning C4820: '_timespec64': '4' bytes padding added after data member 'tv_nsec'
            #pragma warning(disable:4820)
            #include <time.h>
            #pragma warning(pop)
            #define ACR_HAS_RTC ACR_BOOL_TRUE
            #define ACR_TIME_NOW(name) time(&name)
            #define ACR_DATETIME_FROM_TIME(name,time) gmtime_s(&name,&time)
        #endif
    #endif // #ifndef ACR_NO_LIBC
#endif // #ifndef ACR_NO_RTC

#ifndef ACR_HAS_RTC
    #define ACR_HAS_RTC ACR_BOOL_FALSE
#endif // #ifndef ACR_HAS_RTC

#if ACR_HAS_RTC == ACR_BOOL_TRUE

    /** time value (seconds since unix epoch Jan 1, 1970)
    */
    typedef time_t ACR_Time_t;

    /** standard date time structure
    */
    typedef struct tm ACR_DateTime_t;

#else

    /** time value (seconds since unix epoch Jan 1, 1970)
    */
    #if ACR_USE_64BIT == ACR_BOOL_TRUE
        // 64bit
        typedef unsigned long long ACR_Time_t;
    #else
        // 32bit
        typedef unsigned long ACR_Time_t;
    #endif // #if ACR_USE_64BIT == ACR_BOOL_TRUE

    /// \todo support struct for time with seconds and microseconds

    /** standard date time structure
    */
    typedef struct ACR_DateTime_s
    {
        int tm_sec;          /* seconds, range 0 to 59           */
        int tm_min;          /* minutes, range 0 to 59           */
        int tm_hour;         /* hours, range 0 to 23             */
        int tm_mday;         /* day of the month, range 1 to 31  */
        int tm_mon;          /* month, range 0 to 11             */
        int tm_year;         /* The number of years since 1900   */
        int tm_wday;         /* day of the week, range 0 to 6    */
        int tm_yday;         /* day in the year, range 0 to 365  */
        int tm_isdst;        /* daylight saving time             */	
        int tm_gmtoff;		 /* Seconds east of UTC.             */
        const char *tm_zone; /* Timezone abbreviation.           */
    } ACR_DateTime_t;

    #define ACR_TIME_NOW(name) ACR_TimeNow(&name)
    #define ACR_DATETIME_FROM_TIME(name,time) ACR_DateTimeFromTime(&name,&time)

#endif // #if ACR_HAS_RTC == ACR_BOOL_TRUE

/** get the current date and time
    \param name any ACR_DateTime_t variable
*/
#define ACR_DATETIME_NOW(name) {ACR_Time_t temp; ACR_TIME_NOW(temp); ACR_DATETIME_FROM_TIME(name,temp);}

/** values that represent whether in day light savings time or not
    see tm_isdst in ACR_DateTime_t
*/
enum ACR_DST_e
{
    ACR_DST_UNKNOWN = -1,
    ACR_DST_OFF = 0,
    ACR_DST_ON = 1
};

/** define an empty date time on the stack
*/
#define ACR_DATETIME(name) ACR_DateTime_t name = {0};

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

/** ntp time is the number of seconds since Jan 1, 1900.
    this will convert NTP time to UNIX timestamp by subtracting
    seventy years in seconds
*/
#define ACR_TIME_FROM_NTP(ntpTime) (ntpTime - ACR_SEC_FROM_1900_TO_1970)

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - SIMPLE MEMORY BUFFER
//
////////////////////////////////////////////////////////////

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

/** define a buffer using stack memory of the specified size on the stack and with the specified name
*/
#define ACR_BUFFER_USE_DATA(name, data, length) name.m_Pointer = &name_data; name.m_Length = length; name.m_Flags = ACR_BUFFER_IS_REF;

/** determine if the buffer is valid
*/
#define ACR_BUFFER_IS_VALID(name) ((name.m_Pointer != ACR_NULL) && (name.m_Length > 0))

/** get the length of the buffer
*/
#define ACR_BUFFER_GET_LENGTH(name) name.m_Length

/** clear the buffer
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
