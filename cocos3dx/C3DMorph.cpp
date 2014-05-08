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

#include "C3DMorph.h"

namespace cocos3d
{
C3DMorph::C3DMorph(void)
{
	_morphTargets = new std::vector<MorphTarget*>();
	_curTargets = new std::vector<unsigned int>();
}

C3DMorph::~C3DMorph(void)
{
	for( std::vector<MorphTarget*>::iterator iter=_morphTargets->begin(); iter!=_morphTargets->end(); iter++ )
	{
		delete *iter;
	}
	delete _morphTargets;
	delete _curTargets;
}

MorphTarget* C3DMorph::getMorphTarget(std::string name)
{
	std::vector<MorphTarget*>::iterator iter;
	for(iter = _morphTargets->begin(); iter!= _morphTargets->end(); ++iter )
	{
		if((*iter)->name==name)
			return *iter;
	}

	return NULL;
}

MorphTarget* C3DMorph::getMorphTarget(int index)
{
	std::vector<MorphTarget*>::iterator iter;
	for(iter = _morphTargets->begin(); iter!= _morphTargets->end(); ++iter )
	{
		if((*iter)->index==index)
			return *iter;
	}

	return NULL;
}

void C3DMorph::addMorphTarget(MorphTarget* target)
{
	std::vector<MorphTarget*>::iterator iter;
	for(iter = _morphTargets->begin(); iter!= _morphTargets->end(); ++iter )
	{
		if((*iter)==target)
		{
			_morphTargets->erase(iter);
			break;
		}
	}

	_morphTargets->push_back(target);
}

void C3DMorph::clearCurTarget()
{
	_curTargets->clear();
}

bool C3DMorph::pushTarget(unsigned int targetIndex)
{
	std::vector<unsigned int>::iterator iter;
	for(iter = _curTargets->begin(); iter!= _curTargets->end(); ++iter )
	{
		if((*iter)==targetIndex)
			return false;
	}

	_curTargets->push_back(targetIndex);

	return true;
}

bool C3DMorph::popTarget(unsigned int targetIndex)
{
	std::vector<unsigned int>::iterator iter;
	for(iter = _curTargets->begin(); iter!= _curTargets->end(); ++iter )
	{
		if((*iter)==targetIndex)
		{
			_curTargets->erase(iter);
			return true;
		}
	}

	return false;
}

std::vector<unsigned int>* C3DMorph::getCurTargets()
{
	return _curTargets;
}
}