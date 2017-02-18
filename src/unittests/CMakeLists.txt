include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)

set(TEST_LINKS tentacliot gtest gtest_main)

add_executable(basicServerTest BasicServerTestFixture.cpp)
target_link_libraries(basicServerTest ${TEST_LINKS})

add_executable(ClientTest ClientTestFixture.cpp)
target_link_libraries(ClientTest ${TEST_LINKS})

add_executable(DiscoveryTest DiscoveryThreadTestFixture.cpp ${ALL_FILES})
target_link_libraries(DiscoveryTest ${TEST_LINKS})

add_executable(DiscoveringResourcesTest DiscoveringResourcesTestFixtures.cpp ${ALL_FILES})
target_link_libraries(DiscoveringResourcesTest ${TEST_LINKS})