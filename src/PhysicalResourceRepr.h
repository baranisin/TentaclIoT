#ifndef IOTIVITY_BAKALARKA_PHYSICALSERVER_H
#define IOTIVITY_BAKALARKA_PHYSICALSERVER_H

#include <exceptions/ForbiddenForPhysicalResException.h>
#include "ResourceRepresentation.h"

class PhysicalResourceRepr : public ResourceRepresentation{
protected:
    const bool isVirtual = false;
    virtual void init(const unsigned int id, RCSRemoteResourceObject::Ptr r){
        resourceId = id;
        resource = r;
        initCallbacks();
        resource->startCaching(cacheCallback);
    }
    void init(const unsigned int id, DiscoveryThread &dt){
        throw ForbiddenForPhysicalResException();
    };
public:
    bool virtualServerIsRequired(){return isVirtual;}
};


#endif //IOTIVITY_BAKALARKA_PHYSICALSERVER_H
