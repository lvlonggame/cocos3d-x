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

#include "FacialAnimation.h"
#include "C3DLayer.h"
#include "StringTool.h"
#include "C3DTechnique.h"
#include "C3DMaterial.h"
#include "C3DPass.h"
#include "C3DTexture.h"
#include "C3DVector2.h"
#include "MaterialParameter.h"

namespace cocos3d
{
SheetAnimation::SheetAnimation()
{
	wrapType = SheetAnimWrapType_Loop;

	frameNum = 0;
	fps = 0.001f;

	partName = "";
	typeName = "";

	mat = NULL;
	enable = false;
}

SheetAnimation::~SheetAnimation()
{
	SAFE_DELETE_ARRAY(frameSerials);
}

void SheetAnimation::generateFrameSerial(std::string &frameSerial)
{
	if(frameSerial == "")
		return;

	std::vector<string> a = StringTool::StringSplitByChar(frameSerial,'-');

	frameSerialNum = a.size();
	frameSerials = new int[frameSerialNum];
	for(int i = 0;i<frameSerialNum;i++)
	{
		frameSerials[i] = std::atoi(a[i].c_str());
	}
}

void SheetAnimation::update(long elapsedTime)
{
	if(mat == NULL || enable==false)
		return;

	int index = (int)C3DLayer::getGameTime() * fps;

	index = index % (frameSerialNum);

	if(index >= frameSerialNum)
		index = 0;

	_curFrameIndex = frameSerials[index];
}

TextureAnimation::TextureAnimation()
{
	_textures = NULL;
}

TextureAnimation::~TextureAnimation()
{
	for( int i=0; i<frameNum; i++)
	{
		SAFE_RELEASE(_textures[i]);
	}
	SAFE_DELETE_ARRAY(_textures);
}

void TextureAnimation::generateFrameSerial(std::string &frameSerial)
{
	SheetAnimation::generateFrameSerial(frameSerial);

	_textures = new C3DTexture*[frameNum];
	std::string path = "objects/Test_0";
	char name[128];
	for( int i=0; i<frameNum; i++)
	{
		sprintf(name,"%s%d.png",path.c_str(),i);

		_textures[i] = C3DTexture::create(name, true);
	}
}

void TextureAnimation::update(long elapsedTime)
{
	SheetAnimation::update(elapsedTime);

	//mat->getParameter("u_diffuseTexture")->setValue(texture);

	C3DTechnique* technique = mat->getTechnique(C3DMaterial::TECH_USAGE_SCREEN);
	unsigned int passCount = technique->getPassCount();
	for (unsigned int i = 0; i < passCount; ++i)
	{
		C3DPass* pass = technique->getPass(i);
		pass->getParameter("u_diffuseTexture")->setValue(_textures[_curFrameIndex]);
	}
}

UVAnimation::UVAnimation()
{
	tileX = 0;
	tileY = 0;
}

UVAnimation::~UVAnimation()
{
}

void UVAnimation::update(long elapsedTime)
{
	SheetAnimation::update(elapsedTime);

	C3DVector2 size(1.0f/tileX,1.0f/tileY);

	int uIndex = _curFrameIndex % tileX;
	int vIndex = _curFrameIndex / tileX;

	C3DVector2 offset(uIndex*size.x,1.0f-size.y-vIndex*size.y);

    mat->getParameter("u_uvOffset")->setValue(offset);
	mat->getParameter("u_uvSize")->setValue(size);
}
}