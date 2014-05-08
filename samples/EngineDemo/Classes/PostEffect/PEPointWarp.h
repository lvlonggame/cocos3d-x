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

#ifndef PEPointWarp_H
#define PEPointWarp_H

#include "C3DPostEffect.h"

namespace cocos3d
{
static const unsigned int MAX_CLICKS = 8;

class MaterialParameter;

class PEPointWarp : public C3DPostEffect
{
	friend class C3DPostEffect;
protected:

	PEPointWarp(C3DPostProcess* postProcess, const std::string& name);
	virtual ~PEPointWarp();

public:
	static C3DPostEffect* create( const std::string& name,const std::string& materialName, C3DPostProcess* postProcess );

	virtual bool init(const std::string& szMaterial);

	virtual void setShaderParameter();

	C3DVector4* getClicks(void)
	{
		return _clicks;
	}

	C3DVector4* getEmptyClick(void);
	void addClick( float x, float y );

	void update( float dt );

	void setSpeed( float f )
	{
		_speed = f;
	}
	float getSpeed(void) const
	{
		return _speed;
	}

	void setMaxRadius( float f )
	{
		_maxRadius = f;
	}
	float getMaxRadius(void) const
	{
		return _maxRadius;
	}

private:
	void resetClick( C3DVector4* click );

private:
	float _speed;
	float _maxRadius;
	C3DVector4 _clicks[MAX_CLICKS];
	MaterialParameter* _paramClicks;
};
}	//namespace cocos3d
#endif	//#define PEPointWarp_H