#include "LightResource.h"


LightResource::LightResource(ResourceArgumentsBundle args) {
    brightnessValue = 0;
    init(args.resources.back());
}

LightResource::~LightResource() {
    resource->stopCaching();
}

void LightResource::turnOff() {
    if(getBrightness() != LightServer::ZERO_BRIGHTNESS){
        setBrightness(LightServer::ZERO_BRIGHTNESS);
    }
}

void LightResource::turnOn() {
    if(getBrightness() != LightServer::MAX_BRIGHTNESS){
        setBrightness(LightServer::MAX_BRIGHTNESS);
    }
}

int LightResource::getBrightness(){
    if(resource->isCaching() && resource->isCachedAvailable()){
        brightnessValue = stoi(resource->getCachedAttribute(LightServer::BRIGHTNESS_ATTR).toString());
    }else{
        resource->getRemoteAttributes(getCallback);
        sleep(1);
    }
//    if(brightnessValue == stoi(resource->getCachedAttribute(LightServer::BRIGHTNESS_ATTR).toString())){
//        waitForUpdate();
//    }

    cout << brightnessValue << endl;
    return brightnessValue;
}

void LightResource::setBrightness(const int value) {
    int brightnessValue = 0;
    if(value <= LightServer::ZERO_BRIGHTNESS){
        brightnessValue = LightServer::ZERO_BRIGHTNESS;
    } else if(value >= LightServer::MAX_BRIGHTNESS){
        brightnessValue = LightServer::MAX_BRIGHTNESS;
    }else{
       brightnessValue = value;
    }

    RCSResourceAttributes attribute;
    attribute[LightServer::BRIGHTNESS_ATTR] = brightnessValue;
    resource->setRemoteAttributes(attribute, setCallback);
    sleep(3);

}

void LightResource::onAttrSet(const RCSResourceAttributes& attrs, int eCode) {
    cout << "----SET---- Brightness: " << attrs.at(LightServer::BRIGHTNESS_ATTR).toString() << "-----------" << endl;
    brightnessValue = stoi(attrs.at(LightServer::BRIGHTNESS_ATTR).toString());
    isWaitingForUpdate = false;
}

void LightResource::onAttrGet(const RCSResourceAttributes &attrs, int eCode) {
    cout << "----GET---- Brightness: " << attrs.at(LightServer::BRIGHTNESS_ATTR).toString() << "-----------" << endl;
    brightnessValue = stoi(attrs.at(LightServer::BRIGHTNESS_ATTR).toString());
    isWaitingForUpdate = false;
}

void LightResource::raiseBrightness() {
    setBrightness(getBrightness()+LightServer::STAGE_OF_BRIGHTNESS);
}

void LightResource::lowBrightness() {
    setBrightness(getBrightness()-LightServer::STAGE_OF_BRIGHTNESS);
}

void LightResource::onBrightnessChanged() {

}

void LightResource::onCacheUpdated(const RCSResourceAttributes &attrs) {
    cout << "----UPDATED---- Brightness: " << attrs.at(LightServer::BRIGHTNESS_ATTR).toString() << " -----------" << endl;
    isWaitingForUpdate = false;
    brightnessValue = stoi(attrs.at(LightServer::BRIGHTNESS_ATTR).toString());
    for(OnAttrChangeListener* listener : listeners){
        listener->onAttrChanged();
    }
}

void LightResource::set(RCSResourceAttributes attrs) {
    if(attrs.contains(LightServer::BRIGHTNESS_ATTR)){
        setBrightness(stoi(attrs[LightServer::BRIGHTNESS_ATTR].toString()));
    }
}

void LightResource::defineServices() {
    pair<string, bool> turnOnService(TURN_ON_SERVICE_NAME, false);
    pair<string, bool> turnOffService(TURN_OFF_SERVICE_NAME, false);
    pair<string, bool> raiseService(RAISE_BRIGHTNESS_SERVICE_NAME, false);
    pair<string, bool> lowService(LOW_BRIGHTNESS_SERVICE_NAME, false);
    pair<string, bool> getService(GET_BRIGHTNESS_SERVICE_NAME, false);
    pair<string, bool> setService(SET_BRIGHTNESS_SERVICE_NAME, true);

    services.push_back(turnOnService);
    services.push_back(turnOffService);
    services.push_back(raiseService);
    services.push_back(lowService);
    services.push_back(getService);
    services.push_back(setService);

}

void LightResource::callService(const string &service) {
    int serviceId = getServiceId(service);

    switch(serviceId){
        case NOT_FOUND:
            //TODO throw exception
            break;
        case TURN_ON:
            turnOn();
            break;
        case TURN_OFF:
            turnOff();
            break;
        case INCREASE:
            raiseBrightness();
            break;
        case DECREASE:
            lowBrightness();
            break;
        case GET:
            serviceReturnStorage = getBrightness();
            break;
        case SET:
            setBrightness(serviceArgumentStorage);
            break;
        default:
            //TODO throw exception
            break;
    }
}



































