// included for printf()
#include <stdio.h>

// defining ACR_CONFIG_NO_LIBC before including any ACR headers
// will configure the ACR library to avoid using standard libraries
// that come with the compiler.
// Note: normally it is best to define this as a compiler flag or
//       project setting and not directly within the code so that
//       the IDE knows which code will be used and the order that
//       source files are included is of no concern.
// Note: do not define this unless necessary. the standard libraries
//       include a lot of optimized code that will run significantly
//       faster on the system it is compiled for
//#define ACR_CONFIG_NO_LIBC

// defining ACR_CONFIG_NO_64BIT before any ACR headers
// will configure the ACR library to use 32bit integers.
// ACR_USE_64BIT will be ACR_BOOL_TRUE when 64bit is enabled
// Note: it is very important that this setting is correct.
//       the ACR_PointerValue_t type is based on this setting,
//       which means any pointer math performed by the ACR
//       library could cause critical runtime errors when not
//       configured properly.
// Note: unless ACR_CONFIG_NO_LIBC is defined, the standard libraries
//       will be used to determine this setting automatically
//#define ACR_CONFIG_NO_64BIT

#define TEXT_START "START        "
#define TEXT_END   "END          "
#define TEXT_ERROR "      ERROR  "
#define TEXT_OK    "             "

