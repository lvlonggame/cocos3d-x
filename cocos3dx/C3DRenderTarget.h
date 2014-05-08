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

#ifndef RENDERTARGET_H_
#define RENDERTARGET_H_

#include "cocos2d.h"

namespace cocos3d
{
class C3DTexture;
/**
 * Represents a linear area of display memory and usually reside
 * in the display memory of the display card.
 */
class C3DRenderTarget : public cocos2d::CCObject
{
public:

	/**
	 * create render target
	 */
    static C3DRenderTarget* create(const std::string& id, unsigned int width, unsigned int height, unsigned int fmt);
    static C3DRenderTarget* getRenderTarget(const std::string& id);

	/**
	 * string id
	 */
    const std::string& getID() const;

	/**
	 * get texture
	 */
    C3DTexture* getTexture() const;

private:

	/**
	 * constructor & destructor
	 */
    C3DRenderTarget(const std::string& id);
    ~C3DRenderTarget();

	//properties
    std::string _id;
    C3DTexture* _texture;
};
}

#endif
