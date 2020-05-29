// Helps in printing out reports

#include "pch.h"
#include <iostream>

#include "COMInitiliser.h"
#include "HResultException.h"

int main() {

    try {
        auto comInit{ COMInitiliser::getInstance() };

        // Get the service locator

        comInit->relase();
    }
    catch (const HResultException& ex) {
        std::cerr << "System Error!!";
        std::cerr << ex.getMessage() << std::endl;
    }

    return 0;
}

