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

#ifndef __TEST_LAYER_H__
#define __TEST_LAYER_H__

#include "CCNode.h"
#include "cocos2d.h"
#include "cocos3d.h"

USING_NS_CC;


class  TestLayer :  public cocos3d::C3DLayer
{
public:
	virtual CCLayer* createUILayer() = 0;

	virtual void touchEvent(cocos3d::TouchEvent evt, float x, float y, unsigned int contactIndex) = 0;


	virtual void onTouchesBegan( const std::vector<Touch*>& touches, Event *unused_event )
	{
		float scalex = cocos2d::CCDirector::getInstance()->getOpenGLView()->getScaleX();
		float scaley = cocos2d::CCDirector::getInstance()->getOpenGLView()->getScaleY();

		Touch *pTouch;
		std::vector<Touch*>::const_iterator iter;
		for (iter = touches.begin(); iter != touches.end(); ++iter)
		{
			pTouch = (Touch *)(*iter);		
			Point touchPoint = pTouch->getLocationInView();

			touchPoint.x *= scalex;
			touchPoint.y *= scaley;

			touchEvent(cocos3d::TouchEvent_PRESS, touchPoint.x , touchPoint.y , pTouch->getID());
		}   

	}

	virtual void onTouchesMoved( const std::vector<Touch*>& touches, Event *unused_event )
	{
		float scalex = cocos2d::CCDirector::getInstance()->getOpenGLView()->getScaleX();
		float scaley = cocos2d::CCDirector::getInstance()->getOpenGLView()->getScaleY();

		Touch *pTouch;    
		std::vector<Touch*>::const_iterator iter;
		for (iter = touches.begin(); iter != touches.end(); ++iter)
		{
			pTouch = (Touch *)(*iter);	
			Point touchPoint = pTouch->getLocationInView();

			touchPoint.x *= scalex;
			touchPoint.y *= scaley;

			touchEvent(cocos3d::TouchEvent_MOVE, touchPoint.x , touchPoint.y , pTouch->getID());
			
		}

	}

	virtual void onTouchesEnded( const std::vector<Touch*>& touches, Event *unused_event )
	{
		float scalex = cocos2d::CCDirector::getInstance()->getOpenGLView()->getScaleX();
		float scaley = cocos2d::CCDirector::getInstance()->getOpenGLView()->getScaleY();

		Touch *pTouch;    
		std::vector<Touch*>::const_iterator iter;
		for (iter = touches.begin(); iter != touches.end(); ++iter)
		{
			pTouch = (Touch *)(*iter);	
			Point touchPoint = pTouch->getLocationInView();

			touchPoint.x *= scalex;
			touchPoint.y *= scaley;

			touchEvent(cocos3d::TouchEvent_RELEASE, touchPoint.x , touchPoint.y , pTouch->getID());
		}
	}

	virtual void onTouchesCancelled( const std::vector<Touch*>&touches, Event *unused_event )
	{

	}
    
    virtual void draw(cocos2d::Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
    {
        C3DLayer::draw3D();
    }
    


};

#endif