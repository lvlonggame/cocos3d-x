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

#include "Base.h"
#include "C3DRenderTarget.h"
#include "C3DTexture.h"

namespace cocos3d
{
static std::vector<C3DRenderTarget*> __renderTargets;

C3DRenderTarget::C3DRenderTarget(const std::string& id)
    : _id(id), _texture(NULL)
{
}

C3DRenderTarget::~C3DRenderTarget()
{
    SAFE_RELEASE(_texture);

    // Remove ourself from the cache
    std::vector<C3DRenderTarget*>::iterator it = std::find(__renderTargets.begin(), __renderTargets.end(), this);
    if (it != __renderTargets.end())
    {
        __renderTargets.erase(it);
    }
}

C3DRenderTarget* C3DRenderTarget::create(const std::string& id, unsigned int width, unsigned int height, unsigned int fmt)
{
    // Create a new texture with the given width
    C3DTexture* texture = C3DTexture::create(width, height, (C3DTexture::Format)fmt, false);
    if (texture == NULL)
    {
        return NULL;
    }

    C3DRenderTarget* renderTarget = new C3DRenderTarget(id);
    renderTarget->_texture = texture;
	texture->retain();

    __renderTargets.push_back(renderTarget);

    renderTarget->autorelease();
    return renderTarget;
}

C3DRenderTarget* C3DRenderTarget::getRenderTarget(const std::string& id)
{
    // Search the vector for a matching ID.
    std::vector<C3DRenderTarget*>::const_iterator it;
    for (it = __renderTargets.begin(); it < __renderTargets.end(); it++)
    {
        C3DRenderTarget* dst = *it;
        if (id == dst->getID())
        {
            return dst;
        }
    }

    return NULL;
}

const std::string& C3DRenderTarget::getID() const
{
    return _id;
}

C3DTexture* C3DRenderTarget::getTexture() const
{
    return _texture;
}
}