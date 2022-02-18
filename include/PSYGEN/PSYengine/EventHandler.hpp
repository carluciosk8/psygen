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
#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__


#include <functional>
#include <SDL/SDL.h>

namespace psy {////////////////////////////////////////////////////////////////


class EventHandlerCallback : public std::unary_function<SDL_Event, void>
{
    public:
		virtual void operator()(SDL_Event event)=0;
};



template <class Listener>
class  EventHandler : public EventHandlerCallback
{
    public:
		EventHandler(Listener* opListener) : m_opListener(opListener){}
		Listener* getListener()  {return m_opListener;}

	private:
		Listener*  m_opListener;
};


}//////////////////////////////////////////////////////////////////////////////


#define DeclareEventHandler(HANDLER, LISTENER)               \
class LISTENER;                                              \
class HANDLER : public psy::EventHandler<LISTENER>           \
{                                                            \
public:                                                      \
	HANDLER(LISTENER* p) : psy::EventHandler<LISTENER>(p) {}      \
	virtual void operator()(SDL_Event);                      \
}


#define ImplementEventHandler(HANDLER, EVENT)           \
void HANDLER::operator()(SDL_Event EVENT)


#endif
