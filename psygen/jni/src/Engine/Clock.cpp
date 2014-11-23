#include <algorithm>

#include "Engine/Clock.hpp"
#include "Engine/TimeSource.hpp"
#include "Engine/Observer.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


Clock::Clock(const TimeSource * pSource)
:
    m_pTimeSource(NULL),
    m_currentTime(0),
    m_frameTime(0),
    m_frameNumber(0),
    m_sourceStartValue(0),
    m_sourceLastValue(0)
{
    SetTimeSource(pSource);
    SetFiltering(1);
    m_frameTime = GetPredictedFrameDuration();
}



Clock::~Clock()
{
    this->shutdown();
}



void Clock::SetTimeSource(const TimeSource * pSource)
{
    delete m_pTimeSource;
    m_pTimeSource = pSource;
    if (m_pTimeSource != NULL)
    {
        m_sourceStartValue = m_pTimeSource->get_time();
        m_sourceLastValue = m_sourceStartValue;
    }
}


void Clock::init()
{
}


void Clock::shutdown()
{
    if (m_pTimeSource)
        delete m_pTimeSource;
    m_pTimeSource = NULL;
}


double Clock::GetAbsoluteTime() const
{
	return m_pTimeSource->get_time();
}

void Clock::FrameStep()
{
    double exactLastFrameDuration = GetExactLastFrameDuration();
    AddToFrameHistory(exactLastFrameDuration);

    m_frameTime = GetPredictedFrameDuration();
    m_currentTime += m_frameTime;

    m_frameNumber++;

    ObserverList::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); ++it)
        (*it)->notify();
}



double Clock::GetExactLastFrameDuration()
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



void Clock::AddToFrameHistory(double exactFrameDuration)
{
    m_frameDurationHistory.push_back (exactFrameDuration);
    if (m_frameDurationHistory.size () > (unsigned int) m_frameFilteringWindow)
        m_frameDurationHistory.pop_front ();
}



double Clock::GetPredictedFrameDuration() const
{
    double totalFrameTime = 0;

    std::deque<double>::const_iterator it;
    for (it = m_frameDurationHistory.begin(); it != m_frameDurationHistory.end(); ++it)
        totalFrameTime += *it;
    return totalFrameTime/m_frameDurationHistory.size();
}



void Clock::AddObserver(IObserver * pObserver)
{
    if (pObserver != NULL)
        m_observers.push_back(pObserver);
}



void Clock::RemoveObserver(IObserver * pObserver)
{
    m_observers.erase(std::remove(m_observers.begin(),m_observers.end(), pObserver),
                       m_observers.end());

}



void Clock::SetFiltering(int frameWindow, double frameDefault)
{
    //m_frameFilteringWindow = std::max(1, frameWindow);
    m_frameFilteringWindow = frameWindow > 1 ? frameWindow : 1;
    m_frameDefaultTime = frameDefault;
    m_frameDurationHistory.clear ();
    m_frameDurationHistory.push_back(m_frameDefaultTime);
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
