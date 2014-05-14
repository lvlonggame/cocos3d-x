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

#ifndef __C3DActor_H__
#define __C3DActor_H__

#include "cocos2d.h"
#include "cocos3d.h"
#include <string>

#include "C3DBaseActor.h"

namespace cocos3d
{
	class C3DNode;
	class C3DSprite;
	class C3DVector3;
	class C3DLayer;
}

namespace cocos3d
{
	class C3DNode;
	class C3DSprite;
	class C3DVector3;
	class C3DLayer;
	class FacialAnimManager;
}

namespace cocos2d
{
class BodyPartConfig;
class MorphConfig;

class C3DActor : public C3DBaseActor
{
public:
	C3DActor(std::string& name,cocos3d::C3DNode* node, cocos3d::C3DLayer* layer);
	virtual ~C3DActor();

	/**
    * add valid config info for the sprite.
    *
	* @param type part type
	* @param canNone whether the part of avata model can been 1to removed.
	* @param modelName the mesh name of the part.
	* @param matName the material name of the part.
    */
	bool addPartConfig(const std::string& type,bool canNone);

	/**
    * delete valid config info for the avatar model.
	* @param type part type
	*/
	bool delPartConfig(const std::string& type);

	bool addPart(const std::string& type, const std::string& modelName, const std::string& matName);
	bool delPart(const std::string& type,const std::string& modelName,const std::string& matName);
	/**
    * set the cur materials of the avatar model.
    *
    * @param type The part type of the avatar model.
    * @param index The part index in the parts of special type.
    */
	void setPart(const std::string& type,int index);

	/**
    * load the cur materials of the avatar model.
    *
    * @param type The part type of the avatar model.
    * @param index The part index in the parts of special type.
    */
	void loadParts();

	/**
    * change to the next material for the special type part of the avatar model.
    *
    * @param type The part type of the avatar model.
    */
	void changePart(const std::string& type);

	/**
    * change to the next material for the special type part of the avatar model.
    *
    * @param type The part type of the avatar model.
	* @param index The part index of the part.
    */
	void changePart(const std::string& type,int index);

	void removePart(const std::string& type);
	void changePart(const std::string& type,const std::string& modelName,const std::string& matName);

	void setMaterial(const std::string& type, const std::string& modelName, const std::string& matName);

	void createMorph(const std::string& meshName);
	void setMorphToMesh(const std::string&  type,unsigned int morphTargetIndex,float weight);
	void addMorph(const std::string& modelName,unsigned int morphTargetIndex,float weight);
	void changeMorph(const std::string& type,float weight);

//	void createFacialAnim();
//	void setSheetAnim(cocos3d::FacialAnimManager* facialAnimManager);
//	void initExpression(cocos3d::FacialAnimManager* facialAnimManager);

protected:

	float _life;

	std::map<std::string,BodyPartConfig*>* _partConfigs;

	MorphConfig* _morphConfig;

	std::map<std::string,cocos3d::C3DNode*>* _models;
};
}
#endif
