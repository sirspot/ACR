/** \file counter.c

    Functions for accessing global and local counters.

*/
#include "ACR/counter.h"

// included for ACR_UNUSED
#include "ACR/public/public_functions.h"

ACR_COUNTER(g_ACRGlobalCounter, ACR_ZERO_COUNT, (ACR_MAX_COUNT-1), ACR_ZERO_COUNT);

ACR_Count_t ACR_GlobalCounter(void)
{
    ACR_Count_t value;
    ACR_COUNTER_CURRENT(g_ACRGlobalCounter, value);
    return value;
}

ACR_Bool_t ACR_GlobalCounterNext(
    ACR_Count_t* value)
{
    ACR_Bool_t ok;
    ACR_COUNTER_NEXT(g_ACRGlobalCounter, (*value), ok);
    return ok;
}

ACR_Bool_t ACR_CounterFirst(
    ACR_Counter_t* me,
    ACR_Count_t* value)
{
    ACR_Bool_t ok;
    if(me)
    {
        if(ACR_COUNTER_IS_VALID((*me)))
        {
            ACR_COUNTER_RESET((*me));
            if(value)
            {
                ACR_COUNTER_CURRENT((*me), (*value));
            }
            ok = ACR_BOOL_TRUE;
        }
        else
        {
            ok = ACR_BOOL_FALSE;
        }
    }
    else
    {
        ok = ACR_BOOL_FALSE;
    }
    return ok;
}

ACR_Bool_t ACR_CounterNext(
    ACR_Counter_t* me,
    ACR_Count_t* value)
{
    ACR_Bool_t ok;
    if(value)
    {
        ACR_COUNTER_NEXT((*me), (*value), ok);
    }
    else
    {
        ACR_Count_t tempValue;
        ACR_COUNTER_NEXT((*me), tempValue, ok);
        ACR_UNUSED(tempValue);
    }
    return ok;
}
