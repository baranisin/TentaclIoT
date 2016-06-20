//
// Created by kingofwolwes on 20.6.2016.
//

#include "SensorServer.h"

const string SensorServer::SENSOR_URI = "/sensor";
const string SensorServer::IS_ON_ATTR = "is_turned_on";

SensorServer::SensorServer(const string &n) {
    name = Server::nameValidation(n);
    setRequestHandler = bind(
            &SensorServer::onSetRequest,
            this,
            placeholders::_1,
            placeholders::_2
    );

    attributeUpdatedListener = bind(
            &SensorServer::onAttrUpdated,
            this,
            placeholders::_1,
            placeholders::_2
    );

    initServer(SENSOR_URI, OIC_SWITCH_TYPE);
}

void SensorServer::buildServer(const string &rUri, const string &resourceType) {
    resource = RCSResourceObject::Builder(rUri, resourceType, ACTUATOR_INTERFACE)
            .addInterface(SWITCH_INTERFACE)
            .addInterface(SENSOR_INTERFACE)
            .setDefaultInterface(BASELINE_INTERFACE)
            .setDiscoverable(true)
            .setObservable(true)
            .build();

    resource->setAutoNotifyPolicy(RCSResourceObject::AutoNotifyPolicy::UPDATED);
    resource->setSetRequestHandlerPolicy(RCSResourceObject::SetRequestHandlerPolicy::NEVER);

    resource->setAttribute(IS_ON_ATTR, false);
    resource->addAttributeUpdatedListener(IS_ON_ATTR, attributeUpdatedListener);
}

void SensorServer::setI2CDevice(I2CDevice *d, uint8_t id) {
    device = d;
    this->id = id;
    device->registerEventListener(this);
}

void SensorServer::onAttrUpdated(const RCSResourceAttributes::Value &oldValue,
                                 const RCSResourceAttributes::Value &newValue) {
    cout << oldValue.toString() << " ---> " << newValue.toString() << endl;
}
RCSSetResponse SensorServer::onSetRequest(const RCSRequest& req, RCSResourceAttributes& attrs)
{
    std::cout << "Received a Set request from Client" << std::endl;
    printAttributes(attrs);

    return RCSSetResponse::defaultAction();
}

void SensorServer::onEvent(int newValue) {
    cout <<  "OnEvent listener: "  << newValue <<endl;
    resource->setAttribute(IS_ON_ATTR, (bool) newValue);
    this_thread::sleep_for(chrono::milliseconds(500));
    cout <<  "OnEvent listener get value: "  << resource->getAttribute(IS_ON_ATTR) <<endl;
}









