#include <NTPClient.h>
#include <WiFiUDP.h>
#include <ESP8266WiFi.h>

WiFiUDP udp;
NTPClient ntp(udp, "0.br.pool.ntp.org", -3 * 3600, 60000);

const char* ssid = "Montalvao_2.4";
const char* senha = "20071990";

const char* horaAbrir = "19:11:15";
const char* horaFechar = "19:11:00";

const byte ledMovimento = 2;
const byte ledJanela = 16;
const byte chave = 12;

String horario;

void ICACHE_RAM_ATTR ativarSensor();

void setup()
{
   Serial.begin(9600);
   
   pinMode(chave, INPUT);
   pinMode(ledJanela, OUTPUT);
   pinMode(ledMovimento, OUTPUT);
   digitalWrite(ledJanela, HIGH);
   digitalWrite(ledMovimento, HIGH);
   attachInterrupt(digitalPinToInterrupt(chave),ativarSensor,CHANGE);

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, senha);
   Serial.print("Conecnato a rede: ");
   Serial.println(ssid);
   while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
   }
   Serial.println("\nConectado com sucesso");

   ntp.begin();
   
   Serial.print("\nAguardadndo sincronização");
   while(!ntp.update()){
      Serial.print(".");   
      ntp.forceUpdate();
      delay(500);
   }
   Serial.println("\nHorário sincronizado");
}

//simula o movimento de abrir a janela com o sinal do sensor de chuvar
void movimentoAbrir() {
   digitalWrite(ledMovimento, LOW);
   digitalWrite(ledJanela, HIGH);
   digitalWrite(ledMovimento, HIGH);
}

//simula o movimento de fechar a janela com o sinal do sensor de chuvar
void movimentoFechar() {
   digitalWrite(ledMovimento, LOW);
   digitalWrite(ledJanela, LOW);
   digitalWrite(ledMovimento, HIGH);
}

void ICACHE_RAM_ATTR ativarSensor() {
   if(digitalRead(chave) == LOW) {
      if(digitalRead(ledJanela) == LOW)
         movimentoAbrir();
   }

   if(digitalRead(chave) == HIGH) {
      if(digitalRead(ledJanela) == HIGH)
         movimentoFechar();
   }
}

void loop() {
   horario = ntp.getFormattedTime();
   Serial.println(horario);

   if(horario == horaFechar) {
      if(digitalRead(ledJanela) == HIGH){
         movimentoFechar();
      }
   }

   if (horario == horaAbrir) {
      if(digitalRead(chave) == LOW) {
         if(digitalRead(ledJanela) == LOW){
            movimentoAbrir();
         }  
      }
   }

   delay(1000);
}