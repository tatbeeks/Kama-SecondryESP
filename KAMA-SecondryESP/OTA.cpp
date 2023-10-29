/**
 ************************************************************************                  
 * @file                    : OTA.c
 * @author                  : Ahmed Hesham
 * @brief                   : OTA Module source file
 ************************************************************************
 */

#include "OTA.h"

void OTA_Init(void) {
  OTADRIVE.setInfo("1dad2597-bec7-4204-9f5d-1b87d709cdd9", "v@1.0.0");
}


void OTA_Runnable(void) {
  if (OTADRIVE.timeTick(3600)) {
    OTADRIVE.updateFirmware();
  }
}
