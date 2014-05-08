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

#ifndef C3DCIRCLE_H_
#define C3DCIRCLE_H_

#include "C3DMatrix.h"
#include "C3DVector3.h"

namespace cocos3d
{
class C3DRay;
class C3DVector3;

/**
 * Defines a class describe 3-dimensional Circle.
 */
class C3DCircle
{
public:
	C3DCircle(const C3DVector3& center, const C3DVector3& normal, float radius);

	virtual ~C3DCircle(){;}

	virtual bool Intersect(const C3DRay *ray)const;

	float dist(const C3DRay *ray)const;

	void setCenter(const C3DVector3& center){_center = center;}

	C3DVector3 getCenter(){return _center;}

	void setRadius(float radius){_radius = radius;}

	float getRadius() const {return _radius;}

private:
	C3DVector3 _center;
	C3DVector3 _normal;
	float _radius;
};
}

#endif//C3DCIRCLE_H_
