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

#ifndef SCENE_H_
#define SCENE_H_

#include <map>
#include <list>
#include "C3DNode.h"
#include <vector>

namespace cocos3d
{
class C3DCamera;
class C3DRenderNode;
class C3DVector3;
class RenderChannelManager;
class C3DLight;

class C3DSprite;
class C3DStaticObj;
class C3DBatchMesh;
class C3DParticleSystem;
class C3DShadowMap;
class C3DLayer;
class C3DPostProcess;
class C3DGeoWireRender;

class C3DOctree;

/**
*Defines the scene node,which includes all the scene object,for example,light,camera,sprite,and so on.
*/
class  C3DScene : public C3DNode
{
friend class C3DNode;
public:

    static C3DScene* createScene(C3DLayer* layer);

    void setLayer(C3DLayer* layer);
    C3DLayer* getLayer() const;

    C3DNode* findNode(const std::string& strId);

    void removeAllNode();

    C3DCamera* getActiveCamera() const;

    //set active camera by index
    bool setActiveCamera(int index);
    //get number of cameras in the scene
    int getCameraCount() const;

   // get light count
    int getLightCount() const { return (int)_lights.size(); }
    // get light by index
    C3DLight* getLight(int index);

    /**
     *  set default depth, used when z is not provided during function call C3DNode::setScreenPos()
     */
    void setDefDepthZ(float defDepth)  { _defDepthZ = defDepth; }

    /**
     *  get default depth
     */
    float getDefDepthZ() { return _defDepthZ; }

	void setViewAspectRatio(float aspectRatio);

	const C3DVector3* getAmbientColor() const;

    void setAmbientColor(float red, float green, float blue);

    void draw();
	void preDraw();
	void postDraw();
	void drawDebug();
	void showBoundingBox(bool show);

    // update routine
    virtual void update(long elapsedTime);

    C3DScene(const std::string& strId = "");

    virtual ~C3DScene();

    //void EnalbeFrustumCull(bool bEnable, bool )

	virtual Type getType() const;

    const C3DMatrix& getViewProjectionMatrix() const;

    C3DShadowMap* getActiveShadowMap() const;
    C3DShadowMap* setActiveShadowMap(int index);
    int getShadowMapCount() const;

    bool isInShadowPass() const { return _inShadowPass; }

	C3DPostProcess* getActivePostProcess() const;
	void setActivePostProcess( C3DPostProcess* process );

	C3DGeoWireRender* getGeoWireRender();

	void addNodeToRenderList(C3DNode* node);
	void removeNodeFromRenderList(C3DNode* node);

	const C3DVector4& getTimeParam(void) const;

protected:
	virtual void onChildChanged(ChangeEvent eventType, C3DNode* child);

private:

    C3DVector3* _ambientColor;

    std::vector<C3DLight*> _lights;
    std::vector<C3DCamera*> _cameras;
    std::vector<C3DShadowMap*> _shadowMaps;
	std::vector<C3DPostProcess*> _postProcesss;
	std::vector<C3DNode*> _postDrawNode;

	bool _showBoundingBox;
	bool _showLightPos;

    float _defDepthZ;//default depth z.

    bool _inShadowPass;

	C3DCamera* _activeCamera;

	C3DLight* _activeLight;

    C3DShadowMap* _activeShadowMap;

	C3DPostProcess* _activePostProcess;
    C3DLayer* _layer;

	C3DGeoWireRender* _geoWireRender;

};
}

#endif
