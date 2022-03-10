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
/** \file csv.h

    public functions for access to the ACR_CsvObj_t type

*/
#ifndef _ACR_CSV_H_
#define _ACR_CSV_H_

// included for ACR_String_t
#include "ACR/public/public_string.h"

// included for ACR_Info_t
#include "ACR/public/public_info.h"

// included for ACR_FileInterface_t
#include "ACR/public/public_file.h"

// included for ACR_VarBuffer_t
#include "ACR/public/public_varbuffer.h"

// included for ACR_Length_t
#include "ACR/public/public_memory.h"

/** predefined object type
*/
typedef struct ACR_CsvObj_s ACR_CsvObj_t;

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
extern "C" {                                              //
#endif                                                    //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
////////////////////////////////////////////////////////////

/** allocate data.
	\param mePtr location to store the pointer
    \param fileInterface the file interface to use.
                         this must exist for the life of
                         this object
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_CsvNew(
	ACR_CsvObj_t** mePtr,
    ACR_FileInterface_t* fileInterface);

/** free data
	\param mePtr location of the pointer, which will
	       be set to ACR_NULL after the memory is freed
*/
void ACR_CsvDelete(
	ACR_CsvObj_t** mePtr);

/** read string data from the specified row and column
    \param me the csv object
    \param row row index 0 to row count - 1
    \param column column index 0 to column count - 1
    \param value location to store a pointer to the string data
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_CsvReadCell(
	ACR_CsvObj_t* me,
    ACR_Count_t row,
    ACR_Count_t column,
    ACR_String_t** value);

/** read string data from the specified row
    \param me the csv object
    \param row row index 0 to row count - 1
    \param value location to store a pointer to the first column string data
    \param valueCount location to store the number of values found in the row (column count for this row)
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_CsvReadRow(
	ACR_CsvObj_t* me,
    ACR_Count_t row,
    ACR_String_t** value,
    ACR_Count_t* valueCount);

/** read string data from the specified column
    \param me the csv object
    \param column column index 0 to column count - 1
    \param value location to store a pointer to the first row string data
    \param valueCount location to store the number of values found in the column (row count for this column)
	\returns ACR_INFO_OK or ACR_INFO_ERROR
*/
ACR_Info_t ACR_CsvReadColumn(
	ACR_CsvObj_t* me,
    ACR_Count_t column,
    ACR_String_t** value,
    ACR_Count_t* valueCount);

////////////////////////////////////////////////////////////
// ALLOW FUNCTIONS TO BE CALLED FROM C++                  //
////////////////////////////////////////////////////////////
#ifdef __cplusplus                                        //
}                                                         //
#endif                                                    //
////////////////////////////////////////////////////////////

#endif
