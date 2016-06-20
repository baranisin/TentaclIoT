//
// Created by kingofwolwes on 20.6.2016.
//

#ifndef IOTIVITY_BAKALARKA_SENSORSERVER_H
#define IOTIVITY_BAKALARKA_SENSORSERVER_H


#include <I2CEventListener.h>
#include <I2CDevice.h>
#include "Server.h"

class SensorServer : public Server, public I2CEventListener{
    I2CDevice device;
    uint8_t id;
    RCSResourceObject::SetRequestHandler setRequestHandler;
    RCSResourceObject::AttributeUpdatedListener attributeUpdatedListener;

    void onAttrUpdated(const RCSResourceAttributes::Value& oldValue, const RCSResourceAttributes::Value& newValue);

    virtual void buildServer(const string &rUri, const string &resourceType);

public:
    SensorServer(const string &n);
    void setI2CDevice(I2CDevice d, uint8_t id);
    virtual void onEvent(int newValue);

    static const string SENSOR_URI;
    static const string IS_ON_ATTR;
};


#endif //IOTIVITY_BAKALARKA_SENSORSERVER_H
