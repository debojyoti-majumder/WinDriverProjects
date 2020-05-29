#include "pch.h"
#include "HResultException.h"

HResultException::HResultException(HRESULT hr) : _errorCode(hr) {
}

std::string HResultException::getMessage() const {
    return std::system_category().message(_errorCode);
}
