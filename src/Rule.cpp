//
// Created by kingofwolwes on 4.6.2016.
//

#include "Rule.h"
void Rule::registerAsListener(){
    cout << "------------ Rule registered --------------" << endl;

    triggerResRepr->registerOnAttrChangeListener(this);
};

void Rule::onAttrChanged(){
    cout << "----------- Rule triggered ----------------" << endl;
    triggerResRepr->callService(triggerServiceName);
    cout << triggerResRepr->getServiceReturnStorage() << endl;
    if(triggerResRepr->getServiceReturnStorage() == value){
        cout << "----------- Rule REACTION ----------------" << endl;
        reactionResRepr->callService(reactionServiceName);
    }
};