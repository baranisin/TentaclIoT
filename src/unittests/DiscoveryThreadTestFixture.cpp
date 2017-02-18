#include <gtest/gtest.h>
#include <LightServer.h>
#include "DiscoveryThread.h"

struct DiscoveryThreadTestFixture : testing::Test{
    DiscoveryThread *DTallTypes;
    DiscoveryThread *dt1;
    DiscoveryThread *dt2;
    DiscoveryThread *dt3;

    DiscoveryThreadTestFixture(){
        DTallTypes = new DiscoveryThread();
        dt1 = new DiscoveryThread();
        dt2 = new DiscoveryThread(OIC_LIGHT_TYPE);
        dt3 = new DiscoveryThread(vector<string>{OIC_LIGHT_TYPE, OIC_TEMPERATURE_TYPE});
    }

    ~DiscoveryThreadTestFixture(){
        delete DTallTypes;
        delete dt1;
        delete dt2;
        delete dt3;
    }

    void SetUp() {
        sleep(1);
    }

    void TearDown() {

    }
};

TEST_F(DiscoveryThreadTestFixture, isDiscovering){
    EXPECT_FALSE(DTallTypes->isRunningDiscovery());
    DTallTypes->startDiscovering();
    EXPECT_TRUE(DTallTypes->isRunningDiscovery());
    DTallTypes->startDiscovering();
    EXPECT_TRUE(DTallTypes->isRunningDiscovery());
    DTallTypes->stopDiscovering();
    EXPECT_FALSE(DTallTypes->isRunningDiscovery());
    DTallTypes->stopDiscovering();
    EXPECT_FALSE(DTallTypes->isRunningDiscovery());
    EXPECT_THROW(DTallTypes->startDiscovering(),ThreadStoppedException);
}

TEST_F(DiscoveryThreadTestFixture, Types){
    EXPECT_FALSE(dt1->hasDiscoveryType(""));
    EXPECT_FALSE(dt1->hasDiscoveryType("oic.r.light"));
    EXPECT_FALSE(dt1->hasDiscoveryType("oic.r.temperaturesensor"));

    EXPECT_FALSE(dt2->hasDiscoveryType(""));
    EXPECT_FALSE(dt2->hasDiscoveryType("oic.r.temperaturesensor"));
    EXPECT_TRUE(dt2->hasDiscoveryType("oic.r.light"));

    EXPECT_FALSE(dt3->hasDiscoveryType(""));
    EXPECT_TRUE(dt3->hasDiscoveryType("oic.r.light"));
    EXPECT_TRUE(dt3->hasDiscoveryType("oic.r.temperaturesensor"));
}

TEST_F(DiscoveryThreadTestFixture, getTypes){
    EXPECT_EQ(EMPTY_STRING_VECTOR, dt1->getDiscoveryTypes());
    EXPECT_EQ(vector<string>{"oic.r.light"}, dt2->getDiscoveryTypes());
    vector<string> v{"oic.r.light", "oic.r.temperaturesensor"};
    EXPECT_EQ(v, dt3->getDiscoveryTypes());
}

TEST_F(DiscoveryThreadTestFixture, hasResource){
    LightServer *ls = new LightServer("svetlo");
    string uri1 = ls->getResourceURI();
    EXPECT_FALSE(DTallTypes->hasResource(uri1));

    DTallTypes->startDiscovering();
    sleep(SECONDS_TO_SLEEP_TEST);
    EXPECT_TRUE(DTallTypes->hasResource(uri1));

    delete ls;
    sleep(SECONDS_TO_SLEEP_TEST);
    EXPECT_FALSE(DTallTypes->hasResource(uri1));

    LightServer ls2 = LightServer("light");
    sleep(SECONDS_TO_SLEEP_TEST);
    EXPECT_TRUE(DTallTypes->hasResource(ls2.getResourceURI()));

    DTallTypes->stopDiscovering();
    sleep(SECONDS_TO_SLEEP_TEST);
    EXPECT_FALSE(DTallTypes->hasResource(ls2.getResourceURI()));
}

TEST_F(DiscoveryThreadTestFixture, countDiscoveredResWithUri){
    EXPECT_EQ(0, DTallTypes->getDiscoveredResSize());
    vector<LightServer*> lss{};
    for (int j = 0; j < 6; ++j) {
        string name = "svetlo";
        name += j+"";
        lss.push_back(new LightServer(name));
    }

    DTallTypes->startDiscovering();
    EXPECT_EQ(6+2, DTallTypes->getDiscoveredResSize()); // +2 for oic/p and oic/d !!
}

TEST_F(DiscoveryThreadTestFixture, getRange){
    EXPECT_EQ(DiscoveryThread::getRangeFromMinMax(100, 500), 400);
    EXPECT_EQ(DiscoveryThread::getRangeFromMinMax(0, 0), 0);
    EXPECT_EQ(DiscoveryThread::getRangeFromMinMax(0, 500), 500);
    EXPECT_ANY_THROW(DiscoveryThread::getRangeFromMinMax(10, 0));
    EXPECT_ANY_THROW(DiscoveryThread::getRangeFromMinMax(-10, 0));
    EXPECT_ANY_THROW(DiscoveryThread::getRangeFromMinMax(-10, -200));
    EXPECT_EQ(DiscoveryThread::getRangeFromMinMax(-100, -60), 40);
    EXPECT_NO_THROW(DiscoveryThread::getRangeFromMinMax(0, -10));
}

TEST_F(DiscoveryThreadTestFixture, waitRandomTime){
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange());
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(200, 500));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(0, 0));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(10, 0));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(0, 10));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(-50, 300));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(500000, 0));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(0, 50000));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(0, -50000));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(0, 50000));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(-200, 50000));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(-3000, -50000));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(-300, -50));
    EXPECT_TRUE(DiscoveryThread::waitRandomTimeInRange(-30, 50));
}
