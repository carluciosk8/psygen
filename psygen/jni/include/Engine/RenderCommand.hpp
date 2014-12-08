#pragma once

#include <list>

#include "Engine/Logger.hpp"

namespace psy {


class RenderCommand
{
public:
    virtual ~RenderCommand() {}

    virtual void execute() = 0;
};



class RenderProgram : protected std::list<RenderCommand*>
{
public:
               ~RenderProgram()                  { for (RenderCommand* cmd : *this) delete cmd; }

    inline void add_command(RenderCommand* cmd)  { this->push_back(cmd); }
    inline void execute()                        { for (RenderCommand* cmd : *this) cmd->execute(); }
};


} // end namespace psy
