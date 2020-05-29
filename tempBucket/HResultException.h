#pragma once

#include <Windows.h>
#include <string>

class HResultException {
    private:
        HRESULT _errorCode;

    public:
        HResultException(HRESULT);
        std::string getMessage() const;
};
