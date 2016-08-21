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

#include "KeyOperationException.h"
#include <sstream>

namespace Ishiko
{
namespace WindowsRegistry
{

KeyOperationException::KeyOperationException(EOperation operation, 
											 const std::string& path,
											 LONG windowsErrorCode, 
											 const char* file,
											 int line)
	: Exception(createMessage(operation, path, windowsErrorCode), file, line),
	m_windowsErrorCode(windowsErrorCode)
{
}

LONG KeyOperationException::windowsErrorCode() const
{
	return m_windowsErrorCode;
}

std::string KeyOperationException::createMessage(EOperation operation, 
												 const std::string& path,
												 LONG windowsErrorCode)
{
	std::stringstream result;
	result << "WindowsRegistry: ";
	switch (operation)
	{
	case eCreate:
		result << "failed to create key ";
		break;

	case eCreateSubKey:
		result << "failed to create subkey ";
		break;

	case eOpen:
		result << "failed to open key ";
		break;

	case eDelete:
		result << "failed to delete path ";
		break;

	case eEnumValues:
		result << "failed to enumerate values of key ";
		break;

	case eDeleteValue:
		result << "failed to delete value ";
		break;
	}
	result << path << " (";

	char formattedErrorCode[1024];
	DWORD n = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, windowsErrorCode, 0,
		formattedErrorCode, 1024, NULL);
	if (n >= 2)
	{
		if (formattedErrorCode[n - 2] == '\r')
		{
			formattedErrorCode[n - 2] = 0;
		}
	}
	result << formattedErrorCode;
	result << ")";

	return result.str();
}

}
}
