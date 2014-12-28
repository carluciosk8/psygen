namespace psy {



template <typename TYPE> TYPE*  Singleton<TYPE>::ms_singleton_ptr = 0;



template <typename TYPE>
inline Singleton<TYPE>::Singleton()
{
    assert ( !ms_singleton_ptr );
    unsigned long offset = ( unsigned long ) ( TYPE* ) 1 - ( unsigned long ) ( Singleton<TYPE>* ) ( TYPE* ) 1;
    ms_singleton_ptr = ( TYPE* ) ( ( unsigned long ) this + offset );
}



template <typename TYPE>
Singleton<TYPE>::~Singleton()
{
    assert ( ms_singleton_ptr );
    ms_singleton_ptr = 0;
}



template <typename TYPE>
TYPE& Singleton<TYPE>::get_singleton ()
{
    assert ( ms_singleton_ptr );
    return ( *ms_singleton_ptr );
}



template <typename TYPE>
TYPE* Singleton<TYPE>::get_singleton_ptr ()
{
    return ( ms_singleton_ptr );
}



}
