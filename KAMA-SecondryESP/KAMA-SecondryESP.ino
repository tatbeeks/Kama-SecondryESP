/**
 ************************************************************************                  
 * @file                    : KAMA_Project.ino
 * @author                  : Tatbeek Company
 * @brief                   : KAMA second half of the production line source file

 this part of KAMA project handles the production line which is responsible of summing collecting glasses into inner packs then gather these packs into one large package.
 Solution depends on calculate number of inner packs by means of object monitoring through photo electric sensor and get the weight of each package after filling it.
 ************************************************************************
 */

#include "main.h"

unsigned long Last_Publish_Time = 0;


void setup() {
  WIFI_Init();
  Client_Init();
  OTA_Init();
  PhotoElectric_Init();
  LoadCell_Init();
  Shift_Time_Init();
}

void loop() {
  Serial.begin(57600);
  PhotoElectric_Runnable();  // Only prints on serial Monitor
  LoadCell_Runnable();
  Conveyer_Status();
  Shift_Check();
  OTA_Runnable();
  if ((millis() - Last_Publish_Time) >= PUBLISH_TIME_INTERVAL_MS) {

    if (WIFI_Check()) {
      Client_Connect();
      if (Client_Connectivity_Flag == 1) {
        Client_Publish();
        Last_Publish_Time = millis();
      }
    }
  }
}