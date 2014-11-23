#pragma once

#include <string>

namespace psy {


class ObjectData
{
public:
    inline ObjectData(std::string name) : m_name(name) {}

protected:
    std::string m_name;
};


} // end namespace psy
