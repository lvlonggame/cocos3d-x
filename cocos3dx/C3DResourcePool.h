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

#ifndef ResourcePool_H_
#define ResourcePool_H_

#include <map>
#include <string>

namespace cocos3d
{
class C3DResource;
class C3DResourceManager;

/**
Resource pool
*/
class  C3DResourcePool
{
public:
	C3DResourcePool(C3DResourceManager* manager);
	virtual ~C3DResourcePool();

	bool  removeItem(const std::string& name);

	bool addItem(C3DResource* item);

    C3DResource* getItem(const std::string& name);
	void clear();

	virtual void update(long elapsedTime) = 0;

	void reload();

public:
	std::map<std::string,C3DResource*> _items;
	C3DResourceManager* _manager;
};

class C3DUsedResourcePool : public C3DResourcePool
{
public:
	C3DUsedResourcePool(C3DResourceManager* manager);
	virtual void update(long elapsedTime);
};

class C3DWaitResourcePool : public C3DResourcePool
{
public:
	C3DWaitResourcePool(C3DResourceManager* manager);
	virtual void update(long elapsedTime);
};
}

#endif
