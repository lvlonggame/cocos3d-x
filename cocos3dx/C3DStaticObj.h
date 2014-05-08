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

#ifndef SCENEMODEL_H_
#define SCENEMODEL_H_

#include "C3DRenderNode.h"
using namespace std;
namespace cocos3d
{
class C3DMaterial;
class C3DScene;
class C3DNode;
class MeshBatch;

/**
*Defines this static object of the scene,which can change material.
*/
class C3DStaticObj : public C3DRenderNode
{
	friend class C3DScene;
	friend class C3DRenderNodeManager;
public:
	virtual bool load(C3DResourceLoader* loader, bool isLoadAll = false);

	C3DNode::Type getType() const;

	void calculateBoundingBox_();

	virtual void copyFrom(const C3DTransform* other, C3DNode::CloneContext& context);
	virtual C3DNode* clone(CloneContext& context) const;
protected:
	static C3DStaticObj* create(const std::string& id);

private:

    C3DStaticObj(const std::string& id);
    ~C3DStaticObj();
};
}

#endif
