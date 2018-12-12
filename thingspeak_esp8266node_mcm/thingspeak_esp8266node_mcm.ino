#include <ESP8266WiFi.h>

//WIFI
const char* ssid = "P1d3zz";
const char* password = "987654321";

WiFiClient client;

//ThingSpeak Settings
const int channelID= 648118;
String writeAPIKey = "V2KZXBI0FTJMHPPX";
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000;  //posta a cada 20 segundos 1000=millis

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);  
  }
}


void loop() {
  if(client.connect(server,80)){
  //medir a força do sinal (RSSI) da conexão wifi
  long rssi = WiFi.RSSI();

  //Construindo API request.
  String body ="field2=";
         body += String(rssi);
  Serial.print("RSSI: ");
  Serial.println(rssi);

   client.println("POST /update HTTP/1.1");
   client.println("Host: api.thingspeak.com");
   client.println("User-Agent: ESP8266 (nothans)/1.0");
   client.println("Connection: close");
   client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey);
   client.println("Content-Type: application/x-www-form-urlencoded");
   client.println("Content-Length: " + String(body.length()));
   client.println("");
   client.println(body);

   
    
  }
client.stop();

//wait and then post again
delay(postingInterval);
}
