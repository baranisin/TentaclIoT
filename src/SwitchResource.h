//
// Created by kingofwolwes on 17.6.2016.
//

#ifndef IOTIVITY_BAKALARKA_SWITCHRESOURCE_H
#define IOTIVITY_BAKALARKA_SWITCHRESOURCE_H


#include "PhysicalResourceRepr.h"
#include "ResourceArgumentsBundle.h"

class SwitchResource : public PhysicalResourceRepr{
    bool isOn;
    enum servicesIds{
        NOT_FOUND = -1,
        TURN_ON,
        TURN_OFF,
        GET
    };
    void defineServices();
    void onAttrSet(const RCSResourceAttributes& attrs, int eCode);
    void onAttrGet(const RCSResourceAttributes& attrs, int eCode);
    void onCacheUpdated(const RCSResourceAttributes& attrs);
public:
    SwitchResource(ResourceArgumentsBundle args);
    void callService(const string &service);
    void turnOn();
    void turnOff();
};


#endif //IOTIVITY_BAKALARKA_SWITCHRESOURCE_H
