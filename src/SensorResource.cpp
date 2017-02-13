//
// Created by kingofwolwes on 21.6.2016.
//

#include "SensorResource.h"
#include "SensorServer.h"

SensorResource::SensorResource(ResourceArgumentsBundle args) {
    isOn = false;
    init(args.resources.back());
    resource->getRemoteAttributes(getCallback);
}

SensorResource::~SensorResource() {
    resource->stopCaching();
}

void SensorResource::onAttrSet(const RCSResourceAttributes &attrs, int eCode) {
    cout << "----SET---- State: " << attrs.at(SensorServer::IS_ON_ATTR).toString() << "-----------" << endl;
    isWaitingForUpdate = false;
}

void SensorResource::onAttrGet(const RCSResourceAttributes &attrs, int eCode) {
    cout << "----GET---- State: " << attrs.at(SensorServer::IS_ON_ATTR).toString() << "-----------" << endl;
}

void SensorResource::onCacheUpdated(const RCSResourceAttributes &attrs) {
    cout << "----UPDATED---- State: " << attrs.at(SensorServer::IS_ON_ATTR).toString() << "-----------" << endl;
    isOn = attrs.at(SensorServer::IS_ON_ATTR).toString() == "true";
    for(OnAttrChangeListener* listener : listeners){
        listener->onAttrChanged();
    }
    isWaitingForUpdate = false;
}

void SensorResource::defineServices() {
    pair<string, bool> getService("get_state_on", false);
    services.push_back(getService);
}

void SensorResource::callService(const string &service) {
    int serviceId = getServiceId(service);
    switch(serviceId){
        case NOT_FOUND:
            //TODO throw exception
            break;
        case GET:
            serviceReturnStorage = getState();
            break;
    }
}

int SensorResource::getState() {
    return isOn;
}















