//
// Created by kingofwolwes on 17.6.2016.
//

#include "SwitchResource.h"
#include "SwitchServer.h"

void SwitchResource::defineServices() {
    pair<string, bool> turnOnService(TURN_ON_SERVICE_NAME, false);
    pair<string, bool> turnOffService(TURN_OFF_SERVICE_NAME, false);
    pair<string, bool> getService("get_state_on", false);
    services.push_back(turnOnService);
    services.push_back(turnOffService);
    services.push_back(getService);
}

void SwitchResource::onAttrSet(const RCSResourceAttributes &attrs, int eCode) {
    cout << "----SET---- State: " << attrs.at(SwitchServer::IS_ON_ATTR).toString() << "-----------" << endl;
    isOn = attrs.at(SwitchServer::IS_ON_ATTR).toString() == "true";
}

void SwitchResource::onAttrGet(const RCSResourceAttributes &attrs, int eCode) {
    cout << "----GET---- State: " << attrs.at(SwitchServer::IS_ON_ATTR).toString() << "-----------" << endl;
    isOn = attrs.at(SwitchServer::IS_ON_ATTR).toString() == "true";
}

void SwitchResource::onCacheUpdated(const RCSResourceAttributes &attrs) {
    isWaitingForUpdate = false;
    cout << "----UPDATED---- State: " << attrs.at(SwitchServer::IS_ON_ATTR).toString() << "-----------" << endl;
    isOn = attrs.at(SwitchServer::IS_ON_ATTR).toString() == "true";
    for(OnAttrChangeListener* listener : listeners){
        listener->onAttrChanged();
    }

}

void SwitchResource::callService(const string &service) {
    int serviceId = getServiceId(service);

    switch(serviceId){
        case NOT_FOUND:
            //TODO throw exception
            break;
        case TURN_ON:
            turnOn();
            break;
        case TURN_OFF:
            turnOff();
            break;
        case GET:
            serviceReturnStorage = getState();
            break;
    }
}

void SwitchResource::turnOn() {
    waitForUpdate();
    RCSResourceAttributes attribute;
    attribute[SwitchServer::IS_ON_ATTR] = true;
    resource->setRemoteAttributes(attribute, setCallback);
    isWaitingForUpdate = true;
}

void SwitchResource::turnOff() {
    waitForUpdate();
    RCSResourceAttributes attribute;
    attribute[SwitchServer::IS_ON_ATTR] = false;
    resource->setRemoteAttributes(attribute, setCallback);
    isWaitingForUpdate = true;
}

SwitchResource::SwitchResource(ResourceArgumentsBundle args) {
    isOn = false;
    init(args.resources.back());
    resource->getRemoteAttributes(getCallback);
    cout << "......."  << isOn << endl;
}

int SwitchResource::getState() {
    waitForUpdate();
    return isOn;
}

SwitchResource::~SwitchResource() {
    resource->stopCaching();
}



















