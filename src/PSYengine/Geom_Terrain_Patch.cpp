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

#include "PSYGEN/PSYmath/Noise.hpp"
#include "PSYGEN/PSYengine/Geom_Terrain_Patch.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Geom_Terrain_Patch, Geom_Vbo)
{
    m_sys_memory_use = sizeof(*this);

    bind_parameter2(Parameter::FLOAT, "posX", &posX, 0.0f);
    bind_parameter2(Parameter::FLOAT, "posZ", &posZ, 0.0f);
    bind_parameter2(Parameter::FLOAT, "sizeX", &sizeX, 0.0f);
    bind_parameter2(Parameter::FLOAT, "sizeZ", &sizeZ, 0.0f);
    bind_parameter2(Parameter::INT,   "subdivisionsX", &subdivisionsX, 0);
    bind_parameter2(Parameter::INT,   "subdivisionsZ", &subdivisionsZ, 0);
    bind_parameter2(Parameter::FLOAT, "H", &H, 0.0f);
    bind_parameter2(Parameter::FLOAT, "lacunarity", &lacunarity, 0.0f);
    bind_parameter2(Parameter::FLOAT, "octaves", &octaves, 0.0f);
    bind_parameter2(Parameter::FLOAT, "offset", &offset, 0.0f);
    bind_parameter2(Parameter::FLOAT, "gain", &gain, 0.0f);
    bind_parameter2(Parameter::FLOAT, "scale_v", &scale_v, 1.0f);
    bind_parameter2(Parameter::FLOAT, "scale_h", &scale_h, 1.0f);
}



void Geom_Terrain_Patch::amplify(Mutex* mutex)
{
    //if (get_state() == SHRINKED)
    //{
//         std::cout << "amplify Geom_Terrain_Patch: name = \"" << get_name() << "\"" << std::endl;
//         std::cout << "   posX = " << posX << std::endl;
//         std::cout << "   posZ = " << posZ << std::endl;
//         std::cout << "   sizeX = " << sizeX << std::endl;
//         std::cout << "   sizeZ = " << sizeZ << std::endl;
//         std::cout << "   subdivisionsX = " << subdivisionsX << std::endl;
//         std::cout << "   subdivisionsZ = " << subdivisionsZ << std::endl;
//         std::cout << "   H = " << H << std::endl;
//         std::cout << "   lacunarity = " << lacunarity << std::endl;
//         std::cout << "   octaves = " << octaves << std::endl;
//         std::cout << "   offset = " << offset << std::endl;
//         std::cout << "   gain = " << gain << std::endl;

        float dx = sizeX / (float)subdivisionsX;
        float dz = sizeZ / (float)subdivisionsZ;

        int uiHeigtmapSizeX = subdivisionsX + 1;
        int uiHeigtmapSizeZ = subdivisionsZ + 1;
        m_kVertices.resize(uiHeigtmapSizeX*uiHeigtmapSizeZ);
        m_kNormals.resize(uiHeigtmapSizeX*uiHeigtmapSizeZ);
//        m_kColors.resize(uiHeigtmapSizeX*uiHeigtmapSizeZ);
        m_kTexCoords.resize(uiHeigtmapSizeX*uiHeigtmapSizeZ);
        float z=0;//-sizeZ*0.5f;
        int numeroverts=0;
        for (int zi=0 ; zi<uiHeigtmapSizeZ ; zi++, z+=dz)
        {
            float x=0;//-sizeX*0.5f;
            for (int xi=0 ; xi<uiHeigtmapSizeX ; xi++, x+=dx)
            {
                m_kVertices[ xi + zi*uiHeigtmapSizeX ] = vec3(x-sizeZ*0.5f, height(x+posX, z+posZ), z-sizeX*0.5f);
                m_kNormals[xi + zi*uiHeigtmapSizeX] = normal(x+posX, z+posZ); m_kNormals[xi + zi*uiHeigtmapSizeX].normalize();
                //m_kColors[xi + zi*uiHeigtmapSizeX] = vec3(1, 1, 1);
                m_kTexCoords[xi + zi*uiHeigtmapSizeX] = vec3(x/sizeX, z/sizeZ, 0);
                numeroverts++;
            }
        }

        m_kIndices.resize(6*(uiHeigtmapSizeX-1)*(uiHeigtmapSizeZ-1));
        int index = 0;
        for (int z=0 ; z<uiHeigtmapSizeZ-1 ; z++)
        {
            for (int x=0 ; x<uiHeigtmapSizeX-1 ; x++)
            {
                m_kIndices[index++] = (x+1 + (z+1)*uiHeigtmapSizeX);
                m_kIndices[index++] = (x+1 + z*uiHeigtmapSizeX);
                m_kIndices[index++] = (x + z*uiHeigtmapSizeX);

                m_kIndices[index++] = (x + z*uiHeigtmapSizeX);
                m_kIndices[index++] = (x + (z+1)*uiHeigtmapSizeX);
                m_kIndices[index++] = (x+1 + (z+1)*uiHeigtmapSizeX);

                //assert( index <= 6*sqr(m_uiResolution) );
            }
        }
        create(m_kVertices[0], m_kNormals[0], /*m_kColors[0],*/ m_kTexCoords[0], &(m_kIndices[0]),
               3*m_kVertices.size(), m_kIndices.size(), GL_TRIANGLES);


        // Memory use
        m_gpu_memory_use = PSY_BYTES_TO_MEGA (m_kVertices.size()*sizeof(vec3) +
                       m_kNormals.size()*sizeof(vec3) +
                       m_kTexCoords.size()*sizeof(vec3) +
                       m_kIndices.size()*sizeof(unsigned int));
        //m_gpu_memory_use *= 1.0f/(1024.0f*1024.0f);


        glFlush();

        // Clean-up
        m_kVertices.clear();
        m_kNormals.clear();
        m_kTexCoords.clear();
        m_kIndices.clear();

        if (mutex) mutex->lock();
        m_eState = Object::AMPLIFIED;
        Object::Manager.inc_mem_usage( m_gpu_memory_use );
        if (mutex) mutex->unlock();
    //}
}



