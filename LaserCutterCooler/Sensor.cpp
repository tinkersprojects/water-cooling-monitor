#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Sensor.h"

Sensor::Sensor(uint8_t _pin, double _maxTemp)
{
  maxTemp = _maxTemp;
  pin = _pin;
  one_wire = new OneWire(pin); 
  sensor = new DallasTemperature(one_wire);
  sensor->begin();
}

double Sensor::getTempC()
{
  sensor->requestTemperatures();
  return sensor->getTempCByIndex(0);
}

bool Sensor::overMax()
{
  return this->getTempC() > maxTemp;
}

bool Sensor::readError()
{
  return false; //for now
}


