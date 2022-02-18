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

#define PSYGEN_DECLARE_PARAMETERS(cClass)  \
	public:  \
				 cClass(const char* name); \
		virtual ~cClass(){}\
		 \
		virtual const char* get_type(){ return m_type.c_str(); }  \
		static const std::string  m_type;  \
		friend class Object_Manager<Object>;  \
	private


#define PSYGEN_BIND_PARAMETERS(cClass, cDerived)   \
    const std::string  cClass::m_type(#cClass);  \
	cClass::cClass(const char* name) : cDerived(name)


namespace psy {////////////////////////////////////////////////////////////////////////////////////


template<typename T>
inline void Object::bind_parameter(const std::string& name, void* pointer, T value)
{
    m_parameter_table[name] = pointer;
    *(static_cast<T*>(pointer)) = value;
}



template<typename T>
inline void Object::bind_parameter2(Parameter::Type type, const std::string& name, void* pointer, T value)
{
    //Parameter param(type, pointer);
    //param.addr = pointer; param.type = type;
    m_parameter_table2[name] = new Parameter(type, pointer);
    *(static_cast<T*>(pointer)) = value;
}



template <typename T>
inline bool Object::set_parameter(const std::string& name, T value)
{
    if (m_parameter_table.find(name) == m_parameter_table.end())
        return false;
    *(static_cast<T*>(m_parameter_table[name])) = value;
    return true;
}



template <typename T>
inline bool Object::set_parameter2(const std::string& name, T value)
{
    if (m_parameter_table2.find(name) == m_parameter_table2.end())
        return false;
    *(static_cast<T*>(m_parameter_table2[name]->addr)) = value;
    return true;
}



template <typename T>
inline T Object::get_parameter(const std::string& name)
{
    if (m_parameter_table.find(name) != m_parameter_table.end())
        return *static_cast<T*>(m_parameter_table[name]);
    else
        return 0;
}



template <typename T>
inline bool Object::have_parameter(const std::string& name)
{
    if (m_parameter_table.find(name) != m_parameter_table.end())
        return true;
    else
        return false;
}



}//////////////////////////////////////////////////////////////////////////////////////////////////
