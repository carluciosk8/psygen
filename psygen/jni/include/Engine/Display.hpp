#pragma once

#include "Engine/Singleton.hpp"
#include "Engine/Subsystem.hpp"

namespace psy {


class Display : public Singleton<Display> , public Subsystem
{
public:
    virtual ~Display() {}

    virtual void begin_frame() = 0;
    virtual void end_frame() = 0;

    inline bool is_initialized() const { return m_initialized; }

protected:
    bool m_initialized;
};


#define sg_display      Display::GetSingleton()
#define sg_display_ptr  Display::GetSingletonPtr()


}
