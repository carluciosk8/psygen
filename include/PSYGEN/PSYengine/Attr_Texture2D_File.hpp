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
#ifndef __PSYGEN_ATTR_TEXTURE2D_FILE_H__
#define __PSYGEN_ATTR_TEXTURE2D_FILE_H__

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "PSYGEN/PSYengine/Attribute.hpp"


namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Attr_Texture2D_File : public Attribute
{
public:
    /// Procedural generation and collapse
    ///
    virtual void amplify (Mutex*);
    virtual void shrink  (Mutex*);

    /// Generation time and memory usage estimation
    ///
    virtual float estimate_mem_usage  ();
    virtual float        estimate_time_usage ();

    /// OpenGL rendering commands here
    virtual void enable  ();
    virtual void disable ();


private:
    GLuint        m_gl_texture;
    SDL_Surface  *m_sdl_surface;

PSYGEN_DECLARE_PARAMETERS(Attr_Texture2D_File):
    std::string  filename;
    float        size;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////


#endif //__PSYGEN_ATTR_TEXTURE2D_FILE_H__
