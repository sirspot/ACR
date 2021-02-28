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

/** \file public_bytes_and_flags.h
 
    This header contains commonly used types and values
    for manipulating bit flags. It can be used standalone
    from the entire library or is included automatically
    with public.h

    See public.h for more information.

*/
#ifndef _ACR_PUBLIC_BYTES_AND_FLAGS_H_
#define _ACR_PUBLIC_BYTES_AND_FLAGS_H_

////////////////////////////////////////////////////////////
//
// TYPES AND DEFINES - BYTES
//
////////////////////////////////////////////////////////////

/** type for a single byte

    ### New to C? ###

    Q: What does unsigned mean?
    A: When a variable type is unsigned, it cannot be negative.
       This has a few pros and cons.
       Pros: 1. the sign bit can be used for the value and thus a larger number can be stored
             2. the value is never negative so it is not necessary to check when used as an index into arrays
             3. bit flags are easier to understand because changing a single bit will never make the value negative
                see TYPES AND DEFINES - FLAGS for details on bit flags
             4. binary values are easier to understand because they don't use Two's complement
                see https://en.wikipedia.org/wiki/Two%27s_complement for a detailed explanation
       Cons: 1. negative numbers are not available so subtraction must be done more carefully
             2. when signed and unsigned variables are compared, the compiler could make some
                unexpected type changes so this must be done carefully to support all platforms.

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
// TYPES AND DEFINES - FLAGS
//
////////////////////////////////////////////////////////////

/** flags are always a single byte to keep options organized.
    if necessary, use more than one set of flags.

    ### New to C? ###

    Q: What are flags?
    A: Flags are a clever way to store boolean values.
       There are 8 bits in a byte and each one can be set
       to 0 (false) or 1 (true). Checking and modifying
       these bits individually allows them to be used
       as a single boolean value but the real power of
       this feature is the ability to do this on many
       of the bits at the same time. 

*/
typedef ACR_Byte_t ACR_Flags_t;

/* Hex values for each flag
*/
#define ACR_FLAG_NONE  0x00
#define ACR_FLAG_ONE   0x01
#define ACR_FLAG_TWO   0x02
#define ACR_FLAG_THREE 0x04
#define ACR_FLAG_FOUR  0x08
#define ACR_FLAG_FIVE  0x10
#define ACR_FLAG_SIX   0x20
#define ACR_FLAG_SEVEN 0x40
#define ACR_FLAG_EIGHT 0x80

/** Converts a number between 1 and 8 to the cooresponding flag
*/
#define ACR_FLAG(n) (0x01 << (n-1))

/** checks if any of the flags are present
 
    example:

    ACR_Flags_t flags = ACR_FLAG_ONE | ACR_FLAG_FOUR | ACR_FLAG_SEVEN;
    if(ACR_HAS_ANY_FLAGS(flags, ACR_FLAG_ONE | ACR_FLAG_FOUR))
    {
        // flags has ONE and/or FOUR
    }

*/
#define ACR_HAS_ANY_FLAGS(checkFlags, forFlags) ((checkFlags) & (forFlags)) != 0

/** checks if all of the flags are present
 
    example:

    ACR_Flags_t flags = ACR_FLAG_ONE | ACR_FLAG_FOUR | ACR_FLAG_SEVEN;
    if(ACR_HAS_ALL_FLAGS(flags, ACR_FLAG_ONE | ACR_FLAG_FOUR | ACR_FLAG_SEVEN))
    {
        // flags has ONE, FOUR, and SEVEN
    }

*/
#define ACR_HAS_ALL_FLAGS(checkFlags, forFlags) ((checkFlags) & (forFlags)) == forFlags

/** use this when checking for just one flag
*/
#define ACR_HAS_FLAG(checkFlags, forFlag) ACR_HAS_ALL_FLAGS(checkFlags, forFlag)

/** checks if any flags exist that are not specified
 
    example:

    ACR_Flags_t flags = ACR_FLAG_ONE | ACR_FLAG_FOUR | ACR_FLAG_SEVEN;
    if(ACR_HAS_ONLY_FLAGS(flags, ACR_FLAG_ONE | ACR_FLAG_FOUR))
    {
        // flags has ONE and/or FOUR and no other flags
    }
    else
    {
        // there are flags other than ONE and FOUR present
    }

*/
#define ACR_HAS_ONLY_FLAGS(checkFlags, forFlags) ((checkFlags) & (~(forFlags)) == 0

/** adds one or more flags to the existing flags
*/
#define ACR_ADD_FLAGS(flags, flagsToAdd) flags |= (flagsToAdd)

/** removes one or more flags from the existing flags
*/
#define ACR_REMOVE_FLAGS(flags, flagsToRemove) flags &= (~(flagsToRemove))

#endif
