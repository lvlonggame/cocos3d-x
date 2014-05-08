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

#ifndef C3DBASEMODEL_H_
#define C3DBASEMODEL_H_

#include "cocos2d.h"
#include "Base.h"

namespace cocos3d
{
class C3DMaterial;
class C3DBaseMesh;
class C3DNode;

class C3DBaseModel : public cocos2d::Ref
{
public:

	C3DBaseModel();

    virtual ~C3DBaseModel();

	virtual void draw() = 0;

	//virtual void setNode(C3DNode* node) = 0;

	//virtual void setMesh(C3DBatchMesh* mesh) = 0;

public:
	//C3DNode* _node;
	//C3DBaseMesh* _mesh;
	//C3DMaterial* _material;
};
}

#endif
