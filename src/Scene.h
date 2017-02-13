#ifndef IOTIVITY_BAKALARKA_SCENE_H
#define IOTIVITY_BAKALARKA_SCENE_H


#include "VirtualResourceRepr.h"
#include "ResourceArgumentsBundle.h"

class Scene : public VirtualResourceRepr {
    enum servicesIds{
        NOT_FOUND = -1,
        TURN_ON,
        TURN_OFF
    };

    string serverName;
    vector<RCSRemoteResourceObject::Ptr> resources;
    RCSResourceAttributes attrConfig;
    void onAttrSet(const RCSResourceAttributes& attrs, int eCode);
    void onAttrGet(const RCSResourceAttributes& attrs, int eCode);
    void onCacheUpdated(const RCSResourceAttributes& attrs){};
    void defineServices();
public:
    bool isOn;
    Scene(ResourceArgumentsBundle args);
    Server* createVirtualServer();
    void turnOff();
    void turnOn();
    void callService(const string &service);

};


#endif //IOTIVITY_BAKALARKA_SCENE_H
