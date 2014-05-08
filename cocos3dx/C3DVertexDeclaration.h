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

#ifndef VERTEXATTRIBUTEBINDING_H_
#define VERTEXATTRIBUTEBINDING_H_

#include "Base.h"

#include "cocos2d.h"

namespace cocos3d
{
class C3DMesh;
class C3DEffect;
class C3DVertexFormat;

/**
 * Defines a vertexdeclaration.
 * This class provide a binding between the vertex layout of a Mesh and the vertex
 * input attributes of a vertex shader.Two Ways:
 * 1.software binding:vertex layout definition,which set when per frame.
 * 2.hardware binding:VAO per VBO.which set only once when init.
 *
 */
class C3DVertexDeclaration : public cocos2d::CCObject
{
public:

    static C3DVertexDeclaration* create(C3DMesh* mesh, C3DEffect* effect);

    static C3DVertexDeclaration* create(const C3DVertexFormat* vertexFormat, void* vertexPointer, C3DEffect* effect);
	bool   init(C3DMesh* mesh, const C3DVertexFormat* vertexFormat, void* vertexPointer, C3DEffect* effect);

    void bind();

    void unbind();

	void reload();

    static int getCurVertAttEnables();

    static void setCurVertAttEnables(int enableMask, bool force = false);

private:

    class C3DVertexAttribute
    {
    public:
        bool enabled;
        int size;
        GLenum type;
        bool normalized;
        unsigned int stride;
        void* pointer;
    };

    C3DVertexDeclaration();

    ~C3DVertexDeclaration();

    void setVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalize, GLsizei stride, void* pointer);

    GLuint _handle;
    C3DVertexDeclaration::C3DVertexAttribute* _attributes;
    C3DMesh* _mesh;
    C3DEffect* _effect;

    int _vaEnableMask;
};
}

#endif
