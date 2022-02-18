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

#include "PSYGEN/PSYmath/Transforms.hpp"

#include "PSYGEN/PSYengine/Geom_Tree.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Geom_Tree, Geom_Vbo)
{
    m_sys_memory_use = sizeof(*this);

    bind_parameter2(Parameter::INT,   "seed", &seed, 0);
    bind_parameter2(Parameter::FLOAT, "size", &size, 0.0f);
    bind_parameter2(Parameter::FLOAT, "radius", &radius, 0.0f);
    bind_parameter2(Parameter::INT,   "iterations", &iterations, 0);
    bind_parameter2(Parameter::INT,   "min_branches", &min_branches, 0);
    bind_parameter2(Parameter::INT,   "max_branches", &max_branches, 0);
    bind_parameter2(Parameter::INT,   "segments", &segments, 0);
    bind_parameter2(Parameter::INT,   "subdivisions", &subdivisions, 0);
}



void Geom_Tree::amplify(Mutex* mutex)
{
    //if (m_eState == SHRINKED)
    //{
//         std::cout << "amplify Geom_Tree: name = \"" << get_name() << "\"" << std::endl;
//         std::cout << "   seed = " << seed << std::endl;
//         std::cout << "   size = " << size << std::endl;
//         std::cout << "   radius = " << radius << std::endl;
//         std::cout << "   iterations = " << iterations << std::endl;
//         std::cout << "   min_branches = " << min_branches << std::endl;
//         std::cout << "   max_branches = " << max_branches << std::endl;
//         std::cout << "   segments = " << segments << std::endl;
//         std::cout << "   subdivisions = " << subdivisions << std::endl;

        m_oGenerator.seed(seed);
        float dx = size*0.2f*(m_oGenerator() - 0.5f);
        float dz = size*0.2f*(m_oGenerator() - 0.5f);
        Branch trunk(size, radius, segments, subdivisions, dx, dz);
        trunk.generate(m_oBuffer);
        recursiveGenerate(trunk, m_oBuffer, iterations, min_branches, max_branches, segments, subdivisions);


        create(m_oBuffer.m_oVertices[0],
               m_oBuffer.m_oNormals[0],
               m_oBuffer.m_oTexCoords[0],
               &(m_oBuffer.m_oIndices[0]),
               3*m_oBuffer.m_oVertices.size(),
               m_oBuffer.m_oIndices.size(),
               GL_TRIANGLES);

        // Memory use
        m_gpu_memory_use = PSY_BYTES_TO_MEGA (m_oBuffer.m_oVertices.size()*12 +
                       m_oBuffer.m_oNormals.size()*12 +
                       m_oBuffer.m_oTexCoords.size()*12 +
                       m_oBuffer.m_oIndices.size()*4);

        glFlush();
        m_oBuffer.clear();

        // Now, the object state is synthetic
        if (mutex) mutex->lock();
        m_eState = AMPLIFIED;
        Object::Manager.inc_mem_usage( m_gpu_memory_use );
        if (mutex) mutex->unlock();
    //}
}



void Geom_Tree::shrink(Mutex* mutex)
{
    //if (get_state() == AMPLIFIED)
    //{
//         std::cout << "shrink Geom_Tree: name = \"" << get_name() << "\"" << std::endl;
        //m_eState = SHRINKED;

        destroy();

        //glFlush();

        if (mutex) mutex->lock();
        m_eState = SHRINKED;
        Object::Manager.dec_mem_usage( m_gpu_memory_use );
        if (mutex) mutex->unlock();
        m_gpu_memory_use = 0;
    //}
}



float Geom_Tree::estimate_mem_usage()
{
    int num_branches = (pow( max_branches, iterations+1)-1) / (max_branches-1);
    int num_leafs = 3 * pow(max_branches, iterations);
    return PSY_BYTES_TO_MEGA
    (
        num_branches * (subdivisions) * (segments+1) * 36 +
        num_branches * (subdivisions)*(segments)*24 +
        num_leafs *4*36 +
        num_leafs *48
    );
}



