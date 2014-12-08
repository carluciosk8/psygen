#pragma once

#include <cassert>


namespace psy {


template <typename TYPE>
class Singleton
{
public:
    inline Singleton();
    ~Singleton();

    static TYPE& get_singleton ();
    static TYPE* get_singleton_ptr ();

private:
    static TYPE*  ms_singleton_ptr;
};


}

#include "Singleton.inl"
