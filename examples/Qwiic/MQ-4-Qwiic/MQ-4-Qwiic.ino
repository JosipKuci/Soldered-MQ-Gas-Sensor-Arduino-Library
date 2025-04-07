/*
  MQUnifiedsensor Library - reading an mq4

  Demonstrates the use a mq4 sensor.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez

  Added example
  modified 23 May 2019
  by Miguel Califa

  Updated library usage
  modified 26 March 2020
  by Miguel Califa

  Example is modified by Soldered.com

 This example code is in the public domain.

*/

// Include the library
#include <MQ-Sensor-SOLDERED.h>

#define numOfCalibrations 10 //How many readings of R0 we take to get average measurement

//Create an instance of the sensor object
MQ4 mq4; 

//To configure the sensor to measure LPG, you can create a custom configuration for
//the sensor method, more details here: **LINK TO DOCS**
/*
const struct sensorType MQ4_LPG_config={
  1, //Regression method type (a*ratio^b)

  4.4, //Rs/R0 in clean air

  //Coefficient values calculated (LPG)
  3811.9, //a

  -3.113, //b
  
};*/

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    //Initialize I2C connection with sensor, if it fails inform user
    if(!mq4.begin(0x30))
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
    bool calibrationResult=mq4.calibrateSensor(numOfCalibrations);
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
  mq4.update();      // Update data, read voltage level from sensor
  Serial.println("CH4: " + String(mq4.readSensor())+"ppm"); // Print the readings to the serial monitor
  delay(500);        // Sampling frequency
}