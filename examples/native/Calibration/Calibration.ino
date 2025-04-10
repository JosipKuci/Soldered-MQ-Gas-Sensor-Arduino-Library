/*
  Example that shows calibrating a sensor indefinitely
*/

// Include the library
#include "MQ-Sensor-SOLDERED.h"

unsigned long counter = 1;

// Predefined microcontroller pins for AO sensor pin (microcontroller dependent)
// You can change the pin to suit your setup.
#if defined(__AVR__) || defined(STM32)
#define SENSOR_ANALOG_PIN A1
#elif defined(ESP32)
#define SENSOR_ANALOG_PIN 34
#else
#define SENSOR_ANALOG_PIN 5
#endif

//Create an instance of the sensor object
MQ135 mq135(SENSOR_ANALOG_PIN); 

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Initialize I2C communication with the sensor
    mq135.begin(); 

    Serial.println("MQ135 - Calibration");
    Serial.println("Note - Make sure you are in a clean room and the sensor has been pre-heating for almost 24 hours");
    Serial.println("Current calibration | R0 value");
}

void loop()
{
    mq135.update();
    // Read the sensor and print to serial monitor
    float lecture = mq135.calibrate(MQ135_config.Rs_R0_ratio);
    // Print in serial monitor
    Serial.print(counter);
    Serial.print(" | ");
    Serial.println(lecture);
    // Increment counter
    counter++;
    // Wait to measure next sample
    delay(400);
}
