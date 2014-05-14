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

#include "Base.h"
#include "C3DCircle.h"
#include "C3DRay.h"
#include "C3DVector3.h"
#include "C3DPlane.h"

namespace cocos3d
{
C3DCircle::C3DCircle(const C3DVector3& center, const C3DVector3& normal, float radius)
:_center(center)
,_normal(normal)
,_radius(radius)
{
}

bool C3DCircle::Intersect(const C3DRay *ray)const
{
	C3DPlane *plane = new C3DPlane(_normal, _center);
    float t = ray->dist(plane);
    if ( t > FLT_EPSILON)
    {
        C3DVector3 hitpoint = ray->intersects(plane);;
        if ( (hitpoint - _center).length() < _radius )
        {
			SAFE_DELETE(plane);
            return true;
        }
        else
		{
			SAFE_DELETE(plane);
            return false;
		}
    }
	SAFE_DELETE(plane);
    return false;
};

float C3DCircle::dist(const C3DRay *ray)const
{
	C3DPlane *plane = new C3DPlane(_normal, _center);
	float t = ray->dist(plane);
	if ( t > FLT_EPSILON)
	{
		C3DVector3 hitpoint = ray->intersects(plane);;
		if ( (hitpoint - _center).length() < _radius )
		{
			SAFE_DELETE(plane);
			return t;
		}
	}
	SAFE_DELETE(plane);
	return -1;
}
}