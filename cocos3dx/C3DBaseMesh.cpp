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

#include "C3DBaseMesh.h"
#include "C3DVertexFormat.h"

namespace cocos3d
{
C3DBaseMesh::C3DBaseMesh(C3DVertexFormat* vertexFormat,PrimitiveType primitiveType)
	: _vertexFormat(NULL), _primitiveType(primitiveType)
{
	_vertexFormat = new C3DVertexFormat(vertexFormat);
}

C3DBaseMesh::~C3DBaseMesh()
{
	SAFE_DELETE(_vertexFormat);
}

const C3DVertexFormat* C3DBaseMesh::getVertexFormat() const
{
    return _vertexFormat;
}

unsigned int C3DBaseMesh::getVertexSize() const
{
    return _vertexFormat->getVertexSize();
}

PrimitiveType C3DBaseMesh::getPrimitiveType() const
{
    return _primitiveType;
}

void C3DBaseMesh::setPrimitiveType(PrimitiveType type)
{
    _primitiveType = type;
}

unsigned int C3DBaseMesh::getTriangleCount() const
{
	return 0;
}
}