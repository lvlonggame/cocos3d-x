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

#ifndef SKELETON_H_
#define SKELETON_H_

#include <string>
#include <map>
#include "C3DBatchMesh.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
namespace cocos3d
{
class C3DNode;
class C3DAnimation;
class C3DBone;
class C3DGeoWireRender;

/**
 * Defines a class for controlling skeleton bone.
 */
class C3DSkeleton
{
public:
	/**
     * Constructor.
     */
    C3DSkeleton();

	/**
     * Destructor.
     */
    virtual ~C3DSkeleton();

	/**
     * Creates C3DBone.
     */
    C3DBone* createBone(const std::string& name);

	/**
     * Get root bone.
     */
	C3DBone* getRootBone(void) const{return _rootBone;}

	/**
     * Get root by specified name.
     */
    C3DBone* getBone(const std::string& name) const;

	/**
     * Creates C3DAnimation.
     */
    C3DAnimation* createAnimation(const std::string& name);

	/**
     * Gets C3DAnimation by specified name.
     */
    C3DAnimation* getAnimation(const std::string& name) const;

	/**
     * Removes C3DAnimation by specified name.
     */
    void removeAnimation(const std::string& name);

	/**
     * Sets C3DBone.
     */
	void set(C3DBone* joint);

	/**
     * Gets bone's child bone.
     */
	void getChild(std::map<std::string, C3DBone*>& bones,C3DNode* node);

	/**
     * clone.
     */
	C3DSkeleton* clone();

private:
	C3DBone* _rootBone;
    /// Lookup by bone name
    std::map<std::string, C3DBone*> _bones;

    /// Storage of animations, lookup by name
    std::map<std::string, C3DAnimation*> _animations;
};

}

#endif
