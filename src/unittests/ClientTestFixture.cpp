#include <Client.h>
#include "gtest/gtest.h"

struct ClientTestFixture : testing::Test{

    ClientTestFixture() = default;

    ~ClientTestFixture() = default;

    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(ClientTestFixture, init) {
    Client test = Client();
}