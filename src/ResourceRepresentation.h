#include <exceptions/NullPtrException.h>
#include "RCSRemoteResourceObject.h"
#include "Server.h"
#include "DiscoveryThread.h"

using namespace OC;
using namespace OIC::Service;
using namespace std;

#ifndef IOTIVITY_BAKALARKA_RESOURCEREPRESENTATION_H
#define IOTIVITY_BAKALARKA_RESOURCEREPRESENTATION_H


class ResourceRepresentation {
protected:
    RCSRemoteResourceObject::Ptr resource;
    RCSRemoteResourceObject::RemoteAttributesSetCallback setCallback;
    RCSRemoteResourceObject::RemoteAttributesGetCallback getCallback;
    RCSRemoteResourceObject::CacheUpdatedCallback cacheCallback;
    virtual void onAttrSet(const RCSResourceAttributes& attrs, int eCode) = 0;
    virtual void onAttrGet(const RCSResourceAttributes& attrs, int eCode) = 0;
    virtual void onCacheUpdated(const RCSResourceAttributes& attrs) = 0;
    virtual void init(RCSRemoteResourceObject::Ptr r) = 0;
    virtual void init(DiscoveryThread &dt) = 0;

    bool isWaitingForUpdate = false;
    virtual void waitForUpdate(){
        while(isWaitingForUpdate){
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    };
    void initCallbacks(){
        setCallback = bind(
                &ResourceRepresentation::onAttrSet,
                this,
                placeholders::_1,
                placeholders::_2
        );

        getCallback = bind(
                &ResourceRepresentation::onAttrGet,
                this,
                placeholders::_1,
                placeholders::_2
        );

        cacheCallback = bind(
                &ResourceRepresentation::onCacheUpdated,
                this,
                placeholders::_1
        );
    }
public:
    virtual bool virtualServerIsRequired() = 0;
    string getAbsoluteUri() throw(NullPtrException){
        return resource->getAddress()+"/"+resource->getUri();
    };

    bool hasType(const string &t){
        if(resource == nullptr){
            throw NullPtrException();
        }
        for(const string &type : resource->getTypes()){
            if(t == type){
                return true;
            }
        }
        return false;
    }
};


#endif //IOTIVITY_BAKALARKA_RESOURCEREPRESENTATION_H
