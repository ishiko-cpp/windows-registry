/*
	Copyright (c) 2015-2017 Xavier Leclercq

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

#ifndef _ISHIKO_WINDOWSREGISTRY_KEY_H_
#define _ISHIKO_WINDOWSREGISTRY_KEY_H_

#include "KeyPath.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <memory>

namespace Ishiko
{
namespace WindowsRegistry
{

class KeyImpl;

// This class represents a key in the Windows Registry
class Key
{
public:
	typedef std::shared_ptr<Key> ptr;

public:
	explicit Key(KeyImpl* impl);
	~Key();

    bool hasValue(const std::string& valueName);
	void enumValues(std::vector<std::string>& valueNames);
	std::string getValueAsString(const std::string& valueName) const;
	void setValue(const std::string& valueName, const std::string& valueData);
	void deleteValue(const std::string& valueName);

	HKEY key();
	const KeyPath& path() const;

private:
	std::shared_ptr<KeyImpl> m_impl;
};

}
}

#endif
