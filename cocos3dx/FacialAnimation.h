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

#ifndef SHEETANIMATION_H_
#define SHEETANIMATION_H_
#include <string>

using namespace std;
namespace cocos3d
{
/**
 * Sheet animation wrap type
 */
enum SheetAnimWrapType
{
    SheetAnimWrapType_Loop   = 0 ,
	SheetAnimWrapType_Once ,
};

class C3DMaterial;
class C3DTexture;

/**
 * Defines a base class to describe sheet animation.
 */
class SheetAnimation
{
	friend class FacialAnimManager;
	friend class TextureAnimation;
	friend class UVAnimation;
public:
	/**
     * Constructor.
     */
	SheetAnimation();

	/**
     * Destructor.
     */
    virtual ~SheetAnimation();

	/**
	 * Create SheetAnimation by frame serial string.
	 */
	virtual void generateFrameSerial(string &frameSerial);

	/**
	 * Update per frame.
	 */
	virtual void update(long elapsedTime);

private:

	int frameNum;

	string partName;
	string typeName;

	SheetAnimWrapType wrapType;
	float fps;
	bool enable;

	int  *frameSerials;
	int frameSerialNum;

	C3DMaterial *mat;
	int _curFrameIndex;
};

/**
 * Defines a class for texture animation
 */
class TextureAnimation : public SheetAnimation
{
public:
	/**
     * Constructor.
     */
	TextureAnimation();

	/**
     * Destructor.
     */
	virtual ~TextureAnimation();

	/**
	 * Create SheetAnimation by frame serial string.
	 */
	virtual void generateFrameSerial(string &frameSerial);

	/**
	 * Update per frame.
	 */
	virtual void update(long elapsedTime);

private:
	C3DTexture** _textures;
};

/**
 * Defines a class for UV animation
 */
class UVAnimation : public SheetAnimation
{
	friend class FacialAnimManager;
public:
	/**
     * Constructor.
     */
	UVAnimation();

	/**
     * Destructor.
     */
	virtual ~UVAnimation();

	/**
	 * Update per frame.
	 */
	virtual void update(long elapsedTime);

private:
	int tileX;
	int tileY;
};

}

#endif
