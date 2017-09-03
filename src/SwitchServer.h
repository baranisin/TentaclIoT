//
// Created by Patrik Baranišin on 17.6.2016.
//

#ifndef IOTIVITY_BAKALARKA_SWITCHSERVER_H
#define IOTIVITY_BAKALARKA_SWITCHSERVER_H


#include <I2CDevice.h>
#include "Server.h"

class SwitchServer : public Server{
private:
    I2CDevice device;
    RCSResourceObject::SetRequestHandler setRequestHandler;
    RCSSetResponse onSetRequest(const RCSRequest& req, RCSResourceAttributes& attrs);

    virtual void buildServer(const string &rUri, const string &resourceType);

public:
    SwitchServer(const string &n, I2CDevice);

    void test();

    static const string SWITCH_URI;
    static const string IS_ON_ATTR;

};


#endif //IOTIVITY_BAKALARKA_SWITCHSERVER_H
