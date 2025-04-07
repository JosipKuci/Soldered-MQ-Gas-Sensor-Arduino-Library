/*
  MQUnifiedsensor Library - calibrating an MQ2

  Demonstrates the indefinite calibration of a MQ2 sensor with easyC.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez

  Added example
  modified 27 May 2019
  by Miguel Califa

  Example is modified by Soldered.com

 This example code is in the public domain.

*/

// Include the library
#include "MQ-Sensor-SOLDERED.h"


unsigned long counter = 0;

//Create an instance of the sensor object
MQ2 mq2; 

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Initialize I2C communication with the sensor
    mq2.begin(0x30); 

    Serial.println("MQ2 - Calibration");
    Serial.println("Note - Make sure you are in a clean room and the sensor has been pre-heating for almost 4 hours");
    Serial.println("Current calibration | R0 value");
}

void loop()
{
    mq2.update();
    // Read the sensor and print to serial monitor
    float lecture = mq2.calibrate(MQ2_config.Rs_R0_ratio);
    // Print in serial monitor
    Serial.print(counter);
    Serial.print(" | ");
    Serial.println(lecture);
    // Increment counter
    counter++;
    // Wait to measure next sample
    delay(400);
}
