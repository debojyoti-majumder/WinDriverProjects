#pragma once
#define _WIN32_DCOM

#include <comdef.h>
#include <Wbemidl.h>
#include <string>

class WBEMLocator {
    private:
        IWbemLocator*   _pLocator;
        IWbemServices*  _pService;

    public:
        WBEMLocator(const std::wstring& wbemNamespace);
        void getQueryResultIterator(const std::wstring& wqlQuery);
        ~WBEMLocator();
};
