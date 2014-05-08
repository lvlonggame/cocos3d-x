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

#ifndef __MathUtilty__
#define __MathUtilty__

namespace cocos3d
{
class C3DMathUtility
{
public:
    ~C3DMathUtility();

    static C3DMathUtility& getInstance();

    /**
     * approximate value of sin(rad), precision 1 degree
     *
     * @param rad to retreive.
     * @param isUseTable use look up table retrive sin value.
     */
    float sin(float rad, bool isUseTable = false);

    /**
     * approximate value of cos(rad), precision 1 degree
     *
     * @param rad to retreive.
     * @param isUseTable use look up table retrive sin value.
     */
    float cos(float rad, bool isUseTable = false);

    /**
     * approximate value of cos(rad), precision 1 degree
     *
     * @param rad to retreive.
     * @param sinvalue to receive sin value
     * @param cosvalue to receive cos value
     * @param isUseTable use look up table retrive sin value.
     */
    void sincos(float rad, float *sinvalue, float* cosvalue, bool isUseTable = false);

private:
    C3DMathUtility();

    void initMathUtility();

    /**
     * convert rad to degree
     *
     * @param rad to retreive.
     * @return degree [0, 360)
     */
    int rad2degree(float rad);

    float *_costab;
    float *_sintab;
};
}
#endif /* defined(__C3DUtilty__) */
