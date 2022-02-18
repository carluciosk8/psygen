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
#include <sstream>
#include <fstream>

#include "PSYGEN/PSYmath/Random.hpp"
#include "PSYGEN/PSYengine/Geom_Terrain_Patch.hpp"

#include "PSYGEN/PSYengine/Application.hpp"
#include "PSYGEN/PSYengine/Amplificator.hpp"
#include "PSYGEN/PSYengine/Renderer.hpp"
#include "PSYGEN/PSYengine/Updater.hpp"
#include "PSYGEN/PSYengine/Printer.hpp"
#include "PSYGEN/PSYengine/Camera.hpp"


DeclareEventHandler(SDLKeyDownHandler, Test_World);
DeclareEventHandler(mouse_button_down, Test_World);
DeclareEventHandler(SDLKeyUpHandler, Test_World);

static int num_modelers = 1;

class Test_World : public psy::Application
{
public:
    Test_World(int argc, char** argv)
            :
            psy::Application(argc, argv),
            amplificator(num_modelers, m_oWnd.getMainOpenglContext()),
            camera(NULL),
            scene(NULL)
    {
        psy::Main_Window::debug_off();
        amplificator.init();

        rand.seed(270);
        world_size = 1;
        patch_size = 1.0;
        min_trees = 222;
        max_trees = 333;
        min_rocks = 27;
        max_rocks = 36;
        m_record_stats = false;
        m_camera_fly = false;
        m_total_fly_time = 60.0f;

        int arg=1;
        while (arg < argc)
        {
            if ( std::string(argv[arg]) == std::string("-seed") )
            {
                arg++;
                rand.seed(atoi(argv[arg]));
            }
            else if ( std::string(argv[arg]) == std::string("-worldsize") )
            {
                arg++;
                world_size = atoi(argv[arg]);
            }
            else if ( std::string(argv[arg]) == std::string("-patchsize") )
            {
                arg++;
                patch_size = atof(argv[arg]);
            }
            else if ( std::string(argv[arg]) == std::string("-mintrees") )
            {
                arg++;
                min_trees = atoi(argv[arg]);
            }
            else if ( std::string(argv[arg]) == std::string("-maxtrees") )
            {
                arg++;
                max_trees = atoi(argv[arg]);
            }
            else if ( std::string(argv[arg]) == std::string("-minrocks") )
            {
                arg++;
                min_rocks = atoi(argv[arg]);
            }
            else if ( std::string(argv[arg]) == std::string("-maxrocks") )
            {
                arg++;
                max_rocks = atoi(argv[arg]);
            }
            else if ( std::string(argv[arg]) == std::string("-recordstats") )
            {
                arg++;
                m_record_stats = true;
                m_camera_fly = true;
                m_total_fly_time = atof(argv[arg]);
            }

            arg++;
        }

        m_oClock.SetFiltering(15, 1.0f/60.0f);

        if ( not m_camera_fly )
        {
            m_oEventManager.registerHandler ( SDL_KEYDOWN, new SDLKeyDownHandler ( this ) );
            m_oEventManager.registerHandler ( SDL_MOUSEMOTION, new mouse_button_down ( this ) );
            m_oEventManager.registerHandler ( SDL_KEYUP, new SDLKeyUpHandler ( this ) );

            // Create a tweak bar
            m_opBar = TwNewBar("World");

            TwAddVarRW(m_opBar, "show_bound_volume", TW_TYPE_BOOLCPP, &show_bound_volume, "label='Show bound volume'");
            TwAddVarRW(m_opBar, "light_dir", TW_TYPE_DIR3F, &light_dir, "label='Light direction'");

            TwAddSeparator(m_opBar, NULL, NULL);

            TwAddVarRO(m_opBar, "num_modelers", TW_TYPE_INT32, &num_modelers, "label='Modelers'");
            TwAddVarRO(m_opBar, "fps", TW_TYPE_FLOAT, &fps, "label='FPS'");
            TwAddVarRO(m_opBar, "total_amplification_time", TW_TYPE_FLOAT, &total_amplification_time, "label='PLA running time'");
            TwAddVarRO(m_opBar, "real_gpu_memory", TW_TYPE_FLOAT, &real_gpu_memory, "label='actual GPU Memory use'");
            TwAddVarRO(m_opBar, "system_memory", TW_TYPE_FLOAT, &system_memory, "label='System Memory use'");
            TwAddVarRO(m_opBar, "predicted_gpu_memory", TW_TYPE_FLOAT, &predicted_gpu_memory, "label='Total predicted scene size'");
        }

        light_dir = -psy::vec3(-0.41 , 0.32 , 0.86);
        show_bound_volume = false;
        fps = 0.0f;
        total_amplification_time = 0.0f;
        real_gpu_memory = 0.0f;
        predicted_gpu_memory = 0.0f;
        system_memory = 0.0f;

        h = 0;
        p = 0;
        dh = 0;
        dp = 0;
        ds = 0.0f;
        dv = 0.0f;
        acc = 0;
        damp = 1.0f;
        m_heigth = 0.1f;

        scene_create_time = m_oClock.GetAbsoluteTime();
        create_scene(world_size, patch_size, min_trees, max_trees, min_rocks, max_rocks);
        scene_create_time = m_oClock.GetAbsoluteTime() - scene_create_time;

        scene_setup_time = m_oClock.GetAbsoluteTime();
        amplificator.amplify(scene, camera);
        int pending;
        while ( (pending = amplificator.get_modelers_size() + amplificator.is_working()) )
        {
            m_oWnd.clear();
            psy::Main_Window::printfxy(m_iWidth/2 - 160, m_iHeight/2 -4, "Generating scene....\n");
            psy::Main_Window::printfxy(m_iWidth/2 - 160, m_iHeight/2 +4, "Number of objects in queues %d.\n", pending );
            m_oWnd.refresh();
        }
        scene_setup_time = m_oClock.GetAbsoluteTime() - scene_setup_time;

        if ( m_record_stats )
        {
            m_oHistFile.open( "stats.dat" );
            m_oHistFile << "## number of modelers: " << num_modelers << std::endl;
            m_oHistFile << "## total of system memory use for scene graph: " << system_memory << " megabytes" << std::endl;
            m_oHistFile << "## predicted scene size: " << predicted_gpu_memory << " megabytes" << std::endl;
            m_oHistFile << "## scene creating time: " << scene_create_time << " seconds" << std::endl;
            m_oHistFile << "## scene setup time: " << scene_setup_time << " seconds" << std::endl;
            m_oHistFile << "##" << std::endl;
            m_oHistFile << "## time  -  FPS  -  GPU memory use  -  working threads activity  -  objects in queue " << std::endl;
            m_oHistFile << "##" << std::endl;
        }

        cam_walk = psy::vec3::ZERO;
        m_start_time = m_oClock.GetAbsoluteTime();
        if (m_camera_fly)
        {
            m_start_walk = m_start_time;
            cv = 0;
            acc = 0.13f;
            dh = vdh[cv];
            vmax = vvmax[cv];
        }
    }

