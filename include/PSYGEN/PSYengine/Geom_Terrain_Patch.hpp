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
#ifndef __PSYGEN_GEOM_TERRAIN_PATCH_H__
#define __PSYGEN_GEOM_TERRAIN_PATCH_H__

#include <vector>

#include "PSYGEN/PSYengine/Geom_Vbo.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Basis
{
public:
    virtual float operator () (vec3 p, float H, float lacunarity, float octaves, float offset, float gain)=0;
};


class HeteroTerrain : public Basis
{
public:
    //HeteroTerrain(float H, float lacunarity, float octaves, float offset);
    virtual float operator () (vec3 p, float H, float lacunarity, float octaves, float offset, float gain);


//private:
/*    float  m_fH;
    float  m_fLacunarity;
    float  m_fOctaves;
    float  m_fOffset;*/
};



class HybridMultifractal : public Basis
{
public:
    //HybridMultifractal();
    //HybridMultifractal(float H, float lacunarity, float octaves, float offset, float gain);
    virtual float operator () (vec3 p, float H, float lacunarity, float octaves, float offset, float gain);


//private:
/*    float  m_fH;
    float  m_fLacunarity;
    float  m_fOctaves;
    float  m_fOffset;
    float  m_fGain;*/
};



class RidgedMultifractal : public Basis
{
public:
    //RidgedMultifractal();
    //RidgedMultifractal(float H, float lacunarity, float octaves, float offset, float threshold);
    virtual float operator () (vec3 p, float H, float lacunarity, float octaves, float offset, float gain);


//private:
/*    float  m_fH;
    float  m_fLacunarity;
    float  m_fOctaves;
    float  m_fOffset;
    float  m_fThreshold;*/
};



class Geom_Terrain_Patch : public Geom_Vbo
{
public:
    /// Procedural generation and collapse
    ///
    virtual void amplify (Mutex*);
    virtual void shrink  (Mutex*);

    /// Generation time and memory usage estimation
    ///
    virtual float estimate_mem_usage  ();
    virtual float        estimate_time_usage ();

    /// OpenGL rendering commands here
    virtual void          draw();

    /// Bound volume
    ///
    virtual void calc_bound_volume();

    inline float height(float x, float z) { return scale_v * basis(vec3(x*scale_h, 0, z*scale_h), H, lacunarity, octaves, offset, gain); }
    vec3 normal(float x, float z);

    std::vector<vec3>  m_kVertices;
    std::vector<vec3>  m_kNormals;
    //std::vector<vec3>  m_kColors;
    std::vector<vec3>  m_kTexCoords;
    std::vector<unsigned int>  m_kIndices;


PSYGEN_DECLARE_PARAMETERS(Geom_Terrain_Patch):
    float  posX;
    float  posZ;
    float  sizeX;
    float  sizeZ;
    int    subdivisionsX;
    int    subdivisionsZ;
    float  H;
    float  lacunarity;
    float  octaves;
    float  offset;
    float  gain;
    float  scale_v;
    float  scale_h;

    //Basis*  basis;
    RidgedMultifractal basis;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_GEOM_TERRAIN_PATCH_H__
