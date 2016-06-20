#include "I2CDevice.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

I2CDevice::I2CDevice()
{
	
}


I2CDevice::~I2CDevice()
{
}

I2CDevice::I2CDevice(string name, int address, char *i2C_dev_file)
{
	
	this->I2C_address = address;
	this->I2C_filename = i2C_dev_file;
	
}

// - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - 


				  

// - - - - - - - - - - - - - - - I2C - - - - - - - - - - - - - - - - - - -

bool I2CDevice::Open()
{
	//----- OPEN THE I2C BUS -----
		
	//cout << "Opening i2c on /dev/i2c-1" << endl;
	if ((this->I2C_file = open(this->I2C_filename, O_RDWR)) < 0)
	{
		cout << "Failed to open the i2c bus" << endl;
		return false;
	}
		
	if (ioctl(this->I2C_file, I2C_SLAVE, this->I2C_address) < 0)
	{
		cout << "Failed to acquire bus access and/or talk to slave.\n" << endl;
		
		return false;
	}

	return true;
}

bool I2CDevice::Close()
{
	if ((this->I2C_file = close(this->I2C_file)) < 0)
	{
		cout << "Failed to close the i2c bus" << endl;
		return false;
	}
	return true;
}

bool I2CDevice::Write(uint8_t RegToWrite)
{

	u_int8_t ar[1];
	ar[0] = RegToWrite;
	return this->Write(ar, 1);

}

bool I2CDevice::Write(uint8_t RegToWrite, uint8_t value)
{
	u_int8_t ar[2];
	ar[0] = RegToWrite;
	ar[1] = value;
	return this->Write(ar, 2);
}

bool I2CDevice::Write(uint8_t * txBuffer, int lenghtOfBytesToWrite)
{
	
	if (!this->Open()) return false;
	//----- WRITE BYTES -----
	if (write(this->I2C_file, txBuffer, lenghtOfBytesToWrite) != lenghtOfBytesToWrite)	
	{
		cout << "Failed to write to the i2c bus.\n" << endl;
		return false;
	}
	if (!this->Close()) {
		return false;
	} 
			
	return true;	
}

bool I2CDevice::Read(uint8_t * rxBuffer, int lenghtOfBytesToRead)
{
	
	if (!this->Open()) {
		return false;
	} 
		
	if (read(this->I2C_file, rxBuffer, lenghtOfBytesToRead) != lenghtOfBytesToRead) {
		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
		//ERROR HANDLING: i2c transaction failed
		cout << "Failed to read from the i2c bus.\n" << endl;
	
		return false;
	}
	else
	{
			
		if (!this->Close()) {
			return false;
		} 
			
			
		//cout << "Read data ... Done "  << endl;
		return true;			
	}
	return true;
}

// - - - - - - - - - - - - - - - -Add Resource - - -- - - - - - - - - - - - - - - 

void I2CDevice::addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin)
{
	Resource a;
	a.number = ResourceNumber;
	a.type = type;
	a.pin = pin;
	a.logic = 0;
	
	this->Resources[ResourceNumber] = a;
	AddToCounter(type);
}

void I2CDevice::addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, uint8_t logic)
{
	
	Resource a;
	a.number = ResourceNumber;
	a.type = type;
	a.pin = pin;
	a.logic = logic;
	
	this->Resources[ResourceNumber] = a;	
	AddToCounter(type);
	
}


void I2CDevice::addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, char *data)
{
	Resource a;
	a.number = ResourceNumber;
	a.type = type;
	a.pin = pin;
	a.logic = 0;
	
	char databuf[6];
	
	if (sizeof(a.data) < sizeof(data))
	{
		cout << "Wrong data lenght" << endl;
		return;
	}
	

	memcpy(a.data, data, sizeof(a.data));
	
	this->Resources[ResourceNumber] = a;
	AddToCounter(type);
	
	
}


void I2CDevice::addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, uint8_t *data)
{
	
	Resource a;
	a.number = ResourceNumber;
	a.type = type;
	a.pin = pin;
	a.logic = 0;
	
	
	if (sizeof(a.data) < sizeof(data))
	{
		cout << "Wrong data lenght" << endl;
		return;
	}
	
	
	memcpy(a.data, data, sizeof(data));
	
	this->Resources[ResourceNumber] = a;
	AddToCounter(type);
}

