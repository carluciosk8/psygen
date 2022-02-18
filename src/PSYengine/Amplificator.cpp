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
    *  \brief
    *  \ingroup PSYengine
    *
    *//*******************************************************************************************/

#include "PSYGEN/PSYengine/Amplificator.hpp"
#include "PSYGEN/PSYengine/Attribute.hpp"
#include "PSYGEN/PSYengine/Geometry.hpp"
#include "PSYGEN/PSYengine/Node.hpp"
#ifdef PSYGEN_PLATFORM_LINUX
#   include "PSYGEN/PSYengine/OpenGL_Context_GLX.hpp"
#elif PSYGEN_PLATFORM_OSX
#   include "PSYGEN/PSYengine/OpenglContextCgl.hpp"
#elif PSYGEN_PLATFORM_WINDOWS
#   include "PSYGEN/PSYengine/OpenglContextWgl.hpp"
#endif

namespace psy {////////////////////////////////////////////////////////////////////////////////////

Mutex Amplificator::m_oMutex;

Amplificator::Amplificator(uint uiNumModelers, OpenglContext* main_gl_context)
:
	m_is_running(false),
	m_is_working(false),
    m_opSharedOpenglContext(NULL),
    m_opMainOpenglContext(main_gl_context),
    m_oSemaphore(),
    m_pending_models(0),
    m_uiCurrentModeler(0),
    m_oModelers(uiNumModelers)
{
	start();
    m_oModelers.resize(uiNumModelers);
    for (uint i=0; i<uiNumModelers; i++)
        m_oModelers[i] = new Modeler(&m_oMutex, main_gl_context);
}



Amplificator::~Amplificator()
{
    for (uint i=0; i<m_oModelers.size(); i++)
        delete m_oModelers[i];

    m_oModelers.clear();
}



void Amplificator::run()
{
    #ifdef PSYGEN_PLATFORM_LINUX
    m_opSharedOpenglContext = new OpenglContextGlx();
    #elif PSYGEN_PLATFORM_OSX
    m_opSharedOpenglContext = new OpenglContextCgl();
    #elif PSYGEN_PLATFORM_WINDOWS
    m_opSharedOpenglContext = new OpenglContextWgl();
    #endif

    assert( m_opMainOpenglContext );
    m_opSharedOpenglContext->openContext( m_opMainOpenglContext );
    glFlush();

	m_is_running = true;
	while (m_is_running)
    {
		m_is_working = false;
		m_oSemaphore.wait();
		if (m_is_running)
			this->inspect(m_npScene);
	}

    m_opSharedOpenglContext->closeContext();
    delete m_opSharedOpenglContext;
}



void Amplificator::inspect(Node* node)
{
    if ( m_npCamera->bound_is_nearby(node->world_bound) )
    {
        requestModel(node);

        for ( std::list<Geometry*>::iterator
        i_geom  = node->get_geometry_list().begin();
        i_geom != node->get_geometry_list().end();
        ++i_geom )
            if ( m_npCamera->bound_is_nearby((*i_geom)->world_bound) )
                requestModel(*i_geom);

        for ( std::list<Attribute*>::iterator
        i_attr  = node->get_attribute_list().begin();
        i_attr != node->get_attribute_list().end();
        ++i_attr )
            requestModel(*i_attr);
    }
    else
    {
		if (node->get_state() == Object::AMPLIFIED)
			node->shrink(&m_oMutex);

        for ( std::list<Geometry*>::iterator
        i_geom  = node->get_geometry_list().begin();
        i_geom != node->get_geometry_list().end();
        ++i_geom )
			if ((*i_geom)->get_state() == Object::AMPLIFIED)
				(*i_geom)->shrink(&m_oMutex);

        for ( std::list<Attribute*>::iterator
        i_attr  = node->get_attribute_list().begin();
        i_attr != node->get_attribute_list().end();
        ++i_attr )
			if ((*i_attr)->get_state() == Object::AMPLIFIED)
				(*i_attr)->shrink(&m_oMutex);
    }

    node->accept(this);
}



void Amplificator::init()
{
//     glXWaitX();
//     XFlush( glXGetCurrentDisplay() );
//     glXWaitGL();
//     glFlush();

    for (uint i=0; i<m_oModelers.size(); i++)
        m_oModelers[i]->start();

//    glXWaitX();
//    XFlush( glXGetCurrentDisplay() );
//    glXWaitGL();
//    glFlush();
    SDL_Delay(1000);  // TODO: discover the best manner of makes the threads waiting to be ready for starts gracefully
}


void Amplificator::wait()
{
    for (uint i=0; i<m_oModelers.size(); i++)
        m_oModelers[i]->wait();

	Thread<Amplificator>::wait();
}



void Amplificator::stop()
{
	m_is_running=false;
	m_oSemaphore.post();

    for (uint i=0; i<m_oModelers.size(); i++)
        m_oModelers[i]->stop();
}



void Amplificator::requestModel(Object* opModel)
{
    if (opModel->get_state() == Object::SHRINKED)
    {
        m_oMutex.lock();
        opModel->m_eState = Object::AMPLIFYING;
        m_oModelers[m_uiCurrentModeler]->addJob(opModel);
        m_oMutex.unlock();
        this->scheduleNextWorker();
    }
}



void Amplificator::scheduleNextWorker()
{
    m_uiCurrentModeler = (m_uiCurrentModeler + 1) % m_oModelers.size();
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
