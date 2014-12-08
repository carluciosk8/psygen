#pragma once

#include "Engine/Singleton.hpp"

#include <list>

#include "Engine/Task.hpp"

namespace psy {

class Application : public Singleton<Application>
{
public:
    inline   Application() : m_is_running(false) {}
    virtual ~Application() {}

    virtual void init()     { for (Task* task : m_tasks) task->start(); }
    virtual void shutdown() { for (Task* task : m_tasks) task->stop(); }

    inline bool is_running() const { return m_is_running; }

    void run()
    {
        m_is_running = true;
        while (m_is_running)
            for (Task* task : m_tasks)
                task->update();
    }


protected:
    bool m_is_running;
    std::list<Task*> m_tasks;
};


#define application_sgt      Application::get_singleton()


} // end namespace psy
