#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>

byte park = 0;
byte forward = 1;
byte backward = 2;
byte left = 3;
byte right = 4;
byte matic = 5;
byte manual = 6;



MDNSResponder mdns;

ESP8266WebServer server(80);
String webPage;
const char* ssid     = "Tesla IoT";      //wifi name
const char* password = "fsL6HgjN";  //wifi password
//const char* ssid     = "TP-LINK_2.4GHz_EC6589";      //wifi name
//const char* password = "43716470";  //wifi password

void setup() {
  
  Wire.begin();
  

  webPage += "<h1>ESP8266 Mini Rob</h1><p>Autonoom mode  ";
  webPage += "<a href=\"socket1On\"><button>aan</button></a>&nbsp;";
  webPage += "<a href=\"socket1Off\"><button>uit</button></a></p>";
  webPage += "<a href=\"forward\"><button>forward<button></a></p>";
  webPage += "<a href=\"backward\"><button>backward<button></a></p>";
  webPage += "<a href=\"left\"><button>left<button></a></p>";
  webPage += "<a href=\"right\"><button>right<button></a></p>";
  webPage += "<a href=\"park\"><button>park<button></a></p>";
  

  Serial.begin(74880);
  delay(100);


  Serial.println();
  Serial.println();
  Serial.print("Verbinding maken met ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi aangesloten");
  Serial.println("IP addres: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP()))
    Serial.println("MDNS responder gestart");

  server.on("/", []() {
    server.send(200, "text/html", webPage);
  });
  
  server.on("/socket1On", []() {
    server.send(200, "text/html", webPage);
    
    Wire.beginTransmission(1);
    Wire.write(matic);
    Wire.endTransmission();
    delay(500);
  });
  
  server.on("/socket1Off", []() {
    server.send(200, "text/html", webPage);
    
    Wire.beginTransmission(1);
    Wire.write(manual);
    Wire.endTransmission();
    delay(500);
  });

  server.on("/forward", []() {
    server.send(200, "text/html", webPage);
    
    Wire.beginTransmission(1);
    Wire.write(forward);
    Wire.endTransmission();
    delay(500);

  });
  
  server.on("/backward", []() {
    server.send(200, "text/html", webPage);
    
    Wire.beginTransmission(1);
    Wire.write(backward);
    Wire.endTransmission();
    delay(500);

  });
  server.on("/left", []() {
    server.send(200, "text/html", webPage);
    
    Wire.beginTransmission(1);
    Wire.write(left);
    Wire.endTransmission();
    delay(500);

  });
  server.on("/right", []() {
    server.send(200, "text/html", webPage);
    
    Wire.beginTransmission(1);
    Wire.write(right);
    Wire.endTransmission();
    delay(500);

  });

  server.on("/park", []() {
    server.send(200, "text/html", webPage);
    
    Wire.beginTransmission(1);
    Wire.write(park);
    Wire.endTransmission();
    delay(500);

  });

  server.begin();
  Serial.println("HTTP server gestart");
}



void loop() {
  server.handleClient();

  
  
}
