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
#ifndef __PSYGEN_RENDERER_H__
#define __PSYGEN_RENDERER_H__


#include "PSYGEN/PSYengine/Visitor.hpp"
#include "PSYGEN/PSYengine/Camera.hpp"
#include "PSYGEN/PSYmath/Matrix4.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class Renderer : public Visitor
{
public:
    Renderer() : m_npCamera(NULL) {}
    virtual ~Renderer() {}
    virtual void inspect(Node* opNode);

    inline void render(Node* npScene, Camera* npCam)
    {
        (m_npCamera = npCam)->world.makeGLview(m_mGLview);
        m_npCamera->update_frustum();
        this->inspect(npScene);
    }


protected:
    Camera*  m_npCamera;

    mat4 m_mGLmodel;
    mat4 m_mGLview;
};


class Bound_Renderer : public Visitor
{
public:
    Bound_Renderer() : m_npCamera(NULL) {}
    virtual ~Bound_Renderer() {}
    virtual void inspect(Node* opNode);

    inline void render(Node* npScene, Camera* npCam)
    {
        (m_npCamera = npCam)->world.makeGLview(m_mGLview);
        m_npCamera->update_frustum();
        this->inspect(npScene);
    }


protected:
    Camera*  m_npCamera;
    mat4 m_mGLview;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_RENDERER_H__
