//
// Created by kingofwolwes on 7.5.2016.
//
#include "LightServer.h"
#include "gtest/gtest.h"

struct BasicServerTestFixture : testing::Test {
    const string TEST_NAME_1 = "svetielko1";
    const string TEST_NAME_2 = "svetielko2";
    const string NAME_WITH_SPACES = "sve tielko 3";
    const string NAME_WITH_FORBIDDEN_CHARS = "sv$%&e tie';\\lko 4";
    const string NAME_ALL_FORBIDDEN_CHARS = "$%&';\\";
    const string NAME_EMPTY = "";

    LightServer *testLight;
    LightServer *presenceTestLight;
    LightServer *lightWithSpacesInName;
    LightServer *lightWithForbiddenName;
    LightServer *lightWithEmptyName;
    LightServer *lightAllForbidden;

    BasicServerTestFixture() {
        testLight = new LightServer(TEST_NAME_1);
        presenceTestLight = new LightServer(TEST_NAME_2);
        lightWithSpacesInName = new LightServer(NAME_WITH_SPACES);
        lightWithForbiddenName = new LightServer(NAME_WITH_FORBIDDEN_CHARS);
        lightWithEmptyName = new LightServer(NAME_EMPTY);
        lightAllForbidden = new LightServer(NAME_ALL_FORBIDDEN_CHARS);
    }

    void SetUp() {
        presenceTestLight->setPresenceOn();
    }

    void TearDown() {
        presenceTestLight->setPresenceOff();
    }

    ~BasicServerTestFixture() {
        delete testLight;
        delete presenceTestLight;
        delete lightWithSpacesInName;
        delete lightWithForbiddenName;
        delete lightWithEmptyName;
        delete lightAllForbidden;
    }
};

TEST_F(BasicServerTestFixture, Name) {
    const char *n1 = lightWithSpacesInName->getName().c_str();
    EXPECT_STREQ("sve_tielko_3", n1);

    const char *n2 = testLight->getName().c_str();
    EXPECT_STREQ("svetielko1", n2);

    const char *n3 = lightWithForbiddenName->getName().c_str();
    EXPECT_STREQ("sve_tielko_4", n3);

    const char *n4 = lightWithEmptyName->getName().c_str();
    EXPECT_STREQ("-", n4);

    const char *n5 = lightAllForbidden->getName().c_str();
    EXPECT_STREQ("-", n5);
}

TEST_F(BasicServerTestFixture, Interfaces) {
    EXPECT_FALSE(testLight->getResourceInterfaces().empty());
    EXPECT_FALSE(testLight->hasResourceInterface(""));
    EXPECT_TRUE(testLight->hasResourceInterface("oic.if.a"));
    EXPECT_TRUE(testLight->hasResourceInterface("oic.if.baseline"));
    EXPECT_TRUE(testLight->hasResourceInterface("oic.if.s"));
}

TEST_F(BasicServerTestFixture, Types) {
    EXPECT_FALSE(testLight->getResourceTypes().empty());
    EXPECT_FALSE(testLight->hasResourceType(""));
    EXPECT_TRUE(testLight->hasResourceType("oic.r.light"));
}

TEST_F(BasicServerTestFixture, Presence) {
    EXPECT_TRUE(presenceTestLight->isPresenceOn());
    presenceTestLight->setPresenceOff();
    EXPECT_FALSE(presenceTestLight->isPresenceOn());
    presenceTestLight->setPresenceOn();
    EXPECT_TRUE(presenceTestLight->isPresenceOn());
}