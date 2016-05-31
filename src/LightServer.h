#include "Server.h"

#ifndef IOTIVITY_BAKALARKA_LIGHTSERVER_H
#define IOTIVITY_BAKALARKA_LIGHTSERVER_H

using namespace std;

class LightServer : public Server {
private:
    int brightness = 0;
    virtual void buildServer(const string &rUri, const string &resourceType);

public:
    LightServer(const string &n);

    static const string LIGHT_URI;
    static const string BRIGHTNESS_ATTR ;
    static const int ZERO_BRIGHTNESS;
    static const int MAX_BRIGHTNESS;
    static const int STAGE_OF_BRIGHTNESS;



};

#endif //IOTIVITY_BAKALARKA_LIGHTSERVER_H