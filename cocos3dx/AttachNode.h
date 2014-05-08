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

#ifndef ATTACHNODE_H_
#define ATTACHNODE_H_

#include <vector>
namespace cocos3d
{
class C3DNode;
class C3DSprite;

/**
*Defines a logic attach point.one
*/
class AttachNode
{
public:

    friend class C3DRenderNode;

    AttachNode( C3DNode* pNode, C3DNode* pOwner );

    ~AttachNode();

	C3DNode*		node()				{ return _node; }

	void attach( C3DNode* pAttachment );

    bool detach( C3DNode* pAttachment );

	void update(long elapsedTime);

	void draw();

private:

	C3DNode* _owner;
	C3DNode* _node;
	std::vector<C3DNode*> _attachments;
};
}

#endif
