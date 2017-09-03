#include <condition_variable>

#include "TypeDefs.h"
#include "DiscoveryManager.h"

#ifndef IOTIVITY_BAKALARKA_CLIENT_H
#define IOTIVITY_BAKALARKA_CLIENT_H

class Client {
private:
    void configurePlaform();

    void stopPlatform();
public:
    Client();
};

#endif
