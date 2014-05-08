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

#ifndef GEO_H_
#define GEO_H_

namespace cocos3d
{

class C3DMesh;
class BBVertex;
class C3DVector4;

/**
 * Geo is an interface for creating some C3DMesh.
 */
class Geo
{
    friend class C3DModel;
    friend class C3DResourceLoader;

public:
	/**
	* create board mesh.
	*/
	static C3DMesh* createBoard(float x, float y, float width, float height);

	/**
	* create full screen quad mesh.
	*/
	static C3DMesh* createQuadFullscreen( unsigned int sizeX, unsigned int sizeY );

	static void createQuadFullscreen( unsigned int sizeX, unsigned int sizeY, C3DMesh* mesh );

	/**
	* create Sphere mesh.
	*/
	static bool CreateSphere(float radius, std::vector< BBVertex > &ppVertices, std::vector< unsigned short > &ppIndices, const C3DVector4& color, int stacks = 20, int slices = 20);
};
}

#endif
