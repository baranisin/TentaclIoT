cmake_minimum_required(VERSION 2.8)
project(Iotivity_bakalarka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CLION false)

if (${CLION})
    set(IOTIVITY_PATH ${CMAKE_SOURCE_DIR}/../iotivity-1.1.0)
    set(IOTIVITY_LIBPATH ${IOTIVITY_PATH}/out/linux/x86_64/release)
else()
    find_path(IOTIVITY_PATH iotivity.pc
    	PATHS
    		 ${CMAKE_SOURCE_DIR}/../iotivity-1.1.0
    		 ${CMAKE_SOURCE_DIR}/iotivity-1.1.0
    		 ${CMAKE_SOURCE_DIR}/../iotivity
    		 ${CMAKE_SOURCE_DIR}/iotivity
    )

    find_path(IOTIVITY_LIBPATH librcs_client.so
    	PATHS
    		${IOTIVITY_PATH}/out/linux/arm/release
    		${IOTIVITY_PATH}/out/linux/x86_64/release
    )

    message(STATUS "IoTivity found at ${IOTIVITY_PATH}")
    message(STATUS "IoTivity libs at ${IOTIVITY_LIBPATH}")
endif ()

include_directories(
		"${IOTIVITY_PATH}/resource/include"
		"${IOTIVITY_PATH}/resource/src"
		"${IOTIVITY_PATH}/resource/csdk/stack/include"
		"${IOTIVITY_PATH}/resource/c_common/ocrandom/include"
		"${IOTIVITY_PATH}/resource/csdk/logger/include"
		"${IOTIVITY_PATH}/resource/oc_logger/include"
		"${IOTIVITY_PATH}/resource/c_common/"
		"${IOTIVITY_PATH}/service/resource-encapsulation/include"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/common/primitiveResource/include"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/common/primitiveResource/src"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/resourceBroker/include"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/resourceBroker/src"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/resourceCache/include"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/resourceCache/src"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/resourceClient"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/serverBuilder/include"
		"${IOTIVITY_PATH}/service/resource-encapsulation/src/serverBuilder/src"
		${CMAKE_SOURCE_DIR}/src
		${CMAKE_SOURCE_DIR}/lib
		${CMAKE_SOURCE_DIR}/I2C_protocol
)


link_directories(
	    ${IOTIVITY_LIBPATH}
		${CMAKE_SOURCE_DIR}/lib/jsoncpp/json
)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(I2C_protocol)
