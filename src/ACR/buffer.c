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
/** \file buffer.c

    public and private functions for access to the ACR_BufferObj_t type

*/
#include "ACR/private/private_buffer.h"

// included for ACR_UNUSED
#include "ACR/public/public_functions.h"

////////////////////////////////////////////////////////////
//
// HELPER FUNCTIONS
//
////////////////////////////////////////////////////////////

/** shift left without wrap
*/
void _ACR_BufferShiftLeftNoWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes);

/** shift right without wrap
*/
void _ACR_BufferShiftRightNoWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes);

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
ACR_Info_t ACR_BufferNew(
    ACR_BufferObj_t** mePtr)
{
    ACR_Info_t result = ACR_INFO_ERROR;
    if (mePtr != ACR_NULL)
    {
        ACR_NEW_BY_TYPE(newBuffer, ACR_BufferObj_t);
        if (newBuffer)
        {
            ACR_BufferInit(newBuffer);
            result = ACR_INFO_OK;
        }
        (*mePtr) = newBuffer;
    }
    return result;
}

/**********************************************************/
void ACR_BufferDelete(
    ACR_BufferObj_t** mePtr)
{
    if (mePtr != ACR_NULL)
    {
        ACR_BufferDeInit((*mePtr));
        ACR_FREE((*mePtr));
        (*mePtr) = ACR_NULL;
    }
}

/**********************************************************/
ACR_Info_t ACR_BufferAllocate(
    ACR_BufferObj_t* me,
    ACR_Length_t length)
{
    if (me == ACR_NULL)
    {
        return ACR_INFO_ERROR;
    }

    if (length == 0)
    {
        ACR_BUFFER_FREE(me->m_Base);
        return ACR_INFO_ERROR;
    }

    ACR_BUFFER_ALLOC(me->m_Base, length);
    if (ACR_BUFFER_IS_VALID(me->m_Base))
    {
        return ACR_INFO_OK;
    }

    return ACR_INFO_ERROR;
}

/**********************************************************/
ACR_Info_t ACR_BufferRef(
    ACR_BufferObj_t* me,
    void* ptr,
    ACR_Length_t length)
{
    if (me == ACR_NULL)
    {
        return ACR_INFO_ERROR;
    }

    if (length == 0)
    {
        ACR_BUFFER_FREE(me->m_Base);
        return ACR_INFO_ERROR;
    }

    ACR_BUFFER_SET_DATA(me->m_Base, ptr, length);
    if (ACR_BUFFER_IS_VALID(me->m_Base))
    {
        return ACR_INFO_OK;
    }

    return ACR_INFO_ERROR;
}

/**********************************************************/
void ACR_BufferClear(
    ACR_BufferObj_t* me)
{
    if (me == ACR_NULL)
    {
        return;
    }

    ACR_BUFFER_CLEAR(me->m_Base);
}

/**********************************************************/
ACR_Info_t ACR_BufferSetByteAt(
    ACR_BufferObj_t* me,
    ACR_Length_t pos,
    ACR_Byte_t value)
{
    if (me == ACR_NULL)
    {
        return ACR_INFO_ERROR;
    }

    if ((me->m_Base.m_Pointer == ACR_NULL) ||
        (pos >= me->m_Base.m_Length))
    {
        return ACR_INFO_ERROR;
    }

    ((ACR_Byte_t*)me->m_Base.m_Pointer)[pos] = value;
    return ACR_INFO_OK;
}

/**********************************************************/
void ACR_BufferShift(
    ACR_BufferObj_t* me,
    ACR_Length_t shiftBytes,
    ACR_Info_t direction,
    ACR_Bool_t wrap)
{
    if (me == ACR_NULL)
    {
        return;
    }

    if (wrap)
    {
        // wrap
        //ACR_Byte_t swap[ACR_BUFFER_BYTE_COUNT_PER_SHIFT];
        //ACR_Length_t swapLength;
    }
    else
    {
        // no wrap
        if (direction == ACR_INFO_LEFT)
        {
            _ACR_BufferShiftLeftNoWrap(
                (ACR_Byte_t*)me->m_Base.m_Pointer,
                me->m_Base.m_Length,
                shiftBytes);
        }
        else if (direction == ACR_INFO_RIGHT)
        {
            _ACR_BufferShiftRightNoWrap(
                (ACR_Byte_t*)me->m_Base.m_Pointer,
                me->m_Base.m_Length,
                shiftBytes);
        }
        else
        {
            // invalid direction
        }
    }
}

