

#ifndef IOTIVITY_BAKALARKA_RULE_H
#define IOTIVITY_BAKALARKA_RULE_H

#include <functional>
#include "OnAttrChangeListener.h"
#include "ResourceRepresentation.h"

using namespace std;

struct Rule : OnAttrChangeListener{
    ResourceRepresentation *triggerResRepr;
    string triggerServiceName;
    int value;
    ResourceRepresentation *reactionResRepr;
    string reactionServiceName;


    void registerAsListener(){
        triggerResRepr->registerOnAttrChangeListener(this);
    };

    void onAttrChanged(){
        triggerResRepr->callService(triggerServiceName);
        if(triggerResRepr->getServiceReturnStorage() == value){
            reactionResRepr->callService(reactionServiceName);
        }
    };
};


#endif //IOTIVITY_BAKALARKA_RULE_H
