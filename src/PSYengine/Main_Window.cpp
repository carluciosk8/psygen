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
#include <stdexcept>
#include <sstream>

#include <GL/glew.h>
#include <SDL/SDL.h>

#include "PSYGEN/PSYengine/Main_Window.hpp"
#ifdef PSYGEN_PLATFORM_LINUX
#   include "PSYGEN/PSYengine/OpenGL_Context_GLX.hpp"
#elif PSYGEN_PLATFORM_OSX
#   include "PSYGEN/PSYengine/OpenGL_Context_CGL.hpp"
#elif PSYGEN_PLATFORM_WINDOWS
#   include "PSYGEN/PSYengine/OpenGL_Context_WGL.hpp"
#endif


namespace psy {////////////////////////////////////////////////////////////////////////////////////


bool Main_Window::m_bDebug = true;
TextBox  Main_Window::m_oTextBox;

Main_Window::Main_Window()
:// Singleton<Main_Window>(),
  m_iWidth(960),
  m_iHeight(600),
  m_bFullScreen(false),
  m_opMainOpenglContext(NULL)
{
    XInitThreads();
}


Main_Window::~Main_Window()
{
    if (m_opMainOpenglContext)
        this->close();
}


void Main_Window::open(const char* cpName, int iWidth, int iHeight, bool bFullScreen)
{
    m_iWidth=iWidth;
    m_iHeight=iHeight;
    m_bFullScreen=bFullScreen;

    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
        throw std::runtime_error( std::string("Couldn't initialize SDL: ") + std::string(SDL_GetError()) );

    SDL_WM_SetCaption(cpName,0);

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );


    int  iFlags = SDL_OPENGL;

    if ( bFullScreen )
        iFlags |= SDL_FULLSCREEN;

    const SDL_VideoInfo* video = SDL_GetVideoInfo();

    if( !video )
        throw std::runtime_error( std::string("Couldn't get video information: ") + std::string(SDL_GetError()) );

    if( SDL_SetVideoMode( iWidth, iHeight, video->vfmt->BitsPerPixel, iFlags ) == 0 )
        throw std::runtime_error( std::string("Couldn't set video mode: ") + std::string(SDL_GetError()) );

    // init glew lib
    glewInit();

#ifdef PSYGEN_PLATFORM_LINUX
    m_opMainOpenglContext = new OpenglContextGlx();
#elif PSYGEN_PLATFORM_OSX
    m_opMainOpenglContext = new OpenglContextCgl();
#elif PSYGEN_PLATFORM_WINDOWS
    m_opMainOpenglContext = new OpenglContextWgl();
#endif

    m_opMainOpenglContext->openContext();

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor( 0.666f , 0.666f , 0.777f , 1 );

    m_oTextBox.init(iWidth, iHeight, 0, iWidth, 0, iHeight);
}



void Main_Window::close()
{
    SDL_Quit();

    delete m_opMainOpenglContext;
    m_opMainOpenglContext = NULL;
}



void Main_Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Main_Window::refresh()
{
    //if (m_bDebug)
    //    m_oTextBox.Draw();
    SDL_GL_SwapBuffers();
}


}
