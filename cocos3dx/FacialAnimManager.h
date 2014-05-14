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

#ifndef SHEETANIMMANAGER_H_
#define SHEETANIMMANAGER_H_

#include <map>
#include <list>

using namespace std;
namespace cocos3d
{
/**
 * Defines structure to describe runtime expression.
 */
struct Expression
{
	string name;
	int frameNum;
	string frameSerials;
};

/**
 * Defines structure to describe facial.
 */
class  FacialComponent
{
private:
	string name;
	std::map<std::string,Expression*>* _expressions;
};

class SheetAnimation;

/**
 * Defines structure to Manage facial animation.
 */
class FacialAnimManager
{
public:
	FacialAnimManager();
	~FacialAnimManager();

	void update(long elapsedTime);

	/**
	* Add TextureAnimation to Manager.
	*/
	void addTextureAnim(string partName,string typeName,int frameNum,string frameSerial);

	/**
	* Add UVAnimation to Manager.
	*/
	void addUVAnim(string partName,string typeName,int tileX,int tileY,int frameNum,string frameSerial);

	/**
	* Sets target animation material.
	*/
	bool setAnim(string partName,string typeName,C3DMaterial *mat);

private:
	typedef pair <string, list<SheetAnimation*>*> map_pair;
	typedef map<string,list<SheetAnimation*>*>::iterator map_iter;
	typedef list<SheetAnimation*>::iterator list_iter;
	map<string,list<SheetAnimation*>*>* _anims;
};
}

#endif
