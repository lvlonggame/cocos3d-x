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

#ifndef TRANSFORM_PSA_H_
#define TRANSFORM_PSA_H_

#include "C3DTransform.h"
#include "C3DMesh.h"
#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DTexture.h"
#include "Rectangle.h"

#include "C3DElementNode.h"
#include "cocos2d.h"
#include "C3DParticleSystemCommon.h"
namespace cocos3d
{
class C3DElementNode;
class C3DParticleSystem;

/**
Defines particle system transform action
It is a compulsory component for particle system
It updates particle rotation, age, size, frame, velocity, and so on
*/
class C3DTransformPSA : public C3DBaseParticleAction
{
public:

	/**
     * Constructor & Destructor
     */
	C3DTransformPSA(C3DParticleSystem* system);
	virtual ~C3DTransformPSA();

	/**
     * load & save particle action
     */
	virtual	void load(C3DElementNode* properties);
	virtual void save(C3DElementNode* properties);

	/**
     * particle action, change particle state by elapsed time
     */
	virtual void action(long elapsedTime);

	/**
     * get & set end size
     */
    void setEndSize(float size) { _endSize = size; }
	float getEndSize() const { return _endSize; }

	/**
     * get & set size rate
     */
	void setSizeRate( float rate) { _sizeRate = rate; }
	float getSizeRate() const { return _sizeRate; }

	/**
     * clone method
     */
    virtual C3DBaseParticleAction* clone(C3DParticleSystem* system) const;

private:

	// property
    C3DMatrix _rotation;

	float _endSize;		// Eventual size of the particles.
	float _sizeRate;		// Increment per second towards the size.
};
}

#endif
