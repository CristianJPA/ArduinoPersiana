#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#define WIFI_SSID "VTR-1244526"
#define WIFI_PASSWORD "k5hMmmw9qzxk"
//#define WIFI_SSID "iPhone de Cristian"
//#define WIFI_PASSWORD "Cjpa132500"
#define FIREBASE_HOST "persiana-automatica-3b8f8-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "2czHLYZ8SGZ2XzLpv4DQyrCQ3IwWBrN0m6Aukcs2"
//librerias para getTime()
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//PINES
int LUZ=A0;//Fotoresistor
int switch1 = 5; //D3 ARRIBA
int switch2 = 4; //D4 ABAJO
int MOTORA = 14; //D5
int MOTORB = 12; //D6
//registroAutomatico
int tiempoMedicion = 15; //segundos
unsigned long tiempoAntMedicion = 0;
long randNumber; //NumeroRandom para ID
//Switches
int valorSwitch1;
int valorSwitch2;

void setup() {
  Serial.begin(9600);
  
  // Conectando A WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Conectando...");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  //Ya conectado al WIFI
  Serial.println();
  Serial.print("Conectado :D");
  Serial.print(WiFi.localIP());
  //Conexion a firebase
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  if (Firebase.failed()){
    Serial.println("Conexion con Firebase fallida :c");
    Serial.print(Firebase.error());
  } else {
    Serial.println("Conexion con Firebase exitosa!!! :D");
  }
  //////////////
  //PINMODE
  pinMode(LUZ,INPUT);
  pinMode(switch1,OUTPUT);
  pinMode(switch2,OUTPUT);
  pinMode(MOTORA ,OUTPUT);
  pinMode(MOTORB ,OUTPUT);   
  
}

