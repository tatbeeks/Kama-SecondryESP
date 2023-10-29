/**
 ************************************************************************                  
 * @file                    : Services.c
 * @author                  : Ahmed Hesham
 * @brief                   : Services source file
 ************************************************************************
 */

#include "Services.h"

WiFiClient espClient;
PubSubClient client(espClient);
byte Client_Connectivity_Flag;

const char* mqttServer = "35.172.244.127";  //mqtt server
const int mqttPort = 1883;                  //mqtt port
const char* mqttUser = "amr";               //mqtt username
const char* mqttPassword = "amr123";        //mqtt password

void Client_Init(void) {
  client.setServer(mqttServer, mqttPort);
}

void Client_Connect(void) {
  //connect to MQTT
  byte repeat = 0;
  Client_Connectivity_Flag = 1;
  while ((!client.connected()) && (repeat < 2)) {

    Serial.println("Connecting to MQTT...");

    if (client.connect("", mqttUser, mqttPassword)) {
      Serial.println("connected");
      Client_Connectivity_Flag = 1;
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      Client_Connectivity_Flag = 0;
    }
    repeat++;
    delay(100);
  }

  // while (!mqtt.connected() && (repeat < 2)) {
  //       mqttConnect();
  //       repeat++;
  // }
}

void Client_Publish(void) {
  static char Packages_Count_str[8];
  static char Package_Weight_str[8];
  static char Packages_Placed_OnLoadCell_count_str[8];

  static char Running_Time_str[8];
  static char Down_Time_str[8];

  //Inner Packets topics

  itoa(PE_pulseCount, Packages_Count_str, 10);
  client.publish("KAMA1/InnerPacks", Packages_Count_str);  //debug

  itoa(Running_time, Running_Time_str, 10);
  client.publish("KAMA1/InnerRunningTime", Running_Time_str);  //debug

  itoa(Down_Time, Down_Time_str, 10);
  client.publish("KAMA1/InnerDownTime", Down_Time_str);  //debug


  // Packages topics
  if (LoadCell_Package_verify_flag == 1) {
  itoa(LoadCell_Package_No, Packages_Placed_OnLoadCell_count_str, 10);
  client.publish("KAMA1/loadCellPackage_No", Packages_Placed_OnLoadCell_count_str);  //debug

  // itoa(LoadCell_Package_Weight, Package_Weight_str, 10);
  // client.publish("ahmed/PackageWeight", Package_Weight_str);  //debug

  dtostrf(LoadCell_Package_Weight_MQTT, 6, 2, Package_Weight_str);
  client.publish("KAMA1/loadcelPackageWeight", Package_Weight_str);  //debug

  LoadCell_Package_verify_flag = 2;
  }
}
