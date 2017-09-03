//
// Created by Patrik Baranišin on 3.9.2017.
//

#include <gtest/gtest.h>
#include <DiscoveryManager.h>

struct DiscoveryManagerTestFixture : testing::Test {

    DiscoveryManagerTestFixture() {

    }

    void SetUp() {

    }

    void TearDown() {

    }
};


TEST_F(DiscoveryManagerTestFixture, Discovery) {
    EXPECT_NO_THROW(DiscoveryManager::getInstance().findAvalaibleServers());
}