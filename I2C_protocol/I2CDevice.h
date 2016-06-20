#pragma once

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <bitset>
#include <map>
#include <vector>
#include "I2CEventListener.h"

using namespace std;


// Buffer length
#define MAX_IM_SIZE 16


// Resources types
#define BINP 1
#define BOUT 2
#define AINP 3
#define AOUT 4
#define TEMPnHUMI 5
#define RQRES 6


// Resources logic types
#define NORMAL  0
#define INVERTED  1

// Registers

#define REG_CONFIG         250
#define REG_EEPROM_SAVE    251
#define REG_EEPROM_ERASE   252
#define REG_EEPROM_ISEMPTY 253
#define REG_EVENT		   255



// Analog pins


union
{
	unsigned char bytes[4];
	float value;
	
}Float4Value;

union
{
	unsigned char bytes[2];
	int number;
}Int2Value;

struct  Resource { 
	
	uint8_t number = 0;
	uint8_t type = 0;
	uint8_t pin = 0;
	uint8_t logic = 0;
	uint8_t data[6] = {};
	
};

struct TempHumiMessage {
	float temperature = 0;
	float humidity =  0;
	uint8_t status = -1;
	
};




class I2CDevice
{
private:
	
	string deviceName;
	
	int I2C_address;		// Slave Addresa Arduina
	int I2C_file;			// cesta k i2C suboru v Rpi
	char *I2C_filename;		// Default  (char *)"/dev/i2c-1"
	
	map<uint8_t, Resource> Resources;
	vector<I2CEventListener*> eventListeners;
	
	uint8_t c_BINP = 0;
	uint8_t c_BOUT = 0;
	uint8_t c_AIN = 0;
	uint8_t c_AOUT = 0;
	uint8_t c_TEMPnHUMI = 0;
		
	uint8_t rxBuffer[32];  // receive buffer
	uint8_t txBuffer[32];  // transmit buffer
	
	
	bool interrupt = false;
	int pocet = 0;
	
	
	void AddToCounter(uint8_t type);
	void subFromCounter(uint8_t type);
	
	// I2C
	
	bool Open();
	bool Close();
	
	// Write do I2C zariadenia
	bool Write(uint8_t RegToWrite);
	bool Write(uint8_t RegToWrite, uint8_t value);
	bool Write(uint8_t * txBuffer, int lenghtOfBytesToWrite);
	
	// Read z I2C zariadenia
	bool Read(uint8_t * rxBuffer, int lenghtOfBytesToRead);
	
	// Citanie z Resourcu do rxBuffera
	bool readResource(uint8_t ResourceNumber);
	
public:
	
	
	I2CDevice();
	I2CDevice(string name, int address, char *i2C_dev_file);
	
		
	// Nastavovanie konfiguracie zariadenia
	
	void addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin);
	void addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, char *data);
	void addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, uint8_t *data);
	void addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, uint8_t logic);
	void addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, uint8_t logic, uint8_t *data);
	void addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, uint8_t logic, char *data);
	void removeResource(uint8_t ResourceNumber);
	void PrintResources();
	
	// Uploadovanie konfiguracie do zariadenia 
	bool setConfiguration();	// Nastaví zariadeniu jeho konfiguráciu
	bool getConfiguration();	// Získa konfiguraciu zariadenia 
	bool isConfigured();		// Vrati true ak je zariadenie nakonfigurovane
	
	// EEPROM
	bool EEPROM_IsEmpty();
	bool EEPROM_ConfigSave();
	bool EEPROM_ConfigErase();
	
	// Konfiguracia zo/do suborov
	bool loadConfigurationFromFile(char *fileName);	
	bool saveCurrentConfigToFile(char *fileName);
	
	bool writeDataToResource(uint8_t ResourceNumber, uint8_t value);
	
	
	// Read temperature
	TempHumiMessage readFromTempHumi(uint8_t ResourceNumber);
	float getTemperature(uint8_t ResourceNumber);
	float getHumidity(uint8_t ResourceNumber);
	
	// Read BINP BOUT AINP 
	int readData(uint8_t ResourceNumber);
	
	// Funkcie pre prepnutie BOUT
	bool turnOn(uint8_t ResourceNumber);
	bool turnOff(uint8_t ResourceNumber);
	
	
	void eventHandler();
	
	int numberOfResources();
	map<uint8_t, Resource> getResources();
	Resource getResource(uint8_t ResourceNumber);
	uint8_t getResourceType(uint8_t ResourceNumber);
	uint8_t getResourceLogic(uint8_t ResourceNumber);
	uint8_t getResourcePin(uint8_t ResourceNumber);
	string getResourceData(uint8_t ResourceNumber);

	void registerEventListener(I2CEventListener* listener);
    void notifyListeners(int newValue);
	
	~I2CDevice();
};

