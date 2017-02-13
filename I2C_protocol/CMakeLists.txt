add_executable(bridge
        I2CBridge.cpp
        I2CDevice.cpp
        I2CDevice.h
        I2CEventListener.h)
target_link_libraries(bridge wiringPi tentacliot)