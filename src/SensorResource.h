//
// Created by kingofwolwes on 21.6.2016.
//

#ifndef IOTIVITY_BAKALARKA_SENSORRESOURCE_H
#define IOTIVITY_BAKALARKA_SENSORRESOURCE_H


#include "PhysicalResourceRepr.h"
#include "ResourceArgumentsBundle.h"

class SensorResource : public PhysicalResourceRepr {
    bool isOn;
    enum {
        NOT_FOUND = -1,
        GET
    };
    void defineServices();
    void onAttrSet(const RCSResourceAttributes& attrs, int eCode);
    void onAttrGet(const RCSResourceAttributes& attrs, int eCode);
    void onCacheUpdated(const RCSResourceAttributes& attrs);

public:
    SensorResource(ResourceArgumentsBundle args);
    ~SensorResource();
    virtual void callService(const string &service);
    int getState();
};


#endif //IOTIVITY_BAKALARKA_SENSORRESOURCE_H