void I2CDevice::addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, uint8_t logic, uint8_t *data)
{
	
	Resource a;
	a.number = ResourceNumber;
	a.type = type;
	a.pin = pin;
	a.logic = logic;
	
	
	if (sizeof(a.data) < sizeof(data))
	{
		cout << "Wrong data lenght" << endl;
		return;
	}
	memcpy(a.data, data, sizeof(data));
		
	this->Resources[ResourceNumber] = a;	
	AddToCounter(type);
}

void I2CDevice::addResource(uint8_t ResourceNumber, uint8_t type, uint8_t pin, uint8_t logic, char *data)
{
	
	Resource a;
	a.number = ResourceNumber;
	a.type = type;
	a.pin = pin;
	a.logic = logic;
	
	
	if (sizeof(a.data) < sizeof(data))
	{
		cout << "Wrong data lenght" << endl;
		return;
	}
	memcpy(a.data, data, sizeof(data));
		
	this->Resources[ResourceNumber] = a;	
	AddToCounter(type);
	
}

void I2CDevice::removeResource(uint8_t ResourceNumber)
{
	
	this->subFromCounter(Resources[ResourceNumber].type);
	Resources.erase(ResourceNumber);
}


// - - - - - - - - - - - - - - - - Configuration  - - -- - - - - - - - - - - - - - - 

bool I2CDevice::setConfiguration()
{
	
	// Poslanie prvej spravy v ktorej sa nastavi velkost jednotlivych bufferov
	uint8_t pocet = Resources.size();
	
	txBuffer[0] = REG_CONFIG;
	txBuffer[1] = pocet;		// Logic number of Resource 
	
	if (!this->Write(txBuffer, 2))return false;	
	
	for (map<uint8_t, Resource>::iterator kv = Resources.begin(); kv != Resources.end(); ++kv)
	{
		
		txBuffer[0] = REG_CONFIG;
		
		txBuffer[1] = kv->first;			// Logic number of Resource 
		txBuffer[2] = kv->second.type;		// Type of Resource
		txBuffer[3] = kv->second.logic;		// Logic if 1 inverted (HIGH = LOW)
		txBuffer[4] = kv->second.pin;		// Pin on Board
		
		txBuffer[5] = kv->second.data[0];
		txBuffer[6] = kv->second.data[1];
		txBuffer[7] = kv->second.data[2];
		txBuffer[8] = kv->second.data[3];
		txBuffer[9] = kv->second.data[4];
		txBuffer[10] = kv->second.data[5];
		
		if (!this->Write(txBuffer, 11))return false;	
	
	}
	
	return true;
}


bool I2CDevice::getConfiguration()
{
	
	map<uint8_t, Resource> result;
	Resource a;
	this->Resources.clear();
	// Napisat si define pre velkost buffera pre REG_GET_CONFIGU
	if (!this->Write(REG_CONFIG)) return false;	
		
	while (true) {	
		if (this->Read(rxBuffer, sizeof(Resource)+1)) {
			if (rxBuffer[0] == REG_CONFIG && rxBuffer[1] != 0) {
				Resource a;
				a.number = rxBuffer[1];
				a.type = rxBuffer[2];
				a.logic = rxBuffer[3];
				a.pin = rxBuffer[4];
				
				a.data[0] = rxBuffer[5];				
				a.data[1] = rxBuffer[6];
				a.data[2] = rxBuffer[7];
				a.data[3] = rxBuffer[8];
				a.data[4] = rxBuffer[9];
				a.data[5] = rxBuffer[10];
				
				
				
				this->Resources[rxBuffer[1]] = a;
				result[rxBuffer[1]] = a;
			}else {
				break;
			} 
		}else {
			return false;
		}
	}
	cout << "Configuration Downloaded" << endl;

	return true;
	
}

