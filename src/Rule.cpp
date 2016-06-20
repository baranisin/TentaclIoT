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
    this_thread::sleep_for(chrono::milliseconds(MAX_RANGE_TO_WAIT));
    cout << triggerResRepr->getServiceReturnStorage() << endl;
    if(triggerResRepr->getServiceReturnStorage() == value){
        cout << "----------- Rule REACTION ----------------" << endl;
        reactionResRepr->callService(reactionServiceName);
        this_thread::sleep_for(chrono::milliseconds(MAX_RANGE_TO_WAIT));
    }
};