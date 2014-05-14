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

#include "C3DMatrix.h"

namespace cocos3d
{
inline const C3DMatrix C3DMatrix::operator+(const C3DMatrix& m) const
{
    C3DMatrix result(*this);
    result.add(m);
    return result;
}

inline C3DMatrix& C3DMatrix::operator+=(const C3DMatrix& m)
{
    add(m);
    return *this;
}

inline const C3DMatrix C3DMatrix::operator-(const C3DMatrix& m) const
{
    C3DMatrix result(*this);
    result.subtract(m);
    return result;
}

inline C3DMatrix& C3DMatrix::operator-=(const C3DMatrix& m)
{
    subtract(m);
    return *this;
}

inline const C3DMatrix C3DMatrix::operator-() const
{
    C3DMatrix m(*this);
    m.negate();
    return m;
}

inline const C3DMatrix C3DMatrix::operator*(const C3DMatrix& m) const
{
    C3DMatrix result(*this);
    result.multiply(m);
    return result;
}

inline C3DMatrix& C3DMatrix::operator*=(const C3DMatrix& m)
{
    multiply(m);
    return *this;
}

inline C3DVector3& operator*=(C3DVector3& v, const C3DMatrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const C3DVector3 operator*(const C3DMatrix& m, const C3DVector3& v)
{
    C3DVector3 x;
    m.transformVector(v, &x);
    return x;
}

inline C3DVector4& operator*=(C3DVector4& v, const C3DMatrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const C3DVector4 operator*(const C3DMatrix& m, const C3DVector4& v)
{
    C3DVector4 x;
    m.transformVector(v, &x);
    return x;
}
}