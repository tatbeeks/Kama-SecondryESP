/**
 ************************************************************************                  
 * @file                    : LoadCell.cpp
 * @author                  : Ahmed Hesham
 * @brief                   : Load Cell Sensor source file
 Module is used to interface with Load Cell sensors connected through HX711-ADC chip.

 to first use:
 1-run code from Examples-> HX711-ADC-> calibration.
 2-change the value of stabilizingtime to 5000 and make sure to customize pins
 3-follow instructions popped on serial monitor
 4-run upper code many times (for a single load cell) with different defined weights to get a table of calibration factors.
 5-calcaulate the average and update the calibrationValue variable in this code by this obtained value.

 notes:
 -make sure to input a regulated voltage to your load cell.
 -in case of draft issue shown,
 1-make sure to seperate power lines from signal lines
 2-pair twist the two signal lines coming from load cell to chip (make them as a twisted pair cable), this enhance the chance to cancel noise
 3-move wires until you get a constant line of readings
 ************************************************************************
 */

#include "LoadCell.hpp"


HX711_ADC LoadCell(HX711_DOUT, HX711_SCK);
static const float calibrationValue = 13.56;  //run calibration.ino first to get this value
static double Load_Cell_Val;
static long Load_Cell_Last_Tare_time;

double LoadCell_Package_Weight;
double LoadCell_Package_Weight_MQTT;
unsigned long LoadCell_Package_No;

unsigned int LoadCell_Package_verify_counter;
unsigned int LoadCell_Package_verify_flag;

unsigned long t = 0;

void LoadCell_Init(void) {
  delay(10);
  Serial.println("Starting...");
  LoadCell.begin();
  unsigned long stabilizingtime = 4000;  // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true;                  //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1)
      ;
  } else {
    LoadCell.setCalFactor(calibrationValue);  // set calibration value (float)
    Serial.println("Startup is complete");
  }
}

//Function works on getting the read of load cell and also make sure that weight is higher than the minimum weight of factory package "PACKAGE_WEIGHT_LIMIT".
//LoadCell_Package_verify_counter variable is a counter of how many reading load cell got that fullfill the upper condition so no misreadings occur.
//after fulfilling the upper two conditions, LoadCell_Package_verify_flag variable works as a connection between this module and Services module to insure that only
//correct weight of a single package is published once.
//LoadCell_Package_No variable is considered a footprint of a package that indicates the number of this package through the shift.
void LoadCell_Runnable(void) {
  Load_Cell_Get_Reading();

  if (LoadCell_Package_Weight > PACKAGE_WEIGHT_LIMIT) {
    LoadCell_Package_verify_counter++;
  }
  else
  {
    LoadCell_Package_verify_counter=0;
  }

  if ((LoadCell_Package_verify_counter > 100) && (LoadCell_Package_verify_flag == 0)) {
    LoadCell_Package_No+=1;
    LoadCell_Package_Weight_MQTT = LoadCell_Package_Weight;
    LoadCell_Package_verify_flag = 1;
  }

  if ((LoadCell_Package_verify_flag == 2))
  {
      if (LoadCell_Package_Weight < PACKAGE_WEIGHT_LIMIT) {
      LoadCell_Package_verify_flag = 0;
      LoadCell_Package_verify_counter = 0;
    }
  }

  /*Draft issue rescue*/
  if (LoadCell_Package_Weight < -100.0)
  {
    LoadCell.tare();
  }
}

void Load_Cell_Get_Reading(void) {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0;  //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      Load_Cell_Val = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.println(Load_Cell_Val);
      newDataReady = 0;
      t = millis();
    }
  }

  // receive command from serial terminal, send 't' to initiate tare operation:
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay();
  }

  // check if last tare operation is complete:
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }
  if (Load_Cell_Val != 0) {
    LoadCell_Package_Weight = Load_Cell_Val;
  }
  Load_Cell_Val = 0;
}
