#include "pch.h"
#include "DeviceClassrepository.hpp"
#include <iostream>

// Building the list of devices
void DeviceClassRepository::buildDeviceDescription(SP_DEVINFO_DATA devInfo) {
    getDeviceRegistryProperty(devInfo, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME);
}

// Helper function get device specific values
void DeviceClassRepository::getDeviceRegistryProperty(SP_DEVINFO_DATA data, DWORD property, DWORD expectedType) {
    DWORD length{ 0 };
    auto retStatus = SetupDiGetDeviceRegistryProperty(_deivceInfoHandle, &data, property,
        NULL, NULL, 0, &length);

    // Reporting error
    if (FALSE == retStatus) {
        std::string errorMessage("Unable to get property value");
        throw errorMessage;
    }
}

// Intiate build the repository
DeviceClassRepository::DeviceClassRepository(const GUID& classGuid) {
    
    // Getting device class data handle
    _deivceInfoHandle = SetupDiGetClassDevs(&classGuid, NULL, NULL,
        DIGCF_PROFILE | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

    if (INVALID_HANDLE_VALUE == _deivceInfoHandle) {
        ErrorObject e;
        throw e;
    }

    // Stroing the class GUID
    _deviceGuid = classGuid;
}

void DeviceClassRepository::getDevices() {

    // Seting up for getting actual data
    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    
    // Enumurating all the devices
    for (int deviceIndex = 0; SetupDiEnumDeviceInfo(_deivceInfoHandle, deviceIndex, &deviceInfoData); deviceIndex++) {
        buildDeviceDescription(deviceInfoData);
    }
}
