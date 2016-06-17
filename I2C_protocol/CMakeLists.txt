add_executable(bridge
        I2CBridge.cpp
        I2CDevice.cpp
        I2CDevice.h
        SwitchServer.cpp
        SwitchServer.h)
target_link_libraries(bridge wiringPi tentacliotServer)