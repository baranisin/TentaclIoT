cmake_minimum_required(VERSION 3.5)
project(Iotivity_bakalarka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        "iotivity-1.1.0/resource/include"
        "iotivity-1.1.0/resource/src"
        "iotivity-1.1.0/resource/csdk/stack/include"
        "iotivity-1.1.0/resource/c_common/ocrandom/include"
        "iotivity-1.1.0/resource/csdk/logger/include"
        "iotivity-1.1.0/resource/oc_logger/include"
        "iotivity-1.1.0/resource/c_common/"
        "iotivity-1.1.0/service/resource-encapsulation/include"
        "iotivity-1.1.0/service/resource-encapsulation/src"
        "iotivity-1.1.0/service/resource-encapsulation/src/common/primitiveResource/include"
        "iotivity-1.1.0/service/resource-encapsulation/src/common/primitiveResource/src"
        "iotivity-1.1.0/service/resource-encapsulation/src/resourceBroker/include"
        "iotivity-1.1.0/service/resource-encapsulation/src/resourceBroker/src"
        "iotivity-1.1.0/service/resource-encapsulation/src/resourceCache/include"
        "iotivity-1.1.0/service/resource-encapsulation/src/resourceCache/src"
        "iotivity-1.1.0/service/resource-encapsulation/src/resourceClient"
        "iotivity-1.1.0/service/resource-encapsulation/src/serverBuilder/include"
        "iotivity-1.1.0/service/resource-encapsulation/src/serverBuilder/src"
        src
        samples
        lib
)

link_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/iotivity-1.1.0/out/linux/x86_64/release"
        lib/jsoncpp/json
)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(samples)


