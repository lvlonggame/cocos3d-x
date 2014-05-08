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

#include "C3DBaseActor.h"
#include "C3DNode.h"
#include "C3DSprite.h"
#include "C3DModel.h"
#include "C3DModelNode.h"
#include "C3DMaterial.h"
namespace cocos2d
{
C3DBaseActor::C3DBaseActor(std::string& name,cocos3d::C3DNode* node,cocos3d::C3DLayer* layer)
{
	_node = node;
	_name = name;
	_layer = layer;
	_life = 30.f;
}

C3DBaseActor::~C3DBaseActor()
{
	_layer = NULL;
}

void C3DBaseActor::moveTo(cocos3d::C3DVector3& target)
{
	_target = target;
}

cocos3d::C3DNode* C3DBaseActor::getNode()
{
	return _node;
}
}