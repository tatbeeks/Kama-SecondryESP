#include "esp32-hal-gpio.h"
#include "esp32-hal.h"
#include <sys/_types.h>
/**
 ************************************************************************                  
 * @file                    : PhotoElectricSensor.cpp
 * @author                  : Ahmed Hesham
 * @brief                   : Photo Electric Sensor source file

 Module interface with photo electric sensors (whether NPN or PNP type).
 ************************************************************************
 */

#include "PhotoElectricSensor.hpp"

unsigned long int PE_pulseCount;
static unsigned long int PE_Depouncing_prev_time;
static unsigned long int PE_Detect_Element_prev_time;
static unsigned long int PE_current_time;
static int PE_flag_object;


unsigned long Running_time;
unsigned long Down_Time;

void IRAM_ATTR pulseCounter() {
  PE_current_time = millis();
  //50 ms represent a depouncing time interval
  if ((PE_flag_object == 0) && ((PE_current_time - PE_Depouncing_prev_time) >= 50)) {
    //if condition to ensure that the detection signal is for another element
    //this if condition is a solution for multi detection of the same element specially for glass elements
    //uncomment the condition in case you noticed that object is detected more than one time(sensor malfunction). 1000 ms represent a time interval that if the interrupt is activated
    //before this period passes,no count plus will take place
    //  if ((PE_current_time - PE_Detect_Element_prev_time) >= 1000) {
      PE_flag_object = 1;
      PE_Depouncing_prev_time = PE_current_time;
      PE_Detect_Element_prev_time = PE_current_time;
      PE_pulseCount++;
    //  }
  } else if ((PE_flag_object == 1) && ((PE_current_time - PE_Depouncing_prev_time) >= 50)) {
    PE_flag_object = 0;
    PE_Depouncing_prev_time = PE_current_time;
  }
}

void PhotoElectric_Init(void) {
  pinMode(PHOTOELECTRIC_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(PHOTOELECTRIC_PIN), pulseCounter, CHANGE);
}



void PhotoElectric_Runnable(void) {
  Serial.print("count :");
  Serial.println(PE_pulseCount);
}

//Function works on calculating run time & down time by indicating if there is an update happens to variable-> PE_current_time value (this variable is updated when an object is detected) or not.
//if variable is not updated then an increase in down time will happen and vice versa 
void Conveyer_Status(void)
{
  static unsigned long Function_Last_Call_time;

  if ((millis() - Function_Last_Call_time) > 15000)
  {
    if ((millis() - PE_current_time) > 15000)
    {
      Down_Time +=15;
    }
    else
    {
      Running_time +=15;
    }
  Function_Last_Call_time = millis();
  }
}