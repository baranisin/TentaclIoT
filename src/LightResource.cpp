#include "LightResource.h"


LightResource::LightResource(ResourceArgumentsBundle args) {
    brightnessValue = 0;
    init(args.resId, args.resources.back());
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
    waitForUpdate();
    return brightnessValue;
}

void LightResource::setBrightness(const int value) {
    waitForUpdate();

    int brightnessValue = 0;
    if(value <= LightServer::ZERO_BRIGHTNESS){
        brightnessValue = LightServer::ZERO_BRIGHTNESS;
    } else if(value >= LightServer::MAX_BRIGHTNESS){
        brightnessValue = LightServer::MAX_BRIGHTNESS;
    }else{
       brightnessValue = value;
    }

    if(this->brightnessValue == brightnessValue){
        return;
    }

    RCSResourceAttributes attribute;
    attribute[LightServer::BRIGHTNESS_ATTR] = brightnessValue;
    resource->setRemoteAttributes(attribute, setCallback);

    isWaitingForUpdate = true;
}

void LightResource::onAttrSet(const RCSResourceAttributes& attrs, int eCode) {
    cout << "----SET---- Brightness: " << attrs.at(LightServer::BRIGHTNESS_ATTR).toString() << "-----------" << endl;
}

void LightResource::onAttrGet(const RCSResourceAttributes &attrs, int eCode) {
    cout << "----GET---- Brightness: " << attrs.at(LightServer::BRIGHTNESS_ATTR).toString() << "-----------" << endl;
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
}





























