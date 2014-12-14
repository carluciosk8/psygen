//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//
//_____________________________________________________________________________________________________________________________________________________________

#pragma once

#include "Engine/Singleton.hpp"

#include <list>

namespace psy { // --------------------------------------------------------------------------------------------------------------------------------------------


class Task;


class Application : public Singleton<Application>
{
public:
    Application();
    virtual ~Application();

    virtual void init();
    virtual void shutdown();
    virtual void run();

    inline bool is_running() const { return m_is_running; }
    inline void stop() { m_is_running = false; }
    inline void add_task(Task* task) { m_tasks.push_back(task); }


protected:
    bool m_is_running;
    std::list<Task*> m_tasks;
};


} // end namespace psy ----------------------------------------------------------------------------------------------------------------------------------------

#define application_sgt   Application::get_singleton()
