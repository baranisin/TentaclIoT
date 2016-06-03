#include <thread>
#include "Configuration.h"

void Configuration::writeOutput(
        map<string, RCSRemoteResourceObject::Ptr> discoveredResMap,
        map<string, ResourceRepresentation*> regResourcesMap){
    Json::StyledWriter writer;
    Json::Value resourcesJson;
    resourcesJson["discovered_resources"] = getDiscoveredResJson(discoveredResMap);
    resourcesJson["registered_resources"] = getRegisteredResJson(regResourcesMap);

    ofstream outputFile;
    outputFile.open(OUTPUT_FILE.c_str(), ios::out | ios::trunc);

    if(outputFile.is_open()){
        outputFile << writer.write(resourcesJson) << endl;
        outputFile.close();
    }else{

    }
}

    Json::Value Configuration::getDiscoveredResJson(map<string, RCSRemoteResourceObject::Ptr> map){
        Json::Value mapJson(Json::arrayValue);
        for(std::map<string,RCSRemoteResourceObject::Ptr>::iterator it=map.begin(); it!=map.end(); ++it){
            Json::Value res = getJsonRemoteResource(it->first, it->second);
            mapJson.append(res);
        }
        return mapJson;
    };

        Json::Value Configuration::getJsonRemoteResource(string first, RCSRemoteResourceObject::Ptr second){
            RCSRemoteResourceObject::RemoteAttributesGetCallback onReceivedCallback = bind(
                    &Configuration::onRemoteAttributesReceived,
                    this,
                    placeholders::_1,
                    placeholders::_2
            );
            second->getRemoteAttributes(onReceivedCallback);
            this_thread::sleep_for(chrono::milliseconds(100));

            Json::Value resourceJson;
            resourceJson["absolute_uri"] = first;
            resourceJson["types"] = getResTypesToJson(second);
            resourceJson["interfaces"] = getResInterfacesToJson(second);
            resourceJson["relative_uri"] = second->getUri();
            resourceJson["adress"] = second->getAddress();
            resourceJson["state"] = (int) second->getState();
            resourceJson["attributes"] = receivedAttributes;
            return resourceJson;
        }

            void Configuration::onRemoteAttributesReceived(const RCSResourceAttributes& attributes, int){
                Json::Value attributesJson;
                for(auto &attr : attributes){
                    attributesJson[attr.key()] = attr.value().toString();
                }
                receivedAttributes = attributesJson;
            }

            Json::Value Configuration::getResTypesToJson(RCSRemoteResourceObject::Ptr resPtr){
                Json::Value types(Json::arrayValue);
                for(string &type : resPtr->getTypes()) {
                    types.append(Json::Value(type));
                }
                return types;
            }

Json::Value Configuration::getRegisteredResJson(map<string, ResourceRepresentation*>  map){
    Json::Value mapJson(Json::arrayValue);
    for(std::map<string, ResourceRepresentation*>::iterator it=map.begin(); it!=map.end(); ++it){
        Json::Value res = getJsonResourceRepr(it->first, it->second);
        mapJson.append(res);
    }
    return mapJson;
}

Json::Value Configuration::getJsonResourceRepr(string first, ResourceRepresentation* second){
    Json::Value resourceJson;
    resourceJson["absolute_uri"] = first;
    resourceJson["id"] = second->getResourceId();
    resourceJson["virtual_type"] = second->virtualServerIsRequired();
    return resourceJson;
}

Json::Value Configuration::getResInterfacesToJson(RCSRemoteResourceObject::Ptr resPtr) {
    Json::Value ifaces(Json::arrayValue);
    for (string &iface : resPtr->getInterfaces()) {
        ifaces.append(Json::Value(iface));
    }
    return ifaces;
}

vector<pair<string, string>> Configuration::readInput(){
    ifstream inputFile;
    Json::Reader reader;
    Json::Value inputJson;
    inputFile.open(INPUT_FILE.c_str(), ios::in);
    if(inputFile.is_open()){
        if(reader.parse(inputFile, inputJson)){
            vector<pair<string, string>> resourcesToRegister;
            for(Json::Value resourceJson : inputJson["register_resources"]){
                pair<string, string> arguments;
                arguments.first = resourceJson["relative_uri"].asString();
                arguments.second = resourceJson["type"].asString();

                resourcesToRegister.push_back(arguments);
            }
            return resourcesToRegister;
        }
    }
}










