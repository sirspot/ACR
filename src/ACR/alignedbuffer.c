/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2020 Adam C. Rosenberg

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
/** \file alignedbuffer.c

    functions for access to the ACR_AlignedBuffer_t type

*/
#include "ACR/alignedbuffer.h"

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
ACR_Info_t ACR_AlignedBufferNew(
	ACR_AlignedBuffer_t** mePtr)
{
	ACR_Info_t result = ACR_INFO_ERROR;
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_BUFFER_ALLOC(buffer, sizeof(ACR_AlignedBuffer_t));
		if(ACR_BUFFER_IS_VALID(buffer))
		{
			ACR_AlignedBufferInit((ACR_AlignedBuffer_t*)buffer.m_Pointer);
			result = ACR_INFO_OK;
		}
		(*mePtr) = (ACR_AlignedBuffer_t*)buffer.m_Pointer;
	}
	return result;
}

/**********************************************************/
void ACR_AlignedBufferDelete(
	ACR_AlignedBuffer_t** mePtr)
{
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_AlignedBufferDeInit((*mePtr));
		ACR_BUFFER_SET_DATA(buffer, (*mePtr), sizeof(ACR_AlignedBuffer_t));
		ACR_BUFFER_FORCE_FREE(buffer);
		(*mePtr) = ACR_NULL;
	}
}

/**********************************************************/
void ACR_AlignedBufferInit(
	ACR_AlignedBuffer_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	me->m_UnalignedBuffer.m_Length = ACR_ZERO_LENGTH;
	me->m_UnalignedBuffer.m_Pointer = ACR_NULL;
	me->m_UnalignedBuffer.m_Flags = ACR_BUFFER_FLAGS_NONE;
	me->m_AlignedBuffer.m_Length = ACR_ZERO_LENGTH;
	me->m_AlignedBuffer.m_Pointer = ACR_NULL;
	me->m_AlignedBuffer.m_Flags = ACR_BUFFER_FLAGS_NONE;
}

/**********************************************************/
void ACR_AlignedBufferDeInit(
	ACR_AlignedBuffer_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_ALIGNED_BUFFER_FREE((*me));
}

/**********************************************************/
ACR_Info_t ACR_AlignedBufferRef(
	ACR_AlignedBuffer_t* me,
	void* ptr,
	ACR_Length_t length)
{
	if(me == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	ACR_ALIGNED_BUFFER_REFERENCE((*me), ptr, length);
	if(ACR_ALIGNED_BUFFER_IS_VALID((*me)))
	{
		return ACR_INFO_OK;
	}

	return ACR_INFO_ERROR;
}

/**********************************************************/
ACR_Info_t ACR_AlignedBufferGetRef(
	ACR_AlignedBuffer_t* me,
	ACR_Buffer_t* buffer)
{
	if(me == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	if(buffer == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	if(ACR_ALIGNED_BUFFER_IS_VALID((*me)))
	{
		(*buffer) = me->m_AlignedBuffer;
		return ACR_INFO_OK;
	}

	return ACR_INFO_ERROR;
}
