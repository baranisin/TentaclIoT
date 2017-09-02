#include "Client.h"

mutex Client::curResourceLock;

Client::Client() {
    init();
}


void Client::init() {
    /* TODO add persistent storage
     * OCPersistentStorage ps {client_open, fread, fwrite, fclose, unlink };
     * then use this constructor
     * PlatformConfig cfg {
        OC::ServiceType::InProc,
        OC::ModeType::Both,
        &ps
        };
     */

    onResourceFoundCallback = bind(&Client::onResourceFound, this, placeholders::_1);
    onDeviceFoundCallback = bind(&Client::onDeviceFound, this, placeholders::_1);
    onPlatformFoundCallback = bind(&Client::onPlatformFound, this, placeholders::_1);

    PlatformConfig config{
            OC::ServiceType::InProc,
            ModeType::Client,
            OC_DEFAULT_ADAPTER,
            OC::QualityOfService::LowQos
    };
    OCPlatform::Configure(config);

    try {
        OC_VERIFY(OCPlatform::start() == OC_STACK_OK);
        while (true) {
            OCPlatform::findResource("", OC_RSRVD_WELL_KNOWN_URI, CT_ADAPTER_IP, onResourceFoundCallback);
            sleep(2);
        }


        OC_VERIFY(OCPlatform::stop() == OC_STACK_OK);

    } catch (OCException &exception) {
        cout << "Exception: " << exception.what();
    }
}

void Client::onResourceFound(std::shared_ptr<OCResource> resource) {
    lock_guard<std::mutex> lock(Client::curResourceLock);
    ResourceMap map;
    if (discoveredHosts.find(resource->host()) == discoveredHosts.end()) {
        map[resource->uniqueIdentifier()] = resource;
        cout << "New host: " << resource->host() << "\n---> with resource: " << resource->uri() << endl;
        OCPlatform::getDeviceInfo(resource->host(), OC_RSRVD_DEVICE_URI, CT_ADAPTER_IP, onDeviceFoundCallback);
        OCPlatform::getPlatformInfo(resource->host(), OC_RSRVD_PLATFORM_URI, CT_ADAPTER_IP, onPlatformFoundCallback);
    } else {
        map = discoveredHosts[resource->host()];
        if (map.find(resource->uniqueIdentifier()) == map.end()) {
            map[resource->uniqueIdentifier()] = resource;
            cout << "Known host: " << resource->host() << "\n---> with new resource: " << resource->uri() << endl;
        } else {
            return;
        }
    }
    discoveredHosts[resource->host()] = map;
    cout << endl;
}

void Client::onDeviceFound(const OCRepresentation &representation) {
    cout << "\nDevice Information received ---->" << endl;
    string value;
    string values[] =
            {
                    OC_RSRVD_DEVICE_ID, "Device ID              ",
                    OC_RSRVD_DEVICE_NAME, "Device name            ",
                    OC_RSRVD_SPEC_VERSION, "Spec version url       ",
                    OC_RSRVD_DATA_MODEL_VERSION, "Data Model Version     ",
                    OC_RSRVD_DEVICE_DESCRIPTION, "Device description     ",
                    OC_RSRVD_SOFTWARE_VERSION, "Software version       ",
                    OC_RSRVD_DEVICE_MFG_NAME, "Manufacturer name      ",
                    OC_RSRVD_DEVICE_MODEL_NUM, "Model number           ",
                    OC_RSRVD_PROTOCOL_INDEPENDENT_ID, "Protocol-Independent ID"
            };

    for (unsigned int i = 0; i < sizeof(values) / sizeof(values[0]); i += 2) {
        if (representation.getValue(values[i], value)) {
            cout << values[i + 1] << " : " << value << endl;
        }
    }
}

void Client::onPlatformFound(const OCRepresentation &representation) {
    cout << "\nPlatform Information received ---->\n";
    string value;
    string values[] =
            {
                    OC_RSRVD_PLATFORM_ID, "Platform ID                    ",
                    OC_RSRVD_MFG_NAME, "Manufacturer name              ",
                    OC_RSRVD_MFG_URL, "Manufacturer url               ",
                    OC_RSRVD_MODEL_NUM, "Manufacturer Model No          ",
                    OC_RSRVD_MFG_DATE, "Manufactured Date              ",
                    OC_RSRVD_PLATFORM_VERSION, "Manufacturer Platform Version  ",
                    OC_RSRVD_OS_VERSION, "Manufacturer OS version        ",
                    OC_RSRVD_HARDWARE_VERSION, "Manufacturer hardware version  ",
                    OC_RSRVD_FIRMWARE_VERSION, "Manufacturer firmware version  ",
                    OC_RSRVD_SUPPORT_URL, "Manufacturer support url       ",
                    OC_RSRVD_SYSTEM_TIME, "Manufacturer system time       ",
            };

    for (unsigned int i = 0; i < sizeof(values) / sizeof(values[0]); i += 2) {
        if (representation.getValue(values[i], value)) {
            cout << values[i + 1] << " : " << value << endl;
        }
    }
}