#define TEXT_TEST_FILE(fileName) "- - - - - - - " fileName " - - - - - - -\n"

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// public/public_bool.h                                                    //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#include "ACR/public/public_bool.h"
void ACR_HeaderTestPublicBool()
{
    ACR_Bool_t testBool;
    printf(TEXT_START TEXT_TEST_FILE("public/public_bool.h"));
    testBool = ACR_BOOL_FALSE;
    if(testBool)
    {
        printf(TEXT_ERROR "ACR_BOOL_FALSE should be false\n");
    }
    else
    {
        printf(TEXT_OK "ACR_BOOL_FALSE is false\n");
        if(testBool == ACR_BOOL_FALSE)
        {
            printf(TEXT_OK "ACR_BOOL_FALSE is an exact match\n");
            testBool = ACR_BOOL_TRUE;
            if(testBool)
            {
                printf(TEXT_OK "ACR_BOOL_TRUE is true\n");
                if(testBool == ACR_BOOL_TRUE)
                {
                    printf(TEXT_OK "ACR_BOOL_TRUE is an exact match\n");
                }
                else
                {
                    printf(TEXT_ERROR "ACR_BOOL_TRUE should be an exact match\n");
                }
            }
            else
            {
                printf(TEXT_ERROR "ACR_BOOL_TRUE should be true\n");
            }
        }
        else
        {
            printf(TEXT_ERROR "ACR_BOOL_FALSE should be an exact match\n");
        }
    }
    printf(TEXT_END TEXT_TEST_FILE("public/public_bool.h"));
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// public/public_functions.h                                               //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#include "ACR/public/public_functions.h"
ACR_TYPEDEF_CALLBACK(TestCallback_t, ACR_Bool_t)();
ACR_Bool_t ACR_HeaderTestCallback0();
ACR_Bool_t ACR_HeaderTestCallback1();
ACR_Bool_t ACR_HeaderTestCallback2();
ACR_Bool_t ACR_HeaderTestCallbackCount();
enum TestCallback_e
{
    TEST_CALLBACK_0 = 0, // ACR_HeaderTestCallback0
    TEST_CALLBACK_1,     // ACR_HeaderTestCallback1
    TEST_CALLBACK_2,     // ACR_HeaderTestCallback2
    TEST_CALLBACK_COUNT  // ACR_HeaderTestCallbackCount
};
const TestCallback_t g_TestCallback[TEST_CALLBACK_COUNT+1] =
{
    ACR_HeaderTestCallback0,    // TEST_CALLBACK_0
    ACR_HeaderTestCallback1,    // TEST_CALLBACK_1
    ACR_HeaderTestCallback2,    // TEST_CALLBACK_2
    ACR_HeaderTestCallbackCount // TEST_CALLBACK_COUNT
};
void ACR_HeaderTestPublicFunctions()
{
    const TestCallback_t* testCallback;
    ACR_Bool_t callbackResult;

    printf(TEXT_START TEXT_TEST_FILE("public/public_functions.h"));

    printf(TEXT_OK "testing callback function at index %d\n", TEST_CALLBACK_1);
    if(g_TestCallback[TEST_CALLBACK_1]())
    {
        printf(TEXT_OK "callback function returned true\n");
    }
    else
    {
        printf(TEXT_OK "callback function returned false\n");
    }

    printf(TEXT_OK "testing callback functions until the result is false\n");
    testCallback = &g_TestCallback[0];
    do
    {
        callbackResult = (*testCallback)();
        testCallback++;
    }
    while (callbackResult);
    
    printf(TEXT_END TEXT_TEST_FILE("public/public_functions.h"));
    printf("\n");
}
ACR_Bool_t ACR_HeaderTestCallback0() // TEST_CALLBACK_0
{
    printf(TEXT_OK "callback function 0\n");
    return ACR_BOOL_TRUE;
}
ACR_Bool_t ACR_HeaderTestCallback1() // TEST_CALLBACK_1
{
    printf(TEXT_OK "callback function 1\n");
    return ACR_BOOL_TRUE;
}
ACR_Bool_t ACR_HeaderTestCallback2() // TEST_CALLBACK_2
{
    printf(TEXT_OK "callback function 2\n");
    return ACR_BOOL_TRUE;
}
ACR_Bool_t ACR_HeaderTestCallbackCount() // TEST_CALLBACK_COUNT
{
    printf(TEXT_OK "no more callback functions\n");
    return ACR_BOOL_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// public/public_memory.h                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#include "ACR/public/public_memory.h"
void ACR_HeaderTestPublicMemory()
{
    unsigned char buffer[2][1024];
    ACR_Length_t bufferIndex;
    printf(TEXT_START TEXT_TEST_FILE("public/public_memory.h"));
    #if ACR_USE_64BIT == ACR_BOOL_TRUE
        printf(TEXT_OK "largest length value is %llu and sizeof(ACR_Length_t) is %d bytes\n", ACR_MAX_LENGTH, sizeof(ACR_Length_t));
    #else
        printf(TEXT_OK "largest length value is %lu and sizeof(ACR_Length_t) is %d bytes\n", ACR_MAX_LENGTH, sizeof(ACR_Length_t));
    #endif
    // ACR_CLEAR_MEMORY uses ACR_MEMSET to fill the buffer with ACR_EMPTY_VALUE
    ACR_CLEAR_MEMORY(buffer[0], sizeof(buffer[0]));
    bufferIndex = 0;
    do
    {
        if(buffer[0][bufferIndex] != ACR_EMPTY_VALUE)
        {
            printf(TEXT_ERROR "ACR_CLEAR_MEMORY failed at %d or the memory was corrupted after being cleared\n", (int)bufferIndex);
            // break out of this loop after encountering an error
            break;
        }
        bufferIndex++;
    }
    while (bufferIndex < sizeof(buffer[0])); 
    if(bufferIndex == sizeof(buffer[0]))
    {
        printf(TEXT_OK "ACR_CLEAR_MEMORY finished. buffer[0] is filled with ACR_EMPTY_VALUE\n");
    }
    buffer[0][0] = 'o';
    buffer[0][1] = 'k';
    buffer[0][2] = '\0';
    buffer[0][sizeof(buffer[0])-1] = '!';
    ACR_MEMCPY(buffer[1], buffer[0], sizeof(buffer[0]));
    if(buffer[1][sizeof(buffer[1])-1] == '!')
    {
        bufferIndex = 0;
        do
        {
            if(buffer[0][bufferIndex] != buffer[1][bufferIndex])
            {
                printf(TEXT_ERROR "ACR_MEMCPY failed at %d or the memory was corrupted after being copied\n", (int)bufferIndex);
                // break out of this loop after encountering an error
                break;
            }
            bufferIndex++;
        }
        while (bufferIndex < sizeof(buffer[0])); 
        if(bufferIndex == sizeof(buffer[0]))
        {
            printf(TEXT_OK "ACR_MEMCPY copied all bytes and null-terminated strings match: \"%s\" == \"%s\"\n", buffer[0], buffer[1]);
        }
    }
    else
    {
        printf(TEXT_ERROR "ACR_MEMCPY did not copy the last byte correctly\n");
    }
    printf(TEXT_END TEXT_TEST_FILE("public/public_memory.h"));
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// public/public_bytes_and_flags.h                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#include "ACR/public/public_bytes_and_flags.h"
void ACR_HeaderTestPublicBytesAndFlags()
{
    ACR_Flags_t flags;
    ACR_Flags_t flag;
    printf(TEXT_START TEXT_TEST_FILE("public/public_bytes_and_flags.h"));
    if(sizeof(ACR_Byte_t) == 1)
    {
        printf(TEXT_OK "ACR_Byte_t can store %d bits\n", ACR_BITS_PER_BYTE);
    }
    else
    {
        printf(TEXT_ERROR "ACR_Byte_t size should be 1 (not %d)\n", sizeof(ACR_Byte_t));
    }
    printf(TEXT_OK "each ACR_Flags_t variable can store %d flags\n", (sizeof(ACR_Flags_t) * ACR_BITS_PER_BYTE));
    flags = ACR_NO_FLAGS;
    printf(TEXT_OK "using ACR_ADD_FLAGS to set flags 4 and 7\n");
    ACR_ADD_FLAGS(flags, ACR_FLAG_FOUR | ACR_FLAG_SEVEN);
    if(ACR_HAS_ALL_FLAGS(flags, ACR_FLAG_FOUR | ACR_FLAG_ONE))
    {
        printf(TEXT_ERROR "flag 1 should not be set\n");
    }
    else
    {
        printf(TEXT_OK "ACR_HAS_ALL_FLAGS found that a flag is missing, as expected\n");
    }
    if(ACR_HAS_ONLY_FLAGS(flags, ACR_FLAG_FOUR))
    {
        printf(TEXT_ERROR "only flag 4 or none are set\n");
    }
    else
    {
        printf(TEXT_OK "ACR_HAS_ONLY_FLAGS found that a flag other than 4 is set\n");
    }
    if(ACR_HAS_FLAG(flags, ACR_FLAG_SEVEN))
    {
        printf(TEXT_OK "flag 7 is set\n");
    }
    else
    {
        printf(TEXT_ERROR "flag 7 is not set\n");
    }
    if(ACR_HAS_FLAG(flags, ACR_FLAG_THREE))
    {
        printf(TEXT_ERROR "flag 3 is set\n");
    }
    else
    {
        printf(TEXT_OK "flag 3 is not set\n");
    }
    printf(TEXT_OK "setting flag 3 by number using ACR_FLAG(n)\n");
    flag = ACR_FLAG(3);
    ACR_ADD_FLAGS(flags, flag);
    if(ACR_HAS_FLAG(flags, ACR_FLAG_THREE))
    {
        printf(TEXT_OK "ACR_HAS_FLAG found flag 3 is set\n");
    }
    else
    {
        printf(TEXT_ERROR "flag 3 is not set\n");
    }
    if(ACR_HAS_ANY_FLAGS(flags, ACR_FLAG_FOUR | ACR_FLAG_FIVE))
    {
        printf(TEXT_OK "ACR_HAS_ANY_FLAGS found flag 4 or flag 5 is set\n");
    }
    else
    {
        printf(TEXT_ERROR "neither flag 4 or flag 5 are set\n");
    }
    ACR_REMOVE_FLAGS(flags, ACR_FLAG_SEVEN);
    if(ACR_HAS_FLAG(flags, ACR_FLAG_SEVEN))
    {
        printf(TEXT_ERROR "flag 7 is still set\n");
    }
    else
    {
        printf(TEXT_OK "ACR_REMOVE_FLAGS has removed flag 7\n");
    }

    printf(TEXT_END TEXT_TEST_FILE("public/public_bytes_and_flags.h"));
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// public/public_bytes_and_flags.h                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#include "ACR/public/public_byte_order.h"
void ACR_HeaderTestPublicByteOrder()
{
    printf(TEXT_START TEXT_TEST_FILE("public/public_byte_order.h"));
    if(sizeof(ACR_16bit_t) == 2)
    {
        printf(TEXT_OK "ACR_16bit_t can store %d bits\n", (sizeof(ACR_16bit_t) * ACR_BITS_PER_BYTE));
    }
    else
    {
        printf(TEXT_ERROR "ACR_16bit_t size should be 2 (not %d)\n", sizeof(ACR_16bit_t));
    }
    if(sizeof(ACR_32bit_t) == 4)
    {
        printf(TEXT_OK "ACR_32bit_t can store %d bits\n", (sizeof(ACR_32bit_t) * ACR_BITS_PER_BYTE));
    }
    else
    {
        printf(TEXT_ERROR "ACR_32bit_t size should be 4 (not %d)\n", sizeof(ACR_32bit_t));
    }
    #if ACR_USE_64BIT == ACR_BOOL_TRUE
        if(sizeof(ACR_64bit_t) == 8)
        {
            printf(TEXT_OK "ACR_64bit_t can store %d bits\n", (sizeof(ACR_64bit_t) * ACR_BITS_PER_BYTE));
        }
        else
        {
            printf(TEXT_ERROR "ACR_64bit_t size should be 8 (not %d)\n", sizeof(ACR_64bit_t));
        }
    #else
        printf(TEXT_OK "ACR_64bit_t is not available on this platform\n");
    #endif

    #if ACR_IS_BIG_ENDIAN == ACR_BOOL_TRUE
        printf(TEXT_OK "platform is big endian\n");
    #else
        printf(TEXT_OK "platform is little endian\n");
    #endif

    printf(TEXT_END TEXT_TEST_FILE("public/public_byte_order.h"));
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// main.c                                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    printf("\n");
    printf(TEXT_OK "= = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
    printf(TEXT_OK "=                                                   =\n");
    printf(TEXT_OK "=                    ACR MAIN                       =\n");
    printf(TEXT_OK "=                                                   =\n");
    printf(TEXT_OK "=  ACR Library Configuration:                       =\n");
#ifdef ACR_CONFIG_NO_LIBC
    printf(TEXT_OK "=      - no standard C library                      =\n");
#else
    printf(TEXT_OK "=      - using standard C library                   =\n");
#endif
#if ACR_USE_64BIT == ACR_BOOL_TRUE
    printf(TEXT_OK "=      - 64bit mode                                 =\n");
#else
    printf(TEXT_OK "=      - 32bit mode                                 =\n");
#endif
#if ACR_IS_BIG_ENDIAN == ACR_BOOL_TRUE
    printf(TEXT_OK "=      - big endian                                 =\n");
#else
    printf(TEXT_OK "=      - little endian                              =\n");
#endif
    printf(TEXT_OK "=                                                   =\n");
    printf(TEXT_OK "= = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
    printf("\n");

    ACR_HeaderTestPublicBool();
    ACR_HeaderTestPublicFunctions();
    ACR_HeaderTestPublicMemory();
    ACR_HeaderTestPublicBytesAndFlags();
    ACR_HeaderTestPublicByteOrder();

    return 0;
}