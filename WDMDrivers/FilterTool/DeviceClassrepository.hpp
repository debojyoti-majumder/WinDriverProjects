#pragma once

#include "pch.h"
#include <initguid.h>

class DeviceClassRepository {
    private:
        GUID _deviceGuid;
        void buildDeviceDescription();

    public:
        explicit DeviceClassRepository(GUID deviceGuid);
        void GetDevices();
};