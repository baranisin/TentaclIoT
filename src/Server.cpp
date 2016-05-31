#include "Server.h"

void Server::initServer(const string &resourceUri, const string &resourceType) {
    string rUri = resourceUri;
    int id = 1;
    bool again = true;
    while (again && id < MAX_RES_WITH_SAME_NAME) {
        try {

            rUri = resourceUri + "/" + name + "/" + to_string(id)+"";
            cout << "URI wil be: " + rUri << endl;

            buildServer(rUri, resourceType);

            again = false;
        } catch (RCSPlatformException e) {
            cout << e.what() << endl;
            cout << e.getReason() << endl;
            cout << "Maybe resource with same URI " + rUri + " exists" << endl;
            cout << "Trying again with higher id" << endl;

            id++;
            again = true;
        }
    }
}

string Server::getName() {
    return name;
}


vector<string> Server::getResourceInterfaces() {
    return resource->getInterfaces();
}

bool Server::hasResourceInterface(const string &iface) {
    for (string interface : getResourceInterfaces()) {
        if (interface == iface) {
            return true;
        }
    }
    return false;
}

vector<string> Server::getResourceTypes() {
    return resource->getTypes();
}

bool Server::hasResourceType(const string &t) {
    for (string type : getResourceTypes()) {
        if (type == t) {
            return true;
        }
    }
    return false;
}

void Server::setPresenceOn() {
    if (!isPresenceOn()) {
        startPresence(1);
        isPresenceStarted = true;
    }
}

void Server::setPresenceOff() {
    if (isPresenceOn()) {
        resource.reset();
        stopPresence();
        isPresenceStarted = false;
    }
    cout << "Presence off" << endl;
}

bool Server::isPresenceOn() {
    return isPresenceStarted;

}

string Server::nameValidation(const string &n) {
    try {
        if (n == "") {
            throw EmptyStringException();
        }

        string validName = n;
        for (const char &c : NAME_FORBIDDEN_CHARS) {
            replace(validName.begin(), validName.end(), c, REPLACEMENT_CHAR);

        }

        replace(validName.begin(), validName.end(), SPACE_CHAR, REPLACEMENT_FOR_SPACE);
        validName.erase(remove(validName.begin(), validName.end(), REPLACEMENT_CHAR), validName.end());

        if (validName == "") {
            throw EmptyStringException();
        }

        return validName;


    } catch (EmptyStringException e) {
        cout << e.what() << endl;
        cout << "Returning \"-\" instead!" << endl;
        return "-";
    }
}

string Server::getResourceURI() {
    return resource->getUri();
}












