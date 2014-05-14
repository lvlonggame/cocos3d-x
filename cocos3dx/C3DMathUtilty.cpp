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

#include "C3DMath.h"

namespace cocos3d
{
C3DMathUtility::C3DMathUtility(): _costab(NULL), _sintab(NULL)
{
}

C3DMathUtility::~C3DMathUtility()
{
    delete[] _costab;
    delete[] _sintab;
}

C3DMathUtility& C3DMathUtility::getInstance()
{
    static C3DMathUtility instance;
    return instance;
}

// approximate value of sin(rad), precision 1 degree
float C3DMathUtility::sin(float rad, bool isUseTable)
{
    if (isUseTable)
    {
        initMathUtility();

        int degree = rad2degree(rad);

        return _sintab[degree];
    }

    return sinf(rad);
}

// approximate value of sin(rad), precision 1 degree
float C3DMathUtility::cos(float rad, bool isUseTable)
{
    if (isUseTable)
    {
        initMathUtility();

        int degree = rad2degree(rad);

        return _costab[degree];
    }
    return cosf(rad);
}

int C3DMathUtility::rad2degree(float rad)
{
    int degree = (int)(MATH_RAD_TO_DEG(rad) + 0.5f);
    if (degree >= 360 || degree <= -360)
    {
        degree = degree % 360;
    }
    if (degree < 0)
        degree += 360;

    return degree;
}

void C3DMathUtility::sincos(float rad, float *sinvalue, float* cosvalue, bool isUseTable)
{
    if (isUseTable)
    {
        initMathUtility();

        int degree = rad2degree(rad);

        if (sinvalue)
            *sinvalue = _sintab[degree];
        if (cosvalue)
            *cosvalue = _costab[degree];
    }
    else
    {
        if (sinvalue)
            *sinvalue = sinf(rad);
        if (cosvalue)
            *cosvalue = cosf(rad);
    }
}

void C3DMathUtility::initMathUtility()
{
    if (_sintab && _costab)
        return;

    delete[] _sintab;
    delete[] _costab;

    const int count = 360;
    _costab = new float[count];
    _sintab = new float[count];

    for (int i = 0; i < count; i++) {
        float rad = MATH_DEG_TO_RAD(i);
        _sintab[i] = sinf(rad);
        _costab[i] = cosf(rad);
    }
}
}