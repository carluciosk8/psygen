/**************************************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
    email:      carlucio@gmail.com

    This file is part of PSYGEN

    PSYGEN is free software: you can redistribute it and/or modify it under the terms of the GNU
    Lesser General Public License as published by the Free Software Foundation, either version 3
    of the License, or (at your option) any later version.

    PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
    even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with PSYGEN.
    If not, see <http://www.gnu.org/licenses/>

---------------------------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief  A clock manager
    *  \ingroup PSYengine
    *
    *//*******************************************************************************************/
#ifndef __PSYGEN_CLOCK_H__
#define __PSYGEN_CLOCK_H__


#include <cstddef>
#include <vector>
#include <deque>

#include "PSYGEN/PSYGEN.hpp"

namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{

class TimeSource;
class IObserver;

class PSYAPI Clock
{
public:
    Clock(const TimeSource* pSource = NULL);
    ~Clock();

    void init();
    void shutdown();

    void SetTimeSource(const TimeSource * pSource);
    void FrameStep();

    double GetAbsoluteTime() const;// { return m_pTimeSource->getTime(); }
    inline double GetTime() const { return m_currentTime; }
    inline double GetFrameDuration() const { return m_frameTime; }
    inline int GetFrameNumber() const { return m_frameNumber; }
    float GetFrameRate() const { return 1.0f/(float)m_frameTime; }

    void AddObserver(IObserver * pObserver);
    void RemoveObserver(IObserver * pObserver);

    void SetFiltering(int frameWindow, double frameDefault = 0.030);

private:
    double GetExactLastFrameDuration();
    void AddToFrameHistory(double exactFrameDuration);
    double GetPredictedFrameDuration() const;


    const TimeSource * m_pTimeSource;
    double m_currentTime;
    double m_frameTime;
    int m_frameNumber;

    double m_sourceStartValue;
    double m_sourceLastValue;

    int    m_frameFilteringWindow;
    double m_frameDefaultTime;
    std::deque<double> m_frameDurationHistory;

    typedef std::vector<IObserver *> ObserverList;
    ObserverList m_observers;
};

}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif
