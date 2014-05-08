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

#ifndef C3DPROFILE_H_
#define C3DPROFILE_H_
#include <limits.h>
#include "cocos3d.h"

#include "cocos2d.h"

#define ENABLE_C3D_PROFILE

namespace cocos3d
{
    /**
     *  class for performance profile
	 *
     */
    class C3DProfile
    {
        friend class C3DProfileDisplay;

        struct ProfileItem
        {
            std::string _name;
            int _accTime; // accumulate time during frame
            int _durTime; //time current frame
            int _avgTime; // average time
            int _startTime;

            int minTime;
            int maxTime;
            int totalTime; // total time
            int numberOfCalls;
            ProfileItem():_name("")
            {
                reset();
            }
            void reset()
            {
                _startTime = 0;
                _accTime = 0;
                _durTime = 0;
                minTime = INT_MAX;
                maxTime = 0;
                totalTime = 0;
                _avgTime = 0;
                numberOfCalls = 0;
            }
        };
    public:
	/**
     * Destructor
     */
        ~C3DProfile();

		/**
         * get singleton
         */
        static C3DProfile* getInstance();

		/**
         * begin & end profile
         */
        void beginProfile(const std::string& itemname);
        void endProfile(const std::string& itemname);

        void removeAllProfile();

        void update();

    protected:
		/**
         * Constructor
         */
        C3DProfile();

		std::map<std::string, ProfileItem*> _profileItems;
    };

    /**
     *  class for performance profile display
	 *
     */
	class C3DProfileDisplay
	{
	public:
		C3DProfileDisplay();
		~C3DProfileDisplay();

        /**
         * get singleton
         */
        static C3DProfileDisplay* getInstance();

		void setLabelBMPFont(cocos2d::CCLabelBMFont* label);

		/**
         * update label string
		 */
        void update();

	private:

		cocos2d::CCLabelBMFont* _label;
	};
}

#ifdef ENABLE_C3D_PROFILE
#define BEGIN_PROFILE(name) C3DProfile::getInstance()->beginProfile(name)
#define END_PROFILE(name) C3DProfile::getInstance()->endProfile(name)
#define PROFILE_UPDATE() C3DProfile::getInstance()->update()
#define SET_PROFILE_DISPLAY(label) C3DProfileDisplay::getInstance()->setLabelBMPFont(label)
#define PROFILE_DISPLAY_UPDATE() C3DProfileDisplay::getInstance()->update()
#else
#define BEGIN_PROFILE(name)
#define END_PROFILE(name)
#define PROFILE_UPDATE()
#define SET_PROFILE_DISPLAY(label)
#define PROFILE_DISPLAY_UPDATE()
#endif

#endif
