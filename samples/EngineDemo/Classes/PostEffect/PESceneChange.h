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

#ifndef PESceneChange_H
#define PESceneChange_H

#include "C3DPostEffect.h"

namespace cocos3d
{
class C3DPass;
class C3DPostEffect;
class C3DPostProcess;
class MaterialParameter;

class PESceneChange : public C3DPostEffect
{
	friend class C3DPostEffect;

protected:

	PESceneChange(C3DPostProcess* postProcess, const std::string& name);

	virtual ~PESceneChange();

public:
	static C3DPostEffect* create( const std::string& name,const std::string& materialName, C3DPostProcess* postProcess );

	virtual bool init(const std::string& szMaterial);
	virtual void draw();

	void update( float dt );

	virtual void setShaderParameter();

	void setAngle( float f )
	{
		_angle = f;
	}
	float getAngel() const
	{
		return _angle;
	}

	void setRadius( float f )
	{
		_radius = f;
	}
	float getRadius()
	{
		return _radius;
	}

	float _angleSpeed;
	float _radiusSpeed;
	float _Time;
	float _maxTime;

private:
	float _angle;
	float _radius;
	MaterialParameter* _paramRadus;
	MaterialParameter* _paramAngle;
	C3DFrameBuffer* _halfFrameBuffer;

	C3DMaterial* _matCopyToScreen;
};
}

#endif	//#define PESceneChange_H
