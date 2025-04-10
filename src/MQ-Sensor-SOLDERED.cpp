/**
 **************************************************
 *
 * @file        MQ-Sensor-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Zvonimir Haramustek for soldered.com
 ***************************************************/

#include "MQ-Sensor-SOLDERED.h"

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
bool MQ_Sensor::begin(int _addr)
{
    if (_addr)
    {
        init(_addr);
        Wire.beginTransmission(_addr);
        if(Wire.endTransmission()!=0)
        {
            return false;
        }
    }
    setConfiguration(this->sensor_type);
    return true;
}
bool MQ_Sensor::begin(int _addr, sensorType configcustom)
{
    if (_addr)
    {
        init(_addr);
        Wire.beginTransmission(_addr);
        if(Wire.endTransmission()!=0)
        {
            return false;
        }
    }
    else
    {
        if (aPin != -1)
            pinMode(aPin, INPUT);
        if (dPin != -1)
            pinMode(dPin, INPUT);
    }
    this->sensor_type=configcustom;
    setConfiguration(this->sensor_type);
    return true;
}

void MQ_Sensor::begin()
{
    if (aPin != -1)
        pinMode(aPin, INPUT);
    if (dPin != -1)
        pinMode(dPin, INPUT);
    setConfiguration(this->sensor_type);
}

void MQ_Sensor::begin(sensorType configcustom)
{
    if (aPin != -1)
        pinMode(aPin, INPUT);
    if (dPin != -1)
        pinMode(dPin, INPUT);
    this->sensor_type=configcustom;
    setConfiguration(this->sensor_type);
}



/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 *
 * @returns bool            Is sensor triggered
 */
bool MQ_Sensor::digitalRead()
{
    return ::digitalRead(dPin);
}

void MQ_Sensor::setRegressionModel(const sensorType& type)
{
    this->setRegressionMethod(type.regression_method); //_PPM =  a*ratio^b
    this->setA(type.coefficient_a);
    this->setB(type.coefficient_b);
}


bool checkCalibration(float calcR0)
{
    return !(isinf(calcR0) || calcR0 == 0);
}

bool MQ_Sensor::calibrateSensor(int numOfCalibrations)
{
    float calcR0 = 0;
    for (int i = 1; i <= numOfCalibrations; i++)
    {
        this->update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += this->calibrate(this->sensor_type.Rs_R0_ratio);
        Serial.print(".");
    }
    if(!checkCalibration(calcR0))
    {
        return false;
    }
    this->setR0(calcR0 / numOfCalibrations);
    return true;
    
}

void MQ_Sensor::setConfiguration(sensorType& type)
{
    this->setRegressionModel(type);
}