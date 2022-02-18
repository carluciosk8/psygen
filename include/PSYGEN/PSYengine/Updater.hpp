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
#ifndef __PSYGEN_UPDATER_H__
#define __PSYGEN_UPDATER_H__

#include "PSYGEN/PSYengine/Visitor.hpp"
//#include "PSYGEN/PSYengine/Singleton.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Updater : public Visitor//, public Singleton<Updater>
{
public:
    virtual void inspect(Node* opNode);

    void update(Node* node);

private:
    bool found_first_bound;
};



class Memory_Predictor : public Visitor
{
public:
    virtual void inspect(Node* opNode);

    void predict(Node* node);
    float get_gpu_memory() { return gpu_memory; }

private:
    unsigned long sys_memory;
    float gpu_memory;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_UPDATER_H__
