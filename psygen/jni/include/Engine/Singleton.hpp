/******************************************************************************
*//**
    *  \file
    *  \brief Automatic singleton utility class by Scott Bilas
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
