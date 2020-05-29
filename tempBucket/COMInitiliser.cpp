#include "pch.h"
#include "COMInitiliser.h"
#include "HResultException.h"

COMInitiliser* COMInitiliser::instance = nullptr;
LONG COMInitiliser::refCount = 0;

COMInitiliser::COMInitiliser() {
    // Making it multithreaded
    auto initHr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(initHr)) throw new HResultException(initHr);

    // Initilising the sceurity
    auto hresSecurity = CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities 
        NULL                         // Reserved
    );
    if (FAILED(hresSecurity)) throw new HResultException(hresSecurity);

}

COMInitiliser* COMInitiliser::getInstance() {
    if ( nullptr == instance ) instance = new COMInitiliser;

    // Adding reference count
    InterlockedIncrement(&refCount);

    // Retruning the object
    return instance;
}

void COMInitiliser::relase() {
    InterlockedDecrement(&COMInitiliser::refCount);
    if (COMInitiliser::refCount == 0) delete COMInitiliser::instance;
}

COMInitiliser::~COMInitiliser() {
    CoUninitialize();
}
