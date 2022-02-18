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
#ifndef __PSYGEN_THREAD_H__
#define __PSYGEN_THREAD_H__

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

namespace psy {////////////////////////////////////////////////////////////////////////////////////


template <class T>
class Thread
{
public:
             Thread() : m_sdl_thread ( NULL ) {}
    virtual ~Thread() {}

    inline  void start () { m_sdl_thread = SDL_CreateThread( run_wrapper, this ); }
    inline  void wait  () { SDL_WaitThread( m_sdl_thread, NULL ); }
    inline  void kill  () { SDL_KillThread( m_sdl_thread ); }

    virtual void run   () = 0;

private:
    SDL_Thread*  m_sdl_thread;
    static int run_wrapper ( void* pthis ) { static_cast<T*>(pthis)->run(); return 0; }
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_THREAD_H__
