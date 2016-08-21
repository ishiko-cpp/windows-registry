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

#ifndef _ISHIKO_WINDOWSREGISTRY_KEYOPERATIONEXCEPTION_H_
#define _ISHIKO_WINDOWSREGISTRY_KEYOPERATIONEXCEPTION_H_

#include "Exception.h"
#include <Windows.h>

namespace Ishiko
{
namespace WindowsRegistry
{

class KeyOperationException : public Exception
{
public:
	enum EOperation
	{
		eCreate,
		eCreateSubKey,
		eOpen,
		eDelete,
		eEnumValues,
		eGetValue,
		eSetValue,
		eDeleteValue,
	};

public:
	KeyOperationException(EOperation operation, const std::string& path,
		LONG windowsErrorCode, const char* file, int line);

	LONG windowsErrorCode() const;

private:
	static std::string createMessage(EOperation operation,
		const std::string& path, LONG windowsErrorCode);

private:
	LONG m_windowsErrorCode;
};

}
}

#endif
