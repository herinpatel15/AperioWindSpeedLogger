#include "ntp_server.h"
#include "time.h"

void ntpConfig(){
  configTime(gmtoffset_sec, daylightoffset_sec, ntpServer);
}

String handelFileName(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain day");
    return "no";
  }
  char formattedTime[50];
  strftime(formattedTime, sizeof(formattedTime), "%B_%d_%Y_%H%M%S", &timeinfo);
  return String(formattedTime);
}

String handelFileTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain day");
    return "no";
  }
  char formattedTime[50];
  strftime(formattedTime, sizeof(formattedTime), "%H:%M:%S", &timeinfo);
  return String(formattedTime);
}

int handelDayFile(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain day");
    return 5;
  }
  char formattedTime[5];
  strftime(formattedTime, sizeof(formattedTime), "%M", &timeinfo);
  return atoi(formattedTime);
}