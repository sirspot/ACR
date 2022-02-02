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
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
ACR_Info_t ACR_BufferNew(
	ACR_BufferObj_t** mePtr)
{
    ACR_Info_t result = ACR_INFO_ERROR;
	if(mePtr != ACR_NULL)
	{
		ACR_NEW_BY_TYPE(newBuffer, ACR_BufferObj_t);
		if(newBuffer)
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
	if(mePtr != ACR_NULL)
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
	if(me == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	if(length == 0)
	{
		ACR_BUFFER_FREE(me->m_Base);
		return ACR_INFO_ERROR;
	}

	ACR_BUFFER_ALLOC(me->m_Base, length);
	if(ACR_BUFFER_IS_VALID(me->m_Base))
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
	if(me == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	if(length == 0)
	{
		ACR_BUFFER_FREE(me->m_Base);
		return ACR_INFO_ERROR;
	}

	ACR_BUFFER_SET_DATA(me->m_Base, ptr, length);
	if(ACR_BUFFER_IS_VALID(me->m_Base))
	{
		return ACR_INFO_OK;
	}

	return ACR_INFO_ERROR;
}

/**********************************************************/
void ACR_BufferClear(
	ACR_BufferObj_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_BUFFER_CLEAR(me->m_Base);
}

/**********************************************************/
void ACR_BufferShiftLeft(
	ACR_BufferObj_t* me,
	ACR_Length_t length)
{
	if(me == ACR_NULL)
	{
		return;
	}

    /// \todo shift left
	ACR_UNUSED(length);
}

/**********************************************************/
void ACR_BufferShiftRight(
	ACR_BufferObj_t* me,
	ACR_Length_t length)
{
	if(me == ACR_NULL)
	{
		return;
	}

    /// \todo shift right
	ACR_UNUSED(length);
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
	if(me == ACR_NULL)
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
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_BUFFER_FREE(me->m_Base);
}
