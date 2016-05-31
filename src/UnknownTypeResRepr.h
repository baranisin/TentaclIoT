//
// Created by kingofwolwes on 20.5.2016.
//

#ifndef IOTIVITY_BAKALARKA_UNKNOWNTYPERESREP_H
#define IOTIVITY_BAKALARKA_UNKNOWNTYPERESREP_H


#include "PhysicalResourceRepr.h"
#include "ResourceArgumentsBundle.h"

class UnknownTypeResRepr : public PhysicalResourceRepr{
    void onAttrSet(const RCSResourceAttributes& attrs, int eCode);
    void onAttrGet(const RCSResourceAttributes& attrs, int eCode);
    void onCacheUpdated(const RCSResourceAttributes& attrs);

public:
    UnknownTypeResRepr(ResourceArgumentsBundle args);
};


#endif //IOTIVITY_BAKALARKA_UNKNOWNTYPERESREP_H
