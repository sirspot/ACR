/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2019 Adam C. Rosenberg

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

    functions for access to the ACR_Buffer_t type

*/
#include "ACR/buffer.h"

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
ACR_Info_t ACR_BufferNew(
	ACR_Buffer_t** mePtr)
{
	ACR_Info_t result = ACR_INFO_ERROR;
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_BUFFER_ALLOC(buffer, sizeof(ACR_Buffer_t));
		if(ACR_BUFFER_IS_VALID(buffer))
		{
			ACR_BufferInit((ACR_Buffer_t*)buffer.m_Pointer);
			result = ACR_INFO_OK;
		}
		(*mePtr) = (ACR_Buffer_t*)buffer.m_Pointer;
	}
	return result;
}

/**********************************************************/
void ACR_BufferDelete(
	ACR_Buffer_t** mePtr)
{
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_BufferDeInit((*mePtr));
		ACR_BUFFER_REFERENCE(buffer, (*mePtr), sizeof(ACR_Buffer_t));
		ACR_BUFFER_FREE(buffer);
		(*mePtr) = ACR_NULL;
	}
}

/**********************************************************/
void ACR_BufferInit(
	ACR_Buffer_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	me->m_Length = ACR_ZERO_LENGTH;
	me->m_Pointer = ACR_NULL;
}

/**********************************************************/
void ACR_BufferDeInit(
	ACR_Buffer_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_BUFFER_FREE((*me));
}

/**********************************************************/
ACR_Info_t ACR_BufferAllocate(
	ACR_Buffer_t* me,
	ACR_Length_t length)
{
	if(me == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	if(length == 0)
	{
		ACR_BUFFER_FREE((*me));
		return ACR_INFO_ERROR;
	}

	ACR_BUFFER_ALLOC((*me), length);
	if(ACR_BUFFER_IS_VALID((*me)))
	{
		return ACR_INFO_OK;
	}

	return ACR_INFO_ERROR;
}

/**********************************************************/
void ACR_BufferClear(
	ACR_Buffer_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_BUFFER_CLEAR((*me));
}
