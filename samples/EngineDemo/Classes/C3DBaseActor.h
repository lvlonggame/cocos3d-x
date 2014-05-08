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

#ifndef __C3DBaseActor_H__
#define __C3DBaseActor_H__

#include "cocos2d.h"
#include "cocos3d.h"
#include <string>
#include "C3DBaseActor.h"
namespace cocos3d
{
	class C3DNode;
	class C3DSprite;
	class C3DVector3;
	class C3DLayer;
}

namespace cocos2d
{
class C3DBaseActor : public CCObject
{
public:
	C3DBaseActor(std::string& name,cocos3d::C3DNode* node, cocos3d::C3DLayer* layer);
	virtual ~C3DBaseActor();

	enum Type
	{
		ActorType_None = 0,
		ActorType_MainPlayer,
		ActorType_Enemy,
		ActorType_Npc,
		ActorType_Bullet,
	};

	virtual void init(){};

	virtual void update(long elapsedTime){};

	virtual C3DBaseActor::Type getType(){return ActorType_None;};

	virtual void moveTo(cocos3d::C3DVector3& target);

	cocos3d::C3DNode* getNode();

protected:
	std::string _name;
	cocos3d::C3DNode* _node;
	cocos3d::C3DVector3 _target;
	cocos3d::C3DLayer* _layer;
	float _life;
};
}
#endif
