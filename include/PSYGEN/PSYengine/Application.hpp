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
#ifndef __PSYGEN_APPLICATION_H__
#define __PSYGEN_APPLICATION_H__

#include <string>
#include <AntTweakBar.h>

#include "PSYGEN/PSYengine/Main_Window.hpp"
#include "PSYGEN/PSYengine/Clock.hpp"
#include "PSYGEN/PSYengine/EventManager.hpp"
#include "PSYGEN/PSYengine/EventHandler.hpp"
#include "PSYGEN/PSYengine/Object.hpp"

namespace psy {////////////////////////////////////////////////////////////////

class PSYAPI Application
{
public:
             Application(int argc, char** argv);
    virtual ~Application();

    int run();
    void stop();
    virtual void step() = 0;

protected:
    //config
    std::string  m_sWindow_Title;
    int  m_iWidth;
    int  m_iHeight;
    int  m_iNum_Modelers;
    bool m_bFull_Screen;

    // Subsystems
    Main_Window          m_oWnd;
    Clock                m_oClock;
    EventManager         m_oEventManager;

    bool     m_Running;
};

DeclareEventHandler(QuitHandler, Application);


}//////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_APPLICATION_H__
