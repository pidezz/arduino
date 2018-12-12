#include <ESP8266WiFi.h>

const char* ssid = "P1d3zz"; //ssid
const char* password = "987654321";

int ledPin = 13; //GPIO13 do esp8266 e D7 DO NODEMCU
int ledPin1 = 2; //GPIO2 DO ESP8266 E D4 DO NODEMCU
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



void loop() {
  // put your main code here, to run repeatedly:
//Verificando se o cliente está conectado
WiFiClient client= server.available();
if (!client) {
  return;
}

//espera ate enviar dados
Serial.println("novo cliente"); 
while (!client.available()){
  delay(1);
    
}
//LER A PRIMEIRA LINHA DO PEDIDO
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

//OPERACAO PEDIDO
int value = LOW;
if (request.indexOf("/LED=ON") != -1) {
  digitalWrite(ledPin, HIGH); // SE O PEDIDO NO LED PIN FOR LED=OFF ACENDE O LED VERMELHO
  value = HIGH ;
  delay(2000);
}
if (request.indexOf("/LED=OFF") != -1) {
  digitalWrite(ledPin, LOW); // SE O PEDIDO NO LED PIN FOR LED=OFF APAGA O LED VERMELHO
  value = LOW ;
  delay(1);
}

if(request.indexOf("/LED1=ON") != -1) {
  digitalWrite(ledPin1, HIGH); //se o pedido no ledpin for led on o led vermelho acende
  value = HIGH ;
  delay(2000);
}
if   (request.indexOf("/LED1=OFF") != -1) {
  digitalWrite(ledPin1, LOW);  
  value = LOW;
  delay(1);
}

// inicializacao do HTML

//RETORNO DA RESPOSTA
client.println("HTTP/1.1 200OK");
client.println("Content-type: text/html");
client.println(""); //nao esquecer
client.println("<!DOCTYPE HTML>");

client.print("TESTANDO WIFI ESP8266 - PIDEZZ");
if(value == HIGH) { // Se está ligado apresenta “on”
 
client.print("ON");
 
} else {
 
client.print("OFF");// Se está desligado apresenta “Off”
 
}
 
client.println("<br><br>");
 
client.println("<a href=\"/LED=ON\"\"><button>LIGAR VERMELHO </button></a>");// Ligar o LED corresponde Turn On
 
client.println("<a href=\"/LED=OFF\"\"><button>DESLIGAR VERMELHO </button></a><br />");  // Desligar o LED corresponde Turn Off
 
client.println("<a href=\"/LED1=ON\"\"><button>LIGAR VERDE </button></a>");
 
client.println("<a href=\"/LED1=OFF\"\"><button>Turn Off </button></a><br />");
 
client.println("</html>");
 
  
 
delay(1);
 
Serial.println("Cliente desconectado"); // Depois do cliente efectuar o pedido apresenta esta mensagem no monitor série
 
Serial.println("");
 
  
 


}
