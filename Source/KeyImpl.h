/*
	Copyright (c) 2015 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OROTHER DEALINGS
	IN THE SOFTWARE.
*/

#ifndef _ISHIKO_WINDOWSREGISTRY_KEYIMPL_H_
#define _ISHIKO_WINDOWSREGISTRY_KEYIMPL_H_

#include "KeyPath.h"
#include "Key.h"

namespace Ishiko
{
namespace WindowsRegistry
{

class KeyImpl
{
public:
	KeyImpl(const KeyPath& keyPath, bool create);
	KeyImpl(Key& key, const std::string& subKeyPath, bool create);
	KeyImpl(HKEY hiveKey, const std::string& subKeyPath, bool create);
	~KeyImpl();

	void enumValues(std::vector<std::string>& valueNames);
	std::string getValueAsString(const std::string& valueName) const;
	void setValue(const std::string& valueName, const std::string& valueData);
	void deleteValue(const std::string& valueName);

	HKEY key();
	const KeyPath& path() const;

private:
	static void open(HKEY key, const std::string subKeyPath, bool create,
		REGSAM accessRights, const KeyPath& keyPath, HKEY& resultKey, 
		REGSAM& resultAccessRights);
	void requireAccessRights(REGSAM accessRights);

private:
	HKEY m_key;
	// The access rights the key has been opened with
	REGSAM m_accessRights;
	// The path of the key in the registry. There 
	// is no API to retrieve the name of a key
	// from a key handle so we need to keep track
	// of the path.
	KeyPath m_path;
};

}
}

#endif