    void create_scene(int world_size, float patch_size, int min_trees, int max_trees, int min_rocks, int max_rocks);
    void create_patch(const char* name, float posx, float posz, float size, int min_trees, int max_trees, int min_rocks, int max_rocks,
                      psy::Node* terrain, psy::Node* tree, psy::Node* rock);


    virtual ~Test_World()
    {
        if ( m_record_stats )
        {
            m_oHistFile << "## total amplification time: " << total_amplification_time << std::endl;
            m_oHistFile.close();
        }
        amplificator.stop();
        amplificator.wait();
    }

    virtual void step()
    {
        if ( ( (m_oClock.GetAbsoluteTime()-m_start_time) > m_total_fly_time) && m_camera_fly )
            stop();

        float dt = m_oClock.GetFrameDuration();
        fps = m_oClock.GetFrameRate();
        real_gpu_memory = psy::Object::Manager.get_mem_usage();

        if ( (m_oClock.GetAbsoluteTime() > (m_start_walk + m_walk_time[cv])) && m_camera_fly )
        {
            m_start_walk = m_oClock.GetAbsoluteTime();
            cv++;
            dh = vdh[cv];
            vmax = vvmax[cv];
        }


        // Update camera position and orientation
        psy::vec3 fwd;
        camera->get_forward(fwd);
        float ddh = dh*dt;
        float ddp = dp*dt;
        h += ddh;
        p += ddp;
        if (dv < vmax && dv > -vmax)
            dv += acc*dt;
        else
            dv *= 0.93f;
        ds = dv*dt + acc*dt*dt*0.5f;
        psy::vec3 v_ds = ds*fwd;
        psy::vec3 pos = camera->world.getTranslate() + v_ds;
        if (m_camera_fly)
        {
            pos.y = height(pos.x + patch_size*0.5f, pos.z + patch_size*0.5f) + m_heigth;
            p = -M_PI/12;
        }
        camera->local.rotateYXZ ( h, p, 0 );
        camera->local.setPos ( pos );
        updater.update(camera);
        if (not m_camera_fly)
        {
            dh = 0.0f;
            dp = 0.0f;
        }
        dv *= damp;

        // update light direction
        light_dir.normalize();
        light->set_parameter2("direction", psy::vec4(-light_dir.x, -light_dir.y, -light_dir.z, 0.0f));

        renderer.render(scene, camera);
        if (show_bound_volume)
            bound_renderer.render(scene, camera);

        // simple prediction algorithm
        cam_walk += v_ds;
        if (length_sqr(cam_walk) > 0.75f*0.75f)// || cam_walk < -0.75f)
        {
            cam_walk = psy::vec3::ZERO;
            amplificator.amplify(scene, camera);
        }

        // calculate total amplification time
        int pending = amplificator.get_modelers_size();
        if (pending)
            total_amplification_time += m_oClock.GetFrameDuration();

        // record stats data
        if (m_record_stats)
            m_oHistFile << m_oClock.GetTime() << " \t "         // column 1: time
                        << fps << " \t "                        // column 2: fps
                        << real_gpu_memory << " \t "            // column 3: actual GPU memory use
                        << (pending>0) << " \t "                // column 4: is running PLA (0: no, 1: yes)
                        << pending                              // column 5: number of objects in queue
                        << std::endl;
    }

