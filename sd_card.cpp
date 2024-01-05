#include "sd_card.h"

#include "FS.h"
#include "SD.h"
#include "SPI.h"

File dataFile;

void handelInitSD(String fileName){
  if(!SD.begin()){
    Serial.println("sd card is not initializ_:(_");
  } else {
    dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    // dataFile = SD.open(finalFName, FILE_WRITE);
    if(!dataFile){
      Serial.println("err : write file error_:(_");
      while(1);
    }
  }
}

void handelAddData(String fileName, String timeCode, float v1, float v2, float v3){
  dataFile = SD.open(fileName.c_str(), FILE_APPEND);
  if(dataFile){
    dataFile.print(timeCode);
    dataFile.print(",");
    dataFile.print(v1);
    dataFile.print(",");
    dataFile.print(v2);
    dataFile.print(",");
    dataFile.println(v3);
    dataFile.close();
    Serial.println("data enter ok");
  } else {
    Serial.println("err : add data in file...");
  }
}