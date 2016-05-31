include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)

set(SERVER_FILES ../Server.cpp ../Server.h ../LightServer.cpp ../LightServer.h)
set(CLIENT_FILES ../Client.h ../Client.cpp ../DiscoveryThread.cpp ../DiscoveryThread.h  ../ResourceRepresentation.h)
set(ALL_FILES ../Constants.h ${SERVER_FILES} ${CLIENT_FILES})

set(COMMON_LINKS gtest gtest_main rcs_common oc octbstack oc_logger)
set(ALL_LINKS rcs_server rcs_client ${COMMON_LINKS})

set(TEST_SERVER_SOURCE ../Constants.h ${SERVER_FILES})
add_executable(basicServerTest BasicServerTestFixture.cpp ${TEST_SERVER_SOURCE})
target_link_libraries(basicServerTest rcs_server ${COMMON_LINKS})

set(TEST_CLIENT_SOURCE ../Constants.h ${CLIENT_FILES})
add_executable(ClientTest ClientTestFixture.cpp ${TEST_CLIENT_SOURCE})
target_link_libraries(ClientTest rcs_client ${COMMON_LINKS})

add_executable(DiscoveryTest DiscoveryThreadTestFixture.cpp ${ALL_FILES})
target_link_libraries(DiscoveryTest ${ALL_LINKS})

add_executable(DiscoveringResourcesTest DiscoveringResourcesTestFixtures.cpp ${ALL_FILES})
target_link_libraries(DiscoveringResourcesTest ${ALL_LINKS})

add_executable(ResReprTest ResRepresentationTestFixture.cpp ${ALL_FILES} ../ResourceRepresentationBuilder.cpp ../ResourceRepresentationBuilder.h)
target_link_libraries(ResReprTest ${ALL_LINKS})