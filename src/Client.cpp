#include "Client.h"

Client::Client() {
    platformConfigure();
    registeredResources = map<string, ResourceRepresentation*>{};
    config = new Configuration();
}

Client::~Client() {
    stopDiscovery();
    delete discoveryThread;
}

void Client::platformConfigure() {
    try {

        PlatformConfig config{
                OC::ServiceType::InProc,
                ModeType::Client,
                ALL_AVALAIBLE_INTERFACES,
                RANDOMLY_AVALAIBLE_PORT,
                OC::QualityOfService::LowQos
        };
        OCPlatform::Configure(config);

    }catch (RCSPlatformException e){
        cout << e.getReason() << endl;
    }
}

void Client::outputActualConfiguration()  {
    if(isDiscovering()){
        config->writeOutput(discoveryThread->getDiscoveredResources(), registeredResources);

        printActualDiscoveredResources();
    }
}

void Client::printActualDiscoveredResources(){
    if(isDiscovering()){
        discoveryThread->printResourceList();
    }
}

bool Client::hasResourceDiscovered(const string &uri) {
    if(isDiscovering()){
        return discoveryThread->hasResource(uri);
    }

}

void Client::startDiscovery(const vector<string> &types) {
    if(!isDiscovering()){
        if(types == EMPTY_STRING_VECTOR){
            discoveryThread = new DiscoveryThread();
        } else {
            discoveryThread = new DiscoveryThread(types);
        }
        sleep(1);
        discoveryThread->startDiscovering();
    }

}

void Client::stopDiscovery() {
    if(isDiscovering()){
        discoveryThread->stopDiscovering();
    }
}

bool Client::isDiscovering() {
    if(discoveryThread == nullptr){
        return false;
    }
    return discoveryThread->isRunningDiscovery();
}

void Client::registerResourceFromDiscovery(const string &uri, const string &type) {
    try {
        if(isDiscovering()){
            RCSRemoteResourceObject::Ptr res = discoveryThread->getResource(uri);
            string absURI = res->getAddress() + res->getUri();

            string resType;
            if(type == DEFAULT_STRING){
                resType = res->getTypes()[0];
            } else{
                resType = type;
            }

            registeredResources[absURI] = ResourceRepresentationBuilder(discoveryThread, resType)
                    .addResource(res)
                    .setId(3)
                    .build();

        }
    }catch(NotInDiscoveredResException e){
        cout << e.what() << endl;
        cout << "URI: " << uri << endl;
    }catch (MoreResWithSameURIException e){
        cout << e.what() << endl;
        cout << "URI: " << uri << endl;
    }
}

bool Client::hasResourceRegistered(const string &uri) {
    return registeredResources[uri] != nullptr;
}

void Client::loadConfiguration() {
    for(pair<string, string> res : config->readInput()){

        registerResourceFromDiscovery(
                res.first,
                res.second
        );
    }

    printRegisteredResources();
}

void Client::printRegisteredResources() {
    for (const auto &res : registeredResources) {
        std::cout << "URI: " << res.second->getAbsoluteUri() << " has ID: " << res.second->getResourceId()<< std::endl;
    }
}



