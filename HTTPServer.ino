#ifndef _HTTPServer_h
#define _HTTPServer_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
ESP8266WebServer server(80);


void handle_OnConnect() {
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", sendHTML()); 
}

void handle_startCalibrating() {
  isCalibrating = true;
  Serial.println("Start calibrating");
  server.send(200, "text/html", sendHTML()); 
}

void handle_endCalibrating() {
  isCalibrating = false;
  myMHZ19.calibrate();    // Take a reading which be used as the zero point for 400 ppm 
  Serial.println("End calibrating");
  server.send(200, "text/html", sendHTML()); 
}

String sendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";

  if (isCalibrating) {
    ptr +="<p>Calibrating Status: ON</p><a class=\"button button-on\" href=\"/endCalibrating\">OFF</a>\n";
  }
  else {
    ptr +="<p>Calibrating Status: OFF</p><a class=\"button button-off\" href=\"/startCalibrating\">ON</a>\n";
  }

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

#endif
