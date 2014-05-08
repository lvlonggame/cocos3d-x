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

#include "C3DResourcePool.h"
#include "C3DResource.h"
#include "C3DResourceManager.h"
#include "Base.h"
namespace cocos3d
{
C3DResourcePool::C3DResourcePool(C3DResourceManager* manager)
{
	_manager = manager;
}

C3DResourcePool::~C3DResourcePool()
{
	clear();

	_manager = NULL;
}

void C3DResourcePool::clear()
{
	for (std::map<std::string,C3DResource*>::iterator iter = _items.begin(); iter != _items.end(); ++iter)
	{
		iter->second->release();
	}
	_items.clear();
}

bool C3DResourcePool::addItem(C3DResource* item)
{
	if(_items.find(item->getID()) == _items.end())
	{
		_items[item->getID()] = item;
		item->retain();
		return true;
	}
	else
		return false;
}

bool C3DResourcePool::removeItem(const std::string& name)
{
	std::map<std::string,C3DResource*>::iterator iter = _items.find(name);

	if(iter != _items.end())
	{
		iter->second->release();
		_items.erase(iter);
		return true;
	}
	else
		return false;
}

C3DResource* C3DResourcePool::getItem(const std::string& name)
{
	std::map<std::string,C3DResource*>::iterator iter = _items.find(name);
	if(iter != _items.end())
	{
		return iter->second;
	}
	else
		return NULL;
}

void C3DResourcePool::reload()
{
	std::map<std::string, C3DResource*>::iterator iter = _items.begin();
	while(iter != _items.end())
	{
		iter->second->reload();
		++iter;
	}
}

C3DUsedResourcePool::C3DUsedResourcePool(C3DResourceManager* manager)
	:C3DResourcePool(manager)
{
	_manager = manager;
}

void C3DUsedResourcePool::update(long elapsedTime)
{
	C3DResource* item = NULL;
	for (std::map<std::string,C3DResource*>::iterator iter = _items.begin(); iter != _items.end(); )
	{
		item = iter->second;

		if(item->getReferenceCount() ==1)
		{
			item->setState(C3DResource::State_Wait);
			_manager->addResource(item);
			item->release();
			_items.erase(iter++);
		}
		else
		{
			++iter;
		}
	}
}

//.............................
C3DWaitResourcePool::C3DWaitResourcePool(C3DResourceManager* manager)
	:C3DResourcePool(manager)
{
	_manager = manager;
}

void C3DWaitResourcePool::update(long elapsedTime)
{
	C3DResource* item = NULL;
	for (std::map<std::string,C3DResource*>::iterator iter = _items.begin(); iter != _items.end(); )
	{
		item = iter->second;

		item->_checkWaitTime += elapsedTime;
		if(item->_checkWaitTime > item->_waitTime)
		{
			item->_checkWaitTime = 0;

			item->release();
			_items.erase(iter++);
		}
		else
		{
			++iter;
		}
	}
}
}