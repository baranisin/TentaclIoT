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

    Json::Value getJsonFromMap(map<string, RCSRemoteResourceObject::Ptr> map);
    Json::Value getJsonResource(string first, RCSRemoteResourceObject::Ptr second);

public:
//    Configuration();
    const string INPUT_FILE = "input.json";
    const string OUTPUT_FILE = "output.json";
    void writeOutput(
            map<string, RCSRemoteResourceObject::Ptr> regResources,
            vector<pair<string, RCSRemoteResourceObject::Ptr>> discoveredResMap
    );
    void readInput();
};


#endif //IOTIVITY_BAKALARKA_CONFIGURATION_H
