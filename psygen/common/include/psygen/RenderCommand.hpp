#pragma once

#include <list>
#include <memory>

#include "psygen/Logger.hpp"


namespace psy {

/*
class RenderCommand
{
public:
    virtual ~RenderCommand() {}

    virtual void execute() = 0;
};



class RenderProgram : protected std::list<RenderCommand*>
{
public:
               ~RenderProgram()                  { for (RenderCommand* cmd : *this) delete cmd; clear(); }

    inline void add_command(RenderCommand* cmd)  { this->push_back(cmd); }
    inline void execute()                        { for (RenderCommand* cmd : *this) cmd->execute(); }
    inline void erase()                          { for (RenderCommand* cmd : *this) delete cmd; clear(); }
};
*/


class RenderingResource
{
public:
    virtual ~RenderingResource() {}

    virtual void inflate() = 0;
    virtual void shrink() = 0;
};


} // end namespace psy
