#ifndef THING_BOARD_CLOUD_H
#define THING_BOARD_CLOUD_H

#include <Arduino.h>

#define TOKEN "WRA_LOGGER"
#define thingsboardServer "thingsboard.cloud"
#define lastSend 0

void tbGetData(int ledDataSentPin, float v1, float v2, float v3);
void tbLoop();

#endif