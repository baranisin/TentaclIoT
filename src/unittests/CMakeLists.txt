include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)
enable_testing()

set(TEST_LINKS oc gtest gtest_main)

add_executable(serverModelTest ServerModelTestFixture.cpp ../ServerModel.h ../ServerModel.cpp)
target_link_libraries(serverModelTest ${TEST_LINKS})

add_executable(ClientTest ClientTestFixture.cpp ../Client.cpp ../Client.h)
target_link_libraries(ClientTest ${TEST_LINKS})

add_executable(DiscoveryTest DiscoveryManagerTestFixture.cpp ../DiscoveryManager.cpp ../DiscoveryManager.h ../ServerModel.cpp ../ServerModel.h)
target_link_libraries(DiscoveryTest ${TEST_LINKS})

add_executable(DiscoveringResourcesTest DiscoveringResourcesTestFixtures.cpp ${ALL_FILES})
target_link_libraries(DiscoveringResourcesTest ${TEST_LINKS})