#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <wiringPi.h>			// Needed for Interrupts from Arduino
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2CDevice.cpp"


using namespace std;
I2CDevice uno = I2CDevice("Arduino Uno Rev3", 4, (char *)"/dev/i2c-1");
I2CDevice uno2 = I2CDevice("Arduino Uno Rev3",6, (char *)"/dev/i2c-1");
I2CDevice uno3 = I2CDevice("Arduino 3", 8, (char *)"/dev/i2c-1");

bool interrupt=false;
int pocetOznameni = 0;

void interrupt_handler()
{
	pocetOznameni++;
	cout << "Pocet oznameni " << int(pocetOznameni) << endl;
	
	//uno.eventHandler();
	//uno2.eventHandler();
	
}

int main(int argc, char *argv [])// TODO Interrupt message 
		
	
{
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
	


	//I2CDevice uno = I2CDevice("Arduino 1", 5, (char *)"/dev/i2c-1");
	//I2CDevice uno2 = I2CDevice("Arduino 2", 6, (char *)"/dev/i2c-1");
//	I2CDevice uno3 = I2CDevice("Arduino 3", 8, (char *)"/dev/i2c-1");
	I2CDevice uno3 = I2CDevice("Arduino 3", 8, (char *)"/dev/i2c-1");
	uno3.getConfiguration();
	uno3.clearConfiguration();
	
	uno3.addResource(1, BOUT, 13, "LED");
	uno3.addResource(2, BOUT, 4, INVERTED,"REL1");
	uno3.addResource(3, BOUT, 5, INVERTED,"REL2");
	uno3.addResource(4, BOUT, 6, INVERTED,"REL3");
	uno3.addResource(5, BOUT, 7, INVERTED,"REL4");
	uno3.addResource(6, BOUT, 8, INVERTED,"REL5");
	uno3.addResource(7, BOUT, 9, INVERTED,"REL6");
	uno3.addResource(8, BOUT, 10,INVERTED, "REL7");
	uno3.addResource(9, BOUT, 11,INVERTED, "REL8");
		
	uno3.sendConfiguration();
	
	uno3.getConfiguration();
	uno3.clearConfiguration();
	
	uno3.addResource(1, BOUT, 13, "LED");
	uno3.addResource(2, BOUT, 4, INVERTED,"REL1");
	uno3.addResource(3, BOUT, 5, INVERTED,"REL2");
	uno3.addResource(4, BOUT, 6, INVERTED,"REL3");
	uno3.addResource(5, BOUT, 7, INVERTED,"REL4");
	
	uno3.sendConfiguration();
	
	uno3.getConfiguration();
	
	while (true)
	{
		
	

	uno3.turnOn(2);
	uno3.turnOn(3);
	uno3.turnOn(4);
	uno3.turnOn(5);
	uno3.turnOn(6);
	uno3.turnOn(7);
	uno3.turnOn(8);
	uno3.turnOn(9);
	

	uno3.turnOff(2);
	uno3.turnOff(3);
	uno3.turnOff(4);
	uno3.turnOff(5);
	uno3.turnOff(6);
	uno3.turnOff(7);
	uno3.turnOff(8);
	uno3.turnOff(9);
	

		sleep(3);
	}
	
	
	//uno.saveConfig(uno.Resources, "cfg01.txt");
	//uno.addResource(1, BOUT, 2, "LEDB");			// Blue LED
	//uno.addResource(2, BINP, 3, "LAST");			// Laser Tranceiver
	//uno.addResource(3, BINP, 4, "LAST");			// Laser Receiver
	//uno.addResource(4, TEMPnHUMI, 6, "TEMP");		// Temperature Sensor
	//uno.addResource(5, BINP, 7, "SOUND");			// Sound Sensor
	//uno.addResource(6, BINP, 8, "PIR");				// Pir Sensor
	//uno.addResource(7, RQRES, 9);					// Request output
	////uno.addResource(8, AINP, 14);					// Sound Sensor
	//
	//uno.saveCurrentConfigToFile("cfg011.txt");
	//uno.sendConfiguration();
	//
	//uno2.addResource(1, BOUT, 6);					// Blue LED
	//uno2.addResource(2, BOUT, 3, "LAST" );			// Laser Tranceiver
	//uno2.addResource(3,BOUT, INVERTED, 4);			// Relay Module
	//uno2.addResource(4, BINP, 5,"BTN");				// Button
	//uno2.addResource(5, BINP, 2, "PIR");			// PIR Sensor
	//uno2.addResource(6, BOUT, 7);					// Red LED
	//uno2.addResource(7, BINP, 8 ,"LAST");			// Laser RECEIVER
	//uno2.addResource(8, BINP, 9 ,"SOUND");			// Sound Sensor
	//uno2.addResource(9, TEMPnHUMI, 10);				// Temperature Sensor
	//uno2.addResource(10, TEMPnHUMI, 11);			// Temperature Sensor
	//uno2.addResource(11, RQRES, 12);				// Request output
	//
	//uno2.saveCurrentConfigToFile("cfg022.txt");
	//uno2.sendConfiguration();
	//uno2.turnOn(2);
	
	
	
	
	
	//cout << "Reading Temperatures from Arduino 2" << endl;
	//uno2.readFromTempHumi(5);
	//
	// - - - - - - - Interrupt
	
	
	wiringPiSetupGpio();
	pinMode(17, INPUT);
	wiringPiISR(17, INT_EDGE_RISING, &interrupt_handler);
	
	
	
	
	while (true)
	{
		delay(5);
		//cout << "cakam" << endl;
	}

	
	// Save to EEPROM
	// Load config from fille
	// Done
	
//	
	return 0;
}
