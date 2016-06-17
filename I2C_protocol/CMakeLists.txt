add_executable(bridge I2CBridge.cpp I2CDevice.cpp I2CDevice.h)
target_link_libraries(wiringPi tentacliotServer)