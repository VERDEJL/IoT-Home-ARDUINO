#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include<Servo.h>
#define cuartos 2
#define banio 3
#define sala 4
#define cochera 5
Servo motor;

char letra;
String cadena; 
char lastv;
int tiempoServo= 10;
int i=0;
String comando;
String dispositivo;

void DeserializeObject()
{
  String json = cadena;
  StaticJsonDocument<300> doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) { return; }
  String comando = doc["COMANDO"];
  String dispositivo = doc["LUGAR"];

  Serial.println(comando);
  Serial.println(dispositivo);
  cadena = " ";
  if (comando == "PRENDER"){
    if(dispositivo=="CUARTOS"){
      digitalWrite(cuartos,HIGH);
    }
    if(dispositivo=="SALA"){
      digitalWrite(sala,HIGH);
    }
    if(dispositivo=="BANIO"){
      digitalWrite(banio,HIGH);
    }
    if(dispositivo=="COCHERA"){
      digitalWrite(cochera,HIGH);
    }
  }
  if(comando == "APAGAR"){
    if(dispositivo=="CUARTOS"){
      digitalWrite(cuartos,LOW);
    }
    if(dispositivo=="SALA"){
      digitalWrite(sala,LOW);
    }
    if(dispositivo=="BANIO"){
      digitalWrite(banio,LOW);
    }
    if(dispositivo=="COCHERA"){
      digitalWrite(cochera,LOW);
    }
  }

  if(comando=="ABRIR" && dispositivo=="COCHERA"){
    AbrirPuerta();
  }
  if(comando=="CERRAR" && dispositivo=="COCHERA"){
    CerrarPuerta();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(cuartos,OUTPUT);//CUARTOS 
  pinMode(banio,OUTPUT);//BAÑO 
  pinMode(sala,OUTPUT);//SALA 
  pinMode(cochera,OUTPUT);//COCHERA 
  motor.attach(8); //SERVO
  motor.write(0);
}

void loop() {
  while (Serial.available() == 0) {} 
  cadena = Serial.readString();
  cadena.trim(); 
  if(cadena != ""){
    Serial.println(cadena);
    DeserializeObject();
  }
  delay(1000);
}


void AbrirPuerta(){
  for(i;i<180; i=i+1){
    motor.write(i);
    Serial.println(i);
    delay(tiempoServo);
  }
}

void CerrarPuerta(){
  for(i ;i>0; i=i-1){
    motor.write(i);
    Serial.println(i);
    delay(tiempoServo);
  }
}
