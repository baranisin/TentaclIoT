#include <gtest/gtest.h>
#include <ResourceRepresentation.h>

struct ResRepresentationTestFixture : testing::Test{
    ResourceRepresentation *rr;
    ResourceRepresentation *rr2;

    ResRepresentationTestFixture(){
        rr = new ResourceRepresentation(1, RCSRemoteResourceObject::Ptr());
        rr2 = new ResourceRepresentation(-1, RCSRemoteResourceObject::Ptr{});
    }

    ~ResRepresentationTestFixture(){
        delete rr;
    }

    void SetUp() {

    }

    void TearDown() {

    }
};

TEST_F(ResRepresentationTestFixture, init){
    EXPECT_NO_FATAL_FAILURE(ResourceRepresentation r1(2, RCSRemoteResourceObject::Ptr{}));
    EXPECT_NO_FATAL_FAILURE(ResourceRepresentation r2(-1, RCSRemoteResourceObject::Ptr{}));
}

TEST_F(ResRepresentationTestFixture, getID){
    EXPECT_EQ(rr->getResourceId(), 1);
    EXPECT_TRUE(rr != NULL);
    unsigned int a = -1;
    EXPECT_EQ(rr2->getResourceId(), a);
}
