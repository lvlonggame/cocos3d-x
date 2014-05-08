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

#ifndef VERTEX_H_
#define VERTEX_H_

#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"

namespace cocos3d
{
class BBVertex
{
public:
	C3DVector3 position;
	C3DVector4 color;

	BBVertex()
	{
		color.x = 1.0f;
		color.y = 0.0f;
		color.z = 0.0f;
		color.w = 1.0f;
	}
};

//vertex with color and u, v
struct VertexColorCoord1
{
    C3DVector3 position;
    C3DVector4 color;

    float u;
    float v;
    VertexColorCoord1():color(1.0f, 1.0f, 1.0f, 1.0f), u(0.0f), v(0.0f)
    {
    }
};

struct VertexPositionUV
{
	C3DVector3 position;
	C3DVector2 uv;
	VertexPositionUV(void):position(C3DVector3::zero()), uv(C3DVector2::zero())
	{
	}
};

struct VertexPosition2UV
{
	C3DVector2 position;
	C3DVector2 uv;

	VertexPosition2UV():position(C3DVector2::zero()),uv(C3DVector2::zero())
	{
	}
};

}

#endif