float Geom_Tree::estimate_time_usage()
{
    return 0.0f;
}



void Geom_Tree::draw()
{
    if (m_eState == AMPLIFIED)
        Geom_Vbo::draw();
}



void Geom_Tree::calc_bound_volume()
{
    local_bound.pos = vec3(0,size*1.5f,0);
    local_bound.rad = size*1.5f;
}



void Geom_Tree::recursiveGenerate(Branch& r_branch, GeometryBuffer& r_buffer, int iter, int minbr, int maxbr, int segs, int  subdivs)
{
    if (iter>0)
    {
        if (segs>1) segs--;
        if (subdivs>3) subdivs--;

        int branches = (maxbr-minbr+1)*m_oGenerator() + minbr;
        float da = 2*PI/branches;
        float a=0;
        for (int c=0 ; c<branches ; c++)
        {
            float dx = r_branch.m_fSize*0.2f*(m_oGenerator() - 0.5f);
            float dz = r_branch.m_fSize*0.2f*(m_oGenerator() - 0.5f);
            Branch twig(r_branch.m_fSize*0.666f, r_branch.m_fRadius*0.666f, segs, subdivs, dx, dz);
            float dh = 0.8f*(m_oGenerator() - 0.5f);
            float dp = 0.8f*(m_oGenerator() - 0.5f);
            r_branch.addBranch(twig, r_buffer, 0.999f, PI*0.25f+dp, a+dh);
            recursiveGenerate(twig, r_buffer, iter-1, minbr, maxbr, segs, subdivs);
            a += da;
        }
    }
    else // add leaves
    {
        float phi = 0;
        for (uint i=0 ; i<3 ; i++)
        {
            Leaf r_leaf = (r_branch.m_fSize);
            float dh = 0.4f*(m_oGenerator() - 0.5f);
            float dy = 0.4f*(m_oGenerator() - 0.5f);
            r_branch.addLeaf(r_leaf, r_buffer, 1.0f, PI/3+dy, phi+dh);
            phi += 2.0f*PI/3;
        }
    }
}


Branch::Branch(float fSize, float fRadius, int uiSegments, int  uiSubdivs, float dx, float dz)
        :
        m_vPos(vec3::ZERO),
        m_vDir(vec3::UY),
        m_fSize(fSize),
        m_fSizeDec(0.9f),
        m_fRadius(fRadius),
        m_fRadiusDec(0.9f),
        m_uiSegments(uiSegments),
        m_uiSubdivs(uiSubdivs),
        m_mRot(mat3::IDENTITY),
        m_oBranchMesh((uiSegments+1)*(uiSubdivs) , 3*2*(uiSegments)*(uiSubdivs)),
        oSpline(vec3::ZERO, 2*fSize*vec3::UY, vec3(dx, fSize, dz), 2*fSize*vec3::UY)
{}



Branch::~Branch()
{
}



void Branch::generate(GeometryBuffer& orBuffer)
{
    float rad = m_fRadius;
    float endRad = m_fRadius*0.6f;
    float dr = (m_fRadius - endRad)/m_uiSegments;


    // Generate Vertices
    float t = 0;
    float dt = 1.0f/m_uiSegments;
    float s = 0;
    float ds = 1.0f/m_uiSubdivs;
    float dphi = 2*PI/(m_uiSubdivs);
    for (int i=0 ; i<m_uiSegments+1 ; i++)
    {
        vec3  p;// = oSpline(t);
        vec3  v;
        oSpline.pos(p, t);
        oSpline.vel(v, t);
        vec3  vx(1 , -v.x/v.y , 0);
        vec3  vz(0 , -v.z/v.y , 1);
        v.normalize();
        vx.normalize();
        vz.normalize();
        mat3  r(vx.x , v.x , vz.x ,
                vx.y , v.y , vz.y ,
                vx.z , v.z , vz.z);
        float phi = 0;
        s = 0;
        for (int j=0 ; j<m_uiSubdivs ; j++)
        {
            int index = m_uiSubdivs*i + j;

            vec3 wp(cos(phi) , 0 , sin(phi));
            wp = r*wp;

            m_oBranchMesh.m_oNormals[index].mul(m_mRot, wp);
            m_oBranchMesh.m_oNormals[index].normalize();

            wp *= rad;
            wp += p;

            m_oBranchMesh.m_oVertices[index].mul(m_mRot, wp);
            m_oBranchMesh.m_oVertices[index] += m_vPos;

            m_oBranchMesh.m_oTexCoords[index].x = s*0.5f;//j;
            m_oBranchMesh.m_oTexCoords[index].y = t*0.5f;//i;
            m_oBranchMesh.m_oTexCoords[index].z = 0;

            s += ds;
            phi += dphi;
        }
        t += dt;
        rad -= dr;
    }

    // Generate triangles
    int pos = 0;
    for (int i=0 ; i<m_uiSegments ; i++)
    {
        for (int j=0 ; j<m_uiSubdivs-1 ; j++)
        {
            int index = i*m_uiSubdivs + j;

            m_oBranchMesh.m_oIndices[pos] = index ; pos++;
            m_oBranchMesh.m_oIndices[pos] = index + m_uiSubdivs ; pos++;
            m_oBranchMesh.m_oIndices[pos] = index + 1 ; pos++;

            m_oBranchMesh.m_oIndices[pos] = index + 1 ; pos++;
            m_oBranchMesh.m_oIndices[pos] = index + m_uiSubdivs ; pos++;
            m_oBranchMesh.m_oIndices[pos] = index + m_uiSubdivs + 1 ; pos++;
        }
        m_oBranchMesh.m_oIndices[pos] = i*m_uiSubdivs ; pos++;
        m_oBranchMesh.m_oIndices[pos] = i*m_uiSubdivs + m_uiSubdivs-1 ; pos++;
        m_oBranchMesh.m_oIndices[pos] = i*m_uiSubdivs + 2*m_uiSubdivs-1 ; pos++;

        m_oBranchMesh.m_oIndices[pos] = i*m_uiSubdivs + m_uiSubdivs ; pos++;
        m_oBranchMesh.m_oIndices[pos] = i*m_uiSubdivs ; pos++;
        m_oBranchMesh.m_oIndices[pos] = i*m_uiSubdivs + 2*m_uiSubdivs-1 ; pos++;
    }

    orBuffer.append(m_oBranchMesh);
}



void Branch::addBranch(Branch& r_branch, GeometryBuffer& r_buffer, float fPos, float fZenith, float fAzimuth)//const vec3& vrDir)
{
    vec3  vDir(cos(fAzimuth)*sin(fZenith), cos(fZenith) , sin(fAzimuth)*sin(fZenith));

    // Rotation matrix
    vec3 uz;
    vec3 ux;
    uz.cross(vec3::UX, vDir);
    ux.cross(vDir, uz);
    mat3 mLocal = mat3(ux.x , vDir.x , uz.x ,
                       ux.y , vDir.y , uz.y ,
                       ux.z , vDir.z , uz.z);


    r_branch.m_mRot.mul(m_mRot, mLocal);
    r_branch.m_vDir.x = r_branch.m_mRot.m[0][1];
    r_branch.m_vDir.y = r_branch.m_mRot.m[1][1];
    r_branch.m_vDir.z = r_branch.m_mRot.m[2][1];

    vec3 p;
    oSpline.pos(p, fPos);
    r_branch.m_vPos = m_vPos + m_mRot*p;

    r_branch.generate(r_buffer);
}



