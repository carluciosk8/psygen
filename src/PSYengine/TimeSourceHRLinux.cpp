/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2008 by Carlucio Santos Cordeiro
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
#include "PSYGEN/PSYengine/TimeSourceHRLinux.hpp"


namespace psy {////////////////////////////////////////////////////////////////////////////////////


TimeSourceHRLinux::TimeSourceHRLinux()
{
    gettimeofday(&start_time, (struct timezone*)0);
}


double TimeSourceHRLinux::getTime() const
{
    struct timeval end_time;

    gettimeofday(&end_time, (struct timezone*)0);

    return (end_time.tv_usec-start_time.tv_usec)*0.000001 + (end_time.tv_sec-start_time.tv_sec);
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
