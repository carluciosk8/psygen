#pragma once

#include "Engine/Singleton.hpp"

namespace psy {

class Subsystem : public Singleton<Subsystem>
{
public:
    virtual ~Subsystem() {}

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;

    inline bool is_initialized() const { return m_initialized; }

protected:
    bool m_initialized;
};

} // end namespace psy
