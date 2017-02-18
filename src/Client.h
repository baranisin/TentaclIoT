#include <string>
#include <RCSAddress.h>
#include "RCSDiscoveryManager.h"
#include "RCSRemoteResourceObject.h"

#include "OCPlatform.h"
#include "Constants.h"
#include "DiscoveryThread.h"
#include "Server.h"
#include "Configuration.h"
#include "ResourceRepresentation.h"
#include "ImplementedResourceTypes.h"
#include "ResourceRepresentationBuilder.h"

using namespace OC;
using namespace OIC::Service;
using namespace std;

#ifndef IOTIVITY_BAKALARKA_CLIENT_H
#define IOTIVITY_BAKALARKA_CLIENT_H


class Client {
private:
    unique_ptr<RCSDiscoveryManager::DiscoveryTask> discoveryTask;
    map<string, RCSRemoteResourceObject::Ptr> discoveredResources;
    map<string, ResourceRepresentation*> registeredResources;
    Configuration *config;
    void platformConfigure();

    void onResourceDiscovered(shared_ptr<RCSRemoteResourceObject> discoveredResource);

public:
    Client();
    ~Client();

    void startDiscovery(const vector<string> &types = vector<string>{});

    void stopDiscovery();

    bool isDiscovering();

    void outputActualConfiguration();

    void printActualDiscoveredResources();

    void printRegisteredResources();

    bool hasResourceDiscovered(const string &uri);

    void loadConfiguration();

    void registerResourceFromDiscovery(const vector<string> &uris, const string &type = DEFAULT_STRING);

    bool hasResourceRegistered(const string &uri);

    void setRules(Json::Value json);

    map<string, RCSRemoteResourceObject::Ptr> getDiscoveredResources();

    RCSRemoteResourceObject::Ptr getResource(
            const string &uri) throw(NotInDiscoveredResException, MoreResWithSameURIException);

    bool hasResource(const string &uri);

    unsigned int countDiscoveredResWithURI(const string &uri);

    string findDiscoveredResource(const string &uri);
};

#endif
