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

#ifndef BASEMESH_H_
#define BASEMESH_H_

#include "cocos2d.h"
#include "EnumDef_GL.h"

namespace cocos3d
{
class C3DVertexFormat;

    class C3DBaseMesh : public cocos2d::Ref
{
public:
	C3DBaseMesh(C3DVertexFormat* vertexFormat,PrimitiveType primitiveType = PrimitiveType_TRIANGLES);
    virtual ~C3DBaseMesh();

	const C3DVertexFormat* getVertexFormat() const;

    unsigned int getVertexSize() const;

	PrimitiveType getPrimitiveType() const;

    void setPrimitiveType(PrimitiveType type);

	virtual unsigned int getTriangleCount() const;

protected:
	const C3DVertexFormat* _vertexFormat;
	PrimitiveType _primitiveType;
};
}

#endif
