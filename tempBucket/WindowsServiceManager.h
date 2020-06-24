#pragma once

#include "IWindowsService.h"
#include <map>

class WindowsServiceManager {
private:
    WindowsServiceManager();

    std::map<ServiceType, IWindowsService*> _serviceRepository;
    static WindowsServiceManager* _instance;

public:
    static WindowsServiceManager* getInstance();
    ~WindowsServiceManager();

    void addServiceType(ServiceType type, IWindowsService* svc);
    IWindowsService* getServiceObject(ServiceType type);
};
