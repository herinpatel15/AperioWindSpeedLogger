#ifndef NTP_SERVER_H
#define NTP_SERVER_H

#include <Arduino.h>

// ntp config constents
#define ntpServer "pool.ntp.org"
#define gmtoffset_sec 19800
#define daylightoffset_sec 0

// all mathods
void ntpConfig();
String handelFileName();
String handelFileTime();
int handelDayFile();

#endif