void loop() {
  //Mensaje de Conexion WiFi y Firebase
  Serial.println("ESTOY EN LOOP CONECTADO WIFI:) ");
  //delay(1000);
//  if (Firebase.failed()){
//    Serial.println("Conexion con Firebase fallida :c");
//    Serial.print(Firebase.error());
//  } else {
//    Serial.println("Conexion con Firebase exitosa!!! :D");
//  }  

  //RECUPERANDO DATOS DE FIREBASE
  //Control
  int bajar = Firebase.getInt("Control/bajar");
  int detener = Firebase.getInt("Control/detener");
  int subir = Firebase.getInt("Control/subir");
  //Horario
  String horarioBajada = Firebase.getString("Horario/horarioBajada");
  String horarioSubida = Firebase.getString("Horario/horarioSubida");
  //Luminosidad
  int luminosidadBajada = Firebase.getInt("Luminosidad/luminosidadBajada");
  int luminosidadSubida = Firebase.getInt("Luminosidad/luminosidadSubida");
  //Luminosidad Sensor
  int cantidadLuz = analogRead(LUZ);
  int lum = map(cantidadLuz,0,1023,1,100);
  //API
   
  String Date = getDate();
//  Serial.println("Fecha API");
//  Serial.println(Date); 
  String Time = getTime();
  Serial.println("Horario API");
  Serial.println(Time); 

  //Almacenamiento del estado de los switch en las variables
  valorSwitch1 = digitalRead(switch1);
  valorSwitch2 = digitalRead(switch2);

  //Boton Subida ArrowUp
  if ((subir == 1)|| (horarioSubida == Time)||(cantidadLuz > luminosidadSubida)){
    if((valorSwitch1==0)&&(valorSwitch2==0)){      
        Serial.println("Estoy Subiendo :D"); 
        //digitalWrite(MOTORA , HIGH);
        //digitalWrite(MOTORB , LOW);
    }    
  }
  if ((subir == 1)|| (horarioSubida == Time)||(cantidadLuz > luminosidadSubida)){
    if((valorSwitch1==0)&&(valorSwitch2==0)){      
        
    }    
  }
  
  
  
//  if ((subir==1)&&(valorSwitch1==0)&&(valorSwitch2==0)|| (horarioSubida == Time)){
//    Serial.println("Estoy Subiendo :D"); 
//    digitalWrite(MOTORA,LOW);
//    digitalWrite(MOTORB,HIGH); 
//  }
    
//  
//   if((horarioSubida == Time) &&(valorSwitch1==1)&&(valorSwitch2==0)){
//    Serial.println("DETENIDO HORA c;"); 
//    digitalWrite(MOTORA,LOW);
//    digitalWrite(MOTORB,LOW);
//}
//// if((cantidadLuz > luminosidadSubida ) &&(valorSwitch1==1)&&(valorSwitch2==0)){
////    Serial.println("DETENIDO HORA c;"); 
////    digitalWrite(MOTORA,LOW);
////    digitalWrite(MOTORB,LOW);
////}
//  //Control de Subida | boton detener
//  if ((detener==1)&&(valorSwitch1==0)&&(valorSwitch2==0)&&(horarioSubida != Time)){
//    Serial.println("Se ha detenido :D"); 
//    digitalWrite(MOTORA,LOW);
//    digitalWrite(MOTORB,LOW);
//  }
//  
// 
//  //Boton Bajar ArrowDown
//  if ((bajar==1)&&(valorSwitch1==0)&&(valorSwitch2==0)|| (horarioBajada == Time )){
//    Serial.println("Estoy Bajando :D"); 
//    digitalWrite(MOTORA,HIGH);
//    digitalWrite(MOTORB,LOW);    
//  } 
//  if((horarioBajada == Time) &&(valorSwitch1==0)&&(valorSwitch2==1)){
//    Serial.println("DETENIDO HORA c;"); 
//    digitalWrite(MOTORA,LOW);
//    digitalWrite(MOTORB,LOW);
//  }
////  if((cantidadLuz < luminosidadBajada) &&(valorSwitch1==0)&&(valorSwitch2==1)){
////    Serial.println("DETENIDO HORA c;"); 
////    digitalWrite(MOTORA,LOW);
////    digitalWrite(MOTORB,LOW);
////}
// //Control de bajada | boton detener
//  if ((detener==1)&&(valorSwitch1==0)&&(valorSwitch2==0)&&(horarioBajada != Time)){
//    Serial.println("Se ha detenido :D"); 
//    digitalWrite(MOTORA,LOW);
//    digitalWrite(MOTORB,LOW);
//  }
//  
//
//
//
//  
//  if ((subir==1)&&(valorSwitch1==0)&&(valorSwitch2==1)){
//    digitalWrite(MOTORA,LOW);
//    digitalWrite(MOTORB,HIGH);
//  }
//  if ((subir==1)&&(valorSwitch1==1)&&(valorSwitch2==0)){
//    digitalWrite(MOTORA,LOW);
//    digitalWrite(MOTORB,LOW);
//  }
//  if ((bajar==1)&&(valorSwitch1==1)&&(valorSwitch2==0)){
//      digitalWrite(MOTORA,HIGH);
//      digitalWrite(MOTORB,LOW);
//  }
//   if ((bajar==1)&&(valorSwitch1==0)&&(valorSwitch2==1)){
//      digitalWrite(MOTORA,LOW);
//      digitalWrite(MOTORB,LOW);
//  }

  
  
  

  
  
//  Serial.print("sw1: ");
//  Serial.println(valorSwitch1);
//  Serial.print("sw2: ");
//  Serial.println(valorSwitch2);
//  Serial.println("bajar");
//  Serial.println(bajar); 
//  Serial.println("detener");
//  Serial.println(detener); 
//  Serial.println("subir");
//  Serial.println(subir); 
//  Serial.println("horarioBajada");
//  Serial.println(horarioBajada); 
//  Serial.println("horarioSubida");
//  Serial.println(horarioSubida); 
//  Serial.println("luminosidadBajada");
//  Serial.println(luminosidadBajada);
//  Serial.println("luminosidadSubida");
//  Serial.println(luminosidadSubida);
  Serial.println("cantidadLuz");
  Serial.println(cantidadLuz); 
//  

  //registroAutomatico
    //registroAutomatico(cantidadLuz);   
     
}



void ControladorMotor(){  
}
void registroAutomatico(int value){
  if (millis() - tiempoAntMedicion >= tiempoMedicion * 1000){
    //subimos Luminosidad al servidor
    tiempoAntMedicion = millis();
    Serial.println("registroAutomatico -> "); 
    Serial.println(value);
    String Time = getTime();
    String Date = getDate();
    String path = "Registro/"; 
    randNumber = random(1000);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();
    data["Voltaje"] = value;
    data["Id"] = randNumber;
    data["Hora"] = Time;
    data["Fecha"] = Date;
    Firebase.push(path,data);
  } 
}

String getTime() {
    WiFiClient client;
    HTTPClient http;  
    String timeS = "";
    
    http.begin(client, "http://worldtimeapi.org/api/timezone/America/Santiago");
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();          
          int beginS = payload.indexOf("datetime");
          int endS = payload.indexOf("day_of_week");
          //Serial.println(payload);
          timeS = payload.substring(beginS + 22, endS - 19);    
    }
    return timeS;
}
String getDate() {
    WiFiClient client;
    HTTPClient http;  
    String dateS = "";
    
    http.begin(client, "http://worldtimeapi.org/api/timezone/America/Santiago");
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();          
          int beginS = payload.indexOf("datetime");
          int endS = payload.indexOf("day_of_week");
          //Serial.println(payload);
          dateS = payload.substring(beginS + 11, endS - 25);    
    }
    return dateS;
}
