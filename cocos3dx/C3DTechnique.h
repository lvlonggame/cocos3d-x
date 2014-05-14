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

#ifndef TECHNIQUE_H_
#define TECHNIQUE_H_

#include<vector>
#include "C3DRenderState.h"

namespace cocos3d
{
class C3DMaterial;
class C3DRenderChannel;

/**
 * Defines a technique for an model to be rendered.
 *
 * one technique contains several pass for render an model.
 * when multiple pass are loaded using a material file,
 * the current pass can be set at runtime.
 */
class C3DTechnique : public C3DRenderState
{
    friend class C3DMaterial;
    friend class C3DPass;
    friend class C3DRenderState;

public:

	C3DTechnique();

	C3DTechnique(const std::string& id, C3DMaterial* material);

    ~C3DTechnique();

    const std::string& getId() const;

    unsigned int getPassCount() const;

    C3DPass* getPass(unsigned int index) const;

    C3DPass* getPass(const std::string& id) const;

	void setChannel(const std::string& channelName);
	C3DRenderChannel* getChannel();
	C3DTechnique* clone() const;

	 /**
     * load info from the elementnode
     *
     * @param nodes elementnode which contains the renderstate info.
     *
     */
	virtual bool load(C3DElementNode* node);

	 /**
     * save the technique info into the elementnode
     *
     * @param nodes elementnode which contains the renderstate info.
     *
     */
	virtual bool save(C3DElementNode* node);

	virtual void reload();

private:

    std::string _id;
    C3DMaterial* _material;
    std::vector<C3DPass*> _passes;

	std::string _renderChannelName;
	//C3DRenderChannel* _renderChannel;
};
}

#endif
