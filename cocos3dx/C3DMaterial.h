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

# ifndef MATERIAL_H_
# define MATERIAL_H_

#include "C3DRenderState.h"
#include "C3DResource.h"

namespace cocos3d
{
class C3DElementNode;
class C3DTechnique;
class C3DRenderChannel;
class C3DEffect;

/**
 * Defines a material for an model to be rendered.
 *
 * one material contains several techniques for render an model.
 * when multiple techniques are loaded using a material file,
 * the current technique can be set at runtime.
 */
class C3DMaterial : public C3DRenderState, public C3DResource
{
	friend class C3DMaterialManager;

public:
    enum TechniqueUsage
    {
        // render to screen
        TECH_USAGE_SCREEN,
        // render depth to shadow map
        TECH_USAGE_SHADOWMAP,

        // Number of this enumeration
        TECH_USAGE_NUM,
    };

protected:
	C3DMaterial(const std::string& name);

	virtual ~C3DMaterial();
	 /**
     * create a material from the file.
     *
     * @param vshSource The vertex shader source code.
     * @param fshSource The fragment shader source code.
     * @param defines A new-line delimited list of preprocessor defines. May be NULL.
     *
     * @return The created material.
     */
    //static C3DMaterial* create(const std::string& fileName);
	/**
     * create a material from the material info of an elementnode.
     *
     * @param materialNodes the elementnode which contain the material info
     *
     * @return The created material.
     */
    //static C3DMaterial* create(C3DElementNode* materialNodes);
public:

	 /**
     * create a material from the given vertex and fragment shader source code.
     *
     * @param vshSource The vertex shader source code.
     * @param fshSource The fragment shader source code.
     * @param defines A new-line delimited list of preprocessor defines. May be NULL.
     *
     * @return The created material.
     */
    //static C3DMaterial* create(const std::string& vshPath, const std::string& fshPath, const std::string& defines = "");

  //  static C3DMaterial* create(C3DEffect* effect);
    unsigned int getTechniqueCount() const;

	 /**
     * get the specified technique.
     *
     * @param index the index of the specified technqiue.
     *
     * @return The created material.
     */
    C3DTechnique* getTechnique(unsigned int index) const;

    C3DTechnique* getTechnique(const std::string& id) const;

    C3DTechnique* getTechnique(TechniqueUsage usage) const;

	C3DTechnique* getTechnique() const;

	 /**
     * set the specified technique to specified technique channel.
     *
     * @param usage the usage of the specified technique channel.
	 * @param index the index of the specified technqiue.
     *
     * @return The created material.
     */
    bool setTechnique(TechniqueUsage usage, unsigned int index);

    bool setTechnique(TechniqueUsage usage, const std::string& id);

	 /**
     * clone a material from current material.
     */
	virtual C3DMaterial* clone() const;

	//virtual void copyFrom(const C3DResource* other);

	 /**
     * load info from the elementnode
     *
     * @param nodes elementnode which contains the renderstate info.
     *
     */
	virtual bool load(C3DElementNode* nodes);

	 /**
     * save the material info into the elementnode
     *
     * @param nodes elementnode which contains the renderstate info.
     *
     */
	virtual bool save(C3DElementNode* nodes);

	virtual void reload();

private:

    std::vector<C3DTechnique*> _techniques;

    C3DTechnique* _techniqueChannel[TECH_USAGE_NUM];
};
}

#endif
