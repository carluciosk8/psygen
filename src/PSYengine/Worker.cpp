/**************************************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
    email:      carlucio@gmail.com

    This file is part of PSYGEN

    PSYGEN is free software: you can redistribute it and/or modify it under the terms of the GNU
    Lesser General Public License as published by the Free Software Foundation, either version 3
    of the License, or (at your option) any later version.

    PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
    even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with PSYGEN.
    If not, see <http://www.gnu.org/licenses/>

---------------------------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief  __________
    *  \ingroup  __________
    *
    *//*******************************************************************************************/
#include "PSYGEN/PSYengine/Worker.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


Worker::Worker()
:
    Thread<Worker>(),
    m_bIsRunning(false),
    m_oSemaphore(),
    m_oJobList()
{
}



Worker::~Worker()
{
}



void Worker::addJob(Object* opJob)
{
    m_oJobList.push(opJob);
    m_oSemaphore.post();
}



void Worker::run()
{
    printf( "starting worker %p ... \n", this );

    //m_opSemaphore = SDL_CreateSemaphore(0);
    m_bIsRunning = true;

    this->onStart();

    while ( m_bIsRunning )
    {
        if ( ! m_oJobList.empty() )
        {
//            m_oJobList.front()->amplify();
            m_oJobList.pop();
            m_oSemaphore.wait();
        }
        else
        {
            m_oSemaphore.wait();
        }

        if ( m_oJobList.empty() )
            printf("worker %p in buzy waiting ...\n", this);
    }

    this->onStop();

    //SDL_DestroySemaphore(m_opSemaphore);

    printf( "stopping worker %p\n", this );
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
