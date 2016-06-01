#include <RCSRemoteResourceObject.h>
#include "jsoncpp/json/json.h"
#include <iostream>
#include <fstream>

#ifndef IOTIVITY_BAKALARKA_CONFIGURATION_H
#define IOTIVITY_BAKALARKA_CONFIGURATION_H

using namespace OC;
using namespace OIC::Service;
using namespace std;

class Configuration {
    Json::Value receivedAttributes;


    Json::Value getJsonFromMap(map<string, RCSRemoteResourceObject::Ptr> map);
    Json::Value getJsonResource(string first, RCSRemoteResourceObject::Ptr second);
    Json::Value getResTypesToJson(RCSRemoteResourceObject::Ptr resPtr);
    Json::Value getResInterfacesToJson(RCSRemoteResourceObject::Ptr resPtr);
    void onRemoteAttributesReceived(const RCSResourceAttributes& attributes, int);

public:
    const string INPUT_FILE = "input.json";
    const string OUTPUT_FILE = "output.json";
    void writeOutput(
            map<string, RCSRemoteResourceObject::Ptr> discoveredResMap,
            map<string, RCSRemoteResourceObject::Ptr> regResources
    );
    void readInput();
};


#endif //IOTIVITY_BAKALARKA_CONFIGURATION_H
