/** \file info.c

    Functions for converting informational values to and from strings.

*/
#include "ACR/info.h"

// included for ACR_StringCompareToMemory and ACR_StringFromReadOnlyMemory
#include "ACR/common.h"

// included for ACR_INFO_STR_*
#include "ACR/public/public_unique_strings.h"

/** info string lookup table
*/
static const char* g_ACRInfoStringLookup[ACR_INFO_COUNT+1] =
{
    //
    // COMPARISON
    //
    ACR_INFO_STR_EQUAL,     // ACR_INFO_EQUAL
    ACR_INFO_STR_NOT_EQUAL, // ACR_INFO_NOT_EQUAL
    ACR_INFO_STR_LESS,      // ACR_INFO_LESS
    ACR_INFO_STR_GREATER,   // ACR_INFO_GREATER
    ACR_INFO_STR_UNKNOWN,   // ACR_INFO_UNKNOWN
    ACR_INFO_STR_UNDEFINED, // ACR_INFO_UNDEFINED

    //
    // POSITIVE, NEGATIVE
    //
    ACR_INFO_STR_TRUE,      // ACR_INFO_TRUE
    ACR_INFO_STR_FALSE,     // ACR_INFO_FALSE
    ACR_INFO_STR_OK,        // ACR_INFO_OK
    ACR_INFO_STR_ERROR,     // ACR_INFO_ERROR
    ACR_INFO_STR_ENABLED,   // ACR_INFO_ENABLED
    ACR_INFO_STR_DISABLED,  // ACR_INFO_DISABLED
    ACR_INFO_STR_YES,       // ACR_INFO_YES
    ACR_INFO_STR_NO,        // ACR_INFO_NO
    ACR_INFO_STR_ON,        // ACR_INFO_ON
    ACR_INFO_STR_OFF,       // ACR_INFO_OFF
    ACR_INFO_STR_START,     // ACR_INFO_START
    ACR_INFO_STR_STOP,      // ACR_INFO_STOP
    ACR_INFO_STR_ACCEPT,    // ACR_INFO_ACCEPT
    ACR_INFO_STR_IGNORE,    // ACR_INFO_IGNORE
    ACR_INFO_STR_VALID,     // ACR_INFO_VALID
    ACR_INFO_STR_INVALID,   // ACR_INFO_INVALID
    ACR_INFO_STR_ALL,       // ACR_INFO_ALL
    ACR_INFO_STR_NONE,      // ACR_INFO_NONE
    ACR_INFO_STR_FULL,      // ACR_INFO_FULL
    ACR_INFO_STR_EMPTY,     // ACR_INFO_EMPTY
    ACR_INFO_STR_OPEN,      // ACR_INFO_OPEN
    ACR_INFO_STR_CLOSED,    // ACR_INFO_CLOSED

    //
    // POSITION
    //
    ACR_INFO_STR_TOP,       // ACR_INFO_TOP
    ACR_INFO_STR_BOTTOM,    // ACR_INFO_BOTTOM
    ACR_INFO_STR_FIRST,     // ACR_INFO_FIRST
    ACR_INFO_STR_LAST,      // ACR_INFO_LAST
    ACR_INFO_STR_PREVIOUS,  // ACR_INFO_PREVIOUS
    ACR_INFO_STR_NEXT,      // ACR_INFO_NEXT
    ACR_INFO_STR_CURRENT,   // ACR_INFO_CURRENT

    // DIRECTION
    ACR_INFO_STR_UP,        // ACR_INFO_UP
    ACR_INFO_STR_DOWN,      // ACR_INFO_DOWN
    ACR_INFO_STR_LEFT,      // ACR_INFO_LEFT
    ACR_INFO_STR_RIGHT,     // ACR_INFO_RIGHT

    // AGE
    ACR_INFO_STR_OLD,       // ACR_INFO_OLD
    ACR_INFO_STR_NEW,       // ACR_INFO_NEW

    // INSTRUCTION
    ACR_INFO_STR_BEGIN,     // ACR_INFO_BEGIN
    ACR_INFO_STR_READY,     // ACR_INFO_READY
    ACR_INFO_STR_WAIT,      // ACR_INFO_WAIT
    ACR_INFO_STR_GO,        // ACR_INFO_GO
    ACR_INFO_STR_END,       // ACR_INFO_END

    // MODE
    ACR_INFO_STR_READ,      // ACR_INFO_READ
    ACR_INFO_STR_WRITE,     // ACR_INFO_WRITE
    ACR_INFO_STR_READ_WRITE,// ACR_INFO_READ_WRITE

    ""                      // ACR_INFO_COUNT
};

ACR_String_t ACR_InfoToString(
    ACR_Info_t info)
{
    return ACR_StringFromReadOnlyMemory((const ACR_Byte_t*)g_ACRInfoStringLookup[info], ACR_MAX_LENGTH, ACR_MAX_COUNT);
}

ACR_Info_t ACR_InfoFromString(
    ACR_String_t src)
{
    ACR_Count_t i = 0;
    ACR_Info_t x;
    do
    {
        x = ACR_StringCompareToMemory(src, (const ACR_Byte_t*)g_ACRInfoStringLookup[i], ACR_MAX_LENGTH, ACR_MAX_COUNT, ACR_INFO_NO);
        if(x == ACR_INFO_EQUAL)
        {
            return (ACR_Info_t)i;
        }
        i++;
    }
    while(i < ACR_INFO_COUNT);
    return ACR_INFO_UNKNOWN;
}
