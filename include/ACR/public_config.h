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

/** \file public_config.h
 
    This header describes the defines used to
    configure the ACR library.
    It is included automatically with public.h

    See public.h for more information.
*/
#ifndef _ACR_PUBLIC_CONFIG_H_
#define _ACR_PUBLIC_CONFIG_H_

/*
    ### Preprocessor Defines For Confguration Options ###

    Hopefully you are able to use one of the development environments
    that have been preconfigured such as Gitpod, Visual Studio, or Qt Creator.
    These platforms are further described in public.h under the
    "TYPES AND DEFINES - PLATFORM AND COMPILER" section.

        ACR_PLATFORM_MAC            MacOS X

            ACR_IDE_XCODE           using XCode
            ACR_IDE_QTCREATOR       using QtCreator

            ACR_COMPILER_CLANG      compiling with clang

        ACR_PLATFORM_WIN            Windows OS

            ACR_IDE_VS2017          using Visual Studio 2017 or higher
            ACR_IDE_QTCREATOR       using QtCreator

            ACR_COMPILER_MSVC       compiling with msvc
            ACR_COMPILER_MINGW      compiling with mingw

            ACR_WIN_NATIVE          define this to include the native Windows headers

        ACR_PLATFORM_GITPOD         Gitpod
        
                                    using Theia
                                    compiling with gcc

    For additional control over the configuration or if using an
    alternate development environment, the following options can
    be defined in your preprocessor flags.

        ACR_DEBUG           include debug tools.
                            see "TYPES AND DEFINES - DEBUG" for details.

        ACR_BIG_ENDIAN      always assume big endian without
                            dynamically checking the system
                            endianess.
                            see "TYPES AND DEFINES - ENDIANNESS" for details.

        ACR_LITTLE_ENDIAN   always assume little endian without
                            dynamically checking the system
                            endianess.
                            see "TYPES AND DEFINES - ENDIANNESS" for details.

        ACR_NO_MALLOC       do not include malloc() or free() and disables
                            ACR_MALLOC and ACR_FREE macros.
                            see "TYPES AND DEFINES - MALLOC" for details.

        ACR_NO_RTC          do not include <time.h> for time_t, struct tm,
                            time(), and gmtime_s() or gmtime_r()
                            Note: this does not completely disables support
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

*/

#endif
