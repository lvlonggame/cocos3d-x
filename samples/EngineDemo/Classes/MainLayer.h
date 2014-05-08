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

#ifndef __MAIN_LAYER_H__
#define __MAIN_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

// Main layer for executing demos

namespace cocos3d
{
    class C3DLayer;
}

class MainLayer : public cocos2d::CCLayer
{
	friend class Npc;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	static MainLayer* getMainLayer()
	{
		return _instance;
	}

    // implement the "static node()" method manually
    CREATE_FUNC(MainLayer);

    void menuCallback(CCObject * pSender);
    void menuBackCallback(CCObject * pSender);
    void closeCallback(CCObject * pSender);

	virtual void onTouchesBegan( const std::vector<Touch*>& touches, Event *unused_event );
	virtual void onTouchesMoved( const std::vector<Touch*>& touches, Event *unused_event );
	




public:
    CCPoint m_tBeginPos;
    CCMenu* m_pItemMenu;
    CCMenu* m_pMenuBack;
    cocos3d::C3DLayer* m_pLayer3D;
    CCLayer* m_pUILayer;
	static MainLayer* _instance;
};

#endif
