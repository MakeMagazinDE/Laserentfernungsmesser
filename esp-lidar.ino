

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

const char* SSID = "MeinESP32";
const char* PASSWORD = "testpasswort";

AsyncWebServer server(80);

 
void setup(){
  Serial.begin(115200);
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz


  WiFi.softAP(SSID, PASSWORD);
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());
  Serial.println(myLidarLite.distance());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    String message = "<!doctype html>\n";
    message += "<html>\n";
    message += "  <head>\n";
    message += "    <title>ESP32 Entfernungsmesser</title>\n";
    message += "  </head>\n";
    message += "  <body>\n";
    message += "    <h1>Entfernung: ";
    message += String(myLidarLite.distance(false));
    message += " &#8451;</h1>\n";
    message += "  </body>\n";
    message += "</html>\n";
    request->send(200, "text/html", message);
  });
 
  server.begin();
}

void loop() {}
