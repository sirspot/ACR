[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/sirspot/ACR) 

# The ACR Library in C

Get ready, get set, ...

# Quick start!

## Project Settings
- Add "ACR/include" to your include paths
- Add "ACR/src/common.c" to your project
- Add "ACR/src/test/test_common.c" to your project

## Code
- Add #include "ACR/test/test_common.h" to the top of your C file
- Call the ACR_TestCommon() function as follows:

```C
if(ACR_TestCommon() == ACR_SUCCESS)
{
    // OK, ACR library is ready for use
}
```

# Slower start...

## What is ACR?
**A** set of **C** functions in a git **R**epository

## Mission
To create a C library that makes *easy things* easier and
*hard things* faster for beginners and experts alike.

## Goals
- Great for beginners and experts
- Portable without trying
- Avoids dependencies whenever possible
- Explains everything in great detail; Documented to excess
- Learn what you never knew; Refresh what you always forget
- Fast when it needs to be; Safe when it doesn't
- Use only what you want; Leave the rest behind
- Object-oriented
- Zero unexplained warnings

## Examples

The fastest way to learn how to use the features provided
by this library is to look at the example projects.

For example:
- Open the source file /example/test_varbuffer/test_varbuffer.c
- Find the main() function
- The functions called by main() are ordered from
  simple to advanced. In this case, StackTest() is the
  first function called so it is the most simple function 
  in the test_varbuffer.c example

Note: All of the functions in each example are completely 
      self-contained and can be copied into your own project
      with ease (just don't forget to also grab the #include
      header(s) from the top of the example file)

## Structure

| path        | notes                                                                                |
| ----------- | ------------------------------------------------------------------------------------ |
| ACR/        | contains the entire ACR library code, examples, and projects                         |
| ACR/example | contains example code for each feature of this library                               |
| ACR/include | contains all of the .h header files                                                  |
| ACR/src     | contains all of the .c source files                                                  |
| ACR/vs2017  | contains a Visual Studio 2017 solution and projects for the library and each example |

## Features

- Commonly defined values
  - main() function return codes
  - boolean and pointer values
  - common result codes
  - common math values and functions like PI and Circumference
  - common time values like seconds per day
- Endianess
  - automatic detection
  - byte order swapping
- 64bit memory
  - standardized types
  - max values
- Gregorian calendar
  - days of the week
  - months of year
  - real-time clock support via <time.h>
- Memory buffer and variable length buffer
- Floating point comparisons
- Basic UTF8 string handling and unicode conversion

## Top Uses

    ACR_DEBUG_PRINT     interface to printf() that only
                        writes messages to stdout
                        when ACR_CONFIG_DEBUG is defined.
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

# Acknowledgments

Each file in the library has a place for contributors to
add their name. It's really important to me that this
library is open to best practices and input from the
community. Thank you to everyone who has helped along the way!
