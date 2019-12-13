// FilterTool.cpp : The main purpose of this is tool is to implement a object oriented 
// implementation to do Create Delete and List filter drivers for a given class

#include "pch.h"
#include <iostream>
#include "DeviceClassrepository.hpp"

int __cdecl _tmain(int argc, _In_reads_(argc) LPTSTR argv[])
{
    DeviceClassRepository diskDevices(GUID_DEVINTERFACE_DISK);
    std::cout << "Filter Tool!\n";

    return 0;
}
