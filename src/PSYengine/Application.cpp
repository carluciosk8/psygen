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

#include "PSYGEN/PSYengine/Application.hpp"
#include "PSYGEN/PSYengine/Attr_Wireframe.hpp"
#include "PSYGEN/PSYengine/Attr_Texture2D_File.hpp"
#include "PSYGEN/PSYengine/Attr_Directional_Light.hpp"
#include "PSYGEN/PSYengine/Attr_Fog.hpp"
#include "PSYGEN/PSYengine/Geom_Sphere.hpp"
#include "PSYGEN/PSYengine/Geom_Vbo.hpp"
#include "PSYGEN/PSYengine/Geom_Asteroid.hpp"
#include "PSYGEN/PSYengine/Geom_Terrain_Patch.hpp"
#include "PSYGEN/PSYengine/Geom_Tree.hpp"
#include "PSYGEN/PSYengine/Node_Group.hpp"
#include "PSYGEN/PSYengine/Node_World.hpp"
#include "PSYGEN/PSYengine/Camera.hpp"

namespace psy{/////////////////////////////////////////////////////////////////


Application::Application(int argc, char** argv)
    :
    m_sWindow_Title("Simple Application"), //TODO: make this data driven!!!
    m_iWidth(960),
    m_iHeight(600),
    m_iNum_Modelers(1),
    m_bFull_Screen(false),

    m_Running(true)
{
    // Open Main Window
    m_oWnd.open(m_sWindow_Title.c_str(), m_iWidth, m_iHeight, m_bFull_Screen);

    // Initialize AntTweakBar
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(m_iWidth, m_iHeight);

    // Initialize Clock
    m_oClock.init();

    // Register event handlers
    m_oEventManager.registerHandler(SDL_QUIT, new QuitHandler(this));

    // Register attributes
    Object::Manager.register_class<Attr_Wireframe>();
    Object::Manager.register_class<Attr_Texture2D_File>();
    Object::Manager.register_class<Attr_Directional_Light>();
    Object::Manager.register_class<Attr_Fog>();

    // Register geometries
    Object::Manager.register_class<Geom_Sphere>();
    Object::Manager.register_class<Geom_Vbo>();
    Object::Manager.register_class<Geom_Asteroid>();
    Object::Manager.register_class<Geom_Terrain_Patch>();
    Object::Manager.register_class<Geom_Tree>();

    // Register nodes
    Object::Manager.register_class<Node_Group>();
    Object::Manager.register_class<Node_World>();
    Object::Manager.register_class<Camera>();
}



Application::~Application()
{
    m_oEventManager.shutdown();
    m_oClock.shutdown();
    TwTerminate();
    m_oWnd.close();
}


int Application::run()
{
    while (m_Running)
    {
        m_oClock.FrameStep();
        m_oEventManager.executeAll();
        m_oWnd.clear();
        step();
        TwDraw();
        m_oWnd.refresh();
    }

    return 0;
}



void Application::stop()
{
    m_Running = false;
}





ImplementEventHandler(QuitHandler, event)
{
    this->getListener()->stop();
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
