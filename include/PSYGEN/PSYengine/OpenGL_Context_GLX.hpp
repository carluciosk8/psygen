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
    *  \ingroup gfx
    *
    *//***********************************************************************/
#ifndef __PSYGEN_OPENGLCONTEXTGLX_H__
#define __PSYGEN_OPENGLCONTEXTGLX_H__


#include <GL/glx.h>

#include "PSYGEN/PSYengine/OpenGL_Context.hpp"

namespace psy {

/**
  *  \author Carlucio Santos Cordeiro <carlucio@gmail.com>
  *  \ingroup gfx
  */
class PSYAPI OpenglContextGlx : public OpenglContext
{
    public:
        OpenglContextGlx();

        virtual void openContext(OpenglContext* opMainContext);
        virtual void closeContext();


    private:
        XVisualInfo*  m_opVisualInfo;
        Display*  m_opDisplay;
        GLXContext  m_opContext;
        //GLXDrawable  m_opDrawable;
        GLXPbuffer  mp_pbuffer;
};

}

#endif //__PSYGEN_OPENGLCONTEXTGLX_H__
