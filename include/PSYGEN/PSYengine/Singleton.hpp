/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2008 by Carlucio Santos Cordeiro
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
    *  \brief Automatic singleton utility class
    *  \ingroup PSYpatterns
    *
    *//***********************************************************************/
#ifndef __PSYGEN_SINGLETON__
#define __PSYGEN_SINGLETON__

#include <cassert>

namespace psy {////////////////////////////////////////////////////////////////


template <typename TYPE>
class Singleton
{
public:
    Singleton()
    {
        assert ( !ms_Singleton );
        unsigned long offset = ( unsigned long ) ( TYPE* ) 1 - ( unsigned long ) ( Singleton<TYPE>* ) ( TYPE* ) 1;
        ms_Singleton = ( TYPE* ) ( ( unsigned long ) this + offset );
    }

    ~Singleton()
    {
        assert ( ms_Singleton );
        ms_Singleton = 0;
    }

    static TYPE& GetSingleton ()
    {
        assert ( ms_Singleton );
        return ( *ms_Singleton );
    }

    static TYPE* GetSingletonPtr ()
    {
        return ( ms_Singleton );
    }


private:
    static TYPE*  ms_Singleton;
};

template <typename TYPE> TYPE*  Singleton<TYPE>::ms_Singleton = 0;



}//////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_SINGLETON__