bool I2CDevice::isConfigured()
{
	if (!this->Write(REG_CONFIG)) return false;	
		

	if (this->Read(rxBuffer, sizeof(Resource)+1)) {
		if (rxBuffer[0] == REG_CONFIG && rxBuffer[1] != 0) {
			return true;
		}
	}

	return false;
	
}

bool I2CDevice::EEPROM_ConfigSave()
{
	if (!this->Write(REG_EEPROM_SAVE)) return false;	
	
	return true;
}


bool I2CDevice::EEPROM_ConfigErase()
{
	if (!this->Write(REG_EEPROM_ERASE)) return false;	
	
	return true;
	
}

bool I2CDevice::EEPROM_IsEmpty()
{
	if (!this->Write(REG_EEPROM_ISEMPTY)) return false;
	
	if (this->Read(rxBuffer, 2)) {
		if (rxBuffer[0] == REG_EEPROM_ISEMPTY) {
			if (rxBuffer[2] == 1)return false;
		};
		
	}
	return true;
}


// - - - - - -  Ukladanie a Nacitavanie konfiguracie do/zo subora
bool I2CDevice::loadConfigurationFromFile(char *fileName)
{
	
	string line;
	ifstream file(fileName);
	int iter;
	
	
	
	int resNum2;
	int type2;
	int logic2;
	int pin2;	
	uint8_t data2[6];
	
	
	string resNum;
	string type;
	string logic;
	string pin;	
	string data;
	
	string subline;
	
	this->Resources.clear();
	
	
	if (file.is_open())
	{
		while (getline(file, line))
		{
			
			
			subline = line;
					
					
			iter = subline.find(',');
			resNum = subline.substr(0, iter);
			subline = subline.substr(iter + 1, subline.length());
			
			iter = subline.find(',');
			type = subline.substr(0, iter);
			subline = subline.substr(iter + 1, subline.length());
			
			iter = subline.find(',');
			logic = subline.substr(0, iter);
			subline = subline.substr(iter + 1, subline.length());
			
			iter = subline.find(',');
			pin = subline.substr(0, iter);
			subline = subline.substr(iter + 1, subline.length());
			
			iter = subline.find(',');
			data = subline.substr(0, iter);
			subline = subline.substr(iter + 1, subline.length());
			
			
			sscanf(resNum.c_str(), "%d", &resNum2);
			sscanf(type.c_str(), "%d", &type2);
			sscanf(logic.c_str(), "%d", &logic2);
			sscanf(pin.c_str(), "%d", &pin2);
	
			strcpy((char *)data2, data.c_str());
	
			this->addResource((uint8_t)resNum2, (uint8_t)type2, (uint8_t)logic2, (uint8_t)pin2, data2);

		}
		file.close();
	}
	
	
}
bool I2CDevice::saveCurrentConfigToFile(char *fileName)
{
	ofstream file;
	file.open(fileName);
	
	for (map<uint8_t, Resource>::iterator kv = Resources.begin(); kv != Resources.end(); ++kv)
	{
		
		file << 
			int(kv->first)			<< "," <<  
			int(kv->second.type)	<< "," <<  
			int(kv->second.logic)	<< "," << 
			int(kv->second.pin)		<< ",";
		
		for (uint8_t i = 0; i <  strlen((char *)kv->second.data); i++)
		{
			file << char(kv->second.data[i]);
		}
		
		file << endl; 		
	}
	file.close();
	
}
// - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - 
void I2CDevice::PrintResources()
{	
	
	cout << "Device addres: " << this->I2C_address << endl;
	for (map<uint8_t, Resource>::iterator kv = Resources.begin(); kv != Resources.end(); ++kv)
	{
		
		cout << "Number: "	<< int(kv->first)			<< "," <<  
				"Type: "	<< int(kv->second.type)		<< "," <<  
				"Logic: "	<< int(kv->second.logic)	<< "," << 
				"Pin: "		<< int(kv->second.pin)		<< ", " <<
				"Data: ";
		for (uint8_t i = 0; i <  strlen((char *)kv->second.data); i++)
		{
			cout << char(kv->second.data[i]);
		}
		
		cout << endl;
	}
	
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool I2CDevice::writeDataToResource(uint8_t ResourceNumber, uint8_t value)
{
	
	if (this->Resources.count(ResourceNumber))
	{
		switch (this->Resources[ResourceNumber].type)
		{
		case BOUT:
		case AOUT:
		
			break;
		default:
			cout << "Can not write to resource:" << "#" << int(ResourceNumber) << " value:  " << int(value)  << endl;
			return false;
			break;
		}
		
		txBuffer[0] = ResourceNumber;
		txBuffer[1] = value;
	
		return this->Write(txBuffer, 2);
	}
	else
	{
		cout << "This key in resources dont exist" << endl;
		return false;
	}
	

	
	return false;
}
	
bool I2CDevice::turnOn(uint8_t ResourceNumber)
{
	return this->writeDataToResource(ResourceNumber, 1);
}

bool I2CDevice::turnOff(uint8_t ResourceNumber)
{
	return this->writeDataToResource(ResourceNumber, 0);
}

void I2CDevice::AddToCounter(uint8_t type)
{
	switch (type)
	{
	
	case BINP:
		this->c_BINP++;
		break;
	case BOUT:
		this->c_BOUT++;
		break;
	case AINP:
		this->c_AIN++;
		break;
	case AOUT:
		this->c_AOUT++;
		break;
	case TEMPnHUMI:
		this->c_TEMPnHUMI++;
		break;
		
	default:
		break;
	}
	
}

void I2CDevice::subFromCounter(uint8_t type)
{
	switch (type)
	{
	
	case BINP:
		this->c_BINP--;
		break;
	case BOUT:
		this->c_BOUT--;
		break;
	case AINP:
		this->c_AIN--;
		break;
	case AOUT:
		this->c_AOUT--;
		break;
	case TEMPnHUMI:
		this->c_TEMPnHUMI--;
		break;
		
	default:
		break;
	}
}



bool I2CDevice::readResource(uint8_t ResourceNumber)
{// Treba premysliet aku hodnotu tu bode vracat pre inverted logic
	

	int n_readBytes; 

	switch (this->Resources[ResourceNumber].type)
	{
		
	case BOUT:
	case BINP:
		n_readBytes = 3;
		break;
	case AINP:
		n_readBytes = 4;
	case TEMPnHUMI:
		n_readBytes = 11;
		//n_readBytes = sizeof(TempHumiMessage); // toto dava 12
		
		break;
	default:
		cout << "Can not read from this Resource " << "#" << int(ResourceNumber) << endl;
		break;
	}
	
	if (!this->Write(ResourceNumber)) return false;
	else {
		if (!this->Read(rxBuffer, n_readBytes)) return false;
		if (rxBuffer[1] == Resources[ResourceNumber].type && rxBuffer[0] == ResourceNumber) {
			// Resource precitalo uspesne 	
			//cout << "Data sa podarilo z Resourcu precitat uspesne " << endl;
		}
		else
		{
			cout << " Data sa nepodarilo precitat" << endl;	
		}
		
	}
	return true;
}

TempHumiMessage I2CDevice::readFromTempHumi(uint8_t ResourceNumber)
{
	
	TempHumiMessage a;
	if (!readResource(ResourceNumber))return a;
	if (Resources[ResourceNumber].type ==  TEMPnHUMI)
	{
//		ERROR_NONE = 0,
//		ERROR_TIMEOUT = 1,
//		ERROR_CHECKSUM =2 ,
		
		a.status = rxBuffer[2];
		Float4Value.bytes[0] = rxBuffer[3];
		Float4Value.bytes[1] = rxBuffer[4];
		Float4Value.bytes[2] = rxBuffer[5];
		Float4Value.bytes[3] = rxBuffer[6];

		a.temperature = Float4Value.value;
		
		Float4Value.bytes[0] = rxBuffer[7];
		Float4Value.bytes[1] = rxBuffer[8];
		Float4Value.bytes[2] = rxBuffer[9];
		Float4Value.bytes[3] = rxBuffer[10];
		float hum = Float4Value.value;
		a.humidity = Float4Value.value;
		cout << "Status :" << int(a.status) << endl;
		cout << "Data from res :[" << int(ResourceNumber) << "] Temp: " <<  float(a.temperature) << " Humi : " << float(a.humidity) << endl;

		return a;

	}
	
	
	
	return a;
	
	
	
}

float I2CDevice::getTemperature(uint8_t ResourceNumber)
{
	
	TempHumiMessage temp = readFromTempHumi(ResourceNumber);
	
	return temp.temperature;
}


float I2CDevice::getHumidity(uint8_t ResourceNumber)
{
	TempHumiMessage temp = readFromTempHumi(ResourceNumber);
	return temp.humidity;
}



int I2CDevice::readData(uint8_t ResourceNumber)
{
	int result = -999;
	if (!readResource(ResourceNumber))return result;
	
	switch (this->Resources[ResourceNumber].type)
	{                                          
	case BINP:
	case BOUT:
		result = int(rxBuffer[2]);
		break;
	case AINP:	
		Int2Value.bytes[0] = rxBuffer[2];
		Int2Value.bytes[1] = rxBuffer[3];
		result = int(Int2Value.number);
		break;
	default:
		cout << "Bad Read function for this type of Resource" << endl;
		break;
	}
	
	
	return result;
}

void I2CDevice::eventHandler()
{	
	
	if (this->interrupt)return ;
	else
	{
		this->interrupt = true;
		this->pocet++;
	}
	
	
	int ResNum = 0;
	u_int8_t ResType;
	uint8_t ResValue;
		
	this->turnOn(1);	// Zapne signalizacnu diodu
	
	if (this->Write(REG_EVENT))
	{
		
		do
		{
			if (this->Read(rxBuffer, 5))
			{
				
				ResNum = rxBuffer[0]; 
				ResType = rxBuffer[1];
				ResValue = rxBuffer[2];
				switch (ResType)
				{
				case 0 :

					interrupt = false;
					break;
				case BINP:
					cout  << "Device address [" << int(this->I2C_address) << "] Resource [" << int(ResNum) << " : ";
					for (uint8_t i = 0; i <  strlen((char *)Resources[ResNum].data); i++){
                        cout << char(Resources[ResNum].data[i]);
                    }
                    cout <<  "] change to " << int(ResValue) << endl;
                    notifyListeners(ResNum, int(ResValue));
					break;

				default:
					cout << "Bad receive resource number" << endl;
					break;
				}
				
				
			}
			
		} while (ResNum != 0);
		
		
	}

	this->turnOff(1);	// vypne signalizacnu diodu
	
}

int I2CDevice::numberOfResources()
{
	return this->Resources.size();
}

// Getovanie Resourcov
map<uint8_t, Resource> I2CDevice::getResources()
{
	return this->Resources;
}

void I2CDevice::registerEventListener(uint8_t ResourceNumber, I2CEventListener* listener) {
    cout << "Listener registered " << endl;
    if(eventListeners[ResourceNumber].size() == 0){
        eventListeners[ResourceNumber] = vector{};
    }
	eventListeners[ResourceNumber].push_back(listener);
    cout << "Listeners size: " << eventListeners.size() << endl;
}




Resource  I2CDevice::getResource(uint8_t ResourceNumber)
{
	return this->Resources[ResourceNumber];	
}

uint8_t I2CDevice::getResourceType(uint8_t ResourceNumber)
{
	return this->Resources[ResourceNumber].type;
}

uint8_t I2CDevice::getResourceLogic(uint8_t ResourceNumber)
{
	return this->Resources[ResourceNumber].logic;
}

uint8_t I2CDevice::getResourcePin(uint8_t ResourceNumber)
{
	return this->Resources[ResourceNumber].pin;
}

string I2CDevice::getResourceData(uint8_t ResourceNumber)
{
	string result((char *)this->Resources[ResourceNumber].data); 
	return result;
}

void I2CDevice::notifyListeners(uint8_t ResourceNumber, int newValue) {
    for(I2CEventListener* listener : eventListeners.at(ResourceNumber)){
        cout << "Notify listener ..." << endl;
        listener->onEvent(newValue);
    }
}




