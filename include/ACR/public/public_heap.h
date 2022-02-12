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

/** \file public_heap.h
 
    This header provides access to a memory heap.
    It is included automatically with public.h

    This header gaurantees the following will be defined:
    ACR_HAS_MALLOC     as either ACR_BOOL_TRUE or ACR_BOOL_FALSE
    ACR_MALLOC         as a macro to allocate memory or return ACR_NULL if memory cannot be allocated
    ACR_FREE           as a macro to free previously allocated memory
    ACR_DELETE         as a macro safer version of ACR_FREE
    ACR_HEAP_IS_GLOBAL as either ACR_BOOL_TRUE or ACR_BOOL_FALSE.
                       the only case where this will be set to
                       ACR_BOOL_TRUE is when ACR_CONFIG_NO_LIBC is
                       set but ACR_CONFIG_NO_MALLOC is not set

*/
#ifndef _ACR_PUBLIC_HEAP_H_
#define _ACR_PUBLIC_HEAP_H_

// included for ACR_BOOL_TRUE and ACR_BOOL_FALSE
#include "ACR/public/public_bool.h"

// included for ACR_CLEAR_MEMORY and ACR_NULL
#include "ACR/public/public_memory.h"

#ifndef ACR_CONFIG_NO_MALLOC
    #ifndef ACR_CONFIG_NO_LIBC
        /** defined when malloc is available
            Note: to remove malloc from this library define
                  ACR_CONFIG_NO_LIBC in your preprocessor
        */
        #define ACR_HAS_MALLOC ACR_BOOL_TRUE
        #define ACR_HEAP_IS_GLOBAL ACR_BOOL_FALSE
        // included for malloc and free
        #include <stdlib.h>
        #define ACR_MALLOC(s) malloc((size_t)s)
        #define ACR_FREE(p) free(p)
        #define ACR_REALLOC(p,s) realloc(p, (size_t)s)
    #else
        // Note: src/ACR/heap.c must be added to any project
        //       that wishes to use ACR/heap.h
        #include "ACR/heap.h"
    #endif // #ifndef ACR_CONFIG_NO_LIBC
#else
    #define ACR_HAS_MALLOC ACR_BOOL_FALSE
    #define ACR_HEAP_IS_GLOBAL ACR_BOOL_FALSE
    #define ACR_MALLOC(s) ACR_NULL
    #define ACR_FREE(p)
    #define ACR_REALLOC(p,s) ACR_NULL
#endif // #ifndef ACR_CONFIG_NO_MALLOC

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
#define ACR_NEW_BY_SIZE(n, t, s) t* n = (t*)ACR_MALLOC(s);ACR_CLEAR_MEMORY(n,s)

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
#define ACR_NEW_BY_TYPE(n, t) ACR_NEW_BY_SIZE(n,t,(sizeof(t)))

/** similar to malloc but automatically defines the variable and clears the memory
 
    example:

        int main()
        {
            ACR_NEW_BY_TYPE(twoDateTime, ACR_DateTime_t, 2);

            twoDateTime[1].tm_sec = 30;
            twoDateTime[1].tm_min = 1;
            // etc
        }
*/
#define ACR_NEW_BY_COUNT(n, t, c) ACR_NEW_BY_SIZE(n,t,(sizeof(t)*c))

/** similar to free but checks the pointer for null and sets it to null when freed
*/
#define ACR_DELETE(n) \
{\
    if(n)\
    {\
        ACR_FREE(n);\
        n = ACR_NULL;\
    }\
}

#endif
