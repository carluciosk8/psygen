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
#ifndef __TEXT_BOX_H__
#define __TEXT_BOX_H__

#include <GL/gl.h>

#include "PSYGEN/PSYGEN.hpp"

typedef struct {unsigned char r, g, b, a;} COLOR;;

#define SET_COLOR(c, rIn, gIn, bIn, aIn) \
	c.r = rIn; \
	c.g = gIn; \
	c.b = bIn; \
	c.a = aIn


#define MAX_STR 16384

#define TEXT_NONE 0x00
#define TEXT_DRAW_BOX 0x04
#define TEXT_DRAW_SPACES 0x02
#define TEXT_WRAP_SPACES 0x08
#define TEXT_DRAW_BACKGROUND 0x01


namespace psy {////////////////////////////////////////////////////////////////


/* Copyright (C) Dante Treglia II, 2000.
 */
class PSYAPI TextBox
{
public:
	//TextBox(int w, int h, int inL, int inR, int inT, int inB);
	//~TextBox() {free(buffer);}
	void init(int w, int h, int inL, int inR, int inT, int inB);

private:
	// Screen size
	float width;
	float height;

	// Bounding Box
	int boxL;
	int boxR;
	int boxT;
	int boxB;

	// Text Buffers
	char * buffer;
	char * drawBufferPtr;

	// Info
	int pageLineCnt;
	int scrollCnt;
	int currX;
	int currY;
	COLOR color;

public:
	unsigned int mode;

public:
	void Begin();
	void End();
	void DrawStr(int x, int y, const char* string);
	void Draw();
	void Printf(const char* fmt, ...);
	void Clear() {buffer[0] = '\0';};
	void SetColor(COLOR colorIn) {color = colorIn;};
	void SetMode(unsigned int modeIn) {mode = modeIn;};
	void PageUp() {scrollCnt += pageLineCnt;};
	void PageDown() {scrollCnt -= pageLineCnt; if (scrollCnt < 0) scrollCnt = 0;};
	void PageReset() {scrollCnt = 0;};

private:
	void Paginate();
	void DrawStr(int x, int y, int maxFlag, int maxY, const char* string);
	void DrawBoundingBox();
	void FormatStrCat(const char * str);


public:
    //---------------------------------------------------------------------------
    //---------------------------------------------------------------------------
    // The text texture only needs to be initialized once
    static GLuint fontID;
    // Forward definition
    static const unsigned char fontData[];

    static const COLOR  BLACK;
    static const COLOR  GREY;
    static const COLOR  GREEN;
    static const COLOR  WHITE;
	static const COLOR  YELLOW;
    static const COLOR  BLUE;
    static const COLOR  RED;
    static const COLOR  MAGENTA;
    static const COLOR  CYAN;
};

}

#endif //__TEXT_BOX_H__
