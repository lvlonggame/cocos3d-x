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

#ifndef PASS_H_
#define PASS_H_

#include "C3DRenderState.h"

namespace cocos3d
{
class C3DTechnique;
class C3DVertexDeclaration;
class C3DEffect;

/**
 * Defines a pass for an model to be rendered.
 *
 * This class includes an effect and a vertexattribute declaration.This class is the direct
 * render interface,you can set all the shader values by which.
 */
class C3DPass : public C3DRenderState
{
    friend class C3DTechnique;
    friend class C3DMaterial;
    friend class C3DRenderState;

public:
	C3DPass();
	C3DPass(const std::string& id, C3DTechnique* technique, C3DEffect* effect);

    ~C3DPass();

    const std::string& getId() const;

    C3DEffect* getEffect() const;

    const std::vector<std::string>* getAutoBindProperties() const;

    void setVertexAttributeBinding(C3DVertexDeclaration* binding);

    void bind();
	void setParamMethonAutoUniform();

    void unbind();

	virtual void reload();

    // get max support lights each type
    int getMaxDirLight() const { return _nMaxDirLight; }
    int getMaxPointLight() const  { return _nMaxPointLight; }
    int getMaxSpotLight() const { return _nMaxSpotLight; }
	int getMaxAnimLight() const { return _nMaxAnimLight; }
    int getMaxShadowMap() const { return _nMaxShadowMap; }

	C3DPass* clone() const;

    void setupParametersFromEffect();

	 /**
     * load info from the elementnode
     *
     * @param nodes elementnode which contains the renderstate info.
     *
     */
	virtual bool load(C3DElementNode* node);

	 /**
     * save the pass info into the elementnode
     *
     * @param nodes elementnode which contains the renderstate info.
     *
     */
	virtual bool save(C3DElementNode* node);

	std::string getVshPath()const{return _vshPath;}
	std::string getFshPath()const{return _fshPath;}
	std::string getDefines()const{return _defines;}
private:

    std::string _id;
    C3DTechnique* _technique;
    C3DEffect* _effect;
    C3DVertexDeclaration* _vaBinding;

    std::string _vshPath;
    std::string _fshPath;
    std::string _defines;

    //max support lights
    int _nMaxDirLight;
    int _nMaxPointLight;
    int _nMaxSpotLight;
	int _nMaxAnimLight;

    int _nMaxShadowMap;
};
}

#endif
