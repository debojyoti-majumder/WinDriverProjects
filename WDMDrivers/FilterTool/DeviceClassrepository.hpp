#pragma once

#include "pch.h"
#include <initguid.h>

class DeviceClassRepository {
    private:
        GUID        _deviceGuid;
        HDEVINFO    _deivceInfoHandle;

        void buildDeviceDescription(SP_DEVINFO_DATA);
        void getDeviceRegistryProperty(SP_DEVINFO_DATA, DWORD, DWORD expectedType = REG_SZ);

    public:
        explicit DeviceClassRepository(const GUID& deviceGuid);
        void getDevices();
};