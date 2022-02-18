/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
    email:      carlucio@gmail.com

    This file is part of PSYGEN

    PSYGEN is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with PSYGEN. If not, see <http://www.gnu.org/licenses/>

-------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief
    *  \ingroup PSYengine
    *
    *//***********************************************************************/
#ifndef __PSYGEN_MAIN_WINDOW_HPP__
#define __PSYGEN_MAIN_WINDOW_HPP__

#include <cstdarg>

#include "PSYGEN/PSYGEN.hpp"
//#include "PSYGEN/PSYpatterns/Singleton.hpp"
//#include "PSYGEN/PSYengine/OpenGL_Context.hpp"
#include "PSYGEN/PSYengine/Text_Box.hpp"
#include "PSYGEN/PSYmath/Vector4.hpp"


namespace psy {////////////////////////////////////////////////////////////////

class OpenglContext;

class PSYAPI  Main_Window// : public Singleton<Main_Window>
{
    public:
        Main_Window();
        virtual ~Main_Window();

        void open(const char* cpName, int iWidth, int iHeight, bool bFullScreen);
        void close();

        inline int getWidth() { return m_iWidth; }
        inline int getHeight() { return m_iHeight; }
        inline bool isFullScreen() { return m_bFullScreen; }

        void clear();
        void refresh();

        inline OpenglContext* getMainOpenglContext() { return m_opMainOpenglContext; }

        //static inline TextBox& getTextBox() { return m_oTextBox; }

        static inline void debug_on() { m_bDebug = true; }
        static inline void debug_off() { m_bDebug = false; }
        static void printfxy(int x, int y, const char* fmt, ... )
        {
            va_list  vlist;
            char buff[MAX_STR];

            // Get output string
            va_start(vlist, fmt);
            vsprintf(buff, fmt, vlist);
            m_oTextBox.DrawStr(x,y,buff);
            va_end(vlist);
        }
        static void printf(const char* fmt, ... )
        {
            va_list  vlist;
            char buff[MAX_STR];

            // Get output string
            va_start(vlist, fmt);
            vsprintf(buff, fmt, vlist);
            m_oTextBox.Printf(buff);
            va_end(vlist);
        }

    protected:
        int  m_iWidth;
        int  m_iHeight;
        bool  m_bFullScreen;

        OpenglContext*  m_opMainOpenglContext;

        static bool     m_bDebug;
        static TextBox  m_oTextBox;
};


} //end namespace Psygen

#define g_Main_Window Main_Window::GetSingleton()

#endif //__PSYGEN_MAIN_WINDOW_HPP__
