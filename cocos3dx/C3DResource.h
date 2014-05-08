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

#ifndef Resource_H_
#define Resource_H_
#include <string>
#include "cocos2d.h"

namespace cocos3d
{
class C3DElementNode;
class C3DResourcePool;

/**
Abstract class representing a loadable resource (e.g. textures, mesh etc)
*/
class C3DResource : public virtual cocos2d::CCObject
{
friend class C3DUsedResourcePool;
friend class C3DWaitResourcePool;

public:
	enum State
	{
		State_Init = 0,

		State_Used,

		State_Wait,
	};

	C3DResource();
	C3DResource(const std::string& id);

	virtual ~C3DResource();

	/** Calculate the size of a resource; this will only be called after 'load' */
	virtual size_t calculateSize(void) const
	{
		return 0;
	}

	virtual bool load(const std::string& fileName){ return false; }
	//virtual bool save(const std::string& fileName);

	 /**
     * load resource info from the elementnode
     *
     * @param nodes elementnode which contains the resource info.
     *
     */
	virtual bool load(C3DElementNode* node);

	 /**
     * save the resource info into the elementnode
     *
     * @param nodes elementnode which contains the renderstate info.
     *
     */
	virtual bool save(C3DElementNode* node);

	virtual void unload(){};

    size_t getSize(void) const;

	/**
    * Returns the unique string identifier for the resource.
    */
    const std::string& getID(void) const ;

	void setID(std::string& id);

	const std::string& getResourceName(void) const;

    const C3DResource::State getState(void) const;

	void setState(C3DResource::State state);

	virtual void update(long elapsedTime);

	/**
    * clone a material from current material.
    */
	virtual C3DResource* clone() const;

	void copyFrom(const C3DResource* other);

	int getCloneNum();
	
	virtual void reload(){}

private:

    std::string _id;  // Unique id of the resource
	std::string _resourceName;

    size_t _size;  // The size of the resource in bytes

	long _waitTime;
	long _checkWaitTime;
	State _state;

	int _cloneNum;
};
}

#endif
