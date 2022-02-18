/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007, 2009 by Carlucio Santos Cordeiro
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
    *  \brief PSYGEN main header file
    *
    *//***********************************************************************/
#ifndef __PSYGEN_HPP__
#define __PSYGEN_HPP__


#define PSYGEN_VERSION    500  // Version Mmm : M=Major mm=minor (e.g., 427 is version 0.4.27)


//  PSYGEN Supported platforms definitions.
#if defined(__linux__)
#   define PSYGEN_PLATFORM_LINUX
#elif defined(__APPLE__)
#   define PSYGEN_PLATFORM_OSX
#elif defined(_WIN32) || defined(_WIN64)
#   define PSYGEN_PLATFORM_WINDOWS
#endif


//  Windows specific definitions for importing and exporting DLLs.
#if defined PSYGEN_PLATFORM_WINDOWS
#   define PSYGEN_EXPORT_API    __declspec(dllexport)
#   define PSYGEN_IMPORT_API    __declspec(dllimport)
#else
#   define PSYGEN_EXPORT_API
#   define PSYGEN_IMPORT_API
#endif

#if defined _USRDLL
#   define PSYAPI   PSYGEN_EXPORT_API
#else
#   define PSYAPI   PSYGEN_IMPORT_API
#endif


#define PSY_BYTES_TO_MEGA(bytes)  ((bytes)*(0.000000954f))


#endif //__PSYGEN_HPP__
