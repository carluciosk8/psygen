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
    *  \ingroup  __________
    *
    *//*******************************************************************************************/
#ifndef __PSYGEN_ATTRIBUTE_H__
#define __PSYGEN_ATTRIBUTE_H__

#include "PSYGEN/PSYengine/Object.hpp"


namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Attribute : public Object
{
public:
    /// Procedural generation and collapse
    ///
    virtual void amplify (Mutex*)=0;
    virtual void shrink  (Mutex*)=0;

    /// Generation time and memory usage estimation
    ///
    virtual float estimate_mem_usage  ()=0;
    virtual float        estimate_time_usage ()=0;

    /// OpenGL rendering commands here
    virtual void enable  ()=0;
    virtual void disable ()=0;

PSYGEN_DECLARE_PARAMETERS(Attribute):
};


}//////////////////////////////////////////////////////////////////////////////////////////////////


#endif //__PSYGEN_ATTRIBUTE_H__
