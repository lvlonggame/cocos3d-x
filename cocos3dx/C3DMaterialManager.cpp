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
#include "C3DMaterial.h"
#include "C3DElementNode.h"
#include "C3DMaterialManager.h"
#include "C3DElementNode.h"

namespace cocos3d
{
static C3DMaterialManager* __materialManagerInstance = NULL;

C3DMaterialManager::C3DMaterialManager()
{
	LOG_TRACE_VARG("@C3DMaterialManager born at: %p", this);
}

C3DMaterialManager::~C3DMaterialManager()
{
	LOG_TRACE_VARG("@C3DMaterialManager dead at: %p", this);
	__materialManagerInstance = NULL;
}

C3DMaterialManager* C3DMaterialManager::getInstance()
{
	if (!__materialManagerInstance)
    {
        __materialManagerInstance = new C3DMaterialManager();
        __materialManagerInstance->autorelease();
    }
    return __materialManagerInstance;
}

C3DResource* C3DMaterialManager::createResource(const std::string& name)
{
    // Load the material properties from file
	C3DElementNode* nodes = C3DElementNode::create(name);
    //assert(nodes);
    if (nodes == NULL)
    {
        return NULL;
    }

    C3DElementNode* materialNodes = nodes->getNodeType().empty() ? nodes->getNextChild() : nodes;
	assert(materialNodes);
    if (!materialNodes || materialNodes->getNodeType()!="material")
    {
        return NULL;
    }

	C3DMaterial* material = new C3DMaterial(name);

	material->autorelease();

	if(material->load(materialNodes) == true)
	{
		this->setResourceState(material, C3DResource::State_Used);
	}
	else
	{
		SAFE_RELEASE(material);
		SAFE_DELETE(nodes);
		return NULL;
	}

    SAFE_DELETE(nodes);

	return material;
}

C3DResource* C3DMaterialManager::cloneResource(C3DResource* resource)
{
	if(resource != NULL)
    {
		C3DResource* newResource = resource->clone();

		this->setResourceState(newResource,C3DResource::State_Used);
		return newResource;
    }
	return NULL;
}
}