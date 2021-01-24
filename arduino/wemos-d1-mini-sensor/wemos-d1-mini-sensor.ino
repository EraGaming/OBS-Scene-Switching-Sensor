// This is a more simplified version that I'm programming so taht I can start working on the Flask API
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

int pirPin = D7;
int val;
int trigger;



void setup()
{
  Serial.begin(9600); // serial for debug
  WiFi.begin("yourSSID", "yourPass"); //your wifi credentials go here

  while (WiFi.status() != WL_CONNECTED) { //Wait for wifi to connect

    delay(500);
    Serial.println("Waiting for connection");
  }

  // Limit call rate by creating a variable so that we only trigger when sensor remains activated (vs. calling everytime the loop occurs)
  trigger = true;
}
 
void loop()
{
val = digitalRead(pirPin);
//low = object, high =  no object
if (val == LOW)
{
  if (trigger == false) { // If the object wasn't in front of the sensor the last time the loop ran
       
    trigger = true; //object is now in front of the sensor

    if (WiFi.status() == WL_CONNECTED) { //check Wifi connection status
     HTTPClient http;
     http.begin("http://10.0.13.132:8068/scene1"); // this is where you put your scene name. make sure scenes in OBS have no spaces. i.e., http://yourip:8068/sceneName
     int httpCode = http.GET();
     if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);  
     }
     http.end();
    } else {
      Serial.println("Error in WiFi connection, reconfigure firmware");
    }
    
  } else {
    trigger = true; //object is 'still' in front of the sensor
  }
}
else
{
  trigger = false; //object is no longer in front of the sensor
}
 
delay(250); //check for object, 4 times a second
}
