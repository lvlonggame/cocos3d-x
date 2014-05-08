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

#ifndef BONEPART_H_
#define BONEPART_H_

namespace cocos3d
{
class C3DNode;
class C3DMeshSkin;

/**
 * Defines a structure of skin-mesh's bone.
 */
class BonePart
{
public:

	/**
     * Constructor.
     */
    BonePart(void);

	/**
     * Destructor.
     */
    virtual ~BonePart(void);

	/**
     * The method for creating BonePart.
     */
	static BonePart* create(C3DMeshSkin* meshSkin, unsigned int batchID,unsigned int offsetVertexIndex,unsigned int numVertexIndex);

	/**
     * Sets the index data.
     *
     * @param indexData Point to the indices memory.
     * @param indexCount The index count.
     */
    void setIndexData(void* indexData, unsigned int indexCount);

public:

	C3DMeshSkin *_meshSkin;
	unsigned int _batchID;
	unsigned int _offsetVertexIndex;
	unsigned int _numVertexIndex;
	std::vector<unsigned int> _indices;
};
}

#endif