void Geom_Terrain_Patch::shrink(Mutex* mutex)
{
  //  if (m_eState == AMPLIFIED)
//    {
//         std::cout << "shrink Geom_Terrain_Patch: name = \"" << get_name() << "\"" << std::endl;

        destroy();

        if (mutex) mutex->lock();
        m_eState = Object::SHRINKED;
        Object::Manager.dec_mem_usage( m_gpu_memory_use );
        if (mutex) mutex->unlock();
        m_gpu_memory_use = 0;
    //}
}



float Geom_Terrain_Patch::estimate_mem_usage()
{
    return PSY_BYTES_TO_MEGA( (subdivisionsX+1)*(subdivisionsZ+1)*36 + (subdivisionsX)*(subdivisionsZ)*24 );
    //return 0;
}



float Geom_Terrain_Patch::estimate_time_usage()
{
    return 0.0;
}



void Geom_Terrain_Patch::draw()
{
    if (m_eState == Object::AMPLIFIED)
        Geom_Vbo::draw();
}


void Geom_Terrain_Patch::calc_bound_volume()
{
    //local_bound.pos = vec3( sizeX*0.5f , 0 , sizeZ*0.5f );
    float h = (height(0,0) + height(0,sizeZ) + height(sizeX,0) + height(sizeX,sizeZ) + height(sizeX*0.5f,sizeZ*0.5f))/5.0f;
    local_bound.pos = vec3(0 , h , 0);
    local_bound.rad = sqrt(sizeX*sizeX + sizeZ*sizeZ)*0.5f;
}

// float Geom_Terrain_Patch::height(float x, float z)
// {
//     return basis(vec3(x, 0, z), H, lacunarity, octaves, offset, gain)*0.01f;
// }



#define DELTA 0.0001f
vec3 Geom_Terrain_Patch::normal(float x, float z)
{
    float dx = sizeX / (float)subdivisionsX;
    float dz = sizeZ / (float)subdivisionsZ;

    return vec3( height(x-dx, z) - height(x+dx, z) , dx+dz , height(x, z-dz) - height(x, z+dz) );
}



// HeteroTerrain::HeteroTerrain(float H, float lacunarity, float octaves, float offset)
//         :
//         m_fH(H),
//         m_fLacunarity(lacunarity),
//         m_fOctaves(octaves),
//         m_fOffset(offset)
// {}



