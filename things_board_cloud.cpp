#include "things_board_cloud.h"

#include <WiFi.h>
#include <ThingsBoard.h>

WiFiClient wifiClient;
ThingsBoard tb(wifiClient);
int status = WL_IDLE_STATUS;

void tbGetData(int ledDataSentPin, float v1, float v2, float v3){
  float Wi_Fi_Strength = abs(WiFi.RSSI());
  float Wi_Fi = map(Wi_Fi_Strength, 90, 25, 0, 100);
  //  Serial.print("Wi-FI Strength (%):   ");
  //  Serial.println(Wi_Fi);
  //  Serial.println("Sending data to ThingsBoard:");
  //  Serial.print("Wind speed : ");  Serial.print(P);
  //  Serial.print(" %\t");
  //  Serial.print("WiFi Strength: ");  Serial.print(Wi_Fi);
  tb.sendTelemetryFloat("Wi_Fi", Wi_Fi);
  tb.sendTelemetryFloat("wind1", v1);
  tb.sendTelemetryFloat("wind2", v2);
  tb.sendTelemetryFloat("wind3", v3);

  Serial.println("Data Send to ThingsWorks");

  digitalWrite(ledDataSentPin, HIGH);
  delay(10);
  digitalWrite(ledDataSentPin, LOW);
  delay(100);
  digitalWrite(ledDataSentPin, HIGH);
  delay(10);
  digitalWrite(ledDataSentPin, LOW);

  delay(50);
}

void tbLoop(){
  tb.loop();
}