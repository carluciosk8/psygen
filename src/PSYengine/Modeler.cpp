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
#include <cassert>

#include "PSYGEN/PSYengine/Main_Window.hpp"
#ifdef PSYGEN_PLATFORM_LINUX
#   include "PSYGEN/PSYengine/OpenGL_Context_GLX.hpp"
#elif PSYGEN_PLATFORM_OSX
#   include "PSYGEN/PSYengine/OpenglContextCgl.hpp"
#elif PSYGEN_PLATFORM_WINDOWS
#   include "PSYGEN/PSYengine/OpenglContextWgl.hpp"
#endif
#include "PSYGEN/PSYengine/Mutex.hpp"
#include "PSYGEN/PSYengine/Modeler.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


Modeler::Modeler(Mutex* opMutex, OpenglContext*  main_gl_context)
:
    Thread<Modeler>(),
    m_bIsRunning(false),
    m_oSemaphore(),
    m_opMutex(opMutex),
    m_opSharedOpenglContext(NULL),
    m_opMainOpenglContext(main_gl_context),
    m_oJobList()
{
}



Modeler::~Modeler()
{
}



void Modeler::addJob(Object* opJob)
{
    m_opMutex->lock();
    m_oJobList.push(opJob);
    m_opMutex->unlock();
    m_oSemaphore.post();
}



void Modeler::run()
{
    m_bIsRunning = true;

    this->onStart();

    while ( m_bIsRunning || ! m_oJobList.empty() )
    {
        if ( ! m_oJobList.empty() )
        {
            //printf("modeler %p is generating object: %s ...\n", this, m_oJobList.front()->get_name());
            m_oJobList.front()->amplify(m_opMutex);
            m_opMutex->lock();
            m_oJobList.pop();
            m_opMutex->unlock();
            m_oSemaphore.wait();
        }
        else
        {
            //printf("modeler %p is waiting ...\n", this);
            m_oSemaphore.wait();
        }
    }

    this->onStop();
}



void Modeler::onStart()
{
    #ifdef PSYGEN_PLATFORM_LINUX
    m_opSharedOpenglContext = new OpenglContextGlx();
    #elif PSYGEN_PLATFORM_OSX
    m_opSharedOpenglContext = new OpenglContextCgl();
    #elif PSYGEN_PLATFORM_WINDOWS
    m_opSharedOpenglContext = new OpenglContextWgl();
    #endif

    //glFlush();
    m_opMutex->lock();
    assert( m_opMainOpenglContext );
    m_opSharedOpenglContext->openContext( m_opMainOpenglContext );
    m_opMutex->unlock();
    glFlush();
/*    glXWaitX();
    glXWaitGL();*/
}



void Modeler::onStop()
{
    m_opMutex->lock();
    m_opSharedOpenglContext->closeContext();
    m_opMutex->unlock();
    //glFlush();

    delete m_opSharedOpenglContext;
}


Destructor::Destructor(Mutex* opMutex, OpenglContext*  main_gl_context)
:
    Thread<Destructor>(),
    m_bIsRunning(false),
    m_oSemaphore(),
    m_opMutex(opMutex),
    m_opSharedOpenglContext(NULL),
    m_opMainOpenglContext(main_gl_context),
    m_oJobList()
{
}



Destructor::~Destructor()
{
}



void Destructor::addJob(Object* opJob)
{
    m_opMutex->lock();
    m_oJobList.push(opJob);
    m_opMutex->unlock();
    m_oSemaphore.post();
}



void Destructor::run()
{
    m_bIsRunning = true;

    this->onStart();

    while ( m_bIsRunning || ! m_oJobList.empty() )
    {
        if ( ! m_oJobList.empty() )
        {
            //printf("destructor %p is shrinking object: %s ...\n", this, m_oJobList.front()->get_name());
            m_oJobList.front()->shrink(m_opMutex);
            m_opMutex->lock();
            m_oJobList.pop();
            m_opMutex->unlock();
            m_oSemaphore.wait();
        }
        else
        {
            //printf("destructor is waiting ...\n");
            m_oSemaphore.wait();
        }
    }

    this->onStop();
}



void Destructor::onStart()
{
    #ifdef PSYGEN_PLATFORM_LINUX
    m_opSharedOpenglContext = new OpenglContextGlx();
    #elif PSYGEN_PLATFORM_OSX
    m_opSharedOpenglContext = new OpenglContextCgl();
    #elif PSYGEN_PLATFORM_WINDOWS
    m_opSharedOpenglContext = new OpenglContextWgl();
    #endif

    //glFlush();
    m_opMutex->lock();
    assert( m_opMainOpenglContext );
    m_opSharedOpenglContext->openContext( m_opMainOpenglContext );
    m_opMutex->unlock();
    //glFlush();
}



void Destructor::onStop()
{
    m_opMutex->lock();
    m_opSharedOpenglContext->closeContext();
    m_opMutex->unlock();
    //glFlush();

    delete m_opSharedOpenglContext;
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
