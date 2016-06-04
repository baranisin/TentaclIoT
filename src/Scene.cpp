#include "Scene.h"
#include "ImplementedResourceTypes.h"

Scene::Scene(ResourceArgumentsBundle args) {
    init(*args.discovery);
    resources = args.resources;
    serverName = args.resName;
    isOn = false;
}

Server *Scene::createVirtualServer() {
    return ImplementedResourceTypes::createServerOfType(OIC_SCENE_TYPE, serverName);
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











