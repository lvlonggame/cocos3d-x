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

#ifndef __CHANGECLOTHES_TEST_LAYER_H__
#define __CHANGECLOTHES_TEST_LAYER_H__

#include "CCNode.h"
//#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "cocos2d.h"
#include "cocos3d.h"
#include "TestLayer.h"

USING_NS_CC;
namespace cocos2d
{
class C3DActor;
class  ChangeClothesTestLayer :  public TestLayer
{
public:
    ChangeClothesTestLayer();
    virtual ~ChangeClothesTestLayer();

	static ChangeClothesTestLayer* getInstance();
	virtual bool init();

	virtual void update(float dt);

	virtual void draw3D(void);//render the 3d contents

	CREATE_FUNC(ChangeClothesTestLayer);

	void createLive();
	void setUpScene();

    // setup initialize camera
    void setUpCamera();
    //setup initialize light
    void setUpLight();

	/**
    * change to the next material for the special type part of the avatar model.
    *
    * @param type The part type of the avatar model.
    */
    void changePart(std::string partType);

	/**
    * change to the morph for the special type part of the avatar model.
    *
    * @param type The part type of the avatar model.
    */
	void changeMorph(std::string type,float weight);//change morph for the equip

    virtual void touchEvent(cocos3d::TouchEvent evt, float x, float y, unsigned int contactIndex);
	

    void menuCallback(CCObject * pSender);

    CCLayer* createUILayer();

public:
	void menuCallback_changeCap(CCObject* pSender);
	void menuCallback_changeHair(CCObject* pSender);
	void menuCallback_changeGlasses(CCObject* pSender);
	void menuCallback_changeUpBody(CCObject* pSender);
	void menuCallback_changeBottomBody(CCObject* pSender);
	void menuCallback_changeShoot(CCObject* pSender);
	void menuCallback_changeNose(CCObject* pSender);
	void menuCallback_changeEye(CCObject* pSender);

protected:
	bool _touched;
	int _touchX;
	int _touchY;
	C3DActor* _actor;
};
}
#endif 