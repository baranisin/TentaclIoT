#include "Client.h"

Client::Client() {
    configurePlaform();
    DiscoveryManager::getInstance().findAvalaibleServers();
    sleep(1); //TODO find better solution
    for (auto const &mapItem : DiscoveryManager::getInstance().getAvailableServerMap()) {
        mapItem.second.printServerInfo();
    }
    stopPlatform();
}

void Client::configurePlaform() {
    /* TODO add persistent storage
     * OCPersistentStorage ps {client_open, fread, fwrite, fclose, unlink };
     * then use this constructor
     * PlatformConfig cfg {
        OC::ServiceType::InProc,
        OC::ModeType::Both,
        &ps
        };
     */
    try {
        PlatformConfig config{
                OC::ServiceType::InProc,
                ModeType::Client,
                OC_DEFAULT_ADAPTER,
                OC::QualityOfService::LowQos
        };
        OCPlatform::Configure(config);
        OC_VERIFY(OCPlatform::start() == OC_STACK_OK);
    } catch (OCException &exception) {
        cout << "Exception: " << exception.what();
    }


}

void Client::stopPlatform() {
    try {
        OC_VERIFY(OCPlatform::stop() == OC_STACK_OK);
    } catch (OCException &exception) {
        cout << "Exception: " << exception.what();
    }
}