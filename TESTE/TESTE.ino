#include <ESP8266WiFi.h>

//WIFI
#define SSID_REDE  "P1d3zz"
#define SENHA_REDE  "987654321"
#define INTERVALO_ENVIO_THINGSPEAK 30000 //intervalo entre envios de dados ao ThingSpeak
#define pino_sinal_analogico A0
#define pino_sinal_digital 7

// constantes e variaveis 
char EnderecoAPIThingSpeak[]= "api.thingspeak.com";
String ChaveEscritaThingSpeak= "V2KZXBI0FTJMHPPX";
long lastConnectionTime;

//long lastConnectionTime;
WiFiClient client;

//ThingSpeak Settings
const int channelID= 648118;

//prototypes
void EnviaInformacoesThingspeak(String StringDados);
void FazConexaoWiFi(void);
float FazLeituraUmidade(void);

//funcao: envia informações ao thingspeak
//parametros: string com a info a ser enviada
//retorno: nenhum

void EnviaInformacoesThingspeak(String StringDados)
 {
    if (client.connect(EnderecoAPIThingSpeak, 80))
    {
       //faz a requisicao HTTP ao ThingSpeak
       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY:" +ChaveEscritaThingSpeak+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(StringDados.length());
       client.print("\n\n");
       client.print(StringDados);

       lastConnectionTime = millis();
       Serial.println("- Informacoes enviadas");
    }
 }
 
//funcao: faz conexao wifi
void FazConexaoWiFi(void)
{
  client.stop();
  Serial.println("Conectando a rede WiFi...");
  Serial.println();
  delay(1000);
  WiFi.begin(SSID_REDE , SENHA_REDE);
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }

   Serial.println("");
   Serial.println("WiFi conectado");
   Serial.println("IP Obtido");
   Serial.println(WiFi.localIP());
   delay(1000);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode(pino_sinal_digital, INPUT);
  }
void loop() {
Serial.print("Digital:");
//SOLO UMIDO LED VERDE
if (digitalRead(pino_sinal_digital)){
     Serial.print("SEM UMIDADE");
     Serial.print(" ");
     } else{
  Serial.print("COM UMIDADE");
   }
  Serial.print("Analogico:");
  Serial.print(analogRead(pino_sinal_analogico));
  Serial.print(" ");
  Serial.print(" Status: ");
  if (analogRead(pino_sinal_analogico) > 700) {
  Serial.println("SOLO SECO");
 
  
    }else {
    Serial.println("SOLO MOLHADO");
      }
  
     }
