#include "PhysicalResourceRepr.h"
#include "LightServer.h"
#include "ResourceArgumentsBundle.h"
#include <exceptions/CacheNotAvailableException.h>

#ifndef IOTIVITY_BAKALARKA_LIGHTRESOURCE_H
#define IOTIVITY_BAKALARKA_LIGHTRESOURCE_H


class LightResource : public PhysicalResourceRepr{
    int brightnessValue;
    void defineServices();
    enum servicesIds{
        NOT_FOUND = -1,
        TURN_ON,
        TURN_OFF,
        RAISE,
        LOW,
        GET,
        SET,
    };

    void onAttrSet(const RCSResourceAttributes& attrs, int eCode);
    void onAttrGet(const RCSResourceAttributes& attrs, int eCode);
    void onCacheUpdated(const RCSResourceAttributes& attrs);
public:
    LightResource(ResourceArgumentsBundle args);
    ~LightResource();
    void set(RCSResourceAttributes attrs);
    void turnOff();
    void turnOn();
    int getBrightness();
    void setBrightness(const int value);
    void raiseBrightness();
    void lowBrightness();
    void onBrightnessChanged();
    void callService(const string &service);
};


#endif //IOTIVITY_BAKALARKA_LIGHTRESOURCE_H
