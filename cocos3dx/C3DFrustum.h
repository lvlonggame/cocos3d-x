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

#ifndef C3DFRUSTUM_H_
#define C3DFRUSTUM_H_

#include "C3DAABB.h"
#include "C3DOBB.h"
#include "C3DPlane.h"

namespace cocos3d
{
    class C3DCamera;
    /**
	* Defines a 3-dimensional frustum.
	*/
	/**
	Defines a frustum created from camera
	It is used for camera culling
	*/
    class C3DFrustum
    {
		friend class C3DCamera;
    public:
        /**
		 * Constructor & Destructor.
		 */
        C3DFrustum(): _bInit(true), _bClipZ(true){}
		~C3DFrustum(){}

		/**
		 * init frustum from camera.
		 */
        bool initFrustum(C3DCamera* pCamera);

		/**
		 * is aabb out of frustum.
		 */
        bool isOutFrustum(const C3DAABB& aabb) const;
		/**
		 * is obb out of frustum
		 */
        bool isOutFrustum(const C3DOBB& obb) const;

		/**
		 * get & set z clip. if bclipZ == true use near and far plane
		 */
        void setClipZ(bool bclipZ) { _bClipZ = bclipZ; }
        bool isClipZ() { return _bClipZ; }

    protected:
		/**
		 * create clip plane
		 */
        void createPlane(C3DCamera* pcamera);

        C3DPlane _plane[6];// clip plane, left, right, top, bottom, near, far
        bool _bClipZ;//use near and far clip plane
        bool _bInit;
    };
}

#endif
