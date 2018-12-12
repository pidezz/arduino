//SENSOR WIFI DE UMIDADE
#include <ESP8266WiFi.h>

const char* SSID = "P1d3zz"; //ssid
const char* PASSWORD = "987654321";
WiFiServer server(80); //portaweb

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
delay(100);
pinMode(ledPin, OUTPUT); //Define D7 como saida
digitalWrite(ledPin, LOW); // o led comeeça apagado

pinMode(ledPin1, OUTPUT); //Define D4 como saida
digitalWrite(ledPin1, LOW); //d4 começa desligado 

// COMUNICACAO WIFI
Serial.println();
Serial.println();
Serial.print("connectando:"); //mensagem apresentada
Serial.println(ssid); //apresenta o nome da rede

WiFi.begin(ssid, password); //inicia ligacao na rede
while (WiFi.status() != WL_CONNECTED) {
  delay (500);
  Serial.print("."); //enquanto a ligacao nao for efetuada com sucesso
}
Serial.println("");
Serial.println("WiFi connected"); //se a ligacao é efetuada com sucesso

//SERVIDOR
server.begin(); //comunicacao com o servidor
Serial.println("Servidor iniciado"); //é apresentado no monitor serie que o servidor foi iniciado 

//IMPRESSAO DE ENDEREÇO IP

Serial.print("Use a seguinte url para a comunicacao:");
Serial.print("http://"); 
Serial.print(WiFi.localIP()); //abrindo o browser com esse ip 
Serial.println("/");

}
