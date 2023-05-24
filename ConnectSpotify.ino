
#include <ESP8266WiFi.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "DESKTOP-NNDINSR 0918";
const char* password = "3i-1255Y";
const char* key = "bp1wfYgb7iulkNc-o-C68l"; 
const char* host = "maker.ifttt.com";
const int httpPort = 80;

const int buttonPin = 5;
int button = LOW;

WiFiClient client;

void connectToWiFi() //connect to WiFi
{
  Serial.print("\n\nConnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendToIFTTT()
{  
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

//This is the very important URL that is received by IFTTT to make the the "THAT" action we want!
  String url = "/trigger/pause/with/key/";  //where 'sheets' is {EVENT} name in my example (I create a google sheet and set it up there)
  url += key;
  

//some properly HTML data that we need to send with our URL
    String req = String("GET ") + url + " HTTP/1.1\r\n" +  
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n";
  Serial.println(req);
  client.print(req);  
  
}


void setup() {
  
  pinMode(button, INPUT);
  Serial.begin(115200); 
  
  connectToWiFi();
  
  if (client.available())
  {
    Serial.write(client.read());
  }
}

void loop() {
  button = digitalRead(buttonPin);

  if (button == HIGH) {
    sendToIFTTT();
  }
}
