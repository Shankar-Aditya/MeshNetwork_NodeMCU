
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

WiFiServer server(80);

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("mi", "12345678");
  server.begin();
  Serial.begin(9600);
  IPAddress IP = WiFi.softAPIP();
  //Serial.flush();
  Serial.println();
  Serial.print("Server IP is: ");
  Serial.println(IP);

}

void loop() {
  char ID, R, G, B, anim_ID;
  WiFiClient client = server.available();



  int data_outgoing[5] = {10, 128, 128, 123, 123};
  int mapFun[5];
  Serial.print("Sent data: ");
  Serial.print(ESP.getChipId());
  Serial.println();
  for(int i = 0; i < 5; i++){
    mapFun[i] =data_outgoing[i];
    //mapFun[i] = map(mapFun[i], 0, 255, 0, 128); 
    client.print(mapFun[i]);
    Serial.print(mapFun[i]);

  }

delay(10);
}
