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
#include <AntTweakBar.h>
#include <iostream>

#include "PSYGEN/PSYengine/EventManager.hpp"
#include "PSYGEN/PSYengine/EventHandler.hpp"

namespace psy {////////////////////////////////////////////////////////////////


EventManager::EventManager()
{
	m_oHandlerTable.resize(256);
}



EventManager::~EventManager()
{
    shutdown();
}



void EventManager::executeNext()
{
    if ( SDL_PollEvent(&m_oLastEvent) )
        if( ! TwEventSDL(&m_oLastEvent, 1, 2) )
            for (unsigned int i = 0;  i < m_oHandlerTable[m_oLastEvent.type].size();  ++i)
                (*(m_oHandlerTable[m_oLastEvent.type][i]))(m_oLastEvent);
}



void EventManager::executeAll()
{
    while ( SDL_PollEvent(&m_oLastEvent) )
        if( ! TwEventSDL(&m_oLastEvent, 1, 2) )
            for(unsigned int i = 0; i < m_oHandlerTable[m_oLastEvent.type].size(); ++i)
                (*(m_oHandlerTable[m_oLastEvent.type][i]))(m_oLastEvent);
}


void EventManager::shutdown()
{
    for (std::list<Uint8>::iterator type = m_Registered_List.begin() ; type != m_Registered_List.end() ; ++type)
    {
        for (std::vector<EventHandlerCallback*>::iterator cb = m_oHandlerTable[*type].begin() ; cb != m_oHandlerTable[*type].end() ; ++cb)
        {
            delete *cb;
        }
        m_oHandlerTable[*type].clear();
    }

    m_oHandlerTable.clear();
    m_Registered_List.clear();
}


void EventManager::unregisterHandler(Uint8 type, const EventHandlerCallback *handler)
{
    for (std::vector<EventHandlerCallback*>::iterator it ; it != m_oHandlerTable[type].end() ; ++it)
    {
        m_oHandlerTable[type].erase(it);
        break;
    }
}


void EventManager::registerHandler(Uint8 type, EventHandlerCallback *handler)
{
    m_oHandlerTable[type].push_back(handler);
    m_Registered_List.push_back(type);
}



}//////////////////////////////////////////////////////////////////////////////
