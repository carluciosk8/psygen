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
#include <sstream>

#include "PSYGEN/PSYmath/Random.hpp"

#include "PSYGEN/PSYengine/Node_World.hpp"
#include "PSYGEN/PSYengine/Updater.hpp"
#include "PSYGEN/PSYengine/Amplificator.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Node_World, Node_Group)
{
    bind_parameter2(Parameter::INT, "num_trees", &num_trees, 0);
    bind_parameter2(Parameter::INT, "num_rocks", &num_rocks, 0);
    bind_parameter2(Parameter::FLOAT, "size_x", &size_x, 0.0f);
    bind_parameter2(Parameter::FLOAT, "size_z", &size_z, 0.0f);
    bind_parameter2(Parameter::FLOAT, "pos_x", &pos_x, 0.0f);
    bind_parameter2(Parameter::FLOAT, "pos_z", &pos_z, 0.0f);

    created = false;

    std::ostringstream terrain_name;
    terrain_name << m_name << "_terrain";
    terrain = psy::Object::Manager.create_concrete<psy::Geom_Terrain_Patch>(terrain_name.str().c_str());
}



void Node_World::amplify(Mutex*)
{
    if (m_eState == SHRINKED)
    {
        //std::cout << "amplify Node_World: name = \"" << get_name() << "\"" << std::endl;

        if (not created)
        {
            created = true;
            create();
        }
        // Now, the object state is synthetic
        m_eState = AMPLIFIED;
    }
}



void Node_World::shrink(Mutex*)
{
    if (m_eState == AMPLIFIED)
    {
        //std::cout << "shrink Node_World: name = \"" << get_name() << "\"" << std::endl;

        //destroy();
        //trees->destroy();
        //terrains->destroy();
        //psy::Object::Manager.destroy(trees);
        //psy::Object::Manager.destroy(terrains);

        m_eState = SHRINKED;
    }
}



float Node_World::estimate_mem_usage()
{
    if (not created)
    {
        int trees_gpu_mem = 23400;

        int rocks_subdivs = 2;
        int num_tris = 1<< (2* (rocks_subdivs+1));
        int num_ndxs = num_tris/2 + 2;
        int rocks_gpu_mem = num_ndxs*48 + num_tris*12;

        int subdivisionsX = 64;
        int subdivisionsZ = 64;
        int terrain_gpu_mem = (subdivisionsX+1)*(subdivisionsZ+1)*48 + (subdivisionsX)*(subdivisionsZ)*24;

        int trees_tex_gpu_mem = 1024*1024*4;
        int rocks_tex_gpu_mem = 256*256*3;
        int terrain_tex_gpu_mem = 512*512*3;

        return PSY_BYTES_TO_MEGA (num_trees*trees_gpu_mem + num_rocks*rocks_gpu_mem + terrain_gpu_mem +
               trees_tex_gpu_mem + rocks_tex_gpu_mem + terrain_tex_gpu_mem );
    }
    else
        return Node_Group::estimate_mem_usage();
}



float Node_World::estimate_time_usage()
{
    return 0.0f;
}



bool Node_World::update_bound()
{
    if (m_eState == SHRINKED && not created)
    {
         world_bound.pos = world.getTranslate();
         world_bound.rad = size_x*0.5f*1.41f;
         return false;
    }
    else
        return Node_Group::update_bound();
}



