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

#include "KeyPath.h"
#include "InvalidPredefinedKeyException.h"

namespace Ishiko
{
namespace WindowsRegistry
{

KeyPath::KeyPath(HKEY key)
	: m_path(getPathFromPredefinedKey(key))
{
}

KeyPath::KeyPath(const std::string& path)
	: m_path(path)
{
}

KeyPath::KeyPath(const KeyPath& keyPath, const std::string& path)
	: m_path(keyPath.m_path)
{
	appendPath(path);
}

KeyPath::KeyPath(const KeyPath& other)
	: m_path(other.m_path)
{
}

KeyPath::~KeyPath()
{
}

void KeyPath::appendPath(const std::string& path)
{
	if (path.empty())
	{
		return;
	}
	if (path[0] != '\\')
	{
		m_path.append("\\");
		m_path.append(path);
	}
	else if (path.size() > 1)
	{
		m_path.append(path);
	}
}

bool KeyPath::operator ==(const std::string& other) const
{
	return (m_path == other);
}

bool KeyPath::operator !=(const std::string& other) const
{
	return (m_path != other);
}

KeyPath& KeyPath::operator =(const std::string& other)
{
	m_path = other;
	return *this;
}

const std::string& KeyPath::str() const
{
	return m_path;
}

bool KeyPath::isPredefinedKey() const
{
	return ((m_path == "HKEY_CLASSES_ROOT") || (m_path == "HKEY_CURRENT_CONFIG") ||
		(m_path == "HKEY_CURRENT_USER") || (m_path == "HKEY_LOCAL_MACHINE") ||
		(m_path == "HKEY_USERS") || (m_path == "HKEY_PERFORMANCE_DATA") ||
		(m_path == "HKEY_PERFORMANCE_NLSTEXT") || (m_path == "HKEY_PERFORMANCE_TEXT"));
}

void KeyPath::splitInHiveAndSubKey(HKEY& hive,
								   std::string& subKeyPath) const
{
	size_t pos = m_path.find('\\');
	if (pos != std::string::npos)
	{
		std::string hiveStr = m_path.substr(0, pos);
		hive = getHive(hiveStr);
		subKeyPath = m_path.substr(pos + 1);
	}
	else
	{
		hive = getHive(m_path);
		subKeyPath.clear();
	}
}

HKEY KeyPath::getHive(const std::string& path)
{
	if (path == "HKEY_CLASSES_ROOT")
	{
		return HKEY_CLASSES_ROOT;
	}
	else if (path == "HKEY_CURRENT_CONFIG")
	{
		return HKEY_CURRENT_CONFIG;
	}
	else if (path == "HKEY_CURRENT_USER")
	{
		return HKEY_CURRENT_USER;
	}
	else if (path == "HKEY_LOCAL_MACHINE")
	{
		return HKEY_LOCAL_MACHINE;
	}
	else if (path == "HKEY_USERS")
	{
		return HKEY_USERS;
	}
	else if (path == "HKEY_PERFORMANCE_DATA")
	{
		return HKEY_PERFORMANCE_DATA;
	}
	else if (path == "HKEY_PERFORMANCE_NLSTEXT")
	{
		return HKEY_PERFORMANCE_NLSTEXT;
	}
	else if (path == "HKEY_PERFORMANCE_TEXT")
	{
		return HKEY_PERFORMANCE_TEXT;
	}
	else
	{
		// TODO
		throw 0;
	}
}

std::string KeyPath::getPathFromPredefinedKey(HKEY key)
{
	if (key == HKEY_CLASSES_ROOT)
	{
		return "HKEY_CLASSES_ROOT";
	}
	else if (key == HKEY_CURRENT_CONFIG)
	{
		return "HKEY_CURRENT_CONFIG";
	}
	else if (key == HKEY_CURRENT_USER)
	{
		return "HKEY_CURRENT_USER";
	}
	else if (key == HKEY_LOCAL_MACHINE)
	{
		return "HKEY_LOCAL_MACHINE";
	}
	else if (key == HKEY_USERS)
	{
		return "HKEY_USERS";
	}
	else if (key == HKEY_PERFORMANCE_DATA)
	{
		return "HKEY_PERFORMANCE_DATA";
	}
	else if (key == HKEY_PERFORMANCE_NLSTEXT)
	{
		return "HKEY_PERFORMANCE_NLSTEXT";
	}
	else if (key == HKEY_PERFORMANCE_TEXT)
	{
		return "HKEY_PERFORMANCE_TEXT";
	}
	else
	{
		throw InvalidPredefinedKeyException(key, __FILE__, __LINE__);
	}
}

}
}
