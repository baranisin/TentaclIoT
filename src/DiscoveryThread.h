#include <thread>
#include <condition_variable>
#include <vector>
#include <map>
#include <iostream>
#include <RCSRemoteResourceObject.h>
#include <RCSAddress.h>
#include <RCSDiscoveryManager.h>

#include "Constants.h"
#include "exceptions/ThreadStoppedException.h"
#include <exceptions/MaxLowerThanMinException.h>
#include <exceptions/NotInDiscoveredResException.h>
#include <exceptions/MoreResWithSameURIException.h>
#include <exceptions/NotDiscoveringException.h>

using namespace OIC::Service;
using namespace std;

#ifndef IOTIVITY_BAKALARKA_DISCOVERYTHREAD_H
#define IOTIVITY_BAKALARKA_DISCOVERYTHREAD_H

class DiscoveryThread {

public:

};


#endif //IOTIVITY_BAKALARKA_DISCOVERYTHREAD_H
