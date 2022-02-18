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
    *  \brief  Abstract psygen object type (PSYOBJECT)
    *  \ingroup  PSYengine
    *
    *//*******************************************************************************************/
#ifndef __PSYGEN_OBJECT_MANAGER_H__
#define __PSYGEN_OBJECT_MANAGER_H__

#include <string>
#include <unordered_map>


namespace psy {////////////////////////////////////////////////////////////////////////////////////

class Attribute;
class Geometry;
class Node;
class Camera;

template <class ABSTRACT>  class Object_Manager
{
public:
     Object_Manager() : m_gpu_memory(0), m_system_memory(0) { this->clear(); }
    ~Object_Manager() { this->clear(); }

    void clear();

    template<class CONCRETE>  bool register_class();
                              bool unregister_class(const char* szName);


  /*template<class CONCRETE>*/ABSTRACT* create_abstract(const char*  szType_Name, const char*  szObject_Name);
  /*template<class CONCRETE>*/Attribute* create_attr(const char*  szType_Name, const char*  szObject_Name)
  {
    return static_cast<Attribute*>( create_abstract(szType_Name, szObject_Name) );
  }
  /*template<class CONCRETE>*/Geometry* create_geom(const char*  szType_Name, const char*  szObject_Name)
  {
    return static_cast<Geometry*>( create_abstract(szType_Name, szObject_Name) );
  }
  /*template<class CONCRETE>*/Node* create_node(const char*  szType_Name, const char*  szObject_Name)
  {
    return static_cast<Node*>( create_abstract(szType_Name, szObject_Name) );
  }
  /*template<class CONCRETE>*/Camera* create_camera(const char*  szType_Name, const char*  szObject_Name)
  {
    return static_cast<Camera*>( create_abstract(szType_Name, szObject_Name) );
  }
    template<class CONCRETE>  CONCRETE* create_concrete(const char*  szObject_Name);

    inline void destroy(const char*  sObject_Name);
    inline void destroy(ABSTRACT*  opObj);
    inline void destroy(class std::unordered_map<std::string, ABSTRACT*>::iterator&  iter);

    inline void         inc_mem_usage (float units) { m_gpu_memory += units; }
    inline void         dec_mem_usage (float units) { m_gpu_memory -= units; }
    inline float        get_mem_usage ()            { return m_gpu_memory; }
    inline unsigned int get_system_memory ()        { return m_system_memory; }


private:
    template<class CONCRETE> static ABSTRACT* factory(const char* name);
    typedef ABSTRACT*(*factory_method)(const char*);

    std::unordered_map<std::string, factory_method>  m_oGenesis_Table;
    std::unordered_map<std::string, ABSTRACT*>       m_oObject_Table;

    float  m_gpu_memory;
    float  m_system_memory;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#include "PSYGEN/PSYengine/Object_Manager.inl"

#endif //__PSYGEN_OBJECT_MANAGER_H__
