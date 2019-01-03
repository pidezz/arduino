#include <ESP8266WiFi.h>

//WIFI
#define SSID_REDE  "P1d3zz"
#define SENHA_REDE  "987654321"
#define INTERVALO_ENVIO_THINGSPEAK 150000 //intervalo entre envios de dados ao ThingSpeak
#define pino_sinal_analogico A0
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
 //Funcao: faz leitura do nivel de umidade
 //parametro:nenhum
 //Retorno: umidade percentual (0-100)
 //observacao: o ADC do NodeMCU permite até no max 3.3v. Dessa forma 
 //para 3.3v obtem-se (empiricamente) 978 como leitura de ADC
 float FazLeituraUmidade(void)
 {
  int ValorADC;
  float UmidadePercentual;

  ValorADC = analogRead(0); //978 > 3.3
  Serial.print("[Leitura ADC] ");
  Serial.println(ValorADC);

//Quanto maior o numero lido do ADC, menor a umidade.
    //Sendo assim, calcula-se a porcentagem de umidade por:
    //      
    //   Valor lido                 Umidade percentual
    //      _    0                           _ 100
    //      |                                |   
    //      |                                |   
    //      -   ValorADC                     - UmidadePercentual 
    //      |                                |   
    //      |                                |   
    //     _|_  978                         _|_ 0
    //
    //   (UmidadePercentual-0) / (100-0)  =  (ValorADC - 978) / (-978)
    //      Logo:
    //      UmidadePercentual = 100 * ((978-ValorADC) / 978)  

    UmidadePercentual = 100 * ((1024-(float)ValorADC) /1024);
    Serial.print("[Umidade Percentual]");
    Serial.print(UmidadePercentual);
    Serial.println("%");

     return UmidadePercentual;
     }
     void setup()
     {
         Serial.begin(9600);
         lastConnectionTime = 0;
         FazConexaoWiFi(); //chama a funcao wifi
         Serial.println("ESP8266-NODEMCU");
      }
      //loop principal
      void loop()
      {
        float UmidadePercentualLida;
        int UmidadePercentualTruncada;
        char FieldUmidade[11];

        //Forca desconexao ao ThingSpeak 
        if (client.connected())
        {
          client.stop();
          Serial.println("- Desconectado do ThingSpeak");
          Serial.println();
        }

        UmidadePercentualLida = FazLeituraUmidade();
        UmidadePercentualTruncada = (int)UmidadePercentualLida; // trunca umidade como numero inteiro

        //Verifica se esta conectado no wifi e se é o momento de enviar dados ao ThingSpeak
        if(!client.connected() && (millis() - lastConnectionTime > INTERVALO_ENVIO_THINGSPEAK))
        {
          sprintf(FieldUmidade,"field2=%d",UmidadePercentualTruncada);
          EnviaInformacoesThingspeak(FieldUmidade);  
        }
        delay(1000);
      }
