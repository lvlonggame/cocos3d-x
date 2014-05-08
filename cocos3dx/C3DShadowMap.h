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

#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "C3DNode.h"

namespace cocos3d
{
class C3DFrameBuffer;
class C3DTexture;
class C3DSampler;

/**
*Defines the shadow map.
*One model casts the shadow through rendering the depth of models into texture.
*One model receive the shadow through compare the value between self depth and the depth from the depth textue.
*/
class C3DShadowMap : public C3DNode
{
public:

    static C3DShadowMap* create(const std::string& id, unsigned int texWidth, unsigned int texHeight);

    C3DTexture* getDepthTexture() const;
    C3DSampler* getSampler() const;
    const C3DMatrix& getViewProjectionMatrix();
    const C3DMatrix& getTextureMatrix();
    const C3DVector3& getDimension() const { return _dimension; }
    void setDimension(float width, float height, float depth);
    bool beginDraw();
    void endDraw();

    virtual void transformChanged();

    void updateMatrix();

    virtual C3DNode* clone(C3DNode::CloneContext& context) const;
    virtual C3DNode::Type getType() const { return C3DNode::NodeType_ShadowMap; };

private:
    C3DShadowMap(const std::string& id);
    virtual ~C3DShadowMap();

    C3DFrameBuffer* _framebuffer;
    C3DMatrix _viewProjMatrix;
    C3DMatrix _textureMatrix;
    unsigned int _texWidth;
    unsigned int _texHeight;
    C3DVector3 _dimension;
    C3DSampler* _sampler;
    int _dirty;
};
}

#endif
