/*

    ********** DO NOT REMOVE THIS INFORMATION ************

    ACR - A set of C functions in a git Repository
    Copyright (C) 2018 - 2021 Adam C. Rosenberg

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

/** \file public_callbacks.h
 
    This header makes defining callback function types easy.
    It can be used standalone from the entire library or
    is included automatically with public.h

    See public.h for more information.

*/
#ifndef _ACR_PUBLIC_CALLBACKS_H_
#define _ACR_PUBLIC_CALLBACKS_H_

/** defines a callback function type
    \param t the name of the type to define
    \param r the return type or void if there is none
  
	example:

        // define a list of all callback names
        enum CallbackExample_e
        {
            CBEX_1 = 0,
            CBEX_2,
            CBEX_3,

            CBEX_COUNT
        };

        // define the callback function prototypes
        ACR_TYPEDEF_CALLBACK(CallbackExample_t, void)(int, void*);
            void CbEx1(int,void*);
            void CbEx2(int,void*);
            void CbEx3(int,void*);

        // create a lookup table of the callback functions
        CallbackExample_t g_CbEx[CBEX_COUNT+1] = 
        {
            CbEx1, // CBEX_1
            CbEx2, // CBEX_2
            CbEx3, // CBEX_3

            ACR_NULL
        };

        int main()
        {
            unsigned int cbIndex;

            // just use one callback function
            g_CbEx[CBEX_1](0, ACR_NULL);

            // loop through all callback functions
            cbIndex = 0;
            while(cbIndex < CBEX_COUNT)
            {
                g_CbEx[cbIndex](cbIndex, ACR_NULL);
                cbIndex++;
            }

            return ACR_SUCCESS;
        }

        // complete the definition of the first callback function
        void CbEx1(int a, void* b)
        {
            ACR_UNUSED(a);
            ACR_UNUSED(b);
            ACR_DEBUG_PRINT(1,"One");
        }

        // complete the definition of the second callback function
        void CbEx2(int a, void* b)
        {
            ACR_UNUSED(a);
            ACR_UNUSED(b);
            ACR_DEBUG_PRINT(2,"Two");
        }
        
        // complete the definition of the third callback function
        void CbEx3(int a, void* b)
        {
            ACR_UNUSED(a);
            ACR_UNUSED(b);
            ACR_DEBUG_PRINT(3,"Three");
        }

*/
#define ACR_TYPEDEF_CALLBACK(t,r) typedef r (*t)

#endif
