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
#ifndef __PSYGEN_ $MODELNAME$ _H__
#define __PSYGEN___________H__

#include "PSYGEN/PSYengine/Model.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class PSYAPI $MODELNAME$ : public Model
{
public: /// Operations:
    virtual void amplify   (Evaluator* v);
    virtual void shrink    (Evaluator* v);
    virtual void draw      (Evaluator* v);
    virtual void step      (Evaluator* v, float dt);
    virtual void enable    ();
    virtual void disable   ();

    $MODELNAME$();
    virtual ~$MODELNAME$();

protected:

private:
};

}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN___________H__
