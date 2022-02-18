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
#ifndef __PSYGEN_AMPLIFICATOR_H__
#define __PSYGEN_AMPLIFICATOR_H__

#include <vector>
#include <queue>

#include "PSYGEN/PSYengine/Visitor.hpp"
#include "PSYGEN/PSYengine/Singleton.hpp"
#include "PSYGEN/PSYengine/Camera.hpp"
#include "PSYGEN/PSYengine/Modeler.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"
#include "PSYGEN/PSYengine/Object.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class Amplificator
:
public Thread<Amplificator>,
public Singleton<Amplificator>,
public Visitor
{
public:
             Amplificator(uint uiNumModelers, OpenglContext* main_gl_context);
    virtual ~Amplificator();

    virtual void run();
    virtual void inspect(Node*);
    inline void amplify(Node* npScene, Camera* npCam)
    {
        m_npCamera = npCam;
        m_npScene = npScene;
		m_oSemaphore.post();
		m_is_working = true;
    }
    void init();
	void wait();
    void stop();
    void requestModel(Object*);
    uint getNumModelers() { return m_oModelers.size(); }
    Modeler* getModeler(uint i) { return m_oModelers[i]; }
    inline uint get_modelers_size()
    {
        uint pending_objects = 0;
        for (uint i=0 ; i<getNumModelers() ; ++i)
            pending_objects += m_oModelers[i]->getJobListSize();
        return pending_objects;
    }

	inline bool is_working() {return m_is_working;}



    static Mutex  m_oMutex;

protected:
    void scheduleNextWorker();

private:
	bool            m_is_running;
	bool            m_is_working;
    OpenglContext*  m_opSharedOpenglContext;
    OpenglContext*  m_opMainOpenglContext;
	Semaphore   m_oSemaphore;
    Camera*     m_npCamera;
    Node*       m_npScene;
    uint        m_pending_models;
    uint        m_uiCurrentModeler;
    std::vector<Modeler*>  m_oModelers;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_AMPLIFICATOR_H__
