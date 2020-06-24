#include "pch.h"
#include "WindowsServiceManager.h"

WindowsServiceManager* WindowsServiceManager::_instance = nullptr;

WindowsServiceManager::WindowsServiceManager() {
}

WindowsServiceManager* WindowsServiceManager::getInstance() {
    if (WindowsServiceManager::_instance == nullptr) {
        WindowsServiceManager::_instance = new WindowsServiceManager();
    }

    return WindowsServiceManager::_instance;
}

WindowsServiceManager::~WindowsServiceManager() {
    // Releaseing all the service objects
    for (auto item : _serviceRepository)
        delete item.second;
}

void WindowsServiceManager::addServiceType(ServiceType type, IWindowsService* svc) {
    auto it = _serviceRepository.find(type);

    if (it == _serviceRepository.end()) {
        svc->setHandle(0);
        _serviceRepository.insert(std::make_pair(type, svc));
    }
}

IWindowsService* WindowsServiceManager::getServiceObject(ServiceType type) {
    return _serviceRepository[type];
}
