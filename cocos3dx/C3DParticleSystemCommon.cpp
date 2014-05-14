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
#include "C3DParticleSystemCommon.h"
#include "C3DParticleSystem.h"
#include "cocos2d.h"

namespace cocos3d
{
C3DBaseParticleAction::C3DBaseParticleAction(C3DParticleSystem* system)
{
	_system = system;
	_name = NULL;
};

C3DBaseParticleAction::~C3DBaseParticleAction()
{
	_system = NULL;
	SAFE_DELETE_ARRAY(_name);
};

void C3DBaseParticleAction::load(C3DElementNode* psaNode)
{
	const std::string& name = psaNode->getElement("name");
	size_t size = name.length();
	_name = new char[size+1];
    memcpy(_name, name.c_str(), size);
	_name[size] = 0;
}

void C3DBaseParticleAction::save(C3DElementNode* psaNode)
{
	psaNode->setElement("name", &_name);
}

void C3DBaseParticleAction::copyFrom(const C3DBaseParticleAction* other)
{
    if (other->_name)
    {
        SAFE_DELETE_ARRAY(_name);
        _name = new char[strlen(other->_name) + 1];
        strcpy(_name, other->_name);
    }
}

C3DBaseParticleAction* C3DBaseParticleAction::clone(C3DParticleSystem* system) const
{
    C3DBaseParticleAction* action = new C3DBaseParticleAction(system);
    action->copyFrom(this);
    return action;
}
}