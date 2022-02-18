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
    *  \brief
    *  \ingroup PSYengine
    *
    *//*******************************************************************************************/

#include "PSYGEN/PSYengine/$MODELNAME$.hpp"

namespace psy /////////////////////////////////////////////////////////////////////////////////////
{


void $MODELNAME$::amplify(Evaluator* v)
{
    Model::amplify(v);
}



void $MODELNAME$::shrink(Evaluator* v)
{
    Model::shrink(v);
}



void $MODELNAME$::draw(Evaluator* v)
{
    Model::draw(v);
}



void $MODELNAME$::step(Evaluator* v, float dt)
{
    Model::step(v,dt);
}



void $MODELNAME$::enable()
{
    Model::enable();
}



void $MODELNAME$::disable()
{
    Model::disable();
}



$MODELNAME$::$MODELNAME$()
{
}



$MODELNAME$::~$MODELNAME$()
{
}


}//////////////////////////////////////////////////////////////////////////////////////////////////