void Node_World::create()
{
        Updater  upd;
        MTRand  rand;
        rand.seed(270);


        // Create terrain node
        std::ostringstream terrain_node_name;
        terrain_node_name << m_name << "_terrain_node";
        terrain_node = psy::Object::Manager.create_node("Node_Group", terrain_node_name.str().c_str());

        std::ostringstream terrain_tex_name;
        terrain_tex_name << m_name << "_terrain_tex";
        Attribute* terrain_tex = psy::Object::Manager.create_attr("Attr_Texture2D_File", terrain_tex_name.str().c_str());
        //std::string terrain_tex_filename("sand.jpg");
        terrain_tex->set_parameter2("filename", std::string("sand.jpg") );
        //terrain_node->insert_attribute( terrain_tex );

        terrain->set_parameter2("posX", pos_x);
        terrain->set_parameter2("posZ", pos_z);
        terrain->set_parameter2("sizeX", size_x);
        terrain->set_parameter2("sizeZ", size_z);
        terrain->set_parameter2("subdivisionsX", 64);
        terrain->set_parameter2("subdivisionsZ", 64);
        terrain->set_parameter2("H", 0.0f);
        terrain->set_parameter2("lacunarity", 0.0f);
        terrain->set_parameter2("octaves", 1.0f);
        terrain->set_parameter2("offset", 0.0f);
        terrain->set_parameter2("gain", 0.0f);
        terrain_node->insert_geometry(terrain);


        // Create trees Node
        std::ostringstream trees_node_name;
        trees_node_name << m_name << "_trees_node";
        trees_node = psy::Object::Manager.create_concrete<psy::Node_Group>(trees_node_name.str().c_str());

        std::ostringstream tree_tex_name;
        tree_tex_name << m_name << "_tree_tex";
        Attribute* tree_tex = psy::Object::Manager.create_attr("Attr_Texture2D_File", tree_tex_name.str().c_str());
        tree_tex->set_parameter2("filename", std::string("tree.png") );
        //trees_node->insert_attribute(tree_tex);

        //create trees
        for (int i=0; i<num_trees; i++)
        {
            std::ostringstream tree_node_name;
            tree_node_name << trees_node_name.str() << "_tree_node_" << i;
            Node*  tree_node = psy::Object::Manager.create_node( "Node_Group", tree_node_name.str().c_str() );
            std::ostringstream tree_name;
            tree_name << trees_node_name.str() << "_tree_" << i;
            Geometry* tree = psy::Object::Manager.create_geom( "Geom_Tree", tree_name.str().c_str() );
            tree->set_parameter2("seed", i);
            tree->set_parameter2("size", 0.01f + (float)rand()*0.01f );
            tree->set_parameter2("radius", 0.0016f  + (float)rand()*0.0017f );
            tree->set_parameter2("iterations", 2 );
            tree->set_parameter2("min_branches", 3 );
            tree->set_parameter2("max_branches", 3 );
            tree->set_parameter2("segments", 1);
            tree->set_parameter2("subdivisions", 3);
            tree_node->insert_geometry(tree);
            float x;
            float z;
            float y;
            //vec3  n;
            //do
            {
                x = size_x*rand();
                z = size_z*rand();
                y = terrain->height(x + pos_x,z + pos_z);
                //n = terrain->normal(x + pos_x,z + pos_z);
                //n.normalize();
            }
            //while ( dot(n,vec3::UY) < 0.8f );
            tree_node->local.setPos( x - size_x*0.5f , y , z - size_z*0.5f );
            tree_node->reparent_to(trees_node);
        }

        // Create rocks Node
        std::ostringstream rocks_node_name;
        rocks_node_name << m_name << "_rocks_node";
        rocks_node = psy::Object::Manager.create_concrete<psy::Node_Group>(rocks_node_name.str().c_str());

        std::ostringstream rock_tex_name;
        rock_tex_name << m_name << "_rock_tex";
        Attribute* rock_tex = psy::Object::Manager.create_attr("Attr_Texture2D_File", rock_tex_name.str().c_str());
        rock_tex->set_parameter2("filename", std::string("rock.jpg") );
        //rocks_node->insert_attribute(rock_tex);

        //create rocks
        for (int i=0; i<num_rocks; i++)
        {
            std::ostringstream rock_node_name;
            rock_node_name << rocks_node_name.str() << "_rock_node_" << i;
            Node*  rock_node = psy::Object::Manager.create_node( "Node_Group", rock_node_name.str().c_str() );
            std::ostringstream rock_name;
            rock_name << rocks_node_name.str() << "_rock_" << i;
            Geometry* rock = psy::Object::Manager.create_geom( "Geom_Asteroid", rock_name.str().c_str() );
            rock->set_parameter2("seed", i);
            rock->set_parameter2("radius", 0.005f + (float)rand()*0.02f );
            rock->set_parameter2("amplitude", 2.0f );
            rock->set_parameter2("decay", 0.0f );
            rock->set_parameter2("subdivisions", 2);
            rock_node->insert_geometry(rock);
            float x;
            float z;
            float y;
            //vec3  n;
            //do
            {
                x = size_x*rand();
                z = size_z*rand();
                y = terrain->height(x + pos_x,z + pos_z);
                //n = terrain->normal(x + pos_x,z + pos_z);
                //n.normalize();
            }
            //while ( dot(n,vec3::UY) < 0.8f );
            rock_node->local.setPos( x - size_x*0.5f , y , z - size_z*0.5f );
            rock_node->reparent_to(rocks_node);
        }

        trees_node->reparent_to(this);
        rocks_node->reparent_to(this);
        terrain_node->reparent_to(this);

        upd.inspect(this);

        Amplificator::GetSingleton().requestModel(this);
}


}//////////////////////////////////////////////////////////////////////////////
