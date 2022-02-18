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
#ifndef __PSYGEN_PRINTER_H__
#define __PSYGEN_PRINTER_H__

#include <iostream>

#include "PSYGEN/PSYengine/Visitor.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class Printer : public Visitor
{
public:
    Printer() : ident(0) {}
    virtual ~Printer() {}
    virtual void inspect(Node* opNode);

    inline void print(Node* npScene)
    {
        ident=0;
        printf("printing:\n");
        this->inspect(npScene);
        std::cout << std::endl;
    }


private:
    int ident;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_RENDERER_H__
