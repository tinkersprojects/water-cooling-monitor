
#ifndef Sensor_h
#define Sensor_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

#include <OneWire.h> 
#include <DallasTemperature.h>


class Sensor
{
  public:
    Sensor(uint8_t pin, double _maxTemp);
    double maxTemp;
    byte pin;
    double getTempC();
    bool overMax();
    bool readError();
    
  private:
    OneWire *one_wire; 
    DallasTemperature *sensor;
};



#endif 
