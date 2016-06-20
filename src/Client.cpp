#include "Client.h"
#include "Rule.h"

Client::Client() {
    platformConfigure();
    registeredResources = map<string, ResourceRepresentation*>{};
    config = Configuration();
    discoveryThread = new DiscoveryThread();
}

Client::~Client() {
    stopDiscovery();
    delete discoveryThread;
    rules.clear();
    registeredResources.clear();
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
        config.writeOutput(discoveryThread->getDiscoveredResources(), registeredResources);

        printActualDiscoveredResources();
    }
}

void Client::printActualDiscoveredResources(){
    if(isDiscovering()){
        discoveryThread->printResourceList();
    }
}

bool Client::hasResourceDiscovered(const string &uri) {
    if(isDiscovering()){
        return discoveryThread->hasResource(uri);
    }

}

void Client::startDiscovery(const vector<string> &types) {
    if(!isDiscovering()){
        discoveryThread->startDiscovering();
    }

}

void Client::stopDiscovery() {
    if(isDiscovering()){
        discoveryThread->stopDiscovering();
    }
}

bool Client::isDiscovering() {
    return discoveryThread->isRunningDiscovery();
}

void Client::registerResourceFromDiscovery(const vector<string> &uris, const string &type) {

        if(isDiscovering()){
            ResourceRepresentationBuilder builder = ResourceRepresentationBuilder(discoveryThread, type);
            for (const string &uri : uris) {
                try {
                    RCSRemoteResourceObject::Ptr res = discoveryThread->getResource(uri);
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
    vector<pair<vector<string>, string>> resourcesToReg = config.readRegistrationInput();
    if(!resourcesToReg.empty()){
        for( pair<vector<string>, string> res : resourcesToReg){
            registerResourceFromDiscovery(
                    res.first,
                    res.second
            );
        }
    }

    printRegisteredResources();
    setRules(config.readRulesInput());

}

void Client::printRegisteredResources() {
    for (const auto &res : registeredResources) {
        std::cout << "URI: " << res.second->getAbsoluteUri() << std::endl;
    }
}

void Client::setRules(Json::Value json) {
    if(!json.empty()){
        for(Json::Value ruleJson : json){
            try{
                Rule* r = new Rule();
                r->triggerResRepr = registeredResources.at(ruleJson[Configuration::TRIGGER_KEY].asString());
                r->triggerServiceName = ruleJson[Configuration::TRIGGER_SERVICE_KEY].asString();
                r->value = ruleJson[Configuration::TRIGGER_VALUE_KEY].asInt();
                r->reactionResRepr = registeredResources.at(ruleJson[Configuration::REACTOR_KEY].asString());
                r->reactionServiceName = ruleJson[Configuration::REACTION_SERVICE_KEY].asString();
                r->registerAsListener();
                rules.push_back(r);
            } catch (out_of_range e){
                std::cout <<  "Rule: adress not in " << e.what() << std::endl;
            }
        }
        initRulesActivation();
    }
}

void Client::initRulesActivation() {
    if(!rules.empty()){
        for(Rule* r : rules){
            r->onAttrChanged();
        }
    }

}








