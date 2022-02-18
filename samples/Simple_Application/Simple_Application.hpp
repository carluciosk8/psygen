/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
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
    *  \ingroup samples
    *
    *//***********************************************************************/
#ifndef __SAMPLES_SIMPLE_APPLICATION_HPP__
#define __SAMPLES_SIMPLE_APPLICATION_HPP__

#include "PSYGEN/PSYengine/Application.hpp"
#include "PSYGEN/PSYengine/Amplificator.hpp"
#include "PSYGEN/PSYengine/Shrinker.hpp"
#include "PSYGEN/PSYengine/Renderer.hpp"
#include "PSYGEN/PSYengine/Updater.hpp"
#include "PSYGEN/PSYengine/Printer.hpp"
#include "PSYGEN/PSYengine/Camera.hpp"


class Simple_Application : public psy::Application
{
public:
                 Simple_Application(int argc, char** argv);
    virtual     ~Simple_Application();
    virtual void step();

    void create_scene();
    void step_scene();

protected:
    psy::Amplificator   amplificator;
    psy::Shrinker       shrinker;
    psy::Renderer       renderer;
    psy::Updater        updater;
    psy::Printer        printer;
    psy::Camera*   camera;

    psy::Node*   scene;
    psy::Node*   camera_orbit;
    psy::Node*   sun_orbit;
    psy::Node*   planet1_orbit;
    psy::Node*   moon1_orbit;

    float z;
};


#endif //__SAMPLES_SIMPLE_APPLICATION_HPP__
