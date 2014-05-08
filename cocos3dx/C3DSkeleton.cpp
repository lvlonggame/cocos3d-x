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

#include "Base.h"
#include "C3DSkeleton.h"
#include "C3DBone.h"
#include "Vertex.h"
#include "C3DGeoWireRender.h"

namespace cocos3d
{
C3DSkeleton::C3DSkeleton()
{
	_rootBone = NULL;
}

C3DSkeleton::~C3DSkeleton()
{
	//SAFE_RELEASE(_activeC3DCameraNode);

	//
	//removeAllCompoundModels();
	//
	//SAFE_DELETE(_ambientColor);

	//SAFE_DELETE(_batchModel);
}

void C3DSkeleton::getChild(std::map<std::string, C3DBone*>& bones,C3DNode* node)
{
	if(node->getType() == C3DNode::NodeType_Bone)
	{
		bones[node->getId()] = static_cast<C3DBone*>(node);
	}

	for(std::vector<C3DNode*>::const_iterator iter=node->_children.begin(); iter!=node->_children.end(); ++iter)
	{
		getChild(bones,*iter);
	}
}

C3DBone* C3DSkeleton::getBone(const std::string& name) const
{
	std::map<std::string, C3DBone*>::const_iterator iter = _bones.find(name);
	if (iter == _bones.end())
		return NULL;
	return iter->second;
}

void C3DSkeleton::set(C3DBone* joint)
{
	if(joint == NULL)
		return;
	_rootBone = joint;

	getChild(_bones,_rootBone);
}

C3DAnimation* C3DSkeleton::getAnimation(const std::string& name) const
{
	return _rootBone->getAnimation(name);
}

C3DSkeleton* C3DSkeleton::clone()
{
	return NULL;
}

}