//
// Created by Patrik Baranišin on 3.9.2017.
//

#include <gtest/gtest.h>
#include <ServerModel.h>

struct ServerModelTestFixture : testing::Test {
    ServerModel nullServerModel;
    ServerModel emptyServerModel;
    ServerModel serverWithInfo1;

    ServerModelTestFixture() {
        emptyServerModel = ServerModel();
        serverWithInfo1 = ServerModel();
    }

    ~ServerModelTestFixture() {
    }

    void SetUp() override {
        string DUMMY_INFO = "SALALA";
        map<string, string> deviceInfoMap;
        deviceInfoMap[OC_RSRVD_DEVICE_ID] = DUMMY_INFO;
        deviceInfoMap[OC_RSRVD_DEVICE_NAME] = DUMMY_INFO;
        deviceInfoMap[OC_RSRVD_SPEC_VERSION] = DUMMY_INFO;
        deviceInfoMap[OC_RSRVD_DATA_MODEL_VERSION] = DUMMY_INFO;
        deviceInfoMap[OC_RSRVD_DEVICE_DESCRIPTION] = DUMMY_INFO;
        deviceInfoMap[OC_RSRVD_SOFTWARE_VERSION] = DUMMY_INFO;
        deviceInfoMap[OC_RSRVD_DEVICE_MFG_NAME] = DUMMY_INFO;
        deviceInfoMap[OC_RSRVD_DEVICE_MODEL_NUM] = DUMMY_INFO;
        deviceInfoMap[OC_RSRVD_PROTOCOL_INDEPENDENT_ID] = DUMMY_INFO;

        map<string, string> platformInfoMap;
        platformInfoMap[OC_RSRVD_PLATFORM_ID] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_MFG_NAME] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_MFG_URL] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_MODEL_NUM] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_MFG_DATE] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_PLATFORM_VERSION] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_OS_VERSION] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_HARDWARE_VERSION] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_FIRMWARE_VERSION] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_SUPPORT_URL] = DUMMY_INFO;
        platformInfoMap[OC_RSRVD_SYSTEM_TIME] = DUMMY_INFO;

        serverWithInfo1.deviceInfoMap = deviceInfoMap;
        serverWithInfo1.platformInfoMap = platformInfoMap;
    }

    void TearDown() override {

    }
};


TEST_F(ServerModelTestFixture, PrintInfo) {
    EXPECT_NO_THROW(nullServerModel.printServerInfo());
    EXPECT_NO_THROW(emptyServerModel.printServerInfo());
    EXPECT_NO_THROW(serverWithInfo1.printServerInfo());
}
