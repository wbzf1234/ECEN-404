// Wire connection:
// Weight: DOUT - A1, SCK - A0
// Compass: SCL - A4, SDA - A5
// GPS: RX - D3, TX - D4

#include "hx711.h"            // Library of weight sensor
int weight;
Hx711 scale(A1, A0);

#include <Wire.h>             // Library of compass sensor
#include <MechaQMC5883.h>
MechaQMC5883 qmc;
uint16_t x, y, z;
int azimuth;

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 3(rx) and 4(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
//float Lng, Lat;

void setup()
{
  Wire.begin();
    Serial.begin(9600);
    ss.begin(GPSBaud);
    pinMode(13, OUTPUT);

    Serial.println(F("Intergration system"));
    Serial.println(F("by Jinyu Dai"));
    Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      //displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }

/*
  Serial.print("Latitude: ");
  Serial.print(Lat);
  Serial.print(",  ");
  Serial.print("Longtitude: ");
  Serial.print(Lng);
  Serial.println();
  */

  Serial.print(F("Latitude: "));
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(F("Longtitude: "));
    Serial.println(gps.location.lng(), 6);

    // compass sensor
    qmc.read(&x, &y, &z,&azimuth);
    Serial.print("Heading: ");
    Serial.print(azimuth);
    Serial.println();

    // weight sensor
    /*weight = abs(scale.getGram());     // read weight sensor
    if(weight > 15){
      Serial.println("Weight detected");
      digitalWrite(13, HIGH);
    }
    else{
      Serial.println("Empty load");
      digitalWrite(13, LOW);
    }

    Serial.println();*/
}
/*
void displayInfo()
{  
  if (gps.location.isValid())
  {
    Lat = gps.location.lat();
    Lng = gps.location.lng();
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}*/
