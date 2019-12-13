#pragma once

#include <string>
#include <Windows.h>
#include <tchar.h>

class ErrorObject {
private:
    DWORD _dwErrorCode;

public:
    ErrorObject() {
        _dwErrorCode = ::GetLastError();
    }

    DWORD getErrorCode() const {
        return _dwErrorCode;
    }

    std::wstring getErrorString() {
        std::wstring errorString{ _T("No Error") };

        return errorString;
    }
};