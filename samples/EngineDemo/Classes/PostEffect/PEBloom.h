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

#ifndef PEBloom_H
#define PEBloom_H
#include "cocos2d.h"
#include "C3DPostEffect.h"

namespace cocos3d
{
/**
* Bloom effect
*/
class PEBloom : public C3DPostEffect
{
    friend class C3DPostEffect;

protected:
    /**
     * Constructor & Destructor
     */
	PEBloom(C3DPostProcess* postProcess, const std::string& name);

	virtual ~PEBloom();

public:

	static C3DPostEffect* create( const std::string& name, const std::string& materialName, C3DPostProcess* postProcess );

    virtual bool init(const std::string& szMaterial);

    /**
     * draw routine
     */
    virtual void draw();

    /**
     * get & set bloom parameter, brightness threshold
     */
    void setBloomThreshold(float threshold);
    float getBloomThreshold() const;

	void setDensityScale(float scale);
	float getDensityScale() const{  return _densityScale; }
protected:

    bool initBloomParam();

    //bloom parameter
    float  _BloomThreshold;    //

    C3DFrameBuffer* _brightFrameBuffer; // frame buffer for select bright pixels
    C3DFrameBuffer* _blurFrameBufferX; // frame buffer for blur
    C3DFrameBuffer* _blurFrameBufferY;

    C3DFrameBuffer* _blurFrameBuffer;

	float _densityScale;
};
}

#endif	//PEBloom_H
