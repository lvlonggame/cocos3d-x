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

#include "AttachNode.h"
#include "C3DNode.h"
#include "C3DLayer.h"
#include "C3DScene.h"

namespace cocos3d
{
AttachNode::AttachNode( C3DNode* pNode, C3DNode* pOwner )
{
	_node = pNode;
	_owner = pOwner;
}

AttachNode::~AttachNode()
{
	_node = NULL;
	_owner = NULL;
}

void AttachNode::attach( C3DNode* pAttachment )
{
	pAttachment->scale(1.0f/_owner->getScaleX(),1.0f/_owner->getScaleY(),1.0f/_owner->getScaleZ());

	_node->addChild(pAttachment);
	_owner->get3DScene()->removeChild(pAttachment);

	_attachments.push_back(pAttachment);
}

bool AttachNode::detach( C3DNode* pAttachment )
{
	std::vector<C3DNode*>::iterator nit;
	for (nit = _attachments.begin(); nit != _attachments.end(); nit++)
	{
		if ( *nit == pAttachment )
		{
			pAttachment->scale(_owner->getScaleX(),_owner->getScaleY(),_owner->getScaleZ());
			_owner->get3DScene()->addChild(pAttachment);
			_attachments.erase(nit);
			return true;
		}
	}

return false;
}

void AttachNode::update(long elapsedTime)
{
	std::vector<C3DNode*>::iterator nit;
	for (nit = _attachments.begin(); nit != _attachments.end(); nit++)
	{
		(*nit)->update(elapsedTime);
	}
}

void AttachNode::draw()
{
	std::vector<C3DNode*>::iterator nit;
	for (nit = _attachments.begin(); nit != _attachments.end(); nit++)
	{
		(*nit)->draw();
	}
}

}