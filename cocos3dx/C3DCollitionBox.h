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

#ifndef COLLITIONBOX_H_
#define COLLITIONBOX_H_
#include "C3DVector3.h"
#include "C3DMatrix.h"
#include "C3DNode.h"

namespace cocos3d
{
class C3DRenderNode;
class C3DCollitionBox : public C3DNode
{
public:
	/**
     * Constructor.
     */
    C3DCollitionBox(C3DRenderNode* pRender, unsigned int nID, const std::string& strBoneName = "", const C3DVector3& offset = C3DVector3::zero(), float fRadius = 1.f);

	unsigned int getID(){return m_nID;}

	std::string getBone(){return m_strBone;}

	float getRadius();

	C3DVector3 getLocalPos();

	void updatePosition();

	void getCorners(C3DVector3* dst) const;

	void update();

	// is a relative pos
	void translate(float cx, float cy, float cz);

	void rotate(const C3DQuaternion& rotate);

	void scale(float fScale);
	float getScale();
	float getScaleLocal();

	C3DVector3 getMin(){return _min;}
	C3DVector3 getMax(){return _max;}

	C3DVector3 getUp();
	C3DVector3 getRight();
	C3DVector3 getForward();
protected:
	C3DCollitionBox(){}

protected:
	C3DRenderNode* m_pParentNode;
	unsigned int m_nID;
	std::string m_strBone;
	float m_fRadius;
	float m_fScale;
	C3DQuaternion m_Rotate;
	C3DVector3 m_vLocalPos;
	C3DVector3 _min;
	C3DVector3 _max;

	C3DVector3 m_vUp;
	C3DVector3 m_vRight;
	C3DVector3 m_vForward;
};
}

#endif//COLLITIONBOX_H_
