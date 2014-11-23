#pragma once

namespace psy {


class Application
{
public:
    virtual ~Application() {}

    virtual void run() = 0;
};


} // end namespace psy
