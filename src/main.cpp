#include <Arduino.h>



//definindo os os led que simulam a janela e o motor;
//ledJanela == HIGH => janela aberta
//ledJanela == LOW => janela fecha 
//ledMovimento == HIGH => motor trabalhando
//ledMovimento == LOW => motor parado
const byte ledMovimento = 2;
const byte ledJanela = 16;
const byte chave = 12;

void setup() {
  Serial.begin(9600);
  pinMode(chave, INPUT);
  pinMode(ledJanela, OUTPUT);
  pinMode(ledMovimento, OUTPUT);
  
}
//simula o movimento de abrir a janela com o sinal do sensor de chuvar
void movimentoAbrir() {
  digitalWrite(ledMovimento, LOW);
  delay(4000);
  digitalWrite(ledMovimento, HIGH);
  digitalWrite(ledJanela, LOW);
}

//simula o movimento de fechar a janela com o sinal do sensor de chuvar
void movimentoFechar() {
  digitalWrite(ledMovimento, LOW);
  delay(4000);
  digitalWrite(ledMovimento, HIGH);
  digitalWrite(ledJanela, HIGH);
}

void loop(){
  //put your main code here, to run repeatedly:
  if(digitalRead(chave) == HIGH){
    if(digitalRead(ledJanela) == HIGH)
      movimentoAbrir();
  }
  if(digitalRead(chave) == LOW){
    if(digitalRead(ledJanela) == LOW)
      movimentoFechar();
  }
}


  
