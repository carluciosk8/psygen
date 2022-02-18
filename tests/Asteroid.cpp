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

#include "PSYGEN/PSYengine/Application.hpp"
#include "PSYGEN/PSYengine/Amplificator.hpp"
#include "PSYGEN/PSYengine/Shrinker.hpp"
#include "PSYGEN/PSYengine/Renderer.hpp"
#include "PSYGEN/PSYengine/Updater.hpp"
#include "PSYGEN/PSYengine/Printer.hpp"
#include "PSYGEN/PSYengine/Camera.hpp"

#include "PSYGEN/PSYengine/Node_Group.hpp"
#include "PSYGEN/PSYengine/Geom_Asteroid.hpp"
#include "PSYGEN/PSYengine/Attr_Texture2D_File.hpp"

void generate_callback(void *clientData);

class Test_Asteroid : public psy::Application
{
public:
    Test_Asteroid(int argc, char** argv)
            :
            psy::Application(argc, argv),
            //amplificator(1, m_oWnd.getMainOpenglContext()),
            camera(NULL),
            scene(NULL)
    {
        //psy::Main_Window::debug_off();
        //amplificator.init(/*1, m_oWnd.getMainOpenglContext()*/);
        //SDL_Delay(100);

        m_uiSeed = 5705;
        m_fRadius = 1.7f;
        m_fAmplitude = 0.75f;
        m_fDecay = 0.27f;
        m_uiSubdivs = 3;

        // Create a tweak bar
        m_opBar = TwNewBar("Asteroid");

        TwAddVarRW(m_opBar, "seed", TW_TYPE_UINT32, &m_uiSeed, " label='Seed' help='Defines the seed for pseudo random number generator.' ");
        TwAddVarRW(m_opBar, "radius", TW_TYPE_FLOAT, &m_fRadius, " label='Radius' min=0.01 max=10 step=0.01 ");
        TwAddVarRW(m_opBar, "amplitude", TW_TYPE_FLOAT, &m_fAmplitude, " label='amplitude' min=0.01 max=5 step=0.01 ");
        TwAddVarRW(m_opBar, "decay", TW_TYPE_FLOAT, &m_fDecay, " label='decay' min=0.01 max=5 step=0.01 ");
        TwAddVarRW(m_opBar, "subdivisions", TW_TYPE_UINT32, &m_uiSubdivs, " label='Subdivs' min=0 max=9 ");

        TwAddSeparator(m_opBar, NULL, NULL);

        TwAddButton(m_opBar, "generate", generate_callback, this, " label='Generate' key=return help='Generate new terrain.' ");
        //TwAddVarRO(m_opBar, "gentime", TW_TYPE_FLOAT, &m_fGenTime, " label='Generation time'");

        //create_scene();
        scene = psy::Object::Manager.create_concrete<psy::Node_Group>("scene");

        camera = psy::Object::Manager.create_concrete<psy::Camera>("camera");
        camera->set_perspective(60, (float)m_oWnd.getWidth() / m_oWnd.getHeight(), 1.5f, 1000.0f);
        camera->local.setPos(0,0,5);
        camera->reparent_to(scene);

        tree_node = psy::Object::Manager.create_concrete<psy::Node_Group>("tree_node");

        psy::Attr_Texture2D_File* texture = psy::Object::Manager.create_concrete<psy::Attr_Texture2D_File>("asteroid.jpg");
        texture->set_parameter2("filename", std::string("asteroid.jpg") );
        tree_node->insert_attribute(texture);

        tree = psy::Object::Manager.create_concrete<psy::Geom_Asteroid>("tree");
        tree->set_parameter2("seed", m_uiSeed);
        tree->set_parameter2("radius", m_fRadius);
        tree->set_parameter2("amplitude", m_fAmplitude);
        tree->set_parameter2("decay", m_fDecay);
        tree->set_parameter2("subdivisions", m_uiSubdivs);
        tree_node->insert_geometry(tree);

        tree_node->reparent_to(scene);

        updater.update(scene);
        //printer.print(scene);
        amplificator.inspect(scene);
        //printer.print(scene);

        z=0;
    }

    // Callback function associated to the 'Generate' button of the Asteroid tweak bar.
    void generate()
    {
        tree->set_parameter2("seed", m_uiSeed);
        tree->set_parameter2("radius", m_fRadius);
        tree->set_parameter2("amplitude", m_fAmplitude);
        tree->set_parameter2("decay", m_fDecay);
        tree->set_parameter2("subdivisions", m_uiSubdivs);

        shrinker.inspect(scene);
        updater.update(scene);
        amplificator.inspect(scene);
        predictor.predict(scene);
        std::cout << "predict: " << tree->estimate_mem_usage() << std::endl;
        std::cout << "real: " << tree->get_gpu_real() << std::endl;
    }



    virtual ~Test_Asteroid()
    {
        printer.print(scene);
        shrinker.inspect(scene);
    }

    virtual void step()
    {
        //step_scene();
        z -= 0.0005f;

        tree_node->local.rotateY(z*0.2f);

        updater.update(scene);
        renderer.render(scene, camera);

        psy::Main_Window::printfxy(m_iWidth - 90, 1, "FPS: %4.1f\n", m_oClock.GetFrameRate());
    }


protected:
    psy::DataAmplificator   amplificator;
    psy::Shrinker       shrinker;
    psy::Renderer       renderer;
    psy::Updater        updater;
    psy::Memory_Predictor predictor;
    psy::Printer        printer;
    psy::Camera*        camera;
    psy::Node*          scene;

    float z;
    psy::Node_Group*  tree_node;
    psy::Geom_Asteroid*   tree;
    TwBar  *m_opBar;

    int    m_uiSeed;
    float  m_fRadius;
    float  m_fAmplitude;
    float  m_fDecay;
    int    m_uiSubdivs;
};


// Callback function associated to the 'Generate' button of the Asteroid tweak bar.
void generate_callback(void *clientData)
{
    Test_Asteroid*  opApp = static_cast<Test_Asteroid*>(clientData); // scene pointer is stored in clientData
    opApp->generate();                               // re-initialize the scene
}




int main(int argc, char** argv)
{
    Test_Asteroid  app(argc, argv);
    return app.run();
}
