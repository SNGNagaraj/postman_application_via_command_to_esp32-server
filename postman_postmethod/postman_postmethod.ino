#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
const char *SSID = "ESIL_UG_2G";
const char *PWD = "Hild#0980";

// Web server running on port 80
WebServer server(80);

// wifi static IP Address settings
IPAddress local_IP(192,168,0,5); // Static IP address set
IPAddress gateway(192,168,0,1);// static gateway set
IPAddress subnet(255,255,255,0);// subnet set
IPAddress primaryDNS(192,168,0,1); //primary DNS sets

// JSON data buffer

StaticJsonDocument<250> jsonDocument;
char buffer[250];

void setup() 
{	 	 
  Serial.begin(9600);	 	 
 	 	 
  // Sensor setup	 	 
  //if (!bme.begin(0x76)) {	 	 
  //  Serial.println("Problem connecting to BME280");	 	 
  //}	 	 
  connectToWiFi();	 	 
   //setup_task();	 	 
  setup_routing(); 	 	 
  // Initialize Neopixel	 	 
 // pixels.begin();	 	 
}

void loop() {	 	 
  server.handleClient();	 	 
}

void setup_routing() 
{	 	 
 	 
  server.on("/led", HTTP_POST, handlePost);	 	 
  	 	 
  // start server	 	 
  server.begin();	 	 
}
void handlePost() {
  if (server.hasArg("plain") == false) {
    //handle error here
  }
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);
  
  // Get RGB components
  int red = jsonDocument["red"];
  int green = jsonDocument["green"];
  int blue = jsonDocument["blue"];
  Serial.print("Red: ");
  Serial.print(red);
  
  //pixels.fill(pixels.Color(red, green, blue));
 // pixels.show();
  // Respond to the client
  server.send(200, "application/json", "{}");
}
void connectToWiFi() {
    if(!WiFi.config(local_IP,gateway,subnet,primaryDNS))
  {
    Serial.print("STA failed to configure");
  }
  Serial.print("Connecting to ");
  Serial.println(SSID);
  
  WiFi.begin(SSID, PWD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    // we can even make the ESP32 to sleep
  }
 
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}