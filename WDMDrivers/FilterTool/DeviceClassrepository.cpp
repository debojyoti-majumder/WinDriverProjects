#include "pch.h"
#include "DeviceClassrepository.hpp"
#include <iostream>

void DeviceClassRepository::buildDeviceDescription() {
}

DeviceClassRepository::DeviceClassRepository(GUID classGuid) {
    // Getting device class data handle
    auto deviceInfo = SetupDiGetClassDevs(&classGuid, NULL, NULL,
        DIGCF_PROFILE | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

    if (INVALID_HANDLE_VALUE == deviceInfo) {
        ErrorObject e;
        throw e;
    }

    // Seting up for getting actual data
    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (int deviceIndex = 0; SetupDiEnumDeviceInfo(deviceInfo, deviceIndex, &deviceInfoData); deviceIndex++) { 
    }
}

void DeviceClassRepository::GetDevices() {
}
