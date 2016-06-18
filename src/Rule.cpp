//
// Created by kingofwolwes on 4.6.2016.
//

#include "Rule.h"
void Rule::registerAsListener(){
    cout << "------------ Rule registered --------------" << endl;

    triggerResRepr->registerOnAttrChangeListener(this);
    onAttrChanged();
};

void Rule::onAttrChanged(){
    cout << "----------- Rule triggered ----------------" << endl;
    triggerResRepr->callService(triggerServiceName);
    if(triggerResRepr->getServiceReturnStorage() == value){
        reactionResRepr->callService(reactionServiceName);
    }
};