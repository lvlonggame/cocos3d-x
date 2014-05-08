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

#include "CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "Base.h"
#include "C3DDeviceAdapter.h"

namespace cocos3d
{

C3DDeviceAdapter* C3DDeviceAdapter::_deviceAdapterInstance = NULL;


C3DDeviceAdapter* C3DDeviceAdapter::getInstance()
{
	if ( _deviceAdapterInstance == NULL )
	{
		_deviceAdapterInstance = new C3DDeviceAdapter();
		_deviceAdapterInstance->autorelease();
	}
	return _deviceAdapterInstance;
}

void C3DDeviceAdapter::checkCpuInfo()
{
	_cpuCount = 4;

    WARN_VARG("default set the cpu counter of pc is : %d", _cpuCount);

}

void C3DDeviceAdapter::checkNeon()
{
	_supportNeon = false;
}

void C3DDeviceAdapter::checkVAO()
{
	

	if(_deviceLevel == DeviceLevel::High)
	{
		_supportVAO = cocos2d::Configuration::getInstance()->checkForGLExtension("vertex_array_object");
	}
	else
		_supportVAO = false;

	WARN_VARG("the gpu support VAO : %d",_supportVAO);
}

void C3DDeviceAdapter::checkDevice()
{
	if(_cpuCount == 1)
		_deviceLevel = DeviceLevel::Low;
	else if(_cpuCount == 2)
		_deviceLevel = DeviceLevel::Mid;
	else if(_cpuCount >= 4)
		_deviceLevel = DeviceLevel::High;
	else
		_deviceLevel = DeviceLevel::Unknow;

	WARN_VARG("the devicelevel is : %d",(int)_deviceLevel);
}

void C3DDeviceAdapter::checkShadow()
{
	_supportShadow = true;
}

void C3DDeviceAdapter::checkPostProcess()
{

	_supportPostProcess = true;
}







}

#endif