#include <gtest/gtest.h>
#include <Client.h>

struct ClientTestFixture : testing::Test{
    Client *client;
    Client *client2;

    ClientTestFixture(){
        client = new Client();
        client2 = new Client();
    }

    ~ClientTestFixture(){
        delete client;
        delete client2;
    }

    void SetUp() {

    }

    void TearDown() {

    }
};

TEST_F(ClientTestFixture, isDiscovering){
    EXPECT_FALSE(client->isDiscovering());
    client->startDiscovery();
    EXPECT_TRUE(client->isDiscovering());
    client->startDiscovery();
    EXPECT_TRUE(client->isDiscovering());
    client->stopDiscovery();
    EXPECT_FALSE(client->isDiscovering());
    client->stopDiscovery();
    EXPECT_FALSE(client->isDiscovering());
    client->startDiscovery();
    EXPECT_TRUE(client->isDiscovering());


}

TEST_F(ClientTestFixture, nonInitializatedDiscovery){
    EXPECT_FALSE(client2->isDiscovering());
    EXPECT_NO_THROW(client2->stopDiscovery());
    EXPECT_FALSE(client2->isDiscovering());
}