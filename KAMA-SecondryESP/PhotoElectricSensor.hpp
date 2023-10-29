/**
 ************************************************************************                  
 * @file                    : PhotoElectricSensor.hpp
 * @author                  : Ahmed Hesham
 * @brief                   : Photo Electric Sensor header File.
 ************************************************************************
 */

#ifndef _PhotoElectricSensor_H
#define _PhotoElectricSensor_H


/********************************************************************** Includes Start ************************************************************************/
#include <Arduino.h>
/********************************************************************** Includes End   ************************************************************************/

/********************************************************************** Macro Declarations Start **************************************************************/
#define PHOTOELECTRIC_PIN 33
/********************************************************************** Macro Declarations End   **************************************************************/

/********************************************************************** Macro Functions Declarations Start ****************************************************/

/********************************************************************** Macro Functions Declarations End   ****************************************************/

/********************************************************************** Data Type Declarations Start **********************************************************/
extern unsigned long PE_pulseCount;
extern unsigned long Running_time;
extern unsigned long Down_Time;
/********************************************************************** Data Type Declarations End   **********************************************************/

/********************************************************************** Software Interfaces Declarations Start ************************************************/
void PhotoElectric_Init(void);
void PhotoElectric_Runnable(void);
void Conveyer_Status(void);
/********************************************************************** Software Interfaces Declarations End   ************************************************/


#endif