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
#ifndef __TIMER_H__
#define __TIMER_H__


#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYengine/Observer.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class Clock;

class PSYAPI Timer : private IObserver
{
    public:
        Timer(Clock & clock);
        virtual ~Timer();

        inline double getTime() const  { return m_currentTime; }
        inline double getFrameDuration() const  { return m_frameTime; }

        void pause (bool bOn)  { m_bPaused = bOn; }
        void setScale (float fScale)  { m_fScale = fScale; }

        bool isPaused () const  { return m_bPaused; }
        float getScale () const  { return m_fScale; }


    private:
        virtual void notify();

        Clock & m_clock;

        double  m_currentTime;
        double  m_frameTime;

        bool    m_bPaused;
        float   m_fScale;
};

}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif
