#ifndef IOTIVITY_BAKALARKA_RULE_H
#define IOTIVITY_BAKALARKA_RULE_H

#include <functional>

using namespace std;

class Rule {
    State trigger;
    Condition condition;
    function action;


};


#endif //IOTIVITY_BAKALARKA_RULE_H
