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
#ifndef __PSYGEN_SHRINKER_H__
#define __PSYGEN_SHRINKER_H__

#include "PSYGEN/PSYengine/Visitor.hpp"
#include "PSYGEN/PSYengine/Modeler.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class Shrinker : public Visitor
{
public:
    virtual void inspect(Node* opNode);
};


class DataAmplificator : public Visitor
{
public:
    virtual void inspect(Node* opNode);
};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_SHRINKER_H__
