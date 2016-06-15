//
// Created by kingofwolwes on 4.6.2016.
//

#include "Rule.h"
void Rule::registerAsListener(){
    triggerResRepr->registerOnAttrChangeListener(this);
};

void Rule::onAttrChanged(){
    triggerResRepr->callService(triggerServiceName);
    if(triggerResRepr->getServiceReturnStorage() == value){
        reactionResRepr->callService(reactionServiceName);
    }
};