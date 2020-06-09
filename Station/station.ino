#include <DHT.h>
#include <Adafruit_Sensor.h>

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiServer.h>

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

const char* ssid = "mi";
const char* password = "12345678";
const char* host = "192.168.4.1";
WiFiServer server(80);

void setup(){
  int count = 0;
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.print(ssid);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting");

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
    count++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Time for connection(s): ");
  Serial.print(count);
  Serial.println();
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println();
  dht.begin();
}

void loop(){
 WiFiClient client;

 float h=dht.readHumidity();
 float t=dht.readTemperature();

 
 if((client.connect(host, 80))){
  Serial.println("Connected: ");
  Serial.println(host);
 }

 
 if(isnan(h)||isnan(t))
 {
   Serial.println("Failed to get reading");
   return;
 }
 
// client.print(h);
 Serial.println("Humidity: ");
 Serial.println(h);

 //client.print(t);
 Serial.println("Temperature: ");
 Serial.println(t);
 int data_outgoing[2]={h,t};
 int mapFun[2];
 //Serial.println("Sent Data: ");
 //Serial.println(ESP.getChipId());
 //Serial.println();
 for(int i=0;i<2;i++)
 {
   mapFun[i]=data_outgoing[i];
   client.print(mapFun[i]);
   Serial.println(mapFun[i]);
 }
 delay(10);
}
 
