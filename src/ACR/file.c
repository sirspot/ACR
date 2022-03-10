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
/** \file file.c

    public and private functions that perform common operations on ACR_FileInterface_t

*/
#include "ACR/file.h"

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
ACR_Length_t ACR_FileGetLength(
	ACR_FileInterface_t* me)
{
    ACR_Length_t length = 0;
    if(me)
    {
        if(me->m_Position && me->m_Seek)
        {
            // save the current position before
            // finding the the end of the file
            // so that it can be returned
            // when finished
            ACR_Length_t position = me->m_Position(me->m_User);
            if(me->m_Seek(0, ACR_INFO_LAST, me->m_User) == ACR_INFO_OK)
            {
                length = me->m_Position(me->m_User);

                // return to the original position
                me->m_Seek(position, ACR_INFO_FIRST, me->m_User);
            }
        }
        else
        {
            // cannot find the length of the file
            // without access to the position and
            // the ability to seek to the end
        }
    }
    return length;
}

/**********************************************************/
ACR_Info_t ACR_FileReadAll(
	ACR_FileInterface_t* me,
    ACR_Buffer_t* buffer)
{
    ACR_Info_t result = ACR_INFO_OK;
    if(me && buffer)
    {
        if(me->m_Read)
        {
            ACR_Length_t length = ACR_FileGetLength(me);
            ACR_BUFFER_ALLOC((*buffer), length);
            if (buffer->m_Pointer)
            {
                if(length > 0)
                {
                    // assign the buffer to a variable length buffer
                    // so that the number of bytes actually read
                    // can be verified
                    ACR_VAR_BUFFER(varBuffer);
                    ACR_VAR_BUFFER_SET_MEMORY(varBuffer, buffer->m_Pointer, buffer->m_Length);
                    if(me->m_Read(&varBuffer, me->m_User) == ACR_INFO_OK)
                    {
                        if(varBuffer.m_Buffer.m_Length != buffer->m_Length)
                        {
                            // failed to read all bytes
                            ACR_BUFFER_FREE((*buffer));
                            result = ACR_INFO_ERROR;
                        }
                        else
                        {
                            // successfully read all bytes
                        }
                    }
                    else
                    {
                        // read failed
                        ACR_BUFFER_FREE((*buffer));
                        result = ACR_INFO_ERROR;
                    }
                }
                else
                {
                    // nothing to read.
                    // this is not an error
                }
            }
            else
            {
                // could not allocate length
                result = ACR_INFO_ERROR;
            }
        }
        else
        {
            // no read function
            result = ACR_INFO_ERROR;
        }
    }
    else
    {
        // invalid pointer
        result = ACR_INFO_ERROR;    
    }

    return result;
}
