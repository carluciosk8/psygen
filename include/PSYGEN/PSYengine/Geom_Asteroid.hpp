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
#ifndef __PSYGEN_GEOM_ASTEROID_H__
#define __PSYGEN_GEOM_ASTEROID_H__

#include <vector>
#include <list>
#include <GL/gl.h>
#include <GL/glu.h>

#include "PSYGEN/PSYengine/Geom_Vbo.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class EdjeMap
{
public:
    EdjeMap(int size)
    {
        m_oEdjeMap = std::vector< std::list< std::pair<int,int> > >(size);
    }

    void setMidVertex(int i1, int i2, int im)
    {
        int imin = std::min(i1,i2);
        int imax = std::max(i1,i2);

        std::list< std::pair<int,int> >::iterator  itr = m_oEdjeMap[imin].begin();
        std::list< std::pair<int,int> >::iterator  end = m_oEdjeMap[imin].end();

        for (itr = itr ; itr != end ; ++itr)
            if (itr->first == imax)
                return;

        m_oEdjeMap[imin].push_back(std::make_pair(imax,im));
    }

    int getMidVertex(int i1, int i2)
    {
        int imin = std::min(i1,i2);
        int imax = std::max(i1,i2);

        std::list< std::pair<int,int> >::iterator  itr = m_oEdjeMap[imin].begin();
        std::list< std::pair<int,int> >::iterator  end = m_oEdjeMap[imin].end();

        for (itr = itr ; itr != end ; ++itr)
            if (itr->first == imax)
                return itr->second;

        return -1;
    }

private:
    std::vector< std::list< std::pair<int,int> > > m_oEdjeMap;
};


class Geom_Asteroid : public Geom_Vbo
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


private:
    std::vector<vec3> m_kVertices;   //!< Vertex buffer.
    std::vector<vec3> m_kNormals;    //!< Normal buffer.
    //std::vector<vec3> m_kColors;     //!< Color buffer.
    std::vector<vec3> m_kTexCoords;  //!< Texture coordinate buffer.
    std::vector<unsigned int> m_kIndices;    //!< Index buffer.

    void _subdivide(unsigned int uiNumSub, float fAmp, float fDec);
    unsigned int _midPoint(unsigned int i1, unsigned int i2, float fAmp, vec3 &kBarycenter);

    EdjeMap*  m_opEdjeMap;


PSYGEN_DECLARE_PARAMETERS(Geom_Asteroid):
    int    seed;
    float  radius;
    float  amplitude;
    float  decay;
    int    subdivisions;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_GEOM_ASTEROID_H__
