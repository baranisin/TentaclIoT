//
// Created by kingofwolwes on 4.6.2016.
//

#include "Rule.h"
void Rule::registerAsListener(){
    cout << "------------ Rule registered --------------" << endl;

    triggerResRepr->registerOnAttrChangeListener(this);
    this_thread::sleep_for(chrono::milliseconds(MIN_RANGE_TO_WAIT));
    onAttrChanged();
};

void Rule::onAttrChanged(){
    cout << "----------- Rule triggered ----------------" << endl;
    triggerResRepr->callService(triggerServiceName);
    if(triggerResRepr->getServiceReturnStorage() == value){
        reactionResRepr->callService(reactionServiceName);
    }
    this_thread::sleep_for(chrono::milliseconds(MIN_RANGE_TO_WAIT));
};