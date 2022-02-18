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

#include <iostream>

#include "PSYGEN/PSYengine/OpenGL_Context_GLX.hpp"



namespace psy
{



OpenglContextGlx::OpenglContextGlx()
        :
        m_opVisualInfo(NULL),
        m_opDisplay(NULL),
        m_opContext(NULL),
        mp_pbuffer(NULL)
{}



void OpenglContextGlx::openContext(OpenglContext* opMainContext)
{
    if (opMainContext == NULL)
    {
        m_opDisplay = glXGetCurrentDisplay();
        m_opContext = glXGetCurrentContext();
    }
    else
    {
        GLXContext  opGlxMainContext = static_cast<OpenglContextGlx*>(opMainContext)->m_opContext;
        m_opDisplay = static_cast<OpenglContextGlx*>(opMainContext)->m_opDisplay;

        int  ipAttrList[] = {GLX_RGBA, None};
        int pbufAttrib[] =
        {
            GLX_PBUFFER_WIDTH,   256,
            GLX_PBUFFER_HEIGHT,  256,
            GLX_LARGEST_PBUFFER, False,
            None
        };
        int nitems;
        GLXFBConfig *fbconfig;
        int attrib[] =
        {
            GLX_DOUBLEBUFFER,  False,
            GLX_RED_SIZE,      8,
            GLX_GREEN_SIZE,    8,
            GLX_BLUE_SIZE,     8,
            GLX_DEPTH_SIZE,    1,
            GLX_RENDER_TYPE,   GLX_RGBA_BIT,
            GLX_DRAWABLE_TYPE, GLX_PBUFFER_BIT | GLX_WINDOW_BIT,
            None
        };
        m_opVisualInfo = glXChooseVisual(m_opDisplay, 0, ipAttrList);
        m_opContext    = glXCreateContext(m_opDisplay, m_opVisualInfo, opGlxMainContext, GL_TRUE);
        fbconfig       = glXChooseFBConfig(m_opDisplay, DefaultScreen(m_opDisplay), attrib, &nitems);
        mp_pbuffer     = glXCreatePbuffer(m_opDisplay, fbconfig[0], pbufAttrib);
        glXMakeCurrent(m_opDisplay, mp_pbuffer, m_opContext);
    }
}



void OpenglContextGlx::closeContext()
{
    glXDestroyContext(m_opDisplay, m_opContext);
    glXDestroyPbuffer(m_opDisplay, mp_pbuffer);
    XFree(m_opVisualInfo);
}



}
