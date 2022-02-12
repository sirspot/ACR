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

// included for ACR_VALUE_AT()
#include "ACR/public/public_count.h"

////////////////////////////////////////////////////////////
//
// HELPER FUNCTIONS
//
////////////////////////////////////////////////////////////

/** shift left without wrap helper for ACR_BufferShift(me, shiftBytes, ACR_INFO_LEFT, ACR_INFO_FALSE)
*/
void _ACR_BufferShiftLeftNoWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes);

/** shift right without wrap helper for ACR_BufferShift(me, shiftBytes, ACR_INFO_RIGHT, ACR_INFO_FALSE)
*/
void _ACR_BufferShiftRightNoWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes);

/** shift left with wrap helper for ACR_BufferShift(me, shiftBytes, ACR_INFO_LEFT, ACR_INFO_TRUE)
*/
void _ACR_BufferShiftLeftWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes,
    ACR_Byte_t* swapPtr,
    ACR_Length_t swapLength);

/** shift right with wrap helper for ACR_BufferShift(me, shiftBytes, ACR_INFO_RIGHT, ACR_INFO_TRUE)
*/
void _ACR_BufferShiftRightWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes,
    ACR_Byte_t* swapPtr,
    ACR_Length_t swapLength);

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
ACR_Info_t ACR_BufferSetData(
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
ACR_Length_t ACR_BufferGetLength(
	ACR_BufferObj_t* me)
{
    if(me)
    {
        return me->m_Base.m_Length;
    }

    return 0;
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
ACR_Info_t ACR_BufferCopyToBuffer(
	ACR_BufferObj_t* me,
	ACR_Length_t srcPos,
	ACR_BufferObj_t* dest,
	ACR_Length_t destPos,
	ACR_Length_t length)
{
    if (me == ACR_NULL || dest == ACR_NULL)
    {
        return ACR_INFO_ERROR;
    }

    if ((me->m_Base.m_Pointer == ACR_NULL) ||
        (dest->m_Base.m_Pointer == ACR_NULL))
    {
        return ACR_INFO_INVALID;
    }

    if((srcPos + length) > me->m_Base.m_Length)
    {
        return ACR_INFO_GREATER;
    }

    if((destPos + length) > dest->m_Base.m_Length)
    {
        return ACR_INFO_LESS;
    }

    ACR_Byte_t* srcPtr = ((ACR_Byte_t*)me->m_Base.m_Pointer) + srcPos;
    ACR_Byte_t* destPtr = ((ACR_Byte_t*)dest->m_Base.m_Pointer) + destPos;
    ACR_MEMCPY(destPtr, srcPtr, length);

    return ACR_INFO_OK;
}

/**********************************************************/
ACR_Info_t ACR_BufferCopyToMemory(
	ACR_BufferObj_t* me,
	ACR_Length_t srcPos,
	void* destPtr,
	ACR_Length_t destLength,
	ACR_Length_t length)
{
    if (me == ACR_NULL)
    {
        return ACR_INFO_ERROR;
    }

    if ((me->m_Base.m_Pointer == ACR_NULL) ||
        (destPtr == ACR_NULL))
    {
        return ACR_INFO_INVALID;
    }

    if((srcPos + length) > me->m_Base.m_Length)
    {
        return ACR_INFO_GREATER;
    }

    if(destLength < length)
    {
        return ACR_INFO_LESS;
    }

    ACR_Byte_t* srcPtr = ((ACR_Byte_t*)me->m_Base.m_Pointer) + srcPos;
    ACR_MEMCPY(destPtr, srcPtr, length);

    return ACR_INFO_OK;
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

    if (me->m_Base.m_Pointer == ACR_NULL)
    {
        return ACR_INFO_INVALID;
    }

    if (pos >= me->m_Base.m_Length)
    {
        return ACR_INFO_GREATER;
    }

    ACR_VALUE_AT(ACR_Byte_t, me->m_Base.m_Pointer, pos) = value;

    return ACR_INFO_OK;
}

/**********************************************************/
ACR_Info_t ACR_BufferGetByteAt(
	ACR_BufferObj_t* me,
	ACR_Length_t pos,
	ACR_Byte_t* value)
{
    if (me == ACR_NULL)
    {
        return ACR_INFO_ERROR;
    }

    if (me->m_Base.m_Pointer == ACR_NULL)
    {
        return ACR_INFO_INVALID;
    }

    if (pos >= me->m_Base.m_Length)
    {
        return ACR_INFO_GREATER;
    }

    if(value)
    {
        (*value) = ACR_VALUE_AT(ACR_Byte_t, me->m_Base.m_Pointer, pos);
    }

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
        ACR_Byte_t swapStackData[ACR_BUFFER_BYTE_COUNT_PER_SHIFT];
        if (direction == ACR_INFO_LEFT)
        {
            _ACR_BufferShiftLeftWrap(
                (ACR_Byte_t*)me->m_Base.m_Pointer,
                me->m_Base.m_Length,
                shiftBytes,
                swapStackData,
                ACR_BUFFER_BYTE_COUNT_PER_SHIFT);
        }
        else if (direction == ACR_INFO_RIGHT)
        {
            _ACR_BufferShiftRightWrap(
                (ACR_Byte_t*)me->m_Base.m_Pointer,
                me->m_Base.m_Length,
                shiftBytes,
                swapStackData,
                ACR_BUFFER_BYTE_COUNT_PER_SHIFT);
        }
        else
        {
            // invalid direction
        }
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

    /* How to visualize shifting data to the left <----

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

        destFree      (destPos) |xxxxxxx|-----------------------------| (length)
                                | --> shrinks this way                |


                                        ^
        srcPos                          ^ --> moves this way by
                                        ^     number of bytes
                                        ^     copied each loop
                                        ^

        srcAvailable           (srcPos) |xxxxxxx|---------------------| (length)
                                        | --> shrinks this way        |


        shiftBytes             (srcPos) |xxxxxxx| (srcPos + shiftBytes)
                                        |       |
                                      <----
                      (destPos) |-------|     each loop copies at most
                                |       |     this number of bytes
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
    // and also the amount of source data available.
    // (srcAvailable variable is not needed)
    ACR_Length_t srcPos = (length - shiftBytes);

    // the position from the start of the buffer
    // used as the destination to copy data to
    // and also the amount of space free
    // (destFree variable is not needed)
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

        shiftBytes                       (srcPos) |xxxxxx| (srcPos + shiftBytes)
                                                  |      |
                                                       ---->
                          each loop copies at most       | (destPos)
                          this number of bytes           |------|
                          to destPos

    */

    do
    {
        if (srcPos < shiftBytes)
        {
            // not enough source data.
            // reduce shiftBytes to just the source available.
            // Note: a previous check was made that ensures
            //       srcPos is greater than 0 so shiftBytes
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

        // keep copying bytes until there is no more space at destPos
    }
    while (destPos > 0);

}

/**********************************************************/
void _ACR_BufferShiftLeftWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes,
    ACR_Byte_t* swapPtr,
    ACR_Length_t swapLength)
{
    if ((ptr == ACR_NULL) || 
        (length == ACR_ZERO_LENGTH))
    {
        // nothing to shift
        return;
    }

    if((swapPtr == ACR_NULL) ||
       (swapLength == 0))
    {
        // no swap space
        return;
    }

    // only shift bytes the necessary
    // amount for the final data position
    // to be correct
    shiftBytes %= length;

    /* See _ACR_BufferShiftLeftNoWrap() for how to visualize shifting data to the left
       and this additional information to visualize the wrapped data

        buffer       (0) |xxxxxx--------------------------------abcdef| (length)
                         |                                            |

                             |                                    ^
                             | copy data from the buffer          |
                             | into the swap so that it           |
                             | can be placed back into            |
                             | the buffer after the shift         |
                             V                                    |
        swapPtr      (0) |abcdef| (swapLength)                 |abcdef|
 
    */

    while(shiftBytes > 0)
    {
        // determine the max number of bytes
        // that can be shifted during this loop
        ACR_Length_t currentShift = swapLength;
        if(currentShift > shiftBytes)
        {
            // reduce the number of bytes to just
            // those that remain to be shifted
            currentShift = shiftBytes;
        }

        // make a copy of the data at the start
        // of the buffer for this shift
        // Note: a previous check ensured currentShift is less than length
        ACR_MEMCPY(swapPtr, ptr, currentShift);
        _ACR_BufferShiftLeftNoWrap(ptr, length, currentShift);
        ACR_MEMCPY(&ptr[length - currentShift], swapPtr, currentShift);
        shiftBytes -= currentShift;
    }
    
}

/**********************************************************/
void _ACR_BufferShiftRightWrap(
    ACR_Byte_t* ptr,
    ACR_Length_t length,
    ACR_Length_t shiftBytes,
    ACR_Byte_t* swapPtr,
    ACR_Length_t swapLength)
{
    if ((ptr == ACR_NULL) || 
        (length == ACR_ZERO_LENGTH))
    {
        // nothing to shift
        return;
    }

    if((swapPtr == ACR_NULL) ||
       (swapLength == 0))
    {
        // no swap space
        return;
    }

    // only shift bytes the necessary
    // amount for the final data position
    // to be correct
    shiftBytes %= length;

    /* See _ACR_BufferShiftLeftNoWrap() for how to visualize shifting data to the left
       and this additional information to visualize the wrapped data

        buffer       (0) |abcdef--------------------------------xxxxxx| (length)
                         |                                            |

                             ^                                    |
                             |         copy data from the buffer  |
                             |         into the swap so that it   |
                             |         can be placed back into    |
                             |         the buffer after the shift |
                             |                                    V
        swapPtr      (0) |abcdef|        (length - shiftBytes) |abcdef| (length + swapLength)
 
    */

    while(shiftBytes > 0)
    {
        // determine the max number of bytes
        // that can be shifted during this loop
        ACR_Length_t currentShift = swapLength;
        if(currentShift > shiftBytes)
        {
            // reduce the number of bytes to just
            // those that remain to be shifted
            currentShift = shiftBytes;
        }

        // make a copy of the data at the start
        // of the buffer for this shift
        // Note: a previous check ensured currentShift is less than length
        ACR_MEMCPY(swapPtr, &ptr[length - currentShift], currentShift);
        _ACR_BufferShiftRightNoWrap(ptr, length, currentShift);
        ACR_MEMCPY(ptr, swapPtr, currentShift);
        shiftBytes -= currentShift;
    }
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
