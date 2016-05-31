#include "LightServer.h"

const string LightServer::LIGHT_URI = "/a/light";
const string LightServer::BRIGHTNESS_ATTR = "Brightness";
const int LightServer::ZERO_BRIGHTNESS = 0;
const int LightServer::MAX_BRIGHTNESS = 100;
const int LightServer::STAGE_OF_BRIGHTNESS = 10;

LightServer::LightServer(const string &n) {
    name = Server::nameValidation(n);
    initServer(LIGHT_URI, OIC_LIGHT_TYPE);
    resource->setAttribute(BRIGHTNESS_ATTR, ZERO_BRIGHTNESS);
}

void LightServer::buildServer(const string &rUri, const string &resourceType) {
    resource = RCSResourceObject::Builder(rUri, resourceType, ACTUATOR_INTERFACE)
            .addInterface(CUSTOM_INTERFACE)
            .addInterface(SENSOR_INTERFACE)
            .setDefaultInterface(BASELINE_INTERFACE)
            .setDiscoverable(true)
            .setObservable(true)
            .build();

    resource->setAutoNotifyPolicy(RCSResourceObject::AutoNotifyPolicy::UPDATED);
    resource->setSetRequestHandlerPolicy(RCSResourceObject::SetRequestHandlerPolicy::NEVER);
}

