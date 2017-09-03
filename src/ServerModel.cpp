//
// Created by Patrik Baranišin on 3.9.2017.
//

#include "ServerModel.h"

const vector<string> ServerModel::DEVICE_INFO_KEYS = {
        OC_RSRVD_DEVICE_ID,
        OC_RSRVD_DEVICE_NAME,
        OC_RSRVD_SPEC_VERSION,
        OC_RSRVD_DATA_MODEL_VERSION,
        OC_RSRVD_DEVICE_DESCRIPTION,
        OC_RSRVD_SOFTWARE_VERSION,
        OC_RSRVD_DEVICE_MFG_NAME,
        OC_RSRVD_DEVICE_MODEL_NUM,
        OC_RSRVD_PROTOCOL_INDEPENDENT_ID,
};

const vector<string> ServerModel::PLATFORM_INFO_KEYS = {
        OC_RSRVD_PLATFORM_ID,
        OC_RSRVD_MFG_NAME,
        OC_RSRVD_MFG_URL,
        OC_RSRVD_MODEL_NUM,
        OC_RSRVD_MFG_DATE,
        OC_RSRVD_PLATFORM_VERSION,
        OC_RSRVD_OS_VERSION,
        OC_RSRVD_HARDWARE_VERSION,
        OC_RSRVD_FIRMWARE_VERSION,
        OC_RSRVD_SUPPORT_URL,
        OC_RSRVD_SYSTEM_TIME,
};

void ServerModel::printServerInfo() const {
    cout << "=========== SERVER ============" << endl;
    printResourcesInfo();
    printDeviceInfo();
    printPlatformInfo();
    cout << "===============================" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
}

void ServerModel::printResourcesInfo() const {
    cout << "-------RESOURCES INFO-------" << endl;
    for (auto const &resMapItem : resourceMap) {
        shared_ptr<OCResource> resource = resMapItem.second;

        cout << "SID:   " << resource->sid() << endl;
        cout << "Host:  " << resource->host() << endl;
        cout << "URI:   " << resource->uri() << endl;
        cout << "Identifier:    " << resource->uniqueIdentifier() << endl;
        cout << "Connectivity type: " << resource->connectivityType() << endl;
        cout << "All hosts: ";
        for (string const &host : resource->getAllHosts()) {
            cout << host << ", ";
        }
        cout << endl;
        cout << "Interfaces:    ";
        for (string const &interface : resource->getResourceInterfaces()) {
            cout << interface << ", ";
        }
        cout << endl;
        cout << "Types:    ";
        for (string const &type : resource->getResourceTypes()) {
            cout << type << ", ";
        }
        cout << endl;
        cout << endl;
    }
    cout << endl;
}

void ServerModel::printDeviceInfo() const {
    map<string, string> deviceInfoNamesMap;

    deviceInfoNamesMap[OC_RSRVD_DEVICE_ID] = "Device ID              ";
    deviceInfoNamesMap[OC_RSRVD_DEVICE_NAME] = "Device name            ";
    deviceInfoNamesMap[OC_RSRVD_SPEC_VERSION] = "Spec version url       ";
    deviceInfoNamesMap[OC_RSRVD_DATA_MODEL_VERSION] = "Data Model Version     ";
    deviceInfoNamesMap[OC_RSRVD_DEVICE_DESCRIPTION] = "Device description     ";
    deviceInfoNamesMap[OC_RSRVD_SOFTWARE_VERSION] = "Software version       ";
    deviceInfoNamesMap[OC_RSRVD_DEVICE_MFG_NAME] = "Manufacturer name      ";
    deviceInfoNamesMap[OC_RSRVD_DEVICE_MODEL_NUM] = "Model number           ";
    deviceInfoNamesMap[OC_RSRVD_PROTOCOL_INDEPENDENT_ID] = "Protocol-Independent ID";


    cout << "-------DEVICE INFO-------" << endl;
    for (auto const &deviceMapItem : deviceInfoMap) {
        cout << deviceInfoNamesMap[deviceMapItem.first] << " : " << deviceMapItem.second << endl;
    }
    cout << endl;
}

void ServerModel::printPlatformInfo() const {
    map<string, string> platformInfoNamesMap;

    platformInfoNamesMap[OC_RSRVD_PLATFORM_ID] = "Platform ID                    ";
    platformInfoNamesMap[OC_RSRVD_MFG_NAME] = "Manufacturer name              ";
    platformInfoNamesMap[OC_RSRVD_MFG_URL] = "Manufacturer url               ";
    platformInfoNamesMap[OC_RSRVD_MODEL_NUM] = "Manufacturer Model No          ";
    platformInfoNamesMap[OC_RSRVD_MFG_DATE] = "Manufactured Date              ";
    platformInfoNamesMap[OC_RSRVD_PLATFORM_VERSION] = "Manufacturer Platform Version  ";
    platformInfoNamesMap[OC_RSRVD_OS_VERSION] = "Manufacturer OS version        ";
    platformInfoNamesMap[OC_RSRVD_HARDWARE_VERSION] = "Manufacturer hardware version  ";
    platformInfoNamesMap[OC_RSRVD_FIRMWARE_VERSION] = "Manufacturer firmware version  ";
    platformInfoNamesMap[OC_RSRVD_SUPPORT_URL] = "Manufacturer support url       ";
    platformInfoNamesMap[OC_RSRVD_SYSTEM_TIME] = "Manufacturer system time       ";


    cout << "-------PLATFORM INFO-------" << endl;
    for (auto const &platformMapItem : platformInfoMap) {
        cout << platformInfoNamesMap[platformMapItem.first] << " : " << platformMapItem.second << endl;
    }
    cout << endl;
}


