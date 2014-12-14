#pragma once

#include "Engine/Task.hpp"
#include "Engine/Singleton.hpp"
#include "Engine/RenderCommand.hpp"

#define GLASM_NEXT(PTR, TYPE, VALUE)  \
    VALUE = *((TYPE*) PTR);           \
    PTR += sizeof(TYPE)

#define GLASM_PUSH(PTR, TYPE, VALUE)  \
    *((TYPE*) PTR) = VALUE;           \
    PTR += sizeof(TYPE)


enum GLASM
{
    CLR,  // glClear
    CCL,  // glClearColor
    DIS,  // glDisable
    ENB,  // glEnable
    SHD,  // gl
    TEX,  // gl
    UF1,  // glUniform1f
    UF2,  // glUniform2f
    UF3,  // glUniform3f
    UF4,  // glUniform4f
    VBO,  // gl
    VWP,  // gl
    JMP,
    END   // gl
};



namespace psy {

class Display : public Task , public Singleton<Display>
{
public:
    virtual ~Display() {}

    inline int  get_width()      const { return m_width; }
    inline int  get_height()     const { return m_height; }
    inline bool is_initialized() const { return m_initialized; }
    inline void set_active_program(RenderProgram* active_program) { m_active_program = active_program; }
    inline void set_program(unsigned char* program) { m_glasm_prg = program; }

    void (*render)(unsigned char*);
    unsigned char* m_glasm_prg;

protected:
    bool  m_initialized;
    int   m_width;
    int   m_height;
    RenderProgram* m_active_program;
};

#define display_sgt   Display::get_singleton()


} // end namespace psy
