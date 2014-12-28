#pragma once

#include "psygen/Task.hpp"
#include "psygen/Singleton.hpp"

namespace psy {

class EventManager : public Task , public Singleton<EventManager>
{
public:
    virtual ~EventManager() {}
};

#define event_manager_sgt     EventManager::get_singleton()

} // end namespace psy
