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
#ifndef __PSYGEN_MUTEX_H__
#define __PSYGEN_MUTEX_H__

#include <stdexcept>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Mutex
{
public:
     Mutex() { m_opMutex = SDL_CreateMutex(); }
    ~Mutex() { SDL_DestroyMutex(m_opMutex); }

    void lock   () { if ( SDL_mutexP(m_opMutex) == -1 ) throw std::runtime_error( "Couldn't lock mutex" ); }
    void unlock () { if ( SDL_mutexV(m_opMutex) == -1 ) throw std::runtime_error( "Couldn't unlock mutex" ); }


private:
    SDL_mutex*  m_opMutex;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_MUTEX_H__
