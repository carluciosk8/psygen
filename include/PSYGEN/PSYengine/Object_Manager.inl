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
#ifndef __PSYGEN_OBJECT_MANAGER_INL__
#define __PSYGEN_OBJECT_MANAGER_INL__

#include <iostream>

namespace psy {////////////////////////////////////////////////////////////////////////////////////


template<class ABSTRACT>  void Object_Manager<ABSTRACT>::clear()
{
    for (class std::unordered_map<std::string, ABSTRACT*>::iterator i = m_oObject_Table.begin() ; i != m_oObject_Table.end() ; ++i)
    {
        destroy(i);
    }
    m_oObject_Table.clear();
    m_oGenesis_Table.clear();
    //std::cout << "system memory: " << m_system_memory << std::endl;
}


template<class ABSTRACT> template<class CONCRETE> bool Object_Manager<ABSTRACT>::register_class()
    {
        if (m_oGenesis_Table.find(CONCRETE::m_type) != m_oGenesis_Table.end())
            return false;

        //std::cout << "register class: name = " << CONCRETE::m_type;

        m_oGenesis_Table[CONCRETE::m_type] = &factory<CONCRETE>;
        return true;
    }


template<class ABSTRACT>
    inline bool Object_Manager<ABSTRACT>::unregister_class(const char* szName)
    {
        return (m_oGenesis_Table.erase(szName) == 1);
    }


template<class ABSTRACT>// template<class CONCRETE>
    ABSTRACT* Object_Manager<ABSTRACT>::create_abstract(const char*  szType_Name, const char*  szObject_Name)
    {
        class std::unordered_map<std::string, factory_method>::iterator  iter = m_oGenesis_Table.find( std::string(szType_Name) );

        if (iter == m_oGenesis_Table.end())
            return NULL;

        class std::unordered_map<std::string, ABSTRACT*>::iterator  it = m_oObject_Table.find( std::string(szObject_Name) );

        if (it == m_oObject_Table.end())
        {
            m_oObject_Table[szObject_Name] = iter->second(szObject_Name);
            m_system_memory += sizeof(*m_oObject_Table[szObject_Name]);
        }

        return (m_oObject_Table[szObject_Name]);
    }



template<class ABSTRACT> template<class CONCRETE>
    inline CONCRETE* Object_Manager<ABSTRACT>::create_concrete(const char*  szObject_Name)
    {
        return static_cast<CONCRETE*>(create_abstract(CONCRETE::m_type.c_str(), szObject_Name));
    }


template<class ABSTRACT>
    inline void Object_Manager<ABSTRACT>::destroy(const char*  sObject_Name)
    {
        class std::unordered_map<std::string, ABSTRACT*>::iterator  iter = m_oObject_Table.find(sObject_Name);
        if (iter != m_oObject_Table.end())
            destroy(iter);
    }


template<class ABSTRACT>
    inline void Object_Manager<ABSTRACT>::destroy(ABSTRACT*  opObj)
    {
        destroy(opObj->get_name());
    }


template<class ABSTRACT>
inline void Object_Manager<ABSTRACT>::destroy(class std::unordered_map<std::string, ABSTRACT*>::iterator&  iter)
{
/*    std::cout << "destroy object: type = " << iter->second->get_type()
    << "\tstate = " << iter->second->get_state_name()
    << "\tname = \"" << iter->second->get_name() << "\"" << std::endl;*/
    if (iter->second->get_state() == ABSTRACT::AMPLIFIED)
    {
        iter->second->shrink(NULL);
        //ABSTRACT::Manager.dec_mem_usage(iter->second->estimate_mem_usage());
    }
    m_system_memory -= sizeof(*iter->second);
    delete(iter->second);
    m_oObject_Table.erase(iter);
}


template<class ABSTRACT> template<class CONCRETE>
ABSTRACT* Object_Manager<ABSTRACT>::factory(const char* name)
{
    //std::cout << "create object: type = " << CONCRETE::m_type << " - name = \"" << name << "\"";
    CONCRETE* opNew_Obj = new CONCRETE(name);
    //std::cout << "  sizeof = " << sizeof(*opNew_Obj) << std::endl;
    //std::cout << "  sizeof = " << opNew_Obj->m_sys_memory_use << std::endl;
    return opNew_Obj;
}


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_OBJECT_MANAGER_INL__
