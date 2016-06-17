#include "SceneServer.h"

const string SceneServer::STATE_ATTR = "stateOn";
const string SceneServer::SCENE_URI = "/scene";


void SceneServer::buildServer(const string &rUri, const string &resourceType) {
    resource = RCSResourceObject::Builder(rUri, resourceType, ACTUATOR_INTERFACE)
            .addInterface(SWITCH_INTERFACE)
            .setDefaultInterface(BASELINE_INTERFACE)
            .setDiscoverable(true)
            .setObservable(true)
            .build();

    resource->setAutoNotifyPolicy(RCSResourceObject::AutoNotifyPolicy::UPDATED);
    resource->setSetRequestHandlerPolicy(RCSResourceObject::SetRequestHandlerPolicy::NEVER);
}

SceneServer::SceneServer(const string &n) {
    name = Server::nameValidation(n);
    initServer(SCENE_URI, SCENE_TYPE);
    resource->setAttribute(STATE_ATTR, false);
}



