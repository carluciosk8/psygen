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
#ifndef __PSYGEN_SEMAPHORE_H__
#define __PSYGEN_SEMAPHORE_H__

#include <stdexcept>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Semaphore
{
public:
     Semaphore (uint s=0) { m_opSemaphore = SDL_CreateSemaphore(s); }
    ~Semaphore ()         { SDL_DestroySemaphore(m_opSemaphore); }

    void wait() { if ( SDL_SemWait(m_opSemaphore) == -1 ) throw std::runtime_error( "Couldn't wait semaphore" ); }
    void post() { if ( SDL_SemPost(m_opSemaphore) == -1 ) throw std::runtime_error( "Couldn't post semaphore" ); }


private:
    SDL_sem*  m_opSemaphore;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_SEMAPHORE_H__
