#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>

int pirPin = D7;
int val;
int trigger;
int chipID;

WiFiManager wm; //global wm instance
WiFiManagerParameter server_ip; // global param (for non blocking w params)
WiFiManagerParameter scene_name; // global param (for non blocking w params) 
void setup()
{
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STAP+AP
  Serial.begin(9600); // serial for debug
  
  //reset settings - wipe creds for testing
  //wm.resetSettings();

  //TODO: we need to check is params are set already before configuring params... these are not saving after reset
  new (&server_ip) WiFiManagerParameter("serverip", "Server IP Address", "", 15,"placeholder=\"0.0.0.0\"");
  new (&scene_name) WiFiManagerParameter("scenename", "OBS Scene Name", "", 60,"placeholder=\"Scene1\"");;
  wm.addParameter(&server_ip);
  wm.addParameter(&scene_name);
  
  wm.setSaveParamsCallback(saveParamCallback);

  wm.setClass("invert"); //darkmode plz
  
  bool res;
  res = wm.autoConnect("DRWN", "administrator");

  if(!res) {
    Serial.println("Failed to connect");
  }
  else {
    Serial.println("Connected to WiFi");
  }

  // Limit call rate by creating a variable so that we only trigger when sensor remains activated (vs. calling everytime the loop occurs)
  trigger = true;
}

String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback(){
  Serial.println("[CALLBACK] saveParamCallback fired");
  Serial.println("PARAM serverip = " + getParam("serverip"));
  Serial.println("PARAM scenename = " + getParam("scenename"));
}
 
void loop()
{
val = digitalRead(pirPin);
//low = object, high =  no object
if (val == LOW)
{
  if (trigger == false) // If the object wasn't in front of the sensor the last time the loop ran
  {
    Serial.println( scene_name.getValue() );
    Serial.println( server_ip.getValue() );
    
    trigger = true; //object is now in front of the sensor
  }
  else
  {
    trigger = true; //object is 'still' in front of the sensor
  }
}
else
{
  trigger = false; //object is no longer in front of the sensor
}
 
delay(250); //check for object, 4 times a second
}
