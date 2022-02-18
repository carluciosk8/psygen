/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
    email:      carlucio@gmail.com

    This file is part of PSYGEN

    PSYGEN is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with PSYGEN. If not, see <http://www.gnu.org/licenses/>

-------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief
    *  \ingroup PSYengine
    *
    *//***********************************************************************/
#ifndef TIMESOURCEHRLINUX_H_
#define TIMESOURCEHRLINUX_H_


#include "PSYGEN/PSYengine/TimeSource.hpp"

#include <sys/time.h>

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class TimeSourceHRLinux : public TimeSource
{
public:
    TimeSourceHRLinux();
    virtual double getTime() const;

private:
    struct timeval start_time;
};

}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif
