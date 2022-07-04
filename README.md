# ESP_CO2_CLOUD
Simple IoT solution for air purity monitoring using esp8266 using MH-Z19b

<br>
<img src="https://user-images.githubusercontent.com/7920555/177143348-ef2c28bd-695a-4756-9212-d40e7af47c02.jpg" width="600" height="350">
<img src="https://user-images.githubusercontent.com/7920555/177143353-80a231df-8cc8-491d-8aa0-bf44f866c9bb.jpg" width="600" height="500">

<p>The idea was to make an IoT device that was compact, easy to use and easily showed how CO2 levels in the air could be tolerated.</p>
***

#### How to use?
1. Just plug in the device with usb port to any charging socket with at least 0.5amps currency (your phone charger is suitable)
2. Next wait untill device will collebrate (about 1 min)
3. Observe the light: it will change gradient from green to red depends on CO2 level (GREEN is for <strong>0-400ppm</strong>, RED is for <strong>2000ppm and above</strong>)
<img src="https://user-images.githubusercontent.com/7920555/177146495-697ed2cd-63e8-481f-ad9f-602f2b557ae8.jpg" width="600" height="500">

#### PCB schema and layout
https://oshwlab.com/alex.zhemblow/sensorco2_iot_esp8266_copy

#### Code and Firmware
- Use arduino IDE as well
- Install libs listed in ESP8266_C02.ino and use instruction in the top to connect usb-uart converter (like CP2102)
- HTTPServer.ino is used for future setuping throught the WIFI
- All pins are listed in Constants.h
