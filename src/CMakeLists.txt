project(iotivity)

set(EXCEPTIONS_SOURCE_FILES exceptions/)

set(SERVER_SOURCE_FILES
        Constants.h
        Server.cpp
        Server.h
        LightServer.cpp
        LightServer.h
        SceneServer.cpp
        SceneServer.h
        ${EXCEPTIONS_SOURCE_FILES})
add_executable(serverSide serverMain.cpp ${SERVER_SOURCE_FILES})
target_link_libraries(serverSide rcs_server rcs_common oc octbstack oc_logger pthread)

set(CLIENT_SOURCE_FILES
        Constants.h
        Client.h
        Client.cpp
        DiscoveryThread.cpp
        DiscoveryThread.h
        ${EXCEPTIONS_SOURCE_FILES}
        ResourceRepresentation.h
        ResourceRepresentationBuilder.cpp
        ResourceRepresentationBuilder.h
        Configuration.cpp
        Configuration.h
        LightResource.cpp
        LightResource.h
        UnknownTypeResRepr.cpp
        UnknownTypeResRepr.h
        Scene.cpp
        Scene.h
        Rule.cpp
        Rule.h
        )
add_executable(clientSide clientMain.cpp ${CLIENT_SOURCE_FILES} ${SERVER_SOURCE_FILES})
target_link_libraries(clientSide rcs_client rcs_server rcs_common oc octbstack oc_logger jsoncpp pthread)

add_subdirectory(unittests)
