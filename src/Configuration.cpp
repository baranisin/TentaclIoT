#include <thread>
#include "Configuration.h"

const string Configuration::INPUT_FILE = "input.json";
const string Configuration::OUTPUT_FILE = "output.json";

const string Configuration::DISCOVERED_RESOURCES_KEY = "discovered_resources";
const string Configuration::REGISTERED_RESOURCES_KEY = "registered_resources";
const string Configuration::RES_TO_REGISTER_KEY = "resources_to_register";

const string Configuration::ABSOLUTE_URI_KEY = "absolute_uri";
const string Configuration::TYPES_KEY = "types";
const string Configuration::REPR_TYPE_KEY = "representation_type";
const string Configuration::INTERFACES_KEY = "interfaces";
const string Configuration::RELATIVE_URI_KEY = "relative_uri";
const string Configuration::ADRESS_KEY = "adress";
const string Configuration::STATE_KEY = "state";
const string Configuration::ATTRIBUTES_KEY = "attributes";
const string Configuration::ID_KEY = "id";
const string Configuration::IS_VIRTUAL_TYPE_KEY = "is_virtual";
const string Configuration::SOURCE_SERVERS_URIS_KEY = "source_uris";
const string Configuration::SERVICES_KEY  = "services";
const string Configuration::SERVICE_NAME_KEY  = "service_name";
const string Configuration::REQUIRE_ARGUMENT_KEY  = "require_argument";


void Configuration::writeOutput(
        map<string, RCSRemoteResourceObject::Ptr> discoveredResMap,
        map<string, ResourceRepresentation*> regResourcesMap){
    Json::StyledWriter writer;
    Json::Value resourcesJson;
    resourcesJson[DISCOVERED_RESOURCES_KEY] = getDiscoveredResJson(discoveredResMap);
    resourcesJson[REGISTERED_RESOURCES_KEY] = getRegisteredResJson(regResourcesMap);

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
            resourceJson[ABSOLUTE_URI_KEY] = first;
            resourceJson[TYPES_KEY] = getResTypesToJson(second);
            resourceJson[INTERFACES_KEY] = getResInterfacesToJson(second);
            resourceJson[RELATIVE_URI_KEY] = second->getUri();
            resourceJson[ADRESS_KEY] = second->getAddress();
            resourceJson[STATE_KEY] = (int) second->getState();
            resourceJson[ATTRIBUTES_KEY] = receivedAttributes;
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

            Json::Value Configuration::getResInterfacesToJson(RCSRemoteResourceObject::Ptr resPtr) {
                Json::Value ifaces(Json::arrayValue);
                for (string &iface : resPtr->getInterfaces()) {
                    ifaces.append(Json::Value(iface));
                }
                return ifaces;
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
        resourceJson[ABSOLUTE_URI_KEY] = first;
        resourceJson[IS_VIRTUAL_TYPE_KEY] = second->virtualServerIsRequired();
        Json::Value services(Json::arrayValue);
        for(auto &service : second->getServices()){
            Json::Value serviceJson;
            serviceJson[SERVICE_NAME_KEY] = service.first;
            serviceJson[REQUIRE_ARGUMENT_KEY] = service.second;
            services.append(serviceJson);
        }
        resourceJson[SERVICES_KEY] = services;
        return resourceJson;
    }



vector<pair<vector<string>, string>> Configuration::readInput(){
    ifstream inputFile;
    Json::Reader reader;
    Json::Value inputJson;
    inputFile.open(INPUT_FILE.c_str(), ios::in);

    if(inputFile.is_open()){
        if(reader.parse(inputFile, inputJson)){
            vector<pair<vector<string>, string>> resourcesToRegister;

            for(Json::Value resourceJson : inputJson[RES_TO_REGISTER_KEY]){
                pair<vector<string>, string> arguments;
                vector<string> uris;

                for(const Json::Value &sourceUri : resourceJson[SOURCE_SERVERS_URIS_KEY]){
                    uris.push_back(sourceUri.asString());
                }

                arguments.first = uris;
                arguments.second = resourceJson[REPR_TYPE_KEY].asString();

                resourcesToRegister.push_back(arguments);
            }
            return resourcesToRegister;
        }
    }
}










