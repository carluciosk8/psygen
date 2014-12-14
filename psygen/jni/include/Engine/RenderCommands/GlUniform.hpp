#pragma once

#include "Engine/RenderCommand.hpp"

#include <GLES2/gl2.h>

namespace psy {


class GlUniform1f : public RenderCommand
{
public:
    GlUniform1f() : m_location(-1), m_value(0) {}

    // from RenderCommand
    virtual void execute() { glUniform1f(m_location, m_value); }


protected:
    GLint    m_location;
    GLfloat  m_value;
};


class GlUniform2f : public RenderCommand
{
public:
    GlUniform2f() : m_location(-1), m_value(0) {}

    // from RenderCommand
    virtual void execute() { glUniform2f(m_location, m_value.x, m_value.y); }


protected:
    GLint    m_location;
    glm::fvec2  m_value;
};


} // end namespace psy



//
// Versão 1 da classe Uniform usando polimorfismo e templates
//
class UniformV1
{
public:
    virtual ~UniformV1() {}
    virtual void update() = 0;
};

template <typename TYPE>
class UniformTemplate// : public UniformV1 : public UniformV1
{
public:
    inline UniformTemplate() : m_location(-1) {}
    inline TYPE& get_value() { return m_value; }
    inline void  set_value(const TYPE& value) { m_value = value; }
protected:
    int   m_location;
    TYPE  m_value;
};


class UniformFloat : public UniformTemplate<float>, public UniformV1
{
public:
    UniformFloat() : UniformTemplate() { m_value = 0; }
    virtual void update() { glUniform1f(m_location, m_value); }
    //UniformTemplate<float> & operator= (float const & value) { return *this; }
};


class UniformFloat2 : public UniformTemplate<glm::vec2>, public UniformV1
{
public:
    UniformFloat2() : UniformTemplate() { m_value[0] = 0; m_value[1] = 0; }
    virtual void update() { glUniform2f(m_location, m_value[0], m_value[1]); }
};


class UniformFloat3 : public UniformTemplate<glm::vec3>, public UniformV1
{
public:
    UniformFloat3() : UniformTemplate() { m_value[0] = 0; m_value[1] = 0; m_value[2] = 0; }
    virtual void update() { glUniform3f(m_location, m_value[0], m_value[1], m_value[2]); }
};


//                      .
//                      .
//                      .
// demais Uniforms são derivados da classe base
//                      .
//                      .
//                      .


//------------------------------------------------------------------------------


//
// Versão 2 da classe Uniform usando union e switch-case
//
class UniformV2
{
public:
    void update()
    {
        switch (m_type)
        {
        case GL_FLOAT:      glUniform1f(m_location, m_value.vfloat); break;
        case GL_FLOAT_VEC2: glUniform2f(m_location, m_value.vfloat2[0], m_value.vfloat2[1]); break;
        case GL_FLOAT_VEC3: glUniform3f(m_location, m_value.vfloat3[0], m_value.vfloat3[1], m_value.vfloat3[2]); break;
        //                .
        //                .
        //                .
        // demais Uniforms são tratados aqui
        //                .
        //                .
        //                .
        }
    }

    inline void set_value(float value) { m_value.vfloat = value; }
    inline void set_value(const float (&value)[2]) { m_value.vfloat2[0] = value[0]; m_value.vfloat2[1] = value[1];}
    inline void set_value(const float (&value)[3]) { m_value.vfloat3[0] = value[0]; m_value.vfloat3[1] = value[1]; m_value.vfloat3[2] = value[2];}

private:
    union Value
    {
        float vfloat;
        float vfloat2[2];
        float vfloat3[3];
        //                .
        //                .
        //                .
        // demais Uniforms são tratados aqui
        //                .
        //                .
        //                .
    };

    int     m_location;
    GLenum  m_type;
    Value   m_value;
};


//------------------------------------------------------------------------------


//
// Usando Uniforms versão 1: polimorfismo
//
class ObjectV1
{
public:
    void draw()
    {
        for (UniformV1* uniform : m_parameters)
            uniform->update();
        //
        // desenha o objeto
        //
    }

protected:
    std::list<UniformV1*> m_parameters;
};



//
// Usando Uniforms versão 2: switch-case
//
class ObjectV2
{
public:
    void draw()
    {
        for (UniformV2 uniform : m_parameters)
            uniform.update();
        //
        // desenha o objeto
        //
    }

protected:
    std::list<UniformV2>    m_parameters;
};
