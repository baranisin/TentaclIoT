#ifndef IOTIVITY_BAKALARKA_SCENESERVER_H
#define IOTIVITY_BAKALARKA_SCENESERVER_H


#include "Server.h"

class SceneServer : public Server{
    virtual void buildServer(const string &rUri, const string &resourceType);

public:
    SceneServer(const string &n);

    static const string STATE_ATTR;
    static const string SCENE_URI;
};


#endif //IOTIVITY_BAKALARKA_SCENESERVER_H
