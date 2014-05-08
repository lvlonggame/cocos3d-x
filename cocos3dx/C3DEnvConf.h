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

#ifndef __C3DEnvConf_H__
#define __C3DEnvConf_H__

#include "cocos3d.h"

#include <string>

#include "C3DRenderState.h"

namespace cocos3d
{
/**
*3D environment configuration.
*
*/
class C3DEnvConf
{
public:

	/**
	* fog type
	*/
	enum FogType
	{
		None,
		Linear,
		Exp,
		Exp2,
	};

public:

	C3DEnvConf()
		:_fogColor(1.0f, 1.0f, 1.0f, 1.0f), _clearColor(0.0f, 0.0f, 0.0f, 0.0f), _ambientColor(0.7f, 0.7f, 0.7f)
	{
		_fogType = None;
		_fogStart = 0.0f;
		_fogEnd = 1.0f;
		_fogDensity = 0.01f;
	}

	void set(C3DEnvConf config)
	{
		_clearColor = config._clearColor;
		_fogColor = config._fogColor;
		_fogType = config._fogType;
		_fogStart = config._fogStart;
		_fogEnd = config._fogEnd;
		_fogParam = C3DVector4(config._fogDensity,config._fogStart,config._fogEnd,(float)((int)config._fogType));
	}

	C3DVector4 _clearColor; //clear color

	C3DVector3 _ambientColor;//ambient color

	//fog type
	FogType _fogType;

	// fog parameter
	C3DVector4 _fogColor;
	C3DVector4 _fogParam;
	float _fogDensity;
	float _fogStart;
	float _fogEnd;
};
}
#endif
