#define pino_sinal_analogico A0
#define pino_sinal_digital 8
#define vermelho 5
#define verde 7
int valor_analogico;
void setup() {
  Serial.begin(9600);
  pinMode(pino_sinal_digital, INPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(verde, OUTPUT);
 
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
  //LEDS ACESOS
   if (analogRead(pino_sinal_analogico) > 700) {
    Serial.println("SOLO SECO");
  apagaleds();
  digitalWrite(vermelho, HIGH);
    }else {
    Serial.println("SOLO MOLHADO");
    apagaleds();
    digitalWrite(verde, HIGH);
    
    }
  delay(100);
       }
       
  void apagaleds()
   { 
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, LOW);
   }
  // put your main code here, to run repeatedly:
