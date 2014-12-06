#pragma once


namespace psy {


class RenderCommand
{
public:
    virtual ~RenderCommand() {}

    virtual void execute() = 0;
};


} // end namespace psy
