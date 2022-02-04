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
/** \file varbuffer.c

    functions for access to the ACR_VarBuffer_t type

*/
#include "ACR/varbuffer.h"

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
ACR_Info_t ACR_VarBufferNew(
	ACR_VarBuffer_t** mePtr)
{
	ACR_Info_t result = ACR_INFO_ERROR;
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_BUFFER_ALLOC(buffer, sizeof(ACR_VarBuffer_t));
		if(ACR_BUFFER_IS_VALID(buffer))
		{
			ACR_VarBufferInit((ACR_VarBuffer_t*)buffer.m_Pointer);
			result = ACR_INFO_OK;
		}
		(*mePtr) = (ACR_VarBuffer_t*)buffer.m_Pointer;
	}
	return result;
}

/**********************************************************/
void ACR_VarBufferDelete(
	ACR_VarBuffer_t** mePtr)
{
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_VarBufferDeInit((*mePtr));
		ACR_BUFFER_SET_DATA(buffer, (*mePtr), sizeof(ACR_VarBuffer_t));
		ACR_BUFFER_FORCE_FREE(buffer);
		(*mePtr) = ACR_NULL;
	}
}

/**********************************************************/
void ACR_VarBufferInit(
	ACR_VarBuffer_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	me->m_MaxLength = ACR_ZERO_LENGTH;
	me->m_Buffer.m_Length = ACR_ZERO_LENGTH;
	me->m_Buffer.m_Pointer = ACR_NULL;
}

/**********************************************************/
void ACR_VarBufferDeInit(
	ACR_VarBuffer_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_VAR_BUFFER_FREE((*me));
}

/**********************************************************/
ACR_Length_t ACR_VarBufferGetMaxLength(
	ACR_VarBuffer_t* me)
{
	if(me == ACR_NULL)
	{
		return ACR_ZERO_LENGTH;
	}

	return ACR_VAR_BUFFER_GET_MAX_LENGTH((*me));
}

/**********************************************************/
ACR_Info_t ACR_VarBufferAllocate(
	ACR_VarBuffer_t* me,
	ACR_Length_t length)
{
	if(me == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	if(length == 0)
	{
		ACR_VAR_BUFFER_FREE((*me));
		return ACR_INFO_ERROR;
	}

	ACR_VAR_BUFFER_ALLOC((*me), length);

	if(ACR_VAR_BUFFER_IS_VALID((*me)))
	{
		return ACR_INFO_OK;
	}

	return ACR_INFO_ERROR;
}

/**********************************************************/
ACR_Info_t ACR_VarBufferRef(
	ACR_VarBuffer_t* me,
	void* ptr,
	ACR_Length_t length)
{
	if(me == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	if(length == 0)
	{
		ACR_VAR_BUFFER_FREE((*me));
		return ACR_INFO_ERROR;
	}

	ACR_VAR_BUFFER_REFERENCE((*me), ptr, length);
	if(ACR_VAR_BUFFER_IS_VALID((*me)))
	{
		return ACR_INFO_OK;
	}

	return ACR_INFO_ERROR;
}

/**********************************************************/
ACR_Info_t ACR_VarBufferSetLength(
	ACR_VarBuffer_t* me,
	ACR_Length_t length)
{
	if(me == ACR_NULL)
	{
		return ACR_INFO_ERROR;
	}

	if(length > ACR_VAR_BUFFER_GET_MAX_LENGTH((*me)))
	{
		return ACR_INFO_ERROR;
	}

	me->m_Buffer.m_Length = length;
	return ACR_INFO_OK;
}

/**********************************************************/
ACR_Info_t ACR_VarBufferAppend(
	ACR_VarBuffer_t* me,
	void* srcPtr,
	ACR_Length_t length)
{
	if(me != ACR_NULL)
	{
		// do what ACR_VAR_BUFFER_APPEND does but with error checking
		if(length <= (me->m_MaxLength - me->m_Buffer.m_Length))
		{
			if(srcPtr != ACR_NULL)
			{
				// Note: warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
				//       can be safely ignored here as it only serves to notify the user that
				//       the mitigation code will be used if desired
				ACR_MEMCPY(((ACR_Byte_t*)me->m_Buffer.m_Pointer) + me->m_Buffer.m_Length, srcPtr, length);
			}
			me->m_Buffer.m_Length += length;
			return ACR_INFO_OK;
		}
	}

	return ACR_INFO_ERROR;
}

/**********************************************************/
ACR_Info_t ACR_VarBufferPrepend(
	ACR_VarBuffer_t* me,
	void* srcPtr,
	ACR_Length_t length)
{
	if(me != ACR_NULL)
	{
		if(length <= (me->m_MaxLength - me->m_Buffer.m_Length))
		{
			if(me->m_Buffer.m_Length > 0)
			{
				me->m_Buffer.m_Length += length;
				/// \todo shift
			}
			else
			{
				me->m_Buffer.m_Length += length;
			}
			if(srcPtr != ACR_NULL)
			{
				ACR_MEMCPY(me->m_Buffer.m_Pointer, srcPtr, length);
			}
			return ACR_INFO_OK;
		}
	}

	return ACR_INFO_ERROR;
}

/**********************************************************/
void ACR_VarBufferClear(
	ACR_VarBuffer_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_BUFFER_CLEAR(me->m_Buffer);
}