    inline float height(float x, float z) { return terrain_basis(psy::vec3(x,0, z), 0.9f, 2.0f, 2.0f, 0.4f, 4.0f); }
    inline psy::vec3 normal(float x, float z)
    {
        float dx = patch_size / (float)64;
        float dz = patch_size / (float)64;
        return psy::vec3(height(x-dx, z) - height(x+dx, z) , dx+dz , height(x, z-dz) - height(x, z+dz));
    }

    float h,p, dh,dp, ds, dv, acc, damp, vmax;


protected:
    psy::Amplificator   amplificator;
    psy::Renderer       renderer;
    psy::Bound_Renderer bound_renderer;
    psy::Updater        updater;
    psy::Memory_Predictor predictor;
    psy::Printer        printer;
    psy::Camera*        camera;
    psy::Node*          scene;

    psy::vec3 cam_walk;

    psy::Node*       world;
    psy::Attribute*  light;
    float patch_size;
    int min_trees;
    int max_trees;
    int min_rocks;
    int max_rocks;
    int world_size;

    psy::RidgedMultifractal  terrain_basis;
    psy::MTRand              rand;

    TwBar  *m_opBar;

    float m_heigth;

    std::ofstream  m_oHistFile;
    bool           m_record_stats;
    bool  m_camera_fly;
    float m_total_fly_time;
    float m_start_time;
    float m_start_walk;
    float m_walk_time[100];
    float vdh[100];
    float vvmax[100];
    int cv;

