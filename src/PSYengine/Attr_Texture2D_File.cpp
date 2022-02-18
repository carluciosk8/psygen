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
    *  \ingroup $GROUP$
    *
    *//***********************************************************************/

#include <stdexcept>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYengine/Attr_Texture2D_File.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Attr_Texture2D_File, Attribute)
,
m_gl_texture(0),
m_sdl_surface(NULL)
{
    bind_parameter2(Parameter::STRING, "filename", &filename, std::string(""));
    bind_parameter2(Parameter::FLOAT, "size", &size, 0.0f);

    m_sys_memory_use = sizeof(*this);
    //m_sdl_surface = IMG_Load(filename.c_str());
    //filesize = 4.0f;//m_sdl_surface->w * m_sdl_surface->h * m_sdl_surface->format->BytesPerPixel;
    //SDL_FreeSurface(m_sdl_surface);
}



void Attr_Texture2D_File::amplify(Mutex* mutex)
{
    //if (m_eState == SHRINKED)
    //{
/*        std::cout << "amplify Attr_Texture2D_File: name = \"" << get_name() << "\"" << std::endl;
        std::cout << "    filename = \"" << filename << "\"" << std::endl;*/
        int mode;

        m_sdl_surface = IMG_Load(filename.c_str());

        if (!m_sdl_surface)
            throw std::runtime_error(std::string("Error: " + std::string(IMG_GetError())));

        if (m_sdl_surface->format->BytesPerPixel == 3)
            mode = GL_RGB;
        else if (m_sdl_surface->format->BytesPerPixel == 4)
            mode = GL_RGBA;
        else
        {
            SDL_FreeSurface(m_sdl_surface);
            throw std::runtime_error(std::string("Invalid BPP format for image: ") + get_name());
        }

        //m_iWidth = surface->w;
        //m_iHeight = surface->h;

        glGenTextures(1, &m_gl_texture);
        glBindTexture(GL_TEXTURE_2D, m_gl_texture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //glTexImage2D(GL_TEXTURE_2D, 0, mode, m_iWidth, m_iHeight, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

        if (m_sdl_surface->format->BytesPerPixel == 3)
            gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_sdl_surface->w, m_sdl_surface->h, GL_RGB, GL_UNSIGNED_BYTE, m_sdl_surface->pixels);
        else if (m_sdl_surface->format->BytesPerPixel == 4)
            gluBuild2DMipmaps(GL_TEXTURE_2D, 4, m_sdl_surface->w, m_sdl_surface->h, GL_RGBA, GL_UNSIGNED_BYTE, m_sdl_surface->pixels);

        // Memory use
        m_gpu_memory_use = PSY_BYTES_TO_MEGA(m_sdl_surface->w * m_sdl_surface->h * m_sdl_surface->format->BytesPerPixel);
        //m_gpu_memory_use *= 1.0f/(1024.0f*1024.0f);

//         std::cout << "file = " << filename << std::endl;
//         std::cout << "w = " << m_sdl_surface->w << std::endl;
//         std::cout << "h = " << m_sdl_surface->h << std::endl;
//         std::cout << "bpp = " << (int) m_sdl_surface->format->BytesPerPixel << std::endl;
//         std::cout << "tex real memory use = " << m_gpu_memory_use << std::endl;
//         std::cout << "tex estimate memory use = " << estimate_mem_usage() << std::endl;

        //glFlush();
        SDL_FreeSurface(m_sdl_surface);

        if (mutex) mutex->lock();
        Object::Manager.inc_mem_usage( m_gpu_memory_use );
        m_eState = AMPLIFIED;
        if (mutex) mutex->unlock();
    //}
}



void Attr_Texture2D_File::shrink(Mutex* mutex)
{
    //if (m_eState == AMPLIFIED)
    //{
//         std::cout << "shrink Attr_Texture2D_File: name = \"" << get_name() << "\"" << std::endl;
        //m_eState = SHRINKED;

        glDeleteTextures(1, &m_gl_texture);

        //glFlush();

        if (mutex) mutex->lock();
        Object::Manager.dec_mem_usage( m_gpu_memory_use );
        m_eState = SHRINKED;
        if (mutex) mutex->unlock();
        m_gpu_memory_use = 0;
//    }
}



float Attr_Texture2D_File::estimate_mem_usage()
{
    return size;
}



float Attr_Texture2D_File::estimate_time_usage()
{
    return 0.0f;
}



void Attr_Texture2D_File::enable()
{
    glAlphaFunc(GL_GREATER,0.1f);      // Set Alpha Testing     (disable blending)
    glEnable(GL_ALPHA_TEST);      // Enable Alpha Testing  (disable blending)

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, m_gl_texture);
}



void Attr_Texture2D_File::disable()
{
    glDisable(GL_TEXTURE_2D);
}


}//////////////////////////////////////////////////////////////////////////////
