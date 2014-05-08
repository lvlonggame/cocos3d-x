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

#ifndef PARTICLEACTION_H_
#define PARTICLEACTION_H_

#include "C3DTransform.h"
#include "C3DMesh.h"
#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DTexture.h"
#include "Rectangle.h"

#include "C3DElementNode.h"
#include "cocos2d.h"

namespace cocos3d
{
//class Node;
class C3DElementNode;
class C3DParticleSystem;

/**
Defines properties for single particle
*/
class C3DParticle
{
public:
	/**
     * Constructor & Destructor
     */
	C3DParticle()
	{
		_visible = true;
		_frame = 0;
	};
	virtual ~C3DParticle(){};

public:
    C3DVector3 _position;
    C3DVector3 _velocity;
    C3DVector3 _acceleration;
    C3DVector4 _color;
    float _rotationPerParticleSpeed;
    C3DVector3 _rotationAxis;
    float _rotationSpeed;
    float _angle;
    long _age;
    float _size;
    bool _visible;
	int _frame;
	int _frameStart;
	long _ageStart;//
};

/**
Base class of particle action
A class affect the particle's movement
*/
class C3DBaseParticleAction
{
public:
	/**
     * Constructor & Destructor
     */
	C3DBaseParticleAction(C3DParticleSystem* system);
	virtual ~C3DBaseParticleAction();

	/**
     * load & particle action property
     */
	virtual	void load(C3DElementNode* psaNode);
	virtual void save(C3DElementNode* psaNode);

	/**
     * particle action, affect particle movement
     */
	virtual void action(long elapsedTime){};

	/**
     * particle action clone method
     */
    virtual C3DBaseParticleAction* clone(C3DParticleSystem* system) const;

protected:

	/**
     * copy particle action
     */
    virtual void copyFrom(const C3DBaseParticleAction* other);

public:
	C3DParticleSystem* _system;
	char* _name;
};
}

#endif
