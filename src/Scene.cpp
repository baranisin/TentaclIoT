#include "Scene.h"
#include "ImplementedResourceTypes.h"

Scene::Scene(ResourceArgumentsBundle args) {
    init(*args.discovery);
    resources = args.resources;
    serverName = args.resName;
    isOn = false;
}

Server *Scene::createVirtualServer() {
    return ImplementedResourceTypes::createServerOfType(SCENE_TYPE, serverName);
}

void Scene::onAttrSet(const RCSResourceAttributes &attrs, int eCode) {
    cout << "----SET----" << endl;
}

void Scene::onAttrGet(const RCSResourceAttributes &attrs, int eCode) {
    cout << "----GET----" << endl;
}

void Scene::turnOff() {
    RCSResourceAttributes attrsZeroValue;
    for (const auto &attr : attrConfig){
        attrsZeroValue[attr.key()] = 0;
    }

    for(const auto &res : resources){
        res->setRemoteAttributes(attrsZeroValue, setCallback);
    }
}

void Scene::turnOn() {
    for(const auto &res : resources){
        res->setRemoteAttributes(attrConfig, setCallback);
    }
}

void Scene::defineServices() {
    pair<string, bool> turnOnService(TURN_ON_SERVICE_NAME, false);
    pair<string, bool> turnOffService(TURN_OFF_SERVICE_NAME, false);

    services.push_back(turnOnService);
    services.push_back(turnOffService);
}

void Scene::callService(const string &service) {
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
        default:
           //TODO throw exception
            break;
    }


}















