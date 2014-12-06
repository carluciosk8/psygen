#pragma once

#include "Engine/Singleton.hpp"

namespace psy {


//class Subsystem;
//class Logger;


class Application : public Singleton<Application>
{
public:
    virtual ~Application() {}

    virtual void init() = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;

    inline bool is_running() const { return m_is_running; }


protected:
    bool m_is_running;

    //Logger*    m_logger;

    //Subsystem*   m_display;
};


#define sg_application      Application::get_singleton()
#define sg_application_ptr  Application::get_singleton_ptr()


} // end namespace psy
