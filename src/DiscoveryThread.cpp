#include "DiscoveryThread.h"


DiscoveryThread::DiscoveryThread() {
    discoveryTypes = EMPTY_STRING_VECTOR;
    init();
}

DiscoveryThread::DiscoveryThread(const string &type) {
    discoveryTypes = vector<string>{type};
    init();
}

DiscoveryThread::DiscoveryThread(const vector<string> &types) {
    discoveryTypes = types;
    init();
}

DiscoveryThread::~DiscoveryThread() {
    runStarted.notify_all();
    stopDiscovering();
}

void DiscoveryThread::init() {
    discoveryLoop = thread(&DiscoveryThread::discover, this);
    isDiscovering = false;
    threadStopped = false;
    onResourceDiscoveredCallback = bind(
            &DiscoveryThread::onResourceDiscovered,
            this,
            placeholders::_1
    );
    discoveredResources = map<string, RCSRemoteResourceObject::Ptr>{};
}

void DiscoveryThread::discover() {
    unique_lock<mutex> lk(m);
    runStarted.wait(lk);

    while (isDiscovering) {
        if (discoveredResources != map<string, RCSRemoteResourceObject::Ptr>{}) {
            discoveredResources = map<string, RCSRemoteResourceObject::Ptr>{};
            isWritten = false;
        }
        discoveryTask = nullptr;
        while (!discoveryTask) {
            try {
                discoveryTask = RCSDiscoveryManager::getInstance()->discoverResourceByTypes(
                        RCSAddress::multicast(),
                        EMPTY_STRING,
                        discoveryTypes,
                        onResourceDiscoveredCallback
                );
            }
            catch (const RCSPlatformException &e) {
                cout << e.what() << endl;
            }
        }
        isWritten = true;
        sleep(SECONDS_TO_SLEEP_DISCOVERY);
    }
}

void DiscoveryThread::startDiscovering() throw(ThreadStoppedException) {
    if (threadStopped) {
        throw ThreadStoppedException();
    }

    if (!isDiscovering) {
        isDiscovering = true;
        runStarted.notify_one();
    }
}

void DiscoveryThread::stopDiscovering() {
    if (isDiscovering) {
        isDiscovering = false;
        threadStopped = true;
    }
    if (discoveryLoop.joinable()) {
        discoveryLoop.join();
    }
}

void DiscoveryThread::onResourceDiscovered(shared_ptr<RCSRemoteResourceObject> discoveredResource) {

    string resAbsoluteURI = discoveredResource->getAddress() + discoveredResource->getUri();
//    cout << "onResourceDiscovered callback :: " << endl;
//    cout << "resourceURI : " << resAbsoluteURI << endl;
//    cout << "hostAddress : " << discoveredResource->getAddress() << endl;

    try {
        discoveredResources[resAbsoluteURI] = discoveredResource;
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }
}



void DiscoveryThread::printResourceList() {
    waitForAccessToDiscoveredResMap();
    for (const auto &res : discoveredResources) {
        std::cout << "URI: " << res.second->getUri() << " has resource " << res.first << std::endl;
    }
}

map<string, RCSRemoteResourceObject::Ptr> DiscoveryThread::getDiscoveredResources(){
    waitForAccessToDiscoveredResMap();
    return discoveredResources;
};


const vector<string> &DiscoveryThread::getDiscoveryTypes() {
    return discoveryTypes;
}

bool DiscoveryThread::isRunningDiscovery() {
    return isDiscovering;
}

bool DiscoveryThread::hasDiscoveryType(const string &type) {
    return find(discoveryTypes.begin(), discoveryTypes.end(), type) != discoveryTypes.end();
}

RCSRemoteResourceObject::Ptr DiscoveryThread::getResource(
        const string &uri) throw(NotInDiscoveredResException, MoreResWithSameURIException) {
    if (!hasResource(uri)) {
        throw NotInDiscoveredResException();
    }
    if (countDiscoveredResWithURI(uri) > 1) {
        throw MoreResWithSameURIException();
    }
    waitForAccessToDiscoveredResMap();
    string key = findDiscoveredResource(uri);
    RCSRemoteResourceObject::Ptr ret = discoveredResources[key];

    return ret;
}

bool DiscoveryThread::hasResource(const string &uri) {
    return countDiscoveredResWithURI(uri) > 0;

}

unsigned int DiscoveryThread::countDiscoveredResWithURI(const string &uri) {
    unsigned int count = 0;
    try {

        waitForAccessToDiscoveredResMap();
        for (const auto &resourceKeyValue : discoveredResources) {
            if (resourceKeyValue.first.find(uri) != string::npos) {
                count++;
            }
        }

    } catch(NotDiscoveringException e){
       cout << e.what() << endl;
        count = 0;
    }

    return count;
}




string DiscoveryThread::findDiscoveredResource(const string &uri) {
    try {

        waitForAccessToDiscoveredResMap();
        for (const auto &resourceKeyValue : discoveredResources) {
            if (resourceKeyValue.first.find(uri) != string::npos) {
                return resourceKeyValue.first;
            }
        }

    } catch(NotDiscoveringException e){
        cout << e.what() << endl;
    }

    return FALSE_STRING_RETURN_VALUE;

}

void DiscoveryThread::waitForAccessToDiscoveredResMap() throw(NotDiscoveringException) {
    if(!isDiscovering){
        throw NotDiscoveringException();
    }
    while (!isWritten) {
        waitRandomTimeInRange();
    }
}


bool DiscoveryThread::waitRandomTimeInRange(
        const unsigned int &minMilliseconds,
        const unsigned int &maxMilliseconds) {
    int range = 0;
    int min = 0;
    try {
        range = getRangeFromMinMax(minMilliseconds, maxMilliseconds);
        min = minMilliseconds;

        if (range < MIN_RANGE_TO_WAIT) {
            range = MIN_RANGE_TO_WAIT;
        }
        if (range > MAX_RANGE_TO_WAIT) {
            range = MAX_RANGE_TO_WAIT;
        }
        if (minMilliseconds < MIN_RANGE_TO_WAIT) {
            min = MIN_RANGE_TO_WAIT;
        }
        if (minMilliseconds > MAX_RANGE_TO_WAIT) {
            min = MAX_RANGE_TO_WAIT;
        }

    } catch (MaxLowerThanMinException e) {
        cout << e.what() << endl;
        cout << "Min and Max set to Default values: MIN = 100, MAX = 500" << endl;
        min = MIN_RANGE_TO_WAIT;
        range = MAX_RANGE_TO_WAIT - MIN_RANGE_TO_WAIT;
    }

    this_thread::sleep_for(chrono::milliseconds(rand() % range + min));
    return true;
}

unsigned int DiscoveryThread::getRangeFromMinMax(
        const unsigned int &min,
        const unsigned int &max) throw(MaxLowerThanMinException) {
    if (min > max) {
        throw MaxLowerThanMinException();
    }

    return max - min;
}

unsigned long DiscoveryThread::getDiscoveredResSize() {
    try{
        waitForAccessToDiscoveredResMap();
        return discoveredResources.size();
    }catch (NotDiscoveringException e){
        return 0;
    }

}







