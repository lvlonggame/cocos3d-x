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
#include "C3DForcePSA.h"

#include "C3DParticleSystem.h"
#include "C3DElementNode.h"
namespace cocos3d
{
C3DForcePSA::C3DForcePSA(C3DParticleSystem* system) :
     C3DBaseParticleAction(system)
{
}

C3DForcePSA::~C3DForcePSA()
{
}

void C3DForcePSA::load(C3DElementNode* properties)
{
	C3DBaseParticleAction::load(properties);

    properties->getElement("force", &_force);
}

void C3DForcePSA::save(C3DElementNode* properties)
{
	properties->empty();

	C3DBaseParticleAction::save(properties);

	properties->setElement("force", &_force);
}

void C3DForcePSA::action(long elapsedTime)
{
	// Calculate the time passed since last update.
    float elapsedSecs = (float)elapsedTime * 0.001f;
	C3DParticle**& _particles = _system->_particles;
	int& _validParticleCount = _system->_validParticleCount;

	for (int i = 0; i < _validParticleCount; ++i)
    {
		C3DParticle*& p = _particles[i];

        p->_velocity.x += _force.x * elapsedSecs;
        p->_velocity.y += _force.y * elapsedSecs;
        p->_velocity.z += _force.z * elapsedSecs;
    }
}

C3DBaseParticleAction* C3DForcePSA::clone(C3DParticleSystem* system) const
{
    C3DForcePSA* psa = new C3DForcePSA(system);

    psa->copyFrom(this);
    psa->_force = _force;

    return psa;
}
}