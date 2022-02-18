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
    *  \brief ________
    *  \ingroup PSYengine
    *
    *//***********************************************************************/
#include <GL/glew.h>
#include <cstdlib>

#include "PSYGEN/PSYengine/Geom_Asteroid.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Geom_Asteroid, Geom_Vbo)
{
    m_sys_memory_use = sizeof(*this);

    bind_parameter2(Parameter::INT,   "seed", &seed, 0);
    bind_parameter2(Parameter::FLOAT, "radius", &radius, 0.0f);
    bind_parameter2(Parameter::FLOAT, "amplitude", &amplitude, 0);
    bind_parameter2(Parameter::FLOAT, "decay", &decay, 0);
    bind_parameter2(Parameter::INT,   "subdivisions", &subdivisions, 0);
}



void Geom_Asteroid::amplify(Mutex* mutex)
{
    //if (m_eState == SHRINKED)
    //{
        //std::cout << "amplify Geom_Asteroid: name = \"" << get_name() << "\"" << std::endl;
        //std::cout << "   seed = " << seed << std::endl;
        //std::cout << "   radius = " << radius << std::endl;
        //std::cout << "   amplitude = " << amplitude << std::endl;
        //std::cout << "   decay = " << decay << std::endl;
        //std::cout << "   subdivisions = " << subdivisions << std::endl;

        const float a=0.57735026918963f;
        const float v=a*radius;

        m_kVertices = std::vector<vec3> (4);
        m_kNormals = std::vector<vec3> (4);
        //m_kColors = std::vector<vec3> (4);
        m_kTexCoords = std::vector<vec3> (4);
        m_kIndices = std::vector<unsigned int> (12);

        m_kVertices[0] = vec3(v ,  v ,  v);
        m_kVertices[1] = vec3(-v ,  v , -v);
        m_kVertices[2] = vec3(v , -v , -v);
        m_kVertices[3] = vec3(-v , -v ,  v);

        m_kNormals[0] = vec3(a ,  a ,  a);
        m_kNormals[1] = vec3(-a ,  a , -a);
        m_kNormals[2] = vec3(a , -a , -a);
        m_kNormals[3] = vec3(-a , -a ,  a);

//         m_kColors[0] = vec3(1.0 , 1.0 , 1.0);
//         m_kColors[1] = vec3(1.0 , 1.0 , 1.0);
//         m_kColors[2] = vec3(1.0 , 1.0 , 1.0);
//         m_kColors[3] = vec3(1.0 , 1.0 , 1.0);

        m_kTexCoords[0] = vec3(1.0 , 1.0 , 0.0);
        m_kTexCoords[1] = vec3(0.0 , 1.0 , 0.0);
        m_kTexCoords[2] = vec3(1.0 , 0.0 , 0.0);
        m_kTexCoords[3] = vec3(0.0 , 0.0 , 0.0);

        m_kIndices[0]=1 ; m_kIndices[1]=0 ; m_kIndices[2]=2;
        m_kIndices[3]=1 ; m_kIndices[4]=3 ; m_kIndices[5]=0;
        m_kIndices[6]=2 ; m_kIndices[7]=0 ; m_kIndices[8]=3;
        m_kIndices[9]=2 ; m_kIndices[10]=3 ; m_kIndices[11]=1;

        unsigned int pow4 = 1<< (2* (subdivisions+1));
/*        std::cout << "T: " << pow4 << std::endl;
        std::cout << "I: " << pow4/2 + 2 << std::endl;*/
        EdjeMap edje_map(pow4/2 + 2);
        m_opEdjeMap = &edje_map;

        srand(seed);
        _subdivide(subdivisions, amplitude, decay);


        //m_opSphere_Vbo = new Gl_Vbo();
        //m_opSphere_Vbo->set_parent(this);
        create(m_kVertices[0], m_kNormals[0], /*m_kColors[0],*/ m_kTexCoords[0], & (m_kIndices[0]),
                               3*m_kVertices.size(), m_kIndices.size(), GL_TRIANGLES);

        m_gpu_memory_use = PSY_BYTES_TO_MEGA (m_kVertices.size()*12 +
                       m_kNormals.size()*12 +
                       m_kTexCoords.size()*12 +
                       m_kIndices.size()*4);
        //m_gpu_memory_use *= 1.0f/(1024.0f*1024.0f);

//         std::cout << "m_kVertices.size(): " << m_kVertices.size() << std::endl;
//         std::cout << "m_kIndices.size(): " << m_kIndices.size() << std::endl;
//         std::cout << "triangles: " << m_kIndices.size()/3 << std::endl;

        glFlush();
        // Clean-up memory, the new sphere is now in GPU memory
        m_kVertices.clear();
        m_kNormals.clear();
        //m_kColors.clear();
        m_kTexCoords.clear();
        m_kIndices.clear();
        //delete m_opEdjeMap;

        // Now, the object state is synthetic
        if (mutex) mutex->lock();
        Object::Manager.inc_mem_usage( m_gpu_memory_use );
        m_eState = AMPLIFIED;
        if (mutex) mutex->unlock();
    //}
}



