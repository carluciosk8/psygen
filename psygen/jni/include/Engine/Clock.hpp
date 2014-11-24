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


namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{

class TimeSource;
class Observer;

class ClockManager
{
public:
    ClockManager(const TimeSource* pSource = NULL);
    ~ClockManager();

    void init();
    void shutdown();

    void   SetTimeSource(const TimeSource * pSource);
    void   step();
    double get_time() const;// { return m_pTimeSource->getTime(); }

    inline double get_current_time() const { return m_current_time; }
    inline double get_frame_time()   const { return m_frame_time; }
    inline int    get_frame_number() const { return m_frame_number; }
    inline float  get_frame_rate()   const { return 1.0f/(float)m_frame_time; }

    void AddObserver(Observer * pObserver);
    void RemoveObserver(Observer * pObserver);

    void SetFiltering(int frameWindow, double frameDefault = 0.030);



private:
    double GetExactLastFrameDuration();
    void AddToFrameHistory(double exactFrameDuration);
    double GetPredictedFrameDuration() const;


    const TimeSource* m_pTimeSource;
    double m_current_time;
    double m_frame_time;
    int    m_frame_number;

    double m_sourceStartValue;
    double m_sourceLastValue;

    int    m_frameFilteringWindow;
    double m_frameDefaultTime;
    std::deque<double> m_frameDurationHistory;

    typedef std::vector<Observer *> ObserverList;
    ObserverList m_observers;
};

}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif
