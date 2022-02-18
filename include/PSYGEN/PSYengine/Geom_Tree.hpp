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
    *  \ingroup  PSYengine
    *
    *//*******************************************************************************************/
#ifndef __PSYGEN_GEOM_TREE_H__
#define __PSYGEN_GEOM_TREE_H__

#include <vector>
#include <list>

#include "PSYGEN/PSYengine/Geom_Vbo.hpp"
#include "PSYGEN/PSYmath/Spline.hpp"
#include "PSYGEN/PSYmath/Random.hpp"

namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{


class GeometryBuffer
{
public:
    GeometryBuffer(unsigned int nv=0, unsigned int ni=0)
    {
        m_oVertices = std::vector<vec3>(nv);
        m_oNormals = std::vector<vec3>(nv);
        m_oTexCoords = std::vector<vec3>(nv);
        m_oIndices = std::vector<unsigned int>(ni);
    }

    ~GeometryBuffer() { clear(); }

    void append(const GeometryBuffer& orBuff)
    {
        unsigned int nv = m_oVertices.size();
        unsigned int ni = m_oIndices.size();

        m_oVertices.insert  (m_oVertices.end()  , orBuff.m_oVertices.begin()  , orBuff.m_oVertices.end());
        m_oNormals.insert   (m_oNormals.end()   , orBuff.m_oNormals.begin()   , orBuff.m_oNormals.end());
        m_oTexCoords.insert (m_oTexCoords.end() , orBuff.m_oTexCoords.begin() , orBuff.m_oTexCoords.end());
        m_oIndices.insert   (m_oIndices.end()   , orBuff.m_oIndices.begin()   , orBuff.m_oIndices.end());

        for (unsigned int i=0 /*ni*/ ; i< /*ni +*/ orBuff.m_oIndices.size() ; i++)
            m_oIndices[i+ni] += nv;
    }

    void clear()
    {
        m_oVertices.clear();
        m_oNormals.clear();
        m_oTexCoords.clear();
        m_oIndices.clear();
    }

    void print()
    {
        std::cout << "verts\t normals\t txcrds" << std::endl;
        std::cout << "-----\t -------\t ------" << std::endl;
        std::cout << std::endl;
        for (unsigned int v=0 ; v<m_oVertices.size() ; v++)
        {
            std::cout << m_oVertices[v] << "\t "
            << m_oNormals[v] << "\t "
            //<< m_oColors[v] << "\t "
            << m_oTexCoords[v] << std::endl;
        }
        std::cout << "triangles" << std::endl;
        std::cout << "---------" << std::endl;
        std::cout << std::endl;
        for (unsigned int i=0 ; i<m_oIndices.size() ; i += 3)
        {
            std::cout << m_oIndices[i] << " , "
            << m_oIndices[i+1] << " , "
            << m_oIndices[i+2] << std::endl;
        }
    }

    //protected:
    std::vector<vec3>  m_oVertices;
    std::vector<vec3>  m_oNormals;
    std::vector<vec3>  m_oTexCoords;
    std::vector<unsigned int>  m_oIndices;
};


class Leaf
{
public:
    Leaf(float fSize);
    ~Leaf();

    void generate(GeometryBuffer& orBuffer);


    //protected:
    vec3   m_vPos;
    vec3   m_vDir;
    float  m_fSize;

    mat3  m_mRot;
    GeometryBuffer  m_oBranchMesh;
};



class Branch
{
public:
    //Branch(){};
    Branch(float fSize, float fRadius, int uiSegments, int  uiSubdivs, float dx, float dz);
    ~Branch();

    void generate(GeometryBuffer& orBuffer/*, GeometryBuffer& orLeafBuffer*/);
//     void addBranch(Branch* opBranch, float fPos, float fZenith, float fAzimuth);
//     void addLeaf(Leaf* opLeaf, float fPos, float fZenith, float fAzimuth);
    void addBranch(Branch& r_branch, GeometryBuffer& r_buffer, float fPos, float fZenith, float fAzimuth);
    void addLeaf(Leaf& r_leaf, GeometryBuffer& r_buffer, float fPos, float fZenith, float fAzimuth);


    //protected:
    vec3  m_vPos;
    vec3  m_vDir;
    float  m_fSize;
    float  m_fSizeDec;
    float  m_fRadius;
    float  m_fRadiusDec;
    int  m_uiSegments;
    int  m_uiSubdivs;

    mat3  m_mRot;
    GeometryBuffer  m_oBranchMesh;

    //std::list<Branch*>  m_oBranches;
    //std::list<Leaf*>  m_oLeaves;

    HermiteSpline  oSpline;
};


class Geom_Tree : public Geom_Vbo
{
public:
    /// Procedural generation and collapse
    ///
    virtual void amplify(Mutex*);
    virtual void shrink(Mutex*);

    /// Generation time and memory usage estimation
    ///
    virtual float estimate_mem_usage();
    virtual float estimate_time_usage();

    /// OpenGL rendering commands here
    virtual void draw();

    /// Bound volume
    ///
    virtual void calc_bound_volume();


private:
    void recursiveGenerate(Branch& r_branch, GeometryBuffer& r_buffer, int iter, int minbr, int maxbr, int segs, int  subdivs);

    GeometryBuffer  m_oBuffer;
    //GeometryBuffer  m_oLeafBuffer;
    MTRand  m_oGenerator;
    //Branch  m_oTrunk;

PSYGEN_DECLARE_PARAMETERS(Geom_Tree):
    int    seed;
    float  size;
    float  radius;
    int    iterations;
    int    min_branches;
    int    max_branches;
    int    segments;
    int    subdivisions;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_GEOM_TREE_H__
