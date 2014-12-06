#pragma once

#include "Engine/RenderCommand.hpp"

#include <vector>
#include <GLES2/gl2.h>

namespace psy {

class GlDisable : public RenderCommand
{
public:
    GlDisable(const std::vector<GLenum>& states);
    virtual ~GlDisable();

	// from Subsystem
	virtual void execute();

protected:
	std::vector<GLenum> m_states;
};

} // end namespace psy
