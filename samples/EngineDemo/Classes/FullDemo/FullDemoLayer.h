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

#ifndef __FULLDEMOLAYER_H__
#define __FULLDEMOLAYER_H__

#include "CCNode.h"
#include "cocos2d.h"
#include "TestLayer.h"

namespace cocos3d {
   class C3DAnimatedLight;
   class C3DPlane;
}

USING_NS_CC;
namespace cocos2d
{
class C3DActor;
class MainPlayer;
class Npc;
class Enemy;

class  FullDemoLayer :  public TestLayer
{
public:

public:
    FullDemoLayer();
    virtual ~FullDemoLayer();
	bool init();

	virtual void update(float dt);

	virtual void draw3D(void);//render the 3d contents

	static FullDemoLayer* getInstance();

	 CREATE_FUNC(FullDemoLayer);

	void createStaticModel();
	void createParticleEffect();
	void createEffect();

	void createMainPlayer();

	void createLive();
	void createEnemy();
	void createNpc();

	MainPlayer* getMainPlayer()
	{
		return _mainPlayer;
	}

	void createAnimLight();

	void setUpScene();

    // setup initialize camera
    void setUpCamera();
    //setup initialize light
    void setUpLight();

    void setUpShadowMap();

    void setUpProfile();

    void switchProfileShow();

    virtual void touchEvent(cocos3d::TouchEvent evt, float x, float y, unsigned int contactIndex);
	
	C3DActor* pick( float x,float y );

	std::list<C3DActor*> getActors(void) const
	{
		return _actors;
	}

public:

    CCLayer* createUILayer();

private:

	bool _touched;
	int _touchX;
	int _touchY;

	cocos3d::C3DPlane* _plane;
	MainPlayer* _mainPlayer;

	std::list<C3DActor*> _actors;
};
}
#endif
