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
#ifndef __PSYGEN_GEOM_VBO_H__
#define __PSYGEN_GEOM_VBO_H__

#include <GL/gl.h>

#include "PSYGEN/PSYengine/Geometry.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class Geom_Vbo : public Geometry
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

    void create ( float* fpVertices, float* fpNormals, /*float* fpColors,*/
                  float* fpTexCoords, unsigned int* fpIndexes,
                  unsigned int uiNumVerts, unsigned int uiNumIndxs, GLenum ePrimType );
    void destroy();

PSYGEN_DECLARE_PARAMETERS(Geom_Vbo):


protected: /// Atributes:
        GLenum m_ePrimType;

        unsigned int  m_uiNumVerts;

        GLuint m_uiVBOVerts;
        unsigned int  m_uiVertDim;
        float*  m_fpVertexArray;

        GLuint m_uiVBONormals;
        float*  m_fpNormalArray;

//         GLuint m_uiVBOColors;
//         unsigned int  m_uiColorDim;
//         float*  m_fpColorArray;

        GLuint m_uiVBOTxCrds;
        unsigned int  m_uiTxCrdDim;
        float*  m_fpTxCrdArray;

        GLuint m_uiVBOIndxs;
        unsigned int  m_uiNumIndxs;
        unsigned int*  m_uipIndexArray;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_GEOM_VBO_H__
