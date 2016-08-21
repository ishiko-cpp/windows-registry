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

#include "KeyImpl.h"
#include "KeyOperationException.h"

namespace Ishiko
{
namespace WindowsRegistry
{

KeyImpl::KeyImpl(const KeyPath& keyPath, bool create)
	: m_path(keyPath)
{
	HKEY hiveKey;
	std::string subKeyPath;
	m_path.splitInHiveAndSubKey(hiveKey, subKeyPath);
	open(hiveKey, subKeyPath, create, KEY_QUERY_VALUE, m_path, m_key, m_accessRights);
}

KeyImpl::KeyImpl(Key& key, const std::string& subKeyPath, bool create)
	: m_path(key.path(), subKeyPath)
{
	open(key.key(), subKeyPath, create, KEY_QUERY_VALUE, m_path, m_key, m_accessRights);
}

KeyImpl::KeyImpl(HKEY hiveKey, const std::string& subKeyPath, bool create)
	: m_path(KeyPath(hiveKey), subKeyPath)
{
	open(hiveKey, subKeyPath, create, KEY_QUERY_VALUE, m_path, m_key, m_accessRights);
}

KeyImpl::~KeyImpl()
{
	RegCloseKey(m_key);
}

void KeyImpl::enumValues(std::vector<std::string>& valueNames)
{
	for (DWORD i = 0;; ++i)
	{
		char valueName[1024];
		DWORD valueSize = 1024;
		LONG result = RegEnumValueA(m_key, i, valueName, &valueSize, NULL, NULL, NULL, NULL);
		if (result != ERROR_SUCCESS)
		{
			if (result == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			else
			{
				throw KeyOperationException(KeyOperationException::eEnumValues,
					m_path.str(), result, __FILE__, __LINE__);
			}
		}

		valueNames.push_back(valueName);
	}
}

std::string KeyImpl::getValueAsString(const std::string& valueName) const
{
	DWORD type;
	char buffer[1024];
	DWORD bufferSize = 1024;
	LONG result = RegQueryValueExA(m_key, valueName.c_str(), 0, &type,
		(LPBYTE)&buffer, &bufferSize);
	if (result != ERROR_SUCCESS)
	{
		throw KeyOperationException(KeyOperationException::eGetValue,
			m_path.str(), result, __FILE__, __LINE__);
	}
	if (buffer[bufferSize - 1] != 0)
	{
		buffer[bufferSize] = 0;
	}

	return std::string(buffer);
}

void KeyImpl::setValue(const std::string& valueName, const std::string& valueData)
{
	requireAccessRights(KEY_SET_VALUE);

	LONG result = RegSetValueExA(m_key, valueName.c_str(), 0,
		REG_SZ, (const BYTE*)valueData.c_str(), valueData.size());
	if (result != ERROR_SUCCESS)
	{
		throw KeyOperationException(KeyOperationException::eSetValue,
			m_path.str(), result, __FILE__, __LINE__);
	}
}

void KeyImpl::deleteValue(const std::string& valueName)
{
	requireAccessRights(KEY_SET_VALUE);

	LONG result = RegDeleteValueA(m_key, valueName.c_str());
	if (result != ERROR_SUCCESS)
	{
		throw KeyOperationException(KeyOperationException::eDeleteValue,
			valueName, result, __FILE__, __LINE__);
	}
}

HKEY KeyImpl::key()
{
	return m_key;
}

const KeyPath& KeyImpl::path() const
{
	return m_path;
}

void KeyImpl::open(HKEY key,
				   const std::string subKeyPath,
				   bool create,
				   REGSAM accessRights,
				   const KeyPath& keyPath,
				   HKEY& resultKey, 
				   REGSAM& resultAccessRights)
{
	LONG result;
	if (create)
	{
		result = RegCreateKeyExA(key, subKeyPath.c_str(),
			0, NULL, 0, accessRights, NULL, &resultKey, NULL);
		resultAccessRights = accessRights;
	}
	else
	{
		result = RegOpenKeyExA(key, subKeyPath.c_str(),
			0, accessRights, &resultKey);
		resultAccessRights = accessRights;
	}
	if (result != ERROR_SUCCESS)
	{
		throw KeyOperationException(create ? KeyOperationException::eCreate : KeyOperationException::eOpen,
			keyPath.str(), result, __FILE__, __LINE__);
	}
}

void KeyImpl::requireAccessRights(REGSAM accessRights)
{
	if ((m_accessRights && accessRights) != accessRights)
	{
		accessRights |= m_accessRights;

		HKEY newKey;
		REGSAM newAccessRights;
		
		HKEY hiveKey;
		std::string subKeyPath;
		m_path.splitInHiveAndSubKey(hiveKey, subKeyPath);

		open(hiveKey, subKeyPath, false, accessRights, m_path, newKey, newAccessRights);
		
		RegCloseKey(m_key);
		m_key = newKey;
		m_accessRights = newAccessRights;
	}
}

}
}
