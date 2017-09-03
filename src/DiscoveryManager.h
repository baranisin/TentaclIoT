//
// Created by Patrik Baranisin on 3.9.2017.
//
#include <condition_variable>
#include "ServerModel.h"


#ifndef IOTIVITY_BAKALARKA_DISCOVERYMANAGER_H
#define IOTIVITY_BAKALARKA_DISCOVERYMANAGER_H

typedef map<string, ServerModel> ServerMap;

class DiscoveryManager {
private:
    ServerMap serverMap;

    FindResListCallback onResourceListFoundCallback;
    FindDeviceCallback onDeviceFoundCallback;
    FindPlatformCallback onPlatformFoundCallback;

    DiscoveryManager();

    void setCallbacks();

    void onResourceListFound(const vector<shared_ptr<OCResource>> &resourceList);

    void onDeviceFound(const OCRepresentation &representation);

    void onPlatformFound(const OCRepresentation &representation);

public:
    DiscoveryManager(DiscoveryManager const &) = delete;

    void operator=(DiscoveryManager const &)  = delete;

    static DiscoveryManager &getInstance();

    static mutex curResourceLock;

    void findAvalaibleServers();

    const ServerMap &getAvailableServerMap();
};


#endif //IOTIVITY_BAKALARKA_DISCOVERYMANAGER_H
