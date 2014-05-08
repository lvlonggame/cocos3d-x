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

#include "C3DVector4.h"

namespace cocos3d
{
inline void C3DVector4::add(const C3DVector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}
inline const C3DVector4 C3DVector4::operator+(const C3DVector4& v) const
{
    return C3DVector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

inline C3DVector4& C3DVector4::operator+=(const C3DVector4& v)
{
    add(v);
    return *this;
}

inline const C3DVector4 C3DVector4::operator-(const C3DVector4& v) const
{
    C3DVector4 result(*this);
    result.subtract(v);
    return result;
}

inline C3DVector4& C3DVector4::operator-=(const C3DVector4& v)
{
    subtract(v);
    return *this;
}

inline const C3DVector4 C3DVector4::operator-() const
{
    C3DVector4 result(*this);
    result.negate();
    return result;
}

inline const C3DVector4 C3DVector4::operator*(float x) const
{
    C3DVector4 result(*this);
    result.scale(x);
    return result;
}

inline C3DVector4& C3DVector4::operator*=(float x)
{
    scale(x);
    return *this;
}

inline bool C3DVector4::operator<(const C3DVector4& v) const
{
    if (x == v.x)
    {
        if (y == v.y)
        {
            if (z < v.z)
            {
                if (w < v.w)
                {
                    return w < v.w;
                }
            }
            return z < v.z;
        }
        return y < v.y;
    }
    return x < v.x;
}

inline bool C3DVector4::operator==(const C3DVector4& v) const
{
    return x==v.x && y==v.y && z==v.z && w==v.w;
}

inline bool C3DVector4::operator!=(const C3DVector4& v) const
{
    return x!=v.x || y!=v.y || z!=v.z || w!=v.w;
}

inline const C3DVector4 operator*(float x, const C3DVector4& v)
{
    C3DVector4 result(v);
    result.scale(x);
    return result;
}

inline const C3DVector4 C3DVector4::operator*(const C3DVector4& v) const
{
	return C3DVector4(x * v.x, y * v.y, z * v.z, w * v.w);
}
}