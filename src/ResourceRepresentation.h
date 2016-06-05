#ifndef IOTIVITY_BAKALARKA_RESOURCEREPRESENTATION_H
#define IOTIVITY_BAKALARKA_RESOURCEREPRESENTATION_H

#include <exceptions/NullPtrException.h>
#include "RCSRemoteResourceObject.h"
#include "Server.h"
#include "DiscoveryThread.h"
#include "OnAttrChangeListener.h"

using namespace OC;
using namespace OIC::Service;
using namespace std;

class ResourceRepresentation {
protected:
    RCSRemoteResourceObject::Ptr resource;
    vector<pair<string, bool>> services;
    vector<OnAttrChangeListener*> listeners;
    int serviceArgumentStorage;
    int serviceReturnStorage;
    RCSRemoteResourceObject::RemoteAttributesSetCallback setCallback;
    RCSRemoteResourceObject::RemoteAttributesGetCallback getCallback;
    RCSRemoteResourceObject::CacheUpdatedCallback cacheCallback;

    virtual void onAttrSet(const RCSResourceAttributes &attrs, int eCode) = 0;

    virtual void onAttrGet(const RCSResourceAttributes &attrs, int eCode) = 0;

    virtual void onCacheUpdated(const RCSResourceAttributes &attrs) = 0;

    virtual void init(RCSRemoteResourceObject::Ptr r) = 0;

    virtual void init(DiscoveryThread &dt) = 0;

    virtual void defineServices() = 0;

    bool isWaitingForUpdate = false;

    virtual void waitForUpdate() {
        while (isWaitingForUpdate) {
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    };

    void initCallbacks() {
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
    };

    int getServiceId(const string &service){
        for (unsigned int i = 0; i < services.size(); i++){
            if (services.at(i).first == service){
                return i;
            }
        }
        return -1;
    }


public:
    virtual bool virtualServerIsRequired() = 0;

    virtual void callService(const string &service) = 0;

    string getAbsoluteUri() throw(NullPtrException) {
        return resource->getAddress() + resource->getUri();
    };

    bool hasType(const string &t) {
        if (resource == nullptr) {
            throw NullPtrException();
        }
        for (const string &type : resource->getTypes()) {
            if (t == type) {
                return true;
            }
        }
        return false;
    };

    vector<pair<string, bool>> getServices() {
        return services;
    };

    bool hasService(const string &serviceName) {
        for(const auto &ser : services){
            if(ser.first == serviceName){
                return true;
            }
        }
        return false;
    };

    void setServiceArgument(int argument){
        serviceArgumentStorage = argument;
    };

    int getServiceReturnStorage(){
        return serviceReturnStorage;
    };

    void registerOnAttrChangeListener(OnAttrChangeListener* listener){
        listeners.push_back(listener);
    };
};


#endif //IOTIVITY_BAKALARKA_RESOURCEREPRESENTATION_H
