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

//#include "PSYGEN/PSYengine/Node_Group.hpp"
#include "PSYGEN/PSYengine/Geom_Terrain_Patch.hpp"
//#include "PSYGEN/PSYengine/Attr_Texture2D_File.hpp"
//#include "PSYGEN/PSYengine/Attr_Directional_Light.hpp"

void generate_callback(void *clientData);

class Test_Terrain_Patch : public psy::Application
{
public:
    Test_Terrain_Patch(int argc, char** argv)
            :
            psy::Application(argc, argv),
            //amplificator(1, m_oWnd.getMainOpenglContext()),
            camera(NULL),
            scene(NULL)
    {
        //psy::Main_Window::debug_off();
        //amplificator.init(/*1, m_oWnd.getMainOpenglContext()*/);
        //SDL_Delay(100);

        m_fPosX = 0.0f;
        m_fPosZ = 0.0f;
        m_fSizeX = 1.0f;
        m_fSizeZ = 1.0f;
        m_iSubdivsX = 128;
        m_iSubdivsZ = 128;
        m_fH = 1.0f;
        m_fLacunarity = 2.0f;
        m_fOctaves = 3.0f;
        m_fOffset = 1.0f;
        m_fGain = 2.0f;
        m_fScale_V = 1.0f;
        m_fScale_H = 1.0f;

        // Create a tweak bar
        m_opBar = TwNewBar("Terrain_Patch");

        TwAddVarRW(m_opBar, "posX", TW_TYPE_FLOAT, &m_fPosX, " label='Pos X' min=-256 max=256 step=1 ");
        TwAddVarRW(m_opBar, "posZ", TW_TYPE_FLOAT, &m_fPosZ, " label='Pos Z' min=-256 max=256 step=1 ");
        TwAddVarRW(m_opBar, "sizeX", TW_TYPE_FLOAT, &m_fSizeX, " label='Size X' min=1 max=4096 step=1 ");
        TwAddVarRW(m_opBar, "sizeZ", TW_TYPE_FLOAT, &m_fSizeZ, " label='Size Z' min=1 max=4096 step=1 ");
        TwAddVarRW(m_opBar, "subdivisionsX", TW_TYPE_UINT32, &m_iSubdivsX, " label='Subdivs X' min=8 max=512 step=8 ");
        TwAddVarRW(m_opBar, "subdivisionsZ", TW_TYPE_UINT32, &m_iSubdivsZ, " label='Subdivs Z' min=8 max=512 step=8 ");
        TwAddVarRW(m_opBar, "H", TW_TYPE_FLOAT, &m_fH, " label='H' min=0 max=2 step=0.0001 ");
        TwAddVarRW(m_opBar, "lacunarity", TW_TYPE_FLOAT, &m_fLacunarity, " label='Lacunarity' min=1 max=3 step=0.0001 ");
        TwAddVarRW(m_opBar, "octaves", TW_TYPE_FLOAT, &m_fOctaves, " label='Octaves' min=0 max=8 step=0.01 ");
        TwAddVarRW(m_opBar, "offset", TW_TYPE_FLOAT, &m_fOffset, " label='Offset' min=0 max=2 step=0.0001 ");
        TwAddVarRW(m_opBar, "gain", TW_TYPE_FLOAT, &m_fGain, " label='Gain' min=0 max=4 step=0.0001 ");
        TwAddVarRW(m_opBar, "scale_v", TW_TYPE_FLOAT, &m_fScale_V, " label='Vertical Scale' min=0 max=1000 step=0.0001 ");
        TwAddVarRW(m_opBar, "scale_h", TW_TYPE_FLOAT, &m_fScale_H, " label='Horizontal Scale' min=0 max=1000 step=0.0001 ");

        TwAddSeparator(m_opBar, NULL, NULL);

        TwAddVarRW(m_opBar, "light_dir", TW_TYPE_DIR3F, &light_dir, "label='Light direction'");
        TwAddButton(m_opBar, "generate", generate_callback, this, " label='Generate' key=return help='Generate new terrain.' ");
        //TwAddVarRO(m_opBar, "gentime", TW_TYPE_FLOAT, &m_fGenTime, " label='Generation time'");

        //create_scene();
        scene = psy::Object::Manager.create_node("Node_Group", "scene");

        light = psy::Object::Manager.create_attr("Attr_Directional_Light", "light");
        light->set_parameter2( "specular", psy::vec4(0.2f, 0.2f, 0.2f, 1.0f) );
        light->set_parameter2( "ambient", psy::vec4(0.8f, 0.8f, 0.8f, 1.0f) );
        light->set_parameter2( "diffuse", psy::vec4(0.5f, 0.5f, 0.5f, 1.0f) );
        light->set_parameter2( "direction", psy::vec4(1.0f, 1.0f, 1.0f, 0.0f) );
        scene->insert_attribute(light);

        tree_node = psy::Object::Manager.create_node("Node_Group", "tree_node");

        psy::Attribute* texture = psy::Object::Manager.create_attr("Attr_Texture2D_File" ,"grass.jpg");
        texture->set_parameter2("filename", std::string("grass.jpg"));
        tree_node->insert_attribute(texture);

        tree = psy::Object::Manager.create_concrete<psy::Geom_Terrain_Patch>("tree");
        tree->set_parameter2("posX", m_fPosX);
        tree->set_parameter2("posZ", m_fPosZ);
        tree->set_parameter2("sizeX", m_fSizeX);
        tree->set_parameter2("sizeZ", m_fSizeZ);
        tree->set_parameter2("subdivisionsX", m_iSubdivsX);
        tree->set_parameter2("subdivisionsZ", m_iSubdivsZ);
        tree->set_parameter2("H", m_fH);
        tree->set_parameter2("lacunarity", m_fLacunarity);
        tree->set_parameter2("octaves", m_fOctaves);
        tree->set_parameter2("offset", m_fOffset);
        tree->set_parameter2("gain", m_fGain);
        tree->set_parameter2("scale_v", m_fScale_V);
        tree->set_parameter2("scale_h", m_fScale_H);
        tree_node->insert_geometry(tree);

        tree_node->reparent_to(scene);

        camera = psy::Object::Manager.create_camera("Camera", "camera");
        camera->set_perspective(60, (float)m_oWnd.getWidth() / m_oWnd.getHeight(), 0.5f, 15512.0f);
        camera->local.setPos(0, tree->height(0,0)+m_fSizeX*.25f, m_fSizeX);
        camera->local.rotateX(-M_PI/6.0f);
        camera->reparent_to(scene);

        updater.update(scene);
        amplificator.inspect(scene);
        //printer.print(scene);

        z=0;
    }

