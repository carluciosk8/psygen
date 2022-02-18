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
#ifndef __PSYGEN_OBJECT_H__
#define __PSYGEN_OBJECT_H__

#include <string>
#include <unordered_map>

#include "PSYGEN/PSYengine/Object_Manager.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////

class Parameter
{
public:
    enum Type { INT , FLOAT , VEC3 , VEC4 , MAT3, STRING };
    static const char* Name[];
    Type  type;
          void* addr;
    Parameter(Type t, void* p) : type(t), addr(p) {;}
};

class Mutex;

class Object
{
public: /// Interface:

    ///  Object state.
    ///
    enum State { SHRINKED , AMPLIFIED, AMPLIFYING, SHRINKING };
    static const char* State_Names[];

    ///  Operations for get Object info.
    ///
    virtual const char* get_type       () { return m_type.c_str(); }
    inline  const char* get_name       () { return m_name.c_str(); }
    inline  const char* get_state_name () { if (m_eState == SHRINKED) return State_Names[SHRINKED]; else return State_Names[AMPLIFIED]; }
    inline        State get_state      () { return m_eState; }

    ///  Operations for manage parameters by string parameter names.
    ///
    template <typename T> void   bind_parameter (const std::string& name, void* pointer, T value);
    template <typename T> bool   set_parameter  (const std::string& name, T value);
    template <typename T> T      get_parameter  (const std::string& name);
    template <typename T> bool   have_parameter (const std::string& name);

    ///  Operations for manage parameters by string parameter names.
    ///
    template <typename T> void   bind_parameter2 (Parameter::Type type, const std::string& name, void* pointer, T value);
    template <typename T> bool   set_parameter2  (const std::string& name, T value);
    //template <typename T> T      get_parameter  (const std::string& name);
    //template <typename T> bool   have_parameter (const std::string& name);

    inline const char* get_current_parameter_name() { return m_current_parameter2->first.c_str(); }
    inline Parameter::Type get_current_parameter_type() { return m_current_parameter2->second->type; }
    inline const char* get_current_parameter_typename() { return Parameter::Name[m_current_parameter2->second->type]; }
    inline void* get_current_parameter_value() { return m_current_parameter2->second->addr; }

inline bool begin_parameter()
{
    m_current_parameter2 = m_parameter_table2.begin();
    if (m_current_parameter2 != m_parameter_table2.end())
        return true;
    else
        return false;
}



inline bool next_parameter()
{
    ++m_current_parameter2;
    if (m_current_parameter2 != m_parameter_table2.end())
        return true;
    else
        return false;
}

    /// Procedural generation and collapse
    ///
    virtual void amplify (Mutex*)=0;
    virtual void shrink  (Mutex*)=0;
    friend class Amplificator;
    friend class Shrinker;

    /// Generation time and memory usage estimation
    ///
    virtual float estimate_mem_usage  ()=0;
    virtual float        estimate_time_usage ()=0;

    inline float get_gpu_real() { return m_gpu_memory_use; }

    /// Memory management and object database:
    ///
    static Object_Manager<Object>  Manager;
    friend class Object_Manager<Object>;

protected: /// Creation and destruction:
    Object(const char* name) : m_name(name), m_eState(SHRINKED), m_gpu_memory_use(0), m_time_use(0.0f) {}
    virtual ~Object() { }


protected: /// Atributes:
    ///  Object info.
    ///
    static const std::string   m_type;
           const std::string   m_name;
                 State         m_eState;
                 float         m_gpu_memory_use;
                 float         m_sys_memory_use;
                 float         m_time_use;

    ///  Parameter table.
    ///
    std::unordered_map<std::string, void*>  m_parameter_table;
    std::unordered_map<std::string, void*>::iterator  m_current_parameter;

    std::unordered_map<std::string, Parameter*>  m_parameter_table2;
    std::unordered_map<std::string, Parameter*>::iterator  m_current_parameter2;
};

}//////////////////////////////////////////////////////////////////////////////////////////////////

#include "PSYGEN/PSYengine/Object.inl"



#endif //__PSYGEN_OBJECT_H__
