/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2026 Adam C. Rosenberg

    Please read LICENSE before using this code

    Please read README.md for instructions on including
    this code in your project and where to find examples

    If you contribute to this code, Please add your name
    and email address to the AUTHORS list below so that
    we know who to thank!

    AUTHORS

    Adam C. Rosenberg <adam@sirspot.com>

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
/** \file unicode.c

*/
#include "ACR/unicode.h"

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS - UTF8 AND UNICODE
//
////////////////////////////////////////////////////////////

ACR_Info_t ACR_Utf8NextChar(
    const ACR_Byte_t* mem,
    ACR_Length_t memLength,
    ACR_Length_t* pos)
{
    if((*pos) < memLength)
    {
        ACR_Byte_t c = mem[(*pos)];
        if(c != 0)
        {
            ACR_Length_t p = (*pos) + ACR_UTF8_BYTE_COUNT(c);
            if(p < memLength)
            {
                (*pos) = p;
                return ACR_INFO_OK;
            }
        }
        else
        {
            // already at end of string
        }
    }
    return ACR_INFO_ERROR;
}

ACR_Info_t ACR_Utf8PrevChar(
    const ACR_Byte_t* mem,
    ACR_Length_t memLength,
    ACR_Length_t* pos)
{
    if(((*pos) > 0) && ((*pos) <= memLength))
    {
        ACR_Byte_t c;
        (*pos) -= 1;
        c = mem[(*pos)];
        if((c & 0x80) == 0)
        {
            // [0xxxxxxx]
            return ACR_INFO_OK;
        }
        else
        {
            // [1xxxxxxx]
            while((c & 0x40) == 0)
            {
                // [?0xxxxxx]
                if((*pos) == 0)
                {
                    return ACR_INFO_ERROR;
                }
                (*pos) -= 1;
                c = mem[(*pos)];
            }
            // [?1xxxxxx]
            return ACR_INFO_OK;
        }
    }
    return ACR_INFO_ERROR;
}

ACR_Unicode_t ACR_UnicodeToLower(
    ACR_Unicode_t unicode)
{
    /// \todo use a conversion table instead to handle additional unicode characters

    // handle ASCII characters
    if((unicode >= 65) && (unicode <= 90))
    {
        unicode += 32;
    }

    return unicode;
}

ACR_Unicode_t ACR_UnicodeToUpper(
    ACR_Unicode_t unicode)
{
    /// \todo use a conversion table instead to handle additional unicode characters

    // handle ASCII characters
    if((unicode >= 97) && (unicode <= 122))
    {
        unicode -= 32;
    }

    return unicode;
}

ACR_Unicode_t ACR_Utf8ToUnicode(
    const ACR_Byte_t* mem,
    int bytes)
{
    int offset = (bytes-1);
    if(offset > 0)
    {
        ACR_Unicode_t c = (((ACR_Unicode_t)(mem[0] & (0x3F>>offset))) << (offset*6));
        int byteNum = 1;
        do
        {
            offset -= 1;
            c |= (((ACR_Unicode_t)(mem[byteNum] & 0x3F)) << (offset*6));
            byteNum += 1;
        }
        while(offset > 0);
        // Note: warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
        //       can be safely ignored here as it only serves to notify the user that
        //       the mitigation code will be used if desired
        return c;
    }
    return (ACR_Unicode_t)mem[0];
}
