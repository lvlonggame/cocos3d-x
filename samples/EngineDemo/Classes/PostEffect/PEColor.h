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

#ifndef PEColor_H
#define PEColor_H
#include "C3DPostEffect.h"

namespace cocos3d
{

/**
Gray color post effect
*/
class PEColor : public C3DPostEffect
{
    friend class C3DPostEffect;
protected:
	/**
     * Constructor & Destructor
     */
	PEColor(C3DPostProcess* postProcess, const std::string& name): C3DPostEffect(postProcess, name), _colorRate(1.5f, 1.0f, 0.5f)
    {
    }
    virtual ~PEColor();

public:

	static C3DPostEffect* create( const std::string& name, const std::string& materialName, C3DPostProcess* postProcess );

	/**
     * set post effect shader parameter
     */
	virtual void setShaderParameter();

    void setColorRate(const C3DVector3& colorRate)
    {
        _colorRate = colorRate;
    }

    const C3DVector3& getColorRate() const
    {
        return _colorRate;
    }

protected:

    C3DVector3 _colorRate;
};

}

#endif	//PEColor_H
