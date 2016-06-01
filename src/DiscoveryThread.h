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
    thread discoveryLoop;
    mutex m;
    condition_variable runStarted;
    vector<string> discoveryTypes;
    unique_ptr<RCSDiscoveryManager::DiscoveryTask> discoveryTask;
    function<void(shared_ptr<RCSRemoteResourceObject>)> onResourceDiscoveredCallback;
    bool isDiscovering;
    bool threadStopped;
    bool isWritten;
    map<string, RCSRemoteResourceObject::Ptr> discoveredResources;

    void discover();

    void onResourceDiscovered(shared_ptr<RCSRemoteResourceObject> discoveredResource);

public:
    DiscoveryThread();

    DiscoveryThread(const string &type);

    DiscoveryThread(const vector<string> &types);

    ~DiscoveryThread();

    void init();

    void startDiscovering()throw(ThreadStoppedException);

    void stopDiscovering();

    bool isRunningDiscovery();

    void printResourceList();

    const vector<string> &getDiscoveryTypes();

    bool hasDiscoveryType(const string &type);

    map<string, RCSRemoteResourceObject::Ptr> getDiscoveredResources();

    bool hasResource(const string &uri);

    unsigned int countDiscoveredResWithURI(const string &uri);

    string findDiscoveredResource(const string &uri);

    RCSRemoteResourceObject::Ptr getResource(
            const string &uri) throw(NotInDiscoveredResException, MoreResWithSameURIException);

    unsigned long getDiscoveredResSize();

    void waitForAccessToDiscoveredResMap() throw(NotDiscoveringException);



    static bool waitRandomTimeInRange(const unsigned int &minMilliseconds = 100,
                                      const unsigned int &maxMilliseconds = 500);

    static unsigned int getRangeFromMinMax(const unsigned int &min,
                                           const unsigned int &max) throw(MaxLowerThanMinException);
};


#endif //IOTIVITY_BAKALARKA_DISCOVERYTHREAD_H
