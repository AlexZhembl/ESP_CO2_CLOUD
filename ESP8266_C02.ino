// Firmware:
// 1. Deatach 3v3 pin
// 2. Short R7 resistor
// 3. Run firmware process
// 4. Connect 3v3 pin

#include <SoftwareSerial.h>
#include <ArduinoOTA.h>
#include "MHZ19.h" 
#include "HTTPServer.h"
#include "Constants.h"

MHZ19 myMHZ19;
SoftwareSerial mySerial(PIN_CO_RX, PIN_CO_TX);
bool isCalibrating = false;
unsigned long timeElapse = 0;

void setup() {
  Serial.begin(115200);
  
  WiFi.softAP(WIFI_SSID, WIFI_PSWD);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/startCalibrating", handle_startCalibrating);
  server.on("/endCalibrating", handle_endCalibrating);
  
  server.begin();
  Serial.println("HTTP server started");

  mySerial.begin(CO_BAUDRATE);    // sensor serial
  myMHZ19.begin(mySerial);     // pass to library

  myMHZ19.autoCalibration(false);     // make sure auto calibration is off
  Serial.print("ABC Status: "); myMHZ19.getABC() ? Serial.println("ON") :  Serial.println("OFF");  // now print it's status
    
  Serial.println("Waiting 20 minutes to stabalise...");
   /* if you don't need to wait (it's already been this amount of time), remove the 2 lines */
  //timeElapse = 12e5;   //  20 minutes in milliseconds
 // delay(timeElapse);    //  wait this duration
  
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
}

void loop() {
  server.handleClient();
  if(isCalibrating) {
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_RED, HIGH);
    return;
  }
  
  if (millis() - timeElapse >= 2000) {
    int CO2= myMHZ19.getCO2();        
    
    // Clear GREEN is for 0-400
    // Clear RED is for 2000 and above
    int greenColor =, 400, 2000, 1023, 0);
    int redColor = map(CO2, 400, 2000, 0, 1023);
    analogWrite(PIN_GREEN, greenColor);
    analogWrite(PIN_RED, redColor);
    
    Serial.print("CO2 (ppm): ");
    Serial.print(CO2);
    Serial.println("GREEN | RED ");
    Serial.print(greenColor);
    Serial.print(redColor);

    int8_t Temp = myMHZ19.getTemperature();    // Request Temperature (as Celsius)
    Serial.print("Temperature (C): ");
    Serial.println(Temp);

    timeElapse = millis();  // Update inerval
  }
}
