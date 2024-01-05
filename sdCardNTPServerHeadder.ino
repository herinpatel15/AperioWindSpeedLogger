#include <WiFi.h>

// header files
#include "ntp_server.h"
#include "sd_card.h"
#include "things_board_cloud.h"

// all const
const int windSensor1Pin = 32;
const int windSensor2Pin = 35;
const int windSensor3Pin = 34;
const int ledPowerPin = 4;
const int powerLed = 21;
const int ledDataSentPin = 22;
const int chipSelect = 5;
const int VoltSens = 14;
const int relay = 2;

//Var
int WindSpeedOP_Volt = 5;
float windSpeed1Voltage = 0;
float windSpeed2Voltage = 0;
float windSpeed3Voltage = 0;

// wifi config data
#define WIFI_SSID "helloworld"
#define WIFI_PASS "hello_world"

// remove delay var
unsigned long previousMillisSD = 0;
unsigned long previousMillisTB = 0;

// SD card add data delay
const long intervalSD = 1000;

// thindsboard send data delay
const long intervalTB = 2000;

// ref var
int dayRef = 0;
String fNameRef = "hello";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(powerLed, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(ledPowerPin, OUTPUT);
  pinMode(ledDataSentPin, OUTPUT);
  pinMode(windSensor1Pin, INPUT);
  pinMode(windSensor2Pin, INPUT);
  pinMode(windSensor3Pin, INPUT);

  digitalWrite(powerLed, HIGH);
  digitalWrite(ledPowerPin, HIGH);
  digitalWrite(relay, LOW);

  InitWifi();
  ntpConfig();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisSD >= intervalSD) {
    previousMillisSD = currentMillis;

    // Read sensor values
    int windSpeed1 = analogRead(windSensor1Pin);
    int windSpeed2 = analogRead(windSensor2Pin);
    int windSpeed3 = analogRead(windSensor3Pin);
    float windSpeed1Voltage = windSpeed1 * (WindSpeedOP_Volt / 4095.0);
    float windSpeed2Voltage = windSpeed2 * (WindSpeedOP_Volt / 4095.0);
    float windSpeed3Voltage = windSpeed3 * (WindSpeedOP_Volt / 4095.0);

    Serial.print("V1=");
    Serial.print(windSpeed1Voltage);
    Serial.print(" V2=");
    Serial.print(windSpeed2Voltage);
    Serial.print(" V3=");
    Serial.println(windSpeed3Voltage);

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("wifi is not connected");
      digitalWrite(relay, HIGH);
      delay(1000);
      digitalWrite(relay, LOW);
      InitWifi();
    } else {
      // Serial.println(handelFileName());
      // Serial.println(handelDayFile());

      if (dayRef != handelDayFile()) {
        dayRef = handelDayFile();
        fNameRef = "/" + handelFileName() + ".csv";

        Serial.println("file name :- " + fNameRef);

        handelInitSD(fNameRef);
      }

      handelAddData(fNameRef, handelFileTime(), windSpeed1Voltage, windSpeed3Voltage, windSpeed3Voltage);
    }
    tbLoop();
  }

  if (currentMillis - previousMillisTB >= intervalTB) {
    previousMillisTB = currentMillis;
    tbGetData(ledDataSentPin, windSpeed1Voltage, windSpeed3Voltage, windSpeed3Voltage);
  }
}

void InitWifi() {
  // Serial.println("connected to : ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("WIFI connected :)");
}
