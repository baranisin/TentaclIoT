//
// Created by kingofwolwes on 17.6.2016.
//

#include "SwitchServer.h"

const string SwitchServer::SWITCH_URI = "/switch";
const string SwitchServer::IS_ON_ATTR = "is_turned_on";

void SwitchServer::buildServer(const string &rUri, const string &resourceType) {
    resource = RCSResourceObject::Builder(rUri, resourceType, ACTUATOR_INTERFACE)
            .addInterface(SWITCH_INTERFACE)
            .addInterface(SENSOR_INTERFACE)
            .setDefaultInterface(BASELINE_INTERFACE)
            .setDiscoverable(true)
            .setObservable(true)
            .build();

    resource->setAutoNotifyPolicy(RCSResourceObject::AutoNotifyPolicy::UPDATED);
    resource->setSetRequestHandlerPolicy(RCSResourceObject::SetRequestHandlerPolicy::NEVER);

    resource->setSetRequestHandler(setRequestHandler);
}

SwitchServer::SwitchServer(const string &n, I2CDevice d) {
    name = Server::nameValidation(n);
    device = d;
    setRequestHandler = bind(
            &SwitchServer::onSetRequest,
            this,
            placeholders::_1,
            placeholders::_2
    );
    attributeUpdatedListener = bind(
            &SwitchServer::onAttrUpdated,
            this,
            placeholders::_1,
            placeholders::_2
    );

    initServer(SWITCH_URI, OIC_SWITCH_TYPE);
    resource->setAttribute(IS_ON_ATTR, false);
    resource->addAttributeUpdatedListener(IS_ON_ATTR, attributeUpdatedListener);
}

RCSSetResponse SwitchServer::onSetRequest(const RCSRequest& req, RCSResourceAttributes& attrs)
{
    std::cout << "Received a Set request from Client" << std::endl;
    printAttributes(attrs);
    if (attrs.at(IS_ON_ATTR).toString() == "true"){
        device.turnOn(1);
        device.turnOn(2);
        device.turnOn(3);
        device.turnOn(4);
    }
    return RCSSetResponse::defaultAction();
}

void SwitchServer::test() {
    cout << " .... " << endl;
    resource->setAttribute(IS_ON_ATTR, true);
}

void SwitchServer::onAttrUpdated(const RCSResourceAttributes::Value &oldValue,
                                 const RCSResourceAttributes::Value &newValue) {
    cout << oldValue.toString() << " .... " << newValue.toString() << endl;
    if (newValue.toString() == "true"){
        device.turnOn(1);
        device.turnOn(2);
        device.turnOn(3);
        device.turnOn(4);
    }
}













