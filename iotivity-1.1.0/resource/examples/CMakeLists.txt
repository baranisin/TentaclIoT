cmake_minimum_required(VERSION 3.5)
project(lightsample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("../../resource/include"
        "../../resource/csdk/stack/include"
        "../../resource/c_common/ocrandom/include"
        "../../resource/csdk/logger/include"
        "../../resource/oc_logger/include"
        "../../resource/c_common/"
        )

link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../out/linux/x86_64/release")

set(SOURCE_FILES simpleserver.cpp)
add_executable(lightsample ${SOURCE_FILES})
target_link_libraries(lightsample oc octbstack oc_logger -lpthread)