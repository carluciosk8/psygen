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
#ifndef __PSYGEN_WORKER_H__
#define __PSYGEN_WORKER_H__

#include <vector>
#include <queue>

#include "PSYGEN/PSYengine/Thread.hpp"
#include "PSYGEN/PSYengine/Semaphore.hpp"
#include "PSYGEN/PSYengine/Object.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Worker : public Thread<Worker>
{
    public:
        Worker();
        virtual ~Worker();

        virtual void run();
        virtual void onStart() = 0;
        virtual void onStop() = 0;

        void stop() { m_bIsRunning = false; }
        bool isRunning() { return m_bIsRunning; }
        uint getJobListSize() { return m_oJobList.size(); }
        void addJob(Object*);


    private:
        bool  m_bIsRunning;
        Semaphore  m_oSemaphore;
        std::queue<Object*>  m_oJobList;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_WORKER_H__
