// Include the library
#include <MQ-Sensor-SOLDERED.h>

#define numOfCalibrations 10 //How many readings of R0 we take to get average measurement

// Predefined microcontroller pins for AO sensor pin (microcontroller dependent)
// You can change the pin to suit your setup.
#if defined(__AVR__) || defined(STM32)
#define SENSOR_ANALOG_PIN A1
#elif defined(ESP32)
#define SENSOR_ANALOG_PIN 34
#else
#define SENSOR_ANALOG_PIN 5
#endif

// Create an instance of the object
MQ138 mq138(SENSOR_ANALOG_PIN);


//If you want to measure a different gas or measure using different parameters, you can do that by 
//Creating a custom confic structure with the values, here we will change the measured gas from toluene
//to alcohol

/*
    Linear regression:
    GAS        | a        | b
    Alcohol    | -0.46099 | 0.0681
    Acetone    | -0.52356 | 0.49225
    Toluene    | -0.4434  | 0.15397
*/
const struct sensorType MQ138CustomConfig={
    0, //Regression method type
    
    1, //Rs/R0 in clean air
    
    //Coefficient values calculated (Alcohol)
    -0.46099, //a
    
    0.0681, //b
    };


void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    //Initialize I2C connection with sensor with custom config
    mq138.begin(MQ138CustomConfig);

    /*****************************  MQ Calibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor after it has been pre-heated for 48h
    // and now is in a clean air enviorment, and it will setup the R0 value.
    // This routine not need to execute on every restart, you can load your R0 into flash memory and read it on startup
    
    Serial.print("Calibrating please wait.");
    bool calibrationResult=mq138.calibrateSensor(numOfCalibrations);
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
  mq138.update();      // Update data, read voltage level from sensor
  Serial.println("Alcohol: " + String(mq138.readSensor())+"ppm"); // Print the readings to the serial monitor
  delay(500);        // Sampling frequency
}