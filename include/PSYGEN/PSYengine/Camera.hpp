
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
#ifndef __PSYGEN_CAMERA_H__
#define __PSYGEN_CAMERA_H__

#include "PSYGEN/PSYengine/Node.hpp"


namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Camera : public Node
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

    /// Scene graph operations
    ///
    virtual void destroy(){}
    virtual void insert_child (Node*);
    virtual void remove_child (Node*);
    virtual bool update_bound();

    /// Scene graph traverse
    ///
    virtual void accept(Visitor*);

    /// Camera operations
    ///
    void set_perspective(float fFoV, float fAspect, float fNear, float fFar);
    void update_frustum();
    bool bound_is_visible(const Bound& bound);
    bool bound_is_nearby(const Bound& bound);
    //bool test_frustum_visibility(Node*);

    //mat4&  get_view_matrix()   { return m_mGLview; }
    //mat4&  get_proj_matrix()   { return m_mGLprojection; }
    //float* get_gl_view_matrix()   { return m_mGLview; }
    //float* get_gl_proj_matrix()   { return m_mGLprojection; }
    void   get_forward(vec3& fwd) { fwd = vec3(-world.getRotate()[0][2], -world.getRotate()[1][2], -world.getRotate()[2][2]); }

private:
    float  m_fFieldOfView;
    float  m_fAspect;
    float  m_fNear;
    float  m_fFar;

    mat4   gl_proj;
    mat4   gl_view;
    float* proj;
    float* view;
    float  frustum[6][4];
    Bound  proximity;


PSYGEN_DECLARE_PARAMETERS(Camera):

};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_CAMERA_H__
