//
// Created by kingofwolwes on 4.6.2016.
//

#include "Rule.h"
void Rule::registerAsListener(){
    cout << "ideme..." << endl;
    cout << "ideme..." << endl;
    cout << "ideme..." << endl;
    cout << "ideme..." << endl;
    cout << "ideme..." << endl;
    cout << "ideme..." << endl;
    cout << "ideme..." << endl;
    cout << "ideme..." << endl;
    triggerResRepr->registerOnAttrChangeListener(this);
    onAttrChanged();
};

void Rule::onAttrChanged(){
    cout << "ideme>>>" << endl;
    cout << "ideme>>>" << endl;
    cout << "ideme>>>" << endl;
    cout << "ideme>>>" << endl;
    cout << "ideme>>>" << endl;
    cout << "ideme>>>" << endl;
    cout << "ideme>>>" << endl;
    cout << "ideme>>>" << endl;
    triggerResRepr->callService(triggerServiceName);
    if(triggerResRepr->getServiceReturnStorage() == value){
        reactionResRepr->callService(reactionServiceName);
    }
};