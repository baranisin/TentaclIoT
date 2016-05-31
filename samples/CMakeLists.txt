set(SERVER_SAMPLE_SOURCE_FILES sampleResourceServer.cpp)
add_executable(serverSample ${SERVER_SAMPLE_SOURCE_FILES})
target_link_libraries(serverSample rcs_server rcs_common oc octbstack oc_logger)

set(CLIENT_SAMPLE_SOURCE_FILES sampleResourceClient.cpp)
add_executable(clientSample ${CLIENT_SAMPLE_SOURCE_FILES})
target_link_libraries(clientSample rcs_client rcs_common oc octbstack oc_logger)