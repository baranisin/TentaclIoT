#ifndef IOTIVITY_BAKALARKA_BUNDLE_H
#define IOTIVITY_BAKALARKA_BUNDLE_H

#include "DiscoveryThread.h"

struct ResourceArgumentsBundle{
    DiscoveryThread *discovery;
    vector<RCSRemoteResourceObject::Ptr> resources;
    string resName;
};

#endif //IOTIVITY_BAKALARKA_BUNDLE_H
