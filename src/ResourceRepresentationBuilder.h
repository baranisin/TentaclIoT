#ifndef IOTIVITY_BAKALARKA_REMOTERESOURCEBUILDER_H
#define IOTIVITY_BAKALARKA_REMOTERESOURCEBUILDER_H


#include "DiscoveryThread.h"
#include "ResourceRepresentation.h"
#include "ResourceArgumentsBundle.h"

class ResourceRepresentationBuilder {
    friend class ResReprBuilderTestFixture;
    ResourceArgumentsBundle arguments;
    string resType;

public:
    ResourceRepresentationBuilder(DiscoveryThread *dt, const string &type);
    ResourceRepresentationBuilder &addResource(RCSRemoteResourceObject::Ptr resPtr);
    ResourceRepresentationBuilder &setName(const string &name);
    ResourceRepresentation *build();
};


#endif //IOTIVITY_BAKALARKA_REMOTERESOURCEBUILDER_H