float HeteroTerrain::operator()(vec3 point, float H, float lacunarity, float octaves, float offset, float gain)
{
    float       value, increment, frequency, remainder;
    int         i;

    //exponent = pow(m_fLacunarity, -m_fH);
    frequency = lacunarity;

    value = offset + Noise::noise(point);
    point *= lacunarity;

    for (i=1; i<octaves; i++)
    {
        //exponent = pow(m_fLacunarity, -i*m_fH);
        frequency *= lacunarity;
        increment = Noise::noise(point) + offset;
        increment *= pow(lacunarity, -i*H);
        increment *= value;
        value += increment;
        point *= lacunarity;
    }

    remainder = octaves - (int)octaves;
    if (remainder)
    {
        increment = (Noise::noise(point) + offset) * pow(lacunarity, -i*H);
        value += remainder * increment * value;
    }

    return value;
}

/*

HybridMultifractal::HybridMultifractal(float H, float lacunarity, float octaves, float offset, float gain)
        :
        m_fH(H),
        m_fLacunarity(lacunarity),
        m_fOctaves(octaves),
        m_fOffset(offset),
        m_fGain(gain)
{}
*/


float HybridMultifractal::operator()(vec3 point, float H, float lacunarity, float octaves, float offset, float gain)
{
    float       value, remainder;
    int         i;

    /* get first octave of function; later octaves are weighted */
    value = Noise::noise(point) + offset;
    float weight = gain * value;
    point.x *= lacunarity;
    point.y *= lacunarity;
    point.z *= lacunarity;

    /* inner loop of spectral construction, where the fractal is built */
    for (i=1; weight>0.001f && i<octaves; i++)
    {
        /* prevent divergence */
        if (weight > 1.0f)  weight = 1.0f;

        /* get next higher frequency */
        float signal = (Noise::noise(point) + offset) * pow(lacunarity, -i*H);
        /* add it in, weighted by previous freq's local value */
        value += weight * signal;
        /* update the (monotonically decreasing) weighting value */
        weight *= gain * signal;

        point.x *= lacunarity;
        point.y *= lacunarity;
        point.z *= lacunarity;
    } /* for */

    /* take care of remainder in "octaves" */
    remainder = octaves - (int)octaves;
    if (remainder)
        /* "i" and spatial freq. are preset in loop above */
        value += remainder * Noise::noise(point) * pow(lacunarity, -i*H);

    return(value);
}



// RidgedMultifractal::RidgedMultifractal()
//         :
//         m_fH(0),
//         m_fLacunarity(0),
//         m_fOctaves(0),
//         m_fOffset(0),
//         m_fThreshold(0)
// {}
//
//
//
// RidgedMultifractal::RidgedMultifractal(float H, float lacunarity, float octaves, float offset, float threshold)
//         :
//         m_fH(H),
//         m_fLacunarity(lacunarity),
//         m_fOctaves(octaves),
//         m_fOffset(offset),
//         m_fThreshold(threshold)
// {}
//


float RidgedMultifractal::operator()(vec3 point, float H, float lacunarity, float octaves, float offset, float gain)
{
    float       result;
    int         i;

    /* get first octave */
    float signal = Noise::noise(point);
    /* get absolute value of signal (this creates the ridges) */
    if (signal < 0.0f) signal = -signal;
    /* invert and translate (note that "offset" should be ~= 1.0) */
    signal = offset - signal;
    /* square the signal, to increase "sharpness" of ridges */
    signal *= signal;
    /* assign initial values */
    result = signal;
    float weight = 1.0f;

    for (i=1; weight>0.001f && i<octaves; i++)
    {
        point.x *= lacunarity;
        point.y *= lacunarity;
        point.z *= lacunarity;

        /* weight successive contributions by previous signal */
        weight = signal * gain;
        if (weight > 1.0f) weight = 1.0f;
        if (weight < 0.0f) weight = 0.0f;
        signal = Noise::noise(point);
        if (signal < 0.0f) signal = -signal;
        signal = offset - signal;
        signal *= signal;
        /* weight the contribution */
        signal *= weight;
        result += signal * pow(lacunarity, -i*H);
    }

    return result;
}


}//////////////////////////////////////////////////////////////////////////////
