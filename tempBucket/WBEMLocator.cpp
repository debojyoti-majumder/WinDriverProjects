#include "pch.h"
#include "WBEMLocator.h"
#include "HResultException.h"

WBEMLocator::WBEMLocator(const std::wstring & wbemNamespace) : _pLocator(NULL), _pService(NULL) {
    // Getting a actual instance of the locator service through an interface
    auto hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID *)&_pLocator);

    if (FAILED(hres)) throw new HResultException(hres);

    // Connecting to a WBEM namespace
    hres = _pLocator->ConnectServer(
        _bstr_t(wbemNamespace.c_str()),     // Object path of WMI namespace
        NULL,                               // User name. NULL = current user
        NULL,                               // User password. NULL = current
        0,                                  // Locale. NULL indicates current
        NULL,                               // Security flags.
        0,                                  // Authority (for example, Kerberos)
        0,                                  // Context object 
        &_pService                          // pointer to IWbemServices proxy
    );
    if (FAILED(hres)) throw new HResultException(hres);

    // Setting the security on the service object
    hres = CoSetProxyBlanket(
        _pService,                          // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,                  // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,                   // RPC_C_AUTHZ_xxx
        NULL,                               // Server principal name 
        RPC_C_AUTHN_LEVEL_CALL,             // RPC_C_AUTHN_LEVEL_xxx 
        RPC_C_IMP_LEVEL_IMPERSONATE,        // RPC_C_IMP_LEVEL_xxx
        NULL,                               // client identity
        EOAC_NONE                           // proxy capabilities 
    );
    if (FAILED(hres)) throw new HResultException(hres);
}

void WBEMLocator::getQueryResultIterator(const std::wstring & wqlQuery) {
}

WBEMLocator::~WBEMLocator() {
    if (NULL != _pService) _pService->Release();
    if (NULL != _pLocator) _pLocator->Release();
}