////////////////////////////////////////////////////////////
//
// HELPER FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
void _ACR_BufferShiftLeftNoWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes)
{
    if ((ptr == ACR_NULL) || 
        (length == ACR_ZERO_LENGTH))
    {
        // nothing to shift
        return;
    }

    if (length <= shiftBytes)
    {
        // effectively clears the memory
        ACR_MEMSET(ptr, ACR_EMPTY_VALUE, length);
        return;
    }

    // the position from the start of the buffer
    // used as the destination to copy data to
    ACR_Length_t destPos = 0;

    // the maximum amount of space available to copy to
    ACR_Length_t destFree = length;

    // the position used as the source of the data.
    // this will only need to be calculated if destFree is greater than 0
    ACR_Length_t srcPos = destPos;

    // the maximum amount of data available to copy.
    // this will only need to be calculated if destFree is greater than 0
    ACR_Length_t srcAvailable;

    /* How to visualize shifting data to the left

        buffer       (0) |--------------------------------------------| (length)
                         |                                            |

                         ^
        ptr              ^ selects a location in
                         ^ the buffer 1 byte long
                         ^

                                ^
        destPos                 ^ --> moves this way by
                                ^     number of bytes
                                ^     copied each loop
                                ^

        destFree      (destPos) |-------|-----------------------------| (length - destPos)
                                | --> shrinks this way                |


                                        ^
        srcPos                          ^ --> moves this way by
                                        ^     number of bytes
                                        ^     copied each loop
                                        ^

        srcAvailable           (srcPos) |-------|---------------------| (length - srcPos)
                                        | --> shrinks this way        |


        shiftBytes             (srcPos) |-------| (srcPos + shiftBytes)
                                        |       |

                      (destPos) | <----   each loop copies at most
                                |-------| this number of bytes
                                          to destPos


    */

    // keep copying bytes until there is no more space at destPos
    while (destFree > 0)
    {
        // move source position to the 
        // position that will be used during this loop.
        srcPos += shiftBytes;
        if (srcPos >= length)
        {
            // no source data available.
            // fill the rest of the free destination
            // memory with empty values
            ACR_MEMSET(&ptr[destPos], ACR_EMPTY_VALUE, destFree);
            // break out of this loop
            break;
        }

        // calculate source data available
        srcAvailable = (length - srcPos);
        if (srcAvailable < shiftBytes)
        {
            // not enough source data.
            // reduce shiftBytes to just the source available.
            // Note: a previous check was made that ensures
            //       srcAvailable is greater than 0 so shiftBytes
            //       will also be greater than 0
            shiftBytes = srcAvailable;
        }

        if (destFree < shiftBytes)
        {
            // not enough free space.
            // fill the rest of the destination with source data
            ACR_MEMCPY(&ptr[destPos], &ptr[srcPos], destFree);
            // break out of this loop
            break;
        }

        // copy all shiftBytes from srcPos to destPos
        ACR_MEMCPY(&ptr[destPos], &ptr[srcPos], shiftBytes);
        destPos += shiftBytes;
        destFree = (length - destPos);
    }
}

/**********************************************************/
void _ACR_BufferShiftRightNoWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes)
{
    if ((ptr == ACR_NULL) ||
        (length == ACR_ZERO_LENGTH))
    {
        // nothing to shift
        return;
    }

    if (length <= shiftBytes)
    {
        // effectively clears the memory
        ACR_MEMSET(ptr, ACR_EMPTY_VALUE, length);
        return;
    }

    // the position used as the source of the data.
    ACR_Length_t srcPos = (length - shiftBytes);

    // the position from the start of the buffer
    // used as the destination to copy data to
    ACR_Length_t destPos = length;

    /* How to visualize shifting data to the right

        buffer          (0) |--------------------------------------------| (length)
                            |                                            |

                            ^
        ptr                 ^ selects a location in
                            ^ the buffer 1 byte long
                            ^

                                                          ^
        destPos                     <-- moves this way by ^
                                        number of bytes   ^
                                        copied each loop  ^
                                                          ^

                                                  ^
        srcPos              <-- moves this way by ^
                                number of bytes   ^
                                copied each loop  ^
                                                  ^

        shiftBytes                       (srcPos) |------| (srcPos + shiftBytes)
                                                  |      |

                          each loop copies at most ----> | (destPos)
                          this number of bytes           |------|
                          to destPos        

    */

    // keep copying bytes until there is no more space at destPos
    do
    {
        if (srcPos < shiftBytes)
        {
            // not enough source data.
            // reduce shiftBytes to just the source available.
            // Note: a previous check was made that ensures
            //       srcAvailable is greater than 0 so shiftBytes
            //       will also be greater than 0
            shiftBytes = srcPos;
        }

        // move positions for the this loop
        destPos -= shiftBytes;
        srcPos -= shiftBytes;

        // copy all shiftBytes from srcPos to destPos
        ACR_MEMCPY(&ptr[destPos], &ptr[srcPos], shiftBytes);

        if (srcPos == 0)
        {
            // no more source data available.
            if (destPos > 0)
            {
                // fill the rest of the free destination
                // memory with empty values
                ACR_MEMSET(&ptr[0], ACR_EMPTY_VALUE, destPos);
            }
            // break out of this loop
            break;
        }

    }
    while (destPos > 0);

}

////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
void ACR_BufferInit(
    ACR_BufferObj_t* me)
{
    if (me == ACR_NULL)
    {
        return;
    }

    me->m_Base.m_Length = ACR_ZERO_LENGTH;
    me->m_Base.m_Pointer = ACR_NULL;
    me->m_Base.m_Flags = ACR_BUFFER_FLAGS_NONE;
}

/**********************************************************/
void ACR_BufferDeInit(
    ACR_BufferObj_t* me)
{
    if (me == ACR_NULL)
    {
        return;
    }

    ACR_BUFFER_FREE(me->m_Base);
}
