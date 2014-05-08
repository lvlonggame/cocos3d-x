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

#ifndef POSTEFFECT_H
#define POSTEFFECT_H
#include "cocos2d.h"
#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"

namespace cocos3d
{
class C3DPostProcess;
class C3DTechnique;
class C3DSampler;
class C3DMaterial;
class C3DFrameBuffer;
class C3DModel;

/**
  Base class of post effect
*/
class C3DPostEffect : public cocos2d::CCObject
{
protected:

	/**
     * Constructor & Destructor
     */

    C3DPostEffect(C3DPostProcess* postProcess, const std::string& szName);
    virtual ~C3DPostEffect();

public:

    /**
     * draw routine
     */
    virtual void draw();

	virtual void setGridSize( unsigned int x, unsigned int y );

	/**
     * set post effect shader parameter
     */
	virtual void setShaderParameter(){};

	virtual void update( float dt ){}

    virtual bool init(const std::string& szMaterial);

	virtual void reload();
	bool reset();

	std::string getName(void) const
	{
		return _name;
	}

public:
	// properties
	C3DPostProcess* _postProcess;
    std::string _name;
    C3DMaterial* _material;
	C3DModel* _model;

	size_t		_x;
	size_t		_y;

	std::string _szMaterial;
};
}

#endif
