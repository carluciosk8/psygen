#include <algorithm>

#include "Engine/Clock.hpp"
#include "Engine/TimeSource.hpp"
#include "Engine/Observer.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


ClockManager::ClockManager(const TimeSource * pSource)
:
    m_pTimeSource(NULL),
    m_current_time(0),
    m_frame_time(0),
    m_frame_number(0),
    m_sourceStartValue(0),
    m_sourceLastValue(0)
{
    SetTimeSource(pSource);
    SetFiltering(1);
    m_frame_time = GetPredictedFrameDuration();
}



ClockManager::~ClockManager()
{
    this->shutdown();
}



void ClockManager::SetTimeSource(const TimeSource * pSource)
{
    delete m_pTimeSource;
    m_pTimeSource = pSource;
    if (m_pTimeSource != NULL)
    {
        m_sourceStartValue = m_pTimeSource->get_time();
        m_sourceLastValue = m_sourceStartValue;
    }
}


void ClockManager::init()
{
}


void ClockManager::shutdown()
{
    if (m_pTimeSource)
        delete m_pTimeSource;
    m_pTimeSource = NULL;
}


double ClockManager::get_time() const
{
	return m_pTimeSource->get_time();
}

void ClockManager::step()
{
    double exactLastFrameDuration = GetExactLastFrameDuration();
    AddToFrameHistory(exactLastFrameDuration);

    m_frame_time = GetPredictedFrameDuration();
    m_current_time += m_frame_time;

    m_frame_number++;

    //ObserverList::iterator it;
    //for (it = m_observers.begin(); it != m_observers.end(); ++it)
    //    (*it)->notify();
    for (Observer* observer : m_observers)
    {
        observer->notify();
    }
}



double ClockManager::GetExactLastFrameDuration()
{
    double sourceTime;
    if (m_pTimeSource == NULL)
        sourceTime = 0;
    else
        sourceTime = m_pTimeSource->get_time();

    double frameDuration = sourceTime - m_sourceLastValue;
    if (frameDuration > 0.200)
        frameDuration = m_frameDurationHistory.back();
    m_sourceLastValue = sourceTime;
    return frameDuration;
}



void ClockManager::AddToFrameHistory(double exactFrameDuration)
{
    m_frameDurationHistory.push_back (exactFrameDuration);
    if (m_frameDurationHistory.size () > (unsigned int) m_frameFilteringWindow)
        m_frameDurationHistory.pop_front ();
}



double ClockManager::GetPredictedFrameDuration() const
{
    double total_frame_time = 0;
    for (int frame_time : m_frameDurationHistory) total_frame_time += frame_time;
    return total_frame_time/m_frameDurationHistory.size();
}



void ClockManager::AddObserver(Observer * observer)
{
    if (observer)
        m_observers.push_back(observer);
}



void ClockManager::RemoveObserver(Observer * observer)
{
    m_observers.erase(std::remove(m_observers.begin(),m_observers.end(), observer), m_observers.end());
}



void ClockManager::SetFiltering(int frameWindow, double frameDefault)
{
    //m_frameFilteringWindow = std::max(1, frameWindow);
    m_frameFilteringWindow = frameWindow > 1 ? frameWindow : 1;
    m_frameDefaultTime = frameDefault;
    m_frameDurationHistory.clear ();
    m_frameDurationHistory.push_back(m_frameDefaultTime);
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
