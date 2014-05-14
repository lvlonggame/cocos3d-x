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

#ifndef __Npc_H__
#define __Npc_H__

#include "cocos2d.h"
//#include "cocos3d.h"
#include "C3DActor.h"
#include "C3DVector2.h"

namespace cocos3d
{
	class C3DSprite;
	class C3DVector2;
}

namespace cocos2d
{
class Npc : public C3DActor
{
public:
	Npc(std::string& name,cocos3d::C3DNode* node,cocos3d::C3DLayer* layer);
	virtual ~Npc();

	class AnimListenerObject : public cocos3d::ListenerObject
	{
	public:
		AnimListenerObject(Npc* npc);
		void onEnd();

	protected:
		Npc* _npc;
	};

	enum State
	{
		State_Idle = 0,
		State_Speak,
	};

	virtual C3DActor::Type getType();

	virtual void init();

	virtual void update(long elapsedTime);

	void speak();

private:
	void updateState(long elapsedTime);

private:
	unsigned int _state;

	Npc::AnimListenerObject* _animListener;
};
}
#endif
