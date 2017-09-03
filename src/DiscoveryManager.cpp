//
// Created by Patrik Baranišin on 3.9.2017.
//

#include "DiscoveryManager.h"

mutex DiscoveryManager::curResourceLock;

DiscoveryManager &DiscoveryManager::getInstance() {
    static DiscoveryManager instance;
    return instance;
}

DiscoveryManager::DiscoveryManager() {
    setCallbacks();
}

void DiscoveryManager::findAvalaibleServers() {
    try {

        OC_VERIFY(
                OCPlatform::findResourceList("", OC_RSRVD_WELL_KNOWN_URI, CT_ADAPTER_IP, onResourceListFoundCallback) ==
                OC_STACK_OK);
        OC_VERIFY(OCPlatform::getDeviceInfo("", OC_RSRVD_DEVICE_URI, CT_ADAPTER_IP, onDeviceFoundCallback) ==
                  OC_STACK_OK);
        OC_VERIFY(OCPlatform::getPlatformInfo("", OC_RSRVD_PLATFORM_URI, CT_ADAPTER_IP, onPlatformFoundCallback) ==
                  OC_STACK_OK);
    } catch (OCException &exception) {
        cout << "Exception: " << exception.what();
    }

}

void DiscoveryManager::setCallbacks() {
    onResourceListFoundCallback = bind(&DiscoveryManager::onResourceListFound, this, placeholders::_1);
    onDeviceFoundCallback = bind(&DiscoveryManager::onDeviceFound, this, placeholders::_1);
    onPlatformFoundCallback = bind(&DiscoveryManager::onPlatformFound, this, placeholders::_1);
}

void DiscoveryManager::onResourceListFound(const vector<shared_ptr<OCResource>> &resourceList) {
    lock_guard<mutex> lock(curResourceLock);
    for (const shared_ptr<OCResource> &resource : resourceList) {
        if (serverMap.find(resource->host()) == serverMap.end()) {
            serverMap[resource->host()] = ServerModel();
            cout << "New host: " << resource->host() << "\n---> with resource: " << resource->sid() << endl;
        } else {
            if (serverMap[resource->host()].resourceMap.find(resource->uniqueIdentifier()) ==
                serverMap[resource->host()].resourceMap.end()) {
                serverMap[resource->host()].resourceMap[resource->uniqueIdentifier()] = resource;
                cout << "Known host: " << resource->host() << "\n---> with new resource: " << resource->uri() << endl;
            } else {
                return;
            }
        }
    }
}

void DiscoveryManager::onDeviceFound(const OCRepresentation &representation) {
    lock_guard<mutex> lock(curResourceLock);
    string value;
    for (const string &deviceInfoKey : ServerModel::DEVICE_INFO_KEYS) {
        if (representation.getValue(deviceInfoKey, value)) {
            cout << deviceInfoKey << " : " << value << endl;
            serverMap[representation.getHost()].deviceInfoMap[deviceInfoKey] = value;
        }
    }
}

void DiscoveryManager::onPlatformFound(const OCRepresentation &representation) {
    lock_guard<mutex> lock(curResourceLock);
    string value;
    for (const string &platformInfoKey : ServerModel::PLATFORM_INFO_KEYS) {
        if (representation.getValue(platformInfoKey, value)) {
            cout << platformInfoKey << " : " << value << endl;
            serverMap[representation.getHost()].platformInfoMap[platformInfoKey] = value;
        }
    }
}

const ServerMap &DiscoveryManager::getAvailableServerMap() {

    return serverMap;
}



