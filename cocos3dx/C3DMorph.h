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

#ifndef MORPH_H_
#define MORPH_H_

#include <string>
#include <vector>
using namespace std;

namespace cocos3d
{
/**
 * Defines structure to describe vertex offset.
 */
struct VertexOffset
{
	unsigned int index;
	float x,y,z;

	VertexOffset(){};
};

/**
 * Defines structure to describe target morph.
 */
struct MorphTarget
{
	unsigned int index;
	float weight;
	std::string name;
	std::vector<VertexOffset> offsets;

	/**
     * Constructor.
     */
	MorphTarget()
	{
		weight = 1.0f;
	}

	/**
     * Destructor.
     */
	~MorphTarget()
	{
	}
};

/**
 * Defines structure to describe morph.
 */
class C3DMorph
{
public:
	/**
     * Constructor.
     */
    C3DMorph();

	/**
     * Destructor.
     */
    ~C3DMorph();

	/**
     * Gets target morph by specified name.
     */
	MorphTarget* getMorphTarget(std::string name);

	/**
     * Gets target morph by specified index.
     */
	MorphTarget* getMorphTarget(int index);

	/**
     * Adds a target morph.
     */
	void addMorphTarget(MorphTarget* target);

	/**
     * Clears current target vector list.
     */
	void clearCurTarget();

	/**
     * Gets current target vector list.
     */
	std::vector<unsigned int>* getCurTargets();

	/**
     * Push target index to current target vector list.
     */
	bool pushTarget(unsigned int targetIndex);

	/**
     * Pop target index to current target vector list.
     */
	bool popTarget(unsigned int targetIndex);

private:
	std::string _meshName;
	std::vector<MorphTarget*>* _morphTargets;

	std::vector<unsigned int>* _curTargets;
};
}

#endif
