// FilterTool.cpp : The main purpose of this is tool is to implement a object oriented 
// implementation to do Create Delete and List filter drivers for a given class

#include "pch.h"
#include <iostream>
#include "DeviceClassrepository.hpp"

int __cdecl _tmain(int argc, _In_reads_(argc) LPTSTR argv[])
{
    std::cout << "Filter Tool!\n";
    DeviceClassRepository diskDevices(DiskClassGuid);
    diskDevices.getDevices();

    return 0;
}
