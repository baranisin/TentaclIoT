#ifndef IOTIVITY_BAKALARKA_VIRTUALSERVER_H
#define IOTIVITY_BAKALARKA_VIRTUALSERVER_H

#include <exceptions/ForbiddenForVirtualResException.h>
#include "Server.h"
#include "ResourceRepresentation.h"

class VirtualResourceRepr : public ResourceRepresentation{
protected:
    const bool isVirtual = true;
    Server *virtualServer;
    void init(const unsigned int id, RCSRemoteResourceObject::Ptr r) throw(ForbiddenForVirtualResException){
        throw ForbiddenForVirtualResException();
    };
    void init(const unsigned int id, DiscoveryThread &dt){
        resourceId = id;
        virtualServer = createVirtualServer();
        sleep(SECONDS_TO_SLEEP_DISCOVERY);
        resource = dt.getResource(virtualServer->getResourceURI());
    }
public:
    virtual Server* createVirtualServer() = 0;
    bool virtualServerIsRequired(){ return isVirtual;}
};

#endif //IOTIVITY_BAKALARKA_VIRTUALSERVER_H
