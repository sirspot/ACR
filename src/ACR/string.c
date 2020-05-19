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
/** \file string.c

    functions for access to the ACR_String_t type

*/
#include "ACR/string.h"

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/**********************************************************/
ACR_Info_t ACR_StringNew(
	ACR_String_t** mePtr)
{
	ACR_Info_t result = ACR_INFO_ERROR;
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_BUFFER_ALLOC(buffer, sizeof(ACR_String_t));
		if(ACR_BUFFER_IS_VALID(buffer))
		{
			ACR_StringInit((ACR_String_t*)buffer.m_Pointer);
			result = ACR_INFO_OK;
		}
		(*mePtr) = (ACR_String_t*)buffer.m_Pointer;
	}
	return result;
}

/**********************************************************/
void ACR_StringDelete(
	ACR_String_t** mePtr)
{
	if(mePtr != ACR_NULL)
	{
		ACR_BUFFER(buffer);

		ACR_StringDeInit((*mePtr));
		ACR_BUFFER_REFERENCE(buffer, (*mePtr), sizeof(ACR_String_t));
		ACR_BUFFER_FORCE_FREE(buffer);
		(*mePtr) = ACR_NULL;
	}
}

/**********************************************************/
void ACR_StringInit(
	ACR_String_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	me->m_Count = ACR_EMPTY_VALUE;
	me->m_Buffer.m_Pointer = ACR_NULL;
	me->m_Buffer.m_Length = ACR_ZERO_LENGTH;
}

/**********************************************************/
void ACR_StringDeInit(
	ACR_String_t* me)
{
	if(me == ACR_NULL)
	{
		return;
	}

	ACR_BUFFER_FREE(me->m_Buffer);
}
