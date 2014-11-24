#pragma once

namespace psy {

class Platform
{
public:
    virtual ~Platform() {}

    virtual void init() = 0;
    virtual void shutdown() = 0;

    inline bool is_running() { return m_is_running; }


protected:
    bool   m_is_running;
};

} // end namespace psy
