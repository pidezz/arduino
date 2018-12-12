//projeto1 - led piscante 
int ledPin=5;
void setup() {
  pinMode(ledPin, OUTPUT);
  }

//REPETIDAS VEZES
void loop() { 
  //3 pontos
  for(int x=0;x<3; x++){
    digitalWrite(ledPin, HIGH); //acende o led
    delay(150);   //espera 150ms
    digitalWrite(ledPin, LOW);  //apaga o led
    delay(100);  //espera 100ms
  }
// espera 100ms para marcar o intervalo entre as letras
delay(100);
//3 traços
for (int x=0;x<3;x++){
  digitalWrite(ledPin, HIGH); //acende o led
  delay(400);     //espera 400ms
  digitalWrite(ledPin, LOW); //apaga o led
  delay(100);     //espera 100ms
  
}
//espera 100 ms para marcar o intervalo entre as letras 
delay(100);

//3 pontos novamente 
for (int x=0 ;x<3;x++){
  digitalWrite(ledPin, HIGH); 
  delay(150);
  digitalWrite(ledPin, LOW);
  delay(100);
}
delay(5000);
}
