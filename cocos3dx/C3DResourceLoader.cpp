﻿/****************************************************************************
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

#include "Base.h"
#include "C3DResourceLoader.h"
#include "C3DStream.h"
#include "MeshPart.h"
#include "BonePart.h"
#include "C3DMorph.h"
#include "C3DScene.h"
#include "C3DBone.h"
#include "C3DCamera.h"

#include "C3DModel.h"
#include "C3DModelNode.h"
#include "C3DSkinModel.h"
#include "C3DSkinlessModel.h"
#include "C3DMesh.h"
#include "C3DMorphMesh.h"
#include "C3DMeshSkin.h"
#include "C3DVertexFormat.h"
#include "C3DNode.h"
#include "C3DLight.h"

#include "C3DAnimation.h"

#include "BundleData.h"
#include "C3DStaticObj.h"
#include "C3DAABB.h"
#include "C3DSprite.h"

#include "C3DAnimationCurve.h"

#include "C3DStream.h"

#define BUNDLE_VERSION_MAJOR            1
#define BUNDLE_VERSION_MINOR            2

#define BUNDLE_TYPE_SCENE               1
#define BUNDLE_TYPE_NODE                2
#define BUNDLE_TYPE_ANIMATIONS          3
#define BUNDLE_TYPE_ANIMATION           4
#define BUNDLE_TYPE_ANIMATION_CHANNEL   5
#define BUNDLE_TYPE_MODEL               10
#define BUNDLE_TYPE_MATERIAL            16
#define BUNDLE_TYPE_EFFECT              18
#define BUNDLE_TYPE_CAMERA              32
#define BUNDLE_TYPE_LIGHT               33
#define BUNDLE_TYPE_MESH                34
#define BUNDLE_TYPE_MESHPART            35
#define BUNDLE_TYPE_MESHSKIN            36

// For sanity checking string reads
#define BUNDLE_MAX_STRING_LENGTH        5000

namespace cocos3d
{

C3DResourceLoader::C3DResourceLoader(const std::string& path) :
    _path(path), _referenceCount(0), _references(NULL), _stream(NULL)
{
	_meshSkins = new std::vector<MeshSkinData*>();
}

C3DResourceLoader::~C3DResourceLoader()
{
    clearLoadSession();
	SAFE_DELETE(_meshSkins)

    SAFE_DELETE_ARRAY(_references);

	if (_stream)
    {
        SAFE_DELETE(_stream);
    }
}

C3DResourceLoader* C3DResourceLoader::create(const std::string& path)
{
    // Open the bundle
    C3DStream* stream = C3DStreamManager::openStream(path, "rb");
    if (!stream)
    {
        WARN_VARG("Failed to open file: '%s'.", path.c_str());
        return NULL;
    }

	char identifier[] = { 'C', 'K', 'B', '\n' };

    // Read header info
    char sig[4];

	if (stream->read(sig, 1, 4) != 4 || memcmp(sig, identifier, 4) != 0)
	{
        LOG_ERROR_VARG("Invalid bundle header: %s", path.c_str());
		SAFE_DELETE(stream);
        return NULL;
    }

    // Read version
    unsigned char ver[2];
    if (stream->read(ver, 1, 2) != 2 || ver[0] != BUNDLE_VERSION_MAJOR || ver[1] != BUNDLE_VERSION_MINOR)
    {
        LOG_ERROR_VARG("Unsupported version (%d.%d) for bundle: %s (expected %d.%d)", (int)ver[0], (int)ver[1], path.c_str(), BUNDLE_VERSION_MAJOR, BUNDLE_VERSION_MINOR);

		SAFE_DELETE(stream);
        return NULL;
    }

	//........
	unsigned char isSkin;
    if (!stream->read(&isSkin))
    {
        LOG_ERROR_VARG("Invalid bundle header: %s", path.c_str());
        return NULL;
    }
	//........

    // Read ref table
    unsigned int refCount;
	if (stream->read(&refCount, 4, 1) != 1)
    {
		SAFE_DELETE(stream);
		LOG_ERROR_VARG("Failed to read ref table for bundle '%s'.", path.c_str());

        return NULL;
    }

    // Read all refs
    Reference* refs = new Reference[refCount];
    for (unsigned int i = 0; i < refCount; ++i)
    {
        if ((refs[i].id = stream->readString()).empty() ||
            stream->read(&refs[i].type, 4, 1) != 1 ||
            stream->read(&refs[i].offset, 4, 1) != 1)
        {
			LOG_ERROR_VARG("Failed to read ref number %d for bundle '%s'.", i,path.c_str());

            SAFE_DELETE(stream);
            SAFE_DELETE_ARRAY(refs);
            return NULL;
        }
    }

    // Keep file open for faster reading later
    C3DResourceLoader* bundle = new C3DResourceLoader(path);
    bundle->_referenceCount = refCount;
    bundle->_references = refs;
    bundle->_stream = stream;
	bundle->_isSkin = isSkin;

    return bundle;
}

C3DResourceLoader::Reference* C3DResourceLoader::find(const std::string& id) const
{
    // Search the ref table for the given id (case-sensitive)
    for (unsigned int i = 0; i < _referenceCount; ++i)
    {
        if (_references[i].id == id)
        {
            // Found a match
            return &_references[i];
        }
    }

    return NULL;
}

void C3DResourceLoader::clearLoadSession()
{
    for (unsigned int i = 0, count = _meshSkins->size(); i < count; ++i)
    {
        SAFE_DELETE((*_meshSkins)[i]);
    }
    _meshSkins->clear();
}

const std::string C3DResourceLoader::getIdFromOffset() const
{
    return getIdFromOffset((unsigned int) _stream->tell());
}

const std::string C3DResourceLoader::getIdFromOffset(unsigned int offset) const
{
    // Search the ref table for the given offset
    if (offset > 0)
    {
        for (unsigned int i = 0; i < _referenceCount; ++i)
        {
            if (_references[i].offset == offset && _references[i].id.length() > 0)
            {
                return _references[i].id;
            }
        }
    }
    return "";
}

C3DResourceLoader::Reference* C3DResourceLoader::seekTo(const std::string& id, unsigned int type)
{
    Reference* ref = find(id);
    if (ref == NULL)
    {
        LOG_ERROR_VARG("No object with name '%s' in bundle '%s'.", id.c_str(), _path.c_str());
        return NULL;
    }

    if (ref->type != type)
    {
        LOG_ERROR_VARG("Object '%s' in bundle '%s' has type %d (expected type %d).", id.c_str(), _path.c_str(), (int)ref->type, (int)type);
        return NULL;
    }

    // Seek to the offset of this object
    if (_stream->seek(ref->offset, SEEK_SET) == false)
    {
        LOG_ERROR_VARG("Failed to seek to object '%s' in bundle '%s'.", id.c_str(), _path.c_str());
        return NULL;
    }

    return ref;
}

C3DResourceLoader::Reference* C3DResourceLoader::seekToFirstType(unsigned int type)
{
    // for each Reference
    for (unsigned int i = 0; i < _referenceCount; ++i)
    {
        Reference* ref = &_references[i];
        if (ref->type == type)
        {
            // Found a match
            if (_stream->seek(ref->offset, SEEK_SET) == false)
            {
                LOG_ERROR_VARG("Failed to seek to object '%s' in bundle '%s'.", ref->id.c_str(), _path.c_str());
                return NULL;
            }
            return ref;
        }
    }
    return NULL;
}

unsigned int C3DResourceLoader::seekToNextType()
{
	size_t tp		 = _stream->tell();

	size_t idx		 = numeric_limits<size_t>::max();
	size_t minOffset = numeric_limits<size_t>::max();

	for(size_t i=0; i<_referenceCount; ++i)
	{
		if(_references[i].offset >= tp && _references[i].offset < minOffset)
		{
			minOffset = _references[i].offset;
			idx = i;
		}
	}

	if(idx<_referenceCount)
	{
		_stream->seek(_references[idx].offset, SEEK_SET);
		return _references[idx].type;
	}

	return -1;
}

void C3DResourceLoader::loadSuperModel(C3DSprite* superModel,std::string nodeName)
{
	clearLoadSession();

	C3DNode* node = this->loadNode(nodeName, superModel);

    if (node)
    {
		superModel->addChild( node);
        node->release(); // scene now owns node
    }

	 resolveJointReferences(superModel);

    return ;
}

void C3DResourceLoader::loadSuperModel(C3DSprite* superModel,std::list<std::string>* models)
{
	clearLoadSession();
	for(std::list<std::string>::iterator iter = models->begin();iter != models->end();++iter)
    {
		C3DNode* node = this->loadNode(*iter, superModel);
        if (node)
        {
			superModel->addChild( node);
            node->release();
        }
    }

	resolveJointReferences(superModel);

    return ;
}

void C3DResourceLoader::loadSkeleton(C3DSprite* superModel,std::string baseBoneName)
{
    Reference* ref = seekToFirstType(BUNDLE_TYPE_SCENE);

    if (!ref)
    {
        return ;
    }

	// Read the number of children
    unsigned int childrenCount;
    if (!_stream->read(&childrenCount))
    {
        SAFE_RELEASE(superModel);
        return ;
    }

    if (childrenCount > 0)
    {
        C3DNode* node = this->loadNode(baseBoneName, superModel);
        if (node)
        {
			superModel->setSkeleton( static_cast<C3DBone*>(node) );
			superModel->addChild( node );
            node->release(); // scene now owns node
        }
    }

    return ;
}

bool C3DResourceLoader::loadAnimation(C3DSprite* superModel)
{
//    // parse animations
//    for (unsigned int i = 0; i < _referenceCount; ++i)
//    {
//        Reference* ref = &_references[i];
//        if (ref->type == BUNDLE_TYPE_ANIMATIONS)
//        {
//            // Found a match
//            if (fseek(_file, ref->offset, SEEK_SET) != 0)
//            {
//                LOG_ERROR_VARG("Failed to seek to object '%s' in bundle '%s'.", ref->id.c_str(), _path.c_str());
//                return ;
//            }
//			readAnimations(superModel);
//
//        }
//    }
//    return ;
    return loadAnimation2(superModel);
}

void C3DResourceLoader::reLoadSuperModel(C3DRenderNode* superModel)
{
	Reference* ref = seekToFirstType(BUNDLE_TYPE_SCENE);
    if (!ref)
    {
        return;
    }

    // Read the number of children
    unsigned int childrenCount;
    if (!_stream->read(&childrenCount))
    {
        return;
    }

	// Read each child directly into the scene
	for (unsigned int i = 0; i < childrenCount; ++i)
	{
		bool res = reloadNode(superModel);
		if(res == false)
		{
			WARN_VARG("reloadNode error,child index : %d",i);
		}
	}
}


class seekCheck
{
public:
	seekCheck(C3DResourceLoader* obj);
	~seekCheck();
private:
	C3DResourceLoader* _object;
};

seekCheck::seekCheck(C3DResourceLoader* obj):_object(obj)
{

}

seekCheck::~seekCheck()
{
	if(_object)
		_object->seekToNextType();
}

bool C3DResourceLoader::reloadNode(C3DNode* context)
{
	seekCheck	autoSeek(this);
    std::string nodeID(getIdFromOffset());

    // Read node type
    unsigned int eNodeType;
    if (!_stream->read(&eNodeType))
    {
        return false;
    }

	if(nodeID.empty())
	{
		WARN("reloadNode : nodeID is empty");
		return false;
	}

    C3DNode* curNode = context->findNode(nodeID, false);
	if(NULL==curNode)
		return false;

	// skip the transform
	_stream->seek(sizeof(float)*16, SEEK_CUR);

    // Skip over the parent ID.
    _stream->readString();

    // Read children
    unsigned int childrenCount;
    _stream->read(&childrenCount);

    if (childrenCount > 0)
    {
        for (unsigned int i = 0; i < childrenCount; ++i)
        {
            reloadNode(curNode);
        }
	}

	//--------------------------------------------------------------
	if(C3DNode::NodeType_Model == curNode->getType())
	{
		// Read model
		C3DModelNode* modelNode = static_cast<C3DModelNode*>(curNode);

		// reloadModel:-----------------------------------------------------------------
		unsigned char hasMesh;
		if (!_stream->read(&hasMesh))
		{
			LOG_ERROR_VARG("Failed to load hasMesh in bundle '%s'.", _path.c_str());
			return false;
		}

		// TODO: read morph
		unsigned char hasMorph;
		if (!_stream->read(&hasMorph))
		{
			LOG_ERROR_VARG("Failed to load hasMorph in bundle '%s'.", _path.c_str());
			return false;
		}

		unsigned char hasSkin;
		if (!_stream->read(&hasSkin))
		{
			LOG_ERROR_VARG("Failed to load hasSkin in bundle '%s'.", _path.c_str());
			return false;
		}

		unsigned char hasMaterial;
		if (!_stream->read(&hasMaterial))
		{
			LOG_ERROR_VARG("Failed to load hasMaterial in bundle '%s'.", _path.c_str());
			return false;
		}

		if(hasMesh)
		{
			// Read mesh
			//-----------------------------------------------------------------------------
			MeshData* meshData = readMeshData();
			if (meshData == NULL)
			{
				return false;
			}

			// Create C3DMesh
			C3DMesh* mesh = modelNode->getModel()->getMesh();
			if (mesh == NULL)
			{
				LOG_ERROR_VARG("Failed to create mesh: %s", nodeID.c_str());
				SAFE_DELETE_ARRAY(meshData);
				return false;
			}

			mesh->reload();

			mesh->_url = _path;
			mesh->_url += "#";
			mesh->_url += nodeID;
			mesh->_url += "_Mesh";

			mesh->init(meshData->vertexFormat, meshData->vertexCount, hasMorph);
			mesh->setVertexData(meshData->vertexData, 0, meshData->vertexCount);

			// Create mesh parts
			for (unsigned int i = 0; i < meshData->parts.size(); ++i)
			{
				MeshPartData* partData = meshData->parts[i];

				MeshPart* part = mesh->addPart(partData->primitiveType, partData->indexFormat, partData->indexCount, false);
				if (part == NULL)
				{
					LOG_ERROR_VARG("Failed to create mesh part (i=%d): %s", i, nodeID.c_str());
					SAFE_DELETE(meshData);
					return false;
				}
				part->setIndexData(partData->indexData, 0, partData->indexCount);
			}

			mesh->_boundingBox->set(meshData->boundingBox->_min,meshData->boundingBox->_max);
			
			SAFE_DELETE(meshData);
		}
	}
	return true;
}

void C3DResourceLoader::loadSuperModel(C3DSprite* superModel)
{
    clearLoadSession();

    Reference* ref = seekToFirstType(BUNDLE_TYPE_SCENE);

    if (!ref)
    {
        return ;
    }

    // Read the number of children
    unsigned int childrenCount;
    if (!_stream->read(&childrenCount))
    {
        SAFE_RELEASE(superModel);
        return ;
    }
    if (childrenCount > 0)
    {
        // Read each child directly into the scene
        for (unsigned int i = 0; i < childrenCount; i++)
        {
            C3DNode* node = readNode(superModel);

            if (node)
            {
				if(node->getType() == C3DNode::NodeType_Bone)
				{
					superModel->setSkeleton( static_cast<C3DBone*>(node) );
				}
				superModel->addChild( node);
                node->release(); // scene now owns node
            }
        }
    }

	loadAnimation(superModel);

    resolveJointReferences(superModel);

    return ;
}

void C3DResourceLoader::loadSceneModel(C3DStaticObj* sceneModel)
{
    Reference* ref = seekToFirstType(BUNDLE_TYPE_SCENE);

    if (!ref)
    {
        return ;
    }

    // Read the number of children
    unsigned int childrenCount;
    if (!_stream->read(&childrenCount))
    {
        SAFE_RELEASE(sceneModel);
        return ;
    }
    if (childrenCount > 0)
    {
        // Read each child directly into the scene
        for (unsigned int i = 0; i < childrenCount; i++)
        {
            C3DNode* node = readNode(sceneModel);

            if (node)
            {
				sceneModel->addChild( node);
                node->release(); // scene now owns node
            }
        }
    }

    return ;
}

C3DNode* C3DResourceLoader::loadNode(const std::string& id, C3DSprite* superModelContext)
{
    assert(!id.empty());

    C3DNode* node = NULL;

    // Search the passed in loading contexts (scene/node) first to see
    // if we've already loaded this node during this load session
    if (superModelContext)
    {
        node = superModelContext->findNode(id);
    }

    if (node == NULL)
    {
        // If not yet found, search the ref table and read
        Reference* ref = seekTo(id, BUNDLE_TYPE_NODE);
        if (ref == NULL)
        {
            return NULL;
        }

        node = readNode(superModelContext);
    }

    return node;
}

C3DNode* C3DResourceLoader::readNode(C3DRenderNode* compoundModelContext)
{
    std::string id = getIdFromOffset();

    // Read node type
    unsigned int nodeType;
    if (!_stream->read(&nodeType))
    {
        return NULL;
    }

    C3DNode* node = NULL;
	switch (nodeType)
    {
	case C3DNode::NodeType_Normal:
        node = C3DNode::create(id);
        break;
	case C3DNode::NodeType_Bone:
        node = C3DBone::create(id);
        break;
	case C3DNode::NodeType_Model:
        node = C3DModelNode::create(id);
        break;
	case C3DNode::NodeType_Camera:
        node = C3DCamera::create(id);
        break;
	case C3DNode::NodeType_Light:
        node = C3DLight::create(id);
        break;
    default:
        return NULL;
    }

    // Read transform
    float transform[16];
	if(_stream->read(transform, sizeof(float), 16) != 16)
    {
        SAFE_RELEASE(node);
        return NULL;
    }
    setTransform(transform, node);

    // Skip over the parent ID.
    _stream->readString();

    // Read children
    unsigned int childrenCount;
    if (!_stream->read(&childrenCount))
    {
        SAFE_RELEASE(node);
        return NULL;
    }
    if (childrenCount > 0)
    {
        // Read each child
        for (unsigned int i = 0; i < childrenCount; i++)
        {
            // Search the passed in loading contexts (scene/node) first to see
            // if we've already loaded this child node during this load session.
            C3DNode* child = NULL;
            id = getIdFromOffset();

            if (compoundModelContext)
            {
                child = compoundModelContext->findNode(id);
            }

            // If the child node wasn't already loaded, load it.
            if (!child)
                child = readNode(compoundModelContext);
            else
            {
                // Otherwise, skip over its data in the file.
                readNode(NULL);
            }

            if (child)
            {
                node->addChild(child);
                child->release(); // 'node' now owns this child
            }
        }
    }

	switch (nodeType)
    {
	case C3DNode::NodeType_Normal:
        break;
	case C3DNode::NodeType_Bone:
        break;
	case C3DNode::NodeType_Model:
		{
			// Read model
			C3DModel* model = readModel(node->getId());
			if (model)
			{
				static_cast<C3DModelNode*>(node)->setModel(model);
				SAFE_RELEASE(model);
			}
		}
        break;
	case C3DNode::NodeType_Camera:
		{
			// Read camera

			readCamera(static_cast<C3DCamera*>(node));
			//if (camera)
			{
				//static_cast<C3DCameraNode*>(node)->setCamera(camera);
				//SAFE_RELEASE(camera);
			}
		}
        break;
	case C3DNode::NodeType_Light:
		{
			// Read light
			readLight(static_cast<C3DLight*>(node));
			//if (light)
			{
				//static_cast<C3DLightNode*>(node)->setLight(light);
				//SAFE_RELEASE(light);
			}
		}

        break;
    default:
        return NULL;
    }
    return node;
}

void C3DResourceLoader::readCamera(C3DCamera* camera)
{
	if(camera == NULL)
		return;

    unsigned char cameraType;
    if (!_stream->read(&cameraType))
    {
        LOG_ERROR_VARG("Failed to load camera type in bundle '%s'.", _path.c_str());
    }

    if (cameraType == 0)
    {
        return ;
    }

    // aspect ratio
    float aspectRatio;
    if (!_stream->read(&aspectRatio))
    {
        LOG_ERROR_VARG("Failed to load camera aspectRatio in bundle '%s'.", _path.c_str());
    }

    // near plane
    float nearPlane;
    if (!_stream->read(&nearPlane))
    {
        LOG_ERROR_VARG("Failed to load camera near plane in bundle '%s'.", _path.c_str());
    }

    // far plane
    float farPlane;
    if (!_stream->read(&farPlane))
    {
        LOG_ERROR_VARG("Failed to load camera far plane in bundle '%s'.", _path.c_str());
    }

    if (cameraType == C3DCamera::PERSPECTIVE)
    {
        // field of view
        float fieldOfView;
        if (!_stream->read(&fieldOfView))
        {
            LOG_ERROR_VARG("Failed to load camera field of view in bundle '%s'.", _path.c_str());
        }
		camera->setPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
        //camera = C3DCamera::createPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    }
    else if (cameraType == C3DCamera::ORTHOGRAPHIC)
    {
        // magnification
        float zoomX;
        if (!_stream->read(&zoomX))
        {
            LOG_ERROR_VARG("Failed to load camera zoomX in bundle '%s'.", _path.c_str());
        }

        float zoomY;
        if (!_stream->read(&zoomY))
        {
            LOG_ERROR_VARG("Failed to load camera zoomY in bundle '%s'.", _path.c_str());
        }

		camera->setOrthographic(zoomX, zoomY, aspectRatio, nearPlane, farPlane);
        //camera = C3DCamera::createOrthographic(zoomX, zoomY, aspectRatio, nearPlane, farPlane);
    }
    else
    {
        LOG_ERROR_VARG("Failed to load camera type in bundle '%s'. Invalid camera type.", _path.c_str());
    }
}

void C3DResourceLoader::readLight(C3DLight* light)
{
    unsigned char type;
    if (!_stream->read(&type))
    {
        LOG_ERROR_VARG("Failed to load light %s in bundle '%s'.", "type", _path.c_str());
    }

    if (type == 0)
    {
        return;
    }

    // read color
    float red, blue, green;
    if (!_stream->read(&red) || !_stream->read(&blue) || !_stream->read(&green))
    {
        LOG_ERROR_VARG("Failed to load light %s in bundle '%s'.", "color", _path.c_str());
    }
    C3DVector3 color(red, blue, green);

    if (type == C3DLight::DIRECTIONAL)
    {
        light->setComponent(C3DDirectionalLight::create(color));
    }
    else if (type == C3DLight::POINT)
    {
        float range;
        if (!_stream->read(&range))
        {
            LOG_ERROR_VARG("Failed to load point light %s in bundle '%s'.", "point", _path.c_str());
        }
        light->setComponent(C3DPointLight::create(color, range));
    }
    else if (type == C3DLight::SPOT)
    {
        float range, innerAngle, outerAngle;
        if (!_stream->read(&range) || !_stream->read(&innerAngle) || !_stream->read(&outerAngle))
        {
            LOG_ERROR_VARG("Failed to load spot light %s in bundle '%s'.", "spot", _path.c_str());
        }
        light->setComponent(C3DSpotLight::create(color, range, innerAngle, outerAngle));
    }
    else
    {
        LOG_ERROR_VARG("Failed to load light %s in bundle '%s'.", "type", _path.c_str());
    }
}

C3DModel* C3DResourceLoader::readModel(const std::string& nodeId)
{
    unsigned char hasMesh;
    if (!_stream->read(&hasMesh))
    {
        LOG_ERROR_VARG("Failed to load hasMesh in bundle '%s'.", _path.c_str());
        return NULL;
    }

	//read morph
	unsigned char hasMorph;
	if (!_stream->read(&hasMorph))
	{
		LOG_ERROR_VARG("Failed to load hasMorph in bundle '%s'.", _path.c_str());
		return NULL;
	}

	unsigned char hasSkin;
    if (!_stream->read(&hasSkin))
    {
        LOG_ERROR_VARG("Failed to load hasSkin in bundle '%s'.", _path.c_str());
        return NULL;
    }

	unsigned char hasMaterial;
    if (!_stream->read(&hasMaterial))
    {
        LOG_ERROR_VARG("Failed to load hasMaterial in bundle '%s'.", _path.c_str());
        return NULL;
    }

	// Read skin
	C3DModel* model = NULL;
    if (hasSkin)
    {
		model = C3DSkinModel::create();
    }
	else
	{
		model = C3DSkinlessModel::create();
	}

    if(hasMesh)
	{
		// Read mesh
		C3DMesh* mesh = loadMesh(nodeId,hasMorph);
		if(mesh != NULL)
		{
			model->setMesh(mesh);
		}
		SAFE_RELEASE(mesh);
	}

	if (hasMorph)
	{
		C3DMorph* morph = readMeshMorph();
		if(morph != NULL)
		{
			model->setMorph(morph);
		}
	}

	// Read skin
    if (hasSkin)
    {
        C3DMeshSkin* skin = readMeshSkin();
        if (skin)
        {
            static_cast<C3DSkinModel*>(model)->setSkin(skin);
        }
    }

	std::string materialName;
    if (hasMaterial)
	{
		materialName = _stream->readString();
		model->setMaterialName(materialName);
	}

    return model;
}

C3DMeshSkin* C3DResourceLoader::readMeshSkin()
{
    C3DMeshSkin* meshSkin = new C3DMeshSkin();

    // Read bindShape
    float bindShape[16];
    if (!_stream->readMatrix(bindShape))
    {
        LOG_ERROR_VARG("Failed to load C3DMeshSkin in bundle '%s'.", _path.c_str());
        SAFE_DELETE(meshSkin);
        return NULL;
    }
    meshSkin->setBindShape(bindShape);

    MeshSkinData* skinData = new MeshSkinData();
    skinData->skin = meshSkin;

    // Read joint count
    unsigned int jointCount;
    if (!_stream->read(&jointCount))
    {
        LOG_ERROR_VARG("Failed to load C3DMeshSkin in bundle '%s'.", _path.c_str());
        SAFE_DELETE(meshSkin);
        SAFE_DELETE(skinData);
        return NULL;
    }
    if (jointCount == 0)
    {
        SAFE_DELETE(meshSkin);
        SAFE_DELETE(skinData);
        return NULL;
    }
    meshSkin->setJointCount(jointCount);

    // Read joint xref strings for all joints in the list
    for (unsigned int i = 0; i < jointCount; i++)
    {
        skinData->joints.push_back(_stream->readString());
    }

    // read bindposes
    unsigned int jointsBindPosesCount;
    if (!_stream->read(&jointsBindPosesCount))
    {
        LOG_ERROR_VARG("Failed to load C3DMeshSkin in bundle '%s'.", _path.c_str());
        SAFE_DELETE(meshSkin);
        SAFE_DELETE(skinData);
        return NULL;
    }
    if (jointsBindPosesCount > 0)
    {
        assert(jointCount * 16 == jointsBindPosesCount);
        float m[16];
        for (unsigned int i = 0; i < jointCount; i++)
        {
            if (!_stream->readMatrix(m))
            {
                LOG_ERROR_VARG("Failed to load C3DMeshSkin in bundle '%s'.", _path.c_str());
                SAFE_DELETE(meshSkin);
                SAFE_DELETE(skinData);
                return NULL;
            }
            skinData->inverseBindPoseMatrices.push_back(m);
        }
    }

	//.........
	// Read bone parts
    unsigned int bonePartCount;
    if (_stream->read(&bonePartCount, 4, 1) != 1)
    {
        SAFE_DELETE(skinData);
        return NULL;
    }
	if(bonePartCount > 0)
	{
        BonePartData* partData = new BonePartData();
		for (unsigned int i = 0; i < bonePartCount; ++i)
		{
			// Read primitive type, index format and index count
			unsigned int iByteCount;
			if (_stream->read(&partData->_batchID, 4, 1) != 1 ||
				_stream->read(&partData->_offsetVertexIndex, 4, 1) != 1 ||
				_stream->read(&partData->_numVertexIndex, 4, 1) != 1 ||
				_stream->read(&iByteCount, 4, 1) != 1)
			{
				SAFE_DELETE(skinData);
                SAFE_DELETE(partData);
				return NULL;
			}
			partData->indexCount = iByteCount / sizeof(unsigned int);

			partData->indexData = new unsigned char[iByteCount];
			if (_stream->read(partData->indexData, 1, iByteCount) != iByteCount)
			{
				SAFE_DELETE(skinData);
                SAFE_DELETE(partData);
				return NULL;
			}

            BonePart* part = meshSkin->addPart(partData->_batchID, partData->_offsetVertexIndex, partData->_numVertexIndex);
            if (part == NULL)
            {
            	LOG_ERROR_VARG("Failed to create bone part (i=%d):", i);
            	SAFE_DELETE(skinData);
                SAFE_DELETE(partData);
            	return NULL;
            }
            part->setIndexData(partData->indexData, partData->indexCount);
		}

        SAFE_DELETE(partData);
	}
	//............

    // Store the MeshSkinData so we can go back and resolve all joint references later
    _meshSkins->push_back(skinData);

    return meshSkin;
}

C3DMorph* C3DResourceLoader::readMeshMorph()
{
	C3DMorph* morph = new C3DMorph();
	std::string meshName = _stream->readString();

	unsigned int morphTargetCount;
	if (!_stream->read(&morphTargetCount))
	{
		SAFE_DELETE(morph);
		return NULL;
	}

	for (unsigned int i = 0; i < morphTargetCount; ++i)
	{
		MorphTarget* morphTarget = new MorphTarget();

		if (!_stream->read(&morphTarget->index))
		{
			SAFE_DELETE(morph);
			return NULL;
		}
		morphTarget->name = _stream->readString();
		unsigned int offsetCount;
		if (!_stream->read(&offsetCount))
		{
			SAFE_DELETE(morph);
			return NULL;
		}
		morphTarget->offsets.resize(offsetCount);
		for (unsigned int i = 0; i < offsetCount; ++i)
		{
			if (_stream->read(&morphTarget->offsets[i], 1, 16) != 16)
			{
				SAFE_DELETE(morphTarget);
				SAFE_DELETE(morph);
				return NULL;
			}
		}
		morph->addMorphTarget(morphTarget);
	}

	return morph;
}

void C3DResourceLoader::resolveJointReferences(C3DSprite* superModelContext)
{
    const unsigned int skinCount = _meshSkins->size();
    for (unsigned int i = 0; i < skinCount; ++i)
    {
        MeshSkinData* skinData = (*_meshSkins)[i];

        // Resolve all joints in skin joint list
        const unsigned int jointCount = skinData->joints.size();
        for (unsigned int j = 0; j < jointCount; ++j)
        {
            // TODO: Handle full xrefs (not just local # xrefs)
            std::string jointId = skinData->joints[j];
            if (jointId.length() > 1 && jointId[0] == '#')
            {
                jointId = jointId.substr(1, jointId.length() - 1);

                C3DNode* n = loadNode(jointId, superModelContext);
				if (n && n->getType() == C3DNode::NodeType_Bone)
                {
                    C3DBone* joint = static_cast<C3DBone*>(n);
                    joint->setInverseBindPose(skinData->inverseBindPoseMatrices[j]);
                    skinData->skin->setJoint(joint, j);
                }
            }
        }

        // Set the root joint
        if (jointCount > 0)
        {
            C3DBone* rootJoint = skinData->skin->getJoint((unsigned int)0);
            C3DNode* node = rootJoint;
            C3DNode* parent = node->getParent();

            while (true)
            {
				if (parent && parent->getType() == C3DNode::NodeType_Bone)
                {
					int jointIndex = skinData->skin->getJointIndex(static_cast<C3DBone*>(parent));
                    if ( jointIndex != -1 )
                    {
                        // Parent is a joint in the C3DMeshSkin, so treat it as the new root
                        rootJoint = static_cast<C3DBone*>(parent);
                    }

                    node = parent;
                    parent = node->getParent();
                }
                else
                {
                    std::string nodeID = node->getId();

                    while (true)
                    {
                        // Get the node's type.
                        Reference* ref = find(nodeID);
                        if (ref == NULL)
                        {
                            LOG_ERROR_VARG("No object with name '%s' in bundle '%s'.", nodeID.c_str(), _path.c_str());
                            break;
                        }

                        // Seek to the current node in the file so we can get it's parent ID.
                        seekTo(nodeID.c_str(), ref->type);

						// Skip over the node type (1 unsigned int) and transform (16 floats) and read the parent id.
                        if (_stream->seek(sizeof(unsigned int) + sizeof(float)*16, SEEK_CUR) == false)
                        {
                           // LOG_ERROR_VARG("Failed to skip over node type and transform for node '%s' in bundle '%s'.", nodeId.c_str(), _path.c_str());
                            return;
                        }

                        // Skip over the node type (1 unsigned int) and transform (16 floats) and read the parent id.
                    //    fseek(_file, sizeof(unsigned int) + sizeof(float)*16, SEEK_CUR);
                        std::string parentID = _stream->readString();

                        if (parentID.size() > 0)
                            nodeID = parentID;
                        else
                            break;
                    }

                    if (nodeID != rootJoint->getId())
                       loadNode(nodeID, superModelContext);

                    break;
                }
            }

            skinData->skin->setRootJoint(rootJoint);
        }

        // Done with this MeshSkinData entry
        SAFE_DELETE((*_meshSkins)[i]);
    }
    _meshSkins->clear();
}
void C3DResourceLoader::readAnimationChannelData(C3DAnimation* animation, const std::string& id, C3DBone* bone)
{
    // length of the arrays
    unsigned int keyTimesCount;
    unsigned int valuesCount;

    std::vector<unsigned long> keyTimes;
    std::vector<float> values;

    // read key times
    if (!_stream->readArray(&keyTimesCount, &keyTimes))
    {
        LOG_ERROR_VARG("Failed to read %s for %s: %s", "keyTimes", "animation", id.c_str());
        return ;
    }

    // read key values
    if (!_stream->readArray(&valuesCount, &values))
    {
        LOG_ERROR_VARG("Failed to read %s for %s: %s", "values", "animation", id.c_str());
        return ;
    }

    assert(keyTimes.size() > 0 && values.size() > 0);

    animation->createChannel(bone,  keyTimesCount, &keyTimes[0], &values[0]);
}

void C3DResourceLoader::readAnimationChannel(C3DSprite* superModel, C3DAnimation* animation, const std::string& animationId)
{
    const std::string& id = animationId;

    // read targetId
    std::string targetId = _stream->readString();
    if (targetId.empty())
    {
        LOG_ERROR_VARG("Failed to read %s for %s: %s", "targetId", "animation", id.c_str());
        return ;
    }

    C3DNode* targetNode = superModel->findNode(targetId.c_str());

    if (!targetNode)
    {
        LOG_ERROR_VARG("Failed to read %s for %s: %s", "animation target", targetId.c_str(), id.c_str());
        return ;
    }

	readAnimationChannelData(animation, animationId, static_cast<C3DBone*>(targetNode));
}

void C3DResourceLoader::readAnimation(C3DSprite* superModel)
{
    const std::string animationId = _stream->readString();

    // read the number of animation channels in this animation
    unsigned int animationChannelCount;
    if (!_stream->read(&animationChannelCount))
    {
        LOG_ERROR_VARG("Failed to read %s for %s: %s", "animationChannelCount", "animation", animationId.c_str());
        return;
    }

   C3DAnimation* animation = new C3DAnimation(animationId);

//	C3DAnimation* animation = NULL;
    for (unsigned int i = 0; i < animationChannelCount; i++)
    {
        readAnimationChannel(superModel, animation, animationId);
    }
	animation->release();
}

void C3DResourceLoader::readAnimations(C3DSprite* superModel)
{
    // read the number of animations in this object
    unsigned int animationCount;
    if (!_stream->read(&animationCount))
    {
        LOG_ERROR_VARG("Failed to read %s for %s", "animationCount", "Animations");
        return;
    }

    for (unsigned int i = 0; i < animationCount; i++)
    {
        readAnimation(superModel);
    }
}

C3DMesh* C3DResourceLoader::loadMesh(const std::string& nodeId,bool hasMorph)
{
    // Read mesh data
    MeshData* meshData = readMeshData();

    if (meshData == NULL)
    {
        return NULL;
    }

    // Create C3DMesh
    C3DMesh* mesh = NULL;
	if(hasMorph == true)
	{
		mesh = C3DMorphMesh::createMesh(meshData->vertexFormat, meshData->vertexCount, true);
	}
	else
	{
		mesh = C3DMesh::createMesh(meshData->vertexFormat, meshData->vertexCount, false);
	}

    if (mesh == NULL)
    {
        LOG_ERROR_VARG("Failed to create mesh: %s", nodeId.c_str());
        SAFE_DELETE_ARRAY(meshData);
        return NULL;
    }

    mesh->_url = _path;
    mesh->_url += "#";
    mesh->_url += nodeId;
	mesh->_url += "_Mesh";

    mesh->setVertexData(meshData->vertexData, 0, meshData->vertexCount);

    // Create mesh parts
    for (unsigned int i = 0; i < meshData->parts.size(); ++i)
    {
        MeshPartData* partData = meshData->parts[i];

        MeshPart* part = mesh->addPart(partData->primitiveType, partData->indexFormat, partData->indexCount, false);
        if (part == NULL)
        {
            LOG_ERROR_VARG("Failed to create mesh part (i=%d): %s", i, nodeId.c_str());
            SAFE_DELETE(meshData);
            return NULL;
        }
        part->setIndexData(partData->indexData, 0, partData->indexCount);
    }

	mesh->_boundingBox->set(meshData->boundingBox->_min,meshData->boundingBox->_max);

	SAFE_DELETE(meshData);

    return mesh;
}

MeshData* C3DResourceLoader::readMeshData()
{
    // Read vertex format/elements
    unsigned int C3DVertexElementCount;
    if (_stream->read(&C3DVertexElementCount, 4, 1) != 1 || C3DVertexElementCount < 1)
    {
        return NULL;
    }
    C3DVertexElement* C3DVertexElements = new C3DVertexElement[C3DVertexElementCount];
    for (unsigned int i = 0; i < C3DVertexElementCount; ++i)
    {
        unsigned int vUsage, vSize;
        if (_stream->read(&vUsage, 4, 1) != 1 || _stream->read(&vSize, 4, 1) != 1)
        {
            SAFE_DELETE_ARRAY(C3DVertexElements);
            return NULL;
        }

        C3DVertexElements[i].usage = (Vertex_Usage)vUsage;
        C3DVertexElements[i].size = vSize;
    }

    MeshData* meshData = new cocos3d::MeshData(C3DVertexElements, C3DVertexElementCount);

    SAFE_DELETE_ARRAY(C3DVertexElements);

    // Read vertex data
    unsigned int vertexByteCount;
    if (_stream->read(&vertexByteCount, 4, 1) != 1 || vertexByteCount == 0)
    {
        SAFE_DELETE(meshData);
        return NULL;
    }
    meshData->vertexCount = vertexByteCount / meshData->vertexFormat->getVertexSize();
    meshData->vertexData = new unsigned char[vertexByteCount];
    if (_stream->read(meshData->vertexData, 1, vertexByteCount) != vertexByteCount)
    {
        SAFE_DELETE(meshData);
        return NULL;
    }

    // Read mesh parts
    unsigned int meshPartCount;
    if (_stream->read(&meshPartCount, 4, 1) != 1)
    {
        SAFE_DELETE(meshData);
        return NULL;
    }
    for (unsigned int i = 0; i < meshPartCount; ++i)
    {
        // Read primitive type, index format and index count
        unsigned int pType, iFormat, iByteCount;
        if (_stream->read(&pType, 4, 1) != 1 ||
            _stream->read(&iFormat, 4, 1) != 1 ||
            _stream->read(&iByteCount, 4, 1) != 1)
        {
            SAFE_DELETE(meshData);
            return NULL;
        }

        MeshPartData* partData = new MeshPartData();
        meshData->parts.push_back(partData);

        partData->primitiveType = (PrimitiveType)pType;
        partData->indexFormat = (IndexFormat)iFormat;

        unsigned int indexSize = 0;
        switch (partData->indexFormat)
        {
        case IndexFormat_INDEX8:
            indexSize = 1;
            break;
        case IndexFormat_INDEX16:
            indexSize = 2;
            break;
        case IndexFormat_INDEX32:
            indexSize = 4;
            break;
        }

        partData->indexCount = iByteCount / indexSize;

        partData->indexData = new unsigned char[iByteCount];
        if (_stream->read(partData->indexData, 1, iByteCount) != iByteCount)
        {
            SAFE_DELETE(meshData);
            return NULL;
        }
    }

	// Read mesh bounds (bounding box and bounding sphere)
    if (_stream->read(&meshData->boundingBox->_min.x, 4, 3) != 3 || _stream->read(&meshData->boundingBox->_max.x, 4, 3) != 3)
    {
        SAFE_DELETE(meshData);
        return NULL;
    }

    return meshData;
}

void C3DResourceLoader::setTransform(const float* values, C3DTransform* transform)
{
    // Load array into transform
    C3DMatrix matrix(values);

    C3DVector3 scale, translation;
    C3DQuaternion rotation;
    matrix.decompose(&scale, &rotation, &translation);
    transform->setScale(scale);
    transform->setPosition(translation);
    transform->setRotation(rotation);
}

bool C3DResourceLoader::contains(const std::string& id) const
{
    return (find(id) != NULL);
}

unsigned int C3DResourceLoader::getObjectCount() const
{
    return _referenceCount;
}

const std::string C3DResourceLoader::getObjectID(unsigned int index) const
{
    return (index >= _referenceCount ? "" : _references[index].id);
}

C3DResourceLoader::Reference::Reference()
    : type(0), offset(0)
{
}

C3DResourceLoader::Reference::~Reference()
{
}

bool C3DResourceLoader::loadAnimation2(C3DSprite* superModel)
{
    const std::string& animationpath = _path;

    bool bHasAnimation = false;

    bool bHasLoad = isAnimationLoaded();
    if (!bHasLoad)
    {
        // parse animations
        for (unsigned int i = 0; i < _referenceCount; ++i)
        {
            Reference* ref = &_references[i];
            if (ref->type == BUNDLE_TYPE_ANIMATIONS)
            {
				bHasAnimation = true;
                // Found a match
                if (_stream->seek(ref->offset, SEEK_SET) == false)
                {
                    LOG_ERROR_VARG("Failed to seek to object '%s' in bundle '%s'.", ref->id.c_str(), _path.c_str());
                    return false ;
                }
                
                bool bRet = readAnimationCurves();
                if (!bRet)
                {
                    //LOG_ERROR_VARG("Failed to seek to object animation curves in bundle '%s'.",  _path.c_str());
                    return false;
                }
            }
        }
    }
	else
	{
		bHasAnimation = true;
	}

	if(bHasAnimation == false)
		return false;

	SAFE_RELEASE(superModel->_animation);
	superModel->_animation = C3DAnimation::create("movements");

    // assign animation data
    C3DAnimationCurveMgr* mgr = C3DAnimationCurveMgr::sharedAnimationCurveMgr();
    C3DAnimationCurveMgr::CurveMap* curvemap = mgr->getAnimationCurves(animationpath);
	
    unsigned int nFrame = 0;
	if (curvemap)
	{
		for (C3DAnimationCurveMgr::CurveMap::iterator it = curvemap->begin(); it != curvemap->end(); it++)
		{
			std::string targetId = it->first;
			C3DAnimationCurve* curve = it->second;

			C3DNode* targetNode = superModel->findNode(targetId);

			float perFrameTime = 1000 / 30.f;// 30 is the 3dMax default frame rate
			unsigned int nFrameCount = curve->getDruationTime() / perFrameTime + 0.5;
			if (nFrameCount > nFrame)
				nFrame = nFrameCount;

			superModel->_animation->createChannel(static_cast<C3DBone*>(targetNode),  curve);
		}
	}
    
    superModel->_animation->setFrameCount(nFrame);
	return true;
}

bool C3DResourceLoader::isAnimationLoaded() const
{
    const std::string& animationpath = _path;
    C3DAnimationCurveMgr* mgr = C3DAnimationCurveMgr::sharedAnimationCurveMgr();
    C3DAnimationCurveMgr::CurveMap* curvemap = mgr->getAnimationCurves(animationpath);
    if (curvemap)
        return true;// already load

    return false;
}

bool C3DResourceLoader::readAnimationCurves()
{
	// caller should guarantee this
	assert(!isAnimationLoaded());

    //create animation curve
	C3DAnimationCurveMgr* mgr = C3DAnimationCurveMgr::sharedAnimationCurveMgr();
	C3DAnimationCurveMgr::CurveMap* curvemap = mgr->createAnimationCurves(_path);

    unsigned int animationCount;
    if (!_stream->read(&animationCount))
    {
        LOG_ERROR_VARG("Failed to read %s for %s", "animationCount", "Animations");
        return false;
    }

    for (unsigned int j = 0; j < animationCount; j++)
    {
        const std::string animationId = _stream->readString();

        // read the number of animation channels in this animation
        unsigned int animationChannelCount;
        if (!_stream->read(&animationChannelCount))
        {
            LOG_ERROR_VARG("Failed to read %s for %s: %s", "animationChannelCount", "animation", animationId.c_str());
            return false;
        }

		if(animationChannelCount == 0)
		{
			return false;
		}

        for (unsigned int i = 0; i < animationChannelCount; i++)
        {
            // read targetId
            std::string targetId = _stream->readString();
            if (targetId.empty())
            {
                LOG_ERROR_VARG("Failed to read %s for %s: %s", "animation", "targetId", targetId.c_str());
                return false;
            }
            // length of the arrays
            unsigned int keyTimesCount;
            unsigned int valuesCount;

            std::vector<unsigned long> keyTimes;
            std::vector<float> values;

            // read key times
            if (!_stream->readArray(&keyTimesCount, &keyTimes))
            {
                LOG_ERROR_VARG("Failed to read %s for %s: %s", "keyTimes", "animation", targetId.c_str());
                return false;
            }

            // read key values
            if (!_stream->readArray(&valuesCount, &values))
            {
                LOG_ERROR_VARG("Failed to read %s for %s: %s", "values", "animation", targetId.c_str());
                return false;
            }

            assert(keyTimes.size() > 0 && values.size() > 0);

            curvemap->insert(std::pair<std::string, C3DAnimationCurve*>(targetId, C3DAnimationCurveMgr::createAniamationCurve(keyTimesCount, &keyTimes[0], &values[0]) ) );
        }
    }

    return true;
}
}