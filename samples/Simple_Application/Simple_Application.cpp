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
    *  \ingroup
    *
    *//***********************************************************************/

#include <iostream>
#include <sstream>
#include <cassert>

#include "PSYGEN/PSYengine/Node_Group.hpp"
#include "PSYGEN/PSYengine/Geom_Sphere.hpp"
#include "PSYGEN/PSYengine/Geom_Asteroid.hpp"
#include "PSYGEN/PSYengine/Geom_Terrain_Patch.hpp"
#include "PSYGEN/PSYengine/Geom_Tree.hpp"
#include "PSYGEN/PSYengine/Attr_Texture2D_File.hpp"

#include "Simple_Application.hpp"

Simple_Application::Simple_Application(int argc, char** argv)
:
    psy::Application(argc, argv),
    amplificator(1, m_oWnd.getMainOpenglContext()),
    camera(NULL),
    scene(NULL)
{
    //psy::Main_Window::debug_off();
    //amplificator.init(/*1, m_oWnd.getMainOpenglContext()*/);
    SDL_Delay(100);
    create_scene();
    z=0;
}



Simple_Application::~Simple_Application()
{
    printer.print(scene);
    shrinker.inspect(scene);
}



void Simple_Application::step()
{
    step_scene();

    updater.update(scene);
    renderer.render(scene, camera);

    psy::Main_Window::printfxy ( m_iWidth - 90, 1, "FPS: %4.1f\n", m_oClock.GetFrameRate() );
}


void Simple_Application::create_scene()
{
    scene = psy::Object::Manager.create_concrete<psy::Node_Group>("scene");
    //
        psy::Attr_Texture2D_File* texture = psy::Object::Manager.create_concrete<psy::Attr_Texture2D_File>("asteroid.jpg");
        scene->insert_attribute(texture);

        camera_orbit = psy::Object::Manager.create_concrete<psy::Node_Group>("camera_orbit");
        //
            camera = psy::Object::Manager.create_concrete<psy::Camera>("camera");
            //
                camera->set_perspective(60, (float)m_oWnd.getWidth() / m_oWnd.getHeight(), 1.5f, 1000.0f );
                camera->local.setPos(0,0,20);
            //
            camera->reparent_to(camera_orbit);
        //
        camera_orbit->reparent_to(scene);

        sun_orbit = psy::Object::Manager.create_concrete<psy::Node_Group>("sun_orbit");
        //
            sun_orbit->local.setPos(1.5f,1.5f,0);

            psy::Attr_Texture2D_File* texture2 = psy::Object::Manager.create_concrete<psy::Attr_Texture2D_File>("tree.png");
            sun_orbit->insert_attribute(texture2);
/*            psy::Geom_Sphere*  sun = psy::Object::Manager.create_concrete<psy::Geom_Sphere>("sun");
            //
                sun->set_parameter2("center", psy::vec3(0,0,0));
                sun->set_parameter2("radius", 1.999f);
                sun->set_parameter2("slices", 4);
                sun->set_parameter2("stacks", 2);
            //
            sun_orbit->insert_geometry(sun);
*/
            psy::Geom_Tree*  sun = psy::Object::Manager.create_concrete<psy::Geom_Tree>("sun");
            //
                sun->set_parameter2("seed", 270);
                sun->set_parameter2("size", 2.999f);
                sun->set_parameter2("radius", 0.420f);
                sun->set_parameter2("iterations", 4);
                sun->set_parameter2("min_branches", 3);
                sun->set_parameter2("max_branches", 4);
                sun->set_parameter2("segments", 3);
                sun->set_parameter2("subdivisions", 7);
            //
            sun_orbit->insert_geometry(sun);

            planet1_orbit = psy::Object::Manager.create_concrete<psy::Node_Group>("planet1_orbit");
            //
                planet1_orbit->local.setPos(8,8,0);

                psy::Geom_Terrain_Patch*  planet1 = psy::Object::Manager.create_concrete<psy::Geom_Terrain_Patch>("planet1");
                //
                    planet1->set_parameter2("posX", 0.0f);
                    planet1->set_parameter2("posZ", 0.0f);
                    planet1->set_parameter2("sizeX", 3.0f);
                    planet1->set_parameter2("sizeZ", 3.0f);
                    planet1->set_parameter2("subdivisionsX", 32);
                    planet1->set_parameter2("subdivisionsZ", 32);
                //
                planet1_orbit->insert_geometry(planet1);

                moon1_orbit = psy::Object::Manager.create_concrete<psy::Node_Group>("moon1_orbit");
                //
                    moon1_orbit->local.setPos(0,5,0);

                    psy::Geom_Asteroid*  moon1 = psy::Object::Manager.create_concrete<psy::Geom_Asteroid>("moon1");
                    //
                        moon1->set_parameter2("seed", 666);
                        moon1->set_parameter2("radius", 1.733f);
                        moon1->set_parameter2("amplitude", 0.25f);
                        moon1->set_parameter2("decay", 1.5f);
                        moon1->set_parameter2("subdivisions", 3);
                    //
                    moon1_orbit->insert_geometry(moon1);
                //
                moon1_orbit->reparent_to(planet1_orbit);
            //
            planet1_orbit->reparent_to(sun_orbit);
        //
        sun_orbit->reparent_to(scene);
    //
    // end scene

    updater.update(scene);
    amplificator.inspect(scene);
    printer.print(scene);
}



void Simple_Application::step_scene()
{
    z -= 0.0005f;

    moon1_orbit->local.rotateZ(-2*z);
    planet1_orbit->local.rotateZ(z);
    sun_orbit->local.rotateZ(z/3);
    camera_orbit->local.rotateY(z*0.2f);
}


/////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    Simple_Application  app(argc, argv);
    return app.run();
}
