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

#ifndef PESpaceWarp_H
#define PESpaceWarp_H
#include "cocos2d.h"
#include "C3DPostProcess.h"

namespace cocos3d
{
/**
Space wrap post effect
*/
class PESpaceWrap : public C3DPostEffect
{
    friend class C3DPostEffect;
protected:
	/**
     * Constructor & Destructor
     */
	PESpaceWrap(C3DPostProcess* postProcess, const std::string& name);

	virtual ~PESpaceWrap();

public:

	static C3DPostEffect* create( const std::string& name, const std::string& materialName, C3DPostProcess* postProcess );

	void update( float dt );

	/**
     * set post effect shader parameter
     */
	virtual void setShaderParameter();

	/**
     * set pixelsize
     */
	void setPixelSize(const C3DVector2& pixelsize)
	{
		_pixelSize = pixelsize;
	}

	/**
     * set space wrap speed
     */
	void setWrapSpeed(float wrapSpeed)
	{
		_wrapSpeed = wrapSpeed;
	}

	/**
     * set space wrap scale
     */
	void setWrapScale(float wrapScale)
	{
		_wrapScale = wrapScale;
	}

protected:
	// properties
	C3DVector2 _pixelSize;
	float _wrapSpeed;
	float _wrapScale;
	C3DSampler* _wrapSampler;
	float _time;
};
}

#endif	//PESpaceWarp_H
