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

#ifndef ANIMATIONCHANNEL_H_
#define ANIMATIONCHANNEL_H_

namespace cocos3d
{
class C3DAnimationCurve;

/**
* Defines a channel which holds the target Animation.
*/
class C3DAnimationChannel
{
    friend class C3DAnimationClip;
    friend class C3DAnimation;
	friend class C3DBone;

private:
	/**
     * Constructor.
     */
    C3DAnimationChannel(C3DAnimation* animation, C3DBone* bone,C3DAnimationCurve* curve, unsigned long duration);

	/**
     * Desstructor.
     */
    ~C3DAnimationChannel();

	/**
     * Get C3DAnimationCurve.
     */
    C3DAnimationCurve* getCurve() const;

    C3DAnimation* _animation;

	C3DBone* _bone;

    C3DAnimationCurve* _curve;
    unsigned long _duration;
};
}

#endif
