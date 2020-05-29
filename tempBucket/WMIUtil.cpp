// Helps in printing out reports

#include "pch.h"
#include <iostream>

#include "COMInitiliser.h"
#include "HResultException.h"
#include "WBEMLocator.h"

#pragma comment(lib, "wbemuuid.lib")

int main() {

    try {
        // TODO: May be craete a contxet class with Lamda expression
        // The service should always happen in cominit context
        auto comInit{ COMInitiliser::getInstance() }; {
            // Get the service locator
            WBEMLocator servicelocator(std::wstring(L"ROOT\\CIMV2"));
        }

        // Done with COM components
        comInit->relase();
    }
    catch (const HResultException& ex) {
        std::cerr << "System Error!!";
        std::cerr << ex.getMessage() << std::endl;
    }

    return 0;
}

