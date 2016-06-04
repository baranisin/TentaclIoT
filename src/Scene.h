#ifndef IOTIVITY_BAKALARKA_SCENE_H
#define IOTIVITY_BAKALARKA_SCENE_H


#include "VirtualResourceRepr.h"
#include "ResourceArgumentsBundle.h"

class Scene : public VirtualResourceRepr {
    string serverName;
    vector<RCSRemoteResourceObject::Ptr> resources;
    RCSResourceAttributes attrConfig;
    void onAttrSet(const RCSResourceAttributes& attrs, int eCode);
    void onAttrGet(const RCSResourceAttributes& attrs, int eCode);
    void onCacheUpdated(const RCSResourceAttributes& attrs){};

public:
    bool isOn;
    Scene(ResourceArgumentsBundle args);
    Server* createVirtualServer();
    void turnOff();
    void turnOn();

};


#endif //IOTIVITY_BAKALARKA_SCENE_H