void Branch::addLeaf(Leaf& r_leaf, GeometryBuffer& r_buffer, float fPos, float fZenith, float fAzimuth)//const vec3& vrDir)
{
    vec3  vDir(cos(fAzimuth)*sin(fZenith), cos(fZenith) , sin(fAzimuth)*sin(fZenith));

    // Rotation matrix
    vec3 uz;
    vec3 ux;
    uz.cross(vec3::UX, vDir);
    ux.cross(vDir, uz);
    //mat3 mLocal = mat3(ux.x , vDir.x , uz.x ,
    //                ux.y , vDir.y , uz.y ,
    //                ux.z , vDir.z , uz.z );

    mat3 mLocal;
    rotateYXZ(mLocal, fAzimuth, fZenith, 0);

    r_leaf.m_mRot.mul(m_mRot, mLocal);
    r_leaf.m_vDir.x = r_leaf.m_mRot.m[0][1];
    r_leaf.m_vDir.y = r_leaf.m_mRot.m[1][1];
    r_leaf.m_vDir.z = r_leaf.m_mRot.m[2][1];

    vec3 p;
    oSpline.pos(p, fPos);
    r_leaf.m_vPos = m_vPos + m_mRot*p;

    r_leaf.generate(r_buffer);
}









Leaf::Leaf(float fSize)
        :
        m_vPos(vec3::ZERO),
        m_vDir(vec3::UY),
        m_fSize(fSize),
        m_mRot(mat3::IDENTITY),
        m_oBranchMesh(4, 12)
{}



Leaf::~Leaf()
{
}



void Leaf::generate(GeometryBuffer& orBuffer)
{
    vec3 vertices[] = { vec3(-m_fSize*0.5f, 0, 0),  vec3(-m_fSize*0.5f, m_fSize, 0),   vec3(m_fSize*0.5f, m_fSize, 0) ,  vec3(m_fSize*0.5f, 0, 0)  };
    vec3 normals[] = { vec3(-1, -1, -1),  vec3(-1, 1, -1),   vec3(1, 1, -1),  vec3(1, -1, -1)  };
    vec3 txcoords[] = { vec3(0.55f, 0.45f, 0),  vec3(0.55f, 0.05f, 0),   vec3(0.95f, 0.05f, 0),   vec3(0.95f, 0.45f, 0)  };
    uint triindxs[] = { 3, 1, 0,   2, 3, 1 };


    // Generate Vertices
    m_oBranchMesh.m_oVertices[0] = m_vPos + m_mRot*vertices[0];
    m_oBranchMesh.m_oVertices[1] = m_vPos + m_mRot*vertices[1];
    m_oBranchMesh.m_oVertices[2] = m_vPos + m_mRot*vertices[2];
    m_oBranchMesh.m_oVertices[3] = m_vPos + m_mRot*vertices[3];

    m_oBranchMesh.m_oNormals[0].mul(m_mRot, normals[0]);
    m_oBranchMesh.m_oNormals[1].mul(m_mRot, normals[1]);
    m_oBranchMesh.m_oNormals[2].mul(m_mRot, normals[2]);
    m_oBranchMesh.m_oNormals[3].mul(m_mRot, normals[3]);

    m_oBranchMesh.m_oTexCoords[0] = txcoords[0];
    m_oBranchMesh.m_oTexCoords[1] = txcoords[1];
    m_oBranchMesh.m_oTexCoords[2] = txcoords[2];
    m_oBranchMesh.m_oTexCoords[3] = txcoords[3];

    // Generate triangles
    m_oBranchMesh.m_oIndices[0] = triindxs[0];
    m_oBranchMesh.m_oIndices[1] = triindxs[2];
    m_oBranchMesh.m_oIndices[2] = triindxs[1];

    m_oBranchMesh.m_oIndices[3] = triindxs[0];
    m_oBranchMesh.m_oIndices[4] = triindxs[1];
    m_oBranchMesh.m_oIndices[5] = triindxs[2];

    m_oBranchMesh.m_oIndices[6] = triindxs[3];
    m_oBranchMesh.m_oIndices[7] = triindxs[4];
    m_oBranchMesh.m_oIndices[8] = triindxs[5];

    m_oBranchMesh.m_oIndices[9] = triindxs[3];
    m_oBranchMesh.m_oIndices[10] = triindxs[5];
    m_oBranchMesh.m_oIndices[11] = triindxs[4];


    orBuffer.append(m_oBranchMesh);
}



}//////////////////////////////////////////////////////////////////////////////
