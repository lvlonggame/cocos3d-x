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

#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_
#include "Base.h"

#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DMatrix.h"

#include <string>
#include <map>
#include "cocos2d.h"
#include "C3DResourceManager.h"

namespace cocos3d
{
class C3DElementNode;
class C3DEffect;

/**
 *A C3DEffectManager manager effect's load£¬preload, and so on.
 */
class C3DEffectManager : public C3DResourceManager
{
public:

	static C3DEffectManager* getInstance();

	virtual C3DResource* createResource(const std::string& name);

	virtual C3DResource* cloneResource(C3DResource* resource);

	/**
     * preload all shader files from the specific config file.
     *
     * @param fileName The path to the shader config file.
     */
	virtual void preload(const std::string& name);

	 /**
     * preload  this shader file.
     *
     * @param vshPath The path to the vertex shader file.
	 * @param fshPath The path to the fragment shader file.
	 * @param defines The precompile defines.
     */
	void preload(C3DElementNode* node);

	static std::string generateID( std::string& vshPath, std::string& fshPath, std::string& defines);
private:

    C3DEffectManager();

    ~C3DEffectManager();

	void loadAllEffect(C3DElementNode* effectNodes);

};
}

#endif
