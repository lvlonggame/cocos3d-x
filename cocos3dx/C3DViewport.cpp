/****************************************************************************
Copyright (c) Chukong Technologies Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "C3DViewport.h"

namespace cocos3d
{
    //---------------------------------------------------------------------
    C3DViewport::C3DViewport(int left, int top, int width1, int height1)
        : x(left)
        , y(top)
        , width(width1)
        , height(height1)
    {
    }

    C3DViewport::C3DViewport(const C3DViewport& viewport)
        : x(viewport.x)
        , y(viewport.y)
        , width(viewport.width)
        , height(viewport.height)
    {
    }

    //---------------------------------------------------------------------
    C3DViewport::~C3DViewport()
    {
    }

    C3DViewport& C3DViewport::operator==(const C3DViewport& viewport)
    {
        this->x = viewport.x;
        this->y = viewport.y;
        this->width = viewport.width;
        this->height = viewport.height;

        return *this;
    }

    void C3DViewport::apply()
    {
        glViewport((GLuint)x, (GLuint)y, (GLuint)width, (GLuint)height);
    }
}