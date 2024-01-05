#ifndef SD_CARD_H
#define SD_CARD_H

#include <Arduino.h>

void handelInitSD(String fileName);
void handelAddData(String fileName, String timeCode, float v1, float v2, float v3);

#endif