    // Callback function associated to the 'Generate' button of the Terrain_Patch tweak bar.
    void generate()
    {
        tree->set_parameter2("posX", m_fPosX);
        tree->set_parameter2("posZ", m_fPosZ);
        tree->set_parameter2("sizeX", m_fSizeX);
        tree->set_parameter2("sizeZ", m_fSizeZ);
        tree->set_parameter2("subdivisionsX", m_iSubdivsX);
        tree->set_parameter2("subdivisionsZ", m_iSubdivsZ);
        tree->set_parameter2("H", m_fH);
        tree->set_parameter2("lacunarity", m_fLacunarity);
        tree->set_parameter2("octaves", m_fOctaves);
        tree->set_parameter2("offset", m_fOffset);
        tree->set_parameter2("gain", m_fGain);
        tree->set_parameter2("scale_v", m_fScale_V);
        tree->set_parameter2("scale_h", m_fScale_H);

        camera->local.setPos(0, tree->height(0,0)+m_fSizeX*.25f, m_fSizeX);

        shrinker.inspect(scene);
        updater.update(scene);
        amplificator.inspect(scene);
        predictor.predict(scene);
        std::cout << "predict: " << tree->estimate_mem_usage() << std::endl;
        std::cout << "real: " << tree->get_gpu_real() << std::endl;
        //printer.print(scene);
    }



    virtual ~Test_Terrain_Patch()
    {
        printer.print(scene);
        shrinker.inspect(scene);
    }

    virtual void step()
    {
        //step_scene();
        z -= 0.0005f;

        light_dir.normalize();
        light->set_parameter2("direction", psy::vec4(-light_dir.x, -light_dir.y, -light_dir.z, 0.0f));

        tree_node->local.rotateY(z*0.2f);

        updater.update(scene);
        renderer.render(scene, camera);

        psy::Main_Window::printfxy(m_iWidth - 90, 1, "FPS: %4.1f\n", m_oClock.GetFrameRate());
    }


protected:
    psy::DataAmplificator   amplificator;
    psy::Shrinker       shrinker;
    psy::Renderer       renderer;
    psy::Memory_Predictor predictor;
    psy::Updater        updater;
    psy::Printer        printer;
    psy::Camera*        camera;
    psy::Node*          scene;

    psy::Node*      tree_node;
    psy::Geom_Terrain_Patch*  tree;
    psy::Attribute* light;
    psy::vec3   light_dir;

    float z;
    TwBar  *m_opBar;

    float  m_fPosX;
    float  m_fPosZ;
    float  m_fSizeX;
    float  m_fSizeZ;
    int    m_iSubdivsX;
    int    m_iSubdivsZ;
    float  m_fH;
    float  m_fLacunarity;
    float  m_fOctaves;
    float  m_fOffset;
    float  m_fGain;
    float  m_fScale_V;
    float  m_fScale_H;
};


// Callback function associated to the 'Generate' button of the Terrain_Patch tweak bar.
void generate_callback(void *clientData)
{
    Test_Terrain_Patch*  opApp = static_cast<Test_Terrain_Patch*>(clientData); // scene pointer is stored in clientData
    opApp->generate();                               // re-initialize the scene
}




int main(int argc, char** argv)
{
    Test_Terrain_Patch  app(argc, argv);
    return app.run();
}
