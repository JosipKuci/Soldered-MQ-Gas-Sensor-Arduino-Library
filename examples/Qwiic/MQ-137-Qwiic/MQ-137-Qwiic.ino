/*
  MQUnifiedsensor Library - reading an MQ137

  Demonstrates the use of an MQ137 sensor.
  Library originally added 01 May 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez

  Modified to work with MQ137 Ammonia Gas Sensor
  by Robert@Soldered.com

  Wiring:
  Connect the sensor to your Dasduino board via an easyC cable or using the I2C pins

  This example code is in the public domain.
*/

// Include the library
#include <MQ-Sensor-SOLDERED.h>

#define numOfCalibrations 10 //How many readings of R0 we take to get average measurement

//Create an instance of the sensor object
MQ137 mq137; 

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    //Initialize I2C connection with sensor, if it fails inform user
    if(!mq137.begin(0x30))
    {
      Serial.println("Failed to initialize I2C communication, check wiring");
      while(1)
      {}
    }

    /*****************************  MQ Calibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor after it has been pre-heated for 48h
    // and now is in a clean air enviorment, and it will setup the R0 value.
    // This routine not need to execute on every restart, you can load your R0 into flash memory and read it on startup
    
    Serial.print("Calibrating please wait.");
    bool calibrationResult=mq137.calibrateSensor(numOfCalibrations);
    if(!calibrationResult) //Check if the sensor was properly calibrated
    {
      Serial.println("There was an error reading the sensor, check connection and try again");
      while(1)
      {}
    }
    Serial.print("Calibration done!");

    /*****************************  MQ Calibration ********************************************/
}

void loop()
{
  mq137.update();      // Update data, read voltage level from sensor
  Serial.println("NH3: " + String(mq137.readSensor())+"ppm"); // Print the readings to the serial monitor
  delay(500);        // Sampling frequency
}