    psy::vec3  light_dir;
    bool       show_bound_volume;
    float      fps;
    float      total_amplification_time;
    float      real_gpu_memory;
    float      predicted_gpu_memory;
    float      system_memory;
    float      scene_create_time;
    float      scene_setup_time;
};



int main(int argc, char** argv)
{
    int arg=1;
    while (arg < argc)
    {
        if ( std::string(argv[arg]) == std::string("-modelers") )
        {
            arg++;
            num_modelers = atoi(argv[arg]);
        }
        arg++;
    }

    Test_World  app(argc, argv);
    return app.run();
}

ImplementEventHandler(SDLKeyDownHandler, event)
{
    switch (event.key.keysym.sym)
    {
        case SDLK_a:
            this->getListener()->acc = +0.3f;
            this->getListener()->damp = 1;
            break;

        case SDLK_z:
            this->getListener()->acc = -0.3f;
            this->getListener()->damp = 1;
            break;

        case SDLK_LSHIFT:
            this->getListener()->vmax = 0.138;
            break;

        default:;
    }
}

ImplementEventHandler(mouse_button_down, event)
{
    if (event.motion.state & SDL_BUTTON(1))
    {
        this->getListener()->dp = + event.motion.yrel*0.2f;
        this->getListener()->dh = - event.motion.xrel*0.2f;
    }
}

ImplementEventHandler(SDLKeyUpHandler, event)
{
    switch (event.key.keysym.sym)
    {
        case SDLK_a:
            this->getListener()->acc = 0;
            this->getListener()->damp = 0.93;
            break;

        case SDLK_z:
            this->getListener()->acc = 0;
            this->getListener()->damp = 0.93;
            break;

        case SDLK_LSHIFT:
            this->getListener()->vmax = 0.0666f;
            break;

        default:;
    }
}


