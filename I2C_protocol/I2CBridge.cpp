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
#include <SwitchServer.h>
#include "I2CDevice.h"



using namespace std;


I2CDevice uno1 = I2CDevice("Arduino 1", 5, (char *)"/dev/i2c-1");
I2CDevice uno2 = I2CDevice("Arduino 2", 6, (char *)"/dev/i2c-1");
I2CDevice uno3 = I2CDevice("Arduino 3", 8, (char *)"/dev/i2c-1");

void interrupt_handler()
{
	uno1.eventHandler();
	uno2.eventHandler();
	
}

int main(int argc, char *argv [])
{
	//UNO1
	if (!uno1.isConfigured())
	{
		uno1.getConfiguration();
		uno1.PrintResources();
		
	}
	else
	{
		uno1.addResource(1, BOUT, 2, "LEDB");			// Blue LED
		uno1.addResource(2, BINP, 3, "LAST");			// Laser Tranceiver
		uno1.addResource(3, BINP, 4, "LAST");			// Laser Receiver
		uno1.addResource(4, TEMPnHUMI, 6, "TEMP");		// Temperature Sensor
		uno1.addResource(5, BINP, 7, "SOUND");			// Sound Sensor
		uno1.addResource(6, BINP, 8, "PIR");				// Pir Sensor
		uno1.addResource(7, RQRES, 9, "RQ");				// Request output
		uno1.addResource(8, AINP, 14);					// Sound Sensor
		uno1.setConfiguration();
		uno1.PrintResources();
	}

	
	// UNO2
	if (uno2.isConfigured())
	{
		uno2.getConfiguration();
		uno2.PrintResources();
	}
	else
	{
		
		uno2.addResource(1,	 BOUT, 6, "LEDB2");				// Blue LED
		uno2.addResource(2,	 BOUT, 3, "LASTR" );			// Laser Tranceiver
		uno2.addResource(3,	 BINP, 5, "BTN" );				// Button
		uno2.addResource(4,	 BINP, 2, "PIR" );				// PIR Sensor
		uno2.addResource(5,	 BOUT, 7, "LEDR2" );			// Red LED
		uno2.addResource(6,	 BINP, 8 , "LASRE" );			// Laser RECEIVER
		uno2.addResource(7,	 BINP, 9 , "SOUND" );			// Sound Sensor
		uno2.addResource(8, TEMPnHUMI, 11, "TEMP4" );		// Temperature Sensor
		uno2.addResource(9, RQRES, 12, "RQ");				// Request output
		
		uno2.setConfiguration();
		uno2.PrintResources();
		
	}
	
	uno2.turnOn(2);
	uno2.turnOn(5);

	//UNO3
	if (uno3.isConfigured())
	{	
		
		uno3.getConfiguration();
		uno3.PrintResources();
		
	}
	else
	{
		uno3.addResource(1, BOUT, 13, "LEDB3");
		uno3.addResource(2, BOUT, 4,  INVERTED, "REL1");
		uno3.addResource(3, BOUT, 5,  INVERTED, "REL2");
		uno3.addResource(4, BOUT, 6,  INVERTED, "REL3");
		uno3.addResource(5, BOUT, 7,  INVERTED, "REL4");
		uno3.addResource(6, BOUT, 8,  INVERTED, "REL5");
		uno3.addResource(7, BOUT, 9,  INVERTED, "REL6");
		uno3.addResource(8, BOUT, 10, INVERTED, "REL7");
		uno3.addResource(9, BOUT, 11, INVERTED, "REL8");
		
		uno3.setConfiguration();
		uno3.PrintResources();
	}

	SwitchServer uno3server = SwitchServer("uno3", uno3);
	sleep(5);
	uno3server.test();

//	uno3.turnOn(1);
//	uno3.turnOn(2);
//	uno3.turnOn(3);
//	uno3.turnOn(4);


	uno2.readFromTempHumi(5);

//	wiringPiSetupGpio();
//	pinMode(17, INPUT);
//	wiringPiISR(17, INT_EDGE_RISING, &interrupt_handler);
//
//	while (true)
//	{
//		sleep(5);
//	}
////
	return 0;
}
