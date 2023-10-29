/**
 ************************************************************************                  
 * @file                    : LoadCell.hpp
 * @author                  : Ahmed Hesham
 * @brief                   : Load Cell Sensor header File.
 ************************************************************************
 */

#ifndef _LoadCell_H
#define _LoadCell_H


/********************************************************************** Includes Start ************************************************************************/
#include <Arduino.h>
//for more info -> https://github.com/olkal/HX711_ADC
#include <HX711_ADC.h> //in LIBRARY MANAGER (HX711_ADC "by Olav Kallhovd")
/********************************************************************** Includes End   ************************************************************************/

/********************************************************************** Macro Declarations Start **************************************************************/
#define HX711_DOUT 21 //mcu > HX711 dout pin
#define HX711_SCK  22 //mcu > HX711 sck pin
#define TARE_TIME_INTERVAL  20000
#define PACKAGE_WEIGHT_LIMIT  500.0
/********************************************************************** Macro Declarations End   **************************************************************/

/********************************************************************** Macro Functions Declarations Start ****************************************************/

/********************************************************************** Macro Functions Declarations End   ****************************************************/

/********************************************************************** Data Type Declarations Start **********************************************************/
extern double LoadCell_Package_Weight;
extern double LoadCell_Package_Weight_MQTT;
extern unsigned long LoadCell_Package_No;
extern unsigned int LoadCell_Package_verify_flag;
/********************************************************************** Data Type Declarations End   **********************************************************/

/********************************************************************** Software Interfaces Declarations Start ************************************************/
void LoadCell_Init(void);
void LoadCell_Runnable(void);
void Load_Cell_Get_Reading(void);
/********************************************************************** Software Interfaces Declarations End   ************************************************/


#endif