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
#ifndef __PSYGEN_ATTR__H__
#define __PSYGEN_ATTR__H__

#include "PSYGEN/PSYengine/Attribute.hpp"


namespace psy {////////////////////////////////////////////////////////////////////////////////////


class ________ : public Object
{
public:
    /// Procedural generation and collapse
    ///
    virtual void amplify ();
    virtual void shrink  ();

    /// Generation time and memory usage estimation
    ///
    virtual unsigned int calc_mem_usage  ();
    virtual float        calc_time_usage ();

    /// OpenGL rendering commands here
    virtual void enable  ();
    virtual void disable ();

PSYGEN_DECLARE_PARAMETERS(________):
};


}//////////////////////////////////////////////////////////////////////////////////////////////////


#endif //__PSYGEN_ATTR__H__
