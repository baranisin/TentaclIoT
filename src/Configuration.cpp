
#include "Configuration.h"

void Configuration::writeOutput(
        map<string, RCSRemoteResourceObject::Ptr> regResourcesMap,
        map<string, RCSRemoteResourceObject::Ptr> discoveredResMap){
    Json::StyledWriter writer;
    Json::Value resourcesJson;
    resourcesJson["discovered_resources"] = getJsonFromMap(discoveredResMap);

    ofstream outputFile;
    outputFile.open(OUTPUT_FILE.c_str(), ios::out);

    if(outputFile.is_open()){
        outputFile <<  "FILE" << endl;
        cout << "---------------------------" << endl;
        cout << writer.write(resourcesJson) << endl;
        cout << "---------------------------" << endl;
        cout << "---------------------------" << endl;

        outputFile << writer.write(resourcesJson) << endl;
        outputFile.flush();
        outputFile.close();
    }
}

Json::Value Configuration::getJsonFromMap(map<string, RCSRemoteResourceObject::Ptr> map){
    Json::Value mapJson(Json::arrayValue);
    for(std::map<string,RCSRemoteResourceObject::Ptr>::iterator it=map.begin(); it!=map.end(); ++it){
        Json::Value res = getJsonResource(it->first, it->second);
        mapJson.append(res);
    }
    return mapJson;
};

Json::Value Configuration::getJsonResource(string first, RCSRemoteResourceObject::Ptr second){
    Json::Value resourceJson;
    resourceJson["absolute_uri"] = first;
    Json::Value types(Json::arrayValue);
    Json::Value ifaces(Json::arrayValue);

    for(string &type : second->getTypes()) {
        types.append(Json::Value(type));
    }
    resourceJson["types"] = types;

    for (string &iface : second->getInterfaces()) {
        ifaces.append(Json::Value(iface));
    }
    resourceJson["interfaces"] = ifaces;

    return resourceJson;
}

void Configuration::readInput(){

}