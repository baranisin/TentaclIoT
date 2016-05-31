project(jsoncpp)
include_directories(jsoncpp.cpp json/json-forwards.h json/json.h)
add_subdirectory(json)

add_library(jsoncpp jsoncpp.cpp json)