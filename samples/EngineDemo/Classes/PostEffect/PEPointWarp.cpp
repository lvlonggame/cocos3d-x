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

#include "PEPointWarp.h"
#include "C3DPostProcess.h"
#include "C3DMaterial.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "C3DFrameBuffer.h"
#include "C3DTexture.h"
#include "C3DDepthStencilTarget.h"
#include "C3DSampler.h"
#include "MaterialParameter.h"
#include "C3DRenderTarget.h"
#include "C3DModel.h"
#include "C3DRenderSystem.h"

namespace cocos3d
{
PEPointWarp::PEPointWarp(C3DPostProcess* postProcess, const std::string& name)
	: C3DPostEffect( postProcess, name )
	, _speed( 0.5f )
	, _maxRadius( 0.4f )
	, _paramClicks( NULL )
{
	for ( unsigned int i = 0; i < MAX_CLICKS; ++i )
	{
		resetClick( &(_clicks[i]) );
	}
}

C3DPostEffect* PEPointWarp::create( const std::string& name, const std::string& materialName, C3DPostProcess* postProcess )
{
	C3DPostEffect* pe = new PEPointWarp( postProcess, name );
	bool bInit = pe->init( materialName );
	if (!bInit)
	{
		SAFE_RELEASE(pe);
	}
	return pe;
}

void PEPointWarp::resetClick( C3DVector4* click )
{
	click->x = 0.0;
	click->y = 0.0;
	click->z = -1.0;
	click->w = _maxRadius;
}

PEPointWarp::~PEPointWarp(void)
{
}

bool PEPointWarp::init(const std::string& szMaterial)
{
	if ( !C3DPostEffect::init(szMaterial) )
	{
		return false;
	}

	C3DTechnique* tech = _material->getTechnique(0u);
	if ( tech == NULL )
	{
		return false;
	}

	C3DPass* pass = tech->getPass(0u);
	if ( pass == NULL )
	{
		return false;
	}

	_paramClicks = pass->getParameter( "u_clicks" );

	return true;
}

void PEPointWarp::setShaderParameter()
{
	if ( _paramClicks != NULL )
	{
		_paramClicks->setValue( &(_clicks[0]), MAX_CLICKS );
	}
}

void PEPointWarp::update( float dt )
{
	for ( int i = 0; i < MAX_CLICKS; ++i )
	{
		if ( _clicks[i].z >= _maxRadius || _clicks[i].z < 0.0 )
		{
			resetClick( &(_clicks[i]) );
		}
		else
		{
			_clicks[i].z += dt*_speed;
		}
	}
}

C3DVector4* PEPointWarp::getEmptyClick(void)
{
	C3DVector4* eldset = &(_clicks[0]);
	for ( unsigned int i = 0; i < MAX_CLICKS; ++i )
	{
		if ( _clicks[i].z < 0 )
		{
			eldset = &(_clicks[i]);
			break;
		}
		else
		{
			if ( eldset->z < _clicks[i].z )
			{
				eldset = &(_clicks[i]);
			}
		}
	}

	return eldset;
}

void PEPointWarp::addClick( float x, float y )
{
	C3DVector4* clicks = getEmptyClick();

	clicks->x = x;
	clicks->y = y;
	clicks->z = 0;
	clicks->w = _maxRadius;
}
}	//namespace cocos3d