void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT); 
  
  
}
void retornoLed (){
  digitalWrite(8,HIGH);
   delay(100); //milisegundos
    digitalWrite(8,LOW); //desliga o led
   delay(80);

   digitalWrite(8,HIGH);
   delay(100); //milisegundos
    digitalWrite(8,LOW); //desliga o led
   delay(80);

   digitalWrite(8,HIGH);
   delay(100); //milisegundos
    digitalWrite(8,LOW); //desliga o led
   delay(80);

   digitalWrite(8,HIGH);
   delay(100); //milisegundos
    digitalWrite(8,LOW); //desliga o led
   delay(80);
        
   digitalWrite(8,HIGH);
   delay(100); //milisegundos
    digitalWrite(8,LOW); //desliga o led
   delay(800);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  piscaLED();
  retornoLed ();
  piscaAMVER();
  
   

}

void piscaLED(){
        
   
   digitalWrite(8,HIGH);
   delay(100); //milisegundos
    digitalWrite(8,LOW); //desliga o led
   delay(800);
   

   digitalWrite(9,HIGH);
   delay(1000);
   digitalWrite(9,LOW);
   delay(100);
   
   digitalWrite(10,HIGH);
   delay(1000);
   digitalWrite(10,LOW);
   delay(100);
}
void piscaAMVER(){ 
  
digitalWrite(9,HIGH);
   delay(1000);
   digitalWrite(9,LOW);
   delay(100);
   
   digitalWrite(10,HIGH);
   delay(1000);
   digitalWrite(10,LOW);
   delay(100);


}
