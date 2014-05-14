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

#ifndef ACTIONLISTENER_H_
#define ACTIONLISTENER_H_

#include <vector>
#include "stdlib.h"

namespace cocos3d
{
class C3DAnimation;
class AnimationValue;

/**
 * The runtime interface to represent an Object Listener.
 */
class ListenerObject
{
};

typedef void (ListenerObject::*ListenerFunction)();

/**
* Interface for listening to Action events.
*/
class  C3DActionListener
{
public:
	/**
     * Constructor.
     */
    C3DActionListener();

	/**
     * Constructor.
     */
	C3DActionListener(const C3DActionListener& actionListener);

	/**
     * Destructor.
     */
    virtual ~C3DActionListener();

    /**
    * The method for creating C3DActionListener.
    */
    static C3DActionListener * create(ListenerObject* object, ListenerFunction function);

	/**
    * Do the listener's action.
    */
    void action();

	/**
    * Get the callback function.
    */
    ListenerObject* getTargetCallback()
    {
        return _object;
    }

	/**
    * Set the callback function.
    */
    void setTargetCallback(ListenerObject* object)
    {
		_object = object;
    }

protected:
   ListenerObject*   _object;
   ListenerFunction  _function;
};

/**
 * Defines a class for Action Event
 */
class C3DActionEvent
{
public:
	/**
     * Constructor.
     */
    C3DActionEvent(C3DActionListener* listener, unsigned long eventTime);

	/**
     * Constructor.
     */
	C3DActionEvent(const C3DActionEvent& actionEvent);

	/**
     * Destructor.
     */
    ~C3DActionEvent();

	bool _finished;
    C3DActionListener* _listener;        // This listener to call back when this event is triggered.
    unsigned long _eventTime;   // The time at which the listener will be called back at during the playback of the AnimationClip.
};
}
#endif
