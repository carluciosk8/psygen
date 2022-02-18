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
#ifndef __PSYGEN_MODELER_H__
#define __PSYGEN_MODELER_H__

#include <queue>

#include "PSYGEN/PSYengine/Thread.hpp"
#include "PSYGEN/PSYengine/Semaphore.hpp"
#include "PSYGEN/PSYengine/Object.hpp"
//#include "PSYGEN/PSYengine/Worker.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Mutex;
class OpenglContext;

class Modeler : public Thread<Modeler>
{
public:
             Modeler(Mutex*, OpenglContext*);
    virtual ~Modeler();

    virtual void run();
    virtual void onStart();
    virtual void onStop();

    void stop      () { m_bIsRunning = false; m_oSemaphore.post(); }
    bool isRunning () { return m_bIsRunning; }
    uint getJobListSize() { return m_oJobList.size(); }
    void addJob(Object*);

private:
    bool            m_bIsRunning;
    Semaphore       m_oSemaphore;
    Mutex*          m_opMutex;
    OpenglContext*  m_opSharedOpenglContext;
    OpenglContext*  m_opMainOpenglContext;

    std::queue<Object*>  m_oJobList;
};


class Destructor : public Thread<Destructor>
{
public:
             Destructor(Mutex*, OpenglContext*);
    virtual ~Destructor();

    virtual void run();
    virtual void onStart();
    virtual void onStop();

    void stop      () { m_bIsRunning = false; m_oSemaphore.post(); }
    bool isRunning () { return m_bIsRunning; }
    uint getJobListSize() { return m_oJobList.size(); }
    void addJob(Object*);

private:
    bool            m_bIsRunning;
    Semaphore       m_oSemaphore;
    Mutex*          m_opMutex;
    OpenglContext*  m_opSharedOpenglContext;
    OpenglContext*  m_opMainOpenglContext;

    std::queue<Object*>  m_oJobList;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_MODELER_H__
