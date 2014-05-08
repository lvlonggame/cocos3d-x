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

#include "C3DModel.h"
#include "C3DMorph.h"
#include "C3DMorphMesh.h"

namespace cocos3d
{

C3DMorph* C3DModel::getMorph()
{
	return _morph;
}

void C3DModel::setMorph(C3DMorph* morph)
{
	if(_morph != morph)
	{
		SAFE_DELETE(_morph);

		_morph = morph;
	}
}

void C3DModel::pushMorph(int morphTargetIndex,float weight)
{
	if(_mesh!=NULL && _morph!=NULL)
	{
		static_cast<C3DMorphMesh*>(_mesh)->pushMorph(_morph,morphTargetIndex,weight);
	}
}

void C3DModel::popMorph(int morphTargetIndex)
{
	if(_mesh!=NULL && _morph!=NULL)
	{
		static_cast<C3DMorphMesh*>(_mesh)->popMorph(_morph,morphTargetIndex);
	}
}

void C3DModel::changeMorph(int morphTargetIndex,float weight)
{
	if(_mesh!=NULL && _morph!=NULL)
	{
		static_cast<C3DMorphMesh*>(_mesh)->changeMorph(_morph,morphTargetIndex,weight);
	}
}
}