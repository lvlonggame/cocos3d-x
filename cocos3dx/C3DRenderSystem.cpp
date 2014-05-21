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

#include "C3DRenderSystem.h"
#include "Base.h"
#include "C3DLayer.h"
#include "C3DScene.h"

#include "Rectangle.h"
#include "C3DVector4.h"
#include "C3DRenderBlock.h"
#include "C3DViewport.h"
#include "C3DEffect.h"

#include "C3DRenderChannel.h"
#include "C3DMaterial.h"

#include "C3DEffectManager.h"
#include "C3DMaterialManager.h"
#include "C3DRenderNodeManager.h"
#include "C3DTexture.h"
#include "C3DFrameBuffer.h"
#include "C3DSampler.h"
#include "C3DPostProcess.h"

#include "C3DDeviceAdapter.h"

namespace cocos3d
{
static C3DRenderSystem* __renderSystemInstance = NULL;

C3DRenderSystem::C3DRenderSystem()
{
	_clearColor = NULL;
	_clearDepth = 1.0f;
	_clearStencil = 0;

	_effectManager = C3DEffectManager::getInstance();
	_effectManager->retain();

	_materialManager = C3DMaterialManager::getInstance();
	_materialManager->retain();

	_renderChannelManager = RenderChannelManager::getInstance();
	_renderChannelManager->retain();

	_deviceAdapter = C3DDeviceAdapter::getInstance();
	_deviceAdapter->retain();

	_textureMgr = C3DTextureMgr::getInstance();
	_textureMgr->retain();

	_frameBufMgr = C3DFrameBufferMgr::getInstance();
	_frameBufMgr->retain();

    initialize();
}

void C3DRenderSystem::onLostDevice()
{
}

void C3DRenderSystem::reload()
{
	WARN("\n\n\n---C3DRenderSystem begin reload---");

	_textureMgr->reload();
	_frameBufMgr->reload();

	C3DEffectManager::getInstance()->reload();
	C3DRenderNodeManager::getInstance()->reload();

	if(g_pPostProcess)
		g_pPostProcess->reload();

	C3DMaterialManager::getInstance()->reload();

	WARN("---C3DRenderSystem end reload---\n\n\n");
}

C3DRenderSystem* C3DRenderSystem::create()
{
    if (!__renderSystemInstance)
    {
        __renderSystemInstance = new C3DRenderSystem();
        __renderSystemInstance->autorelease();
    }
    return __renderSystemInstance;
}

C3DRenderSystem* C3DRenderSystem::getInstance()
{
	if (!__renderSystemInstance)
    {
        __renderSystemInstance = new C3DRenderSystem();
        __renderSystemInstance->autorelease();
    }
    return __renderSystemInstance;
}

C3DRenderSystem::~C3DRenderSystem()
{
	finalize();

	__renderSystemInstance = NULL;

	SAFE_RELEASE(_renderChannelManager);

	SAFE_RELEASE(_materialManager); 
	SAFE_RELEASE(_effectManager); 

	SAFE_RELEASE(_frameBufMgr) //
	SAFE_RELEASE(_textureMgr); //

	SAFE_RELEASE(_deviceAdapter);
	SAFE_RELEASE(_deviceAdapter);
}

void C3DRenderSystem::initialize()
{
	_renderChannelManager->init();

    C3DStateBlock::initialize();
    // initialize as window size
	cocos2d::CCSize size = cocos2d::CCDirector::getInstance()->getOpenGLView()->getFrameSize();

    _viewport = new C3DViewport(0, 0, (int)size.width, (int)size.height);

	C3DEffectManager::getInstance()->preload("config/effect.config");
}

void C3DRenderSystem::finalize()
{
	_renderChannelManager->clear();

    C3DStateBlock::finalize();

    SAFE_DELETE(_viewport);
	SAFE_DELETE(_clearColor);
}

void C3DRenderSystem::setViewport(float x, float y, float width, float height)
{
    _viewport->x = (int)x;
	_viewport->y = (int)y;
	_viewport->width = (int)width;
	_viewport->height = (int)height;
    _viewport->apply();
}

void C3DRenderSystem::setViewport(const C3DViewport* viewport)
{
	if (viewport)
		*_viewport = *viewport;
    _viewport->apply();
}

const C3DViewport* C3DRenderSystem::getViewport() const
{
    return _viewport;
}

RenderChannelManager* C3DRenderSystem::getRenderChannelManager() const
{
    return _renderChannelManager;
}

void C3DRenderSystem::update(long elapsedTime)
{
	C3DEffectManager::getInstance()->update(elapsedTime);
}

void C3DRenderSystem::clear(ClearFlags flags, const C3DVector4* clearColor, float clearDepth, int clearStencil)
{
	if(clearColor == NULL)
		return;

	if(_clearColor == NULL)
	{
		_clearColor = new C3DVector4();
	}

    GLbitfield bits = 0;
    if (flags & CLEAR_COLOR)
    {
        if (clearColor->x != _clearColor->x ||
            clearColor->y != _clearColor->y ||
            clearColor->z != _clearColor->z ||
            clearColor->w != _clearColor->w )
        {
            glClearColor(clearColor->x, clearColor->y, clearColor->z, clearColor->w);
            _clearColor->set(*clearColor);
        }
        bits |= GL_COLOR_BUFFER_BIT;
    }

    if (flags & CLEAR_DEPTH)
    {
        if (clearDepth != _clearDepth)
        {
            glClearDepth(clearDepth);
            _clearDepth = clearDepth;
        }
        bits |= GL_DEPTH_BUFFER_BIT;

        // We need to explicitly call the static enableDepthWrite() method on StateBlock
        // to ensure depth writing is enabled before clearing the depth buffer (and to
        // update the global StateBlock render state to reflect this).
        C3DStateBlock::enableDepthWrite();
    }

    if (flags & CLEAR_STENCIL)
    {
        if (clearStencil != _clearStencil)
        {
            glClearStencil(clearStencil);
            _clearStencil = clearStencil;
        }
        bits |= GL_STENCIL_BUFFER_BIT;
    }
    glClear(bits);
}

}