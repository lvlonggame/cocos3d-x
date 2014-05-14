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

#ifndef ENUMDEF_GL_H_
#define ENUMDEF_GL_H_
#include "Base.h"

namespace cocos3d
{
/**
* Defines supported index formats.
*/
enum IndexFormat
{
    IndexFormat_INDEX8 = GL_UNSIGNED_BYTE,
    IndexFormat_INDEX16 = GL_UNSIGNED_SHORT,
    IndexFormat_INDEX32 = GL_UNSIGNED_INT
};

/**
* Defines supported primitive types.
*/
enum PrimitiveType
{
    PrimitiveType_TRIANGLES = GL_TRIANGLES,
    PrimitiveType_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    PrimitiveType_LINES = GL_LINES,
    PrimitiveType_LINE_STRIP = GL_LINE_STRIP,
    PrimitiveType_POINTS = GL_POINTS
};

/**
* Defines the set of supported texture filters.
*/
enum Texture_Filter
{
    Texture_Filter_NEAREST = GL_NEAREST,
    Texture_Filter_LINEAR = GL_LINEAR,
    Texture_Filter_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
    Texture_Filter_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
    Texture_Filter_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
    Texture_Filter_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

/**
* Flags used when clearing the active frame buffer targets.
*/
enum ClearFlags
{
    CLEAR_COLOR =   0x00000001,
    CLEAR_DEPTH =   0x00000010,
    CLEAR_STENCIL = 0x00000100,
    CLEAR_COLOR_DEPTH = CLEAR_COLOR | CLEAR_DEPTH,
    CLEAR_COLOR_STENCIL = CLEAR_COLOR | CLEAR_STENCIL,
    CLEAR_DEPTH_STENCIL = CLEAR_DEPTH | CLEAR_STENCIL,
    CLEAR_COLOR_DEPTH_STENCIL = CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL
};

/**
* Defines the set of supported texture wrapping modes.
*/
enum Texture_Wrap
{
    Texture_Wrap_REPEAT = GL_REPEAT,
    Texture_Wrap_CLAMP = GL_CLAMP_TO_EDGE
};
}

#endif
