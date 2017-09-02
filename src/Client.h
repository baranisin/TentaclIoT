#include <condition_variable>
#include <OCPlatform.h>

#include "Constants.h"

using namespace OC;
using namespace std;

#ifndef IOTIVITY_BAKALARKA_CLIENT_H
#define IOTIVITY_BAKALARKA_CLIENT_H

typedef std::map<OCResourceIdentifier, std::shared_ptr<OCResource>> ResourceMap;
typedef std::map<string, ResourceMap> DiscoveredHostMap;


class Client {
private:
    static mutex curResourceLock;
    DiscoveredHostMap discoveredHosts;

    FindCallback onResourceFoundCallback;
    FindDeviceCallback onDeviceFoundCallback;
    FindPlatformCallback onPlatformFoundCallback;

    void init();

    void onResourceFound(std::shared_ptr<OCResource> resource);

    void onDeviceFound(const OCRepresentation &representation);

    void onPlatformFound(const OCRepresentation &representation);

public:
    Client();
};

#endif
