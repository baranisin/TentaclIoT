#include <Client.h>
#include <gtest/gtest.h>

struct DiscoveringResourcesTestFixtures : testing::Test{
    const string LS_NAME = "svetielko";

    Client *client;
    LightServer *ls;

    DiscoveringResourcesTestFixtures(){
        ls = new LightServer(LS_NAME);
        client = new Client();
    }

    ~DiscoveringResourcesTestFixtures(){
        delete client;
        delete ls;
    }

    void SetUp() {
        client->startDiscovery();
        ls->setPresenceOn();
        sleep(SECONDS_TO_SLEEP_TEST);
    }

    void TearDown() {
        client->stopDiscovery();
        ls->setPresenceOff();
    }
};

TEST_F(DiscoveringResourcesTestFixtures, findResourceAfterInit){
    Client c2 = Client();
    EXPECT_FALSE(c2.hasResourceDiscovered(ls->getResourceURI()));
}

TEST_F(DiscoveringResourcesTestFixtures, findResource){
    EXPECT_TRUE(client->hasResourceDiscovered(ls->getResourceURI()));
    LightServer *ls2 = new LightServer("s");
    string uri = ls2->getResourceURI();
    sleep(SECONDS_TO_SLEEP_TEST);
    EXPECT_TRUE(client->hasResourceDiscovered(uri));
    delete ls2;
    sleep(SECONDS_TO_SLEEP_TEST);
    EXPECT_FALSE(client->hasResourceDiscovered(uri));
}

TEST_F(DiscoveringResourcesTestFixtures, registerRes){
    string uri = ls->getResourceURI();
    EXPECT_FALSE(client->hasResourceRegistered(uri));
    EXPECT_TRUE(client->hasResourceRegistered(uri));
}

TEST_F(DiscoveringResourcesTestFixtures, registerResNegative){
    EXPECT_FALSE(client->hasResourceRegistered(EMPTY_STRING));
    EXPECT_FALSE(client->hasResourceRegistered(EMPTY_STRING));
}