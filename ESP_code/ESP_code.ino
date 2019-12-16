#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
 
ESP8266WebServer server(80);
String webPage;
const char* ssid     = "Tesla IoT";      //wifi name
const char* password = "fsL6HgjN";  //wifi password
 
void setup() {
 
  pinMode(16, OUTPUT);  //led pin 16
 
  webPage += "<h1>ESP8266 Web Server</h1><p>Uitgang D0  ";
  webPage += "<a href=\"socket1On\"><button>aan</button></a>&nbsp;";
  webPage += "<a href=\"socket1Off\"><button>uit</button></a></p>";
  webPage += "<b><h1>Hallo Maarten</h1></b>";
  webPage += "<b><h5>Ok</h1></b<";
  webPage += "<b><h1>BOOMER</h1></b>";
  
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
 
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    // Turn off LED
    digitalWrite(16, LOW);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    //Turn on LED
    digitalWrite(16, HIGH);
    delay(1000); 
  });

  server.begin();
  Serial.println("HTTP server gestart");
}
 
void loop() {
  server.handleClient();
}
