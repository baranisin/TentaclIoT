#include "ResourceRepresentationBuilder.h"
#include "ImplementedResourceTypes.h"

ResourceRepresentationBuilder::ResourceRepresentationBuilder(DiscoveryThread *dt, const string &type) {
    arguments.discovery = dt;
    resType = type;
}

ResourceRepresentation *ResourceRepresentationBuilder::build() {
    ResourceRepresentation *representation = ImplementedResourceTypes::createResourceRepresentationOfType(resType,
                                                                                                         arguments);
    return representation;
}

ResourceRepresentationBuilder &ResourceRepresentationBuilder::addResource(RCSRemoteResourceObject::Ptr resPtr) {
    arguments.resources.push_back(resPtr);
    return *this;
}

ResourceRepresentationBuilder &ResourceRepresentationBuilder::setName(const string &name) {
    arguments.resName = name;
    return *this;
}

ResourceRepresentationBuilder &ResourceRepresentationBuilder::setId(const unsigned int &id) {
    arguments.resId = id;
    return *this;
}















