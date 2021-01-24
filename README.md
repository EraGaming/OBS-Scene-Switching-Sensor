# OBS-Scene-Switching-Sensor (OBSSSS)
an ESP8266 ultrasonic sensor project that changes OBS Scenes when you get close to a sensor, uses flask python api and OBS Websocket Python api libraries.

## How Does It Work?
OBSSS is a tool that lets you switch scenes using physical sensors (ie motion sensors, distance sensors, object detection sensors, or physical buttons). Unlike a keyboard emulator this script interacts directly with OBS Websockets, freeing up your keyboard for switching scenes. Sensors can be placed anywhere there is WiFi and are powered by USB (or you can use a li-ion battery for a truly wireless experience. just don't expect great battery life).

The Wemos D1 mini will send a request to a python script running on your streaming computer. The python script will check to see what scene is active and change the scene to the one you program into the sensor. 

## Requirements
OBSSS requires the following equipment, software and libraries installed in order to work properly
+ OBS Websockets on OBS
+ Python 3.6+ 
+ An ESP8266 NodeMCU module, I use a Wemos D1 Mini Pro clone (~ $5cad/board)
+ An IR obstacle detection sensor (~ $2cad/board)

## Installation
1. Install OBS Websockets for OBS
2. Pull this repo on your streaming computer with Python 3 installed
3. From the root of the project run `.\.venv\Scripts\activate` in your terminal to launch the python virtual environment with all libraries pre installed
4. with the venv now activated run `python .\main.py` to start the server
5. Wire up the IR sensor to your Wemos D1 Mini (VCC -> 5V, GND -> G, OUT -> D7)
6. Open up the wemos-d1-mini-sensor sketch in arduino and update the firmware with the IP of your streaming PC and the name of the OBS scene you want the sensor to switch to (make sure it's URL Encoded, for example, spaces must be entered in as %20 - this will be fixed in a later update).
7. Upload the sketch to your Wemos D1 Mini
8. Success

## Wemos D1 / NodeMCU Firmware
I am currently working on more user friendly firmware currently there is the simple firmware where you have to configure the script
