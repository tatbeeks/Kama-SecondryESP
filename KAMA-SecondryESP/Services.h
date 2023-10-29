/**
 ************************************************************************                  
 * @file                    : Services.h
 * @author                  : Ahmed Hesham
 * @brief                   : Services header file
 ************************************************************************
 */

#ifndef _SERVICES_H
#define _SERVICES_H

/********************************************************************** Includes Start ************************************************************************/
#include <Arduino.h>
#include <PubSubClient.h>
#include "WIFI.h"
#include "LoadCell.hpp"
#include "PhotoElectricSensor.hpp"
/********************************************************************** Includes End   ************************************************************************/

/********************************************************************** Macro Declarations Start **************************************************************/

/********************************************************************** Macro Declarations End   **************************************************************/

/********************************************************************** Macro Functions Declarations Start ****************************************************/

/********************************************************************** Macro Functions Declarations End   ****************************************************/

/********************************************************************** Data Type Declarations Start **********************************************************/
extern byte Client_Connectivity_Flag;
/********************************************************************** Data Type Declarations End   **********************************************************/

/********************************************************************** Software Interfaces Declarations Start ************************************************/
void Client_Init(void);
void Client_Connect(void);
void Client_Publish(void);
/********************************************************************** Software Interfaces Declarations End   ************************************************/



#endif