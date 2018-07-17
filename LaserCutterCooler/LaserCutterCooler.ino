#include <LiquidCrystal.h>
#include "Sensor.h"

#define buzzerpin 10
#define flowPin 2
#define MinFlowRate 100

LiquidCrystal lcd(2, 4, 5, 6, 7, 8);

Sensor Tank(14,40);
Sensor Motor(15,40);
Sensor Beforelaser(16,40);
Sensor Afterlaser(17,40);
Sensor Aftercooling(18,40);

 double flowRate;
unsigned int flowcount;
unsigned long lastrest= 0;

void Flow()
{  
  if(lastrest+500<millis())
  {
    lastrest = millis();
    flowRate = (flowcount * 2.25 * 60)/1000;
    flowcount = 0;
    return;
  }
   flowcount++;
}

void setup() 
{
  lcd.begin(16, 2);
  pinMode(buzzerpin,OUTPUT);
  pinMode(flowPin, INPUT);
  attachInterrupt(1, Flow, RISING);
  interrupts();
}

void loop() 
{
  if(!displayWarning())
  {
    displayData();
  }
}

void displayData()
{
  lcd.setCursor(0,0);
  switch(millis()/1300%6)
  {
    case 0:
      displaySensor(&Tank,"Tank");
      break;
    case 1:
      displaySensor(&Motor,"Motor");
      break;
    case 2:
      displaySensor(&Beforelaser,"Before Laser");
      break;
    case 3:
      displaySensor(&Afterlaser,"After Laser");
      break;
    case 4:
      displaySensor(&Aftercooling,"After Cooling");
      break;
    case 5:
      displayFlowMeter();
      break;
  }
}

bool displayWarning()
{
  int error = 0;
  error += displayFlowMeterError();
  error += displaySensorError(&Tank,"Tank");
  error += displaySensorError(&Motor,"Motor");
  error += displaySensorError(&Beforelaser,"Before Laser");
  error += displaySensorError(&Afterlaser,"After Laser");
  error += displaySensorError(&Aftercooling,"After Cooling");
  return error>0;
}


bool displayFlowMeterError()
{
  if(flowRate < MinFlowRate)
  {
    lcd.setCursor(0,0);
    lcd.print("Flow: ");
    lcd.print(flowRate);
    lcd.print("L/Min");
    lcd.setCursor(0,1);
    lcd.print("Low Flow");
    makesound();
    return true;
  }
  return false;
}

bool displaySensorError(Sensor *sensor,String name)
{
  if(sensor->overMax())
  {
    lcd.setCursor(0,0);
    lcd.print(name);
    lcd.print(": ");
    lcd.print(sensor->getTempC());
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Over Max");
    makesound();
    return true;
  }
  return false;
}

void displayFlowMeter()
{
  lcd.setCursor(0,0);
  lcd.print("Flow:");
  lcd.setCursor(0,1);
  lcd.print(flowRate);
  lcd.print("L/Min");
}

void displaySensor(Sensor *sensor,String name)
{
  lcd.setCursor(0,0);
  lcd.print(name);
  lcd.print(":");
  lcd.setCursor(0,1);
  lcd.print(sensor->getTempC());
  lcd.print("C");
}

void makesound()
{
  digitalWrite(buzzerpin, 1);
  delay(1000);
  digitalWrite(buzzerpin, 0);
  delay(300);
}
