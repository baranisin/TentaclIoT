#include <RCSRemoteResourceObject.h>
#include "jsoncpp/json/json.h"
#include "ResourceRepresentation.h"
#include <iostream>
#include <fstream>

#ifndef IOTIVITY_BAKALARKA_CONFIGURATION_H
#define IOTIVITY_BAKALARKA_CONFIGURATION_H

using namespace OC;
using namespace OIC::Service;
using namespace std;
struct ConfigReturnArguments{
    string name;
    string uri;
    string type;
};

class Configuration {
    Json::Value receivedAttributes;


    Json::Value getDiscoveredResJson(map<string, RCSRemoteResourceObject::Ptr> map);
    Json::Value getJsonRemoteResource(string first, RCSRemoteResourceObject::Ptr second);
    Json::Value getResTypesToJson(RCSRemoteResourceObject::Ptr resPtr);
    Json::Value getResInterfacesToJson(RCSRemoteResourceObject::Ptr resPtr);
    void onRemoteAttributesReceived(const RCSResourceAttributes& attributes, int);

    Json::Value getRegisteredResJson(map<string, ResourceRepresentation*> map);
    Json::Value getJsonResourceRepr(string first, ResourceRepresentation* second);


public:
    static const string INPUT_FILE;
    static const string OUTPUT_FILE;

    static const string DISCOVERED_RESOURCES_KEY;
    static const string REGISTERED_RESOURCES_KEY;
    static const string RES_TO_REGISTER_KEY;

    static const string ABSOLUTE_URI_KEY;
    static const string TYPES_KEY;
    static const string REPR_TYPE_KEY;
    static const string INTERFACES_KEY;
    static const string RELATIVE_URI_KEY;
    static const string ADRESS_KEY;
    static const string STATE_KEY;
    static const string ATTRIBUTES_KEY;
    static const string ID_KEY;
    static const string IS_VIRTUAL_TYPE_KEY;
    static const string SOURCE_SERVERS_URIS_KEY;
    void writeOutput(
            map<string, RCSRemoteResourceObject::Ptr> discoveredResMap,
            map<string, ResourceRepresentation*> regResources
    );
    vector< pair< vector<string>, string> > readInput();
};


#endif //IOTIVITY_BAKALARKA_CONFIGURATION_H
