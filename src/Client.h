#include <string>
#include <RCSAddress.h>
#include "RCSDiscoveryManager.h"
#include "RCSRemoteResourceObject.h"

#include "OCPlatform.h"
#include "Constants.h"
#include "DiscoveryThread.h"
#include "Server.h"
#include "Configuration.h"

using namespace OC;
using namespace OIC::Service;
using namespace std;

#ifndef IOTIVITY_BAKALARKA_CLIENT_H
#define IOTIVITY_BAKALARKA_CLIENT_H


class Client {
private:
    DiscoveryThread* discoveryThread = nullptr;
    map<string, RCSRemoteResourceObject::Ptr> registeredResources;
    Configuration *config;
    void platformConfigure();

public:
    Client();
    ~Client();

    void startDiscovery(const vector<string> &types = vector<string>{});

    void stopDiscovery();

    bool isDiscovering();

//    void outputActualConfiguration();

    void printActualDiscoveredResources();


    bool hasResourceDiscovered(const string &uri);

//    bool registerResources();

    bool hasResourceRegistered(const string &uri);
};

#endif
