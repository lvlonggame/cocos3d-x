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

#ifndef __UI3DLAYER_H__
#define __UI3DLAYER_H__

#include "CCNode.h"

#include "cocos2d.h"
//#include "cocos3d.h"
#include "TestLayer.h"

USING_NS_CC;
namespace cocos2d
{
class  UI3DLayer :  public cocos3d::C3DLayer
{
public:
    UI3DLayer();
    virtual ~UI3DLayer();
	bool init();

	virtual void update(float dt);

	//virtual void draw(void);//render the 3d contents
	 virtual void draw(cocos2d::Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
    {
        C3DLayer::draw3D();
    }
	static UI3DLayer* getInstance();

	CREATE_FUNC(UI3DLayer);

	void setUpScene();

    // setup initialize camera
    void setUpCamera();
    //setup initialize light
    void setUpLight();

   
	void setBase(cocos3d::C3DVector3& base);

public:

private:

	bool _touched;
	int _touchX;
	int _touchY;

	cocos3d::C3DVector3 _base;
};
}
#endif
