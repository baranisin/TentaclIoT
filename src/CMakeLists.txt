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
        SwitchServer.cpp
        SwitchServer.h
        ${EXCEPTIONS_SOURCE_FILES})
add_library(tentacliotServer ${SERVER_SOURCE_FILES})
target_link_libraries(tentacliotServer rcs_server rcs_common oc octbstack oc_logger pthread)

add_executable(serverSide serverMain.cpp)
target_link_libraries(serverSide tentacliot)

set(CLIENT_SOURCE_FILES
        #        Constants.h
        Client.h
        Client.cpp
        DiscoveryManager.cpp DiscoveryManager.h TypeDefs.h ServerModel.cpp ServerModel.h
        #[[     DiscoveryThread.cpp
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
             Rule.h]]
        )

#[[add_library(tentacliot ${CLIENT_SOURCE_FILES} ${SERVER_SOURCE_FILES})
target_link_libraries(tentacliot rcs_client rcs_server rcs_common oc octbstack oc_logger jsoncpp pthread)]]

add_executable(clientSide clientMain.cpp ${CLIENT_SOURCE_FILES})
target_link_libraries(clientSide oc)

add_subdirectory(unittests)
