/**************************************************************************************************
---------------------------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief  A system independent clock. returns the number of seconds since its construction
    *  \ingroup PSYengine
    *
    *//*******************************************************************************************/
#pragma once

#include "Engine/Singleton.hpp"


namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Clock : public Singleton<Clock>
{
public:
    Clock() : Singleton() {}
    virtual ~Clock() {}

    inline double get_time() const { return (*time_fptr)(); }

protected:
    static double (*time_fptr)();
};


}//////////////////////////////////////////////////////////////////////////////////////////////////


#define g_clock Clock::GetSingleton()
