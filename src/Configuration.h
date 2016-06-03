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
    const string INPUT_FILE = "input.json";
    const string OUTPUT_FILE = "output.json";
    void writeOutput(
            map<string, RCSRemoteResourceObject::Ptr> discoveredResMap,
            map<string, ResourceRepresentation*> regResources
    );
    vector<pair<string, string>> readInput();
};


#endif //IOTIVITY_BAKALARKA_CONFIGURATION_H
