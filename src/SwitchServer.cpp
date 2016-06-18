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
    resource->setAttribute(IS_ON_ATTR, false);
    resource->addAttributeUpdatedListener(IS_ON_ATTR, attributeUpdatedListener);
}

SwitchServer::SwitchServer(const string &n) {
    name = Server::nameValidation(n);

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
}

RCSSetResponse SwitchServer::onSetRequest(const RCSRequest& req, RCSResourceAttributes& attrs)
{
    std::cout << "Received a Set request from Client" << std::endl;
    printAttributes(attrs);
    if(device.isConfigured() && id){
        if (attrs.at(IS_ON_ATTR).toString() == "true"){
            device.turnOn(id);
        }else{
            device.turnOff(id);
        }
    }else{
        //TODO: Throw exception
    }

    return RCSSetResponse::defaultAction();
}

void SwitchServer::onAttrUpdated(const RCSResourceAttributes::Value &oldValue,
                                 const RCSResourceAttributes::Value &newValue) {
    cout << oldValue.toString() << " ---> " << newValue.toString() << endl;
    if(device.isConfigured() && id) {
        if (newValue.toString() == "true") {
            device.turnOn(id);
        } else {
            device.turnOff(id);
        }
    }else{
        //TODO: Throw exception
    }
}

void SwitchServer::setI2CDevice(I2CDevice d, uint8_t id) {
    device = d;
    this->id = id;
}















