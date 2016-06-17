#include <condition_variable>
#include "RCSResourceObject.h"
#include "OCPlatform.h"
#include "Constants.h"
#include "exceptions/EmptyStringException.h"

using namespace OC::OCPlatform;
using namespace OIC::Service;
using namespace std;

#ifndef IOTIVITY_BAKALARKA_SERVER_H
#define IOTIVITY_BAKALARKA_SERVER_H

class Server {

protected:
    string name;
    RCSResourceObject::Ptr resource;
    bool isPresenceStarted;

    void initServer(const string &resourceUri, const string &resourceType);

    virtual void buildServer(const string &rUri, const string &resourceType) = 0;

    static string nameValidation(const string &n);

    static void printAttributes(const RCSResourceAttributes& attrs);

public:
    string getName();

    vector<string> getResourceInterfaces();

    bool hasResourceInterface(const string &iface);

    vector<string> getResourceTypes();

    bool hasResourceType(const string &t);

    void setPresenceOn();

    void setPresenceOff();

    bool isPresenceOn();

    string getResourceURI();
};

#endif//IOTIVITY_BAKALARKA_SERVER_H
