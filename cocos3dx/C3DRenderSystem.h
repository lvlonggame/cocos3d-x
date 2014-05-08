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

#ifndef RenderSystem_H_
#define RenderSystem_H_
#include "EnumDef_GL.h"
#include "cocos2d.h"


namespace cocos3d
{
class Rectangle;
class C3DVector4;
class C3DViewport;
class C3DAnimationController;
class RenderChannelManager;
class C3DEffectManager;
class C3DMaterialManager;
class C3DScreenProcessManager;
class C3DDeviceAdapter;

class C3DSamplerMgr;
class C3DTextureMgr;
class C3DFrameBufferMgr;

/**
Defines the view port and clear flag
*/
class  C3DRenderSystem : public cocos2d::CCObject
{
	friend class C3DLayer;
public:
	/**
	 * get singleton
	 */
    static C3DRenderSystem* getInstance();

	/**
	 * set & get view port
	 */
    void setViewport(float x,float y,float width,float height);
    void setViewport(const C3DViewport* viewport = NULL);
    const C3DViewport* getViewport() const;

	/**
	 * get render channel manager
	 */
    RenderChannelManager* getRenderChannelManager() const;

	/**
	 * update routine
	 */
    void update(long elapsedTime);
    /**
     * Clears the specified resource buffers to the specified clear values.
     *
     * @param flags The flags indicating which buffers to be cleared.
     * @param clearColor The color value to clear to when the flags includes the color buffer.
     * @param clearDepth The depth value to clear to when the flags includes the color buffer.
     * @param clearStencil The stencil value to clear to when the flags includes the color buffer.
    */
    void clear(ClearFlags flags, const C3DVector4* clearColor, float clearDepth, int clearStencil);
	void onLostDevice();
	void reload();
protected:

	/**
	 * constructor & destructor
	 */
    C3DRenderSystem();
    virtual ~C3DRenderSystem();

	/**
	 * create render system
	 */
    static C3DRenderSystem* create();
	/**
	 * initialize & finalize
	 */
    void initialize();
    void finalize();

	// properties
    C3DViewport* _viewport;                        // the games's current viewport.
    RenderChannelManager* _renderChannelManager;

	C3DTextureMgr*		_textureMgr;
	C3DEffectManager*	_effectManager;
	C3DMaterialManager* _materialManager;
	C3DFrameBufferMgr*	_frameBufMgr;

    C3DVector4* _clearColor;                        // The clear color value last used for clearing the color buffer.

    float _clearDepth;                          // The clear depth value last used for clearing the depth buffer.
    int _clearStencil;                          // The clear stencil value last used for clearing the stencil buffer.

	C3DDeviceAdapter* _deviceAdapter;
};
}

#endif
