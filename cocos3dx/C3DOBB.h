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

#ifndef C3DOBB_H_
#define C3DOBB_H_
#include "C3DVector3.h"
#include "C3DMatrix.h"

#include "C3DAABB.h"

namespace cocos3d
{
/**
 * a class represent oriented bounding box
 */

class C3DOBB
{
public:
    C3DOBB();
    C3DOBB(const C3DOBB& obb);

    // is point in this obb
    bool isPointIn(const C3DVector3& point) const;

    // clear obb
    void clear();

    // build obb from oriented bounding box
    void build(const C3DAABB& aabb);

    // build obb from points
    void build(const C3DVector3* verts, int nVerts);

    // face to the obb's -z direction
    // verts[0] : front left bottom corner
    // verts[1] : front right bottom corner
    // verts[2] : front right top corner
    // verts[3] : front left top corner
    // verts[4] : back left bottom corner
    // verts[5] : back right bottom corner
    // verts[6] : back right top corner
    // verts[7] : back left top corner
    void getVertices(C3DVector3* verts) const;

    // compute extX, extY, extZ
    // if obb axis changed call this function before use ext axis
    void completeExtAxis()
    {
        extX = xAxis * extents.x;
        extY = yAxis * extents.y;
        extZ = zAxis * extents.z;
    }

	/**
     * Transforms the obb by the given transformation matrix.
     */
    void transform(const C3DMatrix& mat);

public:

    C3DVector3 center; // obb center

    C3DVector3 xAxis; // x axis of obb, unit vector
    C3DVector3 yAxis; // y axis of obb, unit vecotr
    C3DVector3 zAxis; // z axis of obb, unit vector

    C3DVector3 extX; // xAxis * extents.x
    C3DVector3 extY; // yAxis * extents.y
    C3DVector3 extZ; // zAxis * extents.z

    C3DVector3 extents; // obb length along each axis
};
}

#endif
