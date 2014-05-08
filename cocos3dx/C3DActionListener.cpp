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

#include "C3DActionListener.h"

namespace cocos3d
{
C3DActionListener::C3DActionListener(): _object(NULL),_function(NULL)
{
}

C3DActionListener::C3DActionListener(const C3DActionListener& actionListener)
{
	_object = actionListener._object;
	_function = actionListener._function;
}

C3DActionListener::~C3DActionListener()
{
	_object = NULL;
	_function = NULL;
}

C3DActionListener * C3DActionListener::create(ListenerObject* object, ListenerFunction function)
{
    C3DActionListener *res = new C3DActionListener();

	res->_object = object;

	res->_function = function;

	return res;
}

void C3DActionListener::action()
{
    if (_function)
	{
        (_object->*_function)();
    }
}

C3DActionEvent::C3DActionEvent(C3DActionListener* listener, unsigned long eventTime)
{
    _listener = listener;
    _eventTime = eventTime;

	_finished = false;
}

C3DActionEvent::C3DActionEvent(const C3DActionEvent& actionEvent)
{
	_finished = actionEvent._finished;

	_listener = new C3DActionListener(*actionEvent._listener);

	_eventTime = actionEvent._eventTime;
}

C3DActionEvent::~C3DActionEvent()
{
	delete _listener;
	_listener = NULL;
}
}