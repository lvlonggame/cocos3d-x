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

#ifndef STRINGTOOL_H_
#define STRINGTOOL_H_

#include <cctype>
#include <string>
#include <vector>
#include <sstream>

namespace cocos3d
{
/**
 * StringTool is an interface for the string operating.
 */
class StringTool
{
public:

	/**
     * Constructor.
     */
	 StringTool();

	 /**
     * Destructor.
     */
    ~StringTool();

	/**
     * Splits string by given string.
     */
	static std::vector<std::string> StringSplitByString(const std::string &str, const std::string &strKey, int IgnoreCase = true);

	/**
     * Splits string by given char.
     */
	static std::vector<std::string> StringSplitByChar(const std::string &str, char cKey, int IgnoreCase = true);

	/**
     * get file by given file path.
     */
	static std::string getFileName(const std::string& filepath);

	/**
     * get file by given file path.
     */
	static std::string getFileName(const std::string& filepath,const std::string& expName);

	/**
     * get file by given file path.
     */
	static std::string getFilePath(const std::string& filename);

	/**
    * convert string and other type
	*/
    template<typename T>
    static std::string toString(const T& x);

	/**
    * convert other type from string
	*/
    template<typename T>
    static void fromString(const std::string& str, T& x);

    static std::string toString(bool b);
    static void fromString(const std::string& str, bool& b);

public:

};

/**
* convert to string from other type
*/
template<typename T>
inline std::string StringTool::toString(const T& x)
{
    std::ostringstream stream;
    stream << x;
    return stream.str();
}

/**
* convert to other type from string
*/
template<typename T>
inline void StringTool::fromString(const std::string& str, T& x)
{
    std::istringstream stream(str);
    stream >> x;
}
}

#endif