void Test_World::create_scene(int world_size, float patch_size, int min_trees, int max_trees, int min_rocks, int max_rocks)
{
    scene = psy::Object::Manager.create_node("Node_Group", "scene");

    // Create directional light
    light = psy::Object::Manager.create_attr("Attr_Directional_Light", "light");
    light->set_parameter2("specular", psy::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    light->set_parameter2("ambient", psy::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    light->set_parameter2("diffuse", psy::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    light->set_parameter2("direction", psy::vec4(-light_dir.x, -light_dir.y, -light_dir.z, 0.0f));
    scene->insert_attribute(light);

    // Create terrain texture node
    psy::Node* terrain_texture_node = psy::Object::Manager.create_node("Node_Group", "terrain_texture_node");
    terrain_texture_node->reparent_to(scene);
    // Create terrain texture
    psy::Attribute* terrain_tex = psy::Object::Manager.create_attr("Attr_Texture2D_File", "terrain_texture");
    terrain_tex->set_parameter2("filename", std::string("grass.jpg"));
    terrain_tex->set_parameter2("size", PSY_BYTES_TO_MEGA(512*512*3) );
    terrain_texture_node->insert_attribute(terrain_tex);

    // Create tree texture Node
    psy::Node* tree_texture_node = psy::Object::Manager.create_node("Node_Group", "tree_texture_node");
    tree_texture_node->reparent_to(scene);
    // Create tree texture
    psy::Attribute* tree_tex = psy::Object::Manager.create_attr("Attr_Texture2D_File", "tree_texture");
    tree_tex->set_parameter2("filename", std::string("tree.png"));
    tree_tex->set_parameter2("size", PSY_BYTES_TO_MEGA(256*256*4) );
    tree_texture_node->insert_attribute(tree_tex);

    // Create rock texture node
    psy::Node* rock_texture_node = psy::Object::Manager.create_node("Node_Group", "rock_texture_node");
    rock_texture_node->reparent_to(scene);
    // Create rock texture
    psy::Attribute* rock_tex = psy::Object::Manager.create_attr("Attr_Texture2D_File", "rock_texture");
    rock_tex->set_parameter2("filename", std::string("rock.jpg"));
    rock_tex->set_parameter2("size", PSY_BYTES_TO_MEGA(256*256*3) );
    rock_texture_node->insert_attribute(rock_tex);

    float posx = 0.0f;
    for (int px = 0; px < world_size ; px++, posx += patch_size)
    {
        float posz = 0.0f;
        for (int pz = 0; pz < world_size ; pz++, posz += patch_size)
        {
            std::ostringstream world_node_name;
            world_node_name << "world_node[" << px << "][" << pz << "]";
            create_patch(world_node_name.str().c_str(), posx, posz, patch_size, min_trees, max_trees, min_rocks, max_rocks,
                         terrain_texture_node, tree_texture_node, rock_texture_node);
        }
    }

    float cam_pos = world_size/2;
    camera = psy::Object::Manager.create_camera("Camera", "camera");
    camera->set_perspective(45, (float)m_oWnd.getWidth() / m_oWnd.getHeight(), 0.0005f, 2.5f);
    camera->local.setPos(cam_pos , height(cam_pos, cam_pos) + m_heigth, cam_pos);
    camera->reparent_to(scene);

    // Create fog
    psy::Attribute* fog = psy::Object::Manager.create_attr("Attr_Fog", "fog");
    fog->set_parameter2("mode", GL_EXP2);
    fog->set_parameter2("color", psy::vec4(0.666, 0.666, 0.777, 1.0));
    fog->set_parameter2("density", 0.333f);
    fog->set_parameter2("start", 1.7f );
    fog->set_parameter2("end", 2.5f );
    scene->insert_attribute(fog);

    // Create flying times
    for (cv=0 ; cv<100 ; cv++)
    {
        m_walk_time[cv] = 5.f*rand() + 2.f;
        vdh[cv] = .25f*rand() - .125f;
        vvmax[cv] = 0.0666f + 0.0777*rand();
    }

    updater.update(scene);
    predictor.predict(scene);
    predicted_gpu_memory = predictor.get_gpu_memory();
    system_memory = PSY_BYTES_TO_MEGA(psy::Object::Manager.get_system_memory());
}


void Test_World::create_patch(const char* name, float posx, float posz, float size, int min_trees, int max_trees, int min_rocks, int max_rocks,
                              psy::Node* terrain_texture_node, psy::Node* tree_texture_node, psy::Node* rock_texture_node)
{
    m_oWnd.clear();
    psy::Main_Window::printfxy(m_iWidth/2 - 160, m_iHeight/2 -4, "Creating scene...\n");
    psy::Main_Window::printfxy(m_iWidth/2 - 160, m_iHeight/2 +4, "System memory use: %f megabytes\n", PSY_BYTES_TO_MEGA(psy::Object::Manager.get_system_memory()) );
    m_oWnd.refresh();

    // Create terrain node
    std::ostringstream terrain_node_name;
    terrain_node_name << name << ".terrain_node";
    psy::Node* terrain_node = psy::Object::Manager.create_node("Node_Group", terrain_node_name.str().c_str());
    terrain_node->local.setPos(posx , 0 , posz);

    std::ostringstream terrain_name;
    terrain_name << name << ".terrain";
    psy::Geometry* terrain = psy::Object::Manager.create_concrete<psy::Geom_Terrain_Patch>(terrain_name.str().c_str());
    terrain->set_parameter2("posX", posx);
    terrain->set_parameter2("posZ", posz);
    terrain->set_parameter2("sizeX", size);
    terrain->set_parameter2("sizeZ", size);
    terrain->set_parameter2("subdivisionsX", 128);
    terrain->set_parameter2("subdivisionsZ", 128);
    terrain->set_parameter2("H", 0.9f);
    terrain->set_parameter2("lacunarity", 2.0f);
    terrain->set_parameter2("octaves", 2.0f);
    terrain->set_parameter2("offset", 0.4f);
    terrain->set_parameter2("gain", 4.0f);
    terrain->set_parameter2("scale_v", 1.0f);
    terrain->set_parameter2("scale_h", 1.0f);
    terrain_node->insert_geometry(terrain);


    // Create trees Node
    std::ostringstream trees_node_name;
    trees_node_name << name << ".trees_node";
    psy::Node* trees_node = psy::Object::Manager.create_node("Node_Group", trees_node_name.str().c_str());
    trees_node->local.setPos(posx , 0 , posz);

    //create trees
    int path_trees = min_trees + rand()*(max_trees - min_trees);
    for (int i=0; i<path_trees; i++)
    {
        std::ostringstream tree_node_name;
        tree_node_name << trees_node_name.str() << ".tree_node[" << i << "]";
        psy::Node*  tree_node = psy::Object::Manager.create_node("Node_Group", tree_node_name.str().c_str());
        std::ostringstream tree_name;
        tree_name << trees_node_name.str() << ".tree" << i << "]";
        psy::Geometry* tree = psy::Object::Manager.create_geom("Geom_Tree", tree_name.str().c_str());
        tree->set_parameter2("seed", i);
        tree->set_parameter2("size", 0.003f + (float)rand()*0.003f);
        tree->set_parameter2("radius", 0.00085f  + (float)rand()*0.0001f);
        tree->set_parameter2("iterations", 2);
        tree->set_parameter2("min_branches", 3);
        tree->set_parameter2("max_branches", 3);
        tree->set_parameter2("segments", 1);
        tree->set_parameter2("subdivisions", 3);
        tree_node->insert_geometry(tree);
        float x;
        float z;
        float y;
        psy::vec3  n;
        do
        {
            x = size*rand();
            z = size*rand();
            y = height(x + posx, z + posz);
            n = normal(x + posx,z + posz);
            n.normalize();
        }
        while (dot(n,psy::vec3::UY) < 0.95f || y > 0.08f);
        tree_node->local.setPos(x - size*0.5f , y , z - size*0.5f);
        tree_node->reparent_to(trees_node);
    }

    // Create rocks Node
    std::ostringstream rocks_node_name;
    rocks_node_name << name << ".rocks_node";
    psy::Node* rocks_node = psy::Object::Manager.create_node("Node_Group", rocks_node_name.str().c_str());
    rocks_node->local.setPos(posx , 0 , posz);

    //create rocks
    int path_rocks = min_rocks + rand()*(max_rocks-min_rocks);
    for (int i=0; i<path_rocks; i++)
    {
        std::ostringstream rock_node_name;
        rock_node_name << rocks_node_name.str() << ".rock_node[" << i << "]";
        psy::Node*  rock_node = psy::Object::Manager.create_node("Node_Group", rock_node_name.str().c_str());
        std::ostringstream rock_name;
        rock_name << rocks_node_name.str() << ".rock[" << i << "]";
        psy::Geometry* rock = psy::Object::Manager.create_geom("Geom_Asteroid", rock_name.str().c_str());
        rock->set_parameter2("seed", i);
        rock->set_parameter2("radius", 0.005f + (float)rand()*0.03f);
        rock->set_parameter2("amplitude", 2.0f);
        rock->set_parameter2("decay", 0.0f);
        rock->set_parameter2("subdivisions", 2);
        rock_node->insert_geometry(rock);
        float x;
        float z;
        float y;
        psy::vec3  n;
        do
        {
            x = size*rand();
            z = size*rand();
            y = height(x + posx, z + posz) + 0.001f;
            n = normal(x + posx, z + posz);
            n.normalize();
        }
        while (dot(n,psy::vec3::UY) > 0.75f  || y < 0.1f);
        rock_node->local.setPos(x - size*0.5f , y , z - size*0.5f);
        rock_node->reparent_to(rocks_node);
    }

    trees_node->reparent_to(tree_texture_node);
    rocks_node->reparent_to(rock_texture_node);
    terrain_node->reparent_to(terrain_texture_node);
}
