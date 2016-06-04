#include "UnknownTypeResRepr.h"

UnknownTypeResRepr::UnknownTypeResRepr(ResourceArgumentsBundle args) {
    resource = args.resources.back();
}

void UnknownTypeResRepr::onAttrSet(const RCSResourceAttributes &attrs, int eCode) {

}

void UnknownTypeResRepr::onAttrGet(const RCSResourceAttributes &attrs, int eCode) {

}

void UnknownTypeResRepr::onCacheUpdated(const RCSResourceAttributes &attrs) {

}







