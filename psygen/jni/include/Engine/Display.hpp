#pragma once

#include "Engine/Task.hpp"
#include "Engine/Singleton.hpp"
#include "Engine/RenderCommand.hpp"

namespace psy {


class Display : public Task , public Singleton<Display>
{
public:
    virtual ~Display() {}

    inline int  get_width()      const { return m_width; }
    inline int  get_height()     const { return m_height; }
    inline bool is_initialized() const { return m_initialized; }
    inline void set_active_program(RenderProgram* active_program) { m_active_program = active_program; }

protected:
    bool  m_initialized;
    int   m_width;
    int   m_height;
    RenderProgram* m_active_program;
};

#define display_sgt   Display::get_singleton()


} // end namespace psy
