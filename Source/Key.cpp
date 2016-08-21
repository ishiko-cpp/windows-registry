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

#include "Key.h"
#include "KeyImpl.h"
#include "KeyOperationException.h"

namespace Ishiko
{
namespace WindowsRegistry
{

Key::Key(KeyImpl* impl)
	: m_impl(impl)
{
}

Key::~Key()
{
}

void Key::enumValues(std::vector<std::string>& valueNames)
{
	m_impl->enumValues(valueNames);
}

std::string Key::getValueAsString(const std::string& valueName) const
{
	return m_impl->getValueAsString(valueName);
}

void Key::setValue(const std::string& valueName,
				   const std::string& valueData)
{
	m_impl->setValue(valueName, valueData);
}

void Key::deleteValue(const std::string& valueName)
{
	m_impl->deleteValue(valueName);
}

HKEY Key::key()
{
	return m_impl->key();
}

const KeyPath& Key::path() const
{
	return m_impl->path();
}

}
}
