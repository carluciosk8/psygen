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
#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__


#include <vector>
#include <list>
#include <SDL/SDL.h>

#include "PSYGEN/PSYGEN.hpp"

namespace psy {////////////////////////////////////////////////////////////////

class EventHandlerCallback;

class PSYAPI EventManager
{
    public:
        EventManager();
        ~EventManager();

		void registerHandler(Uint8 type, EventHandlerCallback*);
        void unregisterHandler(Uint8 type, const EventHandlerCallback*);
		void executeNext();
		void executeAll();
		void shutdown();


    protected:
		SDL_Event  m_oLastEvent;
		std::vector< std::vector<EventHandlerCallback*> >  m_oHandlerTable;
		std::list<Uint8> m_Registered_List;
};

}//////////////////////////////////////////////////////////////////////////////

#endif
