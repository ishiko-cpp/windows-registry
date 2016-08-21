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

#ifndef _ISHIKO_WINDOWSREGISTRY_KEYPATH_H_
#define _ISHIKO_WINDOWSREGISTRY_KEYPATH_H_

#include <Windows.h>
#include <string>

namespace Ishiko
{
namespace WindowsRegistry
{

class KeyPath
{
public:
	explicit KeyPath(HKEY key);
	explicit KeyPath(const std::string& path);
	KeyPath(const KeyPath& keyPath, const std::string& path);
	KeyPath(const KeyPath& other);
	~KeyPath();

	void appendPath(const std::string& path);

	bool operator ==(const std::string& other) const;
	bool operator !=(const std::string& other) const;

	KeyPath& operator =(const std::string& other);

	const std::string& str() const;

	// Whether the key is one of the predefined keys:
	// (HKEY_CLASSES_ROOT, HKEY_CURRENT_CONFIG, HKEY_CURRENT_USER,
	// HKEY_LOCAL_MACHINE, HKEY_PERFORMANCE_DATA, HKEY_PERFORMANCE_NLSTEXT,
	// HKEY_PERFORMANCE_TEXT, HKEY_USERS)
	bool isPredefinedKey() const;

	void splitInHiveAndSubKey(HKEY& hive, std::string& subKeyPath) const;

private:
	static HKEY getHive(const std::string& path);
	static std::string getPathFromPredefinedKey(HKEY key);

private:
	std::string m_path;
};

}
}

#endif
