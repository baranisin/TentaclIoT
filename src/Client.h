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
#include "Rule.h"

using namespace OC;
using namespace OIC::Service;
using namespace std;

#ifndef IOTIVITY_BAKALARKA_CLIENT_H
#define IOTIVITY_BAKALARKA_CLIENT_H


class Client {
private:
    DiscoveryThread* discoveryThread;
    map<string, ResourceRepresentation*> registeredResources;
    vector<Rule*> rules;
    Configuration config;
    void platformConfigure();

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

    void initRulesActivation();
};

#endif
