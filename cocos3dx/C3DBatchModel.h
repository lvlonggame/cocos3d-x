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

#ifndef BATCHMODEL_H_
#define BATCHMODEL_H_

#include "C3DRenderChannel.h"
#include "C3DBaseModel.h"

namespace cocos3d
{
class C3DMaterial;
class C3DBatchMesh;
class C3DNode;
class C3DRenderChannel;

/**
 * Defines a C3DBatchModel which contain a C3DBatchMesh and a material.
 */
class C3DBatchModel : public C3DBaseModel
{
    friend class C3DBatchMesh;

public:

	C3DBatchModel(C3DNode* node);

    virtual ~C3DBatchModel();

	static C3DBatchModel* createDebugModel(C3DNode* node);

    C3DBatchMesh* getMesh() const;
	void setMesh(C3DBatchMesh* mesh);

	C3DMaterial* getMaterial();
    void setMaterial(C3DMaterial* material);

	void add(const unsigned char* vertices, unsigned int vertexCount);
	void add(const unsigned char* vertices, unsigned int vertexCount, const unsigned short* indices, unsigned int indexCount);

	unsigned int getVertexCapacity() const;
	void setVertexCapacity(unsigned int capacity);

	unsigned int getIndexCapacity() const;
	void setIndexCapacity(unsigned int capacity);

	void clear();

	virtual	void draw(void);

	C3DRenderChannel* getRenderChannel();

private:
	void bindVertex(void);
	void setMaterialNodeBinding(void);

private:
	C3DNode* _node;
	C3DBatchMesh* _mesh;
    C3DMaterial* _material;
};
}

#endif
