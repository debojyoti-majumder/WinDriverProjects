#pragma once

#include "pch.h"
#include <initguid.h>

class DeviceClassRepository
{
    private:
        GUID _deviceGuid;

    public:
        explicit DeviceClassRepository(GUID deviceGuid);
        void GetDevices();
};