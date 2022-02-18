/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
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
    *  \brief
    *  \ingroup samples
    *
    *//***********************************************************************/
#include <iostream>
#include <cassert>
#include <list>

#include <SDL/SDL.h>

#include "PSYGEN/PSYengine/Bound.hpp"

using namespace std;
using namespace psy;

int main()
{
    Bound b1(vec3(0,0,0), 0);
    Bound b2(vec3(5,5,0), 0);
    //Bound b3;

    cout << "b1.pos = "<< b1.pos << " b1.rad = " << b1.rad << endl;
    cout << "b2.pos = "<< b2.pos << " b2.rad = " << b2.rad << endl;

    b2.merge(b1);

    cout << "b1.pos = "<< b1.pos << " b1.rad = " << b1.rad << endl;
    cout << "b2.pos = "<< b2.pos << " b2.rad = " << b2.rad << endl;
}
