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

#include "Registry.h"
#include "KeyImpl.h"
#include "KeyOperationException.h"

namespace Ishiko
{
namespace WindowsRegistry
{

Key Registry::createKey(const KeyPath& keyPath)
{
	KeyImpl* impl = new KeyImpl(keyPath, true);
	return Key(impl);
}

Key Registry::openKey(const KeyPath& keyPath)
{
	KeyImpl* impl = new KeyImpl(keyPath, false);
	return Key(impl);
}

void Registry::deleteKey(const KeyPath& keyPath)
{
	HKEY hive;
	std::string subKeyPath;
	keyPath.splitInHiveAndSubKey(hive, subKeyPath);
	LONG result = RegDeleteKeyExA(hive, subKeyPath.c_str(), 0, 0);
	if ((result != ERROR_SUCCESS) && (result != ERROR_FILE_NOT_FOUND))
	{
		throw KeyOperationException(KeyOperationException::eDelete,
			keyPath.str(), result, __FILE__, __LINE__);
	}
}

Key Registry::createSubKey(Key& key, const std::string& path)
{
	KeyImpl* impl = new KeyImpl(key, path, true);
	return Key(impl);
}

Key Registry::createSubKey(HKEY hiveKey, const std::string& path)
{
	KeyImpl* impl = new KeyImpl(hiveKey, path, true);
	return Key(impl);
}

Key Registry::openSubKey(Key& key, const std::string& path)
{
	KeyImpl* impl = new KeyImpl(key, path, false);
	return Key(impl);
}

Key Registry::openSubKey(HKEY hiveKey, const std::string& path)
{
	KeyImpl* impl = new KeyImpl(hiveKey, path, false);
	return Key(impl);
}

void Registry::deleteSubKey(Key& key, const std::string& path)
{
	LONG result = RegDeleteKeyExA(key.key(), path.c_str(), 0, 0);
	if ((result != ERROR_SUCCESS) && (result != ERROR_FILE_NOT_FOUND))
	{
		throw KeyOperationException(KeyOperationException::eDelete,
			path, result, __FILE__, __LINE__);
	}
}

void Registry::deleteSubKey(HKEY key, const std::string& path)
{
	LONG result = RegDeleteKeyExA(key, path.c_str(), 0, 0);
	if ((result != ERROR_SUCCESS) && (result != ERROR_FILE_NOT_FOUND))
	{
		throw KeyOperationException(KeyOperationException::eDelete,
			path, result, __FILE__, __LINE__);
	}
}

}
}
