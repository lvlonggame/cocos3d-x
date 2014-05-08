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

#ifndef DEVICEADAPTER_H_
#define DEVICEADAPTER_H_

#include "Base.h"
#include "CCPlatformConfig.h"
#include "CCConfiguration.h"

#include "cocos2d.h"

namespace cocos3d
{


class C3DDeviceAdapter : public cocos2d::CCObject
{
public:
	enum DeviceLevel
    {
		Unknow = 0,
        Low, //one cpu
		Mid, //two cpu
        High, // four cpu
    };
public:
    
	 C3DDeviceAdapter()
	 {
		 _cpuCount = 1;
         _cpuFrequency = 0;
         _platformName = "unknown";
		 _deviceLevel = DeviceLevel::Low;
		 _supportVAO = false;

		 checkCpuInfo();
		 checkNeon();
		 checkDevice();
		 checkVAO();
		 checkPostProcess();
		 checkShadow();
	 }

    ~C3DDeviceAdapter()
    {
 
        _deviceAdapterInstance = NULL;
    }
    

	static C3DDeviceAdapter* getInstance();
	
    void checkCpuInfo();

	void checkVAO();
	
	void checkNeon();

	void checkPostProcess();
	void checkShadow();

	void checkDevice();
	
	unsigned int getCpuCount()
	{
		return _cpuCount;
	}
    
    unsigned int getCpuFrequency()
    {
        return _cpuFrequency;
    }
    
    std::string getPlatformName()
    {
        return _platformName;
    }

	DeviceLevel getDeviceLevel()
	{
		return _deviceLevel;
	}

	bool isSuppoetNeon()
	{
		return _supportNeon;
	}

	
	bool isSupportVAO()
	{
		return _supportVAO;
	}

	void setSupportShadow(bool support)
	{
		_supportShadow = support;
	}
	bool isSupportShadow()
	{
		return _supportShadow;
	}

	void setSupportPostProcess(bool support)
	{
		_supportPostProcess = support;
	}

	bool isSupportPostProcess()
	{
		return _supportPostProcess;
	}
	

private:

	static C3DDeviceAdapter* _deviceAdapterInstance;
	unsigned int _cpuCount;
    unsigned int _cpuFrequency;
    std::string _platformName;
	DeviceLevel _deviceLevel;
	bool _supportVAO;
	bool _supportPostProcess;
	bool _supportShadow;
	bool _supportNeon;

};
}


#endif
