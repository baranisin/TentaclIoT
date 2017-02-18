#include "Client.h"
#include "Rule.h"

Client::Client() {
    platformConfigure();
    registeredResources = map<string, ResourceRepresentation*>{};
    discoveredResources = map<string, RCSRemoteResourceObject::Ptr>{};
    config = new Configuration();
}

void Client::platformConfigure() {
    try {

        PlatformConfig config{
                OC::ServiceType::InProc,
                ModeType::Both,
                ALL_AVALAIBLE_INTERFACES,
                RANDOMLY_AVALAIBLE_PORT,
                OC::QualityOfService::LowQos
        };
        OCPlatform::Configure(config);

    }catch (RCSPlatformException e){
        cout << e.getReason() << endl;
    }
}

void Client::outputActualConfiguration()  {
    if(isDiscovering()){
        config->writeOutput(discoveredResources, registeredResources);

        printActualDiscoveredResources();
    }
}

void Client::printActualDiscoveredResources(){
    for (const auto &res : discoveredResources) {
        std::cout << "URI: " << res.second->getUri() << " has resource " << res.first << std::endl;
    }
}

bool Client::hasResourceDiscovered(const string &uri) {

}

void Client::startDiscovery(const vector<string> &types) {
    function<void(shared_ptr<RCSRemoteResourceObject>)> onResourceDiscoveredCallback;
    onResourceDiscoveredCallback = bind(
            &onResourceDiscovered,
            this,
            placeholders::_1
    );
    while (!discoveryTask) {
        try {
            discoveryTask = RCSDiscoveryManager::getInstance()->discoverResourceByTypes(
                    RCSAddress::multicast(),
                    EMPTY_STRING,
                    types,
                    onResourceDiscoveredCallback
            );
        }
        catch (const RCSPlatformException &e) {
            cout << e.what() << endl;
        }
    }

    while (!discoveryTask->isCanceled()) {
        sleep(SECONDS_TO_SLEEP_DISCOVERY);
    };
}

void Client::onResourceDiscovered(shared_ptr<RCSRemoteResourceObject> discoveredResource) {
    cout << "onResourceDiscovered callback :: " << endl;
    string resAbsoluteURI = discoveredResource->getAddress() + discoveredResource->getUri();
    cout << "resourceURI : " << resAbsoluteURI << endl;
    cout << "hostAddress : " << discoveredResource->getAddress() << endl;

    try {
        discoveredResources[resAbsoluteURI] = discoveredResource;
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }
}

void Client::stopDiscovery() {
    discoveryTask->cancel();
}

bool Client::isDiscovering() {
    return !discoveryTask->isCanceled();
}

void Client::registerResourceFromDiscovery(const vector<string> &uris, const string &type) {

        if(isDiscovering()){
            ResourceRepresentationBuilder builder = ResourceRepresentationBuilder(discoveryThread, type);
            for (const string &uri : uris) {
                try {

                    RCSRemoteResourceObject::Ptr res = getResource(uri);
                    string absURI = res->getAddress() + res->getUri();
                    builder.addResource(res);

                }catch(NotInDiscoveredResException e){
                    cout << e.what() << endl;
                    cout << "URI: " << uri << endl;
                }catch (MoreResWithSameURIException e){
                    cout << e.what() << endl;
                    cout << "URI: " << uri << endl;
                }
            }

            ResourceRepresentation *resRepr = builder.build();
            registeredResources[resRepr->getAbsoluteUri()] = resRepr;
        }
}

bool Client::hasResourceRegistered(const string &uri) {
    return registeredResources[uri] != nullptr;
}

void Client::loadConfiguration() {
    vector<pair<vector<string>, string>> resourcesToReg = config->readRegistrationInput();
    if(!resourcesToReg.empty()){
        for( pair<vector<string>, string> res : resourcesToReg){

            registerResourceFromDiscovery(
                    res.first,
                    res.second
            );
        }
    }


    printRegisteredResources();
    setRules(config->readRulesInput());


}

void Client::printRegisteredResources() {
    for (const auto &res : registeredResources) {
        std::cout << "URI: " << res.second->getAbsoluteUri() << std::endl;
    }
}

void Client::setRules(Json::Value json) {
    if(json.empty()){

        for(Json::Value ruleJson : json){
            Rule r;
            r.triggerResRepr = registeredResources[ruleJson[Configuration::TRIGGER_KEY].asString()];
            r.triggerServiceName = ruleJson[Configuration::TRIGGER_SERVICE_KEY].asString();
            r.value = ruleJson[Configuration::TRIGGER_VALUE_KEY].asInt();
            r.reactionResRepr = registeredResources[ruleJson[Configuration::REACTOR_KEY].asString()];
            r.reactionServiceName = ruleJson[Configuration::REACTION_SERVICE_KEY].asString();
            r.registerAsListener();
        }
    }
}

map<string, RCSRemoteResourceObject::Ptr> Client::getDiscoveredResources() {
    return discoveredResources;
}

RCSRemoteResourceObject::Ptr Client::getResource(const string &uri) {
    if (!hasResource(uri)) {
        throw NotInDiscoveredResException();
    }
    if (countDiscoveredResWithURI(uri) > 1) {
        throw MoreResWithSameURIException();
    }
    string key = findDiscoveredResource(uri);
    RCSRemoteResourceObject::Ptr ret = discoveredResources[key];

    return ret;
}

bool Client::hasResource(const string &uri) {
    return countDiscoveredResWithURI(uri) > 0;
}

unsigned int Client::countDiscoveredResWithURI(const string &uri) {
    unsigned int count = 0;
    for (const auto &resourceKeyValue : discoveredResources) {
        if (resourceKeyValue.first.find(uri) != string::npos) {
            count++;
        }
    }
    return count;
}

string Client::findDiscoveredResource(const string &uri) {
    for (const auto &resourceKeyValue : discoveredResources) {
        if (resourceKeyValue.first.find(uri) != string::npos) {
            return resourceKeyValue.first;
        }
    }

    return FALSE_STRING_RETURN_VALUE;
}






