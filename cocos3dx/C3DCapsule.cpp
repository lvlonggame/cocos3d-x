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
#include "C3DCapsule.h"

namespace cocos3d
{
    C3DCapsule::C3DCapsule(): _radius(0.0f), _height(0.0f), _vAxisX(1.0f, 0.0f, 0.0f),
    _vAxisY(0.0f, 1.0f, 0.0f), _vAxisZ(0.0f, 0.0f, 1.0f), _vCenter(0.0f, 0.0f, 0.0f)
{
}
C3DCapsule::~C3DCapsule()
{
}

/**
* set capsule z, y axis
*/
void C3DCapsule::setDirAndUp(const C3DVector3& dirz, const C3DVector3& upY)
{
    _vAxisZ = dirz;
	_vAxisZ.normalize();
	_vAxisY = upY;
	_vAxisY.normalize();

	C3DVector3::cross(_vAxisY, _vAxisZ, &_vAxisX);
    C3DVector3::cross(_vAxisZ, _vAxisX, &_vAxisY);
}

}