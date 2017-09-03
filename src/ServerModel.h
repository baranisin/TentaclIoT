//
// Created by Patrik Baranišin on 3.9.2017.
//
#include "TypeDefs.h"

#ifndef IOTIVITY_BAKALARKA_SERVERMODEL_H
#define IOTIVITY_BAKALARKA_SERVERMODEL_H


class ServerModel {
public:
    ResourceMap resourceMap;
    map<string, string> deviceInfoMap; // TODO: Add member variables instead of map
    map<string, string> platformInfoMap; // Also here

    void printServerInfo() const;

    void printDeviceInfo() const;

    void printPlatformInfo() const;

    void printResourcesInfo() const;

    // TODO: create parsing functions for platformInfo and deviceInfo
    // setDeviceInfo(map)
    // setPlatformInfo(map)

    static const vector<string> DEVICE_INFO_KEYS;
    static const vector<string> PLATFORM_INFO_KEYS;
};


#endif //IOTIVITY_BAKALARKA_SERVERMODEL_H
