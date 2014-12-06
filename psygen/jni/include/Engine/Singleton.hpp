#pragma once

/******************************************************************************
*//**
    *  \brief Automatic singleton utility class by Scott Bilas
    *//***********************************************************************/

#include <cassert>

namespace psy {////////////////////////////////////////////////////////////////

template <typename TYPE>
class Singleton
{
public:
    inline Singleton()
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

    static TYPE& get_singleton ()
    {
        assert ( ms_Singleton );
        return ( *ms_Singleton );
    }

    static TYPE* get_singleton_ptr ()
    {
        return ( ms_Singleton );
    }


private:
    static TYPE*  ms_Singleton;
};

template <typename TYPE> TYPE*  Singleton<TYPE>::ms_Singleton = 0;

}//////////////////////////////////////////////////////////////////////////////
