#include "Client.h"

Client::Client() {
    platformConfigure();
    registeredResources = map<string, RCSRemoteResourceObject::Ptr>{};
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

//void Client::outputActualConfiguration()  {
//    if(isDiscovering()){
//        config->writeOutput(discoveryThread->getDiscoveredResources(), registeredResources);
//
//        printActualDiscoveredResources();
//    }
//}

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

/*bool Client::registerResourceFromDiscovery(const string &uri) {
    try {

        if(isDiscovering()){
            RCSRemoteResourceObject::Ptr res = discoveryThread->getResource(uri);
            registeredResources[uri] = res;
            return true;
        }

    }catch(NotInDiscoveredResException e){
        cout << e.what() << endl;
        cout << "URI: " << uri << endl;
    }catch (MoreResWithSameURIException e){
        cout << e.what() << endl;
        cout << "URI: " << uri << endl;
    }
    return false;
}*/



bool Client::hasResourceRegistered(const string &uri) {
    return registeredResources[uri] != nullptr;
}