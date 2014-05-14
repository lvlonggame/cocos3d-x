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

#ifndef C3DCONE_H_
#define C3DCONE_H_

#include "C3DMatrix.h"

namespace cocos3d
{
class C3DRay;
class C3DVector3;
class C3DCone
{
public:
	enum align
	{
		xAxis,
		yAxis,
		zAxis
	};
public:
    /**
     * axis aligned cone
     * the alignment is not given as parameter, thus: only cone in y-direction!
     * since I have a translation class which supports rotation
     */
    C3DCone(const C3DVector3& center, align dim, float radius, float height);

    virtual ~C3DCone(){}

    virtual bool Intersect(const C3DRay *ray)const;

private:
	void setVector(C3DVector3& src, unsigned int nIndex, float fVal)const;
	float getVector(const C3DVector3& src, unsigned int nIndex)const;

private:
	C3DVector3 _center;
	float _radius;
	float _height;
	int _dim;
};
}

#endif//C3DCONE_H_
