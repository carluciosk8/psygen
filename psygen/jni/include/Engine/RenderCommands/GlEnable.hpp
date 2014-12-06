#pragma once

#include "Engine/RenderCommand.hpp"

#include <vector>
#include <GLES2/gl2.h>

namespace psy {

class GlEnable : public RenderCommand
{
public:
	GlEnable(const std::vector<GLenum>& states);
    virtual ~GlEnable();

	// from Subsystem
	virtual void execute();

protected:
	std::vector<GLenum> m_states;
};

} // end namespace psy
