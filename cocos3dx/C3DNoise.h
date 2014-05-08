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

#ifndef __C3D_NOISE_H__
#define __C3D_NOISE_H__

namespace cocos3d
{
class C3DNoise
{
public:
	C3DNoise(){}
	virtual ~C3DNoise(){}
	// between -1 and 1
	virtual double generateNoise1D(double x) = 0;
	// between -1 and 1
	virtual double generateNoise2D(double x, double y) = 0;
};

class C3DPerlinNoise : public C3DNoise
{
public:
	C3DPerlinNoise(double mimValue = 0.0, double maxValue = 1.0, double frequency = 1.0, int seed = 0);
	virtual ~C3DPerlinNoise(){}
	// between -1 and 1, frequency is 1
	virtual double generateNoise1D(double x);
	// between -1 and 1, frequency is 1
	virtual double generateNoise2D(double x, double y);

protected:
	double interpolate(double x, double y, double s);

	double _frequency;
	int _seed;
	double _factorScale;
	double _factorAdd;
};
}
#endif