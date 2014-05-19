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

#ifndef C3DSTAT_H_
#define C3DSTAT_H_

#include "cocos3d.h"

#include "cocos2d.h"

namespace cocos3d
{
    /**
     *  class for statistic the 3D scene
	 *  stat the total triangles, drawing triangles, and draw calls
     */
    class C3DStat
    {
    public:
	/**
     * Destructor
     */
        ~C3DStat();

		/**
         * get singleton
         */
        static C3DStat* getInstance();

		static void destroyInstance();

		/**
         * begin & end stat
         */
        void beginStat();
        void endStat();

		/**
         * add draw triangles
         */
        void incTriangleDraw(int nTriangle){ if (_bStart) _nTriangleDraw += nTriangle; }

		/**
         * add total triangles
         */
        void incTriangleTotal(int nTriangle){ if (_bStart) _nTriangleTotal += nTriangle; }

		/**
         * add draw calls
         */
        void incDrawCall(int nDrawCall) { if (_bStart) _nDrawCall += nDrawCall; }

		/**
         * get & set stat enable
         */
        void setStatEnable(bool bEnable);
        bool isStatEnable() const { return _bEnable; }

		/**
         * get drawing triangles
         */
        int getTriangleDraw() const { return _nTriangleDraw; }
		/**
         * get total triangles
         */
        int getTriangleTotal() const { return _nTriangleTotal; }
		/**
         * get draw calls
         */
        int getDrawCall() const { return _nDrawCall; }

    protected:
		/**
         * Constructor
         */
        C3DStat();

		// properties

        int _nTriangleDraw; // triangle rendered (total triangle substract those culled by camera frustum)

        int _nTriangleTotal; // total triangle in the scene

        int _nDrawCall;

        bool _bStart; // start stat

        bool _bEnable; // enable stat or not
    };


	class C3DStatRender
	{
	public:
		C3DStatRender(cocos2d::Node* parent, float statfont = 10.f);
		~C3DStatRender();

		void setUpdateInterval(long interval) { _UpdateInterval = interval; }
		long getUpdateInterval() const { return _UpdateInterval; }

		void setStatFont(float fontsize);

		void setStatLabelPos(const cocos2d::Point& pt);

        void update(long elapsedTime); //update label string

	private:

		long _UpdateInterval; // update show stat label every _UpdateInterval ms

		long _UpdateIntervalAcc; // accumlate of deltaTime of update

		cocos2d::LabelTTF* _TriangleDrawLabel;
		cocos2d::LabelTTF* _TriangleTotalLabel;
		cocos2d::LabelTTF* _DrawCallLabel;
		float _fontSize;

		cocos2d::Node* _parent;
	};

#ifdef ENABLE_C3D_PROFILE
#define STAT_BEGIN()\
	C3DStat::getInstance()->beginStat();

#define STAT_END()\
	C3DStat::getInstance()->endStat();

#define STAT_INC_TRIANGLE_TOTAL(val)\
	if (C3DStat::getInstance()->isStatEnable())\
	{\
		C3DStat::getInstance()->incTriangleTotal(val);\
	}

#define STAT_INC_TRIANGLE_DRAW(val)\
	if (C3DStat::getInstance()->isStatEnable())\
	{\
	C3DStat::getInstance()->incTriangleDraw(val);\
	}

#define STAT_INC_DRAW_CALL(val)\
	if (C3DStat::getInstance()->isStatEnable())\
	{\
	C3DStat::getInstance()->incDrawCall(val);\
	}
#else
#define STAT_BEGIN()
#define STAT_END()

#define STAT_INC_TRIANGLE_TOTAL(val)
#define STAT_INC_TRIANGLE_DRAW(val)
#define STAT_INC_DRAW_CALL(val)
#endif
}

#endif