void Geom_Asteroid::shrink(Mutex* mutex)
{
    //if (m_eState == AMPLIFIED)
    //{
        //std::cout << "shrink Geom_Asteroid: name = \"" << get_name() << "\"" << std::endl;
        destroy();

        if (mutex) mutex->lock();
        m_eState = SHRINKED;
        Object::Manager.dec_mem_usage( m_gpu_memory_use );
        if (mutex) mutex->unlock();
        m_gpu_memory_use = 0;
    //}
}



float Geom_Asteroid::estimate_mem_usage()
{
    int num_tris = 1<< (2* (subdivisions+1));
    int num_ndxs = num_tris/2 + 2;
    return PSY_BYTES_TO_MEGA(num_ndxs*36 + num_tris*12);
}



float Geom_Asteroid::estimate_time_usage()
{
    return 0.0f;
}



void Geom_Asteroid::draw()
{
    if (m_eState == AMPLIFIED)
        Geom_Vbo::draw();
}


void Geom_Asteroid::calc_bound_volume()
{
    local_bound.pos = vec3::ZERO;
    local_bound.rad = radius + radius*amplitude;
}


void Geom_Asteroid::_subdivide(unsigned int uiNumSub, float fAmp, float fDec)
{
    int i0, i1, i2;
    int i01, i02, i12;
    unsigned int uiNumIndxs;
    vec3 vrBarycenter;


    // iterative subdivision
    for (unsigned int sub=0; sub<uiNumSub; sub++)
    {
        // calculate the barycenter of asteroid
        vrBarycenter = vec3::ZERO;
        for (unsigned int i=0; i<m_kVertices.size(); i++)
            vrBarycenter += m_kVertices[i];
        vrBarycenter *= 1.0f/m_kVertices.size();

        // for each triangle
        uiNumIndxs = (unsigned int) m_kIndices.size();
/*        std::cout << "sub: " << sub << std::endl;
        std::cout << "uiNumIndxs: " << uiNumIndxs << std::endl;
        std::cout << "num tris: " << uiNumIndxs/3 << std::endl;*/
        for (unsigned int tri=0; tri<uiNumIndxs; tri+=3)
        {
            i0 = m_kIndices[tri];
            i1 = m_kIndices[tri+1];
            i2 = m_kIndices[tri+2];

            i01 = _midPoint(i0, i1, fAmp, vrBarycenter);
            i02 = _midPoint(i0, i2, fAmp, vrBarycenter);
            i12 = _midPoint(i1, i2, fAmp, vrBarycenter);

            m_kIndices[tri] = i02;
            m_kIndices[tri+1] = i01;
            m_kIndices[tri+2] = i12;

            unsigned int ind[9] = { i0, i01, i02 ,
                                    i1, i12, i01 ,
                                    i2, i02, i12
                                  };
            m_kIndices.insert(m_kIndices.end(), ind, ind+9);
        }
        fAmp *= fDec;
    }

    // Barycenter is origin
    if (uiNumSub>0)
        for (unsigned int i=0; i<m_kVertices.size(); i++)
            m_kVertices[i] -= vrBarycenter ;
}



unsigned int Geom_Asteroid::_midPoint(unsigned int i1, unsigned int i2, float fAmp, vec3 &vrBarycenter)
{
    int i = m_opEdjeMap->getMidVertex(i1,i2);

    //std::cout << "getMidVertex" << i;

    // test if edje has already subdivided
    if (i == -1)
    {
        // Create new vertex
        vec3 v;
        float d, l, r;

        // Calculate vertex position
        i = (unsigned int) m_kVertices.size();
        v = (m_kVertices[i1]+m_kVertices[i2])*0.5f;
        r = (length(m_kVertices[i1]-vrBarycenter) +
             length(m_kVertices[i2]-vrBarycenter))/2.0f;
        l = fAmp*length(m_kVertices[i1]-m_kVertices[i2]);
        d = (float(rand())/RAND_MAX)-0.5f;
        v -= vrBarycenter;
        v.normalize();
        v *= (r+d*l/2.0f);
        v += vrBarycenter;
        m_kVertices.push_back(v);

        // Calculate normal
        v.normalize();
        m_kNormals.push_back(v);

        // Calculate color
        //m_kColors.push_back((m_kColors[i1]+m_kColors[i2])*0.5f);

        // Calculate texture coord
        m_kTexCoords.push_back((m_kTexCoords[i1]+m_kTexCoords[i2])*0.5f);

        // assign new vertex on edje matrix
        m_opEdjeMap->setMidVertex(i1,i2, i);

    }
    return i;
}


}//////////////////////////////////////////////////////////////////